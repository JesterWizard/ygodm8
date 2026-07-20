#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "effect_conditions.h"

u8 EffectCond_ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

u8 EffectCond_InactiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

u8 EffectCond_SpellTrapOnBackrow(u8 requiredBackrow, u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != requiredBackrow)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER;
}

u8 EffectCond_OppBackrowSpellTrap(u8 fixedRow, u8 fixedCol)
{
  return EffectCond_SpellTrapOnBackrow(OPPONENT_BACKROW, fixedRow, fixedCol);
}

u8 EffectCond_ActiveFaceUpSpell(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != EffectCond_ActiveBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL;
}

u8 EffectCond_OppMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != EffectCond_InactiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE
      && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

u8 EffectCond_AnyFaceUpMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE && zone->isFaceUp
      && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static const EffectCondFn sEffectConds[EFFECT_COND_COUNT] __attribute__((section(".text"))) = {
  EffectCond_OppBackrowSpellTrap,
  EffectCond_ActiveFaceUpSpell,
  EffectCond_OppMonster,
  EffectCond_AnyFaceUpMonster,
};

EffectCondFn EffectCond_Get(u8 condId)
{
  if (condId >= EFFECT_COND_COUNT)
    return NULL;
  return sEffectConds[condId];
}

u8 EffectCond_Eval(u8 condId, u8 fixedRow, u8 fixedCol)
{
  EffectCondFn fn = EffectCond_Get(condId);

  if (fn == NULL)
    return FALSE;
  return fn(fixedRow, fixedCol);
}
