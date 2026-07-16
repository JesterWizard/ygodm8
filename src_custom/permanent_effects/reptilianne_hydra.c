#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void SetCursorToCardDest(void);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target validation */
  (void)fixedRow;
  (void)fixedCol;
  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target resolution */
  (void)fixedRow;
  (void)fixedCol;
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  /* TODO: implement AI target selection */
  (void)outRow;
  (void)outCol;
  return FALSE;
}

unsigned char ShouldActivateREPTILIANNE_HYDRA(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != REPTILIANNE_HYDRA)
    return FALSE;

  if (GetPendingTributeSummonCardId() != REPTILIANNE_HYDRA)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  /* TODO: add field-has-target check */
  return TRUE;
}

void ActivateREPTILIANNE_HYDRA(void)
{
  u8 originRow = gActiveEffect.turnRow;
  u8 originCol = gActiveEffect.col;

  Duel_ShowEffectTextTyped(REPTILIANNE_HYDRA, 8);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER && originRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
