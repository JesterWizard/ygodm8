#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void UpdateDuelGfxExceptField(void);

static u8 AnyCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 HasFieldTarget(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 IsRaigekiBreakFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > 3)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE;
}

static void CancelRaigekiBreakTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickRaigekiBreakTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsRaigekiBreakFieldTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void ResolveRaigekiBreakTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *trapZone;

  if (!IsRaigekiBreakFieldTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  Duel_DestroyZone(zone, DUEL_PLAYER, FALSE);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (trapZone != NULL)
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectRAIGEKI_BREAK(void)
{
  s8 handZone;

  Duel_ShowTrapResponseText(RAIGEKI_BREAK, gTrapEffectData.originCardId);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0 || !HasFieldTarget()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], AnyCard);
  else
    handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);

  if (handZone >= 0)
    Duel_DestroyZone(gTurnHands[INACTIVE_DUELIST][handZone], INACTIVE_DUELIST, FALSE);

  gDuelCursor.destY = INACTIVE_DUELIST_BACKROW;
  gDuelCursor.destX = gTrapEffectData.trapZoneCol;

  Duel_SetupPickZone(IsRaigekiBreakFieldTarget, ResolveRaigekiBreakTarget,
                     CancelRaigekiBreakTargeting, AiPickRaigekiBreakTarget);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    Duel_RunPickZoneInputLoop();
  else
    Duel_ResolvePickZoneForAi();
}
