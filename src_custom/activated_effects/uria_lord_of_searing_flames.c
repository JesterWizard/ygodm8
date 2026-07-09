#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "uria_lord_of_searing_flames.h"

void UpdateDuelGfxExceptField(void);

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;
  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 IsSetSpellTrapZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (zone->isFaceUp)
    return FALSE;
  return TRUE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return IsSetSpellTrapZone(zone);
}

static u8 FieldHasTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(OPPONENT_BACKROW, col))
      return TRUE;
  }
  return FALSE;
}

static u8 ScoreTarget(u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[OPPONENT_BACKROW][fixedCol];

  if (zone->id == CARD_NONE)
    return 0;

  SetCardInfo(zone->id);
  if (GetTypeGroup(zone->id) == TYPE_GROUP_TRAP)
    return 80;
  return 50;
}

static u8 AiPickTarget(u8 *outCol)
{
  u8 col;
  u8 bestCol = 0xFF;
  u8 bestScore = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u8 score;

    if (!IsValidTarget(OPPONENT_BACKROW, col))
      continue;

    score = ScoreTarget(col);
    if (score > bestScore) {
      bestScore = score;
      bestCol = col;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

u8 CanActivateURIA_LORD_OF_SEARING_FLAMES(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != URIA_LORD_OF_SEARING_FLAMES)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateURIA_LORD_OF_SEARING_FLAMESEffect(void)
{
  u8 bestCol;

  Duel_ShowCardEffectText(URIA_LORD_OF_SEARING_FLAMES,
                          CARD_EFFECT_TEXT_URIA_LORD_OF_SEARING_FLAMES_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(gTurnZones[gMonEffect.row][gMonEffect.zone]);

  if (!AiPickTarget(&bestCol))
    return;

  Duel_DestroyZone(gFixedZones[OPPONENT_BACKROW][bestCol],
                   (WhoseTurn() == DUEL_PLAYER) ? DUEL_OPPONENT : DUEL_PLAYER,
                   TRUE);
}
