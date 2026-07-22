#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

extern const CardData gCardData_NEW[];

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sCrossKeeperInit APPEND_DATA = {0};
static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsCrossKeeperTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  if (Duel_IsElementalHeroCard(cardId))
    return TRUE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static s8 FindTargetHandZone(u8 skipZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  for (i = 0; i < max; i++) {
    if (i == skipZone)
      continue;

    if (IsCrossKeeperTarget(SixCardHand_ZoneAtHandRow(handRow, i)->id))
      return (s8)i;
  }

  return -1;
}

static u8 GyHasTarget(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsCrossKeeperTarget(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsCrossKeeperTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 HasSummonTarget(u8 skipHandZone)
{
  if (FindTargetHandZone(skipHandZone) >= 0)
    return TRUE;

  return GyHasTarget(FixedDuelistForActive());
}

static void MarkSummonedNegated(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= 0x80;
      return;
    }
  }
}

static enum DuelActionResult SpecialSummonTarget(u8 skipHandZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone = FindTargetHandZone(skipHandZone);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;
  u8 i;

  if (handZone >= 0)
    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsCrossKeeperTarget(cardId))
      return DUEL_ACTION_NO_TARGET;

    if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) != DUEL_ACTION_OK)
      return DUEL_ACTION_NO_TARGET;

    MarkSummonedNegated(cardId);
    return DUEL_ACTION_OK;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsCrossKeeperTarget(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      return DUEL_ACTION_NO_TARGET;

    MarkSummonedNegated(cardId);
    return DUEL_ACTION_OK;
  }

  return DUEL_ACTION_NO_TARGET;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static s8 FindCrossKeeperInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == CROSS_KEEPER)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == CROSS_KEEPER)
      return (s8)i;
  }
  return -1;
}

static u8 IsElementalHeroFusion(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (gCardData_NEW[cardId].color != FUSION_CARD)
    return FALSE;
  return Duel_IsElementalHeroCard(cardId);
}

/* Fusion leave ≈ E-HERO Fusion SS while CK in GY; draw1 stand-in for
 * banish→draw2→bottom. Upgrade: true SS trigger + banish cost. */
static void OnElementalHeroFusionLeaveWhileKeeperInGy(const struct EffectEvent *ev)
{
  u8 turnDuelist;

  if (ev == NULL || ev->cardId == CARD_NONE || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (!IsElementalHeroFusion(ev->cardId))
    return;
  if (EffectOpt_IsUsed(CROSS_KEEPER))
    return;
  if (FindCrossKeeperInGy(ev->controller) < 0)
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  Duel_ShowEffectTextTyped(CROSS_KEEPER, 8);
  if (Duel_DrawCards(turnDuelist, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(CROSS_KEEPER);
  UpdateDuelGfxExceptField();
}

void CrossKeeper_EnsureInit(void)
{
  if (sCrossKeeperInit)
    return;

  sCrossKeeperInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnElementalHeroFusionLeaveWhileKeeperInGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnElementalHeroFusionLeaveWhileKeeperInGy);
}

unsigned char CanActivateCROSS_KEEPER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CROSS_KEEPER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CROSS_KEEPER)
    return FALSE;

  /* GY Fusion-leave draw via CrossKeeper_EnsureInit.
   * send self → SS Elemental HERO or Neo-Spacian from hand/GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasSummonTarget(0xFF);
}

void ActivateCROSS_KEEPEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(CROSS_KEEPER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked() || !HasSummonTarget(0xFF))
    return;

  ClearZoneAndSendMonToGraveyard2(self, fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (SpecialSummonTarget(0xFF) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanActivateCrossKeeperFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != CROSS_KEEPER)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasSummonTarget(handZone);
}

u8 TryActivateCrossKeeperFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateCrossKeeperFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(CROSS_KEEPER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (SpecialSummonTarget(handZone) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateCrossKeeperFromHand(u8 handZone);
u8 TryActivateCrossKeeperFromHand(u8 handZone);
#endif
