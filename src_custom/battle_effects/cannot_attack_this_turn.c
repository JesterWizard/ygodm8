#include "global.h"
#include "common-chax.h"
#include "cannot_attack_this_turn.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const u16 sCannotAttackThisTurnIds[] APPEND_RODATA = {
  BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON,
  VENOM_SNAKE,
  VENOM_BOA,
};

static u8 UsesCannotAttackMark(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sCannotAttackThisTurnIds); i++) {
    if (sCannotAttackThisTurnIds[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

u8 CannotAttackThisTurn_CanDeclareAttack(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  if (!UsesCannotAttackMark(zone->id))
    return TRUE;

  return (zone->unk4 & DUEL_CANNOT_ATTACK_THIS_TURN_MARK) == 0;
}

void CannotAttackThisTurn_ClearMarksAtEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone == NULL || !UsesCannotAttackMark(zone->id))
        continue;

      zone->unk4 &= (u8)~DUEL_CANNOT_ATTACK_THIS_TURN_MARK;
    }
  }
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CannotAttackThisTurn_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = VENOM_SNAKE;
  zone.unk4 = DUEL_CANNOT_ATTACK_THIS_TURN_MARK;
  if (CannotAttackThisTurn_CanDeclareAttack(&zone) != FALSE)
    __builtin_trap();

  zone.unk4 = 0;
  if (CannotAttackThisTurn_CanDeclareAttack(&zone) == FALSE)
    __builtin_trap();

  zone.id = BLUE_EYES_WHITE_DRAGON;
  zone.unk4 = DUEL_CANNOT_ATTACK_THIS_TURN_MARK;
  if (CannotAttackThisTurn_CanDeclareAttack(&zone) == FALSE)
    __builtin_trap();
}
#endif
