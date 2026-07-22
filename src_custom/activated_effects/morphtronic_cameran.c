#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "morphtronic_cameran.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sCameranInit APPEND_DATA = {0};
static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsLevel4Morphtronic(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sMorphtronicName))
    return FALSE;
  if (cardId == MORPHTRONIC_CAMERAN)
    return FALSE;
  return gCardData_NEW[cardId].level <= 4;
}

static u8 HandHasLevel4Morphtronic(u8 turnDuelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLevel4Morphtronic(gTurnHands[turnDuelist][i]->id))
      return TRUE;
  }
  return FALSE;
}

static u8 GyHasLevel4Morphtronic(u8 turnDuelist, u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

    return IsLevel4Morphtronic(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLevel4Morphtronic(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;
  }
  return FALSE;
}

static s8 FindGyLevel4MorphtronicIndex(u8 turnDuelist, u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

    if (IsLevel4Morphtronic(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;
    return -1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (IsLevel4Morphtronic(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s8)(i - 1);
  }
  return -1;
}

static enum DuelActionResult SpecialSummonGyLevel4Morphtronic(u8 turnDuelist, u8 fixedDuelist)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 gyIndex = FindGyLevel4MorphtronicIndex(turnDuelist, fixedDuelist);
  u16 cardId;

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (!GraveyardExpand_IsEnabled())
    return Duel_SpecialSummonFromGrave(turnDuelist, CARD_NONE, opts);

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void TryCameranBattleDestroySs(u8 fixedDuelist, struct DuelCard *zone)
{
  u8 turnDuelist;
  u8 monsterRow;
  struct DuelSummonOpts opts;

  /* ATK-position battle-destroy only. */
  if (zone != NULL && zone->isDefending)
    return;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;
  if (!HandHasLevel4Morphtronic(turnDuelist)
      && !GyHasLevel4Morphtronic(turnDuelist, fixedDuelist))
    return;

  Duel_ShowEffectTextTyped(MORPHTRONIC_CAMERAN, 2);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (HandHasLevel4Morphtronic(turnDuelist)) {
    if (Duel_SpecialSummonFromHand(turnDuelist, CARD_NONE, IsLevel4Morphtronic, opts)
        == DUEL_ACTION_OK)
      goto done;
  }

  if (GyHasLevel4Morphtronic(turnDuelist, fixedDuelist)) {
    if (SpecialSummonGyLevel4Morphtronic(turnDuelist, fixedDuelist) == DUEL_ACTION_OK)
      goto done;
  }
  return;

done:
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void OnCameranBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != MORPHTRONIC_CAMERAN)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryCameranBattleDestroySs(ev->controller, ev->zone);
}

void MorphtronicCameran_EnsureInit(void)
{
  if (sCameranInit)
    return;
  sCameranInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnCameranBattleDestroyed);
}

unsigned char CanActivateMORPHTRONIC_CAMERAN(void)
{
  if (gMonEffect.id != MORPHTRONIC_CAMERAN)
    return FALSE;

  /* ATK battle-destroy SS via MorphtronicCameran_EnsureInit.
   * ponytail: DEF Morphtronic untargetable needs targeting gate. */
  return FALSE;
}

void ActivateMORPHTRONIC_CAMERANEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_CAMERAN, 2);
}
