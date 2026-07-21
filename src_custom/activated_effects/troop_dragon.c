#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "troop_dragon.h"

void UpdateDuelGfxExceptField(void);

static u8 sTroopDragonInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void TryTroopDragonSs(u8 fixedDuelist)
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
  if (Duel_FindDeckCardIndex(turnDuelist, TROOP_DRAGON) < 0)
    return;

  Duel_ShowEffectTextTyped(TROOP_DRAGON, 2);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(turnDuelist, TROOP_DRAGON, opts);
  UpdateDuelGfxExceptField();
}

static void OnTroopDragonBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != TROOP_DRAGON)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryTroopDragonSs(ev->controller);
}

void TroopDragon_EnsureInit(void)
{
  if (sTroopDragonInit)
    return;
  sTroopDragonInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnTroopDragonBattleDestroyed);
}

unsigned char CanActivateTROOP_DRAGON(void)
{
  if (gMonEffect.id != TROOP_DRAGON)
    return FALSE;

  /* Battle-destroy SS via TroopDragon_EnsureInit. */
  return FALSE;
}

void ActivateTROOP_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(TROOP_DRAGON, 2);
}
