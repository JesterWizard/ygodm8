#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOwnFaceUpMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 FieldHasOwnMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnFaceUpMonster(ACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOwnFaceUpMonster(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  /* ponytail: until end of turn clear + vs Special Summoned only need battle
   * hooks. Ceiling: mark unk4 on own monster as battle-destroy stand-in. */
  zone->unk4 |= 0x40;

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

  *outRow = ACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnFaceUpMonster(ACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateEL_SHADDOLL_WENDIGO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EL_SHADDOLL_WENDIGO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EL_SHADDOLL_WENDIGO)
    return FALSE;

  /* ponytail: quick battle protection + GY add Shaddoll S/T need chain/send
   * hooks. Ceiling: OPT mark 1 own monster unk4. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOwnMonster();
}

void ActivateEL_SHADDOLL_WENDIGOEffect(void)
{
  Duel_ShowEffectTextTyped(EL_SHADDOLL_WENDIGO, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsOwnFaceUpMonster, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
