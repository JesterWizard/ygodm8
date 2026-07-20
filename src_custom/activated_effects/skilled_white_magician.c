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

#define SKILLED_WHITE_MAGICIAN_COUNTER_COST 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyHasBusterBlader(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == BUSTER_BLADER;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == BUSTER_BLADER)
      return TRUE;
  }

  return FALSE;
}

static u8 HasBusterBladerSource(void)
{
  u8 i;
  u8 fixedDuelist = FixedDuelistForActive();

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == BUSTER_BLADER)
      return TRUE;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, BUSTER_BLADER) >= 0)
    return TRUE;

  return GyHasBusterBlader(fixedDuelist);
}

static enum DuelActionResult SpecialSummonBusterBlader(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, BUSTER_BLADER, NULL, opts) == DUEL_ACTION_OK)
    return DUEL_ACTION_OK;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, BUSTER_BLADER, opts) == DUEL_ACTION_OK)
    return DUEL_ACTION_OK;

  return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, BUSTER_BLADER, opts);
}

unsigned char CanActivateSKILLED_WHITE_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SKILLED_WHITE_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SKILLED_WHITE_MAGICIAN)
    return FALSE;

  /* ponytail: Spell Counters on Spell resolve need spell-resolve hook.
   * Ceiling: ignition when unk4>=3; upgrade: on Spell resolve → unk4++ (cap 3). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (zone->unk4 < SKILLED_WHITE_MAGICIAN_COUNTER_COST)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasBusterBladerSource();
}

void ActivateSKILLED_WHITE_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(SKILLED_WHITE_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->unk4 < SKILLED_WHITE_MAGICIAN_COUNTER_COST || !HasBusterBladerSource())
    return;

  self->unk4 = (u8)(self->unk4 - SKILLED_WHITE_MAGICIAN_COUNTER_COST);
  ClearZone(self);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE || ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (SpecialSummonBusterBlader() != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
