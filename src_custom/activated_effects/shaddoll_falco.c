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

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static s16 FindShaddollGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsShaddollMonster(cardId) && cardId != SHADDOLL_FALCO
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsShaddollMonster(cardId) && cardId != SHADDOLL_FALCO
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonShaddollFaceDownDefFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForActive();
  s8 emptyZone;
  u16 cardId;
  enum DuelActionResult result;
  struct DuelCard *zone;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZone < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsShaddollMonster(cardId) || cardId == SHADDOLL_FALCO
        || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
    if (!IsShaddollMonster(cardId) || cardId == SHADDOLL_FALCO
        || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  }

  if (result != DUEL_ACTION_OK)
    return result;

  zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone];
  if (zone != NULL && zone->id != CARD_NONE) {
    zone->unk4 = 2;
    zone->isFaceUp = FALSE;
    zone->isDefending = TRUE;
    FlipCardFaceDown(zone);
  }

  return DUEL_ACTION_OK;
}

unsigned char CanActivateSHADDOLL_FALCO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != SHADDOLL_FALCO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != SHADDOLL_FALCO)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT SS 1 other Shaddoll from GY face-down DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindShaddollGyIndex() >= 0;
}

void ActivateSHADDOLL_FALCOEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(SHADDOLL_FALCO, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindShaddollGyIndex();
  if (gyIndex < 0)
    return;

  if (SpecialSummonShaddollFaceDownDefFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
