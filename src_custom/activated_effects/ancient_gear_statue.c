#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearGolemName[] APPEND_RODATA = "Ancient Gear Golem";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountMonstersInRow(struct DuelCard **row)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (row[col] != NULL && row[col]->id != CARD_NONE
        && GetTypeGroup(row[col]->id) == TYPE_GROUP_MONSTER)
      count++;
  }

  return count;
}

static u8 OppHasMoreMonsters(void)
{
  return CountMonstersInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
      > CountMonstersInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
}

static u8 IsGolemOrMentionsGolem(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_STATUE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM)
    return TRUE;

  return Duel_CardNameContains(cardId, sAncientGearGolemName);
}

static u16 FindGolemTargetInHand(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if (IsGolemOrMentionsGolem(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindGolemTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGolemOrMentionsGolem(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanTributeSsGolem(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Self occupies a zone; after tribute there is room. */
  return FindGolemTargetInDeck() != CARD_NONE || FindGolemTargetInHand() != CARD_NONE;
}

unsigned char CanActivateANCIENT_GEAR_STATUE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_STATUE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_STATUE)
    return FALSE;

  /* Ceiling: OPT tribute self → SS AG Golem / mentions-Golem from hand/Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanTributeSsGolem();
}

void ActivateANCIENT_GEAR_STATUEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_STATUE, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanTributeSsGolem())
    return;

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  cardId = FindGolemTargetInDeck();
  if (cardId != CARD_NONE) {
    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_OK)
      goto done;
  }

  cardId = FindGolemTargetInHand();
  if (cardId == CARD_NONE)
    return;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, cardId, NULL, opts) != DUEL_ACTION_OK)
    return;

done:
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonAncientGearStatueFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ANCIENT_GEAR_STATUE)
    return FALSE;

  if (!OppHasMoreMonsters())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAncientGearStatueFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAncientGearStatueFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_STATUE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* FromHand SS when opp has more monsters; once-per-turn not tracked. */
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAncientGearStatueFromHand(u8 handZone);
u8 TrySpecialSummonAncientGearStatueFromHand(u8 handZone);
#endif
