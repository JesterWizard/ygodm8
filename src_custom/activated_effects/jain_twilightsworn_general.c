#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 HandHasLightsworn(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsLightswornMonster(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornMonster(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 HasLightswornInHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  return HandHasLightsworn() || GyHasLightsworn(fixedDuelist);
}

static u8 BanishOneLightswornFromHandOrGy(u8 *outLevel)
{
  u8 col;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = gTurnHands[ACTIVE_DUELIST][col];
    u16 cardId = slot->id;

    if (!IsLightswornMonster(cardId))
      continue;

    *outLevel = gCardData_NEW[cardId].level;
    if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    return TRUE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (!IsLightswornMonster(cardId))
      return FALSE;

    *outLevel = gCardData_NEW[cardId].level;
    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsLightswornMonster(cardId))
      continue;

    *outLevel = gCardData_NEW[cardId].level;
    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    return TRUE;
  }

  return FALSE;
}

static u8 IsFaceUpMonsterTarget(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  return IsFaceUpMonsterTarget(gFixedZones[fixedRow][fixedCol]);
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ApplyLevelReduction(struct DuelCard *zone, u8 level)
{
  s8 stages = (s8)(-((s32)level * 300 + 499) / 500);

  /* Until End Phase via ResetTempStagesForAllCards at EP. */
  zone->tempStage = stages;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 level;

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  level = self->unkThree;
  if (level == 0)
    return;

  ApplyLevelReduction(zone, level);
  self->unkThree = 0;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

static void CancelTargeting(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (self != NULL)
    self->unkThree = 0;

  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = Duel_GetZoneFinalAtk(zone);
      if (bestCol < 0 || atk > bestAtk) {
        bestCol = (s8)col;
        bestAtk = atk;
        *outRow = row;
      }
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateJAIN_TWILIGHTSWORN_GENERAL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != JAIN_TWILIGHTSWORN_GENERAL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != JAIN_TWILIGHTSWORN_GENERAL)
    return FALSE;

  /* Ceiling: other-Lightsworn-activated mill 2 needs chain hook. OPT banish 1
   * Lightsworn from hand/GY → weaken 1 face-up monster. EP mill 2 via
   * TryApplyTwilightswornEndPhase. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HasLightswornInHandOrGy() && FieldHasTarget();
}

void ActivateJAIN_TWILIGHTSWORN_GENERALEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 level = 0;

  Duel_ShowEffectTextTyped(JAIN_TWILIGHTSWORN_GENERAL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!BanishOneLightswornFromHandOrGy(&level) || level == 0)
    return;

  self->unkThree = level;

  if (IsDuelOver() == TRUE || !FieldHasTarget())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
