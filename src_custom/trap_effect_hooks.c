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
/* D_TACTICS trap effect */
  /* TODO: wire D_TACTICS in trap dispatcher */
/* D_TIME trap effect */
  /* TODO: wire D_TIME in trap dispatcher */
/* DAMAGE_POLARIZER trap effect */
  /* TODO: wire DAMAGE_POLARIZER in trap dispatcher */
/* DES_COUNTERBLOW trap effect */
  /* TODO: wire DES_COUNTERBLOW in trap dispatcher */
/* DOPPELGANGER trap effect */
  /* TODO: wire DOPPELGANGER in trap dispatcher */
/* DRAGON_S_RAGE trap effect */
  /* TODO: wire DRAGON_S_RAGE in trap dispatcher */
/* GIFT_CARD trap effect */
  /* TODO: wire GIFT_CARD in trap dispatcher */
/* MAGICAL_HATS trap effect */
  /* TODO: wire MAGICAL_HATS in trap dispatcher */
/* METEORAIN trap effect */
  /* TODO: wire METEORAIN in trap dispatcher */
/* NEEDLE_WALL trap effect */
  /* TODO: wire NEEDLE_WALL in trap dispatcher */
/* NUMINOUS_HEALER trap effect */
  /* TODO: wire NUMINOUS_HEALER in trap dispatcher */
/* PROPHECY trap effect */
  /* TODO: wire PROPHECY in trap dispatcher */
/* RAIGEKI_BREAK trap effect */
  /* TODO: wire RAIGEKI_BREAK in trap dispatcher */
/* SIXTH_SENSE trap effect */
  /* TODO: wire SIXTH_SENSE in trap dispatcher */
/* SOLEMN_JUDGMENT trap effect */
  /* TODO: wire SOLEMN_JUDGMENT in trap dispatcher */
/* SPARK_BLASTER trap effect */
  /* TODO: wire SPARK_BLASTER in trap dispatcher */
/* TORNADO_WALL trap effect */
  /* TODO: wire TORNADO_WALL in trap dispatcher */
/* TRAP_DUSTSHOOT trap effect */
  /* TODO: wire TRAP_DUSTSHOOT in trap dispatcher */
/* TYRANT_WING trap effect */
  /* TODO: wire TYRANT_WING in trap dispatcher */
/* AMBUSH_FANGS trap effect */
  /* TODO: wire AMBUSH_FANGS in trap dispatcher */
/* BLESSED_WINDS trap effect */
  /* TODO: wire BLESSED_WINDS in trap dispatcher */
/* CHAIN_MATERIAL trap effect */
  /* TODO: wire CHAIN_MATERIAL in trap dispatcher */
/* DAMAGE_REPTILE trap effect */
  /* TODO: wire DAMAGE_REPTILE in trap dispatcher */
/* DARK_RENEWAL trap effect */
  /* TODO: wire DARK_RENEWAL in trap dispatcher */
/* DARK_SUPREMACY trap effect */
  /* TODO: wire DARK_SUPREMACY in trap dispatcher */
/* DESTINED_RIVALS trap effect */
  /* TODO: wire DESTINED_RIVALS in trap dispatcher */
/* DRIED_WINDS trap effect */
  /* TODO: wire DRIED_WINDS in trap dispatcher */
/* ETERNAL_SOUL trap effect */
  /* TODO: wire ETERNAL_SOUL in trap dispatcher */
/* HARPIE_LADY_ELEGANCE trap effect */
  /* TODO: wire HARPIE_LADY_ELEGANCE in trap dispatcher */
/* HARPIES_FEATHER_STORM trap effect */
  /* TODO: wire HARPIES_FEATHER_STORM in trap dispatcher */
/* HUMID_WINDS trap effect */
  /* TODO: wire HUMID_WINDS in trap dispatcher */
/* HYSTERIC_PARTY trap effect */
  /* TODO: wire HYSTERIC_PARTY in trap dispatcher */
/* MAGICIAN_NAVIGATION trap effect */
  /* TODO: wire MAGICIAN_NAVIGATION in trap dispatcher */
/* MAGICIANS_COMBINATION trap effect */
  /* TODO: wire MAGICIANS_COMBINATION in trap dispatcher */
/* METAVERSE trap effect */
  /* TODO: wire METAVERSE in trap dispatcher */
/* OFFERING_TO_THE_SNAKE_DEITY trap effect */
  /* TODO: wire OFFERING_TO_THE_SNAKE_DEITY in trap dispatcher */
/* RED_REBOOT trap effect */
  /* TODO: wire RED_REBOOT in trap dispatcher */
/* RISE_OF_THE_SNAKE_DEITY trap effect */
  /* TODO: wire RISE_OF_THE_SNAKE_DEITY in trap dispatcher */
/* SERPENT_SUPPRESSION trap effect */
  /* TODO: wire SERPENT_SUPPRESSION in trap dispatcher */
/* SHADDOLL_CORE trap effect */
  /* TODO: wire SHADDOLL_CORE in trap dispatcher */
/* SHADDOLL_SCHISM trap effect */
  /* TODO: wire SHADDOLL_SCHISM in trap dispatcher */
/* SNAKE_DEITYS_COMMAND trap effect */
  /* TODO: wire SNAKE_DEITYS_COMMAND in trap dispatcher */
/* SNAKE_WHISTLE trap effect */
  /* TODO: wire SNAKE_WHISTLE in trap dispatcher */
/* TRAP_TRICK trap effect */
  /* TODO: wire TRAP_TRICK in trap dispatcher */
/* VENOM_BURN trap effect */
  /* TODO: wire VENOM_BURN in trap dispatcher */
/* ACE_OF_WAND trap effect */
  /* TODO: wire ACE_OF_WAND in trap dispatcher */
/* ARCANA_CALL trap effect */
  /* TODO: wire ARCANA_CALL in trap dispatcher */

/* FAVOURITE_CONTACT trap effect */
  /* TODO: wire FAVOURITE_CONTACT in trap dispatcher */
/* GLADIATOR_BEAST_WAR_CHARIOT trap effect */
  /* TODO: wire GLADIATOR_BEAST_WAR_CHARIOT in trap dispatcher */
/* GLADIATOR_BEASTS_MEDUSA_SHIELD trap effect */
  /* TODO: wire GLADIATOR_BEASTS_MEDUSA_SHIELD in trap dispatcher */
/* GLADIATOR_BEASTS_VALOR trap effect */
  /* TODO: wire GLADIATOR_BEASTS_VALOR in trap dispatcher */
/* GLADIATOR_NAUMACHIA trap effect */
  /* TODO: wire GLADIATOR_NAUMACHIA in trap dispatcher */
/* GLORIOUS_ILLUSION trap effect */
  /* TODO: wire GLORIOUS_ILLUSION in trap dispatcher */
/* LIGHT_OF_DESTRUCTION trap effect */
  /* TODO: wire LIGHT_OF_DESTRUCTION in trap dispatcher */
/* LIGHT_SPIRAL trap effect */
  /* TODO: wire LIGHT_SPIRAL in trap dispatcher */
/* LIGHTSWORN_AEGIS trap effect */
  /* TODO: wire LIGHTSWORN_AEGIS in trap dispatcher */
/* LIGHTSWORN_BARRIER trap effect */
  /* TODO: wire LIGHTSWORN_BARRIER in trap dispatcher */
/* LIGHTSWORN_JUDGEMENT trap effect */
  /* TODO: wire LIGHTSWORN_JUDGEMENT in trap dispatcher */
/* NEXT trap effect */
  /* TODO: wire NEXT in trap dispatcher */
/* REVERSAL_OF_FATE trap effect */
  /* TODO: wire REVERSAL_OF_FATE in trap dispatcher */
/* THUMBS_DOWN trap effect */
  /* TODO: wire THUMBS_DOWN in trap dispatcher */
/* TOUR_OF_DOOM trap effect */
  /* TODO: wire TOUR_OF_DOOM in trap dispatcher */
/* TROJAN_GLADIATOR_BEAST trap effect */
  /* TODO: wire TROJAN_GLADIATOR_BEAST in trap dispatcher */
/* TWILIGHT_CLOTH trap effect */
  /* TODO: wire TWILIGHT_CLOTH in trap dispatcher */
/* TWILIGHT_ERASER trap effect */
  /* TODO: wire TWILIGHT_ERASER in trap dispatcher */
/* VANQUISHING_LIGHT trap effect */
  /* TODO: wire VANQUISHING_LIGHT in trap dispatcher */
/* ALL_OUT_ATTACKS trap effect */
  /* TODO: wire ALL_OUT_ATTACKS in trap dispatcher */
/* ANCIENT_GEAR_DUEL trap effect */
  /* TODO: wire ANCIENT_GEAR_DUEL in trap dispatcher */
/* BATTLE_MANIA trap effect */
  /* TODO: wire BATTLE_MANIA in trap dispatcher */
/* CROSS_DIMENSONAL_DUEL trap effect */
  /* TODO: wire CROSS_DIMENSONAL_DUEL in trap dispatcher */
/* DAMAGE_EQUALS_REPTILE trap effect */
  /* TODO: wire DAMAGE_EQUALS_REPTILE in trap dispatcher */
/* EXCHANGE_OF_THE_SPIRIT trap effect */
  /* TODO: wire EXCHANGE_OF_THE_SPIRIT in trap dispatcher */
/* FOSSIL_EXCAVATION trap effect */
  /* TODO: wire FOSSIL_EXCAVATION in trap dispatcher */
/* HUNTING_INSTINCT trap effect */
  /* TODO: wire HUNTING_INSTINCT in trap dispatcher */
/* ICARUS_ATTACK trap effect */
  /* TODO: wire ICARUS_ATTACK in trap dispatcher */
/* MACRO_COSMOS trap effect */
  /* TODO: wire MACRO_COSMOS in trap dispatcher */
/* MAGICAL_ARM_SHIELD trap effect */
  /* TODO: wire MAGICAL_ARM_SHIELD in trap dispatcher */
/* MAGICIANS_CIRCLE trap effect */
  /* TODO: wire MAGICIANS_CIRCLE in trap dispatcher */
/* MORPHTRONIC_BIND trap effect */
  /* TODO: wire MORPHTRONIC_BIND in trap dispatcher */