#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "green_baboon_defender_of_the_forest.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define GREEN_BABOON_LP_COST 1000

static u8 sBaboonInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 CanPayGreenBaboonCostFixed(u8 fixedDuelist)
{
  return gDuelLifePoints[fixedDuelist] >= GREEN_BABOON_LP_COST;
}

static u8 HandHasBaboon(u8 turnDuelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == GREEN_BABOON_DEFENDER_OF_THE_FOREST)
      return TRUE;
  }
  return FALSE;
}

static s16 FindBaboonInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard
        == GREEN_BABOON_DEFENDER_OF_THE_FOREST)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == GREEN_BABOON_DEFENDER_OF_THE_FOREST)
      return (s16)i;
  }
  return -1;
}

static void TryBaboonSsOnBeastDestroy(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s16 gyIndex;

  if (!CanPayGreenBaboonCostFixed(fixedDuelist))
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;
  if (!HandHasBaboon(turnDuelist) && FindBaboonInGy(fixedDuelist) < 0)
    return;

  Duel_ShowEffectTextTyped(GREEN_BABOON_DEFENDER_OF_THE_FOREST, 2);
  if (Duel_ChangeLp(turnDuelist, -(s32)GREEN_BABOON_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
  if (IsDuelOver() == TRUE)
    return;

  if (HandHasBaboon(turnDuelist)) {
    Duel_SpecialSummonFromHand(turnDuelist, GREEN_BABOON_DEFENDER_OF_THE_FOREST, NULL,
                               opts);
    UpdateDuelGfxExceptField();
    return;
  }

  gyIndex = FindBaboonInGy(fixedDuelist);
  if (gyIndex < 0)
    return;
  if (GraveyardExpand_IsEnabled()) {
    GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    Duel_SpecialSummonMonsterId(turnDuelist, GREEN_BABOON_DEFENDER_OF_THE_FOREST, opts);
  } else {
    Duel_SpecialSummonFromGrave(turnDuelist, GREEN_BABOON_DEFENDER_OF_THE_FOREST, opts);
  }
  UpdateDuelGfxExceptField();
}

static void OnBeastEffectDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId == CARD_NONE)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;
  if (ev->cardId == GREEN_BABOON_DEFENDER_OF_THE_FOREST)
    return;
  if (!Duel_CardHasMonsterType(ev->cardId, TYPE_BEAST))
    return;

  TryBaboonSsOnBeastDestroy(ev->controller);
}

void GreenBaboon_EnsureInit(void)
{
  if (sBaboonInit)
    return;
  sBaboonInit = TRUE;
  /* Effect destroy only (printed: except Damage Step). */
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnBeastEffectDestroyed);
}

unsigned char CanActivateGREEN_BABOON_DEFENDER_OF_THE_FOREST(void)
{
  if (gMonEffect.id != GREEN_BABOON_DEFENDER_OF_THE_FOREST)
    return FALSE;

  /* Beast-destroy SS via GreenBaboon_EnsureInit; hand path uses FromHand. */
  return FALSE;
}

void ActivateGREEN_BABOON_DEFENDER_OF_THE_FORESTEffect(void)
{
  Duel_ShowEffectTextTyped(GREEN_BABOON_DEFENDER_OF_THE_FOREST, 2);
}

u8 CanSpecialSummonGreenBaboonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;
  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GREEN_BABOON_DEFENDER_OF_THE_FOREST)
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;
  return CanPayGreenBaboonCostFixed(
      gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT);
}

u8 TrySpecialSummonGreenBaboonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonGreenBaboonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GREEN_BABOON_DEFENDER_OF_THE_FOREST, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;
  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)GREEN_BABOON_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;
  if (IsDuelOver() == TRUE)
    return TRUE;
  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
