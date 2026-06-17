#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "rivalry_of_warlords.h"

void UpdateDuelGfxExceptField(void);
void sub_802ACC0(void);
void sub_8041E70(u8, u8);

u8 IsActivatedRivalryOfWarlordsZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == RIVALRY_OF_WARLORDS && zone->isFaceUp == TRUE;
}

u8 IsRivalryOfWarlordsActiveOnField(void)
{
  return Duel_IsBackrowCardOnField(RIVALRY_OF_WARLORDS, TRUE);
}

static u8 FindTurnZoneForCard(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = 0; row <= 4; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void PresentRivalryTrapForEffectText(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnRow;
  u8 turnCol;
  u8 prevY;

  if (gHideEffectText || zone == NULL)
    return;

  if (!Duel_FindFixedZone(zone, &fixedRow, &col))
    return;

  prevY = gDuelCursor.currentY;
  gDuelCursor.currentY = fixedRow;
  gDuelCursor.currentX = col;
  sub_8041E70(prevY, fixedRow);

  if (gRuntimeConfig.turn_off_visual_scanner)
    return;

  if (!FindTurnZoneForCard(zone, &turnRow, &turnCol))
    return;

  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = turnCol;
  gActiveEffect.cardId = RIVALRY_OF_WARLORDS;
  sub_8034FEC(0x177);
  sub_802ACC0();
}

static void ActivateRivalryOfWarlordsZone(struct DuelCard *zone)
{
  if (zone == NULL)
    return;

  if (!zone->isFaceUp) {
    PresentRivalryTrapForEffectText(zone);
    Duel_ActivateContinuousZone(zone);
    Duel_ShowEffectTextTyped(RIVALRY_OF_WARLORDS, 3);

    if (IsDuelOver() == TRUE)
      return;
  }

  Duel_EnforceSingleMonsterTypeOnBothMonsterRows(TRUE);
}

static void TryFlipRivalryForMonsterRow(u8 fixedRow)
{
  struct DuelCard *rivalryZone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return;

  rivalryZone = Duel_FindBackrowCardOnField(RIVALRY_OF_WARLORDS, FALSE);
  if (rivalryZone == NULL || rivalryZone->isFaceUp)
    return;

  if (!Duel_FixedMonsterRowHasMultipleMonsterTypes(fixedRow))
    return;

  ActivateRivalryOfWarlordsZone(rivalryZone);
  UpdateDuelGfxExceptField();
}

void RivalryOfWarlords_CheckAfterFieldChange(void)
{
  if (gHideEffectText)
    return;

  TryFlipRivalryForMonsterRow(OPPONENT_MONSTER_ROW);
  if (IsDuelOver() == TRUE)
    return;

  TryFlipRivalryForMonsterRow(PLAYER_MONSTER_ROW);
  if (IsDuelOver() == TRUE)
    return;

  if (IsRivalryOfWarlordsActiveOnField())
    Duel_EnforceSingleMonsterTypeOnBothMonsterRows(TRUE);
}

void TryRivalryOfWarlordsOnMonsterPlacement(struct DuelCard *zone)
{
  Duel_NotifyMonsterZoneChanged(zone);
}

APPEND_TEXT void EffectRivalryOfWarlords(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  ActivateRivalryOfWarlordsZone(zone);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void RivalryOfWarlords_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = RIVALRY_OF_WARLORDS;
  zone.isFaceUp = TRUE;
  if (!IsActivatedRivalryOfWarlordsZone(&zone))
    __builtin_trap();
}
#endif
