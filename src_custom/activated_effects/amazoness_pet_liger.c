#include "global.h"
#include "common-chax.h"
#include "amazoness_pet_liger.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define AMAZONESS_PET_LIGER_BASE_ATK 2500
#define AMAZONESS_PET_LIGER_ATK_PER_OTHER 500

static u8 IsFaceUpOppMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
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

static u8 CountOtherAmazonessOnFixedRow(u8 fixedRow, const struct DuelCard *self)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;
    if (Duel_IsAmazonessCard(zone->id))
      count++;
  }

  return count;
}

u8 AmazonessPetLiger_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 others;

  if (zone == NULL || zone->id != AMAZONESS_PET_LIGER)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  others = CountOtherAmazonessOnFixedRow(fixedRow, zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(
      zone->id,
      Duel_StatFromCount(others, AMAZONESS_PET_LIGER_ATK_PER_OTHER,
                         AMAZONESS_PET_LIGER_BASE_ATK),
      gCardInfo.def);
  return TRUE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  /* −800 ≈ −2 tempStage (~−1000); stage granularity. */
  if (zone->tempStage > -126)
    zone->tempStage = (s8)(zone->tempStage - 2);

  {
    u8 c;

    for (c = 0; c < MAX_ZONES_IN_ROW; c++) {
      struct DuelCard *own = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][c];

      if (own != NULL && own->id != CARD_NONE && Duel_IsAmazonessCard(own->id))
        own->isLocked = TRUE;
    }
  }

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
    if (IsValidTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateAMAZONESS_PET_LIGER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_PET_LIGER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_PET_LIGER)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * ATK via AmazonessPetLiger_ApplyDynamicZoneStats. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateAMAZONESS_PET_LIGEREffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_PET_LIGER, 2);

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
