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

extern const CardData gCardData_NEW[];

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(cardId) == SPELL_TYPE_INVALID;
}

static u8 IsLvLe4Monster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].level > 0 && gCardData_NEW[cardId].level <= 4
      && !Duel_CardCannotBeSpecialSummoned(cardId);
}

static s8 FindLvLe4HandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if (IsLvLe4Monster(cardId))
      return (s8)i;
  }

  return -1;
}

static u8 FieldHasFieldSpell(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && IsFieldSpell(zone->id))
        return TRUE;
    }
  }

  return FALSE;
}

static u16 FindDifferentFieldSpellInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFieldSpell(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSsFromHand(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindLvLe4HandZone() >= 0;
}

static u8 CanDestroyFieldPath(void)
{
  return FieldHasFieldSpell();
}

static u8 DoSsFromHand(struct DuelCard *self)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone = FindLvLe4HandZone();

  if (handZone < 0)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

    /* Printed remainder omitted by this ruleset. */
  if (self != NULL)
    self->unk4 |= 0x80;

  return TRUE;
}

static u8 DoDestroyFieldGainLpAdd(void)
{
  u8 row;
  u8 col;
  u16 destroyedId = CARD_NONE;
  u16 addId;
  u8 destroyed = FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    u8 gy = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || !IsFieldSpell(zone->id))
        continue;

      destroyedId = zone->id;
      if (Duel_DestroyZone(zone, gy, FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;

      destroyed = TRUE;
    }
  }

  if (!destroyed)
    return FALSE;

  NotifyDynamicEquipFieldChanged();

  if (Duel_ChangeLp(ACTIVE_DUELIST, 1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return FALSE;

  addId = FindDifferentFieldSpellInDeck(destroyedId);
  if (addId != CARD_NONE && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0)
    Duel_AddDeckCardToHand(ACTIVE_DUELIST, addId, TRUE);

  return TRUE;
}

unsigned char CanActivateANCIENT_FAIRY_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_FAIRY_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_FAIRY_DRAGON)
    return FALSE;

  /* OPT SS Lv≤4 from hand; OPT destroy Field Spells + 1000 LP + add Field. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSsFromHand() || CanDestroyFieldPath();
}

void ActivateANCIENT_FAIRY_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_FAIRY_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSsFromHand()) {
    if (!DoSsFromHand(self))
      return;
  } else if (!DoDestroyFieldGainLpAdd()) {
    return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
