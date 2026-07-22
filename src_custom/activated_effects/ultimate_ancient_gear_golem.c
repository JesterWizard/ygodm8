#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "ultimate_ancient_gear_golem.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sUltimateGolemInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static s16 FindAncientGearGolemInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == ANCIENT_GEAR_GOLEM)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ANCIENT_GEAR_GOLEM)
      return (s16)i;
  }
  return -1;
}

static void TrySsAncientGearGolem(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;
  if (FindAncientGearGolemInGy(fixedDuelist) < 0)
    return;

  Duel_ShowEffectTextTyped(ULTIMATE_ANCIENT_GEAR_GOLEM, 2);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, ANCIENT_GEAR_GOLEM, opts) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnUltimateGolemDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != ULTIMATE_ANCIENT_GEAR_GOLEM)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TrySsAncientGearGolem(ev->controller);
}

void UltimateAncientGearGolem_EnsureInit(void)
{
  if (sUltimateGolemInit)
    return;
  sUltimateGolemInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnUltimateGolemDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnUltimateGolemDestroyed);
}

unsigned char CanActivateULTIMATE_ANCIENT_GEAR_GOLEM(void)
{
  if (gMonEffect.id != ULTIMATE_ANCIENT_GEAR_GOLEM)
    return FALSE;

  /* Pierce/S/T lock via Ancient Gear helpers;
   * destroy SS via UltimateAncientGearGolem_EnsureInit. */
  return FALSE;
}

void ActivateULTIMATE_ANCIENT_GEAR_GOLEMEffect(void)
{
  Duel_ShowEffectTextTyped(ULTIMATE_ANCIENT_GEAR_GOLEM, 2);
}
