#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void FlipCardFaceUp(struct DuelCard *zone);

static u8 IsFaceDownMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsCardFaceUp(zone) && zone->isDefending == TRUE;
}

static u8 FieldHasFaceDownMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceDownMonster(gFixedZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 FlipAllFaceDownMonstersFaceUpDef(void)
{
  u8 row;
  u8 col;
  u8 flipped = FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsFaceDownMonster(zone))
        continue;

      zone->isDefending = TRUE;
      FlipCardFaceUp(zone);
      flipped = TRUE;
    }
  }

  return flipped;
}

unsigned char CanActivateREESHADDOLL_WENDIKURUHU(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != REESHADDOLL_WENDIKURUHU)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != REESHADDOLL_WENDIKURUHU)
    return FALSE;

  /* Quick face-up→face-down follow-up + GY Shaddoll add need flip/send
   * hooks. OPT flip all face-down monsters face-up DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceDownMonster();
}

void ActivateREESHADDOLL_WENDIKURUHUEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(REESHADDOLL_WENDIKURUHU, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!FlipAllFaceDownMonstersFaceUpDef())
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
