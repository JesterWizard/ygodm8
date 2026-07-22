#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindAncientGearGolemInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == ANCIENT_GEAR_GOLEM)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ANCIENT_GEAR_GOLEM)
      return (s16)i;
  }

  return -1;
}

unsigned char CanActivateULTIMATE_ANCIENT_GEAR_GOLEM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ULTIMATE_ANCIENT_GEAR_GOLEM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ULTIMATE_ANCIENT_GEAR_GOLEM)
    return FALSE;

  /* Attack S/T lock via AncientGear_AttackerBlocksOppSpellTrap;
   * pierce via ApplyAncientGearGolemPiercingBattleEffect.
   * ponytail: on-destroy SS need destroy hook.
   * Ceiling: OPT SS Ancient Gear Golem from GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindAncientGearGolemInGy() >= 0;
}

void ActivateULTIMATE_ANCIENT_GEAR_GOLEMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(ULTIMATE_ANCIENT_GEAR_GOLEM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0
      || FindAncientGearGolemInGy() < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
