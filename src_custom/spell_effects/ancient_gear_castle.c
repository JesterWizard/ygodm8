#include "global.h"
#include "common-chax.h"
#include "ancient_gear_castle.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "geartown.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

#define ANCIENT_GEAR_CASTLE_ATK_BOOST 300

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

void ApplyAncientGearCastleAtkBoostForZone(struct DuelCard *zone)
{
  u32 boosted;
  u8 row;
  u8 col;
  u8 fixedDuelist;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!IsAncientGearMonster(zone->id))
    return;

  if (!Duel_FindFixedZone(zone, &row, &col) || !Duel_IsFixedMonsterRow(row))
    return;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  if (Duel_FindBackrowCard(fixedDuelist, ANCIENT_GEAR_CASTLE, TRUE) == NULL)
    return;

  if (gCardInfo.atk != 0xFFFF) {
    boosted = (u32)gCardInfo.atk + ANCIENT_GEAR_CASTLE_ATK_BOOST;
    gCardInfo.atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
}

u8 AncientGearCastle_CanSubstituteTributes(u16 cardId, int requiredTributes)
{
  struct DuelCard *castle;

  if (requiredTributes <= 0 || !IsAncientGearMonster(cardId))
    return FALSE;

  castle = Duel_FindBackrowCard(FixedDuelistForActive(), ANCIENT_GEAR_CASTLE, TRUE);
  if (castle == NULL)
    return FALSE;

  return castle->unk4 >= (u8)requiredTributes;
}

u8 AncientGearCastle_TryConsumeOnNormalSummon(u16 cardId)
{
  struct DuelCard *castle;
  int required;

  if (!IsAncientGearMonster(cardId))
    return FALSE;

  castle = Duel_FindBackrowCard(FixedDuelistForActive(), ANCIENT_GEAR_CASTLE, TRUE);
  if (castle == NULL)
    return FALSE;

  SetCardInfo(cardId);
  required = (gCardInfo.level <= 4) ? 0
      : (gCardInfo.level <= 6)      ? 1
      : (gCardInfo.level <= 8)      ? 2
                                    : 3;
  required = Geartown_ReduceRequiredTributes(cardId, required);

  if (!AncientGearCastle_CanSubstituteTributes(cardId, required))
    return FALSE;

  Duel_DestroyZone(castle, ACTIVE_DUELIST, TRUE);
  return TRUE;
}

u8 Cond_AncientGearCastleOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  struct DuelCard *castle;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (ev->cardId == CARD_NONE || GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  castle = Duel_FindBackrowCard(ev->controller, ANCIENT_GEAR_CASTLE, TRUE);
  return castle != NULL;
}

enum DuelActionResult Op_AncientGearCastleOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  struct DuelCard *castle;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  castle = Duel_FindBackrowCard(ev->controller, ANCIENT_GEAR_CASTLE, TRUE);
  if (castle == NULL)
    return DUEL_ACTION_NO_TARGET;

  if (castle->unk4 < 255)
    castle->unk4++;

  return DUEL_ACTION_OK;
}

APPEND_TEXT void EffectANCIENT_GEAR_CASTLE(void)
{
  const struct EffectScript *script =
      EffectScript_Find(ANCIENT_GEAR_CASTLE, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_CASTLE_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (ANCIENT_GEAR_CASTLE_ATK_BOOST != 300)
    while (1)
      ;
}
#endif
