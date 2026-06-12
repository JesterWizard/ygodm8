#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "embodiment_of_apophis.h"

unsigned char IsSorcererOfDarkMagicTrapLockActive(void);

static u8 OriginMonsterCanBeHarmfullyTargeted(void) {
  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (IsGodCard(gTrapEffectData.originCardId) == TRUE)
    return FALSE;
  if (IsImmuneToHarmfulTargetedEffectsOnField(gTrapEffectData.originCardId, gTrapEffectData.originRow))
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
#define TRAP_MAGIC_CYLINDER 23
extern s16 gUnk_8E1172C[];
extern s16 gUnk_8E11738[];
extern s16 gUnk_8E11744[];
extern s16 gUnk_8E11788[];

static bool8 CheckTrapActivationConditions__Hook(u16 id) {
  unsigned char ret;

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
        gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
        SetFinalStat(&gStatMod);
        ret = gCardInfo.atk <= 500;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_HOUSE_OF_ADHESIVE_TAPE;
      break;
    case TRAP_EATGABOON:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
        SetFinalStat(&gStatMod);
        ret = gCardInfo.atk <= 1000;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_EATGABOON;
      break;
    case TRAP_BEAR_TRAP:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
        SetFinalStat(&gStatMod);
        ret = gCardInfo.atk <= 1500;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_BEAR_TRAP;
      break;
    case TRAP_INVISIBLE_WIRE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
        SetFinalStat(&gStatMod);
        ret = gCardInfo.atk <= 2000;
      }
      if (ret)
        gTrapEffectData.trapCardId = TRAP_INVISIBLE_WIRE;
      break;
    case TRAP_ACID_TRAP_HOLE:
      ret = OriginMonsterCanBeHarmfullyTargeted();
      if (ret) {
        gStatMod.card = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]->id;
        gStatMod.field = gDuel.field;
        gStatMod.stage = GetFinalStage(gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol]);
        SetFinalStat(&gStatMod);
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
    default:
      ret = FALSE;
      break;
  }
  return ret;
}

LYN_REPLACE_CHECK(IsTrapTriggered);
unsigned IsTrapTriggered__Replacement(void) {
  unsigned char i;

  gTrapEffectData.trapCardId = 0;
  if (IsSorcererOfDarkMagicTrapLockActive())
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    gTrapEffectData.trapZoneCol = i;
    if (CheckTrapActivationConditions__Hook(gTurnZones[0][i]->id) == TRUE) {
      if (gTrapEffectData.trapCardId != TRAP_EMBODIMENT_OF_APOPHIS)
        return TRUE;
    }
  }

  return FALSE;
}
