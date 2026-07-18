#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "dynamic_equip.h"
#include "graveyard_effects.h"
#include "yubel.h"
#include "elemental_hero_flash.h"
#include "familiar_knight.h"
#include "giant_rat.h"
#include "the_thing_in_the_crater.h"
#include "pyramid_of_light.h"
#include "dark_magician_knight.h"
#include "zaborg_the_thunder_monarch.h"
#include "caius_the_shadow_monarch.h"
#include "mobius_the_frost_monarch.h"
#include "kaiser_glider.h"
#include "elemental_hero_core.h"
#include "moister_creature.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "the_tyrant_neptune.h"
#include "the_big_saturn.h"
#include "the_tripper_mercury.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "imperial_order.h"
#include "arsenal_bug.h"
#include "berserk_gorilla.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "duel_helpers.h"
#include "duel_attack_restrictions.h"
#include "ring_of_destruction.h"
#include "dark_dust_spirit.h"
#include "harpie_lady_2.h"
#include "ai_sim.h"
#include "card.h"

extern void (*sPermanentEffects[])(void);
extern unsigned char (*g8E0C800[])(void);

void TryActivatingPermanentEffects(void);
void sub_802ACC0(void);
void sub_802ADF4(void);
void sub_80408BC(void);
void sub_802ADA4(void);
void sub_802AE44(void);
void UpdateDuelGfxExceptField(void);
void ResetTempStagesForAllCards(void);
void AddTributeCredit(u16 tributeCardId);
u8 DoubleCostonCoversDarkTributeSummon(u16 summonCardId, u16 tributeCardId);

typedef unsigned char (*PermanentEffectCondition)(void);
typedef void (*PermanentEffectHandler)(void);

typedef struct {
  u16 cardId;
  PermanentEffectCondition shouldActivate;
  PermanentEffectHandler activate;
} PermanentEffectOverride;

unsigned char ShouldActivateMilusRadiant(void);
void ActivateMilusRadiant(void);
unsigned char ShouldActivateMukaMuka(void);
void ActivateMukaMuka(void);
unsigned char ShouldActivateCeremonialBell(void);
void ActivateCeremonialBell(void);
unsigned char ShouldActivateBlueEyesShiningDragon(void);
void ActivateBlueEyesShiningDragon(void);
unsigned char ShouldActivateSpellCanceller(void);
void ActivateSpellCanceller(void);
unsigned char ShouldActivateYamataDragon(void);
void ActivateYamataDragon(void);
unsigned char ShouldActivateMaraudingCaptain(void);
void ActivateMaraudingCaptain(void);
unsigned char ShouldActivatePetenTheDarkClown(void);
void ActivatePetenTheDarkClown(void);
unsigned char ShouldActivateYubelEvolution(void);
void ActivateYubelEvolution(void);
unsigned char ShouldActivateYubelTerrorEvolution(void);
void ActivateYubelTerrorEvolution(void);
unsigned char ShouldActivateGiantRat(void);
void ActivateGiantRat(void);
unsigned char ShouldActivateTheThingInTheCrater(void);
void ActivateTheThingInTheCrater(void);
unsigned char ShouldActivateGrenMajuDaEiza(void);
void ActivateGrenMajuDaEiza(void);
unsigned char ShouldActivateDesFeralImp(void);
void ActivateDesFeralImp(void);
unsigned char ShouldActivateDARK_MAGICIAN_OF_CHAOS(void);
void ActivateDARK_MAGICIAN_OF_CHAOS(void);
unsigned char ShouldActivateArsenalBug(void);
void ActivateArsenalBug(void);
unsigned char ShouldActivateGranadora(void);
void ActivateGranadora(void);
unsigned char ShouldActivateTheBigSaturn(void);
void ActivateTheBigSaturn(void);
unsigned char ShouldActivateBurningAlgae(void);
void ActivateBurningAlgae(void);
unsigned char ShouldActivateBerserkGorilla(void);
unsigned char ShouldActivateMobiusTheFrostMonarch(void);
void ActivateMobiusTheFrostMonarch(void);
void ActivateBerserkGorilla(void);
unsigned char ShouldActivateElementalHeroCaptainGold(void);
void ActivateElementalHeroCaptainGold(void);
unsigned char ShouldActivateTheWickedAvatar(void);
void ActivateTheWickedAvatar(void);
u8 TryAutoSummonBlueEyesShiningDragon(void);
u8 TryAutoSummonTheWingedDragonOfRaSphereMode(void);
unsigned char IsSkillDrainActiveOnField(void);
unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);
unsigned char ShouldActivateARMAGEDDON_KNIGHT(void);
void ActivateARMAGEDDON_KNIGHT(void);
unsigned char ShouldActivateCANNONBALL_SPEAR_SHELLFISH(void);
void ActivateCANNONBALL_SPEAR_SHELLFISH(void);
unsigned char ShouldActivateCYBER_KIRIN(void);
void ActivateCYBER_KIRIN(void);
unsigned char ShouldActivateDARKLORD_NURSE_REFICULE(void);
void ActivateDARKLORD_NURSE_REFICULE(void);
unsigned char ShouldActivateDESPAIR_FROM_THE_DARK(void);
void ActivateDESPAIR_FROM_THE_DARK(void);
unsigned char ShouldActivateDESTINY_HERO_DEFENDER(void);
void ActivateDESTINY_HERO_DEFENDER(void);
unsigned char ShouldActivateDESTINY_HERO_DOGMA(void);
void ActivateDESTINY_HERO_DOGMA(void);
unsigned char ShouldActivateDESTINY_HERO_DOOM_OVERLORD(void);
void ActivateDESTINY_HERO_DOOM_OVERLORD(void);
unsigned char ShouldActivateDESTINY_HERO_DOUBLE_DUDE(void);
void ActivateDESTINY_HERO_DOUBLE_DUDE(void);
unsigned char ShouldActivateDESTINY_HERO_DRAWHAND(void);
void ActivateDESTINY_HERO_DRAWHAND(void);
unsigned char ShouldActivateDESTINY_HERO_DREAD_SERVANT(void);
void ActivateDESTINY_HERO_DREAD_SERVANT(void);
unsigned char ShouldActivateDESTINY_HERO_DREADMASTER(void);
void ActivateDESTINY_HERO_DREADMASTER(void);
unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void);
void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4(void);
unsigned char ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void);
void ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6(void);
unsigned char ShouldActivateLIGHT_AND_DARKNESS_DRAGON(void);
void ActivateLIGHT_AND_DARKNESS_DRAGON(void);
unsigned char ShouldActivateTHUNDER_DRAGON_COLOSSUS(void);
void ActivateTHUNDER_DRAGON_COLOSSUS(void);
unsigned char ShouldActivateDARK_MAGICIAN_OF_DESTRUCTION(void);
void ActivateDARK_MAGICIAN_OF_DESTRUCTION(void);
unsigned char ShouldActivateDEEP_EYES_WHITE_DRAGON(void);
void ActivateDEEP_EYES_WHITE_DRAGON(void);
unsigned char ShouldActivateDRAGON_MASTER_MAGIA(void);
void ActivateDRAGON_MASTER_MAGIA(void);
unsigned char ShouldActivateDRAGON_SPIRIT_OF_WHITE(void);
void ActivateDRAGON_SPIRIT_OF_WHITE(void);

unsigned char ShouldActivateEL_SHADDOLL_ANOYATYLLIS(void);
void ActivateEL_SHADDOLL_ANOYATYLLIS(void);
unsigned char ShouldActivateEL_SHADDOLL_APKALLONE(void);
void ActivateEL_SHADDOLL_APKALLONE(void);
unsigned char ShouldActivateEL_SHADDOLL_CONSTRUCT(void);
void ActivateEL_SHADDOLL_CONSTRUCT(void);
unsigned char ShouldActivateEL_SHADDOLL_GRYSTA(void);
void ActivateEL_SHADDOLL_GRYSTA(void);
unsigned char ShouldActivateEL_SHADDOLL_SHEKHINAGA(void);
void ActivateEL_SHADDOLL_SHEKHINAGA(void);
unsigned char ShouldActivateEL_SHADDOLL_WINDA(void);
void ActivateEL_SHADDOLL_WINDA(void);
unsigned char ShouldActivateEVIL_DRAGON_ANANTA(void);
void ActivateEVIL_DRAGON_ANANTA(void);
unsigned char ShouldActivateEVIL_HERO_DARK_GAIA(void);
void ActivateEVIL_HERO_DARK_GAIA(void);
unsigned char ShouldActivateEVIL_HERO_INFERNAL_PRODIGY(void);
void ActivateEVIL_HERO_INFERNAL_PRODIGY(void);
unsigned char ShouldActivateEVIL_HERO_INFERNAL_SNIPER(void);
void ActivateEVIL_HERO_INFERNAL_SNIPER(void);
unsigned char ShouldActivateEVIL_HERO_INFERNO_WING(void);
void ActivateEVIL_HERO_INFERNO_WING(void);
unsigned char ShouldActivateEVIL_HERO_INFERNO_WING_BACKFIRE(void);
void ActivateEVIL_HERO_INFERNO_WING_BACKFIRE(void);
unsigned char ShouldActivateEVIL_HERO_MALICIOUS_EDGE(void);
void ActivateEVIL_HERO_MALICIOUS_EDGE(void);
unsigned char ShouldActivateEVIL_HERO_MALICIOUS_FIEND(void);
void ActivateEVIL_HERO_MALICIOUS_FIEND(void);
unsigned char ShouldActivateEVIL_HERO_WILD_CYCLONE(void);
void ActivateEVIL_HERO_WILD_CYCLONE(void);
unsigned char ShouldActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION(void);
void ActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION(void);
unsigned char ShouldActivateGOYO_GUARDIAN(void);
void ActivateGOYO_GUARDIAN(void);
unsigned char ShouldActivateGRINDER_GOLEM(void);
void ActivateGRINDER_GOLEM(void);
unsigned char ShouldActivateHARPIE_PERFUMER(void);
void ActivateHARPIE_PERFUMER(void);
unsigned char ShouldActivateHARPIES_PET_PHANTASMAL_DRAGON(void);
void ActivateHARPIES_PET_PHANTASMAL_DRAGON(void);
unsigned char ShouldActivateHERO_KID(void);
void ActivateHERO_KID(void);
unsigned char ShouldActivateIPIRIA(void);
void ActivateIPIRIA(void);
unsigned char ShouldActivateJUNK_WARRIOR(void);
void ActivateJUNK_WARRIOR(void);
unsigned char ShouldActivateLEGENDARY_MAJU_GARZETT(void);
void ActivateLEGENDARY_MAJU_GARZETT(void);
unsigned char ShouldActivateLIGHT_SERPENT(void);
void ActivateLIGHT_SERPENT(void);
unsigned char ShouldActivateMAGICIAN_OF_DARK_ILLUSION(void);
void ActivateMAGICIAN_OF_DARK_ILLUSION(void);
unsigned char ShouldActivateMAGICIANS_ROD(void);
void ActivateMAGICIANS_ROD(void);
unsigned char ShouldActivateOSHALEON(void);
void ActivateOSHALEON(void);
unsigned char ShouldActivateREPTILIANNE_GARDNA(void);
void ActivateREPTILIANNE_GARDNA(void);
unsigned char ShouldActivateREPTILIANNE_HYDRA(void);
void ActivateREPTILIANNE_HYDRA(void);
unsigned char ShouldActivateREPTILIANNE_NAGA(void);
void ActivateREPTILIANNE_NAGA(void);
unsigned char ShouldActivateREPTILIANNE_SERVANT(void);
void ActivateREPTILIANNE_SERVANT(void);
unsigned char ShouldActivateREPTILIANNE_VIPER(void);
void ActivateREPTILIANNE_VIPER(void);
unsigned char ShouldActivateTHE_DARK_MAGICIANS(void);
void ActivateTHE_DARK_MAGICIANS(void);
unsigned char ShouldActivateTHE_WHITE_STONE_OF_LEGEND(void);
void ActivateTHE_WHITE_STONE_OF_LEGEND(void);
unsigned char ShouldActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON(void);
void ActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON(void);
unsigned char ShouldActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES(void);
void ActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES(void);
unsigned char ShouldActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void);
void ActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void);
unsigned char ShouldActivateYOWIE(void);
void ActivateYOWIE(void);
unsigned char ShouldActivateARCANA_FORCE_0_THE_FOOL(void);
void ActivateARCANA_FORCE_0_THE_FOOL(void);
unsigned char ShouldActivateARCANA_FORCE_EX_THE_DARK_RULER(void);
void ActivateARCANA_FORCE_EX_THE_DARK_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void);
void ActivateARCANA_FORCE_EX_THE_LIGHT_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_I_THE_MAGICIAN(void);
void ActivateARCANA_FORCE_I_THE_MAGICIAN(void);
unsigned char ShouldActivateARCANA_FORCE_III_THE_EMPRESS(void);
void ActivateARCANA_FORCE_III_THE_EMPRESS(void);
unsigned char ShouldActivateARCANA_FORCE_IV_THE_EMPEROR(void);
void ActivateARCANA_FORCE_IV_THE_EMPEROR(void);
unsigned char ShouldActivateARCANA_FORCE_THE_CHAOS_RULER(void);
void ActivateARCANA_FORCE_THE_CHAOS_RULER(void);
unsigned char ShouldActivateARCANA_FORCE_VI_THE_LOVERS(void);
void ActivateARCANA_FORCE_VI_THE_LOVERS(void);
unsigned char ShouldActivateARCANA_FORCE_VII_THE_CHARIOT(void);
void ActivateARCANA_FORCE_VII_THE_CHARIOT(void);
unsigned char ShouldActivateARCANA_FORCE_VIII_THE_STRENGTH(void);
void ActivateARCANA_FORCE_VIII_THE_STRENGTH(void);
unsigned char ShouldActivateARCANA_FORCE_XIV_TEMPERANCE(void);
void ActivateARCANA_FORCE_XIV_TEMPERANCE(void);
unsigned char ShouldActivateARCANA_FORCE_XVIII_THE_MOON(void);
void ActivateARCANA_FORCE_XVIII_THE_MOON(void);
unsigned char ShouldActivateARCANA_FORCE_XXI_THE_WORLD(void);
void ActivateARCANA_FORCE_XXI_THE_WORLD(void);
unsigned char ShouldActivateAURKUS_LIGHTSWORN_DRUID(void);
void ActivateAURKUS_LIGHTSWORN_DRUID(void);
unsigned char ShouldActivateELEMENTAL_HERO_AIR_NEOS(void);
void ActivateELEMENTAL_HERO_AIR_NEOS(void);
unsigned char ShouldActivateELEMENTAL_HERO_FLARE_NEOS(void);
void ActivateELEMENTAL_HERO_FLARE_NEOS(void);
static const PermanentEffectOverride sPermanentEffectOverrides[] __attribute__((section(".text"))) = {
  {
    .cardId = MILUS_RADIANT,
    .shouldActivate = ShouldActivateMilusRadiant,
    .activate = ActivateMilusRadiant,
  },
  {
    .cardId = MUKA_MUKA,
    .shouldActivate = ShouldActivateMukaMuka,
    .activate = ActivateMukaMuka,
  },
  {
    .cardId = CEREMONIAL_BELL,
    .shouldActivate = ShouldActivateCeremonialBell,
    .activate = ActivateCeremonialBell,
  },
  {
    .cardId = BLUE_EYES_SHINING_DRAGON,
    .shouldActivate = ShouldActivateBlueEyesShiningDragon,
    .activate = ActivateBlueEyesShiningDragon,
  },
  {
    .cardId = SPELL_CANCELLER,
    .shouldActivate = ShouldActivateSpellCanceller,
    .activate = ActivateSpellCanceller,
  },
  {
    .cardId = YAMATA_DRAGON,
    .shouldActivate = ShouldActivateYamataDragon,
    .activate = ActivateYamataDragon,
  },
  {
    .cardId = SANGAN,
    .shouldActivate = ShouldActivateGraveyardDrawOnDestroy,
    .activate = ActivateGraveyardDrawOnDestroy,
  },
  {
    .cardId = WITCH_OF_THE_BLACK_FOREST,
    .shouldActivate = ShouldActivateGraveyardDrawOnDestroy,
    .activate = ActivateGraveyardDrawOnDestroy,
  },
  {
    .cardId = FAMILIAR_KNIGHT,
    .shouldActivate = ShouldActivateFamiliarKnight,
    .activate = ActivateFamiliarKnight,
  },
  {
    .cardId = ELEMENTAL_HERO_FLASH,
    .shouldActivate = ShouldActivateElementalHeroFlash,
    .activate = ActivateElementalHeroFlash,
  },
  {
    .cardId = DARK_MAGICIAN_KNIGHT,
    .shouldActivate = ShouldActivateDarkMagicianKnight,
    .activate = ActivateDarkMagicianKnight,
  },
  {
    .cardId = ZABORG_THE_THUNDER_MONARCH,
    .shouldActivate = ShouldActivateZaborgTheThunderMonarch,
    .activate = ActivateZaborgTheThunderMonarch,
  },
  {
    .cardId = CAIUS_THE_SHADOW_MONARCH,
    .shouldActivate = ShouldActivateCaiusTheShadowMonarch,
    .activate = ActivateCaiusTheShadowMonarch,
  },
  {
    .cardId = DARK_DUST_SPIRIT,
    .shouldActivate = ShouldActivateDarkDustSpiritSummon,
    .activate = ActivateDarkDustSpiritSummon,
  },
  {
    .cardId = MARAUDING_CAPTAIN,
    .shouldActivate = ShouldActivateMaraudingCaptain,
    .activate = ActivateMaraudingCaptain,
  },
  {
    .cardId = KAISER_GLIDER,
    .shouldActivate = ShouldActivateKaiserGlider,
    .activate = ActivateKaiserGlider,
  },
  {
    .cardId = ELEMENTAL_HERO_CORE,
    .shouldActivate = ShouldActivateElementalHeroCore,
    .activate = ActivateElementalHeroCore,
  },
  {
    .cardId = MOISTER_CREATURE,
    .shouldActivate = ShouldActivateMoisterCreature,
    .activate = ActivateMoisterCreature,
  },
  {
    .cardId = GREAT_MAJU_GARZETT,
    .shouldActivate = ShouldActivateGreatMajuGarzett,
    .activate = ActivateGreatMajuGarzett,
  },
  {
    .cardId = MAJU_GARZETT,
    .shouldActivate = ShouldActivateMajuGarzett,
    .activate = ActivateMajuGarzett,
  },
  {
    .cardId = THE_TYRANT_NEPTUNE,
    .shouldActivate = ShouldActivateTheTyrantNeptune,
    .activate = ActivateTheTyrantNeptune,
  },
  {
    .cardId = PETEN_THE_DARK_CLOWN,
    .shouldActivate = ShouldActivatePetenTheDarkClown,
    .activate = ActivatePetenTheDarkClown,
  },
  {
    .cardId = YUBEL,
    .shouldActivate = ShouldActivateYubelEvolution,
    .activate = ActivateYubelEvolution,
  },
  {
    .cardId = YUBEL_TERROR_INCARNATE,
    .shouldActivate = ShouldActivateYubelTerrorEvolution,
    .activate = ActivateYubelTerrorEvolution,
  },
  {
    .cardId = GIANT_RAT,
    .shouldActivate = ShouldActivateGiantRat,
    .activate = ActivateGiantRat,
  },
  {
    .cardId = THE_THING_IN_THE_CRATER,
    .shouldActivate = ShouldActivateTheThingInTheCrater,
    .activate = ActivateTheThingInTheCrater,
  },
  {
    .cardId = GREN_MAJU_DA_EIZA,
    .shouldActivate = ShouldActivateGrenMajuDaEiza,
    .activate = ActivateGrenMajuDaEiza,
  },
  {
    .cardId = DES_FERAL_IMP,
    .shouldActivate = ShouldActivateDesFeralImp,
    .activate = ActivateDesFeralImp,
  },
  {
    .cardId = ARSENAL_BUG,
    .shouldActivate = ShouldActivateArsenalBug,
    .activate = ActivateArsenalBug,
  },
  {
    .cardId = GRANADORA,
    .shouldActivate = ShouldActivateGranadora,
    .activate = ActivateGranadora,
  },
  {
    .cardId = BURNING_ALGAE,
    .shouldActivate = ShouldActivateBurningAlgae,
    .activate = ActivateBurningAlgae,
  },
  {
    .cardId = BERSERK_GORILLA,
    .shouldActivate = ShouldActivateBerserkGorilla,
    .activate = ActivateBerserkGorilla,
  },
  {
    .cardId = MOBIUS_THE_FROST_MONARCH,
    .shouldActivate = ShouldActivateMobiusTheFrostMonarch,
    .activate = ActivateMobiusTheFrostMonarch,
  },
  {
    .cardId = DARK_MAGICIAN_OF_CHAOS,
    .shouldActivate = ShouldActivateDARK_MAGICIAN_OF_CHAOS,
    .activate = ActivateDARK_MAGICIAN_OF_CHAOS,
  },
  {
    .cardId = ELEMENTAL_HERO_CAPTAIN_GOLD,
    .shouldActivate = ShouldActivateElementalHeroCaptainGold,
    .activate = ActivateElementalHeroCaptainGold,
  },
  {
    .cardId = THE_BIG_SATURN,
    .shouldActivate = ShouldActivateTheBigSaturn,
    .activate = ActivateTheBigSaturn,
  },
  {
    .cardId = THE_WICKED_ERASER,
    .shouldActivate = ShouldActivateTheWickedEraser,
    .activate = ActivateTheWickedEraser,
  },
  {
    .cardId = THE_TRIPPER_MERCURY,
    .shouldActivate = ShouldActivateTheTripperMercury,
    .activate = ActivateTheTripperMercury,
  },
  {
    .cardId = THE_WICKED_AVATAR,
    .shouldActivate = ShouldActivateTheWickedAvatar,
    .activate = ActivateTheWickedAvatar,
  },
  {
    .cardId = ARMAGEDDON_KNIGHT,
    .shouldActivate = ShouldActivateARMAGEDDON_KNIGHT,
    .activate = ActivateARMAGEDDON_KNIGHT,
  },
  {
    .cardId = CANNONBALL_SPEAR_SHELLFISH,
    .shouldActivate = ShouldActivateCANNONBALL_SPEAR_SHELLFISH,
    .activate = ActivateCANNONBALL_SPEAR_SHELLFISH,
  },
  {
    .cardId = CYBER_KIRIN,
    .shouldActivate = ShouldActivateCYBER_KIRIN,
    .activate = ActivateCYBER_KIRIN,
  },
  {
    .cardId = DARKLORD_NURSE_REFICULE,
    .shouldActivate = ShouldActivateDARKLORD_NURSE_REFICULE,
    .activate = ActivateDARKLORD_NURSE_REFICULE,
  },
  {
    .cardId = DESPAIR_FROM_THE_DARK,
    .shouldActivate = ShouldActivateDESPAIR_FROM_THE_DARK,
    .activate = ActivateDESPAIR_FROM_THE_DARK,
  },
  {
    .cardId = DESTINY_HERO_DEFENDER,
    .shouldActivate = ShouldActivateDESTINY_HERO_DEFENDER,
    .activate = ActivateDESTINY_HERO_DEFENDER,
  },
  {
    .cardId = DESTINY_HERO_DOGMA,
    .shouldActivate = ShouldActivateDESTINY_HERO_DOGMA,
    .activate = ActivateDESTINY_HERO_DOGMA,
  },
  {
    .cardId = DESTINY_HERO_DOOM_OVERLORD,
    .shouldActivate = ShouldActivateDESTINY_HERO_DOOM_OVERLORD,
    .activate = ActivateDESTINY_HERO_DOOM_OVERLORD,
  },
  {
    .cardId = DESTINY_HERO_DOUBLE_DUDE,
    .shouldActivate = ShouldActivateDESTINY_HERO_DOUBLE_DUDE,
    .activate = ActivateDESTINY_HERO_DOUBLE_DUDE,
  },
  {
    .cardId = DESTINY_HERO_DRAWHAND,
    .shouldActivate = ShouldActivateDESTINY_HERO_DRAWHAND,
    .activate = ActivateDESTINY_HERO_DRAWHAND,
  },
  {
    .cardId = DESTINY_HERO_DREAD_SERVANT,
    .shouldActivate = ShouldActivateDESTINY_HERO_DREAD_SERVANT,
    .activate = ActivateDESTINY_HERO_DREAD_SERVANT,
  },
  {
    .cardId = DESTINY_HERO_DREADMASTER,
    .shouldActivate = ShouldActivateDESTINY_HERO_DREADMASTER,
    .activate = ActivateDESTINY_HERO_DREADMASTER,
  },
  {
    .cardId = HORUS_THE_BLACK_FLAME_DRAGON_LV4,
    .shouldActivate = ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4,
    .activate = ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV4,
  },
  {
    .cardId = HORUS_THE_BLACK_FLAME_DRAGON_LV6,
    .shouldActivate = ShouldActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6,
    .activate = ActivateHORUS_THE_BLACK_FLAME_DRAGON_LV6,
  },
  {
    .cardId = LIGHT_AND_DARKNESS_DRAGON,
    .shouldActivate = ShouldActivateLIGHT_AND_DARKNESS_DRAGON,
    .activate = ActivateLIGHT_AND_DARKNESS_DRAGON,
  },
  {
    .cardId = THUNDER_DRAGON_COLOSSUS,
    .shouldActivate = ShouldActivateTHUNDER_DRAGON_COLOSSUS,
    .activate = ActivateTHUNDER_DRAGON_COLOSSUS,
  },
  {
    .cardId = DARK_MAGICIAN_OF_DESTRUCTION,
    .shouldActivate = ShouldActivateDARK_MAGICIAN_OF_DESTRUCTION,
    .activate = ActivateDARK_MAGICIAN_OF_DESTRUCTION,
  },
  {
    .cardId = DEEP_EYES_WHITE_DRAGON,
    .shouldActivate = ShouldActivateDEEP_EYES_WHITE_DRAGON,
    .activate = ActivateDEEP_EYES_WHITE_DRAGON,
  },
  {
    .cardId = DRAGON_MASTER_MAGIA,
    .shouldActivate = ShouldActivateDRAGON_MASTER_MAGIA,
    .activate = ActivateDRAGON_MASTER_MAGIA,
  },
  {
    .cardId = DRAGON_SPIRIT_OF_WHITE,
    .shouldActivate = ShouldActivateDRAGON_SPIRIT_OF_WHITE,
    .activate = ActivateDRAGON_SPIRIT_OF_WHITE,
  },
    {
    .cardId = EL_SHADDOLL_ANOYATYLLIS,
    .shouldActivate = ShouldActivateEL_SHADDOLL_ANOYATYLLIS,
    .activate = ActivateEL_SHADDOLL_ANOYATYLLIS,
  },
  {
    .cardId = EL_SHADDOLL_APKALLONE,
    .shouldActivate = ShouldActivateEL_SHADDOLL_APKALLONE,
    .activate = ActivateEL_SHADDOLL_APKALLONE,
  },
  {
    .cardId = EL_SHADDOLL_CONSTRUCT,
    .shouldActivate = ShouldActivateEL_SHADDOLL_CONSTRUCT,
    .activate = ActivateEL_SHADDOLL_CONSTRUCT,
  },
  {
    .cardId = EL_SHADDOLL_GRYSTA,
    .shouldActivate = ShouldActivateEL_SHADDOLL_GRYSTA,
    .activate = ActivateEL_SHADDOLL_GRYSTA,
  },
  {
    .cardId = EL_SHADDOLL_SHEKHINAGA,
    .shouldActivate = ShouldActivateEL_SHADDOLL_SHEKHINAGA,
    .activate = ActivateEL_SHADDOLL_SHEKHINAGA,
  },
  {
    .cardId = EL_SHADDOLL_WINDA,
    .shouldActivate = ShouldActivateEL_SHADDOLL_WINDA,
    .activate = ActivateEL_SHADDOLL_WINDA,
  },
  {
    .cardId = EVIL_DRAGON_ANANTA,
    .shouldActivate = ShouldActivateEVIL_DRAGON_ANANTA,
    .activate = ActivateEVIL_DRAGON_ANANTA,
  },
  {
    .cardId = EVIL_HERO_DARK_GAIA,
    .shouldActivate = ShouldActivateEVIL_HERO_DARK_GAIA,
    .activate = ActivateEVIL_HERO_DARK_GAIA,
  },
  {
    .cardId = EVIL_HERO_INFERNAL_PRODIGY,
    .shouldActivate = ShouldActivateEVIL_HERO_INFERNAL_PRODIGY,
    .activate = ActivateEVIL_HERO_INFERNAL_PRODIGY,
  },
  {
    .cardId = EVIL_HERO_INFERNAL_SNIPER,
    .shouldActivate = ShouldActivateEVIL_HERO_INFERNAL_SNIPER,
    .activate = ActivateEVIL_HERO_INFERNAL_SNIPER,
  },
  {
    .cardId = EVIL_HERO_INFERNO_WING,
    .shouldActivate = ShouldActivateEVIL_HERO_INFERNO_WING,
    .activate = ActivateEVIL_HERO_INFERNO_WING,
  },
  {
    .cardId = EVIL_HERO_INFERNO_WING_BACKFIRE,
    .shouldActivate = ShouldActivateEVIL_HERO_INFERNO_WING_BACKFIRE,
    .activate = ActivateEVIL_HERO_INFERNO_WING_BACKFIRE,
  },
  {
    .cardId = EVIL_HERO_MALICIOUS_EDGE,
    .shouldActivate = ShouldActivateEVIL_HERO_MALICIOUS_EDGE,
    .activate = ActivateEVIL_HERO_MALICIOUS_EDGE,
  },
  {
    .cardId = EVIL_HERO_MALICIOUS_FIEND,
    .shouldActivate = ShouldActivateEVIL_HERO_MALICIOUS_FIEND,
    .activate = ActivateEVIL_HERO_MALICIOUS_FIEND,
  },
  {
    .cardId = EVIL_HERO_WILD_CYCLONE,
    .shouldActivate = ShouldActivateEVIL_HERO_WILD_CYCLONE,
    .activate = ActivateEVIL_HERO_WILD_CYCLONE,
  },
  {
    .cardId = GANDORA_X_THE_DRAGON_OF_DEMOLITION,
    .shouldActivate = ShouldActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION,
    .activate = ActivateGANDORA_X_THE_DRAGON_OF_DEMOLITION,
  },
  {
    .cardId = GOYO_GUARDIAN,
    .shouldActivate = ShouldActivateGOYO_GUARDIAN,
    .activate = ActivateGOYO_GUARDIAN,
  },
  {
    .cardId = GRINDER_GOLEM,
    .shouldActivate = ShouldActivateGRINDER_GOLEM,
    .activate = ActivateGRINDER_GOLEM,
  },
  {
    .cardId = HARPIE_PERFUMER,
    .shouldActivate = ShouldActivateHARPIE_PERFUMER,
    .activate = ActivateHARPIE_PERFUMER,
  },
  {
    .cardId = HARPIES_PET_PHANTASMAL_DRAGON,
    .shouldActivate = ShouldActivateHARPIES_PET_PHANTASMAL_DRAGON,
    .activate = ActivateHARPIES_PET_PHANTASMAL_DRAGON,
  },
  {
    .cardId = HERO_KID,
    .shouldActivate = ShouldActivateHERO_KID,
    .activate = ActivateHERO_KID,
  },
  {
    .cardId = IPIRIA,
    .shouldActivate = ShouldActivateIPIRIA,
    .activate = ActivateIPIRIA,
  },
  {
    .cardId = JUNK_WARRIOR,
    .shouldActivate = ShouldActivateJUNK_WARRIOR,
    .activate = ActivateJUNK_WARRIOR,
  },
  {
    .cardId = LEGENDARY_MAJU_GARZETT,
    .shouldActivate = ShouldActivateLEGENDARY_MAJU_GARZETT,
    .activate = ActivateLEGENDARY_MAJU_GARZETT,
  },
  {
    .cardId = LIGHT_SERPENT,
    .shouldActivate = ShouldActivateLIGHT_SERPENT,
    .activate = ActivateLIGHT_SERPENT,
  },
  {
    .cardId = MAGICIAN_OF_DARK_ILLUSION,
    .shouldActivate = ShouldActivateMAGICIAN_OF_DARK_ILLUSION,
    .activate = ActivateMAGICIAN_OF_DARK_ILLUSION,
  },
  {
    .cardId = MAGICIANS_ROD,
    .shouldActivate = ShouldActivateMAGICIANS_ROD,
    .activate = ActivateMAGICIANS_ROD,
  },
  {
    .cardId = OSHALEON,
    .shouldActivate = ShouldActivateOSHALEON,
    .activate = ActivateOSHALEON,
  },
  {
    .cardId = REPTILIANNE_GARDNA,
    .shouldActivate = ShouldActivateREPTILIANNE_GARDNA,
    .activate = ActivateREPTILIANNE_GARDNA,
  },
  {
    .cardId = REPTILIANNE_HYDRA,
    .shouldActivate = ShouldActivateREPTILIANNE_HYDRA,
    .activate = ActivateREPTILIANNE_HYDRA,
  },
  {
    .cardId = REPTILIANNE_NAGA,
    .shouldActivate = ShouldActivateREPTILIANNE_NAGA,
    .activate = ActivateREPTILIANNE_NAGA,
  },
  {
    .cardId = REPTILIANNE_SERVANT,
    .shouldActivate = ShouldActivateREPTILIANNE_SERVANT,
    .activate = ActivateREPTILIANNE_SERVANT,
  },
  {
    .cardId = REPTILIANNE_VIPER,
    .shouldActivate = ShouldActivateREPTILIANNE_VIPER,
    .activate = ActivateREPTILIANNE_VIPER,
  },
  {
    .cardId = THE_DARK_MAGICIANS,
    .shouldActivate = ShouldActivateTHE_DARK_MAGICIANS,
    .activate = ActivateTHE_DARK_MAGICIANS,
  },
  {
    .cardId = THE_WHITE_STONE_OF_LEGEND,
    .shouldActivate = ShouldActivateTHE_WHITE_STONE_OF_LEGEND,
    .activate = ActivateTHE_WHITE_STONE_OF_LEGEND,
  },
  {
    .cardId = TIMEAEUS_THE_UNITED_MAGICAL_DRAGON,
    .shouldActivate = ShouldActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON,
    .activate = ActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON,
  },
  {
    .cardId = VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES,
    .shouldActivate = ShouldActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES,
    .activate = ActivateVENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES,
  },
  {
    .cardId = VENNOMINON_THE_KING_OF_POISONOUS_SNAKES,
    .shouldActivate = ShouldActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES,
    .activate = ActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES,
  },
  {
    .cardId = YOWIE,
    .shouldActivate = ShouldActivateYOWIE,
    .activate = ActivateYOWIE,
  },
  {
    .cardId = ARCANA_FORCE_0_THE_FOOL,
    .shouldActivate = ShouldActivateARCANA_FORCE_0_THE_FOOL,
    .activate = ActivateARCANA_FORCE_0_THE_FOOL,
  },
  {
    .cardId = ARCANA_FORCE_EX_THE_DARK_RULER,
    .shouldActivate = ShouldActivateARCANA_FORCE_EX_THE_DARK_RULER,
    .activate = ActivateARCANA_FORCE_EX_THE_DARK_RULER,
  },
  {
    .cardId = ARCANA_FORCE_EX_THE_LIGHT_RULER,
    .shouldActivate = ShouldActivateARCANA_FORCE_EX_THE_LIGHT_RULER,
    .activate = ActivateARCANA_FORCE_EX_THE_LIGHT_RULER,
  },
  {
    .cardId = ARCANA_FORCE_I_THE_MAGICIAN,
    .shouldActivate = ShouldActivateARCANA_FORCE_I_THE_MAGICIAN,
    .activate = ActivateARCANA_FORCE_I_THE_MAGICIAN,
  },
  {
    .cardId = ARCANA_FORCE_III_THE_EMPRESS,
    .shouldActivate = ShouldActivateARCANA_FORCE_III_THE_EMPRESS,
    .activate = ActivateARCANA_FORCE_III_THE_EMPRESS,
  },
  {
    .cardId = ARCANA_FORCE_IV_THE_EMPEROR,
    .shouldActivate = ShouldActivateARCANA_FORCE_IV_THE_EMPEROR,
    .activate = ActivateARCANA_FORCE_IV_THE_EMPEROR,
  },
  {
    .cardId = ARCANA_FORCE_THE_CHAOS_RULER,
    .shouldActivate = ShouldActivateARCANA_FORCE_THE_CHAOS_RULER,
    .activate = ActivateARCANA_FORCE_THE_CHAOS_RULER,
  },
  {
    .cardId = ARCANA_FORCE_VI_THE_LOVERS,
    .shouldActivate = ShouldActivateARCANA_FORCE_VI_THE_LOVERS,
    .activate = ActivateARCANA_FORCE_VI_THE_LOVERS,
  },
  {
    .cardId = ARCANA_FORCE_VII_THE_CHARIOT,
    .shouldActivate = ShouldActivateARCANA_FORCE_VII_THE_CHARIOT,
    .activate = ActivateARCANA_FORCE_VII_THE_CHARIOT,
  },
  {
    .cardId = ARCANA_FORCE_VIII_THE_STRENGTH,
    .shouldActivate = ShouldActivateARCANA_FORCE_VIII_THE_STRENGTH,
    .activate = ActivateARCANA_FORCE_VIII_THE_STRENGTH,
  },
  {
    .cardId = ARCANA_FORCE_XIV_TEMPERANCE,
    .shouldActivate = ShouldActivateARCANA_FORCE_XIV_TEMPERANCE,
    .activate = ActivateARCANA_FORCE_XIV_TEMPERANCE,
  },
  {
    .cardId = ARCANA_FORCE_XVIII_THE_MOON,
    .shouldActivate = ShouldActivateARCANA_FORCE_XVIII_THE_MOON,
    .activate = ActivateARCANA_FORCE_XVIII_THE_MOON,
  },
  {
    .cardId = ARCANA_FORCE_XXI_THE_WORLD,
    .shouldActivate = ShouldActivateARCANA_FORCE_XXI_THE_WORLD,
    .activate = ActivateARCANA_FORCE_XXI_THE_WORLD,
  },
  {
    .cardId = AURKUS_LIGHTSWORN_DRUID,
    .shouldActivate = ShouldActivateAURKUS_LIGHTSWORN_DRUID,
    .activate = ActivateAURKUS_LIGHTSWORN_DRUID,
  },
  {
    .cardId = ELEMENTAL_HERO_AIR_NEOS,
    .shouldActivate = ShouldActivateELEMENTAL_HERO_AIR_NEOS,
    .activate = ActivateELEMENTAL_HERO_AIR_NEOS,
  },
  {
    .cardId = ELEMENTAL_HERO_FLARE_NEOS,
    .shouldActivate = ShouldActivateELEMENTAL_HERO_FLARE_NEOS,
    .activate = ActivateELEMENTAL_HERO_FLARE_NEOS,
  },
/* END PERMANENT EFFECT OVERRIDES */
};

static const PermanentEffectOverride *GetPermanentEffectOverride(u16 cardId) {
  unsigned char i;

  for (i = 0; i < ARRAY_COUNT(sPermanentEffectOverrides); i++) {
    if (sPermanentEffectOverrides[i].cardId == cardId)
      return &sPermanentEffectOverrides[i];
  }

  return NULL;
}

static u8 CardHasPermanentEffectSource(u16 cardId)
{
  const PermanentEffectOverride *override;

  if (cardId == CARD_NONE)
    return FALSE;

  override = GetPermanentEffectOverride(cardId);
  if (override != NULL)
    return TRUE;

  SetCardInfo(cardId);
  return gCardInfo.unk1E != 0;
}

static u8 FieldZoneHasPermanentEffectSource(struct DuelCard *zone, u8 turnRow)
{
  u16 copied;

  if (zone->id == CARD_NONE)
    return FALSE;
  if (gHideEffectText && !zone->isFaceUp && (turnRow == 0 || turnRow == 1))
    return FALSE;
  if (CardHasPermanentEffectSource(zone->id))
    return TRUE;

  copied = TheTyrantNeptune_GetCopiedCardId(zone);
  if (copied == CARD_NONE)
    return FALSE;

  return CardHasPermanentEffectSource(copied);
}

u8 AiSimFieldNeedsPermanentRescan(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[2][col], 2))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[1][col], 1))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[3][col], 3))
      return TRUE;
  }
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (FieldZoneHasPermanentEffectSource(gTurnZones[0][col], 0))
      return TRUE;
  }

  if (CardHasPermanentEffectSource(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
    return TRUE;
  if (CardHasPermanentEffectSource(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
    return TRUE;

  return FALSE;
}

static void ResetTempStagesForFieldCards(void)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      gDuel.board[row][col].tempStage = 0;
  }
}

static void TryActivatingPermanentEffect__Hook(void) {
  const PermanentEffectOverride *override;

  /* Skill Drain negates all monster effects on the field */
  if (gActiveEffect.turnRow == 1 || gActiveEffect.turnRow == 2) {
    if (TryActivateSkillDrainAndNegateCardId(gActiveEffect.cardId))
      return;
  }

  override = GetPermanentEffectOverride(gActiveEffect.cardId);

  if (override != NULL) {
    ResetCardEffectTextData();
    SetCardEffectTextType(8);
    override->activate();
    return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  SetCardInfo(gActiveEffect.cardId);
  sPermanentEffects[gCardInfo.unk1E]();
}

static unsigned char ShouldActivatePermanentEffect__Hook(void) {
  const PermanentEffectOverride *override;

  if (gActiveEffect.cardId == CARD_NONE)
    return FALSE;

  /* Skill Drain negates all monster effects on the field */
  if ((gActiveEffect.turnRow == 1 || gActiveEffect.turnRow == 2) && IsSkillDrainActiveOnField())
    return FALSE;

  if (IsImperialOrderNegatingSpell(gActiveEffect.cardId))
    return FALSE;

  /* Harpie Lady 2: negate effects of monsters destroyed in battle */
  if ((gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7)
      && gActiveEffect.cardId == gHarpieLady2NegatedCardId) {
    gHarpieLady2NegatedCardId = CARD_NONE;
    return FALSE;
  }

  override = GetPermanentEffectOverride(gActiveEffect.cardId);

  if (gActiveEffect.cardId == JAM_BREEDING_MACHINE || gActiveEffect.cardId == TOLL)
    return FALSE;

  if (override != NULL)
    return override->shouldActivate();

  SetCardInfo(gActiveEffect.cardId);
  if (gCardInfo.unk1E == 0)
    return FALSE;
  return g8E0C800[gCardInfo.unk1E]();
}

static void TryScanPermanentEffectAt(struct DuelCard **row, u8 turnRow, u8 col,
                                     u8 animateCursor)
{
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = col;
  gActiveEffect.cardId = row[col]->id;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ACC0();
  if (ShouldActivatePermanentEffect__Hook() == 1) {
    if (!gHideEffectText)
      sub_8034FEC(0x177);
    TryActivatingPermanentEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void ScanPermanentEffectRow__Hook(struct DuelCard **row, u8 turnRow, u8 animateCursor) {
  u8 i;

  gActiveEffect.turnRow = turnRow;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 neptuneSavedId;

    if (row[i]->id == CARD_NONE)
      continue;
    /* ponytail: AI sim must not read face-down opponent cards — prevents
       logic loops from spurious effect activation on unknown cards. */
    if (gHideEffectText && !row[i]->isFaceUp && (turnRow == 0 || turnRow == 1))
      continue;

    TryScanPermanentEffectAt(row, turnRow, i, animateCursor);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }

    /* Neptune gains permanent effects of its copied tribute. */
    neptuneSavedId = TheTyrantNeptune_BeginEffectIdentity(row[i]);
    if (neptuneSavedId != CARD_NONE) {
      TryScanPermanentEffectAt(row, turnRow, i, FALSE);
      TheTyrantNeptune_EndEffectIdentity(row[i], neptuneSavedId);
      if (IsDuelOver() == 1) {
        if (!gHideEffectText)
          sub_8034FEC(0x177);
        return;
      }
    }
  }
}

static void ScanPermanentEffectGraveyard__Hook(u8 turnRow, u8 duelist, u8 animateCursor) {
  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = gTurnDuelistBattleState[duelist]->graveyard;
  TheBigSaturn_PrepareGraveyardScan(turnRow, &gActiveEffect.cardId);
  if (gActiveEffect.cardId == CARD_NONE)
    return;
  if (animateCursor == TRUE && !gHideEffectText)
    sub_802ADF4();
  if (ShouldActivatePermanentEffect__Hook() == 1) {
    if (!gHideEffectText)
      sub_8034FEC(0x177);
    TryActivatingPermanentEffect__Hook();
    if (!gHideEffectText)
      PlayMusic(MUSIC_375);
  }
}

static void CheckBoardForPermanentEffects__Hook(u8 animateScanner) {
  /* ponytail: AI sim never runs continuous effects from cards still in hand. */
  if (!gHideEffectText)
    ScanPermanentEffectRow__Hook(gTurnHands[ACTIVE_DUELIST], 4, animateScanner);
  if (IsDuelOver() == 1)
    return;

  /* ponytail: AI sim never activates hand permanent effects on the hidden hand. */
  if (!gHideEffectText) {
    ScanPermanentEffectRow__Hook(gTurnHands[INACTIVE_DUELIST], 5, FALSE);
    if (IsDuelOver() == 1)
      return;
  }

  if (!gHideEffectText)
    PlayMusic(MUSIC_375);

  if (!gHideEffectText ||
      CardHasPermanentEffectSource(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard) ||
      TheBigSaturn_PendingGraveyardTurnRow() == 6) {
    ScanPermanentEffectGraveyard__Hook(6, ACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }
  }

  if (!gHideEffectText ||
      CardHasPermanentEffectSource(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard) ||
      TheBigSaturn_PendingGraveyardTurnRow() == 7) {
    ScanPermanentEffectGraveyard__Hook(7, INACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == 1) {
      if (!gHideEffectText)
        sub_8034FEC(0x177);
      return;
    }
  }

  ScanPermanentEffectRow__Hook(gTurnZones[2], 2, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[1], 1, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[3], 3, animateScanner);
  if (IsDuelOver() == 1)
    return;

  ScanPermanentEffectRow__Hook(gTurnZones[0], 0, animateScanner);
  if (!gHideEffectText)
    sub_8034FEC(0x177);
}

static void TryActivatingPermanentEffectsPostBoardScan(u8 aiSim)
{
  if (!aiSim || IsPyramidOfLightActiveOnField())
    EnforcePyramidOfLightGodBan();

  if (TryAutoSummonBlueEyesShiningDragon() == TRUE
      || TryAutoSummonTheWingedDragonOfRaSphereMode() == TRUE) {
    if (!aiSim)
      UpdateDuelGfxExceptField();
    ResetTempStagesForAllCards();
    CheckBoardForPermanentEffects__Hook(FALSE);
  }

  ResolvePendingGraveyardDrawOnDestroy();
  if (!aiSim) {
    TheBigSaturn_TryResolveGyDamage();
    TheWickedEraser_TryResolveFieldWipe();
  }
  if (!aiSim || IsLevelLimitAreaBActiveOnField())
    Duel_CheckLevelLimitAreaBAfterFieldChange();
  if (!aiSim || IsLevelLimitAreaAActiveOnField())
    Duel_CheckLevelLimitAreaAAfterFieldChange();
  Duel_RefreshAttackRestrictions();

  if (aiSim)
    return;

  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();
  Duel_CheckRingOfDestructionAfterFieldChange();
}

void PermanentEffect_RunSimBoardScan(void)
{
  CheckBoardForPermanentEffects__Hook(FALSE);
}

void PermanentEffect_RunSimPostBoardScan(void)
{
  TryActivatingPermanentEffectsPostBoardScan(TRUE);
}

LYN_REPLACE_CHECK(TryActivatingPermanentEffects);
void TryActivatingPermanentEffects__Replacement(void) {
  u8 hideEffectText = gHideEffectText;
  u8 aiSim = gHideEffectText == TRUE;
  u8 needsRescan;

  if (aiSim) {
    if (HasActiveDynamicEquips())
      RecalculateAllDynamicEquips();
    gActiveEffect.turn = WhoseTurn();
    ResetTempStagesForFieldCards();
    needsRescan = AiSimFieldNeedsPermanentRescan();
    if (needsRescan)
      CheckBoardForPermanentEffects__Hook(FALSE);
    TryActivatingPermanentEffectsPostBoardScan(TRUE);
    gHideEffectText = hideEffectText;
    return;
  }

  if (!aiSim || HasActiveDynamicEquips())
    RecalculateAllDynamicEquips();
  gActiveEffect.turn = WhoseTurn();
  if (!aiSim && !gRuntimeConfig.turn_off_visual_scanner) {
    sub_80408BC();
    sub_802ADA4();
  }
  ResetTempStagesForAllCards();
  if (!aiSim)
    UpdateDuelGfxExceptField();
  if (gRuntimeConfig.turn_off_visual_scanner == TRUE)
    gHideEffectText = TRUE;
  CheckBoardForPermanentEffects__Hook(!aiSim && !gRuntimeConfig.turn_off_visual_scanner);

  TryActivatingPermanentEffectsPostBoardScan(aiSim);

  gHideEffectText = hideEffectText;
  if (!aiSim) {
    UpdateDuelGfxExceptField();
    sub_802AE44();
  }
}