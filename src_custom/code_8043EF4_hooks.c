#include "global.h"
#include "ancient_gear_attack_lock.h"
#include "common-chax.h"
#include "board_placement.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "summon_tribute.h"
#include "archlord_kristya.h"
#include "dynamic_equip.h"
#include "mystical_space_typhoon.h"
#include "athena.h"
#include "cannon_soldier.h"
#include "man_thro_tro.h"
#include "riryoku.h"
#include "pyramid_of_light.h"
#include "mask_of_restrict.h"
#include "soul_exchange.h"
#include "fairy_box.h"
#include "mirror_wall.h"
#include "cyber_barrier_dragon.h"
#include "neo_spacian_glow_moss.h"
#include "red_dragon_archfiend.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "card_passives.h"
#include "duel_helpers.h"
#include "spell_activation_gates.h"
#include "six_card_hand.h"
#include "duel_attack_restrictions.h"
#include "duel_activated_backrow.h"
#include "sasuke_samurai_2.h"
#include "rivalry_of_warlords.h"
#include "level_limit_area_b.h"
#include "ring_of_destruction.h"
#include "nightmare_wheel.h"
#include "dust_tornado.h"
#include "ectoplasmer.h"
#include "yubel.h"
#include "amazoness_tiger.h"
#include "elemental_hero_great_tornado.h"
#include "summon_animations.h"
#include "elemental_hero_absolute_zero.h"
#include "blast_held_by_a_tribute.h"
#include "vengeful_bog_spirit.h"
#include "kaiser_colosseum.h"
#include "breaker_the_magical_warrior.h"
#include "jowls_of_dark_demise.h"
#include "invader_of_the_throne.h"
#include "harpies_pet_baby_dragon.h"
#include "blowback_dragon.h"
#include "dark_end_dragon.h"
#include "light_end_dragon.h"
#include "cyber_laser_dragon.h"
#include "cats_ear_tribe.h"
#include "spirit_ryu.h"
#include "graveyard_effects.h"
#include "the_unhappy_maiden.h"
#include "vampire_baby.h"
#include "ghost_knight_of_jackal.h"
#include "arcana_force_vii_the_chariot.h"
#include "amazoness_spy.h"
#include "amazoness_trainee.h"
#include "amazoness_sage.h"
#include "aroma_jar.h"
#include "flip_deck_search.h"
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "royal_knight.h"
#include "elemental_hero_steam_healer.h"
#include "elemental_hero_core.h"
#include "elemental_hero_sunrise.h"
#include "elemental_hero_blazeman.h"
#include "elemental_hero_stratos.h"
#include "the_suppression_pluto.h"
#include "elemental_hero_flame_wingman.h"
#include "lesser_fiend.h"
#include "dark_magician_of_chaos.h"
#include "needle_burrower.h"
#include "hyper_hammerhead.h"
#include "neo_spacian_grand_mole.h"
#include "lightning_warrior.h"
#include "neo_spacian_glow_moss.h"
#include "neo_spacian_twinkle_moss.h"
#include "reptilianne_gorgon.h"
#include "don_zaloog.h"
#include "red_dragon_archfiend.h"
#include "reptilianne_scylla.h"
#include "des_kangaroo.h"
#include "continuous_destruction_punch.h"
#include "amazoness_heirloom.h"
#include "d_d_warrior.h"
#include "absorbing_kid_from_the_sky.h"
#include "airknight_parshath.h"
#include "sasuke_samurai_3.h"
#include "debug_ruleset.h"
#include "dark_magician_knight.h"
#include "zaborg_the_thunder_monarch.h"
#include "caius_the_shadow_monarch.h"
#include "mobius_the_frost_monarch.h"
#include "ryu_kishin_clown.h"
#include "embodiment_of_apophis.h"
#include "precious_cards_from_beyond.h"
#include "ojama_trio.h"
#include "hayabusa_knight.h"
#include "mermaid_knight.h"
#include "twin_swords_of_flashing_light_tryce.h"
#include "tyrant_dragon.h"
#include "cyber_twin_dragon.h"
#include "the_tripper_mercury.h"
#include "the_wicked_dreadroot.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "chimeratech_overdragon.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_necroid_shaman.h"
#include "elemental_hero_plasma_vice.h"
#include "hero_flash.h"
#include "spell_effects.h"
#include "elemental_hero_terra_firma.h"
#include "elemental_hero_wild_wingman.h"
#include "elemental_hero_wildedge.h"
#include "amazoness_call.h"
#include "d_burst.h"
#include "d_force.h"
#include "neutron_blast.h"
#include "tyrant_wing.h"
#include "arcana_force_ex_the_dark_ruler.h"
#include "destiny_hero_double_dude.h"
#include "elemental_hero_necroshade.h"
#include "ancient_gear_advance.h"
#include "cold_wave.h"
#include "ancient_gear_castle.h"
#include "ancient_gear_drill.h"
#include "ancient_gear_factory.h"
#include "anti_spell_fragrance.h"
#include "aroma_gardening.h"
#include "field_barrier.h"
#include "flavian_colosseum_of_the_gladiator_beasts.h"
#include "lightsworn_barrier.h"
#include "big_evolution_pill.h"
#include "chain_summoning.h"
#include "effect_events.h"
#include "amazoness_archer.h"
#include "sasuke_samurai.h"
#include "block_attack.h"
#include "soul_taker.h"
#include "creature_swap.h"
#include "negative_energy.h"
#include "tribute_doll.h"
#include "r_righteous_justice.h"
#include "valhalla_hall_of_the_fallen.h"
#include "court_of_justice.h"
#include "book_of_moon.h"
#include "h_heated_heart.h"
#include "book_of_taiyou.h"
#include "de_fusion.h"
#include "diffusion_wave_motion.h"
#include "ring_of_destruction.h"
#include "nightmare_wheel.h"
#include "toll.h"
#include "call_of_the_haunted.h"
#include "skull_invitation.h"
#include "self_destruct_button.h"
#include "the_dark_door.h"
#include "gravity_bind.h"
#include "curse_of_darkness.h"
#include "coffin_seller.h"
#include "dark_room_of_nightmare.h"
#include "kaiser_glider.h"
#include "nightmare_horse.h"
#include "servant_of_catabolism.h"
#include "amphibious_bugroth_mk_3.h"
#include "black_tyranno.h"
#include "drillago.h"
#include "thunder_nyan_nyan.h"
#include "elemental_hero_mariner.h"
#include "elemental_hero_knospe.h"
#include "elemental_hero_ice_edge.h"
#include "reaper_on_the_nightmare.h"
#include "spirit_reaper.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "the_tyrant_neptune.h"
#include "the_tripper_mercury.h"
#include "the_wicked_dreadroot.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "the_grand_jupiter.h"
#include "executor_makyura.h"
#include "duel_helpers.h"
#include "hamon_lord_of_striking_thunder.h"
#include "uria_lord_of_searing_flames.h"
#include "raviel_lord_of_phantasms.h"

u8 TryPayChainEnergyCost(void);
u8 IsActivatedChainEnergyZone(const struct DuelCard *zone);
u8 IsActivatedTollZone(const struct DuelCard *zone);
u8 IsActivatedTheDarkDoorZone(const struct DuelCard *zone);
u8 IsActivatedDarkRoomZone(const struct DuelCard *zone);
u8 TryConsumeUltimateOfferingExtraSummonPayment(void);
void TryEnableUltimateOfferingExtraSummonAfterPlacement(void);
void TryEnableCourtOfJusticeIgnitionAfterPlacement(void);
u8 TryConsumeCourtOfJusticeIgnitionPlacement(void);
void CourtOfJustice_FinishHandPlacement(struct DuelCard *zone);
u8 CourtOfJustice_HandSlotMayIgnition(u8 handSlot);
u8 CanUseCourtOfJusticeHandIgnition(void);
void TryEnableValhallaHallOfTheFallenIgnitionAfterPlacement(void);
u8 IsActivatedUltimateOfferingZone(const struct DuelCard *zone);
void MarkUltimateOfferingJustSet(struct DuelCard *zone);
void MarkFairyBoxJustSet(struct DuelCard *zone);
void MarkMirrorWallJustSet(struct DuelCard *zone);
void MarkBottomlessShiftingSandJustSet(struct DuelCard *zone);
unsigned IsTrapTriggered(void);
void ActivateTrapEffect(u16 lp);

extern struct DuelCard gSelectedCard;

void DisplayCardInfoBar(void);
void HandlePlayerBackrowAction(void);
void TrySelectSpellTarget(void);
void sub_8041E70(u8, u8);
void ActivateSpellEffect(void);
void LockMonsterCardsInRow(unsigned char);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void SelectZone(struct DuelCard *zone);
void ResetCursorDestToCurrentPos(void);
unsigned char GetFirstNonEmptyMonZoneId(struct DuelCard *zone[]);
void ClearZone(struct DuelCard *zone);
void CopySelectedCardToZone(struct DuelCard *zone);
void sub_80449D8(void);
void TryActivateGranadoraOnMonsterPlacement(struct DuelCard *zone);
void TryActivateRyuKishinClownOnMonsterPlacement(struct DuelCard *zone);
void TryIofielOnMonsterPlacement(struct DuelCard *zone);
void TryAthenaOnMonsterPlacement(struct DuelCard *zone);
void TryActivateDarkDustSpiritOnMonsterPlacement(struct DuelCard *zone);
void TryBreakerTheMagicalWarriorOnMonsterPlacement(struct DuelCard *zone);
void TryEnforceBerserkGorillaOnMonsterPlacement(struct DuelCard *zone);
void TryLevelLimitAreaAOnMonsterPlacement(struct DuelCard *zone);
signed char FirstEmptyZoneInRow(struct DuelCard **zonePtr);
void sub_80441D0(void);
void MonsterActionMenu(void);
void HandlePlayerBackrowAction(void);
void DisplayNumRequiredTributesTextbox(unsigned char);
void sub_80442AC(void);
void sub_8044570(void);
void TryAttackWithMonster(void);
void SetCursorToCardDest(void);
void sub_8044A5C(void);
void sub_8044A88(void);
void sub_8044A30(void);
void OpenBMenu(void);
void HandleAButtonAction(void);
void HandleBButtonAction(void);
void sub_8022080(void);
void SetAttackAction(s32, s32);
void SetAttackActionDirectAttack(int);
void CheckGraveyardAndLoserFlags(void);
void CheckWinConditionFINAL(void);
void BlockTurnSummoning(u8);
void HandleAtkAndLifePointsAction(void);
void UpdateAllDuelGfx(void);
u8 TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(u8);
u8 TrySpecialSummonGilasaurusFromHand(u8);
u8 TrySpecialSummonFenrirFromHand(u8);
u8 TrySpecialSummonChaosEmperorDragonEnvoyOfTheEndFromHand(u8);
u8 TrySpecialSummonDarkArmedDragonFromHand(u8);
u8 TrySpecialSummonBlackLusterSoldierEnvoyOfTheBeginningFromHand(u8);
u8 TrySpecialSummonArchlordKristyaFromHand(u8);
u8 TryActivateElementalHeroCaptainGoldFromHand(u8);
u8 TryActivateHecatriceFromHand(u8);
u8 TryActivateGRAVEKEEPERS_COMMANDANTFromHand(u8);
u8 TryActivateZERADIAS_HERALD_OF_HEAVENFromHand(u8);
u8 TrySpecialSummonSpellStrikerFromHand(u8);
u8 TrySpecialSummonDarkGrepherFromHand(u8);
u8 TryActivateMAXX_CFromHand(u8);
u8 TrySpecialSummonArmedDragonLv10FromHand(u8);
u8 TryActivateWARRIOR_OF_ATLANTISFromHand(u8);
u8 TryActivateHARPIE_QUEENFromHand(u8);
u8 TryActivateCHARM_OF_SHABTIFromHand(u8);
u8 TryActivateDESTINY_HERO_BLADE_MASTERFromHand(u8);
u8 TrySpecialSummonAncientGearFromHand(u8);
u8 TrySpecialSummonAmazonessBabyTigerFromHand(u8);
u8 TrySpecialSummonAmazonessSpyFromHand(u8);
u8 TrySpecialSummonTheTrickyFromHand(u8);
u8 TrySpecialSummonHamonLordOfStrikingThunderFromHand(u8);
u8 TrySpecialSummonUriaLordOfSearingFlamesFromHand(u8);
u8 TrySpecialSummonRavielLordOfPhantasmsFromHand(u8);
u8 TrySpecialSummonTurboBoosterFromHand(u8);
u8 TrySpecialSummonGreenBaboonFromHand(u8);
u8 TrySpecialSummonBeastMachineKingBarbarosUrFromHand(u8);
u8 TryActivateEvilHeroAdustedGoldFromHand(u8);
u8 TryActivateMagiciansRobeFromHand(u8);
u8 TryActivateGravekeepersWatcherFromHand(u8);
u8 TrySpecialSummonReptilianneVaskiiFromHand(u8);
u8 TrySpecialSummonMontageDragonFromHand(u8);
u8 TrySpecialSummonArcanaForceXixTheSunFromHand(u8);
u8 TryActivateArcanaForceVTheHierophantFromHand(u8);
u8 TrySpecialSummonAromageLaurelFromHand(u8);
u8 TryActivateAromalilithRosalinaFromHand(u8);
u8 TrySpecialSummonTestTigerFromHand(u8);
u8 TrySpecialSummonTimeausTheUnitedDragonFromHand(u8);
u8 TrySpecialSummonOceanDragonLordNeoDaedalusFromHand(u8);
u8 TrySpecialSummonTheAgentOfEntropyUranusFromHand(u8);
u8 TrySpecialSummonLightrayDaedalusFromHand(u8);
u8 TrySpecialSummonHolactieTheCreatorOfLightFromHand(u8);
u8 TrySpecialSummonCyberEltaninFromHand(u8);
u8 TrySpecialSummonHeliosDuoMegistusFromHand(u8);
u8 TrySpecialSummonHeliosTriceMegistusFromHand(u8);
u8 TrySpecialSummonHarpieOracleFromHand(u8);
u8 TrySpecialSummonAmazonessWarChiefFromHand(u8);
u8 TrySpecialSummonMagiciansSoulsFromHand(u8);
u8 TrySpecialSummonOrichalcosShunorosFromHand(u8);
u8 TryActivateWeissLightswornArchfiendFromHand(u8);
u8 TrySpecialSummonAlectorSovereignOfBirdsFromHand(u8);
u8 TrySpecialSummonRainbowDarkDragonFromHand(u8);
u8 TrySpecialSummonLightswornDragonlingFromHand(u8);
u8 TryActivateAshBlossomFromHand(u8);
u8 TrySpecialSummonPoseidraFromHand(u8);
u8 TrySpecialSummonPunishmentDragonFromHand(u8);
u8 TryActivateHonestFromHand(u8);
u8 TryActivateArcanaForceXvTheFiendFromHand(u8);
u8 TrySpecialSummonMasterHyperionFromHand(u8);
u8 TryActivateDestinyHeroDynatagFromHand(u8);
u8 TrySpecialSummonDestinyHeroPlasmaFromHand(u8);
u8 TrySpecialSummonEvilHeroToxicBubbleFromHand(u8);
u8 TrySpecialSummonGuardianEatosFromHand(u8);
u8 TrySpecialSummonDarknessNeosphereFromHand(u8);
u8 TrySpecialSummonMazeraDevilleFromHand(u8);
u8 TryActivateCrossKeeperFromHand(u8);
u8 TrySpecialSummonAndroSphinxFromHand(u8);
u8 TrySpecialSummonGladiatorBeastGistelFromHand(u8);
u8 TrySpecialSummonTheAgentOfDestructionVenusFromHand(u8);
u8 TrySpecialSummonReptilianneLamiaFromHand(u8);
u8 TryActivateArcanaForceXiiTheHangmanFromHand(u8);
u8 TrySpecialSummonVisionHeroFarisFromHand(u8);
u8 TrySpecialSummonApprenticeIllusionMagicianFromHand(u8);
u8 TrySpecialSummonAncientGearStatueFromHand(u8);
u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(u8);
u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(u8);
u8 TrySpecialSummonGandoraGTheDragonOfDestructionFromHand(u8);
u8 TrySpecialSummonTestBearFromHand(u8);
u8 TrySpecialSummonAmazonessSpiritualistFromHand(u8);
u8 TryActivateIllusionOfChaosFromHand(u8);
u8 TrySpecialSummonMaAtFromHand(u8);
u8 TrySpecialSummonNeosWisemanFromHand(u8);
u8 TrySpecialSummonEvilHeroDeadEndPrisonFromHand(u8);
u8 TrySpecialSummonEvilHeroViciousClawsFromHand(u8);
u8 TrySpecialSummonLightrayGearfriedFromHand(u8);
u8 TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeFromHand(u8);
u8 TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(u8);
u8 TrySpecialSummonNibiruThePrimalBeingFromHand(u8);
u8 TrySpecialSummonDestinyHeroDreadnoughtServantFromHand(u8);
u8 TrySpecialSummonMorphtronicScannenFromHand(u8);
u8 TrySpecialSummonGamecialTheSeaTurtleKaijuFromHand(u8);
u8 TrySpecialSummonDestinyHeroDarkAngelFromHand(u8);
u8 TrySpecialSummonGorzTheEmissaryOfDarknessFromHand(u8);
u8 TrySpecialSummonMajestyHyperionFromHand(u8);
u8 TrySpecialSummonTheLegendaryExodiaIncarnateFromHand(u8);
u8 TrySpecialSummonTheAgentOfLifeNeptuneFromHand(u8);
u8 TrySpecialSummonDestinyHeroDestroyDogmaFromHand(u8);
u8 TrySpecialSummonBlueEyesJetDragonFromHand(u8);
u8 TrySpecialSummonMorphtronicSmartfonFromHand(u8);
u8 TrySpecialSummonUltimateConductorTyrannoFromHand(u8);
u8 TrySpecialSummonSilentSwordsmanFromHand(u8);
u8 TrySpecialSummonDivineSerpentGehFromHand(u8);
u8 TrySpecialSummonGuardianDreadscytheFromHand(u8);
void sub_801BC00(void);
unsigned char GetLastNonEmptyMonZoneId(struct DuelCard *zone[]);
s32 NumEmptyZonesInRow(struct DuelCard **row);
unsigned char GetDuelistStatus(unsigned char);

static u8 CardRequiresSpecialSummonOnly(u16 cardId)
{
  return cardId == RARE_METAL_DRAGON || cardId == FENRIR
      || cardId == CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END
      || cardId == BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING
      || cardId == DARK_ARMED_DRAGON
      || cardId == ARMED_DRAGON_LV10
      || cardId == YUBEL_TERROR_INCARNATE || cardId == YUBEL_THE_ULTIMATE_NIGHTMARE
      || cardId == HAMON_LORD_OF_STRIKING_THUNDER
      || cardId == URIA_LORD_OF_SEARING_FLAMES
      || cardId == RAVIEL_LORD_OF_PHANTASMS
      || cardId == MONTAGE_DRAGON || cardId == ARCANA_FORCE_XIX_THE_SUN
      || cardId == OCEAN_DRAGON_LORD_NEO_DAEDALUS || cardId == LIGHTRAY_DAEDALUS
      || cardId == HOLACTIE_THE_CREATOR_OF_LIGHT || cardId == CYBER_ELTANIN
      || cardId == HELIOS_DUO_MEGISTUS || cardId == HELIOS_TRICE_MEGISTUS
      || cardId == RAINBOW_DARK_DRAGON
      || cardId == POSEIDRA_THE_ATLANTEAN_DRAGON || cardId == PUNISHMENT_DRAGON
      || cardId == MAZERA_DEVILLE
      || cardId == MA_AT || cardId == NEOS_WISEMAN
      || cardId == EVIL_HERO_DEAD_END_PRISON
      || cardId == LIGHTRAY_GEARFRIED
      || cardId == MORPHTRONIC_SCANNEN
      || cardId == THE_LEGENDARY_EXODIA_INCARNATE
      || cardId == DESTINY_HERO_DESTROY_DOGMA
      || cardId == MORPHTRONIC_SMARTFON
      || cardId == ULTIMATE_CONDUCTOR_TYRANNO
      || cardId == SILENT_SWORDSMAN
      || cardId == DIVINE_SERPENT_GEH
      || cardId == GUARDIAN_DREADSCYTHE;
}

static void TryPlaceSelectedCardOnField_Local(void)
{
  u16 placedCardId = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;

  SetCardInfo(placedCardId);
  if (CardRequiresSpecialSummonOnly(placedCardId)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }
  switch (GetTypeGroup(gCardInfo.id)) {
    case TYPE_GROUP_SPELL:
    case TYPE_GROUP_TRAP:
    case TYPE_GROUP_RITUAL:
      if (gDuelCursor.currentY == 3) {
        PlayMusic(SFX_PLACE_CARD);
        sub_80449D8();
        CheckWinConditionFINAL();
        TryActivatingPermanentEffects();
      } else {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      }
      break;
    default:
      if (gDuelCursor.currentY != 2) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else if (CourtOfJustice_HandSlotMayIgnition(gDuelCursor.destX)) {
        PlayMusic(SFX_PLACE_CARD);
        sub_80449D8();
        TryActivatingPermanentEffects();
      } else {
        PlayMusic(SFX_PLACE_CARD);
        BlockTurnSummoning(ACTIVE_DUELIST);
        LockMonsterCardsInRow(4);
        RecordPendingSummonTributeCount();
        sub_80449D8();
        TryActivatingPermanentEffects();
        ElementalHeroNecroshade_TryConsumeOnNormalSummon(placedCardId);
        AncientGearCastle_TryConsumeOnNormalSummon(placedCardId);
        AncientGearAdvance_TryConsumeOnNormalSummon(placedCardId);
        AncientGearFactory_TryConsumeOnNormalSummon(placedCardId);
        BigEvolutionPill_TryConsumeOnNormalSummon(placedCardId);
        ChainSummoning_TryUnlockAfterNormalSummon();
        if (placedCardId == GetPendingTributeSummonCardId()) {
          ResetNumTributes();
          ClearPendingTributeSummonCardId();
        }
      }
  }
}

static void FinishEquipSpellTargeting(void)
{
  u8 cursorRow = gDuelCursor.currentY;

  if (cursorRow == PLAYER_MONSTER_ROW)
    sub_8041E70(PLAYER_MONSTER_ROW, PLAYER_BACKROW);

  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}

static void OpenPlayerMonsterActionMenu(void)
{
  if (gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->id != CARD_NONE
      && !gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_SELECT);
    MonsterActionMenu();
  } else {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  }
}


LYN_REPLACE_CHECK(sub_80441D0);
void sub_80441D0__Replacement(void)
{
  switch (gDuelCursor.currentY) {
    case PLAYER_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        OpenPlayerMonsterActionMenu();
      }
      break;
    case OPPONENT_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PerformSoulExchangeOpponentTribute();
        break;
      } else {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      }
      break;
    case PLAYER_BACKROW:
      if (gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id == CARD_NONE) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetRitualNumRequiredTributes(
            gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id);
        if (!numTributes)
          HandlePlayerBackrowAction();
        else {
          PlayMusic(SFX_FORBIDDEN);
          DisplayNumRequiredTributesTextbox(numTributes);
        }
      }
      break;
    case PLAYER_HAND: {
      struct DuelCard *handZone = SixCardHand_GetPlayerHandZone(gDuelCursor.currentX);
      u16 handCardId;
      u8 courtIgnitionSlot;

      if (handZone == NULL) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
        break;
      }

      handCardId = handZone->id;
      courtIgnitionSlot = CourtOfJustice_HandSlotMayIgnition(gDuelCursor.currentX);

      if (handCardId == CARD_NONE) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else if (handZone->isLocked
          && !courtIgnitionSlot) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else if (handCardId == BLUE_EYES_ALTERNATIVE_WHITE_DRAGON
          && TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GILASAURUS
          && TrySpecialSummonGilasaurusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == FENRIR
          && TrySpecialSummonFenrirFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END
          && TrySpecialSummonChaosEmperorDragonEnvoyOfTheEndFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == BLACK_LUSTER_SOLDIER_ENVOY_OF_THE_BEGINNING
          && TrySpecialSummonBlackLusterSoldierEnvoyOfTheBeginningFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_ARMED_DRAGON
          && TrySpecialSummonDarkArmedDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARCHLORD_KRISTYA
          && TrySpecialSummonArchlordKristyaFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ELEMENTAL_HERO_CAPTAIN_GOLD
          && TryActivateElementalHeroCaptainGoldFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HECATRICE
          && TryActivateHecatriceFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GRAVEKEEPERS_COMMANDANT
          && TryActivateGRAVEKEEPERS_COMMANDANTFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ZERADIAS_HERALD_OF_HEAVEN
          && TryActivateZERADIAS_HERALD_OF_HEAVENFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == WARRIOR_OF_ATLANTIS
          && TryActivateWARRIOR_OF_ATLANTISFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HARPIE_QUEEN
          && TryActivateHARPIE_QUEENFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == CHARM_OF_SHABTI
          && TryActivateCHARM_OF_SHABTIFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_BLADE_MASTER
          && TryActivateDESTINY_HERO_BLADE_MASTERFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == EVIL_HERO_ADUSTED_GOLD
          && TryActivateEvilHeroAdustedGoldFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MAGICIANS_ROBE
          && TryActivateMagiciansRobeFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ANCIENT_GEAR
          && TrySpecialSummonAncientGearFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AMAZONESS_BABY_TIGER
          && TrySpecialSummonAmazonessBabyTigerFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AMAZONESS_SPY
          && TrySpecialSummonAmazonessSpyFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == SPELL_STRIKER
          && TrySpecialSummonSpellStrikerFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_GREPHER
          && TrySpecialSummonDarkGrepherFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MAXX_C
          && TryActivateMAXX_CFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARMED_DRAGON_LV10
          && TrySpecialSummonArmedDragonLv10FromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == THE_TRICKY
          && TrySpecialSummonTheTrickyFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HAMON_LORD_OF_STRIKING_THUNDER
          && TrySpecialSummonHamonLordOfStrikingThunderFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == URIA_LORD_OF_SEARING_FLAMES
          && TrySpecialSummonUriaLordOfSearingFlamesFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == RAVIEL_LORD_OF_PHANTASMS
          && TrySpecialSummonRavielLordOfPhantasmsFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == TURBO_BOOSTER
          && TrySpecialSummonTurboBoosterFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GREEN_BABOON_DEFENDER_OF_THE_FOREST
          && TrySpecialSummonGreenBaboonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == BEAST_MACHINE_KING_BARBAROS_UR
          && TrySpecialSummonBeastMachineKingBarbarosUrFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GRAVEKEEPERS_WATCHER
          && TryActivateGravekeepersWatcherFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == REPTILIANNE_VASKII
          && TrySpecialSummonReptilianneVaskiiFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MONTAGE_DRAGON
          && TrySpecialSummonMontageDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARCANA_FORCE_XIX_THE_SUN
          && TrySpecialSummonArcanaForceXixTheSunFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARCANA_FORCE_V_THE_HIEROPHANT
          && TryActivateArcanaForceVTheHierophantFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AROMAGE_LAUREL
          && TrySpecialSummonAromageLaurelFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AROMALILITH_ROSALINA
          && TryActivateAromalilithRosalinaFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == TEST_TIGER
          && TrySpecialSummonTestTigerFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == TIMEAUS_THE_UNITED_DRAGON
          && TrySpecialSummonTimeausTheUnitedDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == OCEAN_DRAGON_LORD_NEO_DAEDALUS
          && TrySpecialSummonOceanDragonLordNeoDaedalusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == THE_AGENT_OF_ENTROPY_URANUS
          && TrySpecialSummonTheAgentOfEntropyUranusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == LIGHTRAY_DAEDALUS
          && TrySpecialSummonLightrayDaedalusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HOLACTIE_THE_CREATOR_OF_LIGHT
          && TrySpecialSummonHolactieTheCreatorOfLightFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == CYBER_ELTANIN
          && TrySpecialSummonCyberEltaninFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HELIOS_DUO_MEGISTUS
          && TrySpecialSummonHeliosDuoMegistusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HELIOS_TRICE_MEGISTUS
          && TrySpecialSummonHeliosTriceMegistusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HARPIE_ORACLE
          && TrySpecialSummonHarpieOracleFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AMAZONESS_WAR_CHIEF
          && TrySpecialSummonAmazonessWarChiefFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MAGICIANS_SOULS
          && TrySpecialSummonMagiciansSoulsFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ORICHALCOS_SHUNOROS
          && TrySpecialSummonOrichalcosShunorosFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == WEISS_LIGHTSWORN_ARCHFIEND
          && TryActivateWeissLightswornArchfiendFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ALECTOR_SOVEREIGN_OF_BIRDS
          && TrySpecialSummonAlectorSovereignOfBirdsFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == RAINBOW_DARK_DRAGON
          && TrySpecialSummonRainbowDarkDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == LIGHTSWORN_DRAGONLING
          && TrySpecialSummonLightswornDragonlingFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ASH_BLOSSOM_AND_JOYOUS_SPRING
          && TryActivateAshBlossomFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == POSEIDRA_THE_ATLANTEAN_DRAGON
          && TrySpecialSummonPoseidraFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == PUNISHMENT_DRAGON
          && TrySpecialSummonPunishmentDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == HONEST
          && TryActivateHonestFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARCANA_FORCE_XV_THE_FIEND
          && TryActivateArcanaForceXvTheFiendFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MASTER_HYPERION
          && TrySpecialSummonMasterHyperionFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_DYNATAG
          && TryActivateDestinyHeroDynatagFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_PLASMA
          && TrySpecialSummonDestinyHeroPlasmaFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == EVIL_HERO_TOXIC_BUBBLE
          && TrySpecialSummonEvilHeroToxicBubbleFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GUARDIAN_EATOS
          && TrySpecialSummonGuardianEatosFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARKNESS_NEOSPHERE
          && TrySpecialSummonDarknessNeosphereFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MAZERA_DEVILLE
          && TrySpecialSummonMazeraDevilleFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == CROSS_KEEPER
          && TryActivateCrossKeeperFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ANDRO_SPHINX
          && TrySpecialSummonAndroSphinxFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GLADIATOR_BEAST_GISTEL
          && TrySpecialSummonGladiatorBeastGistelFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == THE_AGENT_OF_DESTRUCTION_VENUS
          && TrySpecialSummonTheAgentOfDestructionVenusFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == REPTILIANNE_LAMIA
          && TrySpecialSummonReptilianneLamiaFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ARCANA_FORCE_XII_THE_HANGMAN
          && TryActivateArcanaForceXiiTheHangmanFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == VISION_HERO_FARIS
          && TrySpecialSummonVisionHeroFarisFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == APPRENTICE_ILLUSION_MAGICIAN
          && TrySpecialSummonApprenticeIllusionMagicianFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ANCIENT_GEAR_STATUE
          && TrySpecialSummonAncientGearStatueFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC
          && TrySpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS
          && TrySpecialSummonDarkMagicianTheMagicianOfBlackChaosFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GANDORA_G_THE_DRAGON_OF_DESTRUCTION
          && TrySpecialSummonGandoraGTheDragonOfDestructionFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == TEST_BEAR
          && TrySpecialSummonTestBearFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == AMAZONESS_SPIRITUALIST
          && TrySpecialSummonAmazonessSpiritualistFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ILLUSION_OF_CHAOS
          && TryActivateIllusionOfChaosFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MA_AT
          && TrySpecialSummonMaAtFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == NEOS_WISEMAN
          && TrySpecialSummonNeosWisemanFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == EVIL_HERO_DEAD_END_PRISON
          && TrySpecialSummonEvilHeroDeadEndPrisonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == EVIL_HERO_VICIOUS_CLAWS
          && TrySpecialSummonEvilHeroViciousClawsFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == LIGHTRAY_GEARFRIED
          && TrySpecialSummonLightrayGearfriedFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE
          && TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE
          && TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == NIBIRU_THE_PRIMAL_BEING
          && TrySpecialSummonNibiruThePrimalBeingFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_DREADNOUGHT_SERVANT
          && TrySpecialSummonDestinyHeroDreadnoughtServantFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MORPHTRONIC_SCANNEN
          && TrySpecialSummonMorphtronicScannenFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GAMECIAL_THE_SEA_TURTLE_KAIJU
          && TrySpecialSummonGamecialTheSeaTurtleKaijuFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_DARK_ANGEL
          && TrySpecialSummonDestinyHeroDarkAngelFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GORZ_THE_EMISSARY_OF_DARKNESS
          && TrySpecialSummonGorzTheEmissaryOfDarknessFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MAJESTY_HYPERION
          && TrySpecialSummonMajestyHyperionFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == THE_LEGENDARY_EXODIA_INCARNATE
          && TrySpecialSummonTheLegendaryExodiaIncarnateFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == THE_AGENT_OF_LIFE_NEPTUNE
          && TrySpecialSummonTheAgentOfLifeNeptuneFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DESTINY_HERO_DESTROY_DOGMA
          && TrySpecialSummonDestinyHeroDestroyDogmaFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == BLUE_EYES_JET_DRAGON
          && TrySpecialSummonBlueEyesJetDragonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == MORPHTRONIC_SMARTFON
          && TrySpecialSummonMorphtronicSmartfonFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == ULTIMATE_CONDUCTOR_TYRANNO
          && TrySpecialSummonUltimateConductorTyrannoFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == SILENT_SWORDSMAN
          && TrySpecialSummonSilentSwordsmanFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == DIVINE_SERPENT_GEH
          && TrySpecialSummonDivineSerpentGehFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (handCardId == GUARDIAN_DREADSCYTHE
          && TrySpecialSummonGuardianDreadscytheFromHand(gDuelCursor.currentX)) {
        PlayMusic(SFX_PLACE_CARD);
        UpdateDuelGfxExceptField();
        TryActivatingPermanentEffects();
      } else if (CardRequiresSpecialSummonOnly(handCardId)) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetMonsterNumRequiredTributesForHandSlot(
            gDuelCursor.currentX,
            handCardId);
        if (numTributes && !courtIgnitionSlot) {
          if (IsMaskOfRestrictActiveOnField()) {
            PlayMusic(SFX_FORBIDDEN);
            WaitForVBlank();
          } else {
            SetGreatMajuGarzettPendingSummon(handCardId == GREAT_MAJU_GARZETT);
            SetMajuGarzettPendingSummon(handCardId == MAJU_GARZETT);
            /* Clear then arm so a fresh tribute list is used for this summon. */
            SetTheTyrantNeptunePendingSummon(FALSE);
            SetTheTyrantNeptunePendingSummon(handCardId == THE_TYRANT_NEPTUNE);
            SetPendingTributeSummonCardId(handCardId);
            ResetCursorDestToCurrentPos();
            PlayMusic(SFX_FORBIDDEN);
            DisplayNumRequiredTributesTextbox(numTributes);
          }
        } else {
          if (handCardId != GREAT_MAJU_GARZETT)
            SetGreatMajuGarzettPendingSummon(FALSE);
          if (handCardId != MAJU_GARZETT)
            SetMajuGarzettPendingSummon(FALSE);
          if (handCardId != THE_TYRANT_NEPTUNE)
            SetTheTyrantNeptunePendingSummon(FALSE);
          PlayMusic(SFX_SELECT);
          sub_80442AC();
        }
      }
      break;
    }
    default:
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
  }
}

LYN_REPLACE_CHECK(HandlePlayerBackrowAction);
void HandlePlayerBackrowAction__Replacement(void) {
  u16 id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
  struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];

  if (Duel_ZoneIsNonSelectableActivatedBackrow(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsGrandJupiterEquipZone(gDuelCursor.currentY, gDuelCursor.currentX)) {
    if (!CanActivateGrandJupiterEquippedMonster(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    ActivateGrandJupiterEquippedMonster(gDuelCursor.currentY, gDuelCursor.currentX);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  SelectZone(zone);
  ResetCursorDestToCurrentPos();

  if (Duel_IsCardActivationBlocked(id)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (AncientGearDrill_BlocksSpellActivation(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsMysticalSpaceTyphoonCard(id)) {
    if (!FieldHasMysticalSpaceTyphoonTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginMysticalSpaceTyphoonTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsRiryokuCard(id)) {
    if (!FieldHasRiryokuTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginRiryokuTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsBlockAttackCard(id)) {
    if (!FieldHasBlockAttackTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginBlockAttackTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }



  if (IsCreatureSwapCard(id)) {
    if (!FieldHasCreatureSwapTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginCreatureSwapTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == TRIBUTE_DOLL && WhoseTurn() == DUEL_PLAYER) {
    if (!CanActivateTributeDoll()) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginTributeDollTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsNegativeEnergyCard(id)) {
    if (!FieldHasNegativeEnergyTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginNegativeEnergyTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsHHeatedHeartCard(id)) {
    if (!FieldHasHHeatedHeartTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginHHeatedHeartTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsBookOfMoonCard(id)) {
    if (!FieldHasBookOfMoonTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginBookOfMoonTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsBookOfTaiyouCard(id)) {
    if (!FieldHasBookOfTaiyouTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginBookOfTaiyouTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsDeFusionCard(id)) {
    if (!FieldHasDeFusionTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginDeFusionTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsDiffusionWaveMotionCard(id)) {
    if (!FieldHasDiffusionWaveMotionTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginDiffusionWaveMotionTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsRingOfDestructionCard(id)) {
    if (!CanActivateRingOfDestruction()
        || !FieldHasRingOfDestructionTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginRingOfDestructionTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsNightmareWheelCard(id)) {
    if (!CanActivateNightmareWheel()
        || !FieldHasNightmareWheelTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginNightmareWheelTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsDustTornadoCard(id)) {
    if (!FieldHasDustTornadoTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginDustTornadoTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (!zone->isLocked && FieldBarrier_IsFieldSpellCard(id)
      && FieldBarrier_BlocksNewFieldSpellActivation(WhoseTurn())) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (TryRejectSpellActivationGate(id))
    return;

  if (AntiSpellFragrance_BlocksSpellActivation(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == VALHALLA_HALL_OF_THE_FALLEN && zone->isLocked
      && !CanActivateValhallaHallOfTheFallenIgnition(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == COURT_OF_JUSTICE && zone->isLocked
      && !CanActivateCourtOfJusticeIgnition(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (id == R_RIGHTEOUS_JUSTICE
      && !CanActivateRRighteousJustice(gDuelCursor.currentY, gDuelCursor.currentX)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (TryActivateExecutorMakyuraTrapFromBackrow(gDuelCursor.currentY, gDuelCursor.currentX)) {
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  if (IsSoulTakerCard(id)) {
    if (!FieldHasSoulTakerTarget(gDuelCursor.currentY, gDuelCursor.currentX)) {
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      DisplayCardInfoBar();
      sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
      return;
    }

    BeginSoulTakerTargeting(gDuelCursor.currentY, gDuelCursor.currentX);
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  switch (GetSpellType(id)) {
    case SPELL_TYPE_NORMAL: {
      u8 ranPickZone = FALSE;

      gDuelCursor.state = 0;
      gSpellEffectData.id = id;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
        LockMonsterCardsInRow(4);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (gDuelCursor.state == DUEL_CURSOR_PICK_ZONE) {
        ranPickZone = TRUE;
        Duel_RunPickZoneInputLoop();
        Duel_ClearPickZone();
      }
      if (IsDuelOver() != TRUE && !ranPickZone)
        TryActivatingPermanentEffects();
      break;
    }
    case SPELL_TYPE_EQUIP:
      PlayMusic(SFX_SELECT);
      gDuelCursor.state = 2;
      gDuelCursor.currentX = GetFirstNonEmptyMonZoneId(gFixedZones[2]);
      gDuelCursor.currentY = 2;
      break;
    case SPELL_TYPE_INVALID:
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      break;
    default:
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      break;
  }

  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

LYN_REPLACE_CHECK(TrySelectSpellTarget);
void TrySelectSpellTarget__Replacement(void) {
  if (gDuelCursor.currentY != 2) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id == CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (!Duel_SpellMayTargetMonsterZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else {
    SetCardInfo(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
    if (GetTypeGroup(gCardInfo.id) == TYPE_GROUP_MONSTER) {
      gSpellEffectData.id = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;
      gSpellEffectData.row2 = gDuelCursor.destY;
      gSpellEffectData.col2 = gDuelCursor.destX;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
    }
    gDuelCursor.state = 0;
    FinishEquipSpellTargeting();
    TryActivatingPermanentEffects();
  }
}

static u8 PlayerPreferredPlacementCol(u8 fixedRow) {
  u8 col;

  if (gRuntimeConfig.enable_smarter_ai != TRUE)
    return (u8)FirstEmptyZoneInRow(gFixedZones[fixedRow]);

  col = Board_PreferredEmptyFixedCol(fixedRow);
  if (col != 0xFF)
    return col;

  return (u8)FirstEmptyZoneInRow(gFixedZones[fixedRow]);
}

LYN_REPLACE_CHECK(sub_80442AC);
void sub_80442AC__Replacement(void) {
  struct DuelCard *zone;
  u16 id;

  if (gDuelCursor.currentY == PLAYER_HAND)
    zone = SixCardHand_GetPlayerHandZone(gDuelCursor.currentX);
  else
    zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];

  if (zone == NULL)
    return;

  id = zone->id;

  SetGreatMajuGarzettPendingSummon(id == GREAT_MAJU_GARZETT);
  SetMajuGarzettPendingSummon(id == MAJU_GARZETT);
  SetTheTyrantNeptunePendingSummon(id == THE_TYRANT_NEPTUNE);
  if (!PendingTributeSummonStillUnpaid())
    SetPendingTributeSummonCardId(id);
  SelectZone(zone);
  gDuelCursor.state = 1;
  ResetCursorDestToCurrentPos();
  switch (GetTypeGroup(id)) {
  case TYPE_GROUP_MONSTER:
    gDuelCursor.currentX = PlayerPreferredPlacementCol(PLAYER_MONSTER_ROW);
    gDuelCursor.currentY = 2;
    break;
  case TYPE_GROUP_SPELL:
  case TYPE_GROUP_TRAP:
  case TYPE_GROUP_RITUAL:
    gDuelCursor.currentX = PlayerPreferredPlacementCol(PLAYER_BACKROW);
    gDuelCursor.currentY = 3;
    break;
  default:
    break;
  }
  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

LYN_REPLACE_CHECK(sub_80449D8);
void sub_80449D8__Replacement(void)
{
  u8 placedRow;
  u8 placedCol;

  if (!TryPayChainEnergyCost()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (!TryConsumeUltimateOfferingExtraSummonPayment()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (!TryConsumeCourtOfJusticeIgnitionPlacement()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (ShouldBlockGodCardSummon(gSelectedCard.id)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  placedRow = gDuelCursor.currentY;
  placedCol = gDuelCursor.currentX;

  if ((placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW)
      && ArchlordKristya_ShouldBlockFieldPlacement(gSelectedCard.id,
                                                   GetPendingSummonTributeCount())) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (CardRequiresSpecialSummonOnly(gSelectedCard.id)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_MONSTER
      && gSelectedCard.isDefending
      && AncientGearAdvance_CannotSetThisTurn()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if ((GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_SPELL
       || GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_TRAP
       || GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_RITUAL)
      && ColdWave_IsSpellTrapPlayOrSetLocked()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (gRuntimeConfig.enable_smarter_ai == TRUE) {
    u8 preferredCol;

    if (placedRow == PLAYER_MONSTER_ROW)
      preferredCol = Board_PreferredEmptyFixedCol(PLAYER_MONSTER_ROW);
    else if (placedRow == PLAYER_BACKROW)
      preferredCol = Board_PreferredEmptyFixedCol(PLAYER_BACKROW);
    else
      preferredCol = 0xFF;

    if (preferredCol != 0xFF)
      placedCol = preferredCol;
  }

  if (gFixedZones[placedRow][placedCol]->id != CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if ((placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW)
      && !KaiserColosseum_AllowsMonsterPlacement(placedRow)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (gSelectedCard.id == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    MarkAbsoluteZeroHandSummonCleanup();
  {
    struct DuelCard *sourceZone;
    bool32 _summonAnim = TryPlaySummonAnimation(gSelectedCard.id);

    if (gDuelCursor.destY == PLAYER_HAND)
      sourceZone = SixCardHand_GetPlayerHandZone(gDuelCursor.destX);
    else
      sourceZone = gFixedZones[gDuelCursor.destY][gDuelCursor.destX];

    if (sourceZone != NULL)
      ClearZone(sourceZone);
    CopySelectedCardToZone(gFixedZones[placedRow][placedCol]);
    if (placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW) {
      TryEnforceBerserkGorillaOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryActivateGranadoraOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryBreakerTheMagicalWarriorOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryRivalryOfWarlordsOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryLevelLimitAreaBOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryLevelLimitAreaAOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryRingOfDestructionOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryAmazonessTigerOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryBlastHeldByATributeOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryVengefulBogSpiritOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryElementalHeroGreatTornadoOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryTheWickedDreadrootOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryTheWickedEraserOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryTheWickedAvatarOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryElementalHeroSunriseOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
      TryElementalHeroAbsoluteZeroOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    }
    if (placedRow == PLAYER_MONSTER_ROW) {
      TryApplyPreciousCardsFromBeyondOnTributeSummon(
          gFixedZones[placedRow][placedCol]->id, WhoseTurn());
    }
    FinishGreatMajuGarzettTributeSummon(
        gFixedZones[placedRow][placedCol], placedRow, placedCol);
    FinishMajuGarzettTributeSummon(
        gFixedZones[placedRow][placedCol], placedRow, placedCol);
    FinishTheTyrantNeptuneTributeSummon(
        gFixedZones[placedRow][placedCol], placedRow, placedCol);
    if (placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW)
      CourtOfJustice_FinishHandPlacement(gFixedZones[placedRow][placedCol]);
    MarkUltimateOfferingJustSet(gFixedZones[placedRow][placedCol]);
    MarkFairyBoxJustSet(gFixedZones[placedRow][placedCol]);
    MarkMirrorWallJustSet(gFixedZones[placedRow][placedCol]);
    MarkBottomlessShiftingSandJustSet(gFixedZones[placedRow][placedCol]);
    TryEnableUltimateOfferingExtraSummonAfterPlacement();
    TryEnableCourtOfJusticeIgnitionAfterPlacement();
    TryEnableValhallaHallOfTheFallenIgnitionAfterPlacement();
    UpdateDuelGfxExceptField();
    if (_summonAnim == TRUE)
      FinishSummonAnimation();
  }
  /* ponytail: on-summon text after field draw so Blazeman/Stratos is visible. */
  if (placedRow == PLAYER_MONSTER_ROW || placedRow == OPPONENT_MONSTER_ROW) {
    FinishTheTripperMercuryTributeSummon(
        gFixedZones[placedRow][placedCol], placedRow, placedCol);
    FinishTheWickedAvatarTributeSummon(
        gFixedZones[placedRow][placedCol], placedRow, placedCol);
    TryActivateRyuKishinClownOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryActivateDarkDustSpiritOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryElementalHeroBlazemanOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryTheWickedDreadrootEffectTextOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryIofielOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryAthenaOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryElementalHeroStratosOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    TryTheSuppressionPlutoOnMonsterPlacement(gFixedZones[placedRow][placedCol]);
    EffectEvent_EmitSimple(EFFECT_EVENT_ON_SUMMON,
                           gFixedZones[placedRow][placedCol]->id,
                           gFixedZones[placedRow][placedCol]);
  }
  if (gDuelCursor.state != DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET) {
    gDuelCursor.state = 0;
    ResetCursorDestToCurrentPos();
  }
}

LYN_REPLACE_CHECK(sub_8044570);
void sub_8044570__Replacement(void)
{
  unsigned char turn = WhoseTurn();

  if (GetDuelistStatus(turn) == DUELIST_STATUS_CANNOT_ATTACK) {
    PlayMusic(SFX_FORBIDDEN);
    gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
    UpdateDuelGfxExceptField();
  } else if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()) {
    PlayMusic(SFX_FORBIDDEN);
    gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
    UpdateDuelGfxExceptField();
  } else if (!VengefulBogSpirit_CanMonsterAttack(
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    PlayMusic(SFX_FORBIDDEN);
    UpdateDuelGfxExceptField();
  } else if (!Duel_CanMonsterDeclareAttack(
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    PlayMusic(SFX_FORBIDDEN);
    gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
    UpdateDuelGfxExceptField();
  } else if ((NumEmptyZonesInRow(gTurnZones[1]) == MAX_ZONES_IN_ROW
      || CanNightmareHorseAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanServantOfCatabolismAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanAmphibiousBugrothMk3AttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanBlackTyrannoAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanReaperOnTheNightmareAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanDrillagoAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanThunderNyanNyanAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanElementalHeroMarinerAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanElementalHeroKnospeAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)
      || CanElementalHeroIceEdgeAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || CanNeoSpacianGlowMossAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || CanJowlsControlledMonsterAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || HeroFlash_CanMonsterAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || CanInfectedMailMonsterAttackDirectly(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]))
      && !Duel_ForcedAttackBlocksDirect(
          WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER)
      && !ChimeratechOverdragon_BlocksDirectAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    if (!DebugRuleset_AllowDirectAttacks()) {
      PlayMusic(SFX_FORBIDDEN);
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      UpdateDuelGfxExceptField();
    } else {
    gTrapEffectData.originRow = gDuelCursor.currentY;
    gTrapEffectData.originCol = gDuelCursor.currentX;
    gTrapEffectData.originCardId = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
    TryActivateEmbodimentOfApophisOnAttack();
    if (TryNegateDeclaredAttackWithCyberBarrierDragon()) {
      PlayMusic(SFX_ATTACK_REBUFFED);
      gDuelCursor.state = 0;
      return;
    }
    if (SasukeSamurai2_AreInactiveBackrowTrapsBlocked()
        || AncientGear_AttackerBlocksOppSpellTrap(
               gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
        || IsTrapTriggered() != 1) {
      if (!TryPayAttackFieldCosts()) {
        PlayMusic(SFX_FORBIDDEN);
        gDuelCursor.state = 0;
        return;
      }
      PlayMusic(SFX_SELECT);
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp = 1;
      Duel_NotifyMonsterZoneChanged(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      MarkMonsterDeclaredAttackThisTurn(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryArmElementalHeroSunriseOnAttackDeclared(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], NULL);
      ApplyAromaGardeningAttackDeclare();
      LightswornBarrier_OnAttackDeclare(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], NULL);
      Flavian_OnAttackDeclare();
      TryShowBlackTyrannoDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      TryShowDrillagoDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      TryShowThunderNyanNyanDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      TryShowElementalHeroMarinerDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      TryShowElementalHeroKnospeDirectAttackText(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
      PerformDirectAttackOrRedirectToEmbodimentOfApophis(gDuelCursor.currentX);
      TryApplyFairyBoxToPendingAction();
      TryApplyMirrorWallToPendingAction();
      TryApplyElementalHeroCoreAtkDouble();
      TryApplyElementalHeroCoreAtkDouble();
      TryApplyCatsEarTribeToPendingAction();
      TryApplySpiritRyuToPendingAction();
      HandleAtkAndLifePointsAction();
      DebugRuleset_MarkAttackUsed();
      TheDarkDoor_MarkAttackUsed();
      CheckGraveyardAndLoserFlags();
      TryUnlockHayabusaKnightForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockMermaidKnightForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTryceEquipForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTyrantDragonForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockCyberTwinDragonForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTheTripperMercuryForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockChimeratechOverdragonForNextAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockBlackLusterSoldierEnvoyForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockElementalHeroWildedgeForNextAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], NULL);
      TryUnlockAmazonessCallForNextAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], NULL);
      TryUnlockDForcePlasmaForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockTyrantWingForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockArcanaForceExDarkRulerForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockDestinyHeroDoubleDudeForSecondAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockNeutronBlastForExtraAttack(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      {
        u8 fr;
        u8 fc;
        u8 fixed;

        if (Duel_FindFixedMonsterZone(
                gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], &fr, &fc)) {
          fixed = Duel_FixedDuelistForMonsterRow(fr);
          D_Burst_ActivateGyBattle(
              gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], fixed);
        }
      }
      gDuelCursor.state = 0;
      sub_801BC00();
      UpdateAllDuelGfx();
      ResolveTheUnhappyMaidenBattleEffect();
      ResolveVampireBabyBattleEffect();
      ResolveGhostKnightOfJackalBattleEffect();
      ResolveArcanaForceViiChariotBattleEffect();
      ResolveAmazonessSpyBattleEffect();
      ResolveAmazonessTraineeBattleEffect();
      ResolveAmazonessSageBattleEffect();
      ResolveMefistTheInfernalGeneralDiscardBattleEffect();
      ResolveReaperOnTheNightmareDirectDamageEffect();
      ResolveSpiritReaperDiscardBattleEffect();
      ResolveGuardianAngelJoanBattleEffect();
      ResolveRoyalKnightBattleEffect();
      ResolveElementalHeroSteamHealerBattleEffect();
      ResolveElementalHeroFlameWingmanBattleEffect();
      ResolveLesserFiendBattleEffect();
      ResolveDarkMagicianOfChaosBattleEffect();
      ResolveAirknightParshathDrawBattleEffect();
      ResolveSasukeSamurai3BattleEffect();
      ResolveNeedleBurrowerBattleEffect();
      ResolveHyperHammerheadBattleEffect();
      ResolveNeoSpacianGrandMoleBattleEffect();
      ResolveLightningWarriorBattleEffect();
      ResolveNeoSpacianGlowMossBattleEffect();
      ResolveNeoSpacianTwinkleMossBattleEffect();
      ResolveReptilianneGorgonBattleEffect();
      ResolveDonZaloogBattleEffect();
      ResolveRedDragonArchfiendBattleEffect();
      ResolveReptilianneScyllaBattleEffect();
      ResolveDDWarriorBattleEffect();
      ResolveDesKangarooBattleEffect();
      ResolveContinuousDestructionPunchBattleEffect();
      ResolveAmazonessHeirloomBattleEffect();
      ResolveAbsorbingKidFromTheSkyBattleEffect();
      ResolveCoffinSellerBattleEffect();
      sub_8022080();
      FinishGraveyardDrawBattleResolve();
    } else {
      if (!TryPayAttackFieldCosts()) {
        PlayMusic(SFX_FORBIDDEN);
        gDuelCursor.state = 0;
        return;
      }
      if (AttackFieldCostsRequireCoTHResumeSkip())
        MarkCallOfTheHauntedAttackTollPaid();
      PlayMusic(SFX_ATTACK_REBUFFED);
      ActivateTrapEffect(0);
      TryResumeInterruptedAttackAfterCallOfTheHaunted();
      gDuelCursor.state = 0;
    }
    TryActivatingPermanentEffects();
    /* PickZone last — after attack cleanup and permanent effects, so targeting
     * survives into PlayerTurnMain (inline resolve was wiped by state = 0). */
    ResolveElementalHeroCoreBattledEffect();
    ResolveElementalHeroIceEdgeBattleEffect();
    ResolveYubelAttackedReflectEffect();
    ResolveElementalHeroSunriseDestroyEffect();
    ResolveHamonLordOfStrikingThunderBattleEffect();
    }
  } else {
    PlayMusic(SFX_SELECT);
    SelectZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
    gDuelCursor.state = 4;
    ResetCursorDestToCurrentPos();
    gDuelCursor.currentX = GetLastNonEmptyMonZoneId(&gFixedZones[1][4]);
    gDuelCursor.currentY = 1;
    RefreshPendingSasukeBattleTarget();
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    UpdateDuelGfxExceptField();
  }
}

LYN_REPLACE_CHECK(TryAttackWithMonster);
void TryAttackWithMonster__Replacement(void)
{
  if (gDuelCursor.currentY != 1) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id == CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()
      || !Duel_CanMonsterDeclareAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX])
      || !Duel_CanAttackMonsterZone(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])
      || !Duel_MonsterMayBeAttacked(
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else {
    gTrapEffectData.originRow = gDuelCursor.destY;
    gTrapEffectData.originCol = gDuelCursor.destX;
    gTrapEffectData.originCardId = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;
    TryActivateEmbodimentOfApophisOnAttack();
    if (TryNegateDeclaredAttackWithCyberBarrierDragon()) {
      PlayMusic(SFX_ATTACK_REBUFFED);
      gDuelCursor.state = 0;
      return;
    }
    if (SasukeSamurai2_AreInactiveBackrowTrapsBlocked()
        || AncientGear_AttackerBlocksOppSpellTrap(
               gFixedZones[gDuelCursor.destY][gDuelCursor.destX])
        || IsTrapTriggered() != 1) {
      if (!TryPayAttackFieldCosts()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
        return;
      }
      PlayMusic(SFX_SELECT);
      RefreshPendingSasukeBattleTarget();
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isDefending = 0;
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isFaceUp = 1;
      Duel_NotifyMonsterZoneChanged(gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->isLocked = 1;
      MarkMonsterDeclaredAttackThisTurn(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryArmElementalHeroSunriseOnAttackDeclared(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX],
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      ApplyAromaGardeningAttackDeclare();
      LightswornBarrier_OnAttackDeclare(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX],
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      Flavian_OnAttackDeclare();
      SetAttackAction(gDuelCursor.destX, gDuelCursor.currentX);
      TryApplyFairyBoxToPendingAction();
      TryApplyMirrorWallToPendingAction();
      TryApplyElementalHeroCoreAtkDouble();
      TryApplyCatsEarTribeToPendingAction();
      TryApplySpiritRyuToPendingAction();
      RunMonsterBattleAction();
      if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id != CARD_NONE) {
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp = 1;
        TryAromaJarOnFaceUp(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        TryActivateFlipDeckSearchOnFaceUp(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        Duel_NotifyMonsterZoneChanged(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      }
      DebugRuleset_MarkAttackUsed();
      TheDarkDoor_MarkAttackUsed();
      CheckGraveyardAndLoserFlags();
      TryUnlockHayabusaKnightForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockMermaidKnightForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTryceEquipForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTyrantDragonForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockCyberTwinDragonForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTheTripperMercuryForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockChimeratechOverdragonForNextAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockBlackLusterSoldierEnvoyForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockElementalHeroWildedgeForNextAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX],
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockAmazonessCallForNextAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX],
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
      TryUnlockDForcePlasmaForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockTyrantWingForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockArcanaForceExDarkRulerForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockDestinyHeroDoubleDudeForSecondAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      TryUnlockNeutronBlastForExtraAttack(
          gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
      {
        u8 fr;
        u8 fc;
        u8 fixed;

        if (Duel_FindFixedMonsterZone(
                gFixedZones[gDuelCursor.destY][gDuelCursor.destX], &fr, &fc)) {
          fixed = Duel_FixedDuelistForMonsterRow(fr);
          D_Burst_ActivateGyBattle(
              gFixedZones[gDuelCursor.destY][gDuelCursor.destX], fixed);
        }
      }
      gDuelCursor.state = 0;
      SetCursorToCardDest();
      sub_801BC00();
      UpdateAllDuelGfx();
      ResolveTheUnhappyMaidenBattleEffect();
      ResolveVampireBabyBattleEffect();
      ResolveGhostKnightOfJackalBattleEffect();
      ResolveArcanaForceViiChariotBattleEffect();
      ResolveAmazonessSpyBattleEffect();
      ResolveAmazonessTraineeBattleEffect();
      ResolveAmazonessSageBattleEffect();
      ResolveMefistTheInfernalGeneralDiscardBattleEffect();
      ResolveReaperOnTheNightmareDirectDamageEffect();
      ResolveSpiritReaperDiscardBattleEffect();
      ResolveGuardianAngelJoanBattleEffect();
      ResolveRoyalKnightBattleEffect();
      ResolveElementalHeroSteamHealerBattleEffect();
      ResolveElementalHeroFlameWingmanBattleEffect();
      ResolveLesserFiendBattleEffect();
      ResolveDarkMagicianOfChaosBattleEffect();
      ResolveAirknightParshathDrawBattleEffect();
      ResolveSasukeSamurai3BattleEffect();
      ResolveNeedleBurrowerBattleEffect();
      ResolveHyperHammerheadBattleEffect();
      ResolveNeoSpacianGrandMoleBattleEffect();
      ResolveLightningWarriorBattleEffect();
      ResolveNeoSpacianGlowMossBattleEffect();
      ResolveNeoSpacianTwinkleMossBattleEffect();
      ResolveReptilianneGorgonBattleEffect();
      ResolveDonZaloogBattleEffect();
      ResolveRedDragonArchfiendBattleEffect();
      ResolveReptilianneScyllaBattleEffect();
      ResolveDDWarriorBattleEffect();
      ResolveDesKangarooBattleEffect();
      ResolveContinuousDestructionPunchBattleEffect();
      ResolveAmazonessHeirloomBattleEffect();
      ResolveAbsorbingKidFromTheSkyBattleEffect();
      ResolveCoffinSellerBattleEffect();
      sub_8022080();
      FinishGraveyardDrawBattleResolve();
    } else {
      if (!TryPayAttackFieldCosts()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
        return;
      }
      if (AttackFieldCostsRequireCoTHResumeSkip())
        MarkCallOfTheHauntedAttackTollPaid();
      ActivateTrapEffect(0);
      TryResumeInterruptedAttackAfterCallOfTheHaunted();
      gDuelCursor.state = 0;
      SetCursorToCardDest();
      UpdateDuelGfxExceptField();
    }
    TryActivatingPermanentEffects();
    /* PickZone last — after attack cleanup and permanent effects, so targeting
     * survives into PlayerTurnMain (inline resolve was wiped by state = 0). */
    ResolveElementalHeroCoreBattledEffect();
    ResolveElementalHeroIceEdgeBattleEffect();
    ResolveYubelAttackedReflectEffect();
    ResolveElementalHeroSunriseDestroyEffect();
  }
}

LYN_REPLACE_CHECK(HandleAButtonAction);
void HandleAButtonAction__Replacement(void)
{
  if (Duel_TryNegateMonsterEffectTargetSelection())
    return;

  switch (gDuelCursor.state) {
    case 0:
      sub_80441D0__Replacement();
      break;
    case 1:
      TryPlaceSelectedCardOnField_Local();
      break;
    case 2:
      TrySelectSpellTarget();
      break;
    case DUEL_CURSOR_MST_TARGET:
      TrySelectMysticalSpaceTyphoonTarget();
      break;
    case DUEL_CURSOR_RIRYOKU_SOURCE:
      TrySelectRiryokuSourceTarget();
      break;
    case DUEL_CURSOR_RIRYOKU_RECIPIENT:
      TrySelectRiryokuRecipientTarget();
      break;
    case 4:
      TryAttackWithMonster();
      break;
    case DUEL_CURSOR_CANNON_SOLDIER_TARGET:
      TrySelectCannonSoldierTarget();
      break;
    case DUEL_CURSOR_MAN_THRO_TRO_TARGET:
      TrySelectManThroTroTarget();
      break;
    case DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET:
      TrySelectBreakerTheMagicalWarriorTarget();
      break;
    case DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET:
      TrySelectJowlsOfDarkDemiseTarget();
      break;
    case DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET:
      TrySelectInvaderOfTheThroneTarget();
      break;
    case DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET:
      TrySelectDarkMagicianKnightTarget();
      break;
    case DUEL_CURSOR_ZABORG_THE_THUNDER_MONARCH_TARGET:
      TrySelectZaborgTheThunderMonarchTarget();
      break;
    case DUEL_CURSOR_CAIUS_THE_SHADOW_MONARCH_TARGET:
      TrySelectCaiusTheShadowMonarchTarget();
      break;
    case DUEL_CURSOR_MOBIUS_THE_FROST_MONARCH_TARGET:
      TrySelectMobiusTheFrostMonarchTarget();
      break;
    case DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET:
      TrySelectRyuKishinClownTarget();
      break;
    case DUEL_CURSOR_BLOCK_ATTACK_TARGET:
      TrySelectBlockAttackTarget();
      break;
    case DUEL_CURSOR_SOUL_TAKER_TARGET:
      TrySelectSoulTakerTarget();
      break;
    case DUEL_CURSOR_CREATURE_SWAP_OWN:
      TrySelectCreatureSwapOwnTarget();
      break;
    case DUEL_CURSOR_NEGATIVE_ENERGY_TARGET:
      TrySelectNegativeEnergyTarget();
      break;
    case DUEL_CURSOR_TRIBUTE_DOLL_TARGET:
      TrySelectTributeDollTarget();
      break;
    case DUEL_CURSOR_H_HEATED_HEART_TARGET:
      TrySelectHHeatedHeartTarget();
      break;
    case DUEL_CURSOR_BOOK_OF_MOON_TARGET:
      TrySelectBookOfMoonTarget();
      break;
    case DUEL_CURSOR_BOOK_OF_TAIYOU_TARGET:
      TrySelectBookOfTaiyouTarget();
      break;
    case DUEL_CURSOR_DE_FUSION_TARGET:
      TrySelectDeFusionTarget();
      break;
    case DUEL_CURSOR_DIFFUSION_WAVE_MOTION_TARGET:
      TrySelectDiffusionWaveMotionTarget();
      break;
    case DUEL_CURSOR_RING_OF_DESTRUCTION_TARGET:
      TrySelectRingOfDestructionTarget();
      break;
    case DUEL_CURSOR_NIGHTMARE_WHEEL_TARGET:
      TrySelectNightmareWheelTarget();
      break;
    case DUEL_CURSOR_DUST_TORNADO_TARGET:
      TrySelectDustTornadoTarget();
      break;
    case DUEL_CURSOR_ECTOPLASMER_TARGET:
      TrySelectEctoplasmerTarget();
      break;
    case DUEL_CURSOR_KAISER_GLIDER_TARGET:
      TrySelectKaiserGliderTarget();
      break;
    case DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1:
    case DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2:
      TrySelectAmazonessArcherTarget();
      break;
    case DUEL_CURSOR_HARPIES_PET_BABY_DRAGON_TARGET:
      TrySelectHarpiesPetBabyDragonTarget();
      break;
    case DUEL_CURSOR_BLOWBACK_DRAGON_TARGET:
      TrySelectBlowbackDragonTarget();
      break;
    case DUEL_CURSOR_DARK_END_DRAGON_TARGET:
      TrySelectDarkEndDragonTarget();
      break;
    case DUEL_CURSOR_LIGHT_END_DRAGON_TARGET:
      TrySelectLightEndDragonTarget();
      break;
    case DUEL_CURSOR_CYBER_LASER_DRAGON_TARGET:
      TrySelectCyberLaserDragonTarget();
      break;
    case DUEL_CURSOR_BLACK_LUSTER_SOLDIER_ENVOY_TARGET:
      TrySelectBlackLusterSoldierEnvoyTarget();
      break;
    case DUEL_CURSOR_TERRA_FIRMA_TARGET:
      TrySelectElementalHeroTerraFirmaTarget();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_WILD_WINGMAN_TARGET:
      TrySelectElementalHeroWildWingmanTarget();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_GAIA_TARGET:
      TrySelectElementalHeroGaiaTarget();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_PLASMA_VICE_TARGET:
      TrySelectElementalHeroPlasmaViceTarget();
      break;
    case DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET:
      TrySelectTheGrandJupiterAbsorbTarget();
      break;
    case DUEL_CURSOR_ATHENA_COST_TARGET:
      TrySelectAthenaCostTarget();
      break;
    case DUEL_CURSOR_YUBEL_TRIBUTE_TARGET:
      TrySelectYubelTributeTarget();
      break;
    case DUEL_CURSOR_PICK_ZONE:
      Duel_HandlePickZoneA();
      break;
  }
}

LYN_REPLACE_CHECK(HandleBButtonAction);
void HandleBButtonAction__Replacement(void)
{
  switch (gDuelCursor.state) {
    case 0:
      OpenBMenu();
      break;
    case 1:
      sub_8044A30();
      break;
    case 2:
      sub_8044A5C();
      break;
    case DUEL_CURSOR_MST_TARGET:
      CancelMysticalSpaceTyphoonTargeting();
      break;
    case DUEL_CURSOR_RIRYOKU_SOURCE:
    case DUEL_CURSOR_RIRYOKU_RECIPIENT:
      CancelRiryokuTargeting();
      break;
    case DUEL_CURSOR_CANNON_SOLDIER_TARGET:
    case DUEL_CURSOR_MAN_THRO_TRO_TARGET:
    case DUEL_CURSOR_ECTOPLASMER_TARGET:
    case DUEL_CURSOR_YUBEL_TRIBUTE_TARGET:
    case DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1:
    case DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2:
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
      break;
    case DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET:
      CancelBreakerTheMagicalWarriorTargeting();
      break;
    case DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET:
      CancelJowlsOfDarkDemiseTargeting();
      break;
    case DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET:
      CancelInvaderOfTheThroneTargeting();
      break;
    case DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET:
      CancelDarkMagicianKnightTargeting();
      break;
    case DUEL_CURSOR_ZABORG_THE_THUNDER_MONARCH_TARGET:
      CancelZaborgTheThunderMonarchTargeting();
      break;
    case DUEL_CURSOR_CAIUS_THE_SHADOW_MONARCH_TARGET:
      CancelCaiusTheShadowMonarchTargeting();
      break;
    case DUEL_CURSOR_MOBIUS_THE_FROST_MONARCH_TARGET:
      CancelMobiusTheFrostMonarchTargeting();
      break;
    case DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET:
      CancelRyuKishinClownTargeting();
      break;
    case DUEL_CURSOR_BLOCK_ATTACK_TARGET:
      CancelBlockAttackTargeting();
      break;
    case DUEL_CURSOR_SOUL_TAKER_TARGET:
      CancelSoulTakerTargeting();
      break;
    case DUEL_CURSOR_CREATURE_SWAP_OWN:
      CancelCreatureSwapTargeting();
      break;
    case DUEL_CURSOR_NEGATIVE_ENERGY_TARGET:
      CancelNegativeEnergyTargeting();
      break;
    case DUEL_CURSOR_TRIBUTE_DOLL_TARGET:
      CancelTributeDollTargeting();
      break;
    case DUEL_CURSOR_H_HEATED_HEART_TARGET:
      CancelHHeatedHeartTargeting();
      break;
    case DUEL_CURSOR_BOOK_OF_MOON_TARGET:
      CancelBookOfMoonTargeting();
      break;
    case DUEL_CURSOR_BOOK_OF_TAIYOU_TARGET:
      CancelBookOfTaiyouTargeting();
      break;
    case DUEL_CURSOR_DE_FUSION_TARGET:
      CancelDeFusionTargeting();
      break;
    case DUEL_CURSOR_DIFFUSION_WAVE_MOTION_TARGET:
      CancelDiffusionWaveMotionTargeting();
      break;
    case DUEL_CURSOR_RING_OF_DESTRUCTION_TARGET:
      CancelRingOfDestructionTargeting();
      break;
    case DUEL_CURSOR_NIGHTMARE_WHEEL_TARGET:
      CancelNightmareWheelTargeting();
      break;
    case DUEL_CURSOR_DUST_TORNADO_TARGET:
      CancelDustTornadoTargeting();
      break;
    case DUEL_CURSOR_KAISER_GLIDER_TARGET:
      CancelKaiserGliderTargeting();
      break;
    case DUEL_CURSOR_HARPIES_PET_BABY_DRAGON_TARGET:
      CancelHarpiesPetBabyDragonTargeting();
      break;
    case DUEL_CURSOR_BLOWBACK_DRAGON_TARGET:
      CancelBlowbackDragonTargeting();
      break;
    case DUEL_CURSOR_DARK_END_DRAGON_TARGET:
      CancelDarkEndDragonTargeting();
      break;
    case DUEL_CURSOR_LIGHT_END_DRAGON_TARGET:
      CancelLightEndDragonTargeting();
      break;
    case DUEL_CURSOR_CYBER_LASER_DRAGON_TARGET:
      CancelCyberLaserDragonTargeting();
      break;
    case DUEL_CURSOR_BLACK_LUSTER_SOLDIER_ENVOY_TARGET:
      CancelBlackLusterSoldierEnvoyTargeting();
      break;
    case DUEL_CURSOR_TERRA_FIRMA_TARGET:
      CancelElementalHeroTerraFirmaTargeting();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_WILD_WINGMAN_TARGET:
      CancelElementalHeroWildWingmanTargeting();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_GAIA_TARGET:
      CancelElementalHeroGaiaTargeting();
      break;
    case DUEL_CURSOR_ELEMENTAL_HERO_PLASMA_VICE_TARGET:
      CancelElementalHeroPlasmaViceTargeting();
      break;
    case DUEL_CURSOR_THE_GRAND_JUPITER_ABSORB_TARGET:
      CancelTheGrandJupiterAbsorbTargeting();
      break;
    case DUEL_CURSOR_ATHENA_COST_TARGET:
      CancelAthenaCostTargeting();
      break;
    case DUEL_CURSOR_PICK_ZONE:
      Duel_HandlePickZoneB();
      break;
    case 4:
      sub_8044A88();
      break;
  }
}
