#include "global.h"
#include "common-chax.h"
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

static u8 IsTrapCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_TRAP;
}

static s16 FindTrapGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsTrapCard(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsTrapCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 SetTrapFromGy(s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s8 empty;
  struct DuelCard *slot;
  u16 cardId;

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsTrapCard(cardId))
      return FALSE;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
    if (!IsTrapCard(cardId))
      return FALSE;
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
  }

  slot = gTurnZones[ACTIVE_DUELIST_BACKROW][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

unsigned char CanActivateBLUE_EYES_TYRANT_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLUE_EYES_TYRANT_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLUE_EYES_TYRANT_DRAGON)
    return FALSE;

  /* ponytail: multi-attack + Trap immunity + battle-end Set need battle/permanent
   * hooks. Ceiling: OPT Set 1 Trap from GY to backrow. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) < 0)
    return FALSE;

  return FindTrapGyIndex() >= 0;
}

void ActivateBLUE_EYES_TYRANT_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(BLUE_EYES_TYRANT_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindTrapGyIndex();
  if (gyIndex < 0)
    return;

  if (!SetTrapFromGy(gyIndex))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
