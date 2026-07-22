#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define SKILLED_DARK_MAGICIAN_COUNTER_COST 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyHasDarkMagician(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == DARK_MAGICIAN;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_MAGICIAN)
      return TRUE;
  }

  return FALSE;
}

static u8 HasDarkMagicianSource(void)
{
  u8 i;
  u8 fixedDuelist = FixedDuelistForActive();

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == DARK_MAGICIAN)
      return TRUE;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN) >= 0)
    return TRUE;

  return GyHasDarkMagician(fixedDuelist);
}

static enum DuelActionResult SpecialSummonDarkMagician(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, DARK_MAGICIAN, NULL, opts) == DUEL_ACTION_OK)
    return DUEL_ACTION_OK;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, DARK_MAGICIAN, opts) == DUEL_ACTION_OK)
    return DUEL_ACTION_OK;

  return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, DARK_MAGICIAN, opts);
}

unsigned char CanActivateSKILLED_DARK_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SKILLED_DARK_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SKILLED_DARK_MAGICIAN)
    return FALSE;

  /* Spell Counters on resolve via TryIncrementSpellCountersOnSpellResolve.
   * Ignition when unk4>=3. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->unk4 < SKILLED_DARK_MAGICIAN_COUNTER_COST)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasDarkMagicianSource();
}

void ActivateSKILLED_DARK_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SKILLED_DARK_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->unk4 < SKILLED_DARK_MAGICIAN_COUNTER_COST || !HasDarkMagicianSource())
    return;

  self->unk4 = (u8)(self->unk4 - SKILLED_DARK_MAGICIAN_COUNTER_COST);
  ClearZone(self);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE || ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (SpecialSummonDarkMagician() != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
