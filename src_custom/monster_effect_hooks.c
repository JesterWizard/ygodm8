#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "configs/runtime.h"
#include "duel_helpers.h"
#include "synchro_duel.h"
#include "xyz_duel.h"
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
void ActivateMUCUS_YOLKEffect(void);
void ActivateNEO_BLUE_EYES_ULTIMATE_DRAGONEffect(void);
void ActivateNEOS_WISEMANEffect(void);
void ActivateNIBIRU_THE_PRIMAL_BEINGEffect(void);
void ActivateOJAMA_KINGEffect(void);
void ActivateORICHALCOS_SHUNOROSEffect(void);
unsigned char CanActivatePROTECTOR_OF_THE_SANCTUARY(void);
void ActivatePROTECTOR_OF_THE_SANCTUARYEffect(void);
unsigned char CanActivateQUINTET_MAGICIAN(void);
void ActivateQUINTET_MAGICIANEffect(void);
unsigned char CanActivateROYAL_MAGICAL_LIBRARY(void);
void ActivateROYAL_MAGICAL_LIBRARYEffect(void);
unsigned char CanActivateSKILLED_DARK_MAGICIAN(void);
void ActivateSKILLED_DARK_MAGICIANEffect(void);
unsigned char CanActivateSKILLED_WHITE_MAGICIAN(void);
void ActivateSKILLED_WHITE_MAGICIANEffect(void);
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
unsigned char CanActivateCYBER_VALLEY(void);
void ActivateCYBER_VALLEYEffect(void);
unsigned char CanActivateDARK_ARMED_DRAGON(void);
void ActivateDARK_ARMED_DRAGONEffect(void);
unsigned char CanActivateDECOY_DRAGON(void);
void ActivateDECOY_DRAGONEffect(void);
unsigned char CanActivateDESTINY_END_DRAGOON(void);
void ActivateDESTINY_END_DRAGOONEffect(void);
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
unsigned char CanActivateDESTINY_HERO_DENIER(void);
void ActivateDESTINY_HERO_DENIEREffect(void);
unsigned char CanActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCER(void);
void ActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCEREffect(void);
unsigned char CanActivateDESTINY_HERO_DIAMOND_DUDE(void);
void ActivateDESTINY_HERO_DIAMOND_DUDEEffect(void);
unsigned char CanActivateDESTINY_HERO_DISK_COMMANDER(void);
void ActivateDESTINY_HERO_DISK_COMMANDEREffect(void);
unsigned char CanActivateDESTINY_HERO_DOMINANCE(void);
void ActivateDESTINY_HERO_DOMINANCEEffect(void);
unsigned char CanActivateDESTINY_HERO_DOOM_LORD(void);
void ActivateDESTINY_HERO_DOOM_LORDEffect(void);
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
unsigned char CanActivateDESTINY_HERO_MALICIOUS(void);
void ActivateDESTINY_HERO_MALICIOUSEffect(void);
unsigned char CanActivateDESTINY_HERO_PLASMA(void);
void ActivateDESTINY_HERO_PLASMAEffect(void);
unsigned char CanActivateDIVINE_SERPENT_GEH(void);
void ActivateDIVINE_SERPENT_GEHEffect(void);
unsigned char CanActivateDESTINY_HERO_DESTROY_DOGMA(void);
void ActivateDESTINY_HERO_DESTROY_DOGMAEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_CRITIAS(void);
void ActivateLEGENDARY_KNIGHT_CRITIASEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_HERMOS(void);
void ActivateLEGENDARY_KNIGHT_HERMOSEffect(void);
unsigned char CanActivateLEGENDARY_KNIGHT_TIMAEUS(void);
void ActivateLEGENDARY_KNIGHT_TIMAEUSEffect(void);
unsigned char CanActivateLEKUNGA(void);
void ActivateLEKUNGAEffect(void);
unsigned char CanActivateLORD_OF_THE_RED(void);
void ActivateLORD_OF_THE_REDEffect(void);
unsigned char CanActivateMA_AT(void);
void ActivateMA_ATEffect(void);
unsigned char CanActivateMAGICAL_PLANT_MANDRAGOLA(void);
void ActivateMAGICAL_PLANT_MANDRAGOLAEffect(void);
unsigned char CanActivateMAGICAL_SCIENTIST(void);
void ActivateMAGICAL_SCIENTISTEffect(void);
unsigned char CanActivateMAJESTIC_MECH_GORYU(void);
void ActivateMAJESTIC_MECH_GORYUEffect(void);
unsigned char CanActivateMANJU_OF_THE_TEN_THOUSAND_HANDS(void);
void ActivateMANJU_OF_THE_TEN_THOUSAND_HANDSEffect(void);
unsigned char CanActivateMARSHMALLON(void);
void ActivateMARSHMALLONEffect(void);
unsigned char CanActivateMASTER_PEACE_THE_TRUE_DRACOSLAYING_KING(void);
void ActivateMASTER_PEACE_THE_TRUE_DRACOSLAYING_KINGEffect(void);
unsigned char CanActivateMAZERA_DEVILLE(void);
void ActivateMAZERA_DEVILLEEffect(void);
unsigned char CanActivateMIRROR_FORCE_DRAGON(void);
void ActivateMIRROR_FORCE_DRAGONEffect(void);
unsigned char CanActivateMOLTEN_ZOMBIE(void);
void ActivateMOLTEN_ZOMBIEEffect(void);
unsigned char CanActivateTHE_AGENT_OF_JUDGMENT_SATURN(void);
void ActivateTHE_AGENT_OF_JUDGMENT_SATURNEffect(void);
unsigned char CanActivateTHE_AGENT_OF_WISDOM_MERCURY(void);
void ActivateTHE_AGENT_OF_WISDOM_MERCURYEffect(void);
unsigned char CanActivateTHE_CREATOR(void);
void ActivateTHE_CREATOREffect(void);
unsigned char CanActivateTHE_CREATOR_INCARNATE(void);
void ActivateTHE_CREATOR_INCARNATEEffect(void);
unsigned char CanActivateTHE_LEGENDARY_EXODIA_INCARNATE(void);
void ActivateTHE_LEGENDARY_EXODIA_INCARNATEEffect(void);
unsigned char CanActivateTHEINEN_THE_GREAT_SPHINX(void);
void ActivateTHEINEN_THE_GREAT_SPHINXEffect(void);
unsigned char CanActivateTHESTALOS_THE_FIRESTORM_MONARCH(void);
void ActivateTHESTALOS_THE_FIRESTORM_MONARCHEffect(void);
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
unsigned char CanActivateARCANITE_MAGICIAN(void);
void ActivateARCANITE_MAGICIANEffect(void);
unsigned char CanActivateARMORY_ARM(void);
void ActivateARMORY_ARMEffect(void);
unsigned char CanActivateAROMA_JAR(void);
void ActivateAROMA_JAREffect(void);
unsigned char CanActivateAROMAGE_BERGAMOT(void);
void ActivateAROMAGE_BERGAMOTEffect(void);
unsigned char CanActivateAROMAGE_CANANGA(void);
void ActivateAROMAGE_CANANGAEffect(void);
unsigned char CanActivateAROMAGE_JASMINE(void);
void ActivateAROMAGE_JASMINEEffect(void);
unsigned char CanActivateAROMAGE_LAUREL(void);
void ActivateAROMAGE_LAURELEffect(void);
unsigned char CanActivateAROMAGE_MARJORAM(void);
void ActivateAROMAGE_MARJORAMEffect(void);
unsigned char CanActivateAROMAGE_ROSEMARY(void);
void ActivateAROMAGE_ROSEMARYEffect(void);
unsigned char CanActivateAROMALILITH_MAGNOLIA(void);
void ActivateAROMALILITH_MAGNOLIAEffect(void);
unsigned char CanActivateAROMALILITH_ROSALINA(void);
void ActivateAROMALILITH_ROSALINAEffect(void);
unsigned char CanActivateAROMALILITH_ROSEMARY(void);
void ActivateAROMALILITH_ROSEMARYEffect(void);
unsigned char CanActivateAROMASERAPHY_JASMINE(void);
void ActivateAROMASERAPHY_JASMINEEffect(void);
unsigned char CanActivateAROMASERAPHY_ROSEMARY(void);
void ActivateAROMASERAPHY_ROSEMARYEffect(void);
unsigned char CanActivateAROMASERAPHY_SWEET_MARJORAM(void);
void ActivateAROMASERAPHY_SWEET_MARJORAMEffect(void);
unsigned char CanActivateAZURE_EYES_SILVER_DRAGON(void);
void ActivateAZURE_EYES_SILVER_DRAGONEffect(void);
unsigned char CanActivateBLACK_ROSE_DRAGON(void);
void ActivateBLACK_ROSE_DRAGONEffect(void);
unsigned char CanActivateBLUE_EYES_JET_DRAGON(void);
void ActivateBLUE_EYES_JET_DRAGONEffect(void);
unsigned char CanActivateBLUE_EYES_SOLID_DRAGON(void);
void ActivateBLUE_EYES_SOLID_DRAGONEffect(void);
unsigned char CanActivateBLUE_EYES_TYRANT_DRAGON(void);
void ActivateBLUE_EYES_TYRANT_DRAGONEffect(void);
unsigned char CanActivateBLUE_EYES_ULTIMATE_SPIRIT_DRAGON(void);
void ActivateBLUE_EYES_ULTIMATE_SPIRIT_DRAGONEffect(void);
unsigned char CanActivateBLUE_EYES_SPIRIT_DRAGON(void);
void ActivateBLUE_EYES_SPIRIT_DRAGONEffect(void);
unsigned char CanActivateBRIONAC_DRAGON_OF_THE_ICE_BARRIER(void);
void ActivateBRIONAC_DRAGON_OF_THE_ICE_BARRIEREffect(void);
unsigned char CanActivateCOLOSSAL_FIGHTER(void);
void ActivateCOLOSSAL_FIGHTEREffect(void);
unsigned char CanActivateCYBER_SLASH_HARPIE_LADY(void);
void ActivateCYBER_SLASH_HARPIE_LADYEffect(void);
unsigned char CanActivateDARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE(void);
void ActivateDARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICEEffect(void);
unsigned char CanActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC(void);
void ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGICEffect(void);
unsigned char CanActivateDARK_STRIKE_FIGHTER(void);
void ActivateDARK_STRIKE_FIGHTEREffect(void);
unsigned char CanActivateEBON_ILLUSION_MAGICIAN(void);
void ActivateEBON_ILLUSION_MAGICIANEffect(void);
unsigned char CanActivateEL_SHADDOLL_MESHAHRAIL(void);
void ActivateEL_SHADDOLL_MESHAHRAILEffect(void);
unsigned char CanActivateEL_SHADDOLL_WENDIGO(void);
void ActivateEL_SHADDOLL_WENDIGOEffect(void);
unsigned char CanActivateEVIL_HERO_ADUSTED_GOLD(void);
void ActivateEVIL_HERO_ADUSTED_GOLDEffect(void);
unsigned char CanActivateEVIL_HERO_DARKEST_KNIGHT(void);
void ActivateEVIL_HERO_DARKEST_KNIGHTEffect(void);
unsigned char CanActivateEVIL_HERO_DEAD_END_PRISON(void);
void ActivateEVIL_HERO_DEAD_END_PRISONEffect(void);
unsigned char CanActivateEVIL_HERO_INFERNAL_GAINER(void);
void ActivateEVIL_HERO_INFERNAL_GAINEREffect(void);
unsigned char CanActivateEVIL_HERO_INFERNAL_RIDER(void);
void ActivateEVIL_HERO_INFERNAL_RIDEREffect(void);
unsigned char CanActivateEVIL_HERO_LIGHTNING_GOLEM(void);
void ActivateEVIL_HERO_LIGHTNING_GOLEMEffect(void);
unsigned char CanActivateEVIL_HERO_MALICIOUS_BANE(void);
void ActivateEVIL_HERO_MALICIOUS_BANEEffect(void);
unsigned char CanActivateEVIL_HERO_NEOS_LORD(void);
void ActivateEVIL_HERO_NEOS_LORDEffect(void);
unsigned char CanActivateEVIL_HERO_SINISTER_NECROM(void);
void ActivateEVIL_HERO_SINISTER_NECROMEffect(void);
unsigned char CanActivateEVIL_HERO_TOXIC_BUBBLE(void);
void ActivateEVIL_HERO_TOXIC_BUBBLEEffect(void);
unsigned char CanActivateEVIL_HERO_VICIOUS_CLAWS(void);
void ActivateEVIL_HERO_VICIOUS_CLAWSEffect(void);
unsigned char CanActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTION(void);
void ActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTIONEffect(void);
unsigned char CanActivateHARPIE_CHANNELER(void);
void ActivateHARPIE_CHANNELEREffect(void);
unsigned char CanActivateHARPIE_CONDUCTOR(void);
void ActivateHARPIE_CONDUCTOREffect(void);
unsigned char CanActivateHARPIE_DANCER(void);
void ActivateHARPIE_DANCEREffect(void);
unsigned char CanActivateHARPIE_HARPIST(void);
void ActivateHARPIE_HARPISTEffect(void);
unsigned char CanActivateHARPIE_ORACLE(void);
void ActivateHARPIE_ORACLEEffect(void);
unsigned char CanActivateHARPIE_QUEEN(void);
void ActivateHARPIE_QUEENEffect(void);
unsigned char CanActivateHELSHADDOLL_HOLLOW(void);
void ActivateHELSHADDOLL_HOLLOWEffect(void);
unsigned char CanActivateHERALD_OF_PERFECTION(void);
void ActivateHERALD_OF_PERFECTIONEffect(void);
unsigned char CanActivateHERALD_OF_ULTIMATENESS(void);
void ActivateHERALD_OF_ULTIMATENESSEffect(void);
unsigned char CanActivateILLUSION_OF_CHAOS(void);
void ActivateILLUSION_OF_CHAOSEffect(void);
unsigned char CanActivateKEEPER_OF_DRAGON_MAGIC(void);
void ActivateKEEPER_OF_DRAGON_MAGICEffect(void);
unsigned char CanActivateLONEFIRE_BLOSSOM(void);
void ActivateLONEFIRE_BLOSSOMEffect(void);
unsigned char CanActivateMAGICIANS_ROBE(void);
void ActivateMAGICIANS_ROBEEffect(void);
unsigned char CanActivateMAGICIANS_SOULS(void);
void ActivateMAGICIANS_SOULSEffect(void);
unsigned char CanActivateMASTER_OF_CHAOS(void);
void ActivateMASTER_OF_CHAOSEffect(void);
unsigned char CanActivateMILLENNIUM_EYES_RESTRICT(void);
void ActivateMILLENNIUM_EYES_RESTRICTEffect(void);
unsigned char CanActivateNAELSHADDOLL_ARIEL(void);
void ActivateNAELSHADDOLL_ARIELEffect(void);
unsigned char CanActivateNEHSHADDOLL_GENIUS(void);
void ActivateNEHSHADDOLL_GENIUSEffect(void);
unsigned char CanActivatePOWER_TOOL_DRAGON(void);
void ActivatePOWER_TOOL_DRAGONEffect(void);
unsigned char CanActivatePREDAPLANT_VERTE_ANACONDA(void);
void ActivatePREDAPLANT_VERTE_ANACONDAEffect(void);
unsigned char CanActivateQADSHADDOLL_KEIOS(void);
void ActivateQADSHADDOLL_KEIOSEffect(void);
unsigned char CanActivateREESHADDOLL_WENDI(void);
void ActivateREESHADDOLL_WENDIEffect(void);
unsigned char CanActivateREESHADDOLL_WENDIKURUHU(void);
void ActivateREESHADDOLL_WENDIKURUHUEffect(void);
unsigned char CanActivateREPTILIANNE_ECHIDNA(void);
void ActivateREPTILIANNE_ECHIDNAEffect(void);
unsigned char CanActivateREPTILIANNE_LAMIA(void);
void ActivateREPTILIANNE_LAMIAEffect(void);
unsigned char CanActivateREPTILIANNE_MEDUSA(void);
void ActivateREPTILIANNE_MEDUSAEffect(void);
unsigned char CanActivateREPTILIANNE_VASKII(void);
void ActivateREPTILIANNE_VASKIIEffect(void);
unsigned char CanActivateSHADDOLL_BEAST(void);
void ActivateSHADDOLL_BEASTEffect(void);
unsigned char CanActivateSHADDOLL_DRAGON(void);
void ActivateSHADDOLL_DRAGONEffect(void);
unsigned char CanActivateSHADDOLL_FALCO(void);
void ActivateSHADDOLL_FALCOEffect(void);
unsigned char CanActivateSHADDOLL_HEDGEHOG(void);
void ActivateSHADDOLL_HEDGEHOGEffect(void);
unsigned char CanActivateSHADDOLL_HOUND(void);
void ActivateSHADDOLL_HOUNDEffect(void);
unsigned char CanActivateSHADDOLL_SQUAMATA(void);
void ActivateSHADDOLL_SQUAMATAEffect(void);
unsigned char CanActivateSTARDUST_DRAGON(void);
void ActivateSTARDUST_DRAGONEffect(void);
unsigned char CanActivateTIMEAUS_THE_UNITED_DRAGON(void);
void ActivateTIMEAUS_THE_UNITED_DRAGONEffect(void);
unsigned char CanActivateTOHUSHADDOLL_GRYSTA(void);
void ActivateTOHUSHADDOLL_GRYSTAEffect(void);
unsigned char CanActivateVENOM_BOA(void);
void ActivateVENOM_BOAEffect(void);
unsigned char CanActivateVENOM_SERPENT(void);
void ActivateVENOM_SERPENTEffect(void);
unsigned char CanActivateVENOM_SNAKE(void);
void ActivateVENOM_SNAKEEffect(void);
unsigned char CanActivateYAMORIMORI(void);
void ActivateYAMORIMORIEffect(void);
unsigned char CanActivateARCANA_FORCE_V_THE_HIEROPHANT(void);
void ActivateARCANA_FORCE_V_THE_HIEROPHANTEffect(void);
unsigned char CanActivateARCANA_FORCE_XII_THE_HANGMAN(void);
void ActivateARCANA_FORCE_XII_THE_HANGMANEffect(void);
unsigned char CanActivateARCANA_FORCE_XIX_THE_SUN(void);
void ActivateARCANA_FORCE_XIX_THE_SUNEffect(void);
unsigned char CanActivateARCANA_FORCE_XV_THE_FIEND(void);
void ActivateARCANA_FORCE_XV_THE_FIENDEffect(void);
unsigned char CanActivateARMED_NEOS(void);
void ActivateARMED_NEOSEffect(void);
unsigned char CanActivateCELESTIA_LIGHTSWORN_ANGEL(void);
void ActivateCELESTIA_LIGHTSWORN_ANGELEffect(void);
unsigned char CanActivateCHRYSALIS_CHICKY(void);
void ActivateCHRYSALIS_CHICKYEffect(void);
unsigned char CanActivateCHRYSALIS_DOLPHIN(void);
void ActivateCHRYSALIS_DOLPHINEffect(void);
unsigned char CanActivateCHRYSALIS_MOLE(void);
void ActivateCHRYSALIS_MOLEEffect(void);
unsigned char CanActivateCHRYSALIS_PANTAIL(void);
void ActivateCHRYSALIS_PANTAILEffect(void);
unsigned char CanActivateCHRYSALIS_PINNY(void);
void ActivateCHRYSALIS_PINNYEffect(void);
unsigned char CanActivateCROSS_KEEPER(void);
void ActivateCROSS_KEEPEREffect(void);
unsigned char CanActivateCURIOUS_THE_LIGHTSWORN_DOMINION(void);
void ActivateCURIOUS_THE_LIGHTSWORN_DOMINIONEffect(void);
unsigned char CanActivateEHREN_LIGHTSWORN_MONK(void);
void ActivateEHREN_LIGHTSWORN_MONKEffect(void);
unsigned char CanActivateELEMENTAL_HERO_AQUA_NEOS(void);
void ActivateELEMENTAL_HERO_AQUA_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_BRAVE_NEOS(void);
void ActivateELEMENTAL_HERO_BRAVE_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_CHAOS_NEOS(void);
void ActivateELEMENTAL_HERO_CHAOS_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_COSMO_NEOS(void);
void ActivateELEMENTAL_HERO_COSMO_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_DARK_NEOS(void);
void ActivateELEMENTAL_HERO_DARK_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_GLOW_NEOS(void);
void ActivateELEMENTAL_HERO_GLOW_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_GRAND_NEOS(void);
void ActivateELEMENTAL_HERO_GRAND_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_MAGMA_NEOS(void);
void ActivateELEMENTAL_HERO_MAGMA_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_MARINE_NEOS(void);
void ActivateELEMENTAL_HERO_MARINE_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_NEBULA_NEOS(void);
void ActivateELEMENTAL_HERO_NEBULA_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_SHINING_NEOS_WINGMAN(void);
void ActivateELEMENTAL_HERO_SHINING_NEOS_WINGMANEffect(void);
unsigned char CanActivateELEMENTAL_HERO_SPIRIT_OF_NEOS(void);
void ActivateELEMENTAL_HERO_SPIRIT_OF_NEOSEffect(void);
unsigned char CanActivateELEMENTAL_HERO_STORM_NEOS(void);
void ActivateELEMENTAL_HERO_STORM_NEOSEffect(void);
unsigned char CanActivateENLIGHTENMENT_DRAGON(void);
void ActivateENLIGHTENMENT_DRAGONEffect(void);
unsigned char CanActivateFELIS_LIGHTSWORN_ARCHER(void);
void ActivateFELIS_LIGHTSWORN_ARCHEREffect(void);
unsigned char CanActivateGLADIATOR_BEAST_ANDABATA(void);
void ActivateGLADIATOR_BEAST_ANDABATAEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_ATTORIX(void);
void ActivateGLADIATOR_BEAST_ATTORIXEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_AUGUSTUS(void);
void ActivateGLADIATOR_BEAST_AUGUSTUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_BESTIARI(void);
void ActivateGLADIATOR_BEAST_BESTIARIEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_CLAUDIUS(void);
void ActivateGLADIATOR_BEAST_CLAUDIUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_DAREIOS(void);
void ActivateGLADIATOR_BEAST_DAREIOSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_DARIUS(void);
void ActivateGLADIATOR_BEAST_DARIUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_DOMITIANUS(void);
void ActivateGLADIATOR_BEAST_DOMITIANUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_DRAGASES(void);
void ActivateGLADIATOR_BEAST_DRAGASESEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_EQUESTE(void);
void ActivateGLADIATOR_BEAST_EQUESTEEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_GISTEL(void);
void ActivateGLADIATOR_BEAST_GISTELEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_GYZARUS(void);
void ActivateGLADIATOR_BEAST_GYZARUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_HERAKLINOS(void);
void ActivateGLADIATOR_BEAST_HERAKLINOSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_HOPLOMUS(void);
void ActivateGLADIATOR_BEAST_HOPLOMUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_LANISTA(void);
void ActivateGLADIATOR_BEAST_LANISTAEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_LAQUARI(void);
void ActivateGLADIATOR_BEAST_LAQUARIEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_MURMILLO(void);
void ActivateGLADIATOR_BEAST_MURMILLOEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_NEROKIUS(void);
void ActivateGLADIATOR_BEAST_NEROKIUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_NOXIOUS(void);
void ActivateGLADIATOR_BEAST_NOXIOUSEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_SAGITTARII(void);
void ActivateGLADIATOR_BEAST_SAGITTARIIEffect(void);
unsigned char CanActivateGLADIATOR_BEAST_TAMER_EDITOR(void);
void ActivateGLADIATOR_BEAST_TAMER_EDITOREffect(void);
unsigned char CanActivateGLADIATOR_BEAST_VESPASIUS(void);
void ActivateGLADIATOR_BEAST_VESPASIUSEffect(void);
unsigned char CanActivateJAIN_LIGHTSWORN_PALADIN(void);
void ActivateJAIN_LIGHTSWORN_PALADINEffect(void);
unsigned char CanActivateJAIN_TWILIGHTSWORN_GENERAL(void);
void ActivateJAIN_TWILIGHTSWORN_GENERALEffect(void);
unsigned char CanActivateJUDGMENT_THE_DRAGON_OF_HEAVEN(void);
void ActivateJUDGMENT_THE_DRAGON_OF_HEAVENEffect(void);
unsigned char CanActivateLIGHTSWORN_DRAGONLING(void);
void ActivateLIGHTSWORN_DRAGONLINGEffect(void);
unsigned char CanActivateLUMINA_LIGHTSWORN_SUMMONER(void);
void ActivateLUMINA_LIGHTSWORN_SUMMONEREffect(void);
unsigned char CanActivateLUMINA_TWILIGHTSWORN_SHAMAN(void);
void ActivateLUMINA_TWILIGHTSWORN_SHAMANEffect(void);
unsigned char CanActivateLYLA_LIGHTSWORN_SORCERESS(void);
void ActivateLYLA_LIGHTSWORN_SORCERESSEffect(void);
unsigned char CanActivateLYLA_TWILIGHTSWORN_ENCHANTRESS(void);
void ActivateLYLA_TWILIGHTSWORN_ENCHANTRESSEffect(void);
unsigned char CanActivateMICHAEL_THE_ARCH_LIGHTSWORN(void);
void ActivateMICHAEL_THE_ARCH_LIGHTSWORNEffect(void);
unsigned char CanActivateMINERVA_LIGHTSWORN_MAIDEN(void);
void ActivateMINERVA_LIGHTSWORN_MAIDENEffect(void);
unsigned char CanActivateMINERVA_THE_ATHENIAN_LIGHTSWORN(void);
void ActivateMINERVA_THE_ATHENIAN_LIGHTSWORNEffect(void);
unsigned char CanActivateMINERVA_THE_EXHALTED_LIGHTSWORN(void);
void ActivateMINERVA_THE_EXHALTED_LIGHTSWORNEffect(void);
unsigned char CanActivateNEO_SPACE_CONNECTOR(void);
void ActivateNEO_SPACE_CONNECTOREffect(void);
unsigned char CanActivateNEO_SPACIAN_AIR_HUMMINGBIRD(void);
void ActivateNEO_SPACIAN_AIR_HUMMINGBIRDEffect(void);
unsigned char CanActivateNEO_SPACIAN_AQUA_DOLPHIN(void);
void ActivateNEO_SPACIAN_AQUA_DOLPHINEffect(void);
unsigned char CanActivateNEO_SPACIAN_DARK_PANTHER(void);
void ActivateNEO_SPACIAN_DARK_PANTHEREffect(void);
unsigned char CanActivateNEO_SPACIAN_MARINE_DOLPHIN(void);
void ActivateNEO_SPACIAN_MARINE_DOLPHINEffect(void);
unsigned char CanActivatePUNISHMENT_DRAGON(void);
void ActivatePUNISHMENT_DRAGONEffect(void);
unsigned char CanActivateRAIDEN_HAND_OF_THE_LIGHTSWORN(void);
void ActivateRAIDEN_HAND_OF_THE_LIGHTSWORNEffect(void);
unsigned char CanActivateRESCUE_CAT(void);
void ActivateRESCUE_CATEffect(void);
unsigned char CanActivateRESCUE_RABBIT(void);
void ActivateRESCUE_RABBITEffect(void);
unsigned char CanActivateRINYAN_LIGHTSWORN_ROGUE(void);
void ActivateRINYAN_LIGHTSWORN_ROGUEEffect(void);
unsigned char CanActivateRYKO_LIGHTSWORN_HUNTER(void);
void ActivateRYKO_LIGHTSWORN_HUNTEREffect(void);
unsigned char CanActivateRYKO_TWILIGHTSWORN_FIGHTER(void);
void ActivateRYKO_TWILIGHTSWORN_FIGHTEREffect(void);
unsigned char CanActivateTEST_BEAR(void);
void ActivateTEST_BEAREffect(void);
unsigned char CanActivateTEST_PANTHER(void);
void ActivateTEST_PANTHEREffect(void);
unsigned char CanActivateTEST_TIGER(void);
void ActivateTEST_TIGEREffect(void);
unsigned char CanActivateWEISS_LIGHTSWORN_ARCHFIEND(void);
void ActivateWEISS_LIGHTSWORN_ARCHFIENDEffect(void);
unsigned char CanActivateANCIENT_FAIRY_DRAGON(void);
void ActivateANCIENT_FAIRY_DRAGONEffect(void);
unsigned char CanActivateANCIENT_GEAR(void);
void ActivateANCIENT_GEAREffect(void);
unsigned char CanActivateANCIENT_GEAR_BEAST(void);
void ActivateANCIENT_GEAR_BEASTEffect(void);
unsigned char CanActivateANCIENT_GEAR_CANNON(void);
void ActivateANCIENT_GEAR_CANNONEffect(void);
unsigned char CanActivateANCIENT_GEAR_COMMANDER(void);
void ActivateANCIENT_GEAR_COMMANDEREffect(void);
unsigned char CanActivateANCIENT_GEAR_DARK_GOLEM(void);
void ActivateANCIENT_GEAR_DARK_GOLEMEffect(void);
unsigned char CanActivateANCIENT_GEAR_DRAGON(void);
void ActivateANCIENT_GEAR_DRAGONEffect(void);
unsigned char CanActivateANCIENT_GEAR_ENGINEER(void);
void ActivateANCIENT_GEAR_ENGINEEREffect(void);
unsigned char CanActivateANCIENT_GEAR_FRAME(void);
void ActivateANCIENT_GEAR_FRAMEEffect(void);
unsigned char CanActivateANCIENT_GEAR_GADJILTRON_CHIMERA(void);
void ActivateANCIENT_GEAR_GADJILTRON_CHIMERAEffect(void);
unsigned char CanActivateANCIENT_GEAR_GADJILTRON_DRAGON(void);
void ActivateANCIENT_GEAR_GADJILTRON_DRAGONEffect(void);
unsigned char CanActivateANCIENT_GEAR_GOLEM(void);
void ActivateANCIENT_GEAR_GOLEMEffect(void);
unsigned char CanActivateANCIENT_GEAR_GOLEM_ULTIMATE_POUND(void);
void ActivateANCIENT_GEAR_GOLEM_ULTIMATE_POUNDEffect(void);
unsigned char CanActivateANCIENT_GEAR_KNIGHT(void);
void ActivateANCIENT_GEAR_KNIGHTEffect(void);
unsigned char CanActivateANCIENT_GEAR_MEGATON_GOLEM(void);
void ActivateANCIENT_GEAR_MEGATON_GOLEMEffect(void);
unsigned char CanActivateANCIENT_GEAR_SOLDIER(void);
void ActivateANCIENT_GEAR_SOLDIEREffect(void);
unsigned char CanActivateANCIENT_GEAR_STATUE(void);
void ActivateANCIENT_GEAR_STATUEEffect(void);
unsigned char CanActivateANCIENT_GEAR_TANKER(void);
void ActivateANCIENT_GEAR_TANKEREffect(void);
unsigned char CanActivateANCIENT_SACRED_WYVERN(void);
void ActivateANCIENT_SACRED_WYVERNEffect(void);
unsigned char CanActivateARCANA_KNIGHT_JOKER(void);
void ActivateARCANA_KNIGHT_JOKEREffect(void);
unsigned char CanActivateARMITYLE_THE_CHAOS_PHANTASM(void);
void ActivateARMITYLE_THE_CHAOS_PHANTASMEffect(void);
unsigned char CanActivateBABYCERASAURUS(void);
void ActivateBABYCERASAURUSEffect(void);
unsigned char CanActivateBARRIER_STATUE_OF_THE_STORMWINDS(void);
void ActivateBARRIER_STATUE_OF_THE_STORMWINDSEffect(void);
unsigned char CanActivateBLACK_WINGED_DRAGON(void);
void ActivateBLACK_WINGED_DRAGONEffect(void);
unsigned char CanActivateBEAST_MACHINE_KING_BARBAROS_UR(void);
void ActivateBEAST_MACHINE_KING_BARBAROS_UREffect(void);
unsigned char CanActivateCHAOS_ANCIENT_GEAR_GIANT(void);
void ActivateCHAOS_ANCIENT_GEAR_GIANTEffect(void);
unsigned char CanActivateCORAL_DRAGON(void);
void ActivateCORAL_DRAGONEffect(void);
unsigned char CanActivateCRIMSON_BLADER(void);
void ActivateCRIMSON_BLADEREffect(void);
unsigned char CanActivateCRIMSON_DRAGON(void);
void ActivateCRIMSON_DRAGONEffect(void);
unsigned char CanActivateCYBER_DRAGON_INFINITY(void);
void ActivateCYBER_DRAGON_INFINITYEffect(void);
unsigned char CanActivateCYBER_SLASH_HARPY_LADY(void);
void ActivateCYBER_SLASH_HARPY_LADYEffect(void);
unsigned char CanActivateDARK_HORUS(void);
void ActivateDARK_HORUSEffect(void);
unsigned char CanActivateDARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE(void);
void ActivateDARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICEEffect(void);
unsigned char CanActivateDARKBLAZE_DRAGON(void);
void ActivateDARKBLAZE_DRAGONEffect(void);
unsigned char CanActivateBOOT_UP_SOLDIER_DREAD_DYNAMO(void);
void ActivateBOOT_UP_SOLDIER_DREAD_DYNAMOEffect(void);
unsigned char CanActivateCASTEL_THE_SKY_BLASTER_MUSKETEER(void);
void ActivateCASTEL_THE_SKY_BLASTER_MUSKETEEREffect(void);
unsigned char CanActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS(void);
void ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOSEffect(void);
unsigned char CanActivateDEMISE_KING_OF_ARMAGEDDON(void);
void ActivateDEMISE_KING_OF_ARMAGEDDONEffect(void);
unsigned char CanActivateEVOLZAR_DOLKKA(void);
void ActivateEVOLZAR_DOLKKAEffect(void);
unsigned char CanActivateFLAME_RULER(void);
void ActivateFLAME_RULEREffect(void);
unsigned char CanActivateFORMULA_SYNCHRON(void);
void ActivateFORMULA_SYNCHRONEffect(void);
unsigned char CanActivateGANDORA_X_THE_DRAGON_OF_DESTRUCTION(void);
void ActivateGANDORA_X_THE_DRAGON_OF_DESTRUCTIONEffect(void);
unsigned char CanActivateGREAT_POSEIDON_BEETLE(void);
void ActivateGREAT_POSEIDON_BEETLEEffect(void);
unsigned char CanActivateGREEN_BABOON_DEFENDER_OF_THE_FOREST(void);
void ActivateGREEN_BABOON_DEFENDER_OF_THE_FORESTEffect(void);
unsigned char CanActivateGUNGNIR_DRAGON_OF_THE_ICE_BARRIER(void);
void ActivateGUNGNIR_DRAGON_OF_THE_ICE_BARRIEREffect(void);
unsigned char CanActivateHERALD_OF_THE_ARC_LIGHT(void);
void ActivateHERALD_OF_THE_ARC_LIGHTEffect(void);
unsigned char CanActivateHERALD_OF_ULIMATENESS(void);
void ActivateHERALD_OF_ULIMATENESSEffect(void);
unsigned char CanActivateHONEST(void);
void ActivateHONESTEffect(void);
unsigned char CanActivateJUNK_SYNCHRON(void);
void ActivateJUNK_SYNCHRONEffect(void);
unsigned char CanActivateLEVIAIR_THE_SEA_DRAGON(void);
void ActivateLEVIAIR_THE_SEA_DRAGONEffect(void);
unsigned char CanActivateLIFE_STREAM_DRAGON(void);
void ActivateLIFE_STREAM_DRAGONEffect(void);
unsigned char CanActivateMAGICAL_MARIONETTE(void);
void ActivateMAGICAL_MARIONETTEEffect(void);
unsigned char CanActivateMAGNA_DRAGO(void);
void ActivateMAGNA_DRAGOEffect(void);
unsigned char CanActivateMIRAGE_DRAGON(void);
void ActivateMIRAGE_DRAGONEffect(void);
unsigned char CanActivateMONTAGE_DRAGON(void);
void ActivateMONTAGE_DRAGONEffect(void);
unsigned char CanActivateMORPHTRONIC_BOARDEN(void);
void ActivateMORPHTRONIC_BOARDENEffect(void);
unsigned char CanActivateMORPHTRONIC_BOOMBOXEN(void);
void ActivateMORPHTRONIC_BOOMBOXENEffect(void);
unsigned char CanActivateMORPHTRONIC_CAMERAN(void);
void ActivateMORPHTRONIC_CAMERANEffect(void);
unsigned char CanActivateMORPHTRONIC_CELFON(void);
void ActivateMORPHTRONIC_CELFONEffect(void);
unsigned char CanActivateMORPHTRONIC_CLOCKEN(void);
void ActivateMORPHTRONIC_CLOCKENEffect(void);
unsigned char CanActivateMORPHTRONIC_DATATRON(void);
void ActivateMORPHTRONIC_DATATRONEffect(void);
unsigned char CanActivateMORPHTRONIC_EARFON(void);
void ActivateMORPHTRONIC_EARFONEffect(void);
unsigned char CanActivateMORPHTRONIC_LANTRON(void);
void ActivateMORPHTRONIC_LANTRONEffect(void);
unsigned char CanActivateMORPHTRONIC_MAGNEN(void);
void ActivateMORPHTRONIC_MAGNENEffect(void);
unsigned char CanActivateMORPHTRONIC_MAGNEN_BAR(void);
void ActivateMORPHTRONIC_MAGNEN_BAREffect(void);
unsigned char CanActivateMORPHTRONIC_RADION(void);
void ActivateMORPHTRONIC_RADIONEffect(void);
unsigned char CanActivateMORPHTRONIC_REMOTEN(void);
void ActivateMORPHTRONIC_REMOTENEffect(void);
unsigned char CanActivateMORPHTRONIC_SCANNEN(void);
void ActivateMORPHTRONIC_SCANNENEffect(void);
unsigned char CanActivateMORPHTRONIC_SCOPEN(void);
void ActivateMORPHTRONIC_SCOPENEffect(void);
unsigned char CanActivateMORPHTRONIC_SLINGEN(void);
void ActivateMORPHTRONIC_SLINGENEffect(void);
unsigned char CanActivateMORPHTRONIC_SMARTFON(void);
void ActivateMORPHTRONIC_SMARTFONEffect(void);
unsigned char CanActivateMORPHTRONIC_STAPLEN(void);
void ActivateMORPHTRONIC_STAPLENEffect(void);
unsigned char CanActivateMORPHTRONIC_TELEFON(void);
void ActivateMORPHTRONIC_TELEFONEffect(void);
unsigned char CanActivateMORPHTRONIC_VACUUMEN(void);
void ActivateMORPHTRONIC_VACUUMENEffect(void);
unsigned char CanActivateMORPHTRONIC_VIDEON(void);
void ActivateMORPHTRONIC_VIDEONEffect(void);
unsigned char CanActivateNATURIA_BEAST(void);
void ActivateNATURIA_BEASTEffect(void);
unsigned char CanActivateNITRO_WARRIOR(void);
void ActivateNITRO_WARRIOREffect(void);
unsigned char CanActivatePOWER_TOOL_BRAVER_DRAGON(void);
void ActivatePOWER_TOOL_BRAVER_DRAGONEffect(void);
unsigned char CanActivateRAINBOW_DARK_DRAGON(void);
void ActivateRAINBOW_DARK_DRAGONEffect(void);
unsigned char CanActivateROAD_SYNCHRON(void);
void ActivateROAD_SYNCHRONEffect(void);
unsigned char CanActivateROAD_WARRIOR(void);
void ActivateROAD_WARRIOREffect(void);
unsigned char CanActivateSILENT_MAGICIAN_LV4(void);
void ActivateSILENT_MAGICIAN_LV4Effect(void);
unsigned char CanActivateSILENT_MAGICIAN_LV8(void);
void ActivateSILENT_MAGICIAN_LV8Effect(void);
unsigned char CanActivateSIMORGH_BIRD_OF_ANCESTRY(void);
void ActivateSIMORGH_BIRD_OF_ANCESTRYEffect(void);
unsigned char CanActivateSPELL_STRIKER(void);
void ActivateSPELL_STRIKEREffect(void);
unsigned char CanActivateT_G_HYPER_LIBRARIAN(void);
void ActivateT_G_HYPER_LIBRARIANEffect(void);
unsigned char CanActivateTATSUNOKO(void);
void ActivateTATSUNOKOEffect(void);
unsigned char CanActivateTIME_THIEF_REDOER(void);
void ActivateTIME_THIEF_REDOEREffect(void);
unsigned char CanActivateTRISHULA_DRAGON_OF_THE_ICE_BARRIER(void);
void ActivateTRISHULA_DRAGON_OF_THE_ICE_BARRIEREffect(void);
unsigned char CanActivateTUNINGWARE(void);
void ActivateTUNINGWAREEffect(void);
unsigned char CanActivateTURBO_BOOSTER(void);
void ActivateTURBO_BOOSTEREffect(void);
unsigned char CanActivateTURBO_CANNON(void);
void ActivateTURBO_CANNONEffect(void);
unsigned char CanActivateTURBO_ROCKET(void);
void ActivateTURBO_ROCKETEffect(void);
unsigned char CanActivateTURBO_SYNCHRON(void);
void ActivateTURBO_SYNCHRONEffect(void);
unsigned char CanActivateTYRANNO_INFINITY(void);
void ActivateTYRANNO_INFINITYEffect(void);
unsigned char CanActivateULTIMATE_ANCIENT_GEAR_GOLEM(void);
void ActivateULTIMATE_ANCIENT_GEAR_GOLEMEffect(void);
unsigned char CanActivateULTIMATE_TYRANNO(void);
void ActivateULTIMATE_TYRANNOEffect(void);
unsigned char CanActivateWARRIOR_OF_ATLANTIS(void);
void ActivateWARRIOR_OF_ATLANTISEffect(void);
unsigned char CanActivateX_SABER_AIRBELLUM(void);
void ActivateX_SABER_AIRBELLUMEffect(void);
unsigned char CanActivateA_CAT_OF_ILL_OMEN(void);
void ActivateA_CAT_OF_ILL_OMENEffect(void);
unsigned char CanActivateAMAZONESS_AUGUSTA(void);
void ActivateAMAZONESS_AUGUSTAEffect(void);
unsigned char CanActivateAMAZONESS_BABY_TIGER(void);
void ActivateAMAZONESS_BABY_TIGEREffect(void);
unsigned char CanActivateAMAZONESS_EMPRESS(void);
void ActivateAMAZONESS_EMPRESSEffect(void);
unsigned char CanActivateAMAZONESS_PET_LIGER(void);
void ActivateAMAZONESS_PET_LIGEREffect(void);
unsigned char CanActivateAMAZONESS_PET_LIGER_KING(void);
void ActivateAMAZONESS_PET_LIGER_KINGEffect(void);
unsigned char CanActivateAMAZONESS_PRINCESS(void);
void ActivateAMAZONESS_PRINCESSEffect(void);
unsigned char CanActivateAMAZONESS_QUEEN(void);
void ActivateAMAZONESS_QUEENEffect(void);
unsigned char CanActivateAMAZONESS_SAGE(void);
void ActivateAMAZONESS_SAGEEffect(void);
unsigned char CanActivateAMAZONESS_SCOUTS(void);
void ActivateAMAZONESS_SCOUTSEffect(void);
unsigned char CanActivateALECTOR_SOVEREIGN_OF_BIRDS(void);
void ActivateALECTOR_SOVEREIGN_OF_BIRDSEffect(void);
unsigned char CanActivateAMAZONESS_SPIRITUALIST(void);
void ActivateAMAZONESS_SPIRITUALISTEffect(void);
unsigned char CanActivateAMAZONESS_SPY(void);
void ActivateAMAZONESS_SPYEffect(void);
unsigned char CanActivateAMAZONESS_TRAINEE(void);
void ActivateAMAZONESS_TRAINEEEffect(void);
unsigned char CanActivateAMAZONESS_WAR_CHIEF(void);
void ActivateAMAZONESS_WAR_CHIEFEffect(void);
unsigned char CanActivateAN_OWL_OF_LUCK(void);
void ActivateAN_OWL_OF_LUCKEffect(void);
unsigned char CanActivateATLANTEAN_ATTACK_SQUAD(void);
void ActivateATLANTEAN_ATTACK_SQUADEffect(void);
unsigned char CanActivateATLANTEAN_DRAGOONS(void);
void ActivateATLANTEAN_DRAGOONSEffect(void);
unsigned char CanActivateATLANTEAN_HEAVY_INFANTRY(void);
void ActivateATLANTEAN_HEAVY_INFANTRYEffect(void);
unsigned char CanActivateATLANTEAN_MARKSMAN(void);
void ActivateATLANTEAN_MARKSMANEffect(void);
unsigned char CanActivateBEAST_KING_BARBAROS(void);
void ActivateBEAST_KING_BARBAROSEffect(void);
unsigned char CanActivateCELESTIAL_KNIGHTLORD_PARSHATH(void);
void ActivateCELESTIAL_KNIGHTLORD_PARSHATHEffect(void);
unsigned char CanActivateCHAINSAW_INSECT(void);
void ActivateCHAINSAW_INSECTEffect(void);
unsigned char CanActivateCHARM_OF_SHABTI(void);
void ActivateCHARM_OF_SHABTIEffect(void);
unsigned char CanActivateBAZOO_THE_SOUL_EATER(void);
void ActivateBAZOO_THE_SOUL_EATEREffect(void);
unsigned char CanActivateASH_BLOSSOM_AND_JOYOUS_SPRING(void);
void ActivateASH_BLOSSOM_AND_JOYOUS_SPRINGEffect(void);
unsigned char CanActivateCLEAR_VICE_DRAGON(void);
void ActivateCLEAR_VICE_DRAGONEffect(void);
unsigned char CanActivateCYBERNETIC_MAGICIAN(void);
void ActivateCYBERNETIC_MAGICIANEffect(void);
unsigned char CanActivateDARKLORD_DESIRE(void);
void ActivateDARKLORD_DESIREEffect(void);
unsigned char CanActivateDEEP_SEA_DIVA(void);
void ActivateDEEP_SEA_DIVAEffect(void);
unsigned char CanActivateDIVINER_OF_THE_HERALD(void);
void ActivateDIVINER_OF_THE_HERALDEffect(void);
unsigned char CanActivateELDER_ENTITY_NORDEN(void);
void ActivateELDER_ENTITY_NORDENEffect(void);
unsigned char CanActivateENRAGED_BATTLE_OX(void);
void ActivateENRAGED_BATTLE_OXEffect(void);
unsigned char CanActivateFOG_KING(void);
void ActivateFOG_KINGEffect(void);
unsigned char CanActivateGAGAGIGO_THE_RISEN(void);
void ActivateGAGAGIGO_THE_RISENEffect(void);
unsigned char CanActivateGOLDEN_HOMUNCULUS(void);
void ActivateGOLDEN_HOMUNCULUSEffect(void);
unsigned char CanActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEAST(void);
void ActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEASTEffect(void);
unsigned char CanActivateGAMECIAL_THE_SEA_TURTLE_KAIJU(void);
void ActivateGAMECIAL_THE_SEA_TURTLE_KAIJUEffect(void);
unsigned char CanActivateGRAVEKEEPERS_AMBUSHER(void);
void ActivateGRAVEKEEPERS_AMBUSHEREffect(void);
unsigned char CanActivateGRAVEKEEPERS_CANNONHOLDER(void);
void ActivateGRAVEKEEPERS_CANNONHOLDEREffect(void);
unsigned char CanActivateGRAVEKEEPERS_CHIEF(void);
void ActivateGRAVEKEEPERS_CHIEFEffect(void);
unsigned char CanActivateGRAVEKEEPERS_COMMANDANT(void);
void ActivateGRAVEKEEPERS_COMMANDANTEffect(void);
unsigned char CanActivateGRAVEKEEPERS_CURSE(void);
void ActivateGRAVEKEEPERS_CURSEEffect(void);
unsigned char CanActivateGRAVEKEEPERS_DESCENDANT(void);
void ActivateGRAVEKEEPERS_DESCENDANTEffect(void);
unsigned char CanActivateGRAVEKEEPERS_GUARD(void);
void ActivateGRAVEKEEPERS_GUARDEffect(void);
unsigned char CanActivateGRAVEKEEPERS_HEADMAN(void);
void ActivateGRAVEKEEPERS_HEADMANEffect(void);
unsigned char CanActivateGRAVEKEEPERS_HERATIC(void);
void ActivateGRAVEKEEPERS_HERATICEffect(void);
unsigned char CanActivateGRAVEKEEPERS_NOBLEMAN(void);
void ActivateGRAVEKEEPERS_NOBLEMANEffect(void);
unsigned char CanActivateGRAVEKEEPERS_ORACLE(void);
void ActivateGRAVEKEEPERS_ORACLEEffect(void);
unsigned char CanActivateGRAVEKEEPERS_PRIESTESS(void);
void ActivateGRAVEKEEPERS_PRIESTESSEffect(void);
unsigned char CanActivateGRAVEKEEPERS_RECRUITER(void);
void ActivateGRAVEKEEPERS_RECRUITEREffect(void);
unsigned char CanActivateGRAVEKEEPERS_SHAMAN(void);
void ActivateGRAVEKEEPERS_SHAMANEffect(void);
unsigned char CanActivateGRAVEKEEPERS_SPEAR_SOLDIER(void);
void ActivateGRAVEKEEPERS_SPEAR_SOLDIEREffect(void);
unsigned char CanActivateGRAVEKEEPERS_SPIRITUALIST(void);
void ActivateGRAVEKEEPERS_SPIRITUALISTEffect(void);
unsigned char CanActivateGRAVEKEEPERS_SPY(void);
void ActivateGRAVEKEEPERS_SPYEffect(void);
unsigned char CanActivateGRAVEKEEPERS_SUPERNATURALIST(void);
void ActivateGRAVEKEEPERS_SUPERNATURALISTEffect(void);
unsigned char CanActivateGRAVEKEEPERS_VASSAL(void);
void ActivateGRAVEKEEPERS_VASSALEffect(void);
unsigned char CanActivateHELIOS_DUO_MEGISTUS(void);
void ActivateHELIOS_DUO_MEGISTUSEffect(void);
unsigned char CanActivateHELIOS_THE_PRIMORDIAL_SUN(void);
void ActivateHELIOS_THE_PRIMORDIAL_SUNEffect(void);
unsigned char CanActivateHELIOS_TRICE_MEGISTUS(void);
void ActivateHELIOS_TRICE_MEGISTUSEffect(void);
unsigned char CanActivateLADY_OF_D(void);
void ActivateLADY_OF_DEffect(void);
unsigned char CanActivateLEVEL_EATER(void);
void ActivateLEVEL_EATEREffect(void);
unsigned char CanActivateLIGHTRAY_DAEDALUS(void);
void ActivateLIGHTRAY_DAEDALUSEffect(void);
unsigned char CanActivateLIGHTRAY_GEARFRIED(void);
void ActivateLIGHTRAY_GEARFRIEDEffect(void);
unsigned char CanActivateGRAVEKEEPERS_VISIONARY(void);
void ActivateGRAVEKEEPERS_VISIONARYEffect(void);
unsigned char CanActivateGRAVEKEEPERS_WATCHER(void);
void ActivateGRAVEKEEPERS_WATCHEREffect(void);
unsigned char CanActivateMAJESTY_HYPERION(void);
void ActivateMAJESTY_HYPERIONEffect(void);
unsigned char CanActivateMASTER_HYPERION(void);
void ActivateMASTER_HYPERIONEffect(void);
unsigned char CanActivateMASTERFLARE_HYPERION(void);
void ActivateMASTERFLARE_HYPERIONEffect(void);
unsigned char CanActivateMEZUKI(void);
void ActivateMEZUKIEffect(void);
unsigned char CanActivateNECROFACE(void);
void ActivateNECROFACEEffect(void);
unsigned char CanActivateNUMBER_39_UTOPIA(void);
void ActivateNUMBER_39_UTOPIAEffect(void);
unsigned char CanActivateOCEAN_DRAGON_LORD_NEO_DAEDALUS(void);
void ActivateOCEAN_DRAGON_LORD_NEO_DAEDALUSEffect(void);
unsigned char CanActivatePOSEIDRA_THE_ATLANTEAN_DRAGON(void);
void ActivatePOSEIDRA_THE_ATLANTEAN_DRAGONEffect(void);
unsigned char CanActivatePROTECTOR_OF_THE_AGENTS_MOON(void);
void ActivatePROTECTOR_OF_THE_AGENTS_MOONEffect(void);
unsigned char CanActivateMAXX_C(void);
void ActivateMAXX_CEffect(void);
unsigned char CanActivateSILENT_SWORDSMAN(void);
void ActivateSILENT_SWORDSMANEffect(void);
unsigned char CanActivateSILENT_SWORDSMAN_LV3(void);
void ActivateSILENT_SWORDSMAN_LV3Effect(void);
unsigned char CanActivateSILENT_SWORDSMAN_LV5(void);
void ActivateSILENT_SWORDSMAN_LV5Effect(void);
unsigned char CanActivateSILENT_SWORDSMAN_LV7(void);
void ActivateSILENT_SWORDSMAN_LV7Effect(void);
unsigned char CanActivateSILENT_SWORDSMAN_ZERO(void);
void ActivateSILENT_SWORDSMAN_ZEROEffect(void);
unsigned char CanActivateSOUL_ABSORBING_BONE_TOWER(void);
void ActivateSOUL_ABSORBING_BONE_TOWEREffect(void);
unsigned char CanActivateSPINED_GILLMAN(void);
void ActivateSPINED_GILLMANEffect(void);
unsigned char CanActivateSUBSTITOAD(void);
void ActivateSUBSTITOADEffect(void);
unsigned char CanActivateTHE_AGENT_OF_DESTRUCTION_VENUS(void);
void ActivateTHE_AGENT_OF_DESTRUCTION_VENUSEffect(void);
unsigned char CanActivateTHE_AGENT_OF_ENTROPY_URANUS(void);
void ActivateTHE_AGENT_OF_ENTROPY_URANUSEffect(void);
unsigned char CanActivateTHE_AGENT_OF_LIFE_NEPTUNE(void);
void ActivateTHE_AGENT_OF_LIFE_NEPTUNEEffect(void);
unsigned char CanActivateTHE_AGENT_OF_MIRACLES_JUPITER(void);
void ActivateTHE_AGENT_OF_MIRACLES_JUPITEREffect(void);
unsigned char CanActivateTHE_CALCULATOR(void);
void ActivateTHE_CALCULATOREffect(void);
unsigned char CanActivateTHE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO(void);
void ActivateTHE_EXECUTOR_OF_THE_UNDERWORLD_PLUTOEffect(void);
unsigned char CanActivateTHUNDER_END_DRAGON(void);
void ActivateTHUNDER_END_DRAGONEffect(void);
unsigned char CanActivateTOADALLY_AWESOME(void);
void ActivateTOADALLY_AWESOMEEffect(void);
unsigned char CanActivateTREEBORN_FROG(void);
void ActivateTREEBORN_FROGEffect(void);
unsigned char CanActivateTROOP_DRAGON(void);
void ActivateTROOP_DRAGONEffect(void);
unsigned char CanActivateTUALATIN(void);
void ActivateTUALATINEffect(void);
unsigned char CanActivateVICTORIA(void);
void ActivateVICTORIAEffect(void);
unsigned char CanActivateWARM_WORM(void);
void ActivateWARM_WORMEffect(void);
unsigned char CanActivateWHITE_HORNED_DRAGON(void);
void ActivateWHITE_HORNED_DRAGONEffect(void);
unsigned char CanActivateZERADIAS_HERALD_OF_HEAVEN(void);
void ActivateZERADIAS_HERALD_OF_HEAVENEffect(void);
unsigned char CanActivateTHE_AGENT_OF_MYSTERU_EARTH(void);
void ActivateTHE_AGENT_OF_MYSTERU_EARTHEffect(void);
unsigned char CanActivateMonsterEffect(void) {
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  u16 neptuneSavedId;
  unsigned char canActivate;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  neptuneSavedId = Duel_BeginCopiedEffectIdentity(zone);

  if (gMonEffect.id == ELEMENTAL_HERO_NEOS_ALIUS)
    canActivate = CanActivateElementalHeroNeosAlius();
  else if (gMonEffect.id == JUNK_SYNCHRON)
    canActivate = CanActivateJUNK_SYNCHRON();
  else if (gMonEffect.id == EL_SHADDOLL_MESHAHRAIL)
    canActivate = CanActivateEL_SHADDOLL_MESHAHRAIL();
  else if (gMonEffect.id == DESTINY_HERO_DOMINANCE)
    canActivate = CanActivateDESTINY_HERO_DOMINANCE();
  else if (gMonEffect.id == EVIL_HERO_DARKEST_KNIGHT)
    canActivate = CanActivateEVIL_HERO_DARKEST_KNIGHT();
  else if (gMonEffect.id == AROMAGE_MARJORAM)
    canActivate = CanActivateAROMAGE_MARJORAM();
  else if (gMonEffect.id == GLADIATOR_BEAST_NEROKIUS)
    canActivate = CanActivateGLADIATOR_BEAST_NEROKIUS();
  else if (gMonEffect.id == GLADIATOR_BEAST_ANDABATA)
    canActivate = CanActivateGLADIATOR_BEAST_ANDABATA();
  else if (gMonEffect.id == TEST_PANTHER)
    canActivate = CanActivateTEST_PANTHER();
  else if (gMonEffect.id == DESTINY_HERO_DECIDER)
    canActivate = CanActivateDESTINY_HERO_DECIDER();
  else if (gMonEffect.id == MINERVA_THE_ATHENIAN_LIGHTSWORN)
    canActivate = CanActivateMINERVA_THE_ATHENIAN_LIGHTSWORN();
  else if (gMonEffect.id == ARMED_NEOS)
    canActivate = CanActivateARMED_NEOS();
  else if (gMonEffect.id == CURIOUS_THE_LIGHTSWORN_DOMINION)
    canActivate = CanActivateCURIOUS_THE_LIGHTSWORN_DOMINION();
  else if (gMonEffect.id == ANCIENT_GEAR_DRAGON)
    canActivate = CanActivateANCIENT_GEAR_DRAGON();
  else if (gMonEffect.id == AROMALILITH_MAGNOLIA)
    canActivate = CanActivateAROMALILITH_MAGNOLIA();
  else if (gMonEffect.id == GANDORA_G_THE_DRAGON_OF_DESTRUCTION)
    canActivate = CanActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTION();
  else if (gMonEffect.id == BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON)
    canActivate = CanActivateBLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON();
  else if (gMonEffect.id == AMAZONESS_PRINCESS)
    canActivate = CanActivateAMAZONESS_PRINCESS();
  else if (gMonEffect.id == TOHUSHADDOLL_GRYSTA)
    canActivate = CanActivateTOHUSHADDOLL_GRYSTA();
  else if (gMonEffect.id == TEST_BEAR)
    canActivate = CanActivateTEST_BEAR();
  else if (gMonEffect.id == AMAZONESS_PET_LIGER_KING)
    canActivate = CanActivateAMAZONESS_PET_LIGER_KING();
  else if (gMonEffect.id == AMAZONESS_EMPRESS)
    canActivate = CanActivateAMAZONESS_EMPRESS();
  else if (gMonEffect.id == EVIL_HERO_INFERNAL_RIDER)
    canActivate = CanActivateEVIL_HERO_INFERNAL_RIDER();
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
      case MONSTER_EFFECT_DESTINY_HERO_DASHER:
        canActivate = CanActivateDESTINY_HERO_DASHER();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DECIDER:
        canActivate = CanActivateDESTINY_HERO_DECIDER();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DENIER:
        canActivate = CanActivateDESTINY_HERO_DENIER();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DESTROYER_PHOENIX_ENFORCER:
        canActivate = CanActivateDESTINY_HERO_DESTROYER_PHOENIX_ENFORCER();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DIAMOND_DUDE:
        canActivate = CanActivateDESTINY_HERO_DIAMOND_DUDE();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DISK_COMMANDER:
        canActivate = CanActivateDESTINY_HERO_DISK_COMMANDER();
        break;
      case MONSTER_EFFECT_DESTINY_HERO_DOMINANCE:
        canActivate = CanActivateDESTINY_HERO_DOMINANCE();
        break;
      case MONSTER_EFFECT_CYBER_VALLEY:
        canActivate = CanActivateCYBER_VALLEY();
        break;
      case DESTINY_HERO_DOOM_LORD:
        canActivate = CanActivateDESTINY_HERO_DOOM_LORD();
        break;
      case DESTINY_HERO_DREADNOUGHT_MASTER:
        canActivate = CanActivateDESTINY_HERO_DREADNOUGHT_MASTER();
        break;
      case DESTINY_HERO_DREADNOUGHT_SERVANT:
        canActivate = CanActivateDESTINY_HERO_DREADNOUGHT_SERVANT();
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
  if (gMonEffect.id == DESTINY_END_DRAGOON) {
    ActivateDESTINY_END_DRAGOONEffect();
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
  if (gMonEffect.id == DESTINY_HERO_DOMINANCE) {
    ActivateDESTINY_HERO_DOMINANCEEffect();
    return;
  }
  if (gMonEffect.id == DESTINY_HERO_DOOM_LORD) {
    ActivateDESTINY_HERO_DOOM_LORDEffect();
    return;
  }
  if (gMonEffect.id == DESTINY_HERO_DREADNOUGHT_MASTER) {
    ActivateDESTINY_HERO_DREADNOUGHT_MASTEREffect();
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
  if (gMonEffect.id == DESTINY_HERO_MALICIOUS) {
    ActivateDESTINY_HERO_MALICIOUSEffect();
    return;
  }
  if (gMonEffect.id == DESTINY_HERO_PLASMA) {
    ActivateDESTINY_HERO_PLASMAEffect();
    return;
  }
  if (gMonEffect.id == DIVINE_SERPENT_GEH) {
    ActivateDIVINE_SERPENT_GEHEffect();
    return;
  }
  if (gMonEffect.id == DESTINY_HERO_DESTROY_DOGMA) {
    ActivateDESTINY_HERO_DESTROY_DOGMAEffect();
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
  if (gMonEffect.id == LORD_OF_THE_RED) {
    ActivateLORD_OF_THE_REDEffect();
    return;
  }
  if (gMonEffect.id == MA_AT) {
    ActivateMA_ATEffect();
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
  if (gMonEffect.id == MAJESTIC_MECH_GORYU) {
    ActivateMAJESTIC_MECH_GORYUEffect();
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
  if (gMonEffect.id == MASTER_PEACE_THE_TRUE_DRACOSLAYING_KING) {
    ActivateMASTER_PEACE_THE_TRUE_DRACOSLAYING_KINGEffect();
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
  if (gMonEffect.id == MOLTEN_ZOMBIE) {
    ActivateMOLTEN_ZOMBIEEffect();
    return;
  }
  if (gMonEffect.id == MUCUS_YOLK) {
    ActivateMUCUS_YOLKEffect();
    return;
  }
  if (gMonEffect.id == NEO_BLUE_EYES_ULTIMATE_DRAGON) {
    ActivateNEO_BLUE_EYES_ULTIMATE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == NEOS_WISEMAN) {
    ActivateNEOS_WISEMANEffect();
    return;
  }
  if (gMonEffect.id == NIBIRU_THE_PRIMAL_BEING) {
    ActivateNIBIRU_THE_PRIMAL_BEINGEffect();
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
  if (gMonEffect.id == PROTECTOR_OF_THE_SANCTUARY) {
    ActivatePROTECTOR_OF_THE_SANCTUARYEffect();
    return;
  }
  if (gMonEffect.id == QUINTET_MAGICIAN) {
    ActivateQUINTET_MAGICIANEffect();
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
          || zone->id == JUNK_SYNCHRON
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
          || zone->id == ANDRO_SPHINX
          || zone->id == APPRENTICE_ILLUSION_MAGICIAN
          || zone->id == ARMED_DRAGON_LV5
          || zone->id == ARMED_DRAGON_LV7
          || zone->id == ARMED_DRAGON_LV10
          || zone->id == URIA_LORD_OF_SEARING_FLAMES
          || zone->id == RAVIEL_LORD_OF_PHANTASMS
          || zone->id == EL_SHADDOLL_MESHAHRAIL
          || zone->id == DESTINY_HERO_DOMINANCE
          || zone->id == EVIL_HERO_DARKEST_KNIGHT
          || zone->id == CYBER_VALLEY
          || zone->id == AROMAGE_MARJORAM
          || zone->id == GLADIATOR_BEAST_NEROKIUS
          || zone->id == GLADIATOR_BEAST_ANDABATA
          || zone->id == TEST_PANTHER
          || zone->id == DESTINY_HERO_DECIDER
          || zone->id == MINERVA_THE_ATHENIAN_LIGHTSWORN
          || zone->id == ARMED_NEOS
          || zone->id == CURIOUS_THE_LIGHTSWORN_DOMINION
          || zone->id == ANCIENT_GEAR_DRAGON
          || zone->id == AROMALILITH_MAGNOLIA
          || zone->id == GANDORA_G_THE_DRAGON_OF_DESTRUCTION
          || zone->id == BLUE_EYES_ALTERNATIVE_ULTIMATE_DRAGON
          || zone->id == AMAZONESS_PRINCESS
          || zone->id == TOHUSHADDOLL_GRYSTA
          || zone->id == TEST_BEAR
          || zone->id == AMAZONESS_PET_LIGER_KING
          || zone->id == AMAZONESS_EMPRESS
          || zone->id == EVIL_HERO_INFERNAL_RIDER
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
        if ((gCardInfo.monsterEffect == MONSTER_EFFECT_NONE && gMonEffect.id != MASK_OF_DARKNESS && gMonEffect.id != NEEDLE_BALL && gMonEffect.id != AMAZONESS_ARCHER && gMonEffect.id != ELEMENTAL_HERO_NEOS_ALIUS && gMonEffect.id != JUNK_SYNCHRON && gMonEffect.id != EL_SHADDOLL_MESHAHRAIL && gMonEffect.id != EVIL_HERO_DARKEST_KNIGHT && gMonEffect.id != AROMAGE_MARJORAM && gMonEffect.id != GLADIATOR_BEAST_NEROKIUS && gMonEffect.id != GLADIATOR_BEAST_ANDABATA && gMonEffect.id != TEST_PANTHER && gMonEffect.id != MINERVA_THE_ATHENIAN_LIGHTSWORN && gMonEffect.id != ARMED_NEOS && gMonEffect.id != CURIOUS_THE_LIGHTSWORN_DOMINION && gMonEffect.id != ANCIENT_GEAR_DRAGON && gMonEffect.id != AROMALILITH_MAGNOLIA && gMonEffect.id != GANDORA_G_THE_DRAGON_OF_DESTRUCTION && gMonEffect.id != AMAZONESS_PRINCESS && gMonEffect.id != TOHUSHADDOLL_GRYSTA && gMonEffect.id != TEST_BEAR && gMonEffect.id != AMAZONESS_PET_LIGER_KING && gMonEffect.id != AMAZONESS_EMPRESS && gMonEffect.id != EVIL_HERO_INFERNAL_RIDER) || !CanActivateMonsterEffect()) {
FAILED:
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
          gMonEffect.id = CARD_NONE;
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
    case 6:
      SynchroDuel_RunPlayerFlow();
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      CheckWinConditionExodia();
      break;
    case 7:
      XyzDuel_RunPlayerFlow();
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      CheckWinConditionExodia();
      break;
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
  if (gMonEffect.id == THE_AGENT_OF_JUDGMENT_SATURN) {
    ActivateTHE_AGENT_OF_JUDGMENT_SATURNEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_WISDOM_MERCURY) {
    ActivateTHE_AGENT_OF_WISDOM_MERCURYEffect();
    return;
  }
  if (gMonEffect.id == THE_CREATOR) {
    ActivateTHE_CREATOREffect();
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
  if (gMonEffect.id == ARCANITE_MAGICIAN) {
    ActivateARCANITE_MAGICIANEffect();
    return;
  }
  if (gMonEffect.id == ARMORY_ARM) {
    ActivateARMORY_ARMEffect();
    return;
  }
  if (gMonEffect.id == AROMA_JAR) {
    ActivateAROMA_JAREffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_BERGAMOT) {
    ActivateAROMAGE_BERGAMOTEffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_CANANGA) {
    ActivateAROMAGE_CANANGAEffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_JASMINE) {
    ActivateAROMAGE_JASMINEEffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_LAUREL) {
    ActivateAROMAGE_LAURELEffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_MARJORAM) {
    ActivateAROMAGE_MARJORAMEffect();
    return;
  }
  if (gMonEffect.id == AROMAGE_ROSEMARY) {
    ActivateAROMAGE_ROSEMARYEffect();
    return;
  }
  if (gMonEffect.id == AROMALILITH_MAGNOLIA) {
    ActivateAROMALILITH_MAGNOLIAEffect();
    return;
  }
  if (gMonEffect.id == AROMALILITH_ROSALINA) {
    ActivateAROMALILITH_ROSALINAEffect();
    return;
  }
  if (gMonEffect.id == AROMALILITH_ROSEMARY) {
    ActivateAROMALILITH_ROSEMARYEffect();
    return;
  }
  if (gMonEffect.id == AROMASERAPHY_JASMINE) {
    ActivateAROMASERAPHY_JASMINEEffect();
    return;
  }
  if (gMonEffect.id == AROMASERAPHY_ROSEMARY) {
    ActivateAROMASERAPHY_ROSEMARYEffect();
    return;
  }
  if (gMonEffect.id == AROMASERAPHY_SWEET_MARJORAM) {
    ActivateAROMASERAPHY_SWEET_MARJORAMEffect();
    return;
  }
  if (gMonEffect.id == AZURE_EYES_SILVER_DRAGON) {
    ActivateAZURE_EYES_SILVER_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLACK_ROSE_DRAGON) {
    ActivateBLACK_ROSE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_JET_DRAGON) {
    ActivateBLUE_EYES_JET_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_SOLID_DRAGON) {
    ActivateBLUE_EYES_SOLID_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_TYRANT_DRAGON) {
    ActivateBLUE_EYES_TYRANT_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_ULTIMATE_SPIRIT_DRAGON) {
    ActivateBLUE_EYES_ULTIMATE_SPIRIT_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BLUE_EYES_SPIRIT_DRAGON) {
    ActivateBLUE_EYES_SPIRIT_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BRIONAC_DRAGON_OF_THE_ICE_BARRIER) {
    ActivateBRIONAC_DRAGON_OF_THE_ICE_BARRIEREffect();
    return;
  }
  if (gMonEffect.id == COLOSSAL_FIGHTER) {
    ActivateCOLOSSAL_FIGHTEREffect();
    return;
  }
  if (gMonEffect.id == CYBER_SLASH_HARPIE_LADY) {
    ActivateCYBER_SLASH_HARPIE_LADYEffect();
    return;
  }
  if (gMonEffect.id == DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE) {
    ActivateDARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICEEffect();
    return;
  }
  if (gMonEffect.id == DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC) {
    ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGICEffect();
    return;
  }
  if (gMonEffect.id == DARK_STRIKE_FIGHTER) {
    ActivateDARK_STRIKE_FIGHTEREffect();
    return;
  }
  if (gMonEffect.id == EBON_ILLUSION_MAGICIAN) {
    ActivateEBON_ILLUSION_MAGICIANEffect();
    return;
  }
  if (gMonEffect.id == EL_SHADDOLL_MESHAHRAIL) {
    ActivateEL_SHADDOLL_MESHAHRAILEffect();
    return;
  }
  if (gMonEffect.id == EL_SHADDOLL_WENDIGO) {
    ActivateEL_SHADDOLL_WENDIGOEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_ADUSTED_GOLD) {
    ActivateEVIL_HERO_ADUSTED_GOLDEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_DARKEST_KNIGHT) {
    ActivateEVIL_HERO_DARKEST_KNIGHTEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_DEAD_END_PRISON) {
    ActivateEVIL_HERO_DEAD_END_PRISONEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_INFERNAL_GAINER) {
    ActivateEVIL_HERO_INFERNAL_GAINEREffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_INFERNAL_RIDER) {
    ActivateEVIL_HERO_INFERNAL_RIDEREffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_LIGHTNING_GOLEM) {
    ActivateEVIL_HERO_LIGHTNING_GOLEMEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_MALICIOUS_BANE) {
    ActivateEVIL_HERO_MALICIOUS_BANEEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_NEOS_LORD) {
    ActivateEVIL_HERO_NEOS_LORDEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_SINISTER_NECROM) {
    ActivateEVIL_HERO_SINISTER_NECROMEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_TOXIC_BUBBLE) {
    ActivateEVIL_HERO_TOXIC_BUBBLEEffect();
    return;
  }
  if (gMonEffect.id == EVIL_HERO_VICIOUS_CLAWS) {
    ActivateEVIL_HERO_VICIOUS_CLAWSEffect();
    return;
  }
  if (gMonEffect.id == GANDORA_G_THE_DRAGON_OF_DESTRUCTION) {
    ActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTIONEffect();
    return;
  }
  if (gMonEffect.id == HARPIE_CHANNELER) {
    ActivateHARPIE_CHANNELEREffect();
    return;
  }
  if (gMonEffect.id == HARPIE_CONDUCTOR) {
    ActivateHARPIE_CONDUCTOREffect();
    return;
  }
  if (gMonEffect.id == HARPIE_DANCER) {
    ActivateHARPIE_DANCEREffect();
    return;
  }
  if (gMonEffect.id == HARPIE_HARPIST) {
    ActivateHARPIE_HARPISTEffect();
    return;
  }
  if (gMonEffect.id == HARPIE_ORACLE) {
    ActivateHARPIE_ORACLEEffect();
    return;
  }
  if (gMonEffect.id == HARPIE_QUEEN) {
    ActivateHARPIE_QUEENEffect();
    return;
  }
  if (gMonEffect.id == HELSHADDOLL_HOLLOW) {
    ActivateHELSHADDOLL_HOLLOWEffect();
    return;
  }
  if (gMonEffect.id == HERALD_OF_PERFECTION) {
    ActivateHERALD_OF_PERFECTIONEffect();
    return;
  }
  if (gMonEffect.id == HERALD_OF_ULTIMATENESS) {
    ActivateHERALD_OF_ULTIMATENESSEffect();
    return;
  }
  if (gMonEffect.id == ILLUSION_OF_CHAOS) {
    ActivateILLUSION_OF_CHAOSEffect();
    return;
  }
  if (gMonEffect.id == KEEPER_OF_DRAGON_MAGIC) {
    ActivateKEEPER_OF_DRAGON_MAGICEffect();
    return;
  }
  if (gMonEffect.id == LONEFIRE_BLOSSOM) {
    ActivateLONEFIRE_BLOSSOMEffect();
    return;
  }
  if (gMonEffect.id == MAGICIANS_ROBE) {
    ActivateMAGICIANS_ROBEEffect();
    return;
  }
  if (gMonEffect.id == MAGICIANS_SOULS) {
    ActivateMAGICIANS_SOULSEffect();
    return;
  }
  if (gMonEffect.id == MASTER_OF_CHAOS) {
    ActivateMASTER_OF_CHAOSEffect();
    return;
  }
  if (gMonEffect.id == MILLENNIUM_EYES_RESTRICT) {
    ActivateMILLENNIUM_EYES_RESTRICTEffect();
    return;
  }
  if (gMonEffect.id == NAELSHADDOLL_ARIEL) {
    ActivateNAELSHADDOLL_ARIELEffect();
    return;
  }
  if (gMonEffect.id == NEHSHADDOLL_GENIUS) {
    ActivateNEHSHADDOLL_GENIUSEffect();
    return;
  }
  if (gMonEffect.id == POWER_TOOL_DRAGON) {
    ActivatePOWER_TOOL_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == PREDAPLANT_VERTE_ANACONDA) {
    ActivatePREDAPLANT_VERTE_ANACONDAEffect();
    return;
  }
  if (gMonEffect.id == QADSHADDOLL_KEIOS) {
    ActivateQADSHADDOLL_KEIOSEffect();
    return;
  }
  if (gMonEffect.id == REESHADDOLL_WENDI) {
    ActivateREESHADDOLL_WENDIEffect();
    return;
  }
  if (gMonEffect.id == REESHADDOLL_WENDIKURUHU) {
    ActivateREESHADDOLL_WENDIKURUHUEffect();
    return;
  }
  if (gMonEffect.id == REPTILIANNE_ECHIDNA) {
    ActivateREPTILIANNE_ECHIDNAEffect();
    return;
  }
  if (gMonEffect.id == REPTILIANNE_LAMIA) {
    ActivateREPTILIANNE_LAMIAEffect();
    return;
  }
  if (gMonEffect.id == REPTILIANNE_MEDUSA) {
    ActivateREPTILIANNE_MEDUSAEffect();
    return;
  }
  if (gMonEffect.id == REPTILIANNE_VASKII) {
    ActivateREPTILIANNE_VASKIIEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_BEAST) {
    ActivateSHADDOLL_BEASTEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_DRAGON) {
    ActivateSHADDOLL_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_FALCO) {
    ActivateSHADDOLL_FALCOEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_HEDGEHOG) {
    ActivateSHADDOLL_HEDGEHOGEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_HOUND) {
    ActivateSHADDOLL_HOUNDEffect();
    return;
  }
  if (gMonEffect.id == SHADDOLL_SQUAMATA) {
    ActivateSHADDOLL_SQUAMATAEffect();
    return;
  }
  if (gMonEffect.id == STARDUST_DRAGON) {
    ActivateSTARDUST_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == TIMEAUS_THE_UNITED_DRAGON) {
    ActivateTIMEAUS_THE_UNITED_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == TOHUSHADDOLL_GRYSTA) {
    ActivateTOHUSHADDOLL_GRYSTAEffect();
    return;
  }
  if (gMonEffect.id == VENOM_BOA) {
    ActivateVENOM_BOAEffect();
    return;
  }
  if (gMonEffect.id == VENOM_SERPENT) {
    ActivateVENOM_SERPENTEffect();
    return;
  }
  if (gMonEffect.id == VENOM_SNAKE) {
    ActivateVENOM_SNAKEEffect();
    return;
  }
  if (gMonEffect.id == YAMORIMORI) {
    ActivateYAMORIMORIEffect();
    return;
  }
  if (gMonEffect.id == ARCANA_FORCE_V_THE_HIEROPHANT) {
    ActivateARCANA_FORCE_V_THE_HIEROPHANTEffect();
    return;
  }
  if (gMonEffect.id == ARCANA_FORCE_XII_THE_HANGMAN) {
    ActivateARCANA_FORCE_XII_THE_HANGMANEffect();
    return;
  }
  if (gMonEffect.id == ARCANA_FORCE_XIX_THE_SUN) {
    ActivateARCANA_FORCE_XIX_THE_SUNEffect();
    return;
  }
  if (gMonEffect.id == ARCANA_FORCE_XV_THE_FIEND) {
    ActivateARCANA_FORCE_XV_THE_FIENDEffect();
    return;
  }
  if (gMonEffect.id == ARMED_NEOS) {
    ActivateARMED_NEOSEffect();
    return;
  }
  if (gMonEffect.id == CELESTIA_LIGHTSWORN_ANGEL) {
    ActivateCELESTIA_LIGHTSWORN_ANGELEffect();
    return;
  }
  if (gMonEffect.id == CHRYSALIS_CHICKY) {
    ActivateCHRYSALIS_CHICKYEffect();
    return;
  }
  if (gMonEffect.id == CHRYSALIS_DOLPHIN) {
    ActivateCHRYSALIS_DOLPHINEffect();
    return;
  }
  if (gMonEffect.id == CHRYSALIS_MOLE) {
    ActivateCHRYSALIS_MOLEEffect();
    return;
  }
  if (gMonEffect.id == CHRYSALIS_PANTAIL) {
    ActivateCHRYSALIS_PANTAILEffect();
    return;
  }
  if (gMonEffect.id == CHRYSALIS_PINNY) {
    ActivateCHRYSALIS_PINNYEffect();
    return;
  }
  if (gMonEffect.id == CROSS_KEEPER) {
    ActivateCROSS_KEEPEREffect();
    return;
  }
  if (gMonEffect.id == CURIOUS_THE_LIGHTSWORN_DOMINION) {
    ActivateCURIOUS_THE_LIGHTSWORN_DOMINIONEffect();
    return;
  }
  if (gMonEffect.id == EHREN_LIGHTSWORN_MONK) {
    ActivateEHREN_LIGHTSWORN_MONKEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_AQUA_NEOS) {
    ActivateELEMENTAL_HERO_AQUA_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_BRAVE_NEOS) {
    ActivateELEMENTAL_HERO_BRAVE_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_CHAOS_NEOS) {
    ActivateELEMENTAL_HERO_CHAOS_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_COSMO_NEOS) {
    ActivateELEMENTAL_HERO_COSMO_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_DARK_NEOS) {
    ActivateELEMENTAL_HERO_DARK_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_GLOW_NEOS) {
    ActivateELEMENTAL_HERO_GLOW_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_GRAND_NEOS) {
    ActivateELEMENTAL_HERO_GRAND_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_MAGMA_NEOS) {
    ActivateELEMENTAL_HERO_MAGMA_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_MARINE_NEOS) {
    ActivateELEMENTAL_HERO_MARINE_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_NEBULA_NEOS) {
    ActivateELEMENTAL_HERO_NEBULA_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_SHINING_NEOS_WINGMAN) {
    ActivateELEMENTAL_HERO_SHINING_NEOS_WINGMANEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_SPIRIT_OF_NEOS) {
    ActivateELEMENTAL_HERO_SPIRIT_OF_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ELEMENTAL_HERO_STORM_NEOS) {
    ActivateELEMENTAL_HERO_STORM_NEOSEffect();
    return;
  }
  if (gMonEffect.id == ENLIGHTENMENT_DRAGON) {
    ActivateENLIGHTENMENT_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == FELIS_LIGHTSWORN_ARCHER) {
    ActivateFELIS_LIGHTSWORN_ARCHEREffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_ANDABATA) {
    ActivateGLADIATOR_BEAST_ANDABATAEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_ATTORIX) {
    ActivateGLADIATOR_BEAST_ATTORIXEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_AUGUSTUS) {
    ActivateGLADIATOR_BEAST_AUGUSTUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_BESTIARI) {
    ActivateGLADIATOR_BEAST_BESTIARIEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_CLAUDIUS) {
    ActivateGLADIATOR_BEAST_CLAUDIUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_DAREIOS) {
    ActivateGLADIATOR_BEAST_DAREIOSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_DARIUS) {
    ActivateGLADIATOR_BEAST_DARIUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_DOMITIANUS) {
    ActivateGLADIATOR_BEAST_DOMITIANUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_DRAGASES) {
    ActivateGLADIATOR_BEAST_DRAGASESEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_EQUESTE) {
    ActivateGLADIATOR_BEAST_EQUESTEEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_GISTEL) {
    ActivateGLADIATOR_BEAST_GISTELEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_GYZARUS) {
    ActivateGLADIATOR_BEAST_GYZARUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_HERAKLINOS) {
    ActivateGLADIATOR_BEAST_HERAKLINOSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_HOPLOMUS) {
    ActivateGLADIATOR_BEAST_HOPLOMUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_LANISTA) {
    ActivateGLADIATOR_BEAST_LANISTAEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_LAQUARI) {
    ActivateGLADIATOR_BEAST_LAQUARIEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_MURMILLO) {
    ActivateGLADIATOR_BEAST_MURMILLOEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_NEROKIUS) {
    ActivateGLADIATOR_BEAST_NEROKIUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_NOXIOUS) {
    ActivateGLADIATOR_BEAST_NOXIOUSEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_SAGITTARII) {
    ActivateGLADIATOR_BEAST_SAGITTARIIEffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_TAMER_EDITOR) {
    ActivateGLADIATOR_BEAST_TAMER_EDITOREffect();
    return;
  }
  if (gMonEffect.id == GLADIATOR_BEAST_VESPASIUS) {
    ActivateGLADIATOR_BEAST_VESPASIUSEffect();
    return;
  }
  if (gMonEffect.id == JAIN_LIGHTSWORN_PALADIN) {
    ActivateJAIN_LIGHTSWORN_PALADINEffect();
    return;
  }
  if (gMonEffect.id == JAIN_TWILIGHTSWORN_GENERAL) {
    ActivateJAIN_TWILIGHTSWORN_GENERALEffect();
    return;
  }
  if (gMonEffect.id == JUDGMENT_THE_DRAGON_OF_HEAVEN) {
    ActivateJUDGMENT_THE_DRAGON_OF_HEAVENEffect();
    return;
  }
  if (gMonEffect.id == LIGHTSWORN_DRAGONLING) {
    ActivateLIGHTSWORN_DRAGONLINGEffect();
    return;
  }
  if (gMonEffect.id == LUMINA_LIGHTSWORN_SUMMONER) {
    ActivateLUMINA_LIGHTSWORN_SUMMONEREffect();
    return;
  }
  if (gMonEffect.id == LUMINA_TWILIGHTSWORN_SHAMAN) {
    ActivateLUMINA_TWILIGHTSWORN_SHAMANEffect();
    return;
  }
  if (gMonEffect.id == LYLA_LIGHTSWORN_SORCERESS) {
    ActivateLYLA_LIGHTSWORN_SORCERESSEffect();
    return;
  }
  if (gMonEffect.id == LYLA_TWILIGHTSWORN_ENCHANTRESS) {
    ActivateLYLA_TWILIGHTSWORN_ENCHANTRESSEffect();
    return;
  }
  if (gMonEffect.id == MICHAEL_THE_ARCH_LIGHTSWORN) {
    ActivateMICHAEL_THE_ARCH_LIGHTSWORNEffect();
    return;
  }
  if (gMonEffect.id == MINERVA_LIGHTSWORN_MAIDEN) {
    ActivateMINERVA_LIGHTSWORN_MAIDENEffect();
    return;
  }
  if (gMonEffect.id == MINERVA_THE_ATHENIAN_LIGHTSWORN) {
    ActivateMINERVA_THE_ATHENIAN_LIGHTSWORNEffect();
    return;
  }
  if (gMonEffect.id == MINERVA_THE_EXHALTED_LIGHTSWORN) {
    ActivateMINERVA_THE_EXHALTED_LIGHTSWORNEffect();
    return;
  }
  if (gMonEffect.id == NEO_SPACE_CONNECTOR) {
    ActivateNEO_SPACE_CONNECTOREffect();
    return;
  }
  if (gMonEffect.id == NEO_SPACIAN_AIR_HUMMINGBIRD) {
    ActivateNEO_SPACIAN_AIR_HUMMINGBIRDEffect();
    return;
  }
  if (gMonEffect.id == NEO_SPACIAN_AQUA_DOLPHIN) {
    ActivateNEO_SPACIAN_AQUA_DOLPHINEffect();
    return;
  }
  if (gMonEffect.id == NEO_SPACIAN_DARK_PANTHER) {
    ActivateNEO_SPACIAN_DARK_PANTHEREffect();
    return;
  }
  if (gMonEffect.id == NEO_SPACIAN_MARINE_DOLPHIN) {
    ActivateNEO_SPACIAN_MARINE_DOLPHINEffect();
    return;
  }
  if (gMonEffect.id == PUNISHMENT_DRAGON) {
    ActivatePUNISHMENT_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == RAIDEN_HAND_OF_THE_LIGHTSWORN) {
    ActivateRAIDEN_HAND_OF_THE_LIGHTSWORNEffect();
    return;
  }
  if (gMonEffect.id == RESCUE_CAT) {
    ActivateRESCUE_CATEffect();
    return;
  }
  if (gMonEffect.id == RESCUE_RABBIT) {
    ActivateRESCUE_RABBITEffect();
    return;
  }
  if (gMonEffect.id == RINYAN_LIGHTSWORN_ROGUE) {
    ActivateRINYAN_LIGHTSWORN_ROGUEEffect();
    return;
  }
  if (gMonEffect.id == RYKO_LIGHTSWORN_HUNTER) {
    ActivateRYKO_LIGHTSWORN_HUNTEREffect();
    return;
  }
  if (gMonEffect.id == RYKO_TWILIGHTSWORN_FIGHTER) {
    ActivateRYKO_TWILIGHTSWORN_FIGHTEREffect();
    return;
  }
  if (gMonEffect.id == TEST_BEAR) {
    ActivateTEST_BEAREffect();
    return;
  }
  if (gMonEffect.id == TEST_PANTHER) {
    ActivateTEST_PANTHEREffect();
    return;
  }
  if (gMonEffect.id == TEST_TIGER) {
    ActivateTEST_TIGEREffect();
    return;
  }
  if (gMonEffect.id == WEISS_LIGHTSWORN_ARCHFIEND) {
    ActivateWEISS_LIGHTSWORN_ARCHFIENDEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_FAIRY_DRAGON) {
    ActivateANCIENT_FAIRY_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR) {
    ActivateANCIENT_GEAREffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_BEAST) {
    ActivateANCIENT_GEAR_BEASTEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_CANNON) {
    ActivateANCIENT_GEAR_CANNONEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_COMMANDER) {
    ActivateANCIENT_GEAR_COMMANDEREffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_DARK_GOLEM) {
    ActivateANCIENT_GEAR_DARK_GOLEMEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_DRAGON) {
    ActivateANCIENT_GEAR_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_ENGINEER) {
    ActivateANCIENT_GEAR_ENGINEEREffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_FRAME) {
    ActivateANCIENT_GEAR_FRAMEEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_GADJILTRON_CHIMERA) {
    ActivateANCIENT_GEAR_GADJILTRON_CHIMERAEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_GADJILTRON_DRAGON) {
    ActivateANCIENT_GEAR_GADJILTRON_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_GOLEM) {
    ActivateANCIENT_GEAR_GOLEMEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND) {
    ActivateANCIENT_GEAR_GOLEM_ULTIMATE_POUNDEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_KNIGHT) {
    ActivateANCIENT_GEAR_KNIGHTEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_MEGATON_GOLEM) {
    ActivateANCIENT_GEAR_MEGATON_GOLEMEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_SOLDIER) {
    ActivateANCIENT_GEAR_SOLDIEREffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_STATUE) {
    ActivateANCIENT_GEAR_STATUEEffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_GEAR_TANKER) {
    ActivateANCIENT_GEAR_TANKEREffect();
    return;
  }
  if (gMonEffect.id == ANCIENT_SACRED_WYVERN) {
    ActivateANCIENT_SACRED_WYVERNEffect();
    return;
  }
  if (gMonEffect.id == ARCANA_KNIGHT_JOKER) {
    ActivateARCANA_KNIGHT_JOKEREffect();
    return;
  }
  if (gMonEffect.id == ARMITYLE_THE_CHAOS_PHANTASM) {
    ActivateARMITYLE_THE_CHAOS_PHANTASMEffect();
    return;
  }
  if (gMonEffect.id == BABYCERASAURUS) {
    ActivateBABYCERASAURUSEffect();
    return;
  }
  if (gMonEffect.id == BARRIER_STATUE_OF_THE_STORMWINDS) {
    ActivateBARRIER_STATUE_OF_THE_STORMWINDSEffect();
    return;
  }
  if (gMonEffect.id == BLACK_WINGED_DRAGON) {
    ActivateBLACK_WINGED_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BEAST_MACHINE_KING_BARBAROS_UR) {
    ActivateBEAST_MACHINE_KING_BARBAROS_UREffect();
    return;
  }
  if (gMonEffect.id == CHAOS_ANCIENT_GEAR_GIANT) {
    ActivateCHAOS_ANCIENT_GEAR_GIANTEffect();
    return;
  }
  if (gMonEffect.id == CORAL_DRAGON) {
    ActivateCORAL_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == CRIMSON_BLADER) {
    ActivateCRIMSON_BLADEREffect();
    return;
  }
  if (gMonEffect.id == CRIMSON_DRAGON) {
    ActivateCRIMSON_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == CYBER_DRAGON_INFINITY) {
    ActivateCYBER_DRAGON_INFINITYEffect();
    return;
  }
  if (gMonEffect.id == CYBER_SLASH_HARPY_LADY) {
    ActivateCYBER_SLASH_HARPY_LADYEffect();
    return;
  }
  if (gMonEffect.id == DARK_HORUS) {
    ActivateDARK_HORUSEffect();
    return;
  }
  if (gMonEffect.id == DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE) {
    ActivateDARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICEEffect();
    return;
  }
  if (gMonEffect.id == DARKBLAZE_DRAGON) {
    ActivateDARKBLAZE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == BOOT_UP_SOLDIER_DREAD_DYNAMO) {
    ActivateBOOT_UP_SOLDIER_DREAD_DYNAMOEffect();
    return;
  }
  if (gMonEffect.id == CASTEL_THE_SKY_BLASTER_MUSKETEER) {
    ActivateCASTEL_THE_SKY_BLASTER_MUSKETEEREffect();
    return;
  }
  if (gMonEffect.id == DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS) {
    ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOSEffect();
    return;
  }
  if (gMonEffect.id == DEMISE_KING_OF_ARMAGEDDON) {
    ActivateDEMISE_KING_OF_ARMAGEDDONEffect();
    return;
  }
  if (gMonEffect.id == EVOLZAR_DOLKKA) {
    ActivateEVOLZAR_DOLKKAEffect();
    return;
  }
  if (gMonEffect.id == FLAME_RULER) {
    ActivateFLAME_RULEREffect();
    return;
  }
  if (gMonEffect.id == FORMULA_SYNCHRON) {
    ActivateFORMULA_SYNCHRONEffect();
    return;
  }
  if (gMonEffect.id == GANDORA_X_THE_DRAGON_OF_DESTRUCTION) {
    ActivateGANDORA_X_THE_DRAGON_OF_DESTRUCTIONEffect();
    return;
  }
  if (gMonEffect.id == GREAT_POSEIDON_BEETLE) {
    ActivateGREAT_POSEIDON_BEETLEEffect();
    return;
  }
  if (gMonEffect.id == GREEN_BABOON_DEFENDER_OF_THE_FOREST) {
    ActivateGREEN_BABOON_DEFENDER_OF_THE_FORESTEffect();
    return;
  }
  if (gMonEffect.id == GUNGNIR_DRAGON_OF_THE_ICE_BARRIER) {
    ActivateGUNGNIR_DRAGON_OF_THE_ICE_BARRIEREffect();
    return;
  }
  if (gMonEffect.id == HERALD_OF_THE_ARC_LIGHT) {
    ActivateHERALD_OF_THE_ARC_LIGHTEffect();
    return;
  }
  if (gMonEffect.id == HERALD_OF_ULIMATENESS) {
    ActivateHERALD_OF_ULIMATENESSEffect();
    return;
  }
  if (gMonEffect.id == HONEST) {
    ActivateHONESTEffect();
    return;
  }
  if (gMonEffect.id == JUNK_SYNCHRON) {
    if (CanActivateJUNK_SYNCHRON())
      ActivateJUNK_SYNCHRONEffect();
    gMonEffect.id = CARD_NONE;
    return;
  }
  if (gMonEffect.id == LEVIAIR_THE_SEA_DRAGON) {
    ActivateLEVIAIR_THE_SEA_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == LIFE_STREAM_DRAGON) {
    ActivateLIFE_STREAM_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == MAGICAL_MARIONETTE) {
    ActivateMAGICAL_MARIONETTEEffect();
    return;
  }
  if (gMonEffect.id == MAGNA_DRAGO) {
    ActivateMAGNA_DRAGOEffect();
    return;
  }
  if (gMonEffect.id == MIRAGE_DRAGON) {
    ActivateMIRAGE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == MONTAGE_DRAGON) {
    ActivateMONTAGE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_BOARDEN) {
    ActivateMORPHTRONIC_BOARDENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_BOOMBOXEN) {
    ActivateMORPHTRONIC_BOOMBOXENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_CAMERAN) {
    ActivateMORPHTRONIC_CAMERANEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_CELFON) {
    ActivateMORPHTRONIC_CELFONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_CLOCKEN) {
    ActivateMORPHTRONIC_CLOCKENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_DATATRON) {
    ActivateMORPHTRONIC_DATATRONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_EARFON) {
    ActivateMORPHTRONIC_EARFONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_LANTRON) {
    ActivateMORPHTRONIC_LANTRONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_MAGNEN) {
    ActivateMORPHTRONIC_MAGNENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_MAGNEN_BAR) {
    ActivateMORPHTRONIC_MAGNEN_BAREffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_RADION) {
    ActivateMORPHTRONIC_RADIONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_REMOTEN) {
    ActivateMORPHTRONIC_REMOTENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_SCANNEN) {
    ActivateMORPHTRONIC_SCANNENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_SCOPEN) {
    ActivateMORPHTRONIC_SCOPENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_SLINGEN) {
    ActivateMORPHTRONIC_SLINGENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_SMARTFON) {
    ActivateMORPHTRONIC_SMARTFONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_STAPLEN) {
    ActivateMORPHTRONIC_STAPLENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_TELEFON) {
    ActivateMORPHTRONIC_TELEFONEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_VACUUMEN) {
    ActivateMORPHTRONIC_VACUUMENEffect();
    return;
  }
  if (gMonEffect.id == MORPHTRONIC_VIDEON) {
    ActivateMORPHTRONIC_VIDEONEffect();
    return;
  }
  if (gMonEffect.id == NATURIA_BEAST) {
    ActivateNATURIA_BEASTEffect();
    return;
  }
  if (gMonEffect.id == NITRO_WARRIOR) {
    ActivateNITRO_WARRIOREffect();
    return;
  }
  if (gMonEffect.id == POWER_TOOL_BRAVER_DRAGON) {
    ActivatePOWER_TOOL_BRAVER_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == RAINBOW_DARK_DRAGON) {
    ActivateRAINBOW_DARK_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == ROAD_SYNCHRON) {
    ActivateROAD_SYNCHRONEffect();
    return;
  }
  if (gMonEffect.id == ROAD_WARRIOR) {
    ActivateROAD_WARRIOREffect();
    return;
  }
  if (gMonEffect.id == SILENT_MAGICIAN_LV4) {
    ActivateSILENT_MAGICIAN_LV4Effect();
    return;
  }
  if (gMonEffect.id == SILENT_MAGICIAN_LV8) {
    ActivateSILENT_MAGICIAN_LV8Effect();
    return;
  }
  if (gMonEffect.id == SIMORGH_BIRD_OF_ANCESTRY) {
    ActivateSIMORGH_BIRD_OF_ANCESTRYEffect();
    return;
  }
  if (gMonEffect.id == SPELL_STRIKER) {
    ActivateSPELL_STRIKEREffect();
    return;
  }
  if (gMonEffect.id == T_G_HYPER_LIBRARIAN) {
    ActivateT_G_HYPER_LIBRARIANEffect();
    return;
  }
  if (gMonEffect.id == TATSUNOKO) {
    ActivateTATSUNOKOEffect();
    return;
  }
  if (gMonEffect.id == TIME_THIEF_REDOER) {
    ActivateTIME_THIEF_REDOEREffect();
    return;
  }
  if (gMonEffect.id == TRISHULA_DRAGON_OF_THE_ICE_BARRIER) {
    ActivateTRISHULA_DRAGON_OF_THE_ICE_BARRIEREffect();
    return;
  }
  if (gMonEffect.id == TUNINGWARE) {
    ActivateTUNINGWAREEffect();
    return;
  }
  if (gMonEffect.id == TURBO_BOOSTER) {
    ActivateTURBO_BOOSTEREffect();
    return;
  }
  if (gMonEffect.id == TURBO_CANNON) {
    ActivateTURBO_CANNONEffect();
    return;
  }
  if (gMonEffect.id == TURBO_ROCKET) {
    ActivateTURBO_ROCKETEffect();
    return;
  }
  if (gMonEffect.id == TURBO_SYNCHRON) {
    ActivateTURBO_SYNCHRONEffect();
    return;
  }
  if (gMonEffect.id == TYRANNO_INFINITY) {
    ActivateTYRANNO_INFINITYEffect();
    return;
  }
  if (gMonEffect.id == ULTIMATE_ANCIENT_GEAR_GOLEM) {
    ActivateULTIMATE_ANCIENT_GEAR_GOLEMEffect();
    return;
  }
  if (gMonEffect.id == ULTIMATE_TYRANNO) {
    ActivateULTIMATE_TYRANNOEffect();
    return;
  }
  if (gMonEffect.id == WARRIOR_OF_ATLANTIS) {
    ActivateWARRIOR_OF_ATLANTISEffect();
    return;
  }
  if (gMonEffect.id == X_SABER_AIRBELLUM) {
    ActivateX_SABER_AIRBELLUMEffect();
    return;
  }
  if (gMonEffect.id == A_CAT_OF_ILL_OMEN) {
    ActivateA_CAT_OF_ILL_OMENEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_AUGUSTA) {
    ActivateAMAZONESS_AUGUSTAEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_BABY_TIGER) {
    ActivateAMAZONESS_BABY_TIGEREffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_EMPRESS) {
    ActivateAMAZONESS_EMPRESSEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_PET_LIGER) {
    ActivateAMAZONESS_PET_LIGEREffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_PET_LIGER_KING) {
    ActivateAMAZONESS_PET_LIGER_KINGEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_PRINCESS) {
    ActivateAMAZONESS_PRINCESSEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_QUEEN) {
    ActivateAMAZONESS_QUEENEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_SAGE) {
    ActivateAMAZONESS_SAGEEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_SCOUTS) {
    ActivateAMAZONESS_SCOUTSEffect();
    return;
  }
  if (gMonEffect.id == ALECTOR_SOVEREIGN_OF_BIRDS) {
    ActivateALECTOR_SOVEREIGN_OF_BIRDSEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_SPIRITUALIST) {
    ActivateAMAZONESS_SPIRITUALISTEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_SPY) {
    ActivateAMAZONESS_SPYEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_TRAINEE) {
    ActivateAMAZONESS_TRAINEEEffect();
    return;
  }
  if (gMonEffect.id == AMAZONESS_WAR_CHIEF) {
    ActivateAMAZONESS_WAR_CHIEFEffect();
    return;
  }
  if (gMonEffect.id == AN_OWL_OF_LUCK) {
    ActivateAN_OWL_OF_LUCKEffect();
    return;
  }
  if (gMonEffect.id == ATLANTEAN_ATTACK_SQUAD) {
    ActivateATLANTEAN_ATTACK_SQUADEffect();
    return;
  }
  if (gMonEffect.id == ATLANTEAN_DRAGOONS) {
    ActivateATLANTEAN_DRAGOONSEffect();
    return;
  }
  if (gMonEffect.id == ATLANTEAN_HEAVY_INFANTRY) {
    ActivateATLANTEAN_HEAVY_INFANTRYEffect();
    return;
  }
  if (gMonEffect.id == ATLANTEAN_MARKSMAN) {
    ActivateATLANTEAN_MARKSMANEffect();
    return;
  }
  if (gMonEffect.id == BEAST_KING_BARBAROS) {
    ActivateBEAST_KING_BARBAROSEffect();
    return;
  }
  if (gMonEffect.id == CELESTIAL_KNIGHTLORD_PARSHATH) {
    ActivateCELESTIAL_KNIGHTLORD_PARSHATHEffect();
    return;
  }
  if (gMonEffect.id == CHAINSAW_INSECT) {
    ActivateCHAINSAW_INSECTEffect();
    return;
  }
  if (gMonEffect.id == CHARM_OF_SHABTI) {
    ActivateCHARM_OF_SHABTIEffect();
    return;
  }
  if (gMonEffect.id == BAZOO_THE_SOUL_EATER) {
    ActivateBAZOO_THE_SOUL_EATEREffect();
    return;
  }
  if (gMonEffect.id == ASH_BLOSSOM_AND_JOYOUS_SPRING) {
    ActivateASH_BLOSSOM_AND_JOYOUS_SPRINGEffect();
    return;
  }
  if (gMonEffect.id == CLEAR_VICE_DRAGON) {
    ActivateCLEAR_VICE_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == CYBERNETIC_MAGICIAN) {
    ActivateCYBERNETIC_MAGICIANEffect();
    return;
  }
  if (gMonEffect.id == DARKLORD_DESIRE) {
    ActivateDARKLORD_DESIREEffect();
    return;
  }
  if (gMonEffect.id == DEEP_SEA_DIVA) {
    ActivateDEEP_SEA_DIVAEffect();
    return;
  }
  if (gMonEffect.id == DIVINER_OF_THE_HERALD) {
    ActivateDIVINER_OF_THE_HERALDEffect();
    return;
  }
  if (gMonEffect.id == ELDER_ENTITY_NORDEN) {
    ActivateELDER_ENTITY_NORDENEffect();
    return;
  }
  if (gMonEffect.id == ENRAGED_BATTLE_OX) {
    ActivateENRAGED_BATTLE_OXEffect();
    return;
  }
  if (gMonEffect.id == FOG_KING) {
    ActivateFOG_KINGEffect();
    return;
  }
  if (gMonEffect.id == GAGAGIGO_THE_RISEN) {
    ActivateGAGAGIGO_THE_RISENEffect();
    return;
  }
  if (gMonEffect.id == GOLDEN_HOMUNCULUS) {
    ActivateGOLDEN_HOMUNCULUSEffect();
    return;
  }
  if (gMonEffect.id == FUSILIER_DRAGON_THE_DUAL_MODE_BEAST) {
    ActivateFUSILIER_DRAGON_THE_DUAL_MODE_BEASTEffect();
    return;
  }
  if (gMonEffect.id == GAMECIAL_THE_SEA_TURTLE_KAIJU) {
    ActivateGAMECIAL_THE_SEA_TURTLE_KAIJUEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_AMBUSHER) {
    ActivateGRAVEKEEPERS_AMBUSHEREffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_CANNONHOLDER) {
    ActivateGRAVEKEEPERS_CANNONHOLDEREffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_CHIEF) {
    ActivateGRAVEKEEPERS_CHIEFEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_COMMANDANT) {
    ActivateGRAVEKEEPERS_COMMANDANTEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_CURSE) {
    ActivateGRAVEKEEPERS_CURSEEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_DESCENDANT) {
    ActivateGRAVEKEEPERS_DESCENDANTEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_GUARD) {
    ActivateGRAVEKEEPERS_GUARDEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_HEADMAN) {
    ActivateGRAVEKEEPERS_HEADMANEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_HERATIC) {
    ActivateGRAVEKEEPERS_HERATICEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_NOBLEMAN) {
    ActivateGRAVEKEEPERS_NOBLEMANEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_ORACLE) {
    ActivateGRAVEKEEPERS_ORACLEEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_PRIESTESS) {
    ActivateGRAVEKEEPERS_PRIESTESSEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_RECRUITER) {
    ActivateGRAVEKEEPERS_RECRUITEREffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_SHAMAN) {
    ActivateGRAVEKEEPERS_SHAMANEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_SPEAR_SOLDIER) {
    ActivateGRAVEKEEPERS_SPEAR_SOLDIEREffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_SPIRITUALIST) {
    ActivateGRAVEKEEPERS_SPIRITUALISTEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_SPY) {
    ActivateGRAVEKEEPERS_SPYEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_SUPERNATURALIST) {
    ActivateGRAVEKEEPERS_SUPERNATURALISTEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_VASSAL) {
    ActivateGRAVEKEEPERS_VASSALEffect();
    return;
  }
  if (gMonEffect.id == HELIOS_DUO_MEGISTUS) {
    ActivateHELIOS_DUO_MEGISTUSEffect();
    return;
  }
  if (gMonEffect.id == HELIOS_THE_PRIMORDIAL_SUN) {
    ActivateHELIOS_THE_PRIMORDIAL_SUNEffect();
    return;
  }
  if (gMonEffect.id == HELIOS_TRICE_MEGISTUS) {
    ActivateHELIOS_TRICE_MEGISTUSEffect();
    return;
  }
  if (gMonEffect.id == LADY_OF_D) {
    ActivateLADY_OF_DEffect();
    return;
  }
  if (gMonEffect.id == LEVEL_EATER) {
    ActivateLEVEL_EATEREffect();
    return;
  }
  if (gMonEffect.id == LIGHTRAY_DAEDALUS) {
    ActivateLIGHTRAY_DAEDALUSEffect();
    return;
  }
  if (gMonEffect.id == LIGHTRAY_GEARFRIED) {
    ActivateLIGHTRAY_GEARFRIEDEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_VISIONARY) {
    ActivateGRAVEKEEPERS_VISIONARYEffect();
    return;
  }
  if (gMonEffect.id == GRAVEKEEPERS_WATCHER) {
    ActivateGRAVEKEEPERS_WATCHEREffect();
    return;
  }
  if (gMonEffect.id == MAJESTY_HYPERION) {
    ActivateMAJESTY_HYPERIONEffect();
    return;
  }
  if (gMonEffect.id == MASTER_HYPERION) {
    ActivateMASTER_HYPERIONEffect();
    return;
  }
  if (gMonEffect.id == MASTERFLARE_HYPERION) {
    ActivateMASTERFLARE_HYPERIONEffect();
    return;
  }
  if (gMonEffect.id == MEZUKI) {
    ActivateMEZUKIEffect();
    return;
  }
  if (gMonEffect.id == NECROFACE) {
    ActivateNECROFACEEffect();
    return;
  }
  if (gMonEffect.id == NUMBER_39_UTOPIA) {
    ActivateNUMBER_39_UTOPIAEffect();
    return;
  }
  if (gMonEffect.id == OCEAN_DRAGON_LORD_NEO_DAEDALUS) {
    ActivateOCEAN_DRAGON_LORD_NEO_DAEDALUSEffect();
    return;
  }
  if (gMonEffect.id == POSEIDRA_THE_ATLANTEAN_DRAGON) {
    ActivatePOSEIDRA_THE_ATLANTEAN_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == PROTECTOR_OF_THE_AGENTS_MOON) {
    ActivatePROTECTOR_OF_THE_AGENTS_MOONEffect();
    return;
  }
  if (gMonEffect.id == MAXX_C) {
    ActivateMAXX_CEffect();
    return;
  }
  if (gMonEffect.id == SILENT_SWORDSMAN) {
    ActivateSILENT_SWORDSMANEffect();
    return;
  }
  if (gMonEffect.id == SILENT_SWORDSMAN_LV3) {
    ActivateSILENT_SWORDSMAN_LV3Effect();
    return;
  }
  if (gMonEffect.id == SILENT_SWORDSMAN_LV5) {
    ActivateSILENT_SWORDSMAN_LV5Effect();
    return;
  }
  if (gMonEffect.id == SILENT_SWORDSMAN_LV7) {
    ActivateSILENT_SWORDSMAN_LV7Effect();
    return;
  }
  if (gMonEffect.id == SILENT_SWORDSMAN_ZERO) {
    ActivateSILENT_SWORDSMAN_ZEROEffect();
    return;
  }
  if (gMonEffect.id == SOUL_ABSORBING_BONE_TOWER) {
    ActivateSOUL_ABSORBING_BONE_TOWEREffect();
    return;
  }
  if (gMonEffect.id == SPINED_GILLMAN) {
    ActivateSPINED_GILLMANEffect();
    return;
  }
  if (gMonEffect.id == SUBSTITOAD) {
    ActivateSUBSTITOADEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_DESTRUCTION_VENUS) {
    ActivateTHE_AGENT_OF_DESTRUCTION_VENUSEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_ENTROPY_URANUS) {
    ActivateTHE_AGENT_OF_ENTROPY_URANUSEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_LIFE_NEPTUNE) {
    ActivateTHE_AGENT_OF_LIFE_NEPTUNEEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_MIRACLES_JUPITER) {
    ActivateTHE_AGENT_OF_MIRACLES_JUPITEREffect();
    return;
  }
  if (gMonEffect.id == THE_CALCULATOR) {
    ActivateTHE_CALCULATOREffect();
    return;
  }
  if (gMonEffect.id == THE_EXECUTOR_OF_THE_UNDERWORLD_PLUTO) {
    ActivateTHE_EXECUTOR_OF_THE_UNDERWORLD_PLUTOEffect();
    return;
  }
  if (gMonEffect.id == THUNDER_END_DRAGON) {
    ActivateTHUNDER_END_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == TOADALLY_AWESOME) {
    ActivateTOADALLY_AWESOMEEffect();
    return;
  }
  if (gMonEffect.id == TREEBORN_FROG) {
    ActivateTREEBORN_FROGEffect();
    return;
  }
  if (gMonEffect.id == TROOP_DRAGON) {
    ActivateTROOP_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == TUALATIN) {
    ActivateTUALATINEffect();
    return;
  }
  if (gMonEffect.id == VICTORIA) {
    ActivateVICTORIAEffect();
    return;
  }
  if (gMonEffect.id == WARM_WORM) {
    ActivateWARM_WORMEffect();
    return;
  }
  if (gMonEffect.id == WHITE_HORNED_DRAGON) {
    ActivateWHITE_HORNED_DRAGONEffect();
    return;
  }
  if (gMonEffect.id == ZERADIAS_HERALD_OF_HEAVEN) {
    ActivateZERADIAS_HERALD_OF_HEAVENEffect();
    return;
  }
  if (gMonEffect.id == THE_AGENT_OF_MYSTERU_EARTH) {
    ActivateTHE_AGENT_OF_MYSTERU_EARTHEffect();
    return;
  }
}
/* END MONSTER EFFECT DISPATCH */