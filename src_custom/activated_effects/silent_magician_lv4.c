#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "silent_magician_lv4.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void RefreshFieldMonsterStatOverlays(void);

#define SILENT_MAGICIAN_LV4_COUNTER_ATK 500
#define SILENT_MAGICIAN_LV4_STANDBY_COUNTERS 5

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

static void IncrementCounterOnZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV4 || !zone->isFaceUp)
    return;

  if (zone->unk4 < 126)
    zone->unk4++;
}

u8 SilentMagicianLv4_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u32 atk;

  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV4)
    return FALSE;

  SetCardInfo(zone->id);
  atk = (u32)gCardInfo.atk + (u32)zone->unk4 * SILENT_MAGICIAN_LV4_COUNTER_ATK;
  Duel_WriteCardInfoStats(zone->id, Duel_ClampStat(atk), gCardInfo.def);
  return TRUE;
}

void SilentMagicianLv4_NoteSpellResolved(void)
{
  u8 fixedRow;
  u8 col;

  if (IsDuelOver() == TRUE)
    return;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      IncrementCounterOnZone(gFixedZones[fixedRow][col]);
  }

  RefreshFieldMonsterStatOverlays();
}

static u8 TryStandbyEvolve(struct DuelCard *zone)
{
  struct DuelSummonOpts opts;

  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV4 || zone->unk4 != SILENT_MAGICIAN_LV4_STANDBY_COUNTERS)
    return FALSE;

  if (!CanSpecialSummonLv8())
    return FALSE;

  Duel_ShowEffectTextTyped(SILENT_MAGICIAN_LV4, 9);
  ClearZone(zone);
  if (IsDuelOver() == TRUE)
    return TRUE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, SILENT_MAGICIAN_LV8, NULL, opts)
      != DUEL_ACTION_OK)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, SILENT_MAGICIAN_LV8, opts);

  UpdateDuelGfxExceptField();
  return TRUE;
}

void TryApplySilentMagicianLv4Standby(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (TryStandbyEvolve(zone))
      return;
  }
}

unsigned char CanActivateSILENT_MAGICIAN_LV4(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SILENT_MAGICIAN_LV4)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SILENT_MAGICIAN_LV4)
    return FALSE;

  /* Spell Counter ATK via SilentMagicianLv4_ApplyDynamicZoneStats; Standby evolve
   * via TryApplySilentMagicianLv4Standby; counters on spell resolve.
   * Ceiling: OPT send self → SS LV8 from hand/Deck. */
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
