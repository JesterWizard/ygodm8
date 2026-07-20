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

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

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

static u8 HandHasLevel4Morphtronic(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLevel4Morphtronic(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasLevel4Morphtronic(void)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    return IsLevel4Morphtronic(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLevel4Morphtronic(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;
  }

  return FALSE;
}

static s8 FindGyLevel4MorphtronicIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

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

static enum DuelActionResult SpecialSummonGyLevel4Morphtronic(void)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 gyIndex = FindGyLevel4MorphtronicIndex(fixedDuelist);
  u16 cardId;

  if (gyIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts);
  }

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static u8 IsHandLevel4Morphtronic(u16 cardId)
{
  return IsLevel4Morphtronic(cardId);
}

unsigned char CanActivateMORPHTRONIC_CAMERAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_CAMERAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_CAMERAN)
    return FALSE;

  /* ponytail: DEF cannot-be-targeted continuous + battle-destroy trigger need
   * battle/continuous hooks. Ceiling: ATK OPT SS Lv4 Morphtronic from hand/GY. */
  if (zone->isDefending)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasLevel4Morphtronic() || GyHasLevel4Morphtronic();
}

void ActivateMORPHTRONIC_CAMERANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  Duel_ShowEffectTextTyped(MORPHTRONIC_CAMERAN, 2);

  if (self == NULL || IsDuelOver() == TRUE || self->isDefending)
    return;

  if (HandHasLevel4Morphtronic()) {
    if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsHandLevel4Morphtronic, opts)
        == DUEL_ACTION_OK)
      goto done;
  }

  if (GyHasLevel4Morphtronic()) {
    if (SpecialSummonGyLevel4Morphtronic() == DUEL_ACTION_OK)
      goto done;
  }

  return;

done:
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
