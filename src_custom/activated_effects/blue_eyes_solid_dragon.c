#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpOppMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return IsCardFaceUp(zone);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppMonster(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpOppMonster(fixedRow, fixedCol) || zone == NULL)
    return;

  /* ponytail: summon Quick shuffle→SS BEWD + per-effect usage need hooks. */
  zone->unk4 |= 0x80;

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

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppMonster(OPPONENT_MONSTER_ROW, col)) {
      *outRow = OPPONENT_MONSTER_ROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateBLUE_EYES_SOLID_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLUE_EYES_SOLID_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLUE_EYES_SOLID_DRAGON)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateBLUE_EYES_SOLID_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(BLUE_EYES_SOLID_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpOppMonster, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
