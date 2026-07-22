#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void FlipCardFaceDown(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyHasMonster(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedDuelist, i)) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

static u8 BanishOneMonsterFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    return TRUE;
  }

  return FALSE;
}

static u8 IsEffectMonsterFaceUp(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!IsCardFaceUp(zone) && zone->isDefending)
    return FALSE;

  SetCardInfo(zone->id);
  if (gCardInfo.color == EFFECT_CARD)
    return TRUE;

  return gCardInfo.monsterEffect != 0;
}

static u8 FieldHasEffectMonsterFaceUp(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsEffectMonsterFaceUp(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveFlipFaceDown(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsEffectMonsterFaceUp(fixedRow, fixedCol) || zone == NULL)
    return;

  zone->isDefending = TRUE;
  FlipCardFaceDown(zone);
  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickFlipTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsEffectMonsterFaceUp(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateTHE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO)
    return FALSE;

  /* Quick via Sanctuary + GY add Sanctuary FALSE.
   * OPT banish 1 monster from GY → flip 1 Effect Monster face-down DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!GyHasMonster())
    return FALSE;

  return FieldHasEffectMonsterFaceUp();
}

void ActivateTHE_EXECUTOR_OF_THE_UNDERWORLD_PLUTOEffect(void)
{
  Duel_ShowEffectTextTyped(THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (!BanishOneMonsterFromGy())
    return;

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsEffectMonsterFaceUp, ResolveFlipFaceDown, CancelTargeting,
                     AiPickFlipTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
