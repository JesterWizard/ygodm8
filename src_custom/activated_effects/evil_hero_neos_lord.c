#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 CanTakeControlOfOpponentMonster(void)
{
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) > 0
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
          < MAX_ZONES_IN_ROW;
}

static u8 IsValidTakeControlTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  /* Printed: face-up. Face-up ATK often isFaceUp=0 until EOT — ATK stands in. */
  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 FieldHasTakeControlTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTakeControlTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void TakeControlOfMonsterZone(struct DuelCard *src)
{
  s8 destCol;
  struct DuelCard *dst;

  if (src == NULL || src->id == CARD_NONE || !CanTakeControlOfOpponentMonster())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (destCol < 0)
    return;

  dst = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][destCol];
  {
    u16 cardId = src->id;
    u8 newFixedRow = Duel_FixedMonsterRowForDuelist(ACTIVE_DUELIST);

    CopyCard(dst, src);
    dst->isFaceUp = TRUE;
    dst->isLocked = FALSE;
    dst->isDefending = FALSE;
    dst->unkTwo = 0;
    dst->unk4 = 2;
    dst->willChangeSides = TRUE;
    ClearZone(src);
    Duel_NotifyMonsterZoneChanged(dst);
    Duel_NotifyMonsterControlSwitched(cardId, newFixedRow);
  }
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTakeControlTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  TakeControlOfMonsterZone(zone);

  EffectOpt_MarkUsed(EVIL_HERO_NEOS_LORD);
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
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTakeControlTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    zone = gFixedZones[OPPONENT_MONSTER_ROW][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = OPPONENT_MONSTER_ROW;
  *outCol = bestCol;
  return TRUE;
}

void TryEvilHeroNeosLordOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 controller;

  if (zone == NULL || zone->id != EVIL_HERO_NEOS_LORD || !SummonModeIsSpecial(mode))
    return;
  if (gHideEffectText)
    return;
  if (EffectOpt_IsUsed(EVIL_HERO_NEOS_LORD))
    return;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return;

  if (!CanTakeControlOfOpponentMonster() || !FieldHasTakeControlTarget())
    return;

  if (!AiPickTarget(&fixedRow, &fixedCol))
    return;

  Duel_ShowEffectTextTyped(EVIL_HERO_NEOS_LORD, 8);
  TakeControlOfMonsterZone(gFixedZones[fixedRow][fixedCol]);
  EffectOpt_MarkUsed(EVIL_HERO_NEOS_LORD);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateEVIL_HERO_NEOS_LORD(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_NEOS_LORD)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_NEOS_LORD)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (EffectOpt_IsUsed(EVIL_HERO_NEOS_LORD))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanTakeControlOfOpponentMonster() && FieldHasTakeControlTarget();
}

void ActivateEVIL_HERO_NEOS_LORDEffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_NEOS_LORD, 2);

  if (IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(EVIL_HERO_NEOS_LORD))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTakeControlTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
