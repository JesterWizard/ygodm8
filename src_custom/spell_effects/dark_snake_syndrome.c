#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_snake_syndrome.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define DARK_SNAKE_BASE_DAMAGE 200

static u16 GetDarkSnakeDamage(const struct DuelCard *zone)
{
  u8 exponent = zone->permStage;
  u32 damage = (u32)DARK_SNAKE_BASE_DAMAGE << exponent;

  if (damage > 65535)
    damage = 65535;

  return (u16)damage;
}

u8 IsActivatedDarkSnakeSyndromeZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == DARK_SNAKE_SYNDROME && zone->isFaceUp == TRUE;
}

void TryApplyDarkSnakeSyndromeStandbyDamage(void)
{
  u8 controller = WhoseTurn();
  u8 row;
  u8 i;
  struct DuelCard *zone;
  u16 damage;

  if (IsDuelOver() == TRUE || IsImperialOrderNegatingSpell(DARK_SNAKE_SYNDROME))
    return;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      zone = gFixedZones[row][i];
      if (!IsActivatedDarkSnakeSyndromeZone(zone))
        continue;
      if (GetDuelistForZone(zone) != controller)
        continue;

      damage = GetDarkSnakeDamage(zone);

      Duel_ShowEffectText(DARK_SNAKE_SYNDROME);

      if (IsDuelOver() == TRUE)
        return;

      if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)damage, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
      if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;

      IncrementPermStage(zone);

      if (IsDuelOver() == TRUE)
        return;
    }
  }
}

APPEND_TEXT void EffectDarkSnakeSyndrome(void)
{
  const struct EffectScript *script =
      EffectScript_Find(DARK_SNAKE_SYNDROME, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
