#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "embodiment_of_apophis.h"
#include "call_of_the_haunted.h"
#include "negate_attack.h"
#include "gravity_bind.h"
#include "wall_of_revealing_light.h"
#include "world_suppression.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "duel_helpers.h"
#include "sasuke_samurai_2.h"
#include "seven_tools_of_the_bandit.h"
#include "blast_held_by_a_tribute.h"
#include "mirror_force.h"
#include "big_bang_shot.h"
#include "riryoku.h"

static u8 OriginMonsterCanBeHarmfullyTargeted(void) {
  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (IsGodCard(gTrapEffectData.originCardId) == TRUE)
    return FALSE;
  if (IsImmuneToHarmfulTargetedEffectsOnField(gTrapEffectData.originCardId, gTrapEffectData.originRow))
    return FALSE;
  if (IsImmuneToTrapEffectsOnField(gTrapEffectData.originCardId, gTrapEffectData.originRow))
    return FALSE;
  return TRUE;
}

#define TRAP_NONE 0
#define TRAP_WIDESPREAD_RUIN 1
#define TRAP_HOUSE_OF_ADHESIVE_TAPE 2
#define TRAP_EATGABOON 3
#define TRAP_BEAR_TRAP 4
#define TRAP_INVISIBLE_WIRE 5
#define TRAP_ACID_TRAP_HOLE 6
#define TRAP_GOBLIN_FAN 7
#define TRAP_BAD_REACTION_TO_SIMOCHI 8
#define TRAP_REVERSE_TRAP 9
#define TRAP_FAKE_TRAP 10
#define TRAP_ANTI_RAIGEKI 11
#define TRAP_INFINITE_DISMISSAL 12
#define TRAP_TORRENTIAL_TRIBUTE 13
#define TRAP_AMAZON_ARCHERS 14
#define TRAP_DESTINY_BOARD 15
#define TRAP_SPIRIT_MESSAGE_I 16
#define TRAP_SPIRIT_MESSAGE_N 17
#define TRAP_SPIRIT_MESSAGE_A 18
#define TRAP_SPIRIT_MESSAGE_L 19
#define TRAP_DRAGON_CAPTURE_JAR 20
#define TRAP_MAGIC_JAMMER 21
#define TRAP_JAR_ROBBER 40
#define TRAP_MAGIC_CYLINDER 23
#define TRAP_DRAINING_SHIELD 24
extern s16 gUnk_8E1172C[];
extern s16 gUnk_8E11738[];
extern s16 gUnk_8E11744[];
extern s16 gUnk_8E11788[];

static bool8 CheckTrapActivationConditions__Hook(u16 id) {
  unsigned char ret;

  if (Duel_IsCardActivationBlocked(id))
    return FALSE;

  SetCardInfo(id);
  switch (gCardInfo.trapEffect) {
    case TRAP_NONE:
      ret = FALSE;
      break;
    case TRAP_WIDESPREAD_RUIN:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_WIDESPREAD_RUIN;
      break;
    case TRAP_HOUSE_OF_ADHESIVE_TAPE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        struct DuelCard *zone = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
        gStatMod.card = zone->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(zone);
        gSetFinalStatZone = NULL;
        SetFinalStat(&gStatMod);
        ApplyBigBangShotAtkBonusToCardInfo(zone);
        ret = gCardInfo.atk <= 500;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_HOUSE_OF_ADHESIVE_TAPE;
      break;
    case TRAP_EATGABOON:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        struct DuelCard *zone = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
        gStatMod.card = zone->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(zone);
        gSetFinalStatZone = NULL;
        SetFinalStat(&gStatMod);
        ApplyBigBangShotAtkBonusToCardInfo(zone);
        ret = gCardInfo.atk <= 1000;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_EATGABOON;
      break;
    case TRAP_BEAR_TRAP:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        struct DuelCard *zone = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
        gStatMod.card = zone->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(zone);
        gSetFinalStatZone = NULL;
        SetFinalStat(&gStatMod);
        ApplyBigBangShotAtkBonusToCardInfo(zone);
        ret = gCardInfo.atk <= 1500;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_BEAR_TRAP;
      break;
    case TRAP_INVISIBLE_WIRE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        struct DuelCard *zone = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
        gStatMod.card = zone->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(zone);
        gSetFinalStatZone = NULL;
        SetFinalStat(&gStatMod);
        ApplyBigBangShotAtkBonusToCardInfo(zone);
        ret = gCardInfo.atk <= 2000;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_INVISIBLE_WIRE;
      break;
    case TRAP_ACID_TRAP_HOLE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        struct DuelCard *zone = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];
        gStatMod.card = zone->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(zone);
        gSetFinalStatZone = NULL;
        SetFinalStat(&gStatMod);
        ApplyBigBangShotAtkBonusToCardInfo(zone);
        ret = gCardInfo.atk <= 3000;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_ACID_TRAP_HOLE;
      break;
    case TRAP_GOBLIN_FAN:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_SPELL) {
        u32 i;

        SetCardInfo(gTrapEffectData.originCardId);
        for (i = 0; gUnk_8E1172C[i] != -1; i++) {
          if (gUnk_8E1172C[i] == gCardInfo.spellEffect) {
            gTrapEffectData.trapCardId = TRAP_GOBLIN_FAN;
            ret = TRUE;
            break;
          }
        }
      }
      break;
    case TRAP_BAD_REACTION_TO_SIMOCHI:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_SPELL) {
        u32 i;

        SetCardInfo(gTrapEffectData.originCardId);
        for (i = 0; gUnk_8E11738[i] != -1; i++) {
          if (gUnk_8E11738[i] == gCardInfo.spellEffect) {
            gTrapEffectData.trapCardId = TRAP_BAD_REACTION_TO_SIMOCHI;
            ret = TRUE;
            break;
          }
        }
      }
      break;
    case TRAP_REVERSE_TRAP:
      ret = FALSE;
      {
        u32 i;

        SetCardInfo(gTrapEffectData.originCardId);
        for (i = 0; gUnk_8E11744[i] != -1; i++) {
          if (gUnk_8E11744[i] == gCardInfo.spellEffect) {
            gTrapEffectData.trapCardId = TRAP_REVERSE_TRAP;
            ret = TRUE;
            break;
          }
        }
      }
      break;
    case TRAP_FAKE_TRAP:
      ret = FALSE;
      break;
    case TRAP_ANTI_RAIGEKI:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_SPELL) {
        u32 i;

        SetCardInfo(gTrapEffectData.originCardId);
        for (i = 0; gUnk_8E11788[i] != -1; i++) {
          if (gUnk_8E11788[i] == gCardInfo.spellEffect) {
            gTrapEffectData.trapCardId = TRAP_ANTI_RAIGEKI;
            ret = TRUE;
            break;
          }
        }
      }
      break;
    case TRAP_INFINITE_DISMISSAL:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_INFINITE_DISMISSAL;
      break;
    case TRAP_TORRENTIAL_TRIBUTE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_TORRENTIAL_TRIBUTE;
      break;
    case TRAP_AMAZON_ARCHERS:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_AMAZON_ARCHERS;
      break;
    case TRAP_DESTINY_BOARD:
    case TRAP_SPIRIT_MESSAGE_I:
    case TRAP_SPIRIT_MESSAGE_N:
    case TRAP_SPIRIT_MESSAGE_A:
    case TRAP_SPIRIT_MESSAGE_L:
    case TRAP_DRAGON_CAPTURE_JAR:
      ret = FALSE;
      break;
    case TRAP_MAGIC_JAMMER:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_SPELL) {
        gTrapEffectData.trapCardId = TRAP_MAGIC_JAMMER;
        ret = TRUE;
      }
      break;
    case TRAP_JAR_ROBBER:
      ret = FALSE;
      break;
    case TRAP_SEVEN_TOOLS_OF_THE_BANDIT:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_TRAP) {
        gTrapEffectData.trapCardId = TRAP_SEVEN_TOOLS_OF_THE_BANDIT;
        ret = TRUE;
      }
      break;
    case TRAP_IMPERIAL_ORDER:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_SPELL
          && gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol]->isFaceUp == FALSE) {
        gTrapEffectData.trapCardId = TRAP_IMPERIAL_ORDER;
        ret = TRUE;
      }
      break;
    case TRAP_EMBODIMENT_OF_APOPHIS:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER
          && EmbodimentOfApophisHasEmptyMonsterZoneForTrap(
              gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol])
          && !EmbodimentOfApophisTrapZoneIsAwakened(
              gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol])) {
        gTrapEffectData.trapCardId = TRAP_EMBODIMENT_OF_APOPHIS;
        ret = TRUE;
      }
      break;
    case TRAP_MAGIC_CYLINDER:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_MAGIC_CYLINDER;
      break;
    case TRAP_DRAINING_SHIELD:
      ret = GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER;
      if (ret)
        gTrapEffectData.trapCardId = TRAP_DRAINING_SHIELD;
      break;
    case TRAP_NEGATE_ATTACK:
      ret = GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER;
      if (ret)
        gTrapEffectData.trapCardId = TRAP_NEGATE_ATTACK;
      break;
    case TRAP_CALL_OF_THE_HAUNTED:
      ret = FALSE;
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
        u16 graveCard;

        graveCard = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;
        if (graveCard != CARD_NONE
            && GetTypeGroup(graveCard) == TYPE_GROUP_MONSTER
            && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
          gTrapEffectData.trapCardId = TRAP_CALL_OF_THE_HAUNTED;
          ret = TRUE;
        }
      }
      break;
    case TRAP_GRAVITY_BIND:
      ret = GravityBind_ShouldActivateTrapOnAttack(
          gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
          gTrapEffectData.originCardId);
      if (ret)
        gTrapEffectData.trapCardId = TRAP_GRAVITY_BIND;
      break;
    case TRAP_WALL_OF_REVEALING_LIGHT:
      ret = WallOfRevealingLight_ShouldActivateTrapOnAttack(
          gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
          gTrapEffectData.originCardId);
      if (ret)
        gTrapEffectData.trapCardId = TRAP_WALL_OF_REVEALING_LIGHT;
      break;
    case TRAP_WORLD_SUPPRESSION:
      ret = WorldSuppression_ShouldActivateTrapOnFieldSpell(gTrapEffectData.originCardId);
      if (ret)
        gTrapEffectData.trapCardId = TRAP_WORLD_SUPPRESSION;
      break;
    case TRAP_BLAST_HELD_BY_A_TRIBUTE:
      ret = BlastHeldByATribute_ShouldActivateTrap();
      if (ret)
        gTrapEffectData.trapCardId = TRAP_BLAST_HELD_BY_A_TRIBUTE;
      break;
    case TRAP_MIRROR_FORCE:
      ret = GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER;
      if (ret)
        gTrapEffectData.trapCardId = TRAP_MIRROR_FORCE;
      break;
    default:
      ret = FALSE;
      break;
  }
  return ret;
}

LYN_REPLACE_CHECK(IsTrapTriggered);
unsigned IsTrapTriggered__Replacement(void) {
  unsigned char i;
  u16 trapId;

  gTrapEffectData.trapCardId = 0;

  if (SasukeSamurai2_AreInactiveBackrowTrapsBlocked())
    return FALSE;

  if (Duel_IsOriginActivationProtectedFromNegation())
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];

    trapId = zone->id;
    gTrapEffectData.trapZoneCol = i;
    if (trapId == CARD_NONE)
      continue;
    if (Duel_IsCardActivationBlocked(trapId))
      continue;
    // ponytail: AI sim (gHideEffectText) must not treat unknown face-down opponent
    // backrow as chainable — sub_801B35C/sub_801B3AC gate spell actions on this.
    if (gHideEffectText && !zone->isFaceUp)
      continue;
    if (CheckTrapActivationConditions__Hook(trapId) == TRUE) {
      if (gTrapEffectData.trapCardId == TRAP_IMPERIAL_ORDER)
        continue;
      if (gTrapEffectData.trapCardId == TRAP_ROYAL_DECREE)
        continue;
      if (gTrapEffectData.trapCardId != TRAP_EMBODIMENT_OF_APOPHIS)
        return TRUE;
    }
  }

  return FALSE;
}

/* LEVEL_LIMIT_AREA_A handled via spell_effect_hooks.c (manual activation) */
/* A_HERO_EMERGES trap effect */
  /* TODO: wire A_HERO_EMERGES in trap dispatcher */
/* ANTI_SPELL_FRAGRANCE trap effect */
  /* TODO: wire ANTI_SPELL_FRAGRANCE in trap dispatcher */
/* APPROPRIATE trap effect */
  /* TODO: wire APPROPRIATE in trap dispatcher */
/* ATTACK_AND_RECEIVE trap effect */
  /* TODO: wire ATTACK_AND_RECEIVE in trap dispatcher */
/* ATTACK_GUIDANCE_ARMOR trap effect */
  /* TODO: wire ATTACK_GUIDANCE_ARMOR in trap dispatcher */
/* ATTACK_REFLECTOR_UNIT trap effect */
  /* TODO: wire ATTACK_REFLECTOR_UNIT in trap dispatcher */
/* BACKFIRE trap effect */
  /* TODO: wire BACKFIRE in trap dispatcher */
/* BREAK_THE_DESTINY trap effect */
  /* TODO: wire BREAK_THE_DESTINY in trap dispatcher */