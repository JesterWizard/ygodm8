#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsPlantMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_PLANT);
}

static u8 FindPlantGyIndex(u8 fixedDuelist, u8 *outIndex)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsPlantMonster(cardId)) {
      *outIndex = 0;
      return TRUE;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsPlantMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      *outIndex = i;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 IsOppDefenseMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return zone->isDefending == TRUE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return IsOppDefenseMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ZeroTargetAtkUntilEndOfTurn(struct DuelCard *zone)
{
  u16 atk;

  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  SetCardInfo(zone->id);
  atk = gCardInfo.atk;
  zone->tempStage = (s8)(-((s32)atk + 499) / 500);
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  ZeroTargetAtkUntilEndOfTurn(zone);
  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOppDefenseMonster(zone))
      continue;

    SetCardInfo(zone->id);
    if (bestCol == 0xFF || gCardInfo.atk > bestAtk) {
      bestAtk = gCardInfo.atk;
      bestCol = col;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateBLACK_ROSE_DRAGON(void)
{
  struct DuelCard *zone;
  u8 plantIndex;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != BLACK_ROSE_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLACK_ROSE_DRAGON)
    return FALSE;

  /* Ceiling: Synchro Summon destroy-all needs summon hook. Ceiling: OPT banish
   * 1 Plant from GY → opp DEF monster to ATK with 0 ATK (tempStage). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!FindPlantGyIndex(fixedDuelist, &plantIndex))
    return FALSE;

  return FieldHasTarget();
}

void ActivateBLACK_ROSE_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 plantIndex;
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(BLACK_ROSE_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!FindPlantGyIndex(fixedDuelist, &plantIndex))
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, plantIndex);
  GraveyardExpand_RefreshDisplay();
  UpdateDuelGfxExceptField();

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
