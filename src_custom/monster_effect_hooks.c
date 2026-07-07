#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "configs/runtime.h"
#include "duel_helpers.h"
#include "constants/monster_effects.h"
#include "constants/card_ids.h"
#include "cannon_soldier.h"
#include "monster_effect_usage.h"
#include "soul_exchange.h"
#include "tribute.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "the_tyrant_neptune.h"
#include "weather_report.h"
#include "berserk_gorilla.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "vengeful_bog_spirit.h"
#include "sasuke_samurai_2.h"
#include "man_thro_tro.h"
#include "breaker_the_magical_warrior.h"
#include "jowls_of_dark_demise.h"
#include "invader_of_the_throne.h"
#include "possessed_dark_soul.h"
#include "ryu_kishin_clown.h"
#include "nightmare_wheel.h"
#include "dark_dust_spirit.h"
#include "levia_dragon_daedalus.h"
#include "spirit_caller.h"
#include "amazoness_archer.h"
#include "elemental_hero_bubbleman.h"
#include "harpies_pet_baby_dragon.h"
#include "blowback_dragon.h"
#include "cyber_laser_dragon.h"
#include "elemental_hero_rampart_blaster.h"
#include "elemental_hero_tempest.h"
#include "elemental_hero_wildedge.h"
#include "elemental_hero_thunder_giant.h"
#include "elemental_hero_woodsman.h"
#include "elemental_hero_ocean.h"
#include "elemental_hero_lady_heat.h"
#include "elemental_hero_neos_alius.h"
#include "elemental_hero_great_tornado.h"
#include "the_wicked_dreadroot.h"
#include "elemental_hero_sunrise.h"
#include "elemental_hero_absolute_zero.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_necroid_shaman.h"
#include "elemental_hero_plasma_vice.h"
#include "elemental_hero_terra_firma.h"
#include "elemental_hero_wild_wingman.h"
#include "elemental_hero_ice_edge.h"
#include "elemental_hero_blazeman.h"
#include "chiron_the_mage.h"
#include "chaos_emperor_dragon_envoy_of_the_end.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "lyrilusc_independent_nightingale.h"
#include "the_big_saturn.h"
#include "the_wicked_eraser.h"
#include "the_grand_jupiter.h"
#include "the_blazing_mars.h"
#include "athena.h"
#include "yubel.h"

extern void (*const gMonEffects[])(void);

void ActivateMonsterEffect(void);
void MonsterActionMenu(void);
unsigned char HandlePlayerMonsterAction(void);
void sub_8044570(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
unsigned char CanActivateAmazonessChainMaster(void);
void ActivateAmazonessChainMasterEffect(void);
void ActivateGoddessOfWhimEffect(void);
void ActivateMaskOfDarknessEffect(void);
void ActivatePrincessOfTsurugiEffect(void);
void ActivateFireReaperEffect(void);
unsigned char CanActivateNeedleBall(void);
void ActivateNeedleBallEffect(void);
void ActivateNeedleWormEffect(void);
unsigned char CanActivateKarateMan(void);
void ActivateKarateManEffect(void);
unsigned char CanActivateMonsterTamer(void);
void ActivateMonsterTamerEffect(void);
void ActivateHourglassOfLifeEffect(void);
unsigned char CanActivateDesKoala(void);
void ActivateDesKoalaEffect(void);
unsigned char CanActivateHARPIES_PET_BABY_DRAGON(void);
void ActivateHARPIES_PET_BABY_DRAGONEffect(void);
unsigned char CanActivateBLOWBACK_DRAGON(void);
void ActivateBLOWBACK_DRAGONEffect(void);
unsigned char CanActivateCYBER_LASER_DRAGON(void);
void ActivateCYBER_LASER_DRAGONEffect(void);
unsigned char CanActivateDARK_END_DRAGON(void);
void ActivateDARK_END_DRAGONEffect(void);
unsigned char CanActivateLIGHT_END_DRAGON(void);
void ActivateLIGHT_END_DRAGONEffect(void);
unsigned char CanActivateDARK_ARMED_DRAGON(void);
void ActivateDARK_ARMED_DRAGONEffect(void);
unsigned char CanActivateMonsterEffect(void) {
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  u16 neptuneSavedId;
  unsigned char canActivate;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  neptuneSavedId = Duel_BeginCopiedEffectIdentity(zone);

  if (gMonEffect.id == ELEMENTAL_HERO_NEOS_ALIUS)
    canActivate = CanActivateElementalHeroNeosAlius();
  else if (zone->id == THE_GRAND_JUPITER)
    canActivate = CanActivateTheGrandJupiter();
  else {
    switch (gCardInfo.monsterEffect) {
      case MONSTER_EFFECT_INJECTION_FAIRY_LILY:
        canActivate = CanActivateInjectionFairyLily();
        break;
      case MONSTER_EFFECT_CYBER_STEIN:
        canActivate = CanActivateCyberStein();
        break;
      case MONSTER_EFFECT_NEEDLE_BALL:
        canActivate = CanActivateNeedleBall();
        break;
      case MONSTER_EFFECT_AMAZON_CHAIN_MASTER:
        canActivate = CanActivateAmazonessChainMaster();
        break;
      case MONSTER_EFFECT_PENGUIN_SOLDIER:
        canActivate = CanActivatePenguinSoldier();
        break;
      case MONSTER_EFFECT_KARATE_MAN:
        canActivate = CanActivateKarateMan();
        break;
      case MONSTER_EFFECT_KAIBAMAN:
        canActivate = CanActivateKaibaman();
        break;
      case MONSTER_EFFECT_MONSTER_TAMER:
        canActivate = CanActivateMonsterTamer();
        break;
      case MONSTER_EFFECT_CANNON_SOLDIER:
        canActivate = CanActivateCannonSoldier();
        break;
      case MONSTER_EFFECT_DES_KOALA:
        canActivate = CanActivateDesKoala();
        break;
      case MONSTER_EFFECT_WEATHER_REPORT:
        canActivate = CanActivateWeatherReport();
        break;
      case MONSTER_EFFECT_THE_AGENT_OF_CREATION_VENUS:
        canActivate = CanActivateTheAgentOfCreationVenus();
        break;
      case MONSTER_EFFECT_MAGICAL_MERCHANT:
        canActivate = CanActivateMagicalMerchant();
        break;
      case MONSTER_EFFECT_SASUKE_SAMURAI_2:
        canActivate = CanActivateSasukeSamurai2();
        break;
      case MONSTER_EFFECT_MAN_THRO_TRO:
        canActivate = CanActivateManThroTro();
        break;
      case MONSTER_EFFECT_BREAKER_THE_MAGICAL_WARRIOR:
        canActivate = CanActivateBreakerTheMagicalWarrior();
        break;
      case MONSTER_EFFECT_JOWLS_OF_DARK_DEMISE:
        canActivate = CanActivateJowlsOfDarkDemise();
        break;
      case MONSTER_EFFECT_POSSESSED_DARK_SOUL:
        canActivate = CanActivatePossessedDarkSoul();
        break;
      case MONSTER_EFFECT_INVADER_OF_THE_THRONE:
        canActivate = CanActivateInvaderOfTheThrone();
        break;
      case MONSTER_EFFECT_SPIRIT_CALLER:
        canActivate = CanActivateSpiritCaller();
        break;
      case MONSTER_EFFECT_RYU_KISHIN_CLOWN:
        canActivate = CanActivateRyuKishinClown();
        break;
      case MONSTER_EFFECT_DARK_DUST_SPIRIT:
        canActivate = CanActivateDarkDustSpirit();
        break;
      case MONSTER_EFFECT_LEVIA_DRAGON_DAEDALUS:
        canActivate = CanActivateLeviaDragonDaedalus();
        break;
      case MONSTER_EFFECT_BUBBLEMAN:
        canActivate = CanActivateElementalHeroBubbleman();
        break;
      case MONSTER_EFFECT_HARPIES_PET_BABY_DRAGON:
        canActivate = CanActivateHARPIES_PET_BABY_DRAGON();
        break;
      case MONSTER_EFFECT_BLOWBACK_DRAGON:
        canActivate = CanActivateBLOWBACK_DRAGON();
        break;
      case MONSTER_EFFECT_CYBER_LASER_DRAGON:
        canActivate = CanActivateCYBER_LASER_DRAGON();
        break;
      case MONSTER_EFFECT_DARK_END_DRAGON:
        canActivate = CanActivateDARK_END_DRAGON();
        break;
      case MONSTER_EFFECT_LIGHT_END_DRAGON:
        canActivate = CanActivateLIGHT_END_DRAGON();
        break;
      case MONSTER_EFFECT_DARK_ARMED_DRAGON:
        canActivate = CanActivateDARK_ARMED_DRAGON();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_RAMPART_BLASTER:
        canActivate = CanActivateElementalHeroRampartBlaster();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_TEMPEST:
        canActivate = CanActivateElementalHeroTempest();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_WILDEDGE:
        canActivate = CanActivateElementalHeroWildedge();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_THUNDER_GIANT:
        canActivate = CanActivateElementalHeroThunderGiant();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_WOODSMAN:
        canActivate = CanActivateElementalHeroWoodsman();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_OCEAN:
        canActivate = CanActivateElementalHeroOcean();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_LADY_HEAT:
        canActivate = CanActivateElementalHeroLadyHeat();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_TERRA_FIRMA:
        canActivate = CanActivateElementalHeroTerraFirma();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_WILD_WINGMAN:
        canActivate = CanActivateElementalHeroWildWingman();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_PLASMA_VICE:
        canActivate = CanActivateElementalHeroPlasmaVice();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_ICE_EDGE:
        canActivate = CanActivateElementalHeroIceEdge();
        break;
      case MONSTER_EFFECT_ELEMENTAL_HERO_BLAZEMAN:
        canActivate = CanActivateElementalHeroBlazeman();
        break;
      case MONSTER_EFFECT_CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END:
        canActivate = CanActivateChaosEmperorDragonEnvoyOfTheEnd();
        break;
      case MONSTER_EFFECT_BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING:
        canActivate = CanActivateBlackLusterSoldierEnvoyOfTheBeginning();
        break;
      case MONSTER_EFFECT_THE_WINGED_DRAGON_OF_RA_SPHERE_MODE:
        canActivate = CanActivateTheWingedDragonOfRaSphereMode();
        break;
      case MONSTER_EFFECT_LYRILUSC_INDEPENDENT_NIGHTINGALE:
        canActivate = CanActivateLyriluscIndependentNightingale();
        break;
      case MONSTER_EFFECT_THE_BIG_SATURN:
        canActivate = CanActivateTheBigSaturn();
        break;
      case MONSTER_EFFECT_THE_WICKED_ERASER:
        canActivate = CanActivateTheWickedEraser();
        break;
      case MONSTER_EFFECT_THE_GRAND_JUPITER:
        canActivate = CanActivateTheGrandJupiter();
        break;
      case MONSTER_EFFECT_THE_BLAZING_MARS:
        canActivate = CanActivateTheBlazingMars();
        break;
      case MONSTER_EFFECT_ATHENA:
        canActivate = CanActivateATHENA();
        break;
      default:
        canActivate = TRUE;
        break;
    }
  }

  Duel_EndCopiedEffectIdentity(zone, neptuneSavedId);
  return canActivate;
}

unsigned char TryActivateSkillDrainAndNegate(void);

static void ActivateMonsterEffectBody(struct DuelCard *zone)
{
  ResetCardEffectTextData();
  SetCardEffectTextType(2);
  SetCardInfo(gMonEffect.id);

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_GRAND_JUPITER
      || zone->id == THE_GRAND_JUPITER) {
    ActivateTheGrandJupiterEffect();
    return;
  }

  MarkMonsterEffectUsed(zone);

  if (gMonEffect.id == ELEMENTAL_HERO_NEOS_ALIUS) {
    ActivateElementalHeroNeosAliusEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_INJECTION_FAIRY_LILY) {
    ActivateInjectionFairyLilyEffect();
    return;
  }

  if (gMonEffect.id == AMAZON_CHAIN_MASTER) {
    ActivateAmazonessChainMasterEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CYBER_JAR) {
    EffectCyberJar();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CYBER_STEIN) {
    EffectCyberStein();
    return;
  }

  if (gMonEffect.id == NEEDLE_BALL) {
    ActivateNeedleBallEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_NEEDLE_WORM) {
    ActivateNeedleWormEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_GODDESS_OF_WHIM) {
    ActivateGoddessOfWhimEffect();
    return;
  }

  if (gMonEffect.id == MASK_OF_DARKNESS) {
    ActivateMaskOfDarknessEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_PRINCESS_OF_TSURUGI) {
    ActivatePrincessOfTsurugiEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_PENGUIN_SOLDIER) {
    ActivatePenguinSoldierEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_KARATE_MAN) {
    ActivateKarateManEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_FIRE_REAPER) {
    ActivateFireReaperEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_COPYCAT) {
    ActivateCopycatEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_KAIBAMAN) {
    ActivateKaibamanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MONSTER_TAMER) {
    ActivateMonsterTamerEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CANNON_SOLDIER) {
    ActivateCannonSoldierEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DES_KOALA) {
    ActivateDesKoalaEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_WEATHER_REPORT) {
    ActivateWeatherReportEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_AGENT_OF_CREATION_VENUS) {
    ActivateTheAgentOfCreationVenusEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_STEALTH_BIRD) {
    ActivateStealthBirdEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MAGICAL_MERCHANT) {
    ActivateMagicalMerchantEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_SASUKE_SAMURAI_2) {
    ActivateSasukeSamurai2Effect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MAN_THRO_TRO) {
    ActivateManThroTroEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BREAKER_THE_MAGICAL_WARRIOR) {
    ActivateBreakerTheMagicalWarriorEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DICE_JAR) {
    ActivateDiceJarEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_JOWLS_OF_DARK_DEMISE) {
    ActivateJowlsOfDarkDemiseEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_POSSESSED_DARK_SOUL) {
    ActivatePossessedDarkSoulEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_INVADER_OF_THE_THRONE) {
    ActivateInvaderOfTheThroneEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_SPIRIT_CALLER) {
    ActivateSpiritCallerEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_RYU_KISHIN_CLOWN) {
    ActivateRyuKishinClownEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_DUST_SPIRIT) {
    ActivateDarkDustSpiritEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_LEVIA_DRAGON_DAEDALUS) {
    ActivateLeviaDragonDaedalusEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BUBBLEMAN) {
    ActivateElementalHeroBubblemanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_HARPIES_PET_BABY_DRAGON) {
    ActivateHARPIES_PET_BABY_DRAGONEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BLOWBACK_DRAGON) {
    ActivateBLOWBACK_DRAGONEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CYBER_LASER_DRAGON) {
    ActivateCYBER_LASER_DRAGONEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_END_DRAGON) {
    ActivateDARK_END_DRAGONEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_LIGHT_END_DRAGON) {
    ActivateLIGHT_END_DRAGONEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_RAMPART_BLASTER) {
    ActivateElementalHeroRampartBlasterEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_TEMPEST) {
    ActivateElementalHeroTempestEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_WILDEDGE) {
    ActivateElementalHeroWildedgeEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_THUNDER_GIANT) {
    ActivateElementalHeroThunderGiantEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_WOODSMAN) {
    ActivateElementalHeroWoodsmanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_OCEAN) {
    ActivateElementalHeroOceanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_LADY_HEAT) {
    ActivateElementalHeroLadyHeatEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_TERRA_FIRMA) {
    ActivateElementalHeroTerraFirmaEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_WILD_WINGMAN) {
    ActivateElementalHeroWildWingmanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_PLASMA_VICE) {
    ActivateElementalHeroPlasmaViceEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_ICE_EDGE) {
    ActivateElementalHeroIceEdgeEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ELEMENTAL_HERO_BLAZEMAN) {
    ActivateElementalHeroBlazemanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END) {
    ActivateChaosEmperorDragonEnvoyOfTheEndEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING) {
    ActivateBlackLusterSoldierEnvoyOfTheBeginningEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_WINGED_DRAGON_OF_RA_SPHERE_MODE) {
    ActivateTheWingedDragonOfRaSphereModeEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_LYRILUSC_INDEPENDENT_NIGHTINGALE) {
    ActivateLyriluscIndependentNightingaleEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_BIG_SATURN) {
    ActivateTheBigSaturnEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_WICKED_ERASER) {
    ActivateTheWickedEraserEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_BLAZING_MARS) {
    ActivateTheBlazingMarsEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_ATHENA) {
    ActivateATHENAEffect();
    return;
  }

  if (gMonEffect.id == CHIRON_THE_MAGE) {
    ActivateChironTheMageEffect();
    return;
  }

  if (gMonEffect.id == AMAZONESS_ARCHER) {
    ActivateAmazonessArcherEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_HOURGLASS_OF_LIFE) {
    ActivateHourglassOfLifeEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MONSTER_EYE) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++)
      if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
        gTurnHands[INACTIVE_DUELIST][i]->isFaceUp = TRUE;

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = gMonEffect.id;
      ActivateCardEffectText();
    }
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_ARMED_DRAGON) {
    ActivateDARK_ARMED_DRAGONEffect();
    return;
  }

  Duel_BeginMonsterEffectResolve();
  gMonEffects[gCardInfo.monsterEffect]();
  Duel_EndMonsterEffectResolve();
  gChaosCommandMagicianBlockedOriginMonsterEffectId = CARD_NONE;
}

LYN_REPLACE_CHECK(ActivateMonsterEffect);
void ActivateMonsterEffect__Replacement(void) {
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  u16 neptuneSavedId;

  if (TryActivateSkillDrainAndNegate())
    return;

  neptuneSavedId = Duel_BeginCopiedEffectIdentity(zone);
  ActivateMonsterEffectBody(zone);
  Duel_EndCopiedEffectIdentity(zone, neptuneSavedId);
}

LYN_REPLACE_CHECK(MonsterActionMenu);
void MonsterActionMenu__Replacement(void) {
  switch (HandlePlayerMonsterAction()) {
    case 1:
      sub_8044570();
      break;
    case 2:
      if (BerserkGorilla_CannotUseDefensePosition(
              gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
        PlayMusic(SFX_FORBIDDEN);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      } else if (NightmareWheel_CannotChangeBattlePosition(
                     gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
        PlayMusic(SFX_FORBIDDEN);
      } else if (!gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked) {
        PlayMusic(SFX_SELECT);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 1;
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      }
      else {
        PlayMusic(SFX_FORBIDDEN);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
    case 3:
      if (IsSoulExchangeActive() && gDuelCursor.currentY == PLAYER_MONSTER_ROW) {
        PlayMusic(SFX_FORBIDDEN);
        UpdateDuelGfxExceptField();
        break;
      }
      PlayMusic(SFX_TRIBUTE);
      if (IsSoulExchangeActive() && gDuelCursor.currentY == OPPONENT_MONSTER_ROW) {
        ApplyMonsterTributeFromFixedRow(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], OPPONENT_MONSTER_ROW);
      } else {
        TryCaptureGreatMajuGarzettTributeFromZone(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        TryCaptureMajuGarzettTributeFromZone(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        TryCaptureTheTyrantNeptuneTributeFromZone(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        AddTributeCredit(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
        ClearZoneAndSendMonToGraveyard2(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], DUEL_PLAYER);
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
    case 4: {
      struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];
      u8 isFaceUp = zone->isFaceUp;
      u16 effectCardId = Duel_ZoneEffectCardId(zone);

      if (!isFaceUp && NightmareWheel_CannotChangeBattlePosition(zone))
        goto FAILED;

      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked)
        zone->isDefending = 0;
      if (!isFaceUp || zone->id == CANNON_SOLDIER || zone->id == MAN_THRO_TRO
          || zone->id == POSSESSED_DARK_SOUL
          || zone->id == BREAKER_THE_MAGICAL_WARRIOR
          || zone->id == THE_AGENT_OF_CREATION_VENUS
          || zone->id == AMAZONESS_ARCHER
          || zone->id == HARPIES_PET_BABY_DRAGON
          || zone->id == BLOWBACK_DRAGON
          || zone->id == CYBER_LASER_DRAGON
          || zone->id == ELEMENTAL_HERO_RAMPART_BLASTER
          || zone->id == ELEMENTAL_HERO_TEMPEST
          || zone->id == ELEMENTAL_HERO_WILDEDGE
          || zone->id == ELEMENTAL_HERO_THUNDER_GIANT
          || zone->id == ELEMENTAL_HERO_WOODSMAN
          || zone->id == ELEMENTAL_HERO_OCEAN
          || zone->id == ELEMENTAL_HERO_LADY_HEAT
          || zone->id == ELEMENTAL_HERO_TERRA_FIRMA
          || zone->id == ELEMENTAL_HERO_WILD_WINGMAN
          || zone->id == ELEMENTAL_HERO_PLASMA_VICE
          || zone->id == ELEMENTAL_HERO_NEOS_ALIUS
          || zone->id == ELEMENTAL_HERO_ICE_EDGE
          || zone->id == ELEMENTAL_HERO_BLAZEMAN
          || zone->id == CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END
          || zone->id == BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING
          || zone->id == THE_WINGED_DRAGON_OF_RA_SPHERE_MODE
          || zone->id == LYRILUSC_INDEPENDENT_NIGHTINGALE
          || zone->id == THE_GRAND_JUPITER
          || zone->id == THE_BLAZING_MARS
          || zone->id == ATHENA
          || zone->id == DARK_ARMED_DRAGON
          || effectCardId != zone->id
          || SasukeSamurai2_AllowsFaceUpEffectActivation(effectCardId)) {
        gMonEffect.id = effectCardId;
        SetCardInfo(gMonEffect.id);
        if (gMonEffect.id == NEEDLE_BALL) {
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
          break;
        }
        gMonEffect.row = gDuelCursor.currentY;
        gMonEffect.zone = gDuelCursor.currentX;
        if ((gCardInfo.monsterEffect == MONSTER_EFFECT_NONE && gMonEffect.id != MASK_OF_DARKNESS && gMonEffect.id != NEEDLE_BALL && gMonEffect.id != AMAZONESS_ARCHER && gMonEffect.id != ELEMENTAL_HERO_NEOS_ALIUS) || !CanActivateMonsterEffect()) {
FAILED:
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
        }
        else {
          if (!isFaceUp) {
            zone->isDefending = 0;
            zone->isFaceUp = 1;
            TryVengefulBogSpiritOnFlipSummon(zone);
            TryElementalHeroGreatTornadoOnMonsterPlacement(zone);
            TryTheWickedDreadrootOnMonsterPlacement(zone);
            TryElementalHeroSunriseOnMonsterPlacement(zone);
            TryElementalHeroAbsoluteZeroOnMonsterPlacement(zone);
            UpdateDuelGfxExceptField();
            TryTheWickedDreadrootEffectTextOnMonsterPlacement(zone);
            /* ponytail: Blazeman is NS/SS only — not Flip Summon. */
          }
          if (gCardInfo.monsterEffect != MONSTER_EFFECT_RYU_KISHIN_CLOWN
              && gCardInfo.monsterEffect != MONSTER_EFFECT_DARK_DUST_SPIRIT)
            ActivateMonsterEffect();
          if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
            LockMonsterCardsInRow(4);
          if (gCardInfo.monsterEffect == MONSTER_EFFECT_RYU_KISHIN_CLOWN)
            TryActivateRyuKishinClownOnMonsterPlacement(zone);
          if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_DUST_SPIRIT)
            TryActivateDarkDustSpiritOnMonsterPlacement(zone);
          if (gDuelCursor.state == DUEL_CURSOR_CANNON_SOLDIER_TARGET
              || gDuelCursor.state == DUEL_CURSOR_MAN_THRO_TRO_TARGET
              || gDuelCursor.state == DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET
              || gDuelCursor.state == DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_HARPIES_PET_BABY_DRAGON_TARGET
              || gDuelCursor.state == DUEL_CURSOR_BLOWBACK_DRAGON_TARGET
              || gDuelCursor.state == DUEL_CURSOR_CYBER_LASER_DRAGON_TARGET
              || gDuelCursor.state == DUEL_CURSOR_BLACK_LUSTER_SOLDIER_ENVOY_TARGET
              || gDuelCursor.state == DUEL_CURSOR_TERRA_FIRMA_TARGET
              || gDuelCursor.state == DUEL_CURSOR_ELEMENTAL_HERO_WILD_WINGMAN_TARGET
              || gDuelCursor.state == DUEL_CURSOR_ELEMENTAL_HERO_GAIA_TARGET
              || gDuelCursor.state == DUEL_CURSOR_ELEMENTAL_HERO_PLASMA_VICE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET
              || gDuelCursor.state == DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET
              || gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1
              || gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2
              || gDuelCursor.state == DUEL_CURSOR_ATHENA_COST_TARGET
              || gDuelCursor.state == DUEL_CURSOR_YUBEL_TRIBUTE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_PICK_ZONE)
            break;
          UpdateDuelGfxExceptField();
          CheckWinConditionExodia();
          if (IsDuelOver() != 1)
            TryActivatingPermanentEffects();
        }
      }
      else
        goto FAILED;
      break;
    }
    case 5:
      if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending) {
        if (LevelLimitAreaB_CannotUseAttackPosition(
                gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
          PlayMusic(SFX_FORBIDDEN);
        } else if (NightmareWheel_CannotChangeBattlePosition(
                       gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
          PlayMusic(SFX_FORBIDDEN);
        } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked) {
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
        }
      } else {
        if (LevelLimitAreaA_CannotUseDefensePosition(
                gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
          PlayMusic(SFX_FORBIDDEN);
        }
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
  }
}
// Forward declarations for custom card activation handlers
// (moved to file scope because the GBA toolchain compiler
//  does not support declarations inside function bodies)
unsigned char CanActivateAMULET_DRAGON(void);
void ActivateAMULET_DRAGONEffect(void);
unsigned char CanActivateANDRO_SPHINX(void);
void ActivateANDRO_SPHINXEffect(void);
unsigned char CanActivateAPPRENTICE_ILLUSION_MAGICIAN(void);
void ActivateAPPRENTICE_ILLUSION_MAGICIANEffect(void);
unsigned char CanActivateARMAGEDDON_KNIGHT(void);
void ActivateARMAGEDDON_KNIGHTEffect(void);
unsigned char CanActivateBIRDFACE(void);
void ActivateBIRDFACEEffect(void);
unsigned char CanActivateCANNONBALL_SPEAR_SHELLFISH(void);
void ActivateCANNONBALL_SPEAR_SHELLFISHEffect(void);
unsigned char CanActivateCHIMERATECH_FORTRESS_DRAGON(void);
void ActivateCHIMERATECH_FORTRESS_DRAGONEffect(void);
unsigned char CanActivateCHIMERATECH_MEGAFLEET_DRAGON(void);
void ActivateCHIMERATECH_MEGAFLEET_DRAGONEffect(void);
unsigned char CanActivateCHIMERATECH_RAMPAGE_DRAGON(void);
void ActivateCHIMERATECH_RAMPAGE_DRAGONEffect(void);
unsigned char CanActivateCYBER_ELTANIN(void);
void ActivateCYBER_ELTANINEffect(void);
unsigned char CanActivateCYBER_KIRIN(void);
void ActivateCYBER_KIRINEffect(void);
unsigned char CanActivateCYBER_PHOENIX(void);
void ActivateCYBER_PHOENIXEffect(void);
unsigned char CanActivateCYBER_VALLEY(void);
void ActivateCYBER_VALLEYEffect(void);
unsigned char CanActivateDARK_BLADE_THE_DRAGON_KNIGHT(void);
void ActivateDARK_BLADE_THE_DRAGON_KNIGHTEffect(void);
unsigned char CanActivateDARK_GREPHER(void);
void ActivateDARK_GREPHEREffect(void);
unsigned char CanActivateDARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT(void);
void ActivateDARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHTEffect(void);
unsigned char CanActivateDARK_MAGICIAN_THE_DRAGON_KNIGHT(void);
void ActivateDARK_MAGICIAN_THE_DRAGON_KNIGHTEffect(void);
unsigned char CanActivateDARKNESS_NEOSPHERE(void);
void ActivateDARKNESS_NEOSPHEREEffect(void);
unsigned char CanActivateDECOY_DRAGON(void);
void ActivateDECOY_DRAGONEffect(void);
unsigned char CanActivateDESPAIR_FROM_THE_DARK(void);
void ActivateDESPAIR_FROM_THE_DARKEffect(void);
unsigned char CanActivateDESTINY_END_DRAGOON(void);
void ActivateDESTINY_END_DRAGOONEffect(void);
unsigned char CanActivateDIVINE_SERPENT_GEH(void);
void ActivateDIVINE_SERPENT_GEHEffect(void);
unsigned char CanActivateDON_ZALOOG(void);
void ActivateDON_ZALOOGEffect(void);
unsigned char CanActivateDOOM_VIRUS_DRAGON(void);
void ActivateDOOM_VIRUS_DRAGONEffect(void);
unsigned char CanActivateEGYPTIAN_GOD_SLIME(void);
void ActivateEGYPTIAN_GOD_SLIMEEffect(void);
unsigned char CanActivateELEMENTAL_HERO_NEOS_KLUGER(void);
void ActivateELEMENTAL_HERO_NEOS_KLUGEREffect(void);
unsigned char CanActivateFELGRAND_DRAGON(void);
void ActivateFELGRAND_DRAGONEffect(void);
unsigned char CanActivateGATE_GUARDIANS_COMBINED(void);
void ActivateGATE_GUARDIANS_COMBINEDEffect(void);
unsigned char CanActivateGODDESS_BOW(void);
void ActivateGODDESS_BOWEffect(void);
unsigned char CanActivateGORZ_THE_EMISSARY_OF_DARKNESS(void);
void ActivateGORZ_THE_EMISSARY_OF_DARKNESSEffect(void);
unsigned char CanActivateGRANMARG_THE_ROCK_MONARCH(void);
void ActivateGRANMARG_THE_ROCK_MONARCHEffect(void);
unsigned char CanActivateGREEN_GADGET(void);
void ActivateGREEN_GADGETEffect(void);
unsigned char CanActivateGUARDIAN_DREADSCYTHE(void);
void ActivateGUARDIAN_DREADSCYTHEEffect(void);
unsigned char CanActivateGUARDIAN_EATOS(void);
void ActivateGUARDIAN_EATOSEffect(void);
unsigned char CanActivateHERALD_OF_CREATION(void);
void ActivateHERALD_OF_CREATIONEffect(void);
unsigned char CanActivateHOLACTIE_THE_CREATOR_OF_LIGHT(void);
void ActivateHOLACTIE_THE_CREATOR_OF_LIGHTEffect(void);
unsigned char CanActivateJOWGEN_THE_SPIRITUALIST(void);
void ActivateJOWGEN_THE_SPIRITUALISTEffect(void);
unsigned char CanActivateJUDGMENT_DRAGON(void);
void ActivateJUDGMENT_DRAGONEffect(void);
unsigned char CanActivateKING_DRAGUN(void);
void ActivateKING_DRAGUNEffect(void);
unsigned char CanActivateKING_OF_THE_SWAMP(void);
void ActivateKING_OF_THE_SWAMPEffect(void);
unsigned char CanActivateKING_TIGER_WANGHU(void);
void ActivateKING_TIGER_WANGHUEffect(void);
unsigned char CanActivateKURAZ_THE_LIGHT_MONARCH(void);
void ActivateKURAZ_THE_LIGHT_MONARCHEffect(void);
unsigned char CanActivateKURIBANDIT(void);
void ActivateKURIBANDITEffect(void);
unsigned char CanActivateLEGENDARY_FLAME_LORD(void);
void ActivateLEGENDARY_FLAME_LORDEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_CRITIAS(void);
void ActivateLEGENDARY_KNIGHT_CRITIASEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_HERMOS(void);
void ActivateLEGENDARY_KNIGHT_HERMOSEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_TIMAEUS(void);
void ActivateLEGENDARY_KNIGHT_TIMAEUSEffect(void);
unsigned char CanActivateLEKUNGA(void);
void ActivateLEKUNGAEffect(void);
unsigned char CanActivateLIGHT_AND_DARKNESS_DRAGON(void);
void ActivateLIGHT_AND_DARKNESS_DRAGONEffect(void);
unsigned char CanActivateLORD_OF_THE_RED(void);
void ActivateLORD_OF_THE_REDEffect(void);
unsigned char CanActivateMAGICAL_PLANT_MANDRAGOLA(void);
void ActivateMAGICAL_PLANT_MANDRAGOLAEffect(void);
unsigned char CanActivateMAGICAL_SCIENTIST(void);
void ActivateMAGICAL_SCIENTISTEffect(void);
unsigned char CanActivateMANJU_OF_THE_TEN_THOUSAND_HANDS(void);
void ActivateMANJU_OF_THE_TEN_THOUSAND_HANDSEffect(void);
unsigned char CanActivateMARSHMALLON(void);
void ActivateMARSHMALLONEffect(void);
unsigned char CanActivateMAZERA_DEVILLE(void);
void ActivateMAZERA_DEVILLEEffect(void);
unsigned char CanActivateMIRROR_FORCE_DRAGON(void);
void ActivateMIRROR_FORCE_DRAGONEffect(void);
unsigned char CanActivateMOISTURE_CREATURE(void);
void ActivateMOISTURE_CREATUREEffect(void);
unsigned char CanActivateMOLTEN_ZOMBIE(void);
void ActivateMOLTEN_ZOMBIEEffect(void);
unsigned char CanActivateMUCUS_YOLK(void);
void ActivateMUCUS_YOLKEffect(void);
unsigned char CanActivateNEOS_WISEMAN(void);
void ActivateNEOS_WISEMANEffect(void);
unsigned char CanActivateOJAMA_KING(void);
void ActivateOJAMA_KINGEffect(void);
unsigned char CanActivateORICHALCOS_SHUNOROS(void);
void ActivateORICHALCOS_SHUNOROSEffect(void);
unsigned char CanActivateQUINTET_MAGICIAN(void);
void ActivateQUINTET_MAGICIANEffect(void);
unsigned char CanActivateRED_GADGET(void);
void ActivateRED_GADGETEffect(void);
unsigned char CanActivateROCKET_HERMOS_CANNON(void);
void ActivateROCKET_HERMOS_CANNONEffect(void);
unsigned char CanActivateROYAL_MAGICAL_LIBRARY(void);
void ActivateROYAL_MAGICAL_LIBRARYEffect(void);
unsigned char CanActivateSKILLED_DARK_MAGICIAN(void);
void ActivateSKILLED_DARK_MAGICIANEffect(void);
unsigned char CanActivateSKILLED_WHITE_MAGICIAN(void);
void ActivateSKILLED_WHITE_MAGICIANEffect(void);
unsigned char CanActivateSPHINX_TELEIA(void);
void ActivateSPHINX_TELEIAEffect(void);
unsigned char CanActivateSUMMONER_MONK(void);
void ActivateSUMMONER_MONKEffect(void);
unsigned char CanActivateSUMMONER_OF_ILLUSIONS(void);
void ActivateSUMMONER_OF_ILLUSIONSEffect(void);
unsigned char CanActivateTHE_CREATOR_INCARNATE(void);
void ActivateTHE_CREATOR_INCARNATEEffect(void);
unsigned char CanActivateTHE_LEGENDARY_EXODIA_INCARNATE(void);
void ActivateTHE_LEGENDARY_EXODIA_INCARNATEEffect(void);
unsigned char CanActivateTHEINEN_THE_GREAT_SPHINX(void);
void ActivateTHEINEN_THE_GREAT_SPHINXEffect(void);
unsigned char CanActivateTHESTALOS_THE_FIRESTORM_MONARCH(void);
void ActivateTHESTALOS_THE_FIRESTORM_MONARCHEffect(void);
unsigned char CanActivateTHUNDER_DRAGON_COLOSSUS(void);
void ActivateTHUNDER_DRAGON_COLOSSUSEffect(void);
unsigned char CanActivateTHUNDER_DRAGON_TITAN(void);
void ActivateTHUNDER_DRAGON_TITANEffect(void);
unsigned char CanActivateTIMAEUS_THE_KNIGHT_OF_DESTINY(void);
void ActivateTIMAEUS_THE_KNIGHT_OF_DESTINYEffect(void);
unsigned char CanActivateTIME_MAGIC_HAMMER(void);
void ActivateTIME_MAGIC_HAMMEREffect(void);
unsigned char CanActivateTORNADO_BIRD(void);
void ActivateTORNADO_BIRDEffect(void);
unsigned char CanActivateTYRANT_BURST_DRAGON(void);
void ActivateTYRANT_BURST_DRAGONEffect(void);
unsigned char CanActivateULTIMATE_CONDUCTOR_TYRANNO(void);
void ActivateULTIMATE_CONDUCTOR_TYRANNOEffect(void);
unsigned char CanActivateULTIMATE_OBEDIENT_FIEND(void);
void ActivateULTIMATE_OBEDIENT_FIENDEffect(void);
unsigned char CanActivateVISION_HERO_ADORATION(void);
void ActivateVISION_HERO_ADORATIONEffect(void);
unsigned char CanActivateVISION_HERO_FARIS(void);
void ActivateVISION_HERO_FARISEffect(void);
unsigned char CanActivateVISION_HERO_GRAVITO(void);
void ActivateVISION_HERO_GRAVITOEffect(void);
unsigned char CanActivateVISION_HERO_INCREASE(void);
void ActivateVISION_HERO_INCREASEEffect(void);
unsigned char CanActivateVISION_HERO_MINIMUM_RAY(void);
void ActivateVISION_HERO_MINIMUM_RAYEffect(void);
unsigned char CanActivateVISION_HERO_MULTIPLY_GUY(void);
void ActivateVISION_HERO_MULTIPLY_GUYEffect(void);
unsigned char CanActivateVISION_HERO_POISONER(void);
void ActivateVISION_HERO_POISONEREffect(void);
unsigned char CanActivateVISION_HERO_VYON(void);
void ActivateVISION_HERO_VYONEffect(void);
unsigned char CanActivateVISION_HERO_WITCH_RAIDER(void);
void ActivateVISION_HERO_WITCH_RAIDEREffect(void);
unsigned char CanActivateWATAPON(void);
void ActivateWATAPONEffect(void);
unsigned char CanActivateYELLOW_GADGET(void);
void ActivateYELLOW_GADGETEffect(void);
unsigned char CanActivateDESTINY_HERO_BLADE_MASTER(void);
void ActivateDESTINY_HERO_BLADE_MASTEREffect(void);
unsigned char CanActivateDESTINY_HERO_CAPTAIN_TENACIOUS(void);
void ActivateDESTINY_HERO_CAPTAIN_TENACIOUSEffect(void);
unsigned char CanActivateDESTINY_HERO_CELESTIAL(void);
void ActivateDESTINY_HERO_CELESTIALEffect(void);
unsigned char CanActivateDESTINY_HERO_DANGEROUS(void);
void ActivateDESTINY_HERO_DANGEROUSEffect(void);
unsigned char CanActivateDESTINY_HERO_DARK_ANGEL(void);
void ActivateDESTINY_HERO_DARK_ANGELEffect(void);
unsigned char CanActivateDESTINY_HERO_DASHER(void);
void ActivateDESTINY_HERO_DASHEREffect(void);
unsigned char CanActivateDESTINY_HERO_DECIDER(void);
void ActivateDESTINY_HERO_DECIDEREffect(void);
unsigned char CanActivateDESTINY_HERO_DEFENDER(void);
void ActivateDESTINY_HERO_DEFENDEREffect(void);
unsigned char CanActivateDESTINY_HERO_DENIER(void);
void ActivateDESTINY_HERO_DENIEREffect(void);
unsigned char CanActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCER(void);
void ActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCEREffect(void);
unsigned char CanActivateDESTINY_HERO_DIAMOND_DUDE(void);
void ActivateDESTINY_HERO_DIAMOND_DUDEEffect(void);
unsigned char CanActivateDESTINY_HERO_DISK_COMMANDER(void);
void ActivateDESTINY_HERO_DISK_COMMANDEREffect(void);
unsigned char CanActivateDESTINY_HERO_DOGMA(void);
void ActivateDESTINY_HERO_DOGMAEffect(void);
unsigned char CanActivateDESTINY_HERO_DOMINANCE(void);
void ActivateDESTINY_HERO_DOMINANCEEffect(void);
unsigned char CanActivateDESTINY_HERO_DOOM_LORD(void);
void ActivateDESTINY_HERO_DOOM_LORDEffect(void);
unsigned char CanActivateDESTINY_HERO_DOOM_OVERLORD(void);
void ActivateDESTINY_HERO_DOOM_OVERLORDEffect(void);
unsigned char CanActivateDESTINY_HERO_DOUBLE_DUDE(void);
void ActivateDESTINY_HERO_DOUBLE_DUDEEffect(void);
unsigned char CanActivateDESTINY_HERO_DRAWHAND(void);
void ActivateDESTINY_HERO_DRAWHANDEffect(void);
unsigned char CanActivateDESTINY_HERO_DREAD_SERVANT(void);
void ActivateDESTINY_HERO_DREAD_SERVANTEffect(void);
unsigned char CanActivateDESTINY_HERO_DREADMASTER(void);
void ActivateDESTINY_HERO_DREADMASTEREffect(void);
unsigned char CanActivateDESTINY_HERO_DREADNOUGHT_MASTER(void);
void ActivateDESTINY_HERO_DREADNOUGHT_MASTEREffect(void);
unsigned char CanActivateDESTINY_HERO_DREADNOUGHT_SERVANT(void);
void ActivateDESTINY_HERO_DREADNOUGHT_SERVANTEffect(void);
unsigned char CanActivateDESTINY_HERO_DREAMER(void);
void ActivateDESTINY_HERO_DREAMEREffect(void);
unsigned char CanActivateDESTINY_HERO_DRILLDARK(void);
void ActivateDESTINY_HERO_DRILLDARKEffect(void);
unsigned char CanActivateDESTINY_HERO_DUNKER(void);
void ActivateDESTINY_HERO_DUNKEREffect(void);
unsigned char CanActivateDESTINY_HERO_DUSKTOPIA(void);
void ActivateDESTINY_HERO_DUSKTOPIAEffect(void);
unsigned char CanActivateDESTINY_HERO_DYNATAG(void);
void ActivateDESTINY_HERO_DYNATAGEffect(void);
unsigned char CanActivateDESTINY_HERO_DYSTOPIA(void);
void ActivateDESTINY_HERO_DYSTOPIAEffect(void);
unsigned char CanActivateDESTINY_HERO_FEAR_MONGER(void);
void ActivateDESTINY_HERO_FEAR_MONGEREffect(void);
unsigned char CanActivateDESTINY_HERO_MALICIOUS(void);
void ActivateDESTINY_HERO_MALICIOUSEffect(void);
unsigned char CanActivateDESTINY_HERO_PLASMA(void);
void ActivateDESTINY_HERO_PLASMAEffect(void);
unsigned char CanActivateD_D_WARRIOR(void);
void ActivateD_D_WARRIOREffect(void);
unsigned char CanActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON(void);
void ActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGONEffect(void);
unsigned char CanActivateEXODIUS_THE_ULTIMATE_FORBIDDEN_LORD(void);
void ActivateEXODIUS_THE_ULTIMATE_FORBIDDEN_LORDEffect(void);
unsigned char CanActivateMAJESTIC_MECH_GORYU(void);
void ActivateMAJESTIC_MECH_GORYUEffect(void);
unsigned char CanActivateNEO_BLUE_EYES_ULTIMATE_DRAGON(void);
void ActivateNEO_BLUE_EYES_ULTIMATE_DRAGONEffect(void);
unsigned char CanActivateRED_EYES_BLACK_DRAGON_SWORD(void);
void ActivateRED_EYES_BLACK_DRAGON_SWORDEffect(void);
unsigned char CanActivateRED_EYES_DARK_DRAGOON(void);
void ActivateRED_EYES_DARK_DRAGOONEffect(void);
unsigned char CanActivateRED_EYES_DARKNESS_METAL_DRAGON(void);
void ActivateRED_EYES_DARKNESS_METAL_DRAGONEffect(void);
unsigned char CanActivateTHE_AGENT_OF_JUDGMENT_SATURN(void);
void ActivateTHE_AGENT_OF_JUDGMENT_SATURNEffect(void);
unsigned char CanActivateARMED_DRAGON_LEVEL_FIVE(void);
void ActivateARMED_DRAGON_LEVEL_FIVEEffect(void);
unsigned char CanActivateARMED_DRAGON_LEVEL_SEVEN(void);
void ActivateARMED_DRAGON_LEVEL_SEVENEffect(void);
unsigned char CanActivateARMED_DRAGON_LEVEL_TEN(void);
void ActivateARMED_DRAGON_LEVEL_TENEffect(void);
unsigned char CanActivateARMED_DRAGON_LEVEL_THREE(void);
void ActivateARMED_DRAGON_LEVEL_THREEEffect(void);
unsigned char CanActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHT(void);
void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHTEffect(void);
unsigned char CanActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUR(void);
void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUREffect(void);
unsigned char CanActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIX(void);
void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIXEffect(void);
unsigned char CanActivateMAN_THRO_THRO(void);
void ActivateMAN_THRO_THROEffect(void);
unsigned char CanActivateMASTER_PEACE_THE_TRUE_DRACROSLAYING_KING(void);
void ActivateMASTER_PEACE_THE_TRUE_DRACROSLAYING_KINGEffect(void);
unsigned char CanActivateNIBIRU_THE_PRIMAL_BEING(void);
void ActivateNIBIRU_THE_PRIMAL_BEINGEffect(void);
unsigned char CanActivateWOUGHTWEILER(void);
void ActivateWOUGHTWEILEREffect(void);
unsigned char CanActivateMA_AT(void);
void ActivateMA_ATEffect(void);

void CanActivateCustomMonsterEffects(void)
{

    if (gMonEffect.id == AMULET_DRAGON) {
      ActivateAMULET_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == ANDRO_SPHINX) {
      ActivateANDRO_SPHINXEffect();
      return;
    }
    if (gMonEffect.id == APPRENTICE_ILLUSION_MAGICIAN) {
      ActivateAPPRENTICE_ILLUSION_MAGICIANEffect();
      return;
    }
    if (gMonEffect.id == ARMAGEDDON_KNIGHT) {
      ActivateARMAGEDDON_KNIGHTEffect();
      return;
    }
    if (gMonEffect.id == BIRDFACE) {
      ActivateBIRDFACEEffect();
      return;
    }
    if (gMonEffect.id == CANNONBALL_SPEAR_SHELLFISH) {
      ActivateCANNONBALL_SPEAR_SHELLFISHEffect();
      return;
    }
    if (gMonEffect.id == CHIMERATECH_FORTRESS_DRAGON) {
      ActivateCHIMERATECH_FORTRESS_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == CHIMERATECH_MEGAFLEET_DRAGON) {
      ActivateCHIMERATECH_MEGAFLEET_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == CHIMERATECH_RAMPAGE_DRAGON) {
      ActivateCHIMERATECH_RAMPAGE_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == CYBER_ELTANIN) {
      ActivateCYBER_ELTANINEffect();
      return;
    }
    if (gMonEffect.id == CYBER_KIRIN) {
      ActivateCYBER_KIRINEffect();
      return;
    }
    if (gMonEffect.id == CYBER_PHOENIX) {
      ActivateCYBER_PHOENIXEffect();
      return;
    }
    if (gMonEffect.id == CYBER_VALLEY) {
      ActivateCYBER_VALLEYEffect();
      return;
    }
    if (gMonEffect.id == DARK_BLADE_THE_DRAGON_KNIGHT) {
      ActivateDARK_BLADE_THE_DRAGON_KNIGHTEffect();
      return;
    }
    if (gMonEffect.id == DARK_GREPHER) {
      ActivateDARK_GREPHEREffect();
      return;
    }
    if (gMonEffect.id == DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT) {
      ActivateDARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHTEffect();
      return;
    }
    if (gMonEffect.id == DARK_MAGICIAN_THE_DRAGON_KNIGHT) {
      ActivateDARK_MAGICIAN_THE_DRAGON_KNIGHTEffect();
      return;
    }
    if (gMonEffect.id == DARKNESS_NEOSPHERE) {
      ActivateDARKNESS_NEOSPHEREEffect();
      return;
    }
    if (gMonEffect.id == DECOY_DRAGON) {
      ActivateDECOY_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == DESPAIR_FROM_THE_DARK) {
      ActivateDESPAIR_FROM_THE_DARKEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_END_DRAGOON) {
      ActivateDESTINY_END_DRAGOONEffect();
      return;
    }
    if (gMonEffect.id == DIVINE_SERPENT_GEH) {
      ActivateDIVINE_SERPENT_GEHEffect();
      return;
    }
    if (gMonEffect.id == DON_ZALOOG) {
      ActivateDON_ZALOOGEffect();
      return;
    }
    if (gMonEffect.id == DOOM_VIRUS_DRAGON) {
      ActivateDOOM_VIRUS_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == EGYPTIAN_GOD_SLIME) {
      ActivateEGYPTIAN_GOD_SLIMEEffect();
      return;
    }
    if (gMonEffect.id == ELEMENTAL_HERO_NEOS_KLUGER) {
      ActivateELEMENTAL_HERO_NEOS_KLUGEREffect();
      return;
    }
    if (gMonEffect.id == FELGRAND_DRAGON) {
      ActivateFELGRAND_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == GATE_GUARDIANS_COMBINED) {
      ActivateGATE_GUARDIANS_COMBINEDEffect();
      return;
    }
    if (gMonEffect.id == GODDESS_BOW) {
      ActivateGODDESS_BOWEffect();
      return;
    }
    if (gMonEffect.id == GORZ_THE_EMISSARY_OF_DARKNESS) {
      ActivateGORZ_THE_EMISSARY_OF_DARKNESSEffect();
      return;
    }
    if (gMonEffect.id == GRANMARG_THE_ROCK_MONARCH) {
      ActivateGRANMARG_THE_ROCK_MONARCHEffect();
      return;
    }
    if (gMonEffect.id == GREEN_GADGET) {
      ActivateGREEN_GADGETEffect();
      return;
    }
    if (gMonEffect.id == GUARDIAN_DREADSCYTHE) {
      ActivateGUARDIAN_DREADSCYTHEEffect();
      return;
    }
    if (gMonEffect.id == GUARDIAN_EATOS) {
      ActivateGUARDIAN_EATOSEffect();
      return;
    }
    if (gMonEffect.id == HERALD_OF_CREATION) {
      ActivateHERALD_OF_CREATIONEffect();
      return;
    }
    if (gMonEffect.id == HOLACTIE_THE_CREATOR_OF_LIGHT) {
      ActivateHOLACTIE_THE_CREATOR_OF_LIGHTEffect();
      return;
    }
    if (gMonEffect.id == JOWGEN_THE_SPIRITUALIST) {
      ActivateJOWGEN_THE_SPIRITUALISTEffect();
      return;
    }
    if (gMonEffect.id == JUDGMENT_DRAGON) {
      ActivateJUDGMENT_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == KING_DRAGUN) {
      ActivateKING_DRAGUNEffect();
      return;
    }
    if (gMonEffect.id == KING_OF_THE_SWAMP) {
      ActivateKING_OF_THE_SWAMPEffect();
      return;
    }
    if (gMonEffect.id == KING_TIGER_WANGHU) {
      ActivateKING_TIGER_WANGHUEffect();
      return;
    }
    if (gMonEffect.id == KURAZ_THE_LIGHT_MONARCH) {
      ActivateKURAZ_THE_LIGHT_MONARCHEffect();
      return;
    }
    if (gMonEffect.id == KURIBANDIT) {
      ActivateKURIBANDITEffect();
      return;
    }
    if (gMonEffect.id == LEGENDARY_FLAME_LORD) {
      ActivateLEGENDARY_FLAME_LORDEffect();
      return;
    }
    if (gMonEffect.id == LEGENDARY_KNIGHT_CRITIAS) {
      ActivateLEGENDARY_KNIGHT_CRITIASEffect();
      return;
    }
    if (gMonEffect.id == LEGENDARY_KNIGHT_HERMOS) {
      ActivateLEGENDARY_KNIGHT_HERMOSEffect();
      return;
    }
    if (gMonEffect.id == LEGENDARY_KNIGHT_TIMAEUS) {
      ActivateLEGENDARY_KNIGHT_TIMAEUSEffect();
      return;
    }
    if (gMonEffect.id == LEKUNGA) {
      ActivateLEKUNGAEffect();
      return;
    }
    if (gMonEffect.id == LIGHT_AND_DARKNESS_DRAGON) {
      ActivateLIGHT_AND_DARKNESS_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == LORD_OF_THE_RED) {
      ActivateLORD_OF_THE_REDEffect();
      return;
    }
    if (gMonEffect.id == MAGICAL_PLANT_MANDRAGOLA) {
      ActivateMAGICAL_PLANT_MANDRAGOLAEffect();
      return;
    }
    if (gMonEffect.id == MAGICAL_SCIENTIST) {
      ActivateMAGICAL_SCIENTISTEffect();
      return;
    }
    if (gMonEffect.id == MANJU_OF_THE_TEN_THOUSAND_HANDS) {
      ActivateMANJU_OF_THE_TEN_THOUSAND_HANDSEffect();
      return;
    }
    if (gMonEffect.id == MARSHMALLON) {
      ActivateMARSHMALLONEffect();
      return;
    }
    if (gMonEffect.id == MAZERA_DEVILLE) {
      ActivateMAZERA_DEVILLEEffect();
      return;
    }
    if (gMonEffect.id == MIRROR_FORCE_DRAGON) {
      ActivateMIRROR_FORCE_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == MOISTURE_CREATURE) {
      ActivateMOISTURE_CREATUREEffect();
      return;
    }
    if (gMonEffect.id == MOLTEN_ZOMBIE) {
      ActivateMOLTEN_ZOMBIEEffect();
      return;
    }
    if (gMonEffect.id == MUCUS_YOLK) {
      ActivateMUCUS_YOLKEffect();
      return;
    }
    if (gMonEffect.id == NEOS_WISEMAN) {
      ActivateNEOS_WISEMANEffect();
      return;
    }
    if (gMonEffect.id == OJAMA_KING) {
      ActivateOJAMA_KINGEffect();
      return;
    }
    if (gMonEffect.id == ORICHALCOS_SHUNOROS) {
      ActivateORICHALCOS_SHUNOROSEffect();
      return;
    }
    if (gMonEffect.id == QUINTET_MAGICIAN) {
      ActivateQUINTET_MAGICIANEffect();
      return;
    }
    if (gMonEffect.id == RED_GADGET) {
      ActivateRED_GADGETEffect();
      return;
    }
    if (gMonEffect.id == ROCKET_HERMOS_CANNON) {
      ActivateROCKET_HERMOS_CANNONEffect();
      return;
    }
    if (gMonEffect.id == ROYAL_MAGICAL_LIBRARY) {
      ActivateROYAL_MAGICAL_LIBRARYEffect();
      return;
    }
    if (gMonEffect.id == SKILLED_DARK_MAGICIAN) {
      ActivateSKILLED_DARK_MAGICIANEffect();
      return;
    }
    if (gMonEffect.id == SKILLED_WHITE_MAGICIAN) {
      ActivateSKILLED_WHITE_MAGICIANEffect();
      return;
    }
    if (gMonEffect.id == SPHINX_TELEIA) {
      ActivateSPHINX_TELEIAEffect();
      return;
    }
    if (gMonEffect.id == SUMMONER_MONK) {
      ActivateSUMMONER_MONKEffect();
      return;
    }
    if (gMonEffect.id == SUMMONER_OF_ILLUSIONS) {
      ActivateSUMMONER_OF_ILLUSIONSEffect();
      return;
    }
    if (gMonEffect.id == THE_CREATOR_INCARNATE) {
      ActivateTHE_CREATOR_INCARNATEEffect();
      return;
    }
    if (gMonEffect.id == THE_LEGENDARY_EXODIA_INCARNATE) {
      ActivateTHE_LEGENDARY_EXODIA_INCARNATEEffect();
      return;
    }
    if (gMonEffect.id == THEINEN_THE_GREAT_SPHINX) {
      ActivateTHEINEN_THE_GREAT_SPHINXEffect();
      return;
    }
    if (gMonEffect.id == THESTALOS_THE_FIRESTORM_MONARCH) {
      ActivateTHESTALOS_THE_FIRESTORM_MONARCHEffect();
      return;
    }
    if (gMonEffect.id == THUNDER_DRAGON_COLOSSUS) {
      ActivateTHUNDER_DRAGON_COLOSSUSEffect();
      return;
    }
    if (gMonEffect.id == THUNDER_DRAGON_TITAN) {
      ActivateTHUNDER_DRAGON_TITANEffect();
      return;
    }
    if (gMonEffect.id == TIMAEUS_THE_KNIGHT_OF_DESTINY) {
      ActivateTIMAEUS_THE_KNIGHT_OF_DESTINYEffect();
      return;
    }
    if (gMonEffect.id == TIME_MAGIC_HAMMER) {
      ActivateTIME_MAGIC_HAMMEREffect();
      return;
    }
    if (gMonEffect.id == TORNADO_BIRD) {
      ActivateTORNADO_BIRDEffect();
      return;
    }
    if (gMonEffect.id == TYRANT_BURST_DRAGON) {
      ActivateTYRANT_BURST_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == ULTIMATE_CONDUCTOR_TYRANNO) {
      ActivateULTIMATE_CONDUCTOR_TYRANNOEffect();
      return;
    }
    if (gMonEffect.id == ULTIMATE_OBEDIENT_FIEND) {
      ActivateULTIMATE_OBEDIENT_FIENDEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_ADORATION) {
      ActivateVISION_HERO_ADORATIONEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_FARIS) {
      ActivateVISION_HERO_FARISEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_GRAVITO) {
      ActivateVISION_HERO_GRAVITOEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_INCREASE) {
      ActivateVISION_HERO_INCREASEEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_MINIMUM_RAY) {
      ActivateVISION_HERO_MINIMUM_RAYEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_MULTIPLY_GUY) {
      ActivateVISION_HERO_MULTIPLY_GUYEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_POISONER) {
      ActivateVISION_HERO_POISONEREffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_VYON) {
      ActivateVISION_HERO_VYONEffect();
      return;
    }
    if (gMonEffect.id == VISION_HERO_WITCH_RAIDER) {
      ActivateVISION_HERO_WITCH_RAIDEREffect();
      return;
    }
    if (gMonEffect.id == WATAPON) {
      ActivateWATAPONEffect();
      return;
    }
    if (gMonEffect.id == YELLOW_GADGET) {
      ActivateYELLOW_GADGETEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_BLADE_MASTER) {
      ActivateDESTINY_HERO_BLADE_MASTEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_CAPTAIN_TENACIOUS) {
      ActivateDESTINY_HERO_CAPTAIN_TENACIOUSEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_CELESTIAL) {
      ActivateDESTINY_HERO_CELESTIALEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DANGEROUS) {
      ActivateDESTINY_HERO_DANGEROUSEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DARK_ANGEL) {
      ActivateDESTINY_HERO_DARK_ANGELEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DASHER) {
      ActivateDESTINY_HERO_DASHEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DECIDER) {
      ActivateDESTINY_HERO_DECIDEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DEFENDER) {
      ActivateDESTINY_HERO_DEFENDEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DENIER) {
      ActivateDESTINY_HERO_DENIEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER) {
      ActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DIAMOND_DUDE) {
      ActivateDESTINY_HERO_DIAMOND_DUDEEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DISK_COMMANDER) {
      ActivateDESTINY_HERO_DISK_COMMANDEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DOGMA) {
      ActivateDESTINY_HERO_DOGMAEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DOMINANCE) {
      ActivateDESTINY_HERO_DOMINANCEEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DOOM_LORD) {
      ActivateDESTINY_HERO_DOOM_LORDEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DOOM_OVERLORD) {
      ActivateDESTINY_HERO_DOOM_OVERLORDEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DOUBLE_DUDE) {
      ActivateDESTINY_HERO_DOUBLE_DUDEEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DRAWHAND) {
      ActivateDESTINY_HERO_DRAWHANDEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DREAD_SERVANT) {
      ActivateDESTINY_HERO_DREAD_SERVANTEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DREADMASTER) {
      ActivateDESTINY_HERO_DREADMASTEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DREADNOUGHT_MASTER) {
      ActivateDESTINY_HERO_DREADNOUGHT_MASTEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DREADNOUGHT_SERVANT) {
      ActivateDESTINY_HERO_DREADNOUGHT_SERVANTEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DREAMER) {
      ActivateDESTINY_HERO_DREAMEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DRILLDARK) {
      ActivateDESTINY_HERO_DRILLDARKEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DUNKER) {
      ActivateDESTINY_HERO_DUNKEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DUSKTOPIA) {
      ActivateDESTINY_HERO_DUSKTOPIAEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DYNATAG) {
      ActivateDESTINY_HERO_DYNATAGEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_DYSTOPIA) {
      ActivateDESTINY_HERO_DYSTOPIAEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_FEAR_MONGER) {
      ActivateDESTINY_HERO_FEAR_MONGEREffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_MALICIOUS) {
      ActivateDESTINY_HERO_MALICIOUSEffect();
      return;
    }
    if (gMonEffect.id == DESTINY_HERO_PLASMA) {
      ActivateDESTINY_HERO_PLASMAEffect();
      return;
    }
    if (gMonEffect.id == D_D_WARRIOR) {
      ActivateD_D_WARRIOREffect();
      return;
    }
    if (gMonEffect.id == BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON) {
      ActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == EXODIUS_THE_ULTIMATE_FORBIDDEN_LORD) {
      ActivateEXODIUS_THE_ULTIMATE_FORBIDDEN_LORDEffect();
      return;
    }
    if (gMonEffect.id == MAJESTIC_MECH_GORYU) {
      ActivateMAJESTIC_MECH_GORYUEffect();
      return;
    }
    if (gMonEffect.id == NEO_BLUE_EYES_ULTIMATE_DRAGON) {
      ActivateNEO_BLUE_EYES_ULTIMATE_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == RED_EYES_BLACK_DRAGON_SWORD) {
      ActivateRED_EYES_BLACK_DRAGON_SWORDEffect();
      return;
    }
    if (gMonEffect.id == RED_EYES_DARK_DRAGOON) {
      ActivateRED_EYES_DARK_DRAGOONEffect();
      return;
    }
    if (gMonEffect.id == RED_EYES_DARKNESS_METAL_DRAGON) {
      ActivateRED_EYES_DARKNESS_METAL_DRAGONEffect();
      return;
    }
    if (gMonEffect.id == THE_AGENT_OF_JUDGMENT_SATURN) {
      ActivateTHE_AGENT_OF_JUDGMENT_SATURNEffect();
      return;
    }
    if (gMonEffect.id == ARMED_DRAGON_LEVEL_FIVE) {
      ActivateARMED_DRAGON_LEVEL_FIVEEffect();
      return;
    }
    if (gMonEffect.id == ARMED_DRAGON_LEVEL_SEVEN) {
      ActivateARMED_DRAGON_LEVEL_SEVENEffect();
      return;
    }
    if (gMonEffect.id == ARMED_DRAGON_LEVEL_TEN) {
      ActivateARMED_DRAGON_LEVEL_TENEffect();
      return;
    }
    if (gMonEffect.id == ARMED_DRAGON_LEVEL_THREE) {
      ActivateARMED_DRAGON_LEVEL_THREEEffect();
      return;
    }
    if (gMonEffect.id == HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHT) {
      ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_EIGHTEffect();
      return;
    }
    if (gMonEffect.id == HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUR) {
      ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_FOUREffect();
      return;
    }
    if (gMonEffect.id == HORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIX) {
      ActivateHORUS_THE_BLACK_FLAME_DRAGON_LEVEL_SIXEffect();
      return;
    }
    if (gMonEffect.id == MAN_THRO_THRO) {
      ActivateMAN_THRO_THROEffect();
      return;
    }
    if (gMonEffect.id == MASTER_PEACE_THE_TRUE_DRACROSLAYING_KING) {
      ActivateMASTER_PEACE_THE_TRUE_DRACROSLAYING_KINGEffect();
      return;
    }
    if (gMonEffect.id == NIBIRU_THE_PRIMAL_BEING) {
      ActivateNIBIRU_THE_PRIMAL_BEINGEffect();
      return;
    }
    if (gMonEffect.id == WOUGHTWEILER) {
      ActivateWOUGHTWEILEREffect();
      return;
    }
    if (gMonEffect.id == MA_AT) {
      ActivateMA_ATEffect();
      return;
    }

}
