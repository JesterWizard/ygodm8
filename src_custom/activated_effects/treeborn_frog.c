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

static u8 ControlsTreebornFrog(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == TREEBORN_FROG)
      return TRUE;
  }

  return FALSE;
}

static u8 ControlsSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[ACTIVE_DUELIST_BACKROW][col]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static s16 FindTreebornInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == TREEBORN_FROG)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == TREEBORN_FROG)
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonTreebornFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != TREEBORN_FROG)
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, TREEBORN_FROG, opts);
  }

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex) != TREEBORN_FROG)
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, TREEBORN_FROG, opts);
}

unsigned char CanActivateTREEBORN_FROG(void)
{
  if (gMonEffect.id != TREEBORN_FROG)
    return FALSE;

  /* ponytail: Standby Phase GY trigger needs phase hook + GY-menu wire.
   * Ceiling: GY ignition when no S/T, no Treeborn on field, empty monster
   * zone (Malicious pattern). */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindTreebornInGy() < 0)
    return FALSE;

  if (ControlsTreebornFrog())
    return FALSE;

  if (ControlsSpellTrap())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateTREEBORN_FROGEffect(void)
{
  s16 gyIndex;

  Duel_ShowEffectTextTyped(TREEBORN_FROG, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindTreebornInGy();
  if (gyIndex < 0 || ControlsTreebornFrog() || ControlsSpellTrap())
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (SpecialSummonTreebornFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
