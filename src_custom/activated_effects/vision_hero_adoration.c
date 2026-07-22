#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static const char sHeroName[] APPEND_RODATA = "HERO";

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

static u8 IsValidHeroTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != gMonEffect.row)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || zone->id == VISION_HERO_ADORATION)
    return FALSE;

  if (!IsHeroMonster(zone->id) || !IsFaceUpMonsterZone(zone))
    return FALSE;

  return TRUE;
}

static u8 IsValidOpponentTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsFaceUpMonsterZone(zone);
}

static u8 FieldHasHeroTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidHeroTarget(gMonEffect.row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasOpponentTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOpponentTarget(OpponentMonsterRow(), col))
      return TRUE;
  }

  return FALSE;
}

static void ApplyAdorationReduction(struct DuelCard *heroZone, struct DuelCard *oppZone)
{
  u16 heroAtk = Duel_GetZoneFinalAtk(heroZone);
  s8 stages;

  if (heroAtk == 0)
    return;

  stages = (s8)(-((s32)heroAtk + 499) / 500);
  /* Until End Phase via ResetTempStagesForAllCards at EP. */
  oppZone->tempStage = stages;
}

static void BeginOpponentTargetPick(u8 heroCol);

static void ResolveOpponentTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *oppZone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *heroZone;

  if (!IsValidOpponentTarget(fixedRow, fixedCol) || oppZone == NULL || self == NULL)
    return;

  heroZone = gFixedZones[gMonEffect.row][self->unkThree];
  if (heroZone == NULL || !IsValidHeroTarget(gMonEffect.row, self->unkThree))
    return;

  ApplyAdorationReduction(heroZone, oppZone);
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

static u8 AiPickOpponentTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = OpponentMonsterRow();
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidOpponentTarget(*outRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

static void BeginOpponentTargetPick(u8 heroCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (self != NULL)
    self->unkThree = heroCol;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidOpponentTarget, ResolveOpponentTarget, CancelTargeting,
                     AiPickOpponentTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void ResolveHeroTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidHeroTarget(fixedRow, fixedCol))
    return;

  if (IsDuelOver() == TRUE || !FieldHasOpponentTarget())
    return;

  BeginOpponentTargetPick(fixedCol);
}

static u8 AiPickHeroTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidHeroTarget(*outRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateVISION_HERO_ADORATION(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != VISION_HERO_ADORATION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VISION_HERO_ADORATION)
    return FALSE;

  return CanUseMonsterEffect(zone) && FieldHasHeroTarget() && FieldHasOpponentTarget();
}

void ActivateVISION_HERO_ADORATIONEffect(void)
{
  Duel_ShowEffectTextTyped(VISION_HERO_ADORATION, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidHeroTarget, ResolveHeroTarget, CancelTargeting, AiPickHeroTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
