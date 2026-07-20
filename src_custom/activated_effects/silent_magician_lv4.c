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

static u8 HandHasSilentMagicianLv8(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == SILENT_MAGICIAN_LV8)
      return TRUE;
  }

  return FALSE;
}

static u16 FindSilentMagicianLv8InDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == SILENT_MAGICIAN_LV8)
      return SILENT_MAGICIAN_LV8;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonLv8(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasSilentMagicianLv8() || FindSilentMagicianLv8InDeck() != CARD_NONE;
}

unsigned char CanActivateSILENT_MAGICIAN_LV4(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_MAGICIAN_LV4)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV4)
    return FALSE;

  /* ponytail: Spell Counter place/ATK + Standby-after-5th counter need draw/
   * counter hooks. Ceiling: OPT send self → SS Silent Magician LV8 from hand/Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSpecialSummonLv8();
}

void ActivateSILENT_MAGICIAN_LV4Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(SILENT_MAGICIAN_LV4, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanSpecialSummonLv8())
    return;

  ClearZone(self);

  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, SILENT_MAGICIAN_LV8, NULL, opts)
      != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, SILENT_MAGICIAN_LV8, opts);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
