#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 HandHasSilentSwordsmanLv5(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == SILENT_SWORDSMAN_LV5)
      return TRUE;
  }

  return FALSE;
}

static u16 FindSilentSwordsmanLv5InDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == SILENT_SWORDSMAN_LV5)
      return SILENT_SWORDSMAN_LV5;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonLv5(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasSilentSwordsmanLv5() || FindSilentSwordsmanLv5InDeck() != CARD_NONE;
}

unsigned char CanActivateSILENT_SWORDSMAN_LV3(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_SWORDSMAN_LV3)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_SWORDSMAN_LV3)
    return FALSE;

  /* Spell-target negate via IsImmuneToHarmfulTargetedEffectsOnField; Standby send
   * self → SS LV5 wired below. summon/flip turn gate needs hooks. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSpecialSummonLv5();
}

void ActivateSILENT_SWORDSMAN_LV3Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(SILENT_SWORDSMAN_LV3, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanSpecialSummonLv5())
    return;

  ClearZone(self);

  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, SILENT_SWORDSMAN_LV5, NULL, opts)
      != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, SILENT_SWORDSMAN_LV5, opts);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
