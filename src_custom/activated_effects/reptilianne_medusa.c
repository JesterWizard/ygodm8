#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
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

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsFaceUpMonsterZone(zone);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OpponentMonsterRow(), col))
      return TRUE;
  }

  return FALSE;
}

static void SetZoneAtkToZero(struct DuelCard *zone)
{
  u16 baseAtk = gCardData_NEW[zone->id].atk;
  u16 withPerm = Duel_StageModifiedStat(baseAtk, zone->permStage);
  s8 stages = (s8)(-((s32)withPerm + 499) / 500);

  zone->tempStage = stages;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  SetZoneAtkToZero(zone);
  zone->unk4 |= 1; /* cannot change position via Duel_ZoneCannotChangeBattlePosition */

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = OpponentMonsterRow();
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidTarget(*outRow, col))
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

unsigned char CanActivateREPTILIANNE_MEDUSA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != REPTILIANNE_MEDUSA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != REPTILIANNE_MEDUSA)
    return FALSE;

  return CanUseMonsterEffect(zone) && Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0
      && FieldHasTarget();
}

void ActivateREPTILIANNE_MEDUSAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(REPTILIANNE_MEDUSA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

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
