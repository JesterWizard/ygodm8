#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "light_barrier.h"
#include "spell_effects.h"

struct LightBarrierActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
};

extern struct LightBarrierActionData sActionData;

static u8 sLightBarrierNegated[2] APPEND_DATA = {FALSE, FALSE};
static const char sArcanaForceArchetypeName[] APPEND_RODATA = "Arcana Force";

u8 LightBarrier_IsActiveForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return Duel_FindBackrowCard(fixedDuelist, LIGHT_BARRIER, TRUE) != NULL;
}

u8 LightBarrier_IsNegatedForDuelist(u8 fixedDuelist)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  return sLightBarrierNegated[fixedDuelist];
}

void LightBarrier_ResolveStandbyCoin(u8 fixedDuelist, u8 heads)
{
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return;

  sLightBarrierNegated[fixedDuelist] =
      LightBarrier_IsActiveForDuelist(fixedDuelist) && !heads;
}

u8 LightBarrier_AllowsArcanaForceCoinChoice(u8 fixedDuelist)
{
  return LightBarrier_IsActiveForDuelist(fixedDuelist)
      && !LightBarrier_IsNegatedForDuelist(fixedDuelist);
}

u16 LightBarrier_GetArcanaForceBattleDestroyLp(u8 fixedDuelist,
                                                const struct DuelCard *attacker,
                                                const struct DuelCard *destroyed)
{
  if (!LightBarrier_AllowsArcanaForceCoinChoice(fixedDuelist)
      || attacker == NULL || destroyed == NULL
      || destroyed->id >= NUM_TOTAL_CARDS
      || !Duel_CardNameContains(attacker->id, sArcanaForceArchetypeName))
    return 0;

  return gCardData_NEW[destroyed->id].atk;
}

void ApplyLightBarrierBattleEffect(void)
{
  struct DuelCard attacker;
  struct DuelCard destroyed;
  u8 controller;
  u16 lp;

  if ((sActionData.flags & 2) && !(sActionData.flags & 1)) {
    controller = DUEL_PLAYER;
    attacker.id = sActionData.playerCardId;
    destroyed.id = sActionData.opponentCardId;
  } else if ((sActionData.flags & 1) && !(sActionData.flags & 2)) {
    controller = DUEL_OPPONENT;
    attacker.id = sActionData.opponentCardId;
    destroyed.id = sActionData.playerCardId;
  } else {
    return;
  }

  lp = LightBarrier_GetArcanaForceBattleDestroyLp(controller, &attacker, &destroyed);
  if (lp == 0)
    return;

  Duel_ShowEffectText(LIGHT_BARRIER);
  Duel_ChangeLp(controller, (s32)lp, TRUE);
}

APPEND_TEXT void EffectLIGHT_BARRIER(void)
{
  const struct EffectScript *script = EffectScript_Find(LIGHT_BARRIER, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
