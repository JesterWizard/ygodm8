#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpOppMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return IsFaceUpOppMonster(gFixedZones[fixedRow][fixedCol]);
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

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  /* ponytail: −700 ≈ −2 tempStage (~−1000); counter/damage-redirect FALSE. */
  if (zone->tempStage > -126)
    zone->tempStage = (s8)(zone->tempStage - 2);

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

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(INACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateBLACK_WINGED_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BLACK_WINGED_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BLACK_WINGED_DRAGON)
    return FALSE;

  /* ponytail: damage redirect + Black Feather Counters + burn need damage hooks.
   * Ceiling: OPT −2 tempStage on 1 face-up opp monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateBLACK_WINGED_DRAGONEffect(void)
{
  Duel_ShowEffectTextTyped(BLACK_WINGED_DRAGON, 2);

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
