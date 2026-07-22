#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
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

static u8 IsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 IsLevel4DarkMonster(u16 cardId)
{
  if (!IsDarkMonster(cardId))
    return FALSE;

  return gCardInfo.level == 4;
}

static s16 FindLevel4DarkGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsLevel4DarkMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLevel4DarkMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonLevel4DarkFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsLevel4DarkMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsLevel4DarkMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateDARK_HORUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_HORUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_HORUS)
    return FALSE;

  /* Ceiling: after opp Main Phase Spell resolve trigger needs spell hook.
   * OPT SS 1 Lv4 DARK from GY while face-up (EffectOpt). */
  if (EffectOpt_IsUsed(DARK_HORUS))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindLevel4DarkGyIndex() >= 0;
}

void ActivateDARK_HORUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(DARK_HORUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(DARK_HORUS))
    return;

  gyIndex = FindLevel4DarkGyIndex();
  if (gyIndex < 0)
    return;

  if (SpecialSummonLevel4DarkFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(DARK_HORUS);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
