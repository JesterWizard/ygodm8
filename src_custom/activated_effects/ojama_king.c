#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 OpponentMonsterRow(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

unsigned char CanActivateOJAMA_KING(void)
{
  struct DuelCard *zone;
  u8 col;
  u8 row;

  if (gMonEffect.id != OJAMA_KING)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != OJAMA_KING)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  row = OpponentMonsterRow();
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[row][col] != NULL && gFixedZones[row][col]->id == CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

void ActivateOJAMA_KINGEffect(void)
{
  struct DuelCard *king = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 row = OpponentMonsterRow();
  u8 col;
  u8 locked = 0;

  Duel_ShowEffectTextTyped(OJAMA_KING, 2);

  if (king == NULL || IsDuelOver() == TRUE)
    return;

  /* PickZone for up to 3 empty zones + continuous lock gate.
   * auto-lock first 3 empty opp MMZ via isLocked (ignored by
   * FirstEmptyZoneInRow today — same as Ground Collapse). */

  for (col = 0; col < MAX_ZONES_IN_ROW && locked < 3; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id != CARD_NONE)
      continue;
    zone->isLocked = TRUE;
    king->unk4 |= (u8)(1u << (col & 7));
    locked++;
  }

  MarkMonsterEffectUsed(king);
  UpdateDuelGfxExceptField();
}
