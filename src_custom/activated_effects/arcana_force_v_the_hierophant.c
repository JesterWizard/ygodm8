#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 NameAlreadyUsed(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == cardId)
      return TRUE;
  }

  return FALSE;
}

static u16 FindArcanaForceInDeck(u8 maxLevel, u8 requireNewName)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsArcanaForceMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    if (maxLevel != 0 && gCardData_NEW[cardId].level > maxLevel)
      continue;

    if (requireNewName && NameAlreadyUsed(cardId))
      continue;

    return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateARCANA_FORCE_V_THE_HIEROPHANT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARCANA_FORCE_V_THE_HIEROPHANT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARCANA_FORCE_V_THE_HIEROPHANT)
    return FALSE;

  /* ponytail: on-Summon coin + discard summon-lock need summon/FromHand paths.
   * Ceiling: OPT coin → SS 1 Arcana Force from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindArcanaForceInDeck(4, TRUE) != CARD_NONE
      || FindArcanaForceInDeck(0, FALSE) != CARD_NONE;
}

void ActivateARCANA_FORCE_V_THE_HIEROPHANTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_V_THE_HIEROPHANT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (RandRangeU8(0, 1) == 1)
    cardId = FindArcanaForceInDeck(4, TRUE);
  else
    cardId = FindArcanaForceInDeck(0, FALSE);

  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanActivateArcanaForceVTheHierophantFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == ARCANA_FORCE_V_THE_HIEROPHANT;
}

u8 TryActivateArcanaForceVTheHierophantFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateArcanaForceVTheHierophantFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_V_THE_HIEROPHANT, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* ponytail: discard only; opp cannot respond to Arcana Summons needs turn flag hook. */
  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateArcanaForceVTheHierophantFromHand(u8 handZone);
u8 TryActivateArcanaForceVTheHierophantFromHand(u8 handZone);
#endif
