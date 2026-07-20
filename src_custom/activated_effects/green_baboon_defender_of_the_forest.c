#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define GREEN_BABOON_LP_COST 1000

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayGreenBaboonCost(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  return gDuelLifePoints[fixedDuelist] >= GREEN_BABOON_LP_COST;
}

static u8 PayGreenBaboonCost(void)
{
  if (!CanPayGreenBaboonCost())
    return FALSE;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)GREEN_BABOON_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  return TRUE;
}

static s16 FindGreenBaboonInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard
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

static enum DuelActionResult SpecialSummonGreenBaboon(u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateGREEN_BABOON_DEFENDER_OF_THE_FOREST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GREEN_BABOON_DEFENDER_OF_THE_FOREST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone != NULL && zone->id == GREEN_BABOON_DEFENDER_OF_THE_FOREST)
    return FALSE;

  /* ponytail: hand/GY SS when your face-up Beast is destroyed needs destroy
   * trigger hook. Ceiling: GY ignition like Malicious — pay 1000 LP then SS;
   * hand path uses FromHand wire. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindGreenBaboonInGy() < 0)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return CanPayGreenBaboonCost();
}

void ActivateGREEN_BABOON_DEFENDER_OF_THE_FORESTEffect(void)
{
  s16 gyIndex;
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(GREEN_BABOON_DEFENDER_OF_THE_FOREST, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindGreenBaboonInGy();
  if (gyIndex < 0)
    return;

  if (!PayGreenBaboonCost())
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
  } else {
    GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
  }

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  SpecialSummonGreenBaboon(GREEN_BABOON_DEFENDER_OF_THE_FOREST);
  UpdateDuelGfxExceptField();
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

  return CanPayGreenBaboonCost();
}

u8 TrySpecialSummonGreenBaboonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonGreenBaboonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GREEN_BABOON_DEFENDER_OF_THE_FOREST, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!PayGreenBaboonCost())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
}
