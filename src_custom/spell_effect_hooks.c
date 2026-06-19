#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "cost_down.h"
#include "curse_of_darkness.h"
#include "custom_field_spell.h"
#include "soul_taker.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "jar_robber.h"
#include "spirit_of_the_pot_of_greed.h"
#include "duel_helpers.h"
#include "kishido_spirit.h"
#include "ring_of_destruction.h"
extern void EffectCardOfDemise(void);
extern void EffectCardOfSanctity(void);
extern void EffectJamBreedingMachine(void);
extern void EffectShieldAndSword(void);
extern void EffectSwordsOfRevealingLight(void);
extern void EffectChainEnergy(void);
extern void EffectExchange(void);
extern void EffectMagePower(void);
extern void EffectUnitedWeStand(void);
extern void EffectWaveMotionCannon(void);
extern void EffectPyramidOfLight(void);
extern void EffectSoulExchange(void);
extern void EffectMysticalSpaceTyphoon(void);
extern void EffectDoubleSummon(void);
extern void EffectCostDown(void);
extern void EffectAncientRules(void);
extern void EffectSagesStone(void);
extern void EffectDarkMagicCurtain(void);
extern void EffectRiryoku(void);
extern void EffectGuardianTreasure(void);
extern void EffectGoblinThief(void);
extern void EffectDelinquentDuo(void);
extern void EffectConfiscation(void);
extern void EffectMeteorOfDestruction(void);
extern void EffectBlockAttack(void);
extern void EffectToll(void);
extern void EffectSkullInvitation(void);
extern void EffectCoffinSeller(void);
extern void EffectBottomlessShiftingSand(void);
extern void EffectRainOfMercy(void);
extern void EffectUpstartGoblin(void);
extern void EffectReload(void);
extern void EffectThousandEnergy(void);
extern void EffectNegativeEnergy(void);
extern void EffectTrianglePower(void);
extern void EffectTheDarkDoor(void);
extern void EffectLevelLimitAreaB(void);
extern void EffectTheForcefulSentry(void);
extern void EffectLimiterRemoval(void);
extern void EffectCardDestruction(void);
extern void EffectDarkRoomOfNightmare(void);
extern void EffectGracefulCharity(void);
extern void EffectTwinSwordsOfFlashingLightTryce(void);
extern void EffectThousandKnives(void);
extern void EffectSoulTaker(void);
extern void EffectCreatureSwap(void);
extern void EffectPreciousCardsFromBeyond(void);
extern void EffectFinalCountdown(void);
extern void EffectBurningLand(void);
extern void EffectDarkSnakeSyndrome(void);
extern void EffectGravekeepersServant(void);
extern void EffectVengefulBogSpirit(void);
extern void EffectRaregoldArmor(void);
extern void EffectGracefulDice(void);
extern void EffectChaosGreed(void);
extern void EffectBookOfMoon(void);
extern void EffectThunderCrash(void);
extern void EffectRingOfDestruction(void);
extern void EffectKnightsTitle(void);
extern void EffectTheFluteOfSummoningDragon(void);
void ApplyMahaVailoEquipBonus(struct DuelCard* zone);

void ActivateSpellEffect(void);
void ActivateTrapEffect(u16 lp);
unsigned IsTrapTriggered(void);
u8 TryPayChainEnergyCost(void);
u8 TryMaryokutaiSpellCounter(void);

static void SetupSpellTrapOrigin(void)
{
  u8 spellRow;
  u8 spellCol;

  if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP) {
    spellRow = gSpellEffectData.row2;
    spellCol = gSpellEffectData.col2;
  } else {
    spellRow = gSpellEffectData.row1;
    spellCol = gSpellEffectData.col1;
  }

  gTrapEffectData.originRow = spellRow;
  gTrapEffectData.originCol = spellCol;
  gTrapEffectData.originCardId = gSpellEffectData.id;
}

static u8 SpellHandlesOwnTrapResponse(u16 spellId, u8 spellEffect)
{
  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP)
    return TRUE;

  switch (spellId) {
    case MAGE_POWER:
    case UNITED_WE_STAND:
    case MYSTICAL_SPACE_TYPHOON:
    case RIRYOKU:
    case WAVE_MOTION_CANNON:
    case GOBLIN_THIEF:
    case DELINQUENT_DUO:
    case CONFISCATION:
    case METEOR_OF_DESTRUCTION:
    case BLOCK_ATTACK:
    case BOOK_OF_MOON:
    case SOUL_TAKER:
    case CREATURE_SWAP:
    case THUNDER_CRASH:
    case RAIN_OF_MERCY:
    case UPSTART_GOBLIN:
      return TRUE;
    default:
      break;
  }

  switch (spellEffect) {
    case SPELL_EFFECT_MOOYAN_CURRY:
    case SPELL_EFFECT_RED_MEDICINE:
    case SPELL_EFFECT_GOBLINS_SECRET_REMEDY:
    case SPELL_EFFECT_SOUL_OF_THE_PURE:
    case SPELL_EFFECT_DIAN_KETO_THE_CURE_MASTER:
    case SPELL_EFFECT_SPARKS:
    case SPELL_EFFECT_HINOTAMA:
    case SPELL_EFFECT_FINAL_FLAME:
    case SPELL_EFFECT_OOKAZI:
    case SPELL_EFFECT_TREMENDOUS_FIRE:
    case SPELL_EFFECT_DARK_HOLE:
    case SPELL_EFFECT_RAIGEKI:
      return TRUE;
    default:
      return FALSE;
  }
}

static u8 TryResolveSpellActivationThroughTraps(u16 spellId)
{
  return Duel_TryResolveSpellThroughTraps(spellId, NULL) != DUEL_ACTION_BLOCKED;
}

LYN_REPLACE_CHECK(ActivateSpellEffect);
static void ActivateSpellEffect__Body(void)
{
  if (gSpellEffectData.row1 == ACTIVE_DUELIST_HAND) {
    if (!TryPayChainEnergyCost())
      return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(1);
  SetCardInfo(gSpellEffectData.id);
  SetupSpellTrapOrigin();

  if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  TryActivateImperialOrderOnSpellChain();

  if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (GetTypeGroup(gSpellEffectData.id) == TYPE_GROUP_TRAP) {
    TryActivateRoyalDecreeOnTrapChain();
    if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
    if (Duel_TryResolveTrapThroughTraps(gSpellEffectData.id) == DUEL_ACTION_BLOCKED)
      return;
  }

  if (TryJarRobberPotOfGreedCounter())
    return;

  if (TryMaryokutaiSpellCounter())
    return;

  if (!SpellHandlesOwnTrapResponse(gSpellEffectData.id, gCardInfo.spellEffect)) {
    if (!TryResolveSpellActivationThroughTraps(gSpellEffectData.id))
      return;
  }

  TryApplyCurseOfDarknessSpellDamage();
  if (IsDuelOver() == TRUE)
    return;

  if (TryActivateCustomFieldSpell(gSpellEffectData.id))
    return;

  if (TryActivateVanillaFieldSpell(gSpellEffectData.id, gCardInfo.spellEffect))
    return;

  if (gCardInfo.spellEffect >= SPELL_EFFECT_FOREST
      && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI) {
    gSpellEffects[gCardInfo.spellEffect]();
    return;
  }

  switch (gSpellEffectData.id) {
    case CARD_OF_DEMISE:
      EffectCardOfDemise();
      return;
    case CARD_OF_SANCTITY:
      EffectCardOfSanctity();
      return;
    case JAM_BREEDING_MACHINE:
      EffectJamBreedingMachine();
      return;
    case SHIELD_AND_SWORD:
      EffectShieldAndSword();
      return;
    case SWORDS_OF_REVEALING_LIGHT:
      EffectSwordsOfRevealingLight();
      return;
    case CHAIN_ENERGY:
      EffectChainEnergy();
      return;
    case TOLL:
      EffectToll();
      return;
    case SKULL_INVITATION:
      EffectSkullInvitation();
      return;
    case COFFIN_SELLER:
      EffectCoffinSeller();
      return;
    case BOTTOMLESS_SHIFTING_SAND:
      EffectBottomlessShiftingSand();
      return;
    case RAIN_OF_MERCY:
      EffectRainOfMercy();
      return;
    case UPSTART_GOBLIN:
      EffectUpstartGoblin();
      return;
    case RELOAD:
      EffectReload();
      return;
    case WAVE_MOTION_CANNON:
      EffectWaveMotionCannon();
      return;
    case PYRAMID_OF_LIGHT:
      EffectPyramidOfLight();
      return;
    case SOUL_EXCHANGE:
      EffectSoulExchange();
      return;
    case MYSTICAL_SPACE_TYPHOON:
      EffectMysticalSpaceTyphoon();
      return;
    case DOUBLE_SUMMON:
      EffectDoubleSummon();
      return;
    case COST_DOWN:
      EffectCostDown();
      return;
    case ANCIENT_RULES:
      EffectAncientRules();
      return;
    case SAGES_STONE:
      EffectSagesStone();
      return;
    case DARK_MAGIC_CURTAIN:
      EffectDarkMagicCurtain();
      return;
    case RIRYOKU:
      EffectRiryoku();
      return;
    case GUARDIAN_TREASURE:
      EffectGuardianTreasure();
      return;
    case GOBLIN_THIEF:
      EffectGoblinThief();
      return;
    case DELINQUENT_DUO:
      EffectDelinquentDuo();
      return;
    case CONFISCATION:
      EffectConfiscation();
      return;
    case METEOR_OF_DESTRUCTION:
      EffectMeteorOfDestruction();
      return;
    case BLOCK_ATTACK:
      EffectBlockAttack();
      return;
    case EXCHANGE:
      EffectExchange();
      return;
    case MAGE_POWER:
      EffectMagePower();
      return;
    case UNITED_WE_STAND:
      EffectUnitedWeStand();
      return;
    case THOUSAND_ENERGY:
      EffectThousandEnergy();
      return;
    case NEGATIVE_ENERGY:
      EffectNegativeEnergy();
      return;
    case TRIANGLE_POWER:
      EffectTrianglePower();
      return;
    case THE_DARK_DOOR:
      EffectTheDarkDoor();
      return;
    case LEVEL_LIMIT_AREA_B:
      EffectLevelLimitAreaB();
      return;
    case THE_FORCEFUL_SENTRY:
      EffectTheForcefulSentry();
      return;
    case LIMITER_REMOVAL:
      EffectLimiterRemoval();
      return;
    case CARD_DESTRUCTION:
      EffectCardDestruction();
      return;
    case DARK_ROOM_OF_NIGHTMARE:
      EffectDarkRoomOfNightmare();
      return;
    case GRACEFUL_CHARITY:
      EffectGracefulCharity();
      return;
    case TWIN_SWORDS_OF_FLASHING_LIGHT_TRYCE:
      EffectTwinSwordsOfFlashingLightTryce();
      return;
    case THOUSAND_KNIVES:
      EffectThousandKnives();
      return;
    case SOUL_TAKER:
      EffectSoulTaker();
      return;
    case CREATURE_SWAP:
      EffectCreatureSwap();
      return;
    case PRECIOUS_CARDS_FROM_BEYOND:
      EffectPreciousCardsFromBeyond();
      return;
    case FINAL_COUNTDOWN:
      EffectFinalCountdown();
      return;
    case BURNING_LAND:
      EffectBurningLand();
      return;
    case DARK_SNAKE_SYNDROME:
      EffectDarkSnakeSyndrome();
      return;
    case GRAVEKEEPERS_SERVANT:
      EffectGravekeepersServant();
      return;
    case VENGEFUL_BOG_SPIRIT:
      EffectVengefulBogSpirit();
      return;
    case RAREGOLD_ARMOR:
      EffectRaregoldArmor();
      return;
    case GRACEFUL_DICE:
      EffectGracefulDice();
      return;
    case CHAOS_GREED:
      EffectChaosGreed();
      return;
    case BOOK_OF_MOON:
      EffectBookOfMoon();
      return;
    case THUNDER_CRASH:
      EffectThunderCrash();
      return;
    case RING_OF_DESTRUCTION:
      EffectRingOfDestruction();
      return;
    case KNIGHTS_TITLE:
      EffectKnightsTitle();
      return;
    case THE_FLUTE_OF_SUMMONING_DRAGON:
      EffectTheFluteOfSummoningDragon();
      return;
    case KISHIDO_SPIRIT:
      EffectKishidoSpirit();
      return;
    case POT_OF_GREED:
      TryDrawingCard(WhoseTurn());
      TryDrawingCard(WhoseTurn());
      ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);
      TrySpiritOfThePotOfGreedAfterPotOfGreed();
      if (!gHideEffectText) {
        gCardEffectTextData.cardId = POT_OF_GREED;
        ActivateCardEffectText();
      }
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP
          && gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id == CARD_NONE)
        ApplyMahaVailoEquipBonus(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
      return;
  }
}

void ActivateSpellEffect__Replacement(void)
{
  Duel_BeginSpellEffectResolve();
  ActivateSpellEffect__Body();
  Duel_EndSpellEffectResolve();
}
