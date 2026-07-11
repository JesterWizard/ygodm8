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
#include "amulet_dragon.h"
#include "andro_sphinx.h"
#include "apprentice_illusion_magician.h"
#include "armed_dragon_lv5.h"
#include "armed_dragon_lv7.h"
#include "armed_dragon_lv10.h"
#include "uria_lord_of_searing_flames.h"
#include "raviel_lord_of_phantasms.h"

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
unsigned char CanActivateURIA_LORD_OF_SEARING_FLAMES(void);
void ActivateURIA_LORD_OF_SEARING_FLAMESEffect(void);
unsigned char CanActivateRAVIEL_LORD_OF_PHANTASMS(void);
void ActivateRAVIEL_LORD_OF_PHANTASMSEffect(void);
unsigned char CanActivateBIRDFACE(void);
void ActivateBIRDFACEEffect(void);
unsigned char CanActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON(void);
void ActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGONEffect(void);
unsigned char CanActivateCHIMERATECH_FORTRESS_DRAGON(void);
void ActivateCHIMERATECH_FORTRESS_DRAGONEffect(void);
unsigned char CanActivateCHIMERATECH_MEGAFLEET_DRAGON(void);
void ActivateCHIMERATECH_MEGAFLEET_DRAGONEffect(void);
unsigned char CanActivateCHIMERATECH_RAMPAGE_DRAGON(void);
void ActivateCHIMERATECH_RAMPAGE_DRAGONEffect(void);
unsigned char CanActivateCYBER_ELTANIN(void);
void ActivateCYBER_ELTANINEffect(void);
unsigned char CanActivateCYBER_PHOENIX(void);
void ActivateCYBER_PHOENIXEffect(void);
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
      case MONSTER_EFFECT_URIA_LORD_OF_SEARING_FLAMES:
        canActivate = CanActivateURIA_LORD_OF_SEARING_FLAMES();
        break;
      case MONSTER_EFFECT_RAVIEL_LORD_OF_PHANTASMS:
        canActivate = CanActivateRAVIEL_LORD_OF_PHANTASMS();
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

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_URIA_LORD_OF_SEARING_FLAMES) {
    ActivateURIA_LORD_OF_SEARING_FLAMESEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_RAVIEL_LORD_OF_PHANTASMS) {
    ActivateRAVIEL_LORD_OF_PHANTASMSEffect();
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

  /* stub activated monster effect dispatches */
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
  if (gMonEffect.id == ARMED_DRAGON_LV5) {
    ActivateARMED_DRAGON_LV5Effect();
    return;
  }
  if (gMonEffect.id == ARMED_DRAGON_LV7) {
    ActivateARMED_DRAGON_LV7Effect();
    return;
  }
  if (gMonEffect.id == ARMED_DRAGON_LV10) {
    ActivateARMED_DRAGON_LV10Effect();
    return;
  }
  if (gMonEffect.id == BIRDFACE) {
    ActivateBIRDFACEEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON) {
    ActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGONEffect();
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
  if (gMonEffect.id == CYBER_PHOENIX) {
    ActivateCYBER_PHOENIXEffect();
    return;
  }
  if (gMonEffect.id == CYBER_VALLEY) {
    ActivateCYBER_VALLEYEffect();
    return;
  }
  if (gMonEffect.id == D_D_WARRIOR) {
    ActivateD_D_WARRIOREffect();
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
          || zone->id == AMULET_DRAGON
          || zone->id == ANDRO_SPHINX
          || zone->id == APPRENTICE_ILLUSION_MAGICIAN
          || zone->id == ARMED_DRAGON_LV5
          || zone->id == ARMED_DRAGON_LV7
          || zone->id == ARMED_DRAGON_LV10
          || zone->id == URIA_LORD_OF_SEARING_FLAMES
          || zone->id == RAVIEL_LORD_OF_PHANTASMS
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