#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "el_shaddoll_wendigo.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

u8 ElShaddollWendigo_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL
      && (zone->unk4 & EL_SHADDOLL_WENDIGO_BATTLE_PROTECT_MARK) != 0;
}

void ElShaddollWendigo_ClearTurnMarks(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL)
        zone->unk4 &= (u8)~EL_SHADDOLL_WENDIGO_BATTLE_PROTECT_MARK;
    }
  }
}

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

  zone->unk4 |= EL_SHADDOLL_WENDIGO_BATTLE_PROTECT_MARK;

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

  /* Battle protect via ElShaddollWendigo_PreventsBattleDestroy.
   * Ceiling: GY add Shaddoll S/T on send not wired. */
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
