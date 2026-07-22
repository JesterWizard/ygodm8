#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "contact_gate.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "en_engage_neo_space.h"
#include "evil_assault.h"
#include "field_barrier.h"
#include "forbidden_dress.h"
#include "forbidden_lance.h"
#include "flavian_colosseum_of_the_gladiator_beasts.h"
#include "fusion_deployment.h"
#include "fusion_destiny.h"
#include "gadget_box.h"
#include "colosseum_cage_of_the_gladiator_beasts.h"
#include "cannot_attack_this_turn.h"
#include "gladiator_beasts_medusa_shield.h"
#include "d_force.h"
#include "duel_status.h"
#include "effect_events.h"
#include "god_card.h"
#include "mask_of_restrict.h"
#include "mini_card.h"
#include "summon_tribute.h"
#include "raregold_armor.h"
#include "double_tool_c_and_d.h"
#include "rivalry_of_warlords.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "ring_of_destruction.h"
#include "amazoness_tiger.h"
#include "amazoness_baby_tiger.h"
#include "amazoness_call.h"
#include "gladiator_beasts_valor.h"
#include "blast_held_by_a_tribute.h"
#include "breaker_the_magical_warrior.h"
#include "vengeful_bog_spirit.h"
#include "tribute.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "kishido_spirit.h"
#include "lady_of_d.h"
#include "light_of_destruction.h"
#include "light_spiral.h"
#include "ryu_kishin_clown.h"
#include "dark_dust_spirit.h"
#include "kaiser_colosseum.h"
#include "six_card_hand.h"
#include "elemental_hero_tempest.h"
#include "elemental_hero_neos_alius.h"
#include "elemental_hero_great_tornado.h"
#include "the_wicked_dreadroot.h"
#include "evil_hero_dark_gaia.h"
#include "harpie_perfumer.h"
#include "oshaleon.h"
#include "reptilianne_servant.h"
#include "morphtronic_cameran.h"
#include "morphtronic_magnen.h"
#include "morphtronic_staplen.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "cold_wave.h"
#include "elemental_hero_sunrise.h"
#include "elemental_hero_absolute_zero.h"
#include "elemental_hero_blazeman.h"
#include "iofiel.h"
#include "athena.h"
#include "archlord_kristya.h"
#include "crimson_blader.h"
#include "elemental_hero_stratos.h"
#include "the_suppression_pluto.h"
#include "elemental_hero_core.h"
#include "summon_animations.h"
#include "the_supremacy_sun.h"
#include "yubel.h"
#include "chimeratech_overdragon.h"
#include "fusion_duel.h"
#include "synchro_duel.h"
#include "the_tyrant_neptune.h"
#include "the_grand_jupiter.h"
#include "lyrilusc_independent_nightingale.h"
#include "theban_nightmare.h"
#include "hamon_lord_of_striking_thunder.h"
#include "hidden_temples_of_necrovalley.h"
#include "parallel_world_fusion.h"
#include "power_filter.h"
#include "return_of_the_dragon_lords.h"
#include "shining_sarcophagus.h"
#include "el_shaddoll_winda.h"
#include "el_shaddoll_anoyatyllis.h"
#include "ancient_gear_cannon.h"
#include "mirage_dragon.h"
#include "protector_of_the_sanctuary.h"
#include "spell_counter_on_resolve.h"
#include "amazoness_scouts.h"
#include "amazoness_augusta.h"
#include "blue_eyes_alternative_ultimate_dragon.h"
#include "aromalilith_magnolia.h"
#include "neos_wiseman.h"
#include "azure_eyes_silver_dragon.h"
#include "blue_eyes_protect.h"
#include "evil_hero_infernal_sniper.h"
#include "jenis_lightsworn_mender.h"
#include "wulf_lightsworn_beast.h"
#include "garoth_lightsworn_warrior.h"
#include "silent_magician_lv4.h"
#include "silent_magician_lv8.h"
#include "aromaseraphy_sweet_marjoram.h"
#include "uria_lord_of_searing_flames.h"
#include "raviel_lord_of_phantasms.h"
#include "expanded_graveyard.h"
#include "fusion_recipes.h"
#include "removed_from_play.h"
#include "harpie_lady_phoenix_formation.h"
#include "harpies_feather_rest.h"
#include "spell_effects.h"
#include "amazoness_princess.h"
#include "destiny_hero_decider.h"
#include "destiny_hero_drawhand.h"
#include "minerva_lightsworn_maiden.h"
#include "on_summon_hooks.h"
#include "junk_synchron.h"
#include "deep_sea_diva.h"
#include "barrier_statue_wind_lock.h"
#include "card_name_overrides.h"
#include "cyber_phoenix.h"
#include "dark_magician_the_dragon_knight.h"
#include "divine_serpent_geh.h"
#include "gladiator_beast_battled.h"
#include "harpie_lady_elegance_lock.h"
#include "victoria.h"

extern unsigned char IsSpellCancellerSpellLockActive(void);
extern unsigned char IsSorcererOfDarkMagicTrapLockActive(void);

extern void UpdateDuelGfxExceptField(void);
extern void UnlockCardsInRow(unsigned char turnRow);
extern void CourtOfJustice_RefreshHandUnlocks(void);
extern void ActivateTrapEffect(u16 lp);
extern void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);
extern struct DuelCard *gSetFinalStatZone;

/* Forward declarations used by PickZone targeting helpers */
extern void DisplayCardInfoBar(void);
extern void sub_8041E70(u8, u8);
extern void SetCursorToCardDest(void);
extern void ResetCursorDestToCurrentPos(void);
extern void CheckWinConditionExodia(unsigned char);
extern void TryActivatingPermanentEffects(void);

u8 ElementalHeroShiningPhoenixEnforcer_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroElectrum_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroEscuridao_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroHeat_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GoblinKing_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GyakuGirePanda_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 SeraphimBlaster_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GreatMajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheTyrantNeptune_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AmazonessTiger_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AmazonessPetLiger_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AmazonessBabyTiger_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 SilentMagicianLv4_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AncientSacredWyvern_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AtlanteanAttackSquad_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 BootUpSoldierDreadDynamo_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ColossalFighter_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 CyberEltanin_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GoldenHomunculus_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GravekeepersShaman_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GravekeepersVisionary_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 HeliosDuoMegistus_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 HeliosThePrimordialSun_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 HeliosTriceMegistus_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MontageDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MorphtronicClocken_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MorphtronicVideon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MucusYolk_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MagnaDrago_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheCalculator_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TyrannoInfinity_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ThebanNightmare_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheAgentOfForceMars_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 UnstoppableExodiaIncarnate_ApplyStat(struct DuelCard *zone);
u8 HarpiesPetBabyDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 HarpiesPetBabyDragon_CanAttackMonsterZone(struct DuelCard *zone);
u8 MorphtronicCameran_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *MorphtronicMagnen_GetForcedAttackTarget(u8 defenderDuelist);
u8 MorphtronicMagnen_CanAttackMonsterZone(struct DuelCard *zone);
u8 MorphtronicMagnen_CanSelectAttackTarget(const struct DuelCard *attacker,
                                           const struct DuelCard *defender);
struct DuelCard *MorphtronicStaplen_GetForcedAttackTarget(u8 defenderDuelist);
u8 MorphtronicStaplen_CanAttackMonsterZone(struct DuelCard *zone);
u8 ElementalHeroKnospe_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroKnospe_CanAttackMonsterZone(struct DuelCard *zone);
u8 ElementalHeroPoisonRose_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroAbsoluteZero_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 LyriluscIndependentNightingale_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheWickedEraser_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheWickedAvatar_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroPoisonRose_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *ElementalHeroPoisonRose_GetForcedAttackTarget(u8 defenderDuelist);
u8 SphereMode_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *HamonLordOfStrikingThunder_GetForcedAttackTarget(u8 defenderDuelist);
u8 HamonLordOfStrikingThunder_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *EvilHeroMaliciousFiend_GetForcedAttackTarget(u8 defenderDuelist);
u8 EvilHeroMaliciousFiend_CanAttackMonsterZone(struct DuelCard *zone);
u8 UriaLordOfSearingFlames_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AmuletDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 BeastKingBarbaros_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryBeastKingBarbarosOnMonsterPlacement(struct DuelCard *zone);
u8 NeoSpacianFlareScarab_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 OrichalcosShunoros_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ShireLightswornSpirit_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GaronithLightswornDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 BazooTheSoulEater_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroTheShining_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroFlareNeos_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 EvilDragonAnanta_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 VennominagaTheDeityOfPoisonousSnakes_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroAirNeos_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroBraveNeos_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 CyberDragonInfinity_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GandoraX_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ChimeratechFortressDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ChimeratechMegafleetDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AromaseraphySweetMarjoram_CanAttackMonsterZone(struct DuelCard *zone);
u8 KnightOfPentacles_ProtectsBattleZone(u8 fixedRow, u8 fixedCol);
u8 KnightOfPentacles_CanAttackMonsterZone(struct DuelCard *zone);
u8 LadyOfD_CanAttackMonsterZone(struct DuelCard *zone);
u8 HarpiePerfumer_TreatsNameAsHarpieLady(const struct DuelCard *zone);
u8 ReptilianneServant_HasOtherFaceUpMonster(struct DuelCard *zone);
u8 ReptilianneServant_BlocksNormalSummonReptile(u16 cardId);
struct DuelCard *Oshaleon_GetForcedAttackTarget(u8 defenderDuelist);
u8 Oshaleon_CanAttackMonsterZone(struct DuelCard *zone);
u8 EvilHeroDarkGaia_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryRavielOnOpponentMonsterPlacement(struct DuelCard *zone);
void TryAmuletDragonOnMonsterPlacement(struct DuelCard *zone);
struct DuelSummonOpts Duel_DefaultSpecialSummonOpts(u8 updateGfx)
{
  struct DuelSummonOpts opts;

  opts.updateGfx = updateGfx;
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  opts.markSpecialSummon = TRUE;
  opts.lockMonster = FALSE;
  return opts;
}

struct DuelSummonOpts Duel_DefaultNormalSummonOpts(u8 updateGfx)
{
  struct DuelSummonOpts opts;

  opts.updateGfx = updateGfx;
  opts.mode = DUEL_SUMMON_NORMAL_FACE_UP_ATK;
  opts.markSpecialSummon = FALSE;
  opts.lockMonster = FALSE;
  return opts;
}

static void MaybeUpdateGfx(u8 updateGfx)
{
  /* ponytail: AI_Main simulates actions with gHideEffectText set; duel state is
   * restored after each probe but field VRAM is not. */
  if (updateGfx && !gHideEffectText)
    UpdateDuelGfxExceptField();
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 turnDuelist;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return turnDuelist;
  }

  return ACTIVE_DUELIST;
}

static u8 MonsterRowForDuelist(u8 turnDuelist)
{
  if (turnDuelist == ACTIVE_DUELIST)
    return ACTIVE_DUELIST_MONSTER_ROW;

  return INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 HandMatchesCardOrPredicate(u16 handCardId, u16 cardId, HandCardPredicate pred)
{
  if (handCardId == CARD_NONE)
    return FALSE;

  if (cardId != CARD_NONE && handCardId != cardId)
    return FALSE;

  if (pred != NULL && pred(handCardId) != TRUE)
    return FALSE;

  return TRUE;
}

static u16 sSelectHandCardId APPEND_DATA = CARD_NONE;
static HandCardPredicate sSelectHandPred APPEND_DATA = NULL;
static const char sAmazonessArchetypeName[] APPEND_RODATA = "Amazoness";
static const char sElementalHeroArchetypeName[] APPEND_RODATA = "Elemental HERO";

static u8 AnyHandCardForSelect(u16 handCardId)
{
  return handCardId != CARD_NONE;
}

static u8 SelectHandWrapper(u16 handCardId)
{
  return HandMatchesCardOrPredicate(handCardId, sSelectHandCardId, sSelectHandPred);
}

static s8 FindHandZoneMatching(u8 turnDuelist, u16 cardId, HandCardPredicate pred)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (HandMatchesCardOrPredicate(handRow[i]->id, cardId, pred))
      return i;
  }

  return -1;
}

static s8 SelectHandZone(u8 turnDuelist, u16 cardId, HandCardPredicate pred)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];

  if (FindHandZoneMatching(turnDuelist, cardId, pred) < 0)
    return -1;

  if (WhoseTurn() == DUEL_PLAYER) {
    sSelectHandCardId = cardId;
    sSelectHandPred = pred;
    return SelectHandCardMatchingPredicate(handRow, SelectHandWrapper);
  }

  return FindHandZoneMatching(turnDuelist, cardId, pred);
}

static void InitMonsterZone(struct DuelCard *zone, struct DuelSummonOpts opts)
{
  enum DuelSummonMode mode = opts.mode;
  u8 markSpecialSummon = opts.markSpecialSummon;

  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->willChangeSides = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;

  // ponytail: Berserk Gorilla cannot be placed in Defense Position
  if (zone->id == BERSERK_GORILLA
      && mode != DUEL_SUMMON_NORMAL_FACE_UP_ATK
      && mode != DUEL_SUMMON_SPECIAL_FACE_UP_ATK)
    mode = DUEL_SUMMON_NORMAL_FACE_UP_ATK;

  switch (mode) {
  case DUEL_SUMMON_SPECIAL_FACE_UP_DEF:
    zone->isFaceUp = TRUE;
    zone->isDefending = TRUE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    break;
  case DUEL_SUMMON_NORMAL_SET:
    zone->isFaceUp = FALSE;
    zone->isDefending = TRUE;
    zone->isLocked = FALSE;
    FlipCardFaceDown(zone);
    break;
  case DUEL_SUMMON_NORMAL_FACE_UP_ATK:
  case DUEL_SUMMON_SPECIAL_FACE_UP_ATK:
  default:
    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    break;
  }

  if (opts.lockMonster)
    zone->isLocked = TRUE;

  if (markSpecialSummon
      && (mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF))
    zone->unk4 = 2;
  else
    zone->unk4 = 0;

  LevelLimitAreaB_EnforceOnSummon(zone);
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

u8 Duel_CardCannotBeSpecialSummoned(u16 cardId)
{
  if (cardId == THE_SUPREMACY_SUN && gTheSupremacySunOwnEffectSummon)
    return FALSE;

  if (Yubel_IsEvolutionForm(cardId) && gYubelOwnEffectSummon)
    return FALSE;

  return cardId == DARK_DUST_SPIRIT || cardId == THE_TYRANT_NEPTUNE
      || cardId == BEAST_KING_BARBAROS
      || cardId == THE_BIG_SATURN || cardId == THE_SUPREMACY_SUN
      || cardId == THE_WICKED_DREADROOT || cardId == THE_WICKED_ERASER
      || cardId == THE_WICKED_AVATAR
      || cardId == YUBEL_TERROR_INCARNATE
      || cardId == YUBEL_THE_ULTIMATE_NIGHTMARE
      || cardId == HAMON_LORD_OF_STRIKING_THUNDER
      || cardId == URIA_LORD_OF_SEARING_FLAMES
      || cardId == RAVIEL_LORD_OF_PHANTASMS
      || HiddenTemplesOfNecrovalley_BlocksSpecialSummon(cardId)
      || ParallelWorldFusion_BlocksSpecialSummon(cardId)
      || PowerFilter_BlocksSpecialSummon(cardId);
}

u8 Duel_BlocksExtraDeckSpecialSummon(u16 cardId)
{
  if (ContactGate_BlocksExtraDeckSpecialSummon(cardId)
      || EvilAssault_BlocksExtraDeckSpecialSummon(cardId)
      || FusionDestiny_BlocksSpecialSummon(cardId)
      || GadgetBox_BlocksExtraDeckSpecialSummon(WhoseTurn(), cardId)
      || HarpieLadyPhoenixFormation_CannotSpecialSummonFromMainOrExtraDeck())
    return TRUE;

  if (FusionDeployment_IsLocked()) {
    if (cardId == CARD_NONE)
      return TRUE;
    SetCardInfo(cardId);
    if (gCardInfo.color != FUSION_CARD)
      return TRUE;
  }

  if (!EN_ENGAGE_NEO_SPACE_IsLocked() || cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color == FUSION_CARD)
    return FALSE;

  return FusionRecipe_FindByResult(cardId) == NULL;
}

static enum DuelActionResult PlaceMonsterFromId(u8 turnDuelist, u16 monsterId, struct DuelSummonOpts opts)
{
  u8 monsterRow = MonsterRowForDuelist(turnDuelist);
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (monsterId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  if (SummonModeIsSpecial(opts.mode) && Duel_CardCannotBeSpecialSummoned(monsterId))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode)
      && LightForce_BlocksSpecialSummon(TurnDuelistToFixed(turnDuelist), monsterId))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode) && ArchlordKristya_BlocksSpecialSummon(monsterId))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode)
      && BarrierStatueOfTheStormwinds_BlocksSpecialSummon(monsterId))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode)
      && HarpieLadyElegance_BlocksSpecialSummon(turnDuelist, monsterId))
    return DUEL_ACTION_BLOCKED;

  if (CrimsonBlader_BlocksLevel5PlusSummon(turnDuelist, monsterId))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode)
      && ElShaddollWinda_IsSpecialSummonLockedFor(turnDuelist))
    return DUEL_ACTION_BLOCKED;

  if (SummonModeIsSpecial(opts.mode)
      && !HarpiesFeatherRest_CanSpecialSummonCard(monsterId))
    return DUEL_ACTION_BLOCKED;


  if (!KaiserColosseum_AllowsMonsterPlacement(Duel_FixedMonsterRowForDuelist(TurnDuelistToFixed(turnDuelist))))
    return DUEL_ACTION_BLOCKED;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0)
    return DUEL_ACTION_NO_ZONE;

  summonZone = gTurnZones[monsterRow][monsterZone];
  {
    bool32 _summonAnim = TryPlaySummonAnimation(monsterId);
    summonZone->id = monsterId;
    InitMonsterZone(summonZone, opts);
    FinishTheWickedAvatarTributeSummon(
        summonZone,
        Duel_FixedMonsterRowForDuelist(TurnDuelistToFixed(turnDuelist)),
        (u8)monsterZone);
    TryBlastHeldByATributeOnMonsterPlacement(summonZone);
    TryBreakerTheMagicalWarriorOnMonsterPlacement(summonZone);
    TryVengefulBogSpiritOnMonsterPlacement(summonZone);
    TryElementalHeroGreatTornadoOnMonsterPlacement(summonZone);
    TryTheWickedDreadrootOnMonsterPlacement(summonZone);
    TryTheWickedEraserOnMonsterPlacement(summonZone);
    TryTheWickedAvatarOnMonsterPlacement(summonZone);
    TryElementalHeroSunriseOnMonsterPlacement(summonZone);
    TryElementalHeroAbsoluteZeroOnMonsterPlacement(summonZone);
    MaybeUpdateGfx(opts.updateGfx);
    if (_summonAnim == TRUE)
      FinishSummonAnimation();
  }
  /* ponytail: on-summon text after field draw (Blazeman/Stratos popup, DDS, Ryu-Kishin). */
  TryActivateRyuKishinClownOnMonsterPlacement(summonZone);
  TryActivateDarkDustSpiritOnMonsterPlacement(summonZone);
  TryElementalHeroBlazemanOnMonsterPlacement(summonZone);
  TryTheWickedDreadrootEffectTextOnMonsterPlacement(summonZone);
  TryIofielOnMonsterPlacement(summonZone);
  TryAthenaOnMonsterPlacement(summonZone);
  TryElementalHeroStratosOnMonsterPlacement(summonZone);
  TryTheSuppressionPlutoOnMonsterPlacement(summonZone);
  TryAmuletDragonOnMonsterPlacement(summonZone);
  TryBeastKingBarbarosOnMonsterPlacement(summonZone);
  TryMinervaLightswornMaidenOnNormalSummon(summonZone, opts.mode);
  TryJunkSynchronOnNormalSummon(summonZone, opts.mode);
  TryDeepSeaDivaOnNormalSummon(summonZone, opts.mode);
  TryAmazonessPrincessOnMonsterPlacement(summonZone);
  TryDestinyHeroDeciderOnMonsterPlacement(summonZone);
  TryOnSummonPlacementHooks(summonZone, opts.mode);
  Duel_NotifyFixedMonsterRowChanged(Duel_FixedMonsterRowForDuelist(TurnDuelistToFixed(turnDuelist)));
  if (turnDuelist == ACTIVE_DUELIST)
    CourtOfJustice_RefreshHandUnlocks();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_SUMMON, monsterId, summonZone);
  if (SummonModeIsSpecial(opts.mode))
    ElShaddollWinda_OnSpecialSummon(turnDuelist);
  return DUEL_ACTION_OK;
}

static u8 SpellTrapOriginUsesRow2(u16 spellId)
{
  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP)
    return TRUE;

  switch (spellId) {
  case MYSTICAL_SPACE_TYPHOON:
  case DUST_TORNADO:
  case RIRYOKU:
  case BLOCK_ATTACK:
  case BOOK_OF_MOON:
  case BOOK_OF_TAIYOU:
  case SOUL_TAKER:
    return TRUE;
  default:
    return FALSE;
  }
}

static void SetupSpellTrapOrigin(void)
{
  u8 spellRow;
  u8 spellCol;

  if (SpellTrapOriginUsesRow2(gSpellEffectData.id)) {
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

static void ApplyLpDelta(u8 turnDuelist, s32 delta)
{
  u8 affectsPlayerSide = ((turnDuelist == ACTIVE_DUELIST) == (WhoseTurn() == DUEL_PLAYER));

  if (delta >= 0) {
    if (affectsPlayerSide)
      SetPlayerLifePointsToAdd((u32)delta);
    else
      SetOpponentLifePointsToAdd((u32)delta);
  } else {
    if (affectsPlayerSide)
      SetPlayerLifePointsToSubtract((u32)(-delta));
    else
      SetOpponentLifePointsToSubtract((u32)(-delta));
  }
}

static u8 CountTributeMonstersOnRow(u8 turnDuelist, u16 avoidCardId)
{
  u8 row = MonsterRowForDuelist(turnDuelist);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone->id == CARD_NONE || zone->id == avoidCardId)
      continue;

    count++;
  }

  return count;
}

static enum DuelActionResult PayTributesFromMonsterRow(u8 turnDuelist, u8 count, u16 avoidCardId)
{
  u8 row = MonsterRowForDuelist(turnDuelist);
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 paid = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW && paid < count; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone->id == CARD_NONE || zone->id == avoidCardId)
      continue;

    ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
    paid++;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  if (paid < count)
    return DUEL_ACTION_NO_TARGET;

  return DUEL_ACTION_OK;
}

u8 Duel_CountCardsInHand(struct DuelCard **handRow)
{
  u8 i;
  u8 count = 0;
  u8 fixedDuelist;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id != CARD_NONE)
      count++;
  }

  if (IsExpandedCardHandEnabled()) {
    fixedDuelist = ExpandedHand_FixedDuelistForHandRow(handRow);
    if (fixedDuelist != 0xFF) {
      for (i = 0; i < MAX_HAND_EXTRA; i++) {
        if (gHandExtraSlots[fixedDuelist][i].id != CARD_NONE)
          count++;
      }
    }
  }

  return count;
}

enum DuelActionResult Duel_DrawCards(u8 duelist, u8 count, u8 updateGfx)
{
  u8 i;
  u8 fixedDuelist = TurnDuelistToFixed(duelist);

  if (ProtectorOfTheSanctuary_BlocksDraw(duelist))
    return DUEL_ACTION_OK;

  for (i = 0; i < count; i++) {
    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist)) {
      DeclareLoser(fixedDuelist);
      return DUEL_ACTION_DUEL_OVER;
    }

    TryDrawingCard(TurnDuelistToFixed(duelist));

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DrawCardsUntilHandSize(u8 turnDuelist, u8 targetHandSize, u8 updateGfx)
{
  u8 maxHand = ExpandedHand_MaxSlots();

  while (Duel_CountCardsInHand(gTurnHands[turnDuelist]) < targetHandSize) {
    if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) >= maxHand)
      break;
    if (Duel_DrawCards(turnDuelist, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_MillTopDeckCards(u8 duelist, u8 count, u8 updateGfx)
{
  u8 i;
  u8 fixedDuelist = TurnDuelistToFixed(duelist);

  for (i = 0; i < count; i++) {
    u16 cardId;

    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist)) {
      DeclareLoser(fixedDuelist);
      return DUEL_ACTION_DUEL_OVER;
    }

    cardId = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];
    if (GraveyardExpand_IsEnabled())
      GraveyardExpand_PushTurn(duelist, cardId);
    else
      gTurnDuelistBattleState[duelist]->graveyard = cardId;

    gDuelDecks[fixedDuelist].cardsDrawn++;

    TryApplyWulfAfterDeckMill(duelist, cardId);
    JenisLightswornMender_NoteDeckMill(fixedDuelist);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  TryApplyGarothAfterDeckMill(duelist, count);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  TryApplyLightSpiralAfterMill(duelist, count);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;
  TryApplyLightOfDestructionAfterMill(duelist, count);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx)
{
  u16 cardId;
  u8 wasMonster;

  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  if (DForce_PreventsPlasmaEffectDestruction(zone)
      || ColosseumCage_TryPreventDestroyByCardEffect(zone)
      || GladiatorBeastsMedusaShield_PreventsDestroy(zone)
      || FieldBarrier_PreventsFieldSpellDestroy(zone)
      || ForbiddenDress_IsDestroyImmune(zone)
      || GladiatorBeastsBattleArchfiendShield_PreventsDestruction(zone)
      || ReturnOfTheDragonLords_TryProtectDragon(zone)
      || ShiningSarcophagus_PreventsDestroy(zone)
      || ElShaddollWinda_PreventsDestroy(zone)
      || AmazonessScouts_PreventsDestroy(zone)
      || AromalilithMagnolia_PreventsDestroy(zone)
      || NeosWiseman_PreventsDestroy(zone)
      || AzureEyesSilverDragon_PreventsDestroy(zone)
      || EvilHeroInfernalSniper_PreventsDestroy(zone)
      || SilentMagicianLv8_PreventsDestroy(zone)
      || BlueEyesJetDragon_PreventsDestroy(zone)
      || BlueEyesSolidDragon_PreventsDestroy(zone)
      || BlueEyesAlternativeUltimateDragon_PreventsDestroy(zone)
      || AmazonessAugusta_PreventsDestroy(zone))
    return DUEL_ACTION_BLOCKED;

  cardId = zone->id;
  wasMonster = GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_DESTROY, cardId, zone);
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_LEAVE_FIELD, cardId, zone);

  if (cardId == DESTINY_HERO_DRAWHAND) {
    u8 fixedGy = gTurnDuelistBattleState[graveyardDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
        ? DUEL_PLAYER
        : DUEL_OPPONENT;

    DestinyHeroDrawhand_OnSentToGraveyard(fixedGy);
  }

  MarkElementalHeroCoreDestroyedFromField(zone);
  MarkTheSupremacySunDestroyedFromField(zone);
  ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
  MaybeUpdateGfx(updateGfx);

  if (wasMonster)
    EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

void Duel_DestroyMaskedMonstersInFixedRow(u8 fixedRow, u8 colMask, u8 graveyardDuelist, u8 updateGfx)
{
  u8 col;

  if (colMask == 0)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!(colMask & (1 << col)))
      continue;

    zone = gFixedZones[fixedRow][col];
    if (zone->id != CARD_NONE)
      Duel_DestroyZone(zone, graveyardDuelist, updateGfx);
  }
}

enum DuelActionResult Duel_DestroyAllMonstersMatching(u8 turnRow, MonsterZonePredicate pred,
                                                      u8 updateGfx)
{
  u8 col;
  u8 graveyardDuelist;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  if (turnRow != INACTIVE_DUELIST_MONSTER_ROW && turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return DUEL_ACTION_INVALID;

  graveyardDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE)
      continue;

    if (IsGodCard(zone->id))
      continue;

    if (pred != NULL && pred(zone) != TRUE)
      continue;

    ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_DestroyAllMonstersOfType(u8 turnRow, u8 monsterType, u8 updateGfx)
{
  u8 col;
  u8 graveyardDuelist;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  if (turnRow != INACTIVE_DUELIST_MONSTER_ROW && turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return DUEL_ACTION_INVALID;

  graveyardDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!Duel_CardHasMonsterType(zone->id, monsterType))
      continue;

    ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_DestroyAllInTurnRow(u8 turnRow, u8 graveyardDuelist, u8 updateGfx)
{
  u8 col;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

static u8 GraveyardDuelistForMonsterTurnRow(u8 turnRow)
{
  return (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

enum DuelActionResult Duel_DestroyMonstersInRowWithFinalAtkGte(u8 turnRow, u16 atkMin,
                                                              u8 updateGfx)
{
  u8 col;
  u8 graveyardDuelist;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  if (turnRow != INACTIVE_DUELIST_MONSTER_ROW && turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return DUEL_ACTION_INVALID;

  graveyardDuelist = GraveyardDuelistForMonsterTurnRow(turnRow);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE || IsGodCard(zone->id) == 1)
      continue;

    if (Duel_GetZoneFinalAtk(zone) < atkMin)
      continue;

    ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_DestroyHighestAtkMonsterInRow(u8 turnRow, u8 updateGfx)
{
  u8 col;
  u8 graveyardDuelist;

  if (turnRow != INACTIVE_DUELIST_MONSTER_ROW && turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return DUEL_ACTION_INVALID;

  if (NumEmptyZonesAndGodCardsInRow(gTurnZones[turnRow]) == MAX_ZONES_IN_ROW)
    return DUEL_ACTION_NO_TARGET;

  col = (u8)HighestAtkMonInRowExceptGodCards(gTurnZones[turnRow]);
  graveyardDuelist = GraveyardDuelistForMonsterTurnRow(turnRow);
  ClearZoneAndSendMonToGraveyard(gTurnZones[turnRow][col], graveyardDuelist);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

static s8 PickRandomHandZone(struct DuelCard **handRow)
{
  u8 i;
  u8 occupied = Duel_CountCardsInHand(handRow);
  u8 chosen;
  u8 seen = 0;
  u8 maxSlots = ExpandedHand_MaxSlots();
  struct DuelCard *zone;

  if (occupied == 0)
    return -1;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < maxSlots; i++) {
    zone = ExpandedHand_ZoneAtHandRow(handRow, i);
    if (zone->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return -1;
}

static u8 HandCardMatchesDiscardPred(u16 cardId, HandCardPredicate pred)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (pred == NULL)
    return TRUE;

  return pred(cardId);
}

enum DuelActionResult Duel_DiscardFromHand(u8 duelist, u8 count, HandCardPredicate pred, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;

  for (i = 0; i < count; i++) {
    s8 zone;
    struct DuelCard *slot;

    if (Duel_CountCardsInHand(handRow) == 0)
      return DUEL_ACTION_NO_TARGET;

    if (WhoseTurn() == DUEL_PLAYER) {
      if (pred != NULL)
        zone = SelectHandCardMatchingPredicate(handRow, pred);
      else
        zone = SelectHandCardMatchingPredicate(handRow, AnyHandCardForSelect);
    } else {
      zone = PickRandomHandZone(handRow);
      if (zone >= 0) {
        slot = ExpandedHand_ZoneAtHandRow(handRow, (u8)zone);
        if (!HandCardMatchesDiscardPred(slot->id, pred))
          return DUEL_ACTION_NO_TARGET;
      }
    }

    if (zone < 0)
      return DUEL_ACTION_NO_TARGET;

    slot = ExpandedHand_ZoneAtHandRow(handRow, (u8)zone);
    ClearZoneAndSendMonToGraveyard(slot, duelist);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DiscardRandomFromHand(u8 duelist, u8 count, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;

  for (i = 0; i < count; i++) {
    s8 zone;
    struct DuelCard *slot;

    if (Duel_CountCardsInHand(handRow) == 0)
      return DUEL_ACTION_NO_TARGET;

    zone = PickRandomHandZone(handRow);
    if (zone < 0)
      return DUEL_ACTION_NO_TARGET;

    slot = ExpandedHand_ZoneAtHandRow(handRow, (u8)zone);
    ClearZoneAndSendMonToGraveyard(slot, duelist);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

    MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

s8 Duel_PickRandomHandZone(u8 turnDuelist)
{
  return PickRandomHandZone(gTurnHands[turnDuelist]);
}

enum DuelActionResult Duel_DestroyAllHandCards(u8 duelist, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;
  u8 maxSlots = ExpandedHand_MaxSlots();
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;
  struct DuelCard *slot;

  for (i = 0; i < maxSlots; i++) {
    slot = ExpandedHand_ZoneAtHandRow(handRow, i);
    if (slot->id == CARD_NONE)
      continue;

    ClearZoneAndSendMonToGraveyard(slot, duelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_DestroyAllHandCardsExceptGods(u8 duelist, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;
  u8 maxSlots = ExpandedHand_MaxSlots();
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;
  struct DuelCard *slot;

  for (i = 0; i < maxSlots; i++) {
    slot = ExpandedHand_ZoneAtHandRow(handRow, i);
    if (slot->id == CARD_NONE || IsGodCard(slot->id))
      continue;

    ClearZoneAndSendMonToGraveyard(slot, duelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_BurnPerOpponentHandCard(u16 perCard, u8 updateGfx)
{
  u16 count;
  s32 damage;

  if (perCard == 0)
    return DUEL_ACTION_INVALID;

  /* Match vanilla Restructer: MAX_ZONES_IN_ROW - empty in turn hand row. */
  count = (u16)(MAX_ZONES_IN_ROW - NumEmptyZonesInRow(gTurnHands[INACTIVE_DUELIST]));
  damage = (s32)count * (s32)perCard;
  if (damage == 0)
    return DUEL_ACTION_OK;

  return Duel_ChangeLp(INACTIVE_DUELIST, -damage, updateGfx);
}

void Duel_FaceUpMonstersInTurnRow(u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id != CARD_NONE)
      zone->isFaceUp = 1;
  }
}

void Duel_FaceUpHandCards(u8 duelist)
{
  u8 i;
  u8 maxSlots = ExpandedHand_MaxSlots();
  struct DuelCard **handRow = gTurnHands[duelist];

  for (i = 0; i < maxSlots; i++) {
    struct DuelCard *slot = ExpandedHand_ZoneAtHandRow(handRow, i);

    if (slot->id != CARD_NONE)
      slot->isFaceUp = 1;
  }
}

void Duel_DecrementPermStageInTurnRow(u8 turnRow, u8 times)
{
  u8 col;
  u8 t;

  if (times == 0)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE)
      continue;

    for (t = 0; t < times; t++)
      DecrementPermStage(zone);
  }
}

void Duel_ResetNegativePermStagesInTurnRow(u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id != CARD_NONE && PermStage(zone) < 0)
      ResetPermStage(zone);
  }
}

void Duel_ApplyStopDefense(void)
{
  u8 col;

  GladiatorBeast_MarkBattlePhaseActive();
  gTurnDuelistBattleState[INACTIVE_DUELIST]->defenseBlocked = 1;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == CARD_NONE)
      continue;

    zone->isDefending = 0;
    zone->isFaceUp = 1;
  }
}

enum DuelActionResult Duel_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx)
{
  if (delta == 0)
    return DUEL_ACTION_OK;

  ApplyLpDelta(targetDuelist, delta);
  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
  MaybeUpdateGfx(updateGfx);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

void Duel_IncrementPermStageOnDuelistMonsters(u8 turnDuelist)
{
  u8 i;
  u8 row = MonsterRowForDuelist(turnDuelist);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[row][i];

    if (zone->id != CARD_NONE)
      IncrementPermStage(zone);
  }
}

void Duel_RefreshMonsterStatOverlays(void)
{
  RefreshFieldMonsterStatOverlays();
}

u16 Duel_ClampStat(u32 stat)
{
  if (stat > 0xFFFE)
    return 0xFFFE;
  return (u16)stat;
}

u16 Duel_StageModifiedStat(u16 stat, s8 stage)
{
  s32 finalStat;

  if (stat == 0xFFFF)
    return stat;

  finalStat = (s32)stage * 500 + (s32)stat;

  if (finalStat <= 0)
    return 0;
  if (finalStat > 0xFFFE)
    return 0xFFFE;
  return (u16)finalStat;
}

u16 Duel_StatFromCount(u32 count, u16 perUnit, u32 base)
{
  return Duel_ClampStat(base + count * perUnit);
}

u8 Duel_CardIsMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE && cardId >= CUSTOM_CARD_START)
    return FALSE;

  return gCardData_NEW[cardId].type < TYPE_SPELL;
}

u8 Duel_CardHasMonsterType(u16 cardId, u8 monsterType)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (!Duel_CardIsMonster(cardId))
    return FALSE;

  /* ponytail: never SetCardInfo here — ApplyFieldZoneStats overlays call this
   * after stage/field ATK is computed; SetCardInfo would wipe them back to print. */
  return gCardData_NEW[cardId].type == monsterType;
}

u8 Duel_CardNameContains(u16 cardId, const char *needle)
{
  const u8 *name;
  u8 needleLen = 0;
  u8 i;
  u16 savedAtk;
  u16 savedDef;
  u16 savedId;
  u8 match;

  if (cardId == CARD_NONE || needle == NULL)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == cardId)
    cardId = ElementalHeroNeosAlius_GetEffectiveCardId(gSetFinalStatZone);

  while (needle[needleLen] != 0)
    needleLen++;

  if (needleLen == 0)
    return FALSE;

  /* Celestial Sword Eatos is always treated as a Noble Arms card. */
  if (cardId == CELESTIAL_SWORD_EATOS && needleLen == 10
      && needle[0] == 'N' && needle[1] == 'o' && needle[2] == 'b'
      && needle[3] == 'l' && needle[4] == 'e' && needle[5] == ' '
      && needle[6] == 'A' && needle[7] == 'r' && needle[8] == 'm'
      && needle[9] == 's')
    return TRUE;

  /* Legendary Dragon name-treats for the three Dragon Relics. */
  if (needleLen == 16
      && needle[0] == 'L' && needle[1] == 'e' && needle[2] == 'g'
      && needle[3] == 'e' && needle[4] == 'n' && needle[5] == 'd'
      && needle[6] == 'a' && needle[7] == 'r' && needle[8] == 'y'
      && needle[9] == ' ' && needle[10] == 'D' && needle[11] == 'r'
      && needle[12] == 'a' && needle[13] == 'g' && needle[14] == 'o'
      && needle[15] == 'n') {
    if (cardId == THE_EYE_OF_TIMAEUS || cardId == THE_FANG_OF_CRITIAS
        || cardId == THE_CLAW_OF_HERMOS || cardId == THE_GAZE_OF_TIMAEUS)
      return TRUE;
  }

  if (cardId == THE_EYE_OF_TIMAEUS || cardId == THE_GAZE_OF_TIMAEUS) {
    if (needleLen == 7 && needle[0] == 'T' && needle[1] == 'i'
        && needle[2] == 'm' && needle[3] == 'a' && needle[4] == 'e'
        && needle[5] == 'u' && needle[6] == 's')
      return TRUE;
  }

  if (cardId == THE_FANG_OF_CRITIAS && needleLen == 7
      && needle[0] == 'C' && needle[1] == 'r' && needle[2] == 'i'
      && needle[3] == 't' && needle[4] == 'i' && needle[5] == 'a'
      && needle[6] == 's')
    return TRUE;

  if (cardId == THE_CLAW_OF_HERMOS && needleLen == 6
      && needle[0] == 'H' && needle[1] == 'e' && needle[2] == 'r'
      && needle[3] == 'm' && needle[4] == 'o' && needle[5] == 's')
    return TRUE;

  /* Gaze is also treated as Eye of Timaeus. */
  if (cardId == THE_GAZE_OF_TIMAEUS && needleLen == 16
      && needle[0] == 'E' && needle[1] == 'y' && needle[2] == 'e'
      && needle[3] == ' ' && needle[4] == 'o' && needle[5] == 'f'
      && needle[6] == ' ' && needle[7] == 'T' && needle[8] == 'i'
      && needle[9] == 'm' && needle[10] == 'a' && needle[11] == 'e'
      && needle[12] == 'u' && needle[13] == 's')
    return TRUE;

  /* ponytail: SetCardInfo clobbers stage/field ATK·DEF mid-overlay; restore. */
  savedAtk = gCardInfo.atk;
  savedDef = gCardInfo.def;
  savedId = gCardInfo.id;

  SetCardInfo(cardId);
  name = gCardInfo.name;
  match = FALSE;
  if (name != NULL) {
    for (i = 0; name[i] != 0; i++) {
      u8 j = 0;

      while (j < needleLen && name[i + j] == (u8)needle[j])
        j++;

      if (j == needleLen) {
        match = TRUE;
        break;
      }
    }
  }

  if (savedId != CARD_NONE) {
    if (gCardInfo.id != savedId)
      SetCardInfo(savedId);
    gCardInfo.atk = savedAtk;
    gCardInfo.def = savedDef;
  }

  return match;
}

u8 Duel_IsAmazonessCard(u16 cardId)
{
  return Duel_CardNameContains(cardId, sAmazonessArchetypeName);
}

u8 Duel_IsElementalHeroCard(u16 cardId)
{
  return Duel_CardNameContains(cardId, sElementalHeroArchetypeName);
}

u16 Duel_GetEffectiveCardId(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return CARD_NONE;

  return ElementalHeroNeosAlius_GetEffectiveCardId(zone);
}

u16 Duel_EffectHostCardId(struct DuelCard *zone)
{
  u16 hostId;

  if (zone == NULL || zone->id == CARD_NONE)
    return CARD_NONE;

  hostId = TheTyrantNeptune_HostCardId(zone);
  if (hostId != CARD_NONE)
    return hostId;

  return zone->id;
}

u16 Duel_ZoneEffectCardId(struct DuelCard *zone)
{
  u16 copied;

  if (zone == NULL || zone->id == CARD_NONE)
    return CARD_NONE;

  copied = TheTyrantNeptune_GetCopiedCardId(zone);
  if (copied != CARD_NONE)
    return copied;

  copied = GladiatorBeast_GetCopiedEffectCardId(zone);
  if (copied != CARD_NONE)
    return copied;

  if (AmazonessBabyTiger_TreatsNameAsTiger(zone))
    return AMAZONESS_TIGER;

  if (HarpiePerfumer_TreatsNameAsHarpieLady(zone))
    return HARPIE_LADY;

  if (AmazonessPrincess_TreatsNameAsQueen(zone))
    return AMAZONESS_QUEEN;

  if (DarkMagicianTheMagicianOfBlackMagic_TreatsNameAsDarkMagician(zone))
    return DARK_MAGICIAN;

  if (DarkMagicianTheMagicianOfBlackChaos_TreatsNameAsDarkMagician(zone))
    return DARK_MAGICIAN;

  if (DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician(zone))
    return DARK_MAGICIAN;

  if (DarkMagicianGirlTheMagiciansApprentice_TreatsNameAsDarkMagicianGirl(zone))
    return DARK_MAGICIAN_GIRL;

  return zone->id;
}

u8 Duel_ZoneHasEffectOfCard(struct DuelCard *zone, u16 effectCardId)
{
  if (zone == NULL || effectCardId == CARD_NONE)
    return FALSE;
  return Duel_ZoneEffectCardId(zone) == effectCardId;
}

u16 Duel_BeginCopiedEffectIdentity(struct DuelCard *zone)
{
  return TheTyrantNeptune_BeginEffectIdentity(zone);
}

void Duel_EndCopiedEffectIdentity(struct DuelCard *zone, u16 savedHostId)
{
  TheTyrantNeptune_EndEffectIdentity(zone, savedHostId);
}

typedef u16 (*CopiedPassiveAtkBonusFn)(struct DuelCard *hostZone);

struct CopiedPassiveAtkBonus {
  u16 cardId;
  CopiedPassiveAtkBonusFn atkBonus;
};

/* Register passive/continuous ATK bonuses that apply when a host copies this card. */
static const struct CopiedPassiveAtkBonus sCopiedPassiveAtkBonuses[] __attribute__((section(".text"))) = {
  { LYRILUSC_INDEPENDENT_NIGHTINGALE, LyriluscIndependentNightingale_CopiedAtkBonus },
  { THEBAN_NIGHTMARE, ThebanNightmare_CopiedAtkBonus },
};

u16 Duel_CopiedPassiveAtkBonus(struct DuelCard *hostZone, u16 effectCardId)
{
  u8 i;

  if (hostZone == NULL || effectCardId == CARD_NONE)
    return 0;

  for (i = 0; i < ARRAY_COUNT(sCopiedPassiveAtkBonuses); i++) {
    if (sCopiedPassiveAtkBonuses[i].cardId != effectCardId)
      continue;
    if (sCopiedPassiveAtkBonuses[i].atkBonus == NULL)
      return 0;
    return sCopiedPassiveAtkBonuses[i].atkBonus(hostZone);
  }

  return 0;
}

u8 Duel_IsFiendZone(struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE
      && Duel_CardHasMonsterType(zone->id, TYPE_FIEND);
}

u8 Duel_FindFixedMonsterZone(struct DuelCard *zone, u8 *fixedRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gFixedZones[row][*col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Duel_FindTurnMonsterZone(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Duel_FindFixedZone(struct DuelCard *zone, u8 *fixedRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_HAND; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gFixedZones[row][*col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  if (IsExpandedCardHandEnabled() && ExpandedHand_IsHandZone(zone)
      && ExpandedHand_OwnerOf(zone) == DUEL_PLAYER) {
    *fixedRow = PLAYER_HAND;
    *col = 0;
    {
      u8 i;

      for (i = 0; i < MAX_HAND_CARDS; i++) {
        if (ExpandedHand_GetFixed(DUEL_PLAYER, i) == zone) {
          *col = i;
          break;
        }
      }
    }
    return TRUE;
  }

  return FALSE;
}

u8 Duel_CountMonstersOnFixedRow(u8 fixedRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[fixedRow][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

u8 Duel_OpponentMonsterRowForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return OPPONENT_MONSTER_ROW;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

u8 Duel_CountFixedMonstersMatching(MonsterZonePredicate pred)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == CARD_NONE)
        continue;
      if (pred != NULL && pred(zone) != TRUE)
        continue;
      count++;
    }
  }

  return count;
}

u8 Duel_TurnRowHasOtherMonsterMatching(u8 turnRow, u8 exceptCol, MonsterZonePredicate pred)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == exceptCol)
      continue;
    if (gTurnZones[turnRow][col]->id == CARD_NONE)
      continue;
    if (pred != NULL && pred(gTurnZones[turnRow][col]) != TRUE)
      continue;
    return TRUE;
  }

  return FALSE;
}

void Duel_WriteCardInfoStats(u16 cardId, u16 atk, u16 def)
{
  SetCardInfo(cardId);
  gCardInfo.atk = atk;
  gCardInfo.def = def;
}

u8 Duel_ApplyStatModViaZoneApplier(struct StatMod *ptr, u16 cardId,
                                  DuelZoneStatApplier applyZone)
{
  u8 row;
  u8 col;

  if (ptr == NULL || ptr->card != cardId || applyZone == NULL)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == cardId)
    return applyZone(gSetFinalStatZone);

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != cardId)
        continue;
      if (ComputeFinalStage(zone) != ptr->stage)
        continue;
      if (applyZone(zone))
        return TRUE;
    }
  }

  return FALSE;
}

struct DuelDynamicZoneStat {
  u16 cardId;
  DuelZoneStatApplier applyZone;
};

struct DuelAttackGate {
  u16 cardId;
  MonsterZonePredicate blockWhenControllerHasOther;
};

static const struct DuelDynamicZoneStat sDynamicZoneStats[] __attribute__((section(".text"))) = {
  { ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER, ElementalHeroShiningPhoenixEnforcer_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_ELECTRUM, ElementalHeroElectrum_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_SHINING_FLARE_WINGMAN, ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_HEAT, ElementalHeroHeat_ApplyDynamicZoneStats },
  { GREAT_MAJU_GARZETT, GreatMajuGarzett_ApplyDynamicZoneStats },
  { MAJU_GARZETT, MajuGarzett_ApplyDynamicZoneStats },
  { THE_TYRANT_NEPTUNE, TheTyrantNeptune_ApplyDynamicZoneStats },
  { GOBLIN_KING, GoblinKing_ApplyDynamicZoneStats },
  { GYAKU_GIRE_PANDA, GyakuGirePanda_ApplyDynamicZoneStats },
  { SERAPHIM_BLASTER, SeraphimBlaster_ApplyDynamicZoneStats },
  { AMAZONESS_TIGER, AmazonessTiger_ApplyDynamicZoneStats },
  { AMAZONESS_BABY_TIGER, AmazonessBabyTiger_ApplyDynamicZoneStats },
  { AMAZONESS_PET_LIGER, AmazonessPetLiger_ApplyDynamicZoneStats },
  { ANCIENT_SACRED_WYVERN, AncientSacredWyvern_ApplyDynamicZoneStats },
  { ATLANTEAN_ATTACK_SQUAD, AtlanteanAttackSquad_ApplyDynamicZoneStats },
  { BOOT_UP_SOLDIER_DREAD_DYNAMO, BootUpSoldierDreadDynamo_ApplyDynamicZoneStats },
  { COLOSSAL_FIGHTER, ColossalFighter_ApplyDynamicZoneStats },
  { CYBER_ELTANIN, CyberEltanin_ApplyDynamicZoneStats },
  { GOLDEN_HOMUNCULUS, GoldenHomunculus_ApplyDynamicZoneStats },
  { GRAVEKEEPERS_SHAMAN, GravekeepersShaman_ApplyDynamicZoneStats },
  { GRAVEKEEPERS_VISIONARY, GravekeepersVisionary_ApplyDynamicZoneStats },
  { HELIOS_DUO_MEGISTUS, HeliosDuoMegistus_ApplyDynamicZoneStats },
  { HELIOS_THE_PRIMORDIAL_SUN, HeliosThePrimordialSun_ApplyDynamicZoneStats },
  { HELIOS_TRICE_MEGISTUS, HeliosTriceMegistus_ApplyDynamicZoneStats },
  { MONTAGE_DRAGON, MontageDragon_ApplyDynamicZoneStats },
  { MORPHTRONIC_CLOCKEN, MorphtronicClocken_ApplyDynamicZoneStats },
  { MORPHTRONIC_VIDEON, MorphtronicVideon_ApplyDynamicZoneStats },
  { MUCUS_YOLK, MucusYolk_ApplyDynamicZoneStats },
  { MAGNA_DRAGO, MagnaDrago_ApplyDynamicZoneStats },
  { THE_CALCULATOR, TheCalculator_ApplyDynamicZoneStats },
  { TYRANNO_INFINITY, TyrannoInfinity_ApplyDynamicZoneStats },
  { THEBAN_NIGHTMARE, ThebanNightmare_ApplyDynamicZoneStats },
  { THE_AGENT_OF_FORCE_MARS, TheAgentOfForceMars_ApplyDynamicZoneStats },
  { THE_UNSTOPPABLE_EXODIA_INCARNATE, UnstoppableExodiaIncarnate_ApplyStat },
  { HARPIES_PET_BABY_DRAGON, HarpiesPetBabyDragon_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_KNOSPE, ElementalHeroKnospe_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_POISON_ROSE, ElementalHeroPoisonRose_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_ABSOLUTE_ZERO, ElementalHeroAbsoluteZero_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_ESCURIDAO, ElementalHeroEscuridao_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_BLAZEMAN, ElementalHeroBlazeman_ApplyDynamicZoneStats },
  { CHIMERATECH_OVERDRAGON, ChimeratechOverdragon_ApplyDynamicZoneStats },
  { CHIMERATECH_FORTRESS_DRAGON, ChimeratechFortressDragon_ApplyDynamicZoneStats },
  { CHIMERATECH_MEGAFLEET_DRAGON, ChimeratechMegafleetDragon_ApplyDynamicZoneStats },
  { LYRILUSC_INDEPENDENT_NIGHTINGALE, LyriluscIndependentNightingale_ApplyDynamicZoneStats },
  { THE_WICKED_ERASER, TheWickedEraser_ApplyDynamicZoneStats },
  { THE_WICKED_AVATAR, TheWickedAvatar_ApplyDynamicZoneStats },
  { URIA_LORD_OF_SEARING_FLAMES, UriaLordOfSearingFlames_ApplyDynamicZoneStats },
  { AMULET_DRAGON, AmuletDragon_ApplyDynamicZoneStats },
  { BEAST_KING_BARBAROS, BeastKingBarbaros_ApplyDynamicZoneStats },
  { NEO_SPACIAN_FLARE_SCARAB, NeoSpacianFlareScarab_ApplyDynamicZoneStats },
  { ORICHALCOS_SHUNOROS, OrichalcosShunoros_ApplyDynamicZoneStats },
  { SHIRE_LIGHTSWORN_SPIRIT, ShireLightswornSpirit_ApplyDynamicZoneStats },
  { GARONITH_LIGHTSWORN_DRAGON, GaronithLightswornDragon_ApplyDynamicZoneStats },
  { BAZOO_THE_SOUL_EATER, BazooTheSoulEater_ApplyDynamicZoneStats },
  { EVIL_HERO_DARK_GAIA, EvilHeroDarkGaia_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_THE_SHINING, ElementalHeroTheShining_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_FLARE_NEOS, ElementalHeroFlareNeos_ApplyDynamicZoneStats },
  { EVIL_DRAGON_ANANTA, EvilDragonAnanta_ApplyDynamicZoneStats },
  { VENNOMINON_THE_KING_OF_POISONOUS_SNAKES, VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats },
  { VENNOMINAGA_THE_DEITY_OF_POISONOUS_SNAKES, VennominagaTheDeityOfPoisonousSnakes_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_AIR_NEOS, ElementalHeroAirNeos_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_BRAVE_NEOS, ElementalHeroBraveNeos_ApplyDynamicZoneStats },
  { CYBER_DRAGON_INFINITY, CyberDragonInfinity_ApplyDynamicZoneStats },
  { SILENT_MAGICIAN_LV4, SilentMagicianLv4_ApplyDynamicZoneStats },
  { GANDORA_X_THE_DRAGON_OF_DESTRUCTION, GandoraX_ApplyDynamicZoneStats },
  { GANDORA_X_THE_DRAGON_OF_DEMOLITION, GandoraX_ApplyDynamicZoneStats },
};

static const struct DuelAttackGate sAttackGates[] __attribute__((section(".text"))) = {
  { GOBLIN_KING, Duel_IsFiendZone },
  { REPTILIANNE_SERVANT, ReptilianneServant_HasOtherFaceUpMonster },
};

typedef struct DuelCard *(*DuelForcedAttackTargetFn)(u8 defenderDuelist);

struct DuelForcedAttackRedirect {
  DuelForcedAttackTargetFn getForcedTarget;
};

static const struct DuelForcedAttackRedirect sForcedAttackRedirects[] __attribute__((section(".text"))) = {
  { RaregoldArmor_GetForcedAttackTarget },
  { DoubleTool_GetForcedAttackTarget },
  { ElementalHeroPoisonRose_GetForcedAttackTarget },
  { HamonLordOfStrikingThunder_GetForcedAttackTarget },
  { EvilHeroMaliciousFiend_GetForcedAttackTarget },
  { Oshaleon_GetForcedAttackTarget },
  { MorphtronicMagnen_GetForcedAttackTarget },
  { MorphtronicStaplen_GetForcedAttackTarget },
};

typedef u8 (*DuelAttackZoneCheckFn)(struct DuelCard *zone);

static const DuelAttackZoneCheckFn sAttackZoneChecks[] __attribute__((section(".text"))) = {
  AmazonessTiger_CanAttackMonsterZone,
  AmazonessCall_CanAttackMonsterZone,
  GladiatorBeastsValor_CanAttackMonsterZone,
  HarpiesPetBabyDragon_CanAttackMonsterZone,
  ElementalHeroKnospe_CanAttackMonsterZone,
  ElementalHeroPoisonRose_CanAttackMonsterZone,
  SphereMode_CanAttackMonsterZone,
  HamonLordOfStrikingThunder_CanAttackMonsterZone,
  KnightOfPentacles_CanAttackMonsterZone,
  LadyOfD_CanAttackMonsterZone,
  AromaseraphySweetMarjoram_CanAttackMonsterZone,
  EvilHeroMaliciousFiend_CanAttackMonsterZone,
  Oshaleon_CanAttackMonsterZone,
  MorphtronicCameran_CanAttackMonsterZone,
  MorphtronicMagnen_CanAttackMonsterZone,
  MorphtronicStaplen_CanAttackMonsterZone,
  Victoria_CanAttackMonsterZone,
};

u8 Duel_TryApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 i;
  u16 statsCardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  /* Effect-copy hosts (identity-swapped) use the host card's stat applier. */
  statsCardId = Duel_EffectHostCardId(zone);

  for (i = 0; i < ARRAY_COUNT(sDynamicZoneStats); i++) {
    if (sDynamicZoneStats[i].cardId != statsCardId)
      continue;
    return sDynamicZoneStats[i].applyZone(zone);
  }

  return FALSE;
}

u8 Duel_TryApplyDynamicStatMod(struct StatMod *ptr)
{
  u8 i;

  if (ptr == NULL || ptr->card == CARD_NONE)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sDynamicZoneStats); i++) {
    if (sDynamicZoneStats[i].cardId != ptr->card)
      continue;
    return Duel_ApplyStatModViaZoneApplier(ptr, ptr->card,
                                           sDynamicZoneStats[i].applyZone);
  }

  return FALSE;
}

u8 Duel_CanBeAttackedUnlessControllerHasOther(struct DuelCard *zone, u16 cardId,
                                              MonsterZonePredicate otherPred)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id != cardId)
    return TRUE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return TRUE;

  return !Duel_TurnRowHasOtherMonsterMatching(turnRow, col, otherPred);
}

u8 Duel_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 i;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  for (i = 0; i < ARRAY_COUNT(sAttackGates); i++) {
    if (sAttackGates[i].cardId != zone->id)
      continue;
    return Duel_CanBeAttackedUnlessControllerHasOther(
        zone, sAttackGates[i].cardId, sAttackGates[i].blockWhenControllerHasOther);
  }

  for (i = 0; i < ARRAY_COUNT(sAttackZoneChecks); i++) {
    if (!sAttackZoneChecks[i](zone))
      return FALSE;
  }

  return TRUE;
}

struct DuelCard *Duel_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 i;
  struct DuelCard *target;

  for (i = 0; i < ARRAY_COUNT(sForcedAttackRedirects); i++) {
    target = sForcedAttackRedirects[i].getForcedTarget(defenderDuelist);
    if (target != NULL)
      return target;
  }

  return NULL;
}

u8 Duel_MonsterMayBeAttacked(struct DuelCard *zone)
{
  struct DuelCard *forcedTarget;
  u8 defenderDuelist;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  defenderDuelist = GetDuelistForZone(zone);
  if (defenderDuelist == 0xFF)
    return TRUE;

  forcedTarget = Duel_GetForcedAttackTarget(defenderDuelist);
  if (forcedTarget == NULL)
    return TRUE;

  return zone == forcedTarget;
}

u8 Duel_ForcedAttackBlocksDirect(u8 defenderDuelist)
{
  return Duel_GetForcedAttackTarget(defenderDuelist) != NULL;
}

u8 Duel_CanSelectAttackTarget(const struct DuelCard *attacker,
                              const struct DuelCard *defender)
{
  if (!MorphtronicMagnen_CanSelectAttackTarget(attacker, defender))
    return FALSE;

  return TRUE;
}

u8 CanMonsterBeDestroyedByBattle(u16 cardId, u8 duelist, u16 battleAtk, u16 opponentBattleAtk)
{
  (void)duelist;
  (void)battleAtk;
  (void)opponentBattleAtk;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == REAPER_ON_THE_NIGHTMARE || cardId == SPIRIT_REAPER
      || cardId == ELEMENTAL_HERO_PHOENIX_ENFORCER
      || cardId == ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER
      || cardId == YUBEL || cardId == YUBEL_TERROR_INCARNATE
      || cardId == YUBEL_THE_ULTIMATE_NIGHTMARE
      || cardId == MARSHMALLON
      || cardId == TURBO_ROCKET)
    return FALSE;

  return TRUE;
}

struct DuelBattleActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct DuelBattleActionData sActionData;

static u8 IsMonsterVersusMonsterBattleAction(u8 actionId)
{
  return actionId == 1 || actionId == 2 || actionId == 3 || actionId == 5;
}

static u8 BattleAtksEqualForKishido(u16 playerAtk, u16 opponentAtk)
{
  return playerAtk == opponentAtk && (playerAtk | opponentAtk);
}

static void ApplyKishidoSpiritEqualAtkProtection(void)
{
  // GBA text: your-side monsters only — not TCG "neither destroyed".
  if (!BattleAtksEqualForKishido(
          sActionData.playerCardAtkOrLifePointsMod,
          sActionData.opponentCardAtkOrLifePointsMod))
    return;

  if (IsKishidoSpiritActiveForDuelist(DUEL_PLAYER))
    sActionData.flags &= ~1u;

  if (IsKishidoSpiritActiveForDuelist(DUEL_OPPONENT))
    sActionData.flags &= ~2u;
}

void Duel_ApplyBattleDestroyProtection(void)
{
  if (!IsMonsterVersusMonsterBattleAction(sActionData.id))
    return;

  ApplyKishidoSpiritEqualAtkProtection();

  if ((sActionData.flags & 1)
      && !ElementalHeroTempestProtectsBattleZone(sActionData.playerMonsterRow, sActionData.unkA)
      && !KnightOfPentacles_ProtectsBattleZone(sActionData.playerMonsterRow, sActionData.unkA)
      && !Flavian_PreventsBattleDestroy(
          gFixedZones[sActionData.playerMonsterRow][sActionData.unkA])
      && !CanMonsterBeDestroyedByBattle(
          sActionData.playerCardId, DUEL_PLAYER,
          sActionData.playerCardAtkOrLifePointsMod,
          sActionData.opponentCardAtkOrLifePointsMod)) {
    sActionData.flags &= ~1;
  }
  Flavian_ClearBattleDestroyProtection(
      gFixedZones[sActionData.playerMonsterRow][sActionData.unkA]);

  if ((sActionData.flags & 2)
      && !ElementalHeroTempestProtectsBattleZone(sActionData.opponentMonsterRow, sActionData.unk16)
      && !KnightOfPentacles_ProtectsBattleZone(sActionData.opponentMonsterRow, sActionData.unk16)
      && !Flavian_PreventsBattleDestroy(
          gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16])
      && !CanMonsterBeDestroyedByBattle(
          sActionData.opponentCardId, DUEL_OPPONENT,
          sActionData.opponentCardAtkOrLifePointsMod,
          sActionData.playerCardAtkOrLifePointsMod)) {
    sActionData.flags &= ~2;
  }
  Flavian_ClearBattleDestroyProtection(
      gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16]);
}

void Duel_RemapMutualDestroyBattleAnim(u8 playerDestroy, u8 opponentDestroy)
{
  if (!IsMonsterVersusMonsterBattleAction(sActionData.id))
    return;

  if (playerDestroy && opponentDestroy) {
    gUnk2023EA0.unk18 = 2;
    return;
  }

  if (!playerDestroy && !opponentDestroy) {
    gUnk2023EA0.unk18 = 8;
    return;
  }

  if (gUnk2023EA0.unk18 != 2 && gUnk2023EA0.unk18 != 16 && gUnk2023EA0.unk18 != 17)
    return;

  if (!playerDestroy && opponentDestroy)
    gUnk2023EA0.unk18 = 1;
  else if (playerDestroy && !opponentDestroy)
    gUnk2023EA0.unk18 = 3;
}

void Duel_ActivateContinuousZone(struct DuelCard *zone)
{
  if (zone == NULL)
    return;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
}

u16 Duel_GetZoneFinalAtk(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return 0;

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;
  gSetFinalStatZone = NULL;
  return atk;
}

u8 Duel_FixedMonsterRowForDuelist(u8 fixedDuelist)
{
  return fixedDuelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

u8 Duel_FixedDuelistForMonsterRow(u8 fixedRow)
{
  return fixedRow == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;
}

u8 Duel_TurnMonsterRowForDuelist(u8 turnDuelist)
{
  return MonsterRowForDuelist(turnDuelist);
}

u8 Duel_TurnDuelistForFixedDuelist(u8 fixedDuelist)
{
  return FixedDuelistToTurnDuelist(fixedDuelist);
}

u8 Duel_TurnDuelistMatchingWhoseTurn(u8 fixedDuelist)
{
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER) ? ACTIVE_DUELIST
                                                                         : INACTIVE_DUELIST;
}

u8 Duel_CountMonstersOnTurnRow(u8 turnRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[turnRow][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

u8 Duel_IsFixedMonsterRow(u8 fixedRow)
{
  return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == PLAYER_MONSTER_ROW;
}

u8 Duel_IsTurnMonsterRow(u8 turnRow)
{
  return turnRow == INACTIVE_DUELIST_MONSTER_ROW || turnRow == ACTIVE_DUELIST_MONSTER_ROW;
}

u8 Duel_FixedMonsterRowToTurnMonsterRow(u8 fixedRow)
{
  u8 fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);

  return Duel_TurnMonsterRowForDuelist(turnDuelist);
}

u8 Duel_FixedMonsterRowHasMultipleMonsterTypes(u8 fixedRow)
{
  u8 col;
  u8 otherCol;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];
    u8 typeA;

    if (zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    typeA = gCardInfo.type;

    for (otherCol = col + 1; otherCol < MAX_ZONES_IN_ROW; otherCol++) {
      struct DuelCard *other = gFixedZones[fixedRow][otherCol];

      if (other->id == CARD_NONE)
        continue;

      if (GetTypeGroup(other->id) != TYPE_GROUP_MONSTER)
        continue;

      SetCardInfo(other->id);
      if (gCardInfo.type != typeA)
        return TRUE;
    }
  }

  return FALSE;
}

u8 Duel_GetLeftmostMonsterTypeOnFixedRow(u8 fixedRow)
{
  u8 col;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    return gCardInfo.type;
  }

  return 0xFF;
}

static u8 MonsterZoneHasWrongTypeForSingleTypeLock(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 keptType;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  keptType = Duel_GetLeftmostMonsterTypeOnFixedRow(fixedRow);
  if (keptType == 0xFF)
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.type != keptType;
}

enum DuelActionResult Duel_EnforceSingleMonsterTypeOnFixedRow(u8 fixedRow, u8 updateGfx)
{
  u8 turnRow;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return DUEL_ACTION_INVALID;

  if (Duel_GetLeftmostMonsterTypeOnFixedRow(fixedRow) == 0xFF)
    return DUEL_ACTION_OK;

  turnRow = Duel_FixedMonsterRowToTurnMonsterRow(fixedRow);
  return Duel_DestroyAllMonstersMatching(turnRow, MonsterZoneHasWrongTypeForSingleTypeLock,
                                         updateGfx);
}

void Duel_EnforceSingleMonsterTypeOnBothMonsterRows(u8 updateGfx)
{
  if (Duel_EnforceSingleMonsterTypeOnFixedRow(OPPONENT_MONSTER_ROW, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_EnforceSingleMonsterTypeOnFixedRow(PLAYER_MONSTER_ROW, updateGfx);
}

void Duel_NotifyFixedMonsterRowChanged(u8 fixedRow)
{
  if (!Duel_IsFixedMonsterRow(fixedRow))
    return;

  /* Field-continuous checks (Rivalry / Level Limit / Amazoness Tiger / Ring)
   * subscribe to ON_FIELD_CHANGE via EffectEvent_EnsureInit. */
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);
}

void Duel_NotifyMonsterZoneChanged(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnRow;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &col)) {
    Duel_NotifyFixedMonsterRowChanged(fixedRow);
    return;
  }

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  fixedRow = Duel_FixedMonsterRowForDuelist(
      TurnDuelistToFixed(turnRow == ACTIVE_DUELIST_MONSTER_ROW ? ACTIVE_DUELIST
                                                               : INACTIVE_DUELIST));
  Duel_NotifyFixedMonsterRowChanged(fixedRow);
}

void Duel_CheckRivalryOfWarlordsAfterFieldChange(void)
{
  RivalryOfWarlords_CheckAfterFieldChange();
}

void Duel_CheckLevelLimitAreaBAfterFieldChange(void)
{
  LevelLimitAreaB_CheckAfterFieldChange();
}

void Duel_CheckLevelLimitAreaAAfterFieldChange(void)
{
  LevelLimitAreaA_CheckAfterFieldChange();
}

void Duel_CheckAmazonessTigerAfterFieldChange(void)
{
  AmazonessTiger_EnforceUniquenessOnField();
}

void Duel_CheckRingOfDestructionAfterFieldChange(void)
{
  RingOfDestruction_CheckAfterFieldChange();
}

u8 Duel_IsMonsterZoneTarget(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

/* ponytail: PARTIAL batches grew ApplyFieldZoneStats to ~75 overlay calls; many
 * each rescanned both backrows. Snapshot once per overlay pass. */
#define FACEUP_BACKROW_CACHE_MAX (MAX_ZONES_IN_ROW * 2)

struct FaceUpBackrowCacheEntry {
  struct DuelCard *zone;
  u8 fixedRow;
};

static struct FaceUpBackrowCacheEntry sFaceUpBackrowCache[FACEUP_BACKROW_CACHE_MAX] APPEND_DATA = {{0}};
static u8 sFaceUpBackrowCacheCount APPEND_DATA = {0};
static u8 sFaceUpBackrowCacheDepth APPEND_DATA = {0};

void Duel_BeginFaceUpBackrowCache(void)
{
  u8 row;
  u8 col;
  u8 n;

  if (sFaceUpBackrowCacheDepth > 0) {
    sFaceUpBackrowCacheDepth++;
    return;
  }

  n = 0;
  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == CARD_NONE || zone->isFaceUp != TRUE)
        continue;
      if (n >= FACEUP_BACKROW_CACHE_MAX)
        break;
      sFaceUpBackrowCache[n].zone = zone;
      sFaceUpBackrowCache[n].fixedRow = row;
      n++;
    }
  }
  sFaceUpBackrowCacheCount = n;
  sFaceUpBackrowCacheDepth = 1;
}

void Duel_EndFaceUpBackrowCache(void)
{
  if (sFaceUpBackrowCacheDepth == 0)
    return;
  sFaceUpBackrowCacheDepth--;
}

static struct DuelCard *FindInFaceUpBackrowCache(u8 fixedRowOrFF, u16 cardId)
{
  u8 i;

  for (i = 0; i < sFaceUpBackrowCacheCount; i++) {
    if (sFaceUpBackrowCache[i].zone->id != cardId)
      continue;
    if (fixedRowOrFF != 0xFF && sFaceUpBackrowCache[i].fixedRow != fixedRowOrFF)
      continue;
    return sFaceUpBackrowCache[i].zone;
  }
  return NULL;
}

struct DuelCard *Duel_FindFixedZoneById(u8 fixedRow, u16 cardId, u8 requireFaceUp)
{
  u8 col;

  if (sFaceUpBackrowCacheDepth > 0 && requireFaceUp
      && (fixedRow == PLAYER_BACKROW || fixedRow == OPPONENT_BACKROW))
    return FindInFaceUpBackrowCache(fixedRow, cardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id != cardId)
      continue;
    if (requireFaceUp && zone->isFaceUp != TRUE)
      continue;
    return zone;
  }

  return NULL;
}

struct DuelCard *Duel_FindBackrowCard(u8 fixedDuelist, u16 cardId, u8 requireFaceUp)
{
  u8 backrow = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  return Duel_FindFixedZoneById(backrow, cardId, requireFaceUp);
}

struct DuelCard *Duel_FindBackrowCardOnField(u16 cardId, u8 requireFaceUp)
{
  struct DuelCard *zone;

  if (sFaceUpBackrowCacheDepth > 0 && requireFaceUp)
    return FindInFaceUpBackrowCache(0xFF, cardId);

  zone = Duel_FindBackrowCard(DUEL_OPPONENT, cardId, requireFaceUp);

  if (zone != NULL)
    return zone;

  return Duel_FindBackrowCard(DUEL_PLAYER, cardId, requireFaceUp);
}

u8 Duel_IsBackrowCardOnField(u16 cardId, u8 requireFaceUp)
{
  return Duel_FindBackrowCardOnField(cardId, requireFaceUp) != NULL;
}

u8 Duel_FixedMonsterSlotBit(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return 0xFF;

  return (fixedRow - OPPONENT_MONSTER_ROW) * MAX_ZONES_IN_ROW + col;
}

u8 Duel_ZoneIsHandSlot(const struct DuelCard *zone)
{
  u8 turnDuelist;
  u8 col;

  if (zone == NULL)
    return FALSE;

  if (SixCardHand_IsHandZone(zone))
    return TRUE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[PLAYER_HAND][col] == zone)
      return TRUE;
  }

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gTurnHands[turnDuelist][col] == zone)
        return TRUE;
    }
  }

  return FALSE;
}

enum DuelActionResult Duel_ChangeLpSuppressingEffectText(u8 turnDuelist, s32 delta, u8 updateGfx)
{
  u8 hideEffectText = gHideEffectText;
  enum DuelActionResult result;

  gHideEffectText = TRUE;
  result = Duel_ChangeLp(turnDuelist, delta, updateGfx);
  gHideEffectText = hideEffectText;
  return result;
}

enum DuelActionResult Duel_ChangeLpWithPrefaceText(u8 turnDuelist, s32 delta, u16 cardId,
                                                   u8 textType, u8 updateGfx)
{
  u8 hideEffectText = gHideEffectText;
  enum DuelActionResult result;

  if (!hideEffectText) {
    Duel_ShowEffectTextTyped(cardId, textType);
    ResetCardEffectTextData();
  }

  gHideEffectText = TRUE;
  result = Duel_ChangeLp(turnDuelist, delta, updateGfx);
  gHideEffectText = hideEffectText;
  return result;
}

enum DuelActionResult Duel_ResolveBurnSpell(u16 spellId, s32 damage, u8 destroySpellGfx)
{
  enum DuelActionResult result;

  result = Duel_ChangeLp(INACTIVE_DUELIST, -damage, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_ShowEffectText(spellId);
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   destroySpellGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_ResolveHealSpell(u16 spellId, s32 heal, u8 destroySpellGfx)
{
  enum DuelActionResult result;

  result = Duel_ChangeLp(ACTIVE_DUELIST, heal, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_ShowEffectText(spellId);
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   destroySpellGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_TryResolveBurnSpellThroughTraps(u16 spellId, s32 damage)
{
  /* Inline trap gate — do not stash args in APPEND_DATA (ROM; writes are no-ops). */
  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect((u16)damage);
      return DUEL_ACTION_BLOCKED;
    }
  }

  return Duel_ResolveBurnSpell(spellId, damage, TRUE);
}

enum DuelActionResult Duel_TryResolveHealSpellThroughTraps(u16 spellId, s32 heal)
{
  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect((u16)heal);
      return DUEL_ACTION_BLOCKED;
    }
  }

  return Duel_ResolveHealSpell(spellId, heal, TRUE);
}

enum DuelActionResult Duel_TryResolveStealLpThroughTraps(u16 spellId, s32 amount)
{
  enum DuelActionResult result;

  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect((u16)amount);
      return DUEL_ACTION_BLOCKED;
    }
  }

  result = Duel_ChangeLp(INACTIVE_DUELIST, -amount, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  result = Duel_ChangeLp(ACTIVE_DUELIST, amount, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_ShowEffectText(spellId);
  return Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                          TRUE);
}

enum DuelActionResult Duel_TryResolveUpstartThroughTraps(u16 spellId, s32 opponentHeal)
{
  enum DuelActionResult result;

  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect((u16)opponentHeal);
      return DUEL_ACTION_BLOCKED;
    }
  }

  result = Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                            FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  result = Duel_DrawCards(ACTIVE_DUELIST, 1, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  result = Duel_ChangeLp(INACTIVE_DUELIST, opponentHeal, TRUE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_ShowEffectText(spellId);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_TryResolveBothPlayersHealThroughTraps(u16 spellId, s32 heal)
{
  enum DuelActionResult result;

  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect((u16)heal);
      return DUEL_ACTION_BLOCKED;
    }
  }

  result = Duel_ChangeLp(ACTIVE_DUELIST, heal, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  result = Duel_ChangeLp(INACTIVE_DUELIST, heal, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_ShowEffectText(spellId);
  return Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                          TRUE);
}

enum DuelActionResult Duel_TryResolveDestroyInactiveMonstersThroughTraps(u16 spellId)
{
  enum DuelActionResult result;

  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect(0);
      return DUEL_ACTION_BLOCKED;
    }
  }

  result = Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER || IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  Duel_ShowEffectText(spellId);
  return Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                          TRUE);
}

enum DuelActionResult Duel_TryResolveDestroyActiveMonstersBurnPerThroughTraps(u16 spellId,
                                                                              u16 damagePer)
{
  u8 monstersBefore;
  u8 monstersDestroyed;
  enum DuelActionResult result;

  if (damagePer == 0)
    return DUEL_ACTION_INVALID;

  if (GetTypeGroup(spellId) == TYPE_GROUP_SPELL) {
    SetupSpellTrapOrigin();

    if (!Duel_IsOriginActivationProtectedFromNegation()
        && IsTrapTriggered() == TRUE && !gHideEffectText) {
      ActivateTrapEffect(0);
      return DUEL_ACTION_BLOCKED;
    }
  }

  Duel_ShowEffectText(spellId);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  monstersBefore = Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW);
  result = Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW, NULL, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER || IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  monstersDestroyed = monstersBefore - Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW);
  if (monstersDestroyed > 0) {
    result = Duel_ChangeLp(INACTIVE_DUELIST, -(s32)monstersDestroyed * (s32)damagePer, FALSE);
    if (result == DUEL_ACTION_DUEL_OVER || IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  return Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                          TRUE);
}

enum DuelActionResult Duel_MillDeckDifferenceToMatchOpponent(u8 updateGfx)
{
  u8 myRemaining;
  u8 oppRemaining;
  u8 millCount;
  u8 activeFixed;
  u8 inactiveFixed;
  u8 deckSize;
  u8 top;

  activeFixed = (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
                    ? DUEL_PLAYER
                    : DUEL_OPPONENT;
  inactiveFixed = (activeFixed == DUEL_PLAYER) ? DUEL_OPPONENT : DUEL_PLAYER;

  deckSize = NumCardsInDeck(activeFixed);
  top = gDuelDecks[activeFixed].cardsDrawn;
  myRemaining = (deckSize > top) ? (u8)(deckSize - top) : 0;

  deckSize = NumCardsInDeck(inactiveFixed);
  top = gDuelDecks[inactiveFixed].cardsDrawn;
  oppRemaining = (deckSize > top) ? (u8)(deckSize - top) : 0;

  if (myRemaining <= oppRemaining)
    return DUEL_ACTION_BLOCKED;

  millCount = (u8)(myRemaining - oppRemaining);
  return Duel_MillTopDeckCards(ACTIVE_DUELIST, millCount, updateGfx);
}

void Duel_ShowTrapResponseText(u16 trapId, u16 originCardId)
{
  if (gHideEffectText)
    return;

  gCardEffectTextData.cardId2 = originCardId;
  Duel_ShowEffectText(trapId);
}

void Duel_ShowEffectText(u16 cardId)
{
  if (gHideEffectText)
    return;

  gCardEffectTextData.cardId = cardId;
  ActivateCardEffectText();
}

void Duel_ShowEffectTextTyped(u16 cardId, u8 textType)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(textType);
  gCardEffectTextData.cardId = cardId;
  ActivateCardEffectText();
}

enum DuelActionResult Duel_TryResolveSpellThroughTrapsEx(u16 spellId, u16 trapLp,
                                                         void (*resolveBody)(void))
{
  if (GetTypeGroup(spellId) != TYPE_GROUP_SPELL) {
    if (resolveBody != NULL)
      resolveBody();
    return DUEL_ACTION_OK;
  }

  SetupSpellTrapOrigin();

  if (Duel_IsOriginActivationProtectedFromNegation()) {
    if (resolveBody != NULL)
      resolveBody();
    return DUEL_ACTION_OK;
  }

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    if (resolveBody != NULL)
      resolveBody();
    return DUEL_ACTION_OK;
  }

  ActivateTrapEffect(trapLp);
  return DUEL_ACTION_BLOCKED;
}

enum DuelActionResult Duel_TryResolveSpellThroughTraps(u16 spellId, void (*resolveBody)(void))
{
  return Duel_TryResolveSpellThroughTrapsEx(spellId, 0, resolveBody);
}

enum DuelActionResult Duel_TryResolveTrapThroughTraps(u16 trapId)
{
  if (GetTypeGroup(trapId) != TYPE_GROUP_TRAP)
    return DUEL_ACTION_OK;

  if (Duel_IsOriginActivationProtectedFromNegation())
    return DUEL_ACTION_OK;

  if (IsTrapTriggered() != TRUE || gHideEffectText)
    return DUEL_ACTION_OK;

  ActivateTrapEffect(0);
  return DUEL_ACTION_BLOCKED;
}

u8 Duel_IsOriginActivationProtectedFromNegation(void)
{
  u8 originType;

  if (gTrapEffectData.originCardId == CARD_NONE)
    return FALSE;

  originType = GetTypeGroup(gTrapEffectData.originCardId);
  if (originType != TYPE_GROUP_SPELL && originType != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_DuelistActivationsProtectedFromNegation(TurnDuelistToFixed(ACTIVE_DUELIST));
}

s16 Duel_FindDeckCardIndex(u8 duelist, u16 cardId)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == cardId)
      return (s16)i;
  }

  return -1;
}

enum DuelActionResult Duel_RemoveDeckCardAt(u8 duelist, u8 index, u8 updateGfx)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 deckSize = NumCardsInDeck(fixedDuelist);

  if (index < top || index >= deckSize)
    return DUEL_ACTION_INVALID;

  gDuelDecks[fixedDuelist].cards[index] = gDuelDecks[fixedDuelist].cards[top];
  gDuelDecks[fixedDuelist].cardsDrawn++;
  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

void Duel_ShuffleDeckFromDrawn(u8 duelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 start = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 end = NumCardsInDeck(fixedDuelist);
  u8 size;
  int i;

  if (end <= start)
    return;

  size = end - start;
  if (size <= 1)
    return;

  for (i = 0; i < 200; i++) {
    u8 indexA = RandRangeU8(0, size - 1);
    u8 indexB = RandRangeU8(0, size - 1);
    u16 temp = gDuelDecks[fixedDuelist].cards[start + indexA];

    gDuelDecks[fixedDuelist].cards[start + indexA] =
        gDuelDecks[fixedDuelist].cards[start + indexB];
    gDuelDecks[fixedDuelist].cards[start + indexB] = temp;
  }
}

enum DuelActionResult Duel_AddDeckCardToHand(u8 duelist, u16 cardId, u8 updateGfx)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  s16 deckIndex;
  s8 handZone;
  u16 foundId;
  struct DuelCard *handSlot;
  enum DuelActionResult result;

  if (cardId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  handZone = FirstEmptyZoneInRow(gTurnHands[duelist]);
  if (handZone < 0)
    return DUEL_ACTION_NO_ZONE;

  deckIndex = Duel_FindDeckCardIndex(duelist, cardId);
  if (deckIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  foundId = gDuelDecks[fixedDuelist].cards[deckIndex];
  result = Duel_RemoveDeckCardAt(duelist, (u8)deckIndex, FALSE);
  if (result != DUEL_ACTION_OK)
    return result;

  Duel_ShuffleDeckFromDrawn(duelist);

  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[duelist], (u8)handZone);
  handSlot->id = foundId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_SpecialSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  s8 handZone;
  u16 monsterId;
  enum DuelActionResult result;
  u8 relockHand = FALSE;

  if (ArchlordKristya_BlocksSpecialSummon(cardId))
    return DUEL_ACTION_BLOCKED;

  if (ElShaddollAnoyatyllis_BlocksHandOrGySpecialSummon())
    return DUEL_ACTION_BLOCKED;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (duelist == ACTIVE_DUELIST
      && gTurnDuelistBattleState[duelist]->summoningBlocked) {
    UnlockCardsInRow(ACTIVE_DUELIST_HAND);
    relockHand = TRUE;
  }

  handZone = SelectHandZone(duelist, cardId, pred);
  if (handZone < 0) {
    if (relockHand)
      LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);
    return DUEL_ACTION_NO_TARGET;
  }

  monsterId = SixCardHand_ZoneAtHandRow(handRow, handZone)->id;
  if (monsterId == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    MarkAbsoluteZeroHandSummonCleanup();
  ClearZone(SixCardHand_ZoneAtHandRow(handRow, handZone));
  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (relockHand)
    LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonFromHandZone(u8 duelist, s8 handZone,
                                                     struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u16 monsterId;
  enum DuelActionResult result;

  if (ElShaddollAnoyatyllis_BlocksHandOrGySpecialSummon())
    return DUEL_ACTION_BLOCKED;

  if (handZone < 0
      || handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return DUEL_ACTION_INVALID;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  monsterId = SixCardHand_ZoneAtHandRow(handRow, handZone)->id;

  if (ArchlordKristya_BlocksSpecialSummon(monsterId))
    return DUEL_ACTION_BLOCKED;
  if (monsterId == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    MarkAbsoluteZeroHandSummonCleanup();
  ClearZone(SixCardHand_ZoneAtHandRow(handRow, handZone));
  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonFromGrave(u8 duelist, u16 cardId, struct DuelSummonOpts opts)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u16 revivedId;

  if (ArchlordKristya_BlocksSpecialSummon(cardId))
    return DUEL_ACTION_BLOCKED;

  if (ElShaddollAnoyatyllis_BlocksHandOrGySpecialSummon())
    return DUEL_ACTION_BLOCKED;

  if (Necrovalley_BlocksGraveyardMove()
      || GravekeepersInscription_BlocksSpecialSummonFromGraveyard())
    return DUEL_ACTION_BLOCKED;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (cardId != CARD_NONE && gTurnDuelistBattleState[duelist]->graveyard != cardId)
    return DUEL_ACTION_NO_TARGET;

  revivedId = GetGraveCardAndClearGrave(fixedDuelist);
  if (revivedId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  if (cardId != CARD_NONE && revivedId != cardId)
    return DUEL_ACTION_NO_TARGET;

  return PlaceMonsterFromId(duelist, revivedId, opts);
}

enum DuelActionResult Duel_SpecialSummonFromDeck(u8 duelist, u16 cardId, struct DuelSummonOpts opts)
{
  s16 deckIndex;
  u16 monsterId;
  enum DuelActionResult result;

  ColosseumCage_MarkSpecialSummonFromDeck(TurnDuelistToFixed(duelist));

  if (ArchlordKristya_BlocksSpecialSummon(cardId))
    return DUEL_ACTION_BLOCKED;

  if (HarpieLadyPhoenixFormation_CannotSpecialSummonFromMainOrExtraDeck())
    return DUEL_ACTION_BLOCKED;

  if (cardId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  deckIndex = Duel_FindDeckCardIndex(duelist, cardId);
  if (deckIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  monsterId = cardId;
  result = Duel_RemoveDeckCardAt(duelist, (u8)deckIndex, FALSE);
  if (result != DUEL_ACTION_OK)
    return result;

  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonMonsterId(u8 duelist, u16 monsterId,
                                                    struct DuelSummonOpts opts)
{
  enum DuelActionResult result;

  if (ArchlordKristya_BlocksSpecialSummon(monsterId))
    return DUEL_ACTION_BLOCKED;

  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_NormalSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  s8 handZone;
  u16 monsterId;
  int requiredTributes;
  enum DuelActionResult tributeResult;
  u8 monsterRow = MonsterRowForDuelist(duelist);

  if (gTurnDuelistBattleState[duelist]->summoningBlocked)
    return DUEL_ACTION_BLOCKED;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return DUEL_ACTION_NO_ZONE;

  handZone = SelectHandZone(duelist, cardId, pred);
  if (handZone < 0)
    return DUEL_ACTION_NO_TARGET;

  monsterId = SixCardHand_ZoneAtHandRow(handRow, handZone)->id;
  if (ReptilianneServant_BlocksNormalSummonReptile(monsterId))
    return DUEL_ACTION_BLOCKED;
  if (monsterId == RARE_METAL_DRAGON)
    return DUEL_ACTION_INVALID;

  if (GetTypeGroup(monsterId) != TYPE_GROUP_MONSTER)
    return DUEL_ACTION_INVALID;

  requiredTributes = GetMonsterNumRequiredTributesForHandSlot((u8)handZone, monsterId);
  if (requiredTributes == MASK_OF_RESTRICT_TRIBUTE_BLOCK)
    return DUEL_ACTION_BLOCKED;

  if (requiredTributes > 0) {
    if (CountTributeMonstersOnRow(duelist, CARD_NONE) < (u8)requiredTributes)
      return DUEL_ACTION_NO_TARGET;

    SetPendingTributeSummonCardId(monsterId);
    tributeResult = PayTributesFromMonsterRow(duelist, (u8)requiredTributes, CARD_NONE);
    if (tributeResult != DUEL_ACTION_OK)
      return tributeResult;

    SetPendingSummonTributeCount((u8)requiredTributes);
    TryApplyPreciousCardsFromBeyondOnTributeSummon(monsterId, duelist);
  }

  if (monsterId == ELEMENTAL_HERO_ABSOLUTE_ZERO)
    MarkAbsoluteZeroHandSummonCleanup();
  ClearZone(SixCardHand_ZoneAtHandRow(handRow, handZone));
  tributeResult = PlaceMonsterFromId(duelist, monsterId, opts);
  if (tributeResult != DUEL_ACTION_OK)
    return tributeResult;

  BlockTurnSummoning(duelist);
  ClearPendingTributeSummonCardId();
  ClearPendingSummonTributeCount();

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_ReturnMonsterZoneToOwnerHand(struct DuelCard *zone, u8 updateGfx)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 handZone;

  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return DUEL_ACTION_INVALID;

  turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return DUEL_ACTION_NO_ZONE;

  {
    struct DuelCard *handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);

    CopyCard(handSlot, zone);
    handSlot->isFaceUp = FALSE;
    handSlot->isLocked = FALSE;
    handSlot->isDefending = FALSE;
    handSlot->unkTwo = 0;
    handSlot->unkThree = 0;
    handSlot->unk4 = 0;
    handSlot->willChangeSides = FALSE;
    ResetPermStage(handSlot);
    ResetTempStage(handSlot);
  }
  ClearZone(zone);
  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_BanishZone(struct DuelCard *zone, u8 updateGfx)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  RemovedFromPlay_PushZone(zone);
  ClearZone(zone);
  MaybeUpdateGfx(updateGfx);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

u16 Duel_BanishGraveyardAtFixed(u8 fixedDuelist, u8 index)
{
  u16 cardId;

  if (fixedDuelist > DUEL_OPPONENT)
    return CARD_NONE;

  if (Necrovalley_BlocksGraveyardBanish()
      || GravekeepersInscription_BlocksGraveyardBanish())
    return CARD_NONE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, index);
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return cardId;
}

u16 Duel_BanishGraveyardAtTurn(u8 turnDuelist, u8 index)
{
  return Duel_BanishGraveyardAtFixed(TurnDuelistToFixed(turnDuelist), index);
}

u16 Duel_BanishGraveyardTopTurn(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 count = GraveyardExpand_GetCount(fixedDuelist);

  if (count == 0)
    return CARD_NONE;

  return Duel_BanishGraveyardAtTurn(turnDuelist, count - 1);
}

static u8 sSpellEffectResolveDepth APPEND_DATA = 0;
static u8 sMonsterEffectResolveDepth APPEND_DATA = 0;

void Duel_BeginSpellEffectResolve(void)
{
  sSpellEffectResolveDepth++;
}

void Duel_EndSpellEffectResolve(void)
{
  if (sSpellEffectResolveDepth > 0)
    sSpellEffectResolveDepth--;

  if (sSpellEffectResolveDepth == 0) {
    SilentMagicianLv4_NoteSpellResolved();
    TryIncrementSpellCountersOnSpellResolve();
  }
}

u8 Duel_IsSpellEffectResolving(void)
{
  return sSpellEffectResolveDepth > 0;
}

void Duel_BeginMonsterEffectResolve(void)
{
  sMonsterEffectResolveDepth++;
}

void Duel_EndMonsterEffectResolve(void)
{
  if (sMonsterEffectResolveDepth > 0)
    sMonsterEffectResolveDepth--;
}

u8 Duel_IsMonsterEffectResolving(void)
{
  return sMonsterEffectResolveDepth > 0;
}

u8 Duel_ZoneIsImmuneToSpellEffects(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return FALSE;

  return IsImmuneToSpellEffectsOnField(zone->id, turnRow)
      || ForbiddenLance_IsImmuneToSpellTrapEffects(zone);
}

u8 Duel_SpellMayTargetMonsterZone(struct DuelCard *zone)
{
  return !Duel_ZoneIsImmuneToSpellEffects(zone)
      && !ForbiddenDress_IsTargetImmune(zone)
      && !AmazonessScouts_IsTargetImmune(zone)
      && !AmazonessAugusta_IsTargetImmune(zone)
      && !BlueEyesAlternativeUltimateDragon_IsTargetImmune(zone)
      && !DivineSerpentGeh_IsTargetImmune(zone);
}

u8 Duel_IsAnyTrapActivationBlocked(void)
{
  if (IsRoyalDecreeActiveOnField())
    return TRUE;
  if (IsSorcererOfDarkMagicTrapLockActive())
    return TRUE;
  return FALSE;
}

u8 Duel_IsCardActivationBlocked(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (GenerationNext_BlocksCardActivation(cardId))
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_RITUAL) {
    if (ColdWave_IsSpellTrapPlayOrSetLocked())
      return TRUE;
    if (TheWickedAvatar_IsSpellTrapActivationLocked())
      return TRUE;
    if (IsSpellCancellerSpellLockActive())
      return TRUE;
    if (IsImperialOrderNegatingSpell(cardId))
      return TRUE;
    return FALSE;
  }

  if (typeGroup == TYPE_GROUP_TRAP) {
    if (ColdWave_IsSpellTrapPlayOrSetLocked())
      return TRUE;
    if (TheWickedAvatar_IsSpellTrapActivationLocked())
      return TRUE;
    if (IsRoyalDecreeNegatingTrap(cardId))
      return TRUE;
    if (IsSorcererOfDarkMagicTrapLockActive())
      return TRUE;
    if (AncientGearCannon_BlocksOppTrap())
      return TRUE;
    if (MirageDragon_BlocksInactiveTrapInBattlePhase()
        || MirageDragon_BlocksActiveTrapInBattlePhase())
      return TRUE;
    return FALSE;
  }

  return FALSE;
}

u8 Duel_ZoneCannotChangeBattlePosition(const struct DuelCard *zone)
{
  return zone != NULL && (zone->unk4 & 1);
}

// --- PickZone targeting ----------------------------------------------------

static u8 FindFirstValidTarget(u8 *outRow, u8 *outCol)
{
  u8 row, col;

  if (gPickZoneState.validator == NULL)
    return FALSE;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < 5; col++) {
      if (gPickZoneState.validator(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }
  return FALSE;
}

void Duel_SetupPickZone(PickZoneValidator validator, PickZoneResolver resolver,
                         PickZoneCanceller canceller, PickZoneAiPicker aiPicker)
{
  gPickZoneState.validator = validator;
  gPickZoneState.resolver = resolver;
  gPickZoneState.canceller = canceller;
  gPickZoneState.aiPicker = aiPicker;
}

void Duel_ClearPickZone(void)
{
  gPickZoneState.validator = NULL;
  gPickZoneState.resolver = NULL;
  gPickZoneState.canceller = NULL;
  gPickZoneState.aiPicker = NULL;
}

enum DuelActionResult Duel_ActivateContinuousTrapPreamble(struct DuelCard *zone, u16 trapId)
{
  Duel_ActivateContinuousZone(zone);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return DUEL_ACTION_DUEL_OVER;

  Duel_ShowEffectTextTyped(trapId, 3);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

void Duel_TryActivateBackrowTrapOnTurnStart(u16 trapId,
                                            void (*activateBody)(struct DuelCard *))
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != trapId || zone->isFaceUp != FALSE)
      continue;

    activateBody(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}

u8 Duel_ShouldActivateTurnEffect(u16 cardId, u8 requireDefending, u8 requireAttacking)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != cardId)
    return FALSE;
  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->isFaceUp != TRUE)
    return FALSE;
  if (requireDefending && zone->isDefending != TRUE)
    return FALSE;
  if (requireAttacking && zone->isDefending != FALSE)
    return FALSE;

  return TRUE;
}

void Duel_EnterPickZoneTargeting(void)
{
  Duel_EnterPickZoneTargetingFromRow(gDuelCursor.destY);
}

void Duel_EnterPickZoneTargetingFromRow(u8 fromFixedRow)
{
  u8 targetRow, targetCol;

  if (!FindFirstValidTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_PICK_ZONE;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(fromFixedRow, gDuelCursor.currentY);
}

void Duel_HandlePickZoneA(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!gPickZoneState.validator(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gPickZoneState.resolver(targetRow, targetCol);

  /* If resolver re-entered targeting (multi-pick like Mobius), skip cleanup */
  if (gDuelCursor.state == DUEL_CURSOR_PICK_ZONE)
    return;

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void Duel_HandlePickZoneB(void)
{
  u8 currY = gDuelCursor.currentY;

  gPickZoneState.canceller();

  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void Duel_ResolvePickZoneForAi(void)
{
  u8 targetRow, targetCol;
  u16 originId;

  if (gPickZoneState.aiPicker == NULL || !gPickZoneState.aiPicker(&targetRow, &targetCol))
    return;

  if (gMonEffect.id != CARD_NONE && GetTypeGroup(gMonEffect.id) == TYPE_GROUP_MONSTER)
    originId = gMonEffect.id;
  else if (gActiveEffect.cardId != CARD_NONE
           && GetTypeGroup(gActiveEffect.cardId) == TYPE_GROUP_MONSTER)
    originId = gActiveEffect.cardId;
  else
    originId = CARD_NONE;

  if (Duel_TryNegateMonsterEffectOnTarget(originId, targetRow, targetCol))
    return;

  gPickZoneState.resolver(targetRow, targetCol);
}

void Duel_ResolveEquipStatBoost(struct DuelCard *target, struct DuelCard *spellZone,
                                u16 spellId, u8 stages)
{
  if (stages > MAX_ZONES_IN_ROW)
    stages = MAX_ZONES_IN_ROW;

  ApplyDynamicEquipStages(target, stages);
  RegisterDynamicEquip(spellZone, target, spellId, stages);
  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(spellId);
}

void Duel_ResetDestroyMaskState(u8 *destroyMask, u8 *fixedMonsterRow)
{
  *destroyMask = 0;
  *fixedMonsterRow = 0;
}

void Duel_DestroyMaskedMonstersFromState(u8 *destroyMask, u8 *fixedMonsterRow)
{
  u8 row;

  if (*destroyMask == 0)
    return;

  row = *fixedMonsterRow;
  Duel_DestroyMaskedMonstersInFixedRow(row, *destroyMask,
                                       Duel_FixedDuelistForMonsterRow(row), FALSE);
  Duel_ResetDestroyMaskState(destroyMask, fixedMonsterRow);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DuelHelpers_SelfCheck(void)
{
  struct DuelCard hand[5];
  struct DuelCard *handRow[5];
  struct DuelCard zone;
  u8 i;

  if (Duel_ClampStat(0xFFFF) != 0xFFFE || Duel_ClampStat(100) != 100)
    while (1)
      ;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    hand[i].id = (i < 3) ? (u16)(100 + i) : CARD_NONE;
    handRow[i] = &hand[i];
  }

  if (Duel_CountCardsInHand(handRow) != 3)
    while (1)
      ;

  zone.id = 1;
  InitMonsterZone(&zone, Duel_DefaultSpecialSummonOpts(FALSE));
  if (zone.unk4 != 2 || zone.isFaceUp != TRUE || zone.isDefending != FALSE)
    while (1)
      ;

  InitMonsterZone(&zone, Duel_DefaultNormalSummonOpts(FALSE));
  if (zone.unk4 != 0)
    while (1)
      ;

  {
    struct DuelSummonOpts locked = Duel_DefaultSpecialSummonOpts(FALSE);

    locked.lockMonster = TRUE;
    InitMonsterZone(&zone, locked);
    if (zone.isLocked != TRUE)
      while (1)
        ;
  }

  if (Duel_CardIsMonster(THE_THING_IN_THE_CRATER) != TRUE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(THE_THING_IN_THE_CRATER, TYPE_PYRO) != TRUE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(METEOR_B_DRAGON, TYPE_PYRO) != FALSE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(FLAME_MANIPULATOR, TYPE_PYRO) != TRUE)
    while (1)
      ;

  if (CanMonsterBeDestroyedByBattle(SPIRIT_REAPER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(SPIRIT_REAPER, DUEL_PLAYER, 2000, 1999) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(ELEMENTAL_HERO_PHOENIX_ENFORCER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(MARSHMALLON, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(TURBO_ROCKET, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(KAISER_GLIDER, DUEL_PLAYER, 1500, 1500) != TRUE)
    __builtin_trap();

  FusionDuel_SelfCheck();
  SynchroDuel_SelfCheck();
  CannotAttackThisTurn_SelfCheck();
}
#endif
