#include "global.h"
#include "configs/runtime.h"
#include "debug_ai_mode.h"
#include "debug_ruleset.h"
#include "yubel.h"
#include "timed_duel.h"
#include "mechanics_tutorial.h"
#include "duel_helpers.h"
#include "the_dark_door.h"
#include "ring_of_destruction.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "amazoness_tiger.h"
#include "blast_held_by_a_tribute.h"
#include "vengeful_bog_spirit.h"
#include "kaiser_colosseum.h"
#include "wall_of_revealing_light.h"
#include "world_suppression.h"
#include "berserk_gorilla.h"
#include "duel_opponent_hand_scroll.h"
#include "six_card_hand.h"
#include "removed_from_play.h"
#include "delayed_effects.h"
#include "court_of_justice.h"
#include "valhalla_hall_of_the_fallen.h"
#include "duel_attack_restrictions.h"
#include "thousand_energy.h"
#include "triangle_power.h"
#include "limiter_removal.h"
#include "yata_garasu.h"
#include "fenrir.h"
#include "time_seal.h"
#include "reckless_greed.h"
#include "copycat.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "the_tyrant_neptune.h"
#include "the_grand_jupiter.h"
#include "the_big_saturn.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "the_supremacy_sun.h"
#include "archlord_kristya.h"
#include "splendid_venus.h"
#include "card.h"
#include "chimeratech_overdragon.h"
#include "cybernetic_fusion_support.h"
#include "power_bond.h"
#include "imperial_order.h"
#include "dynamic_equip.h"
#include "big_bang_shot.h"
#include "embodiment_of_apophis.h"
#include "ai_sim.h"
#include "expanded_graveyard.h"
#include "xyz_duel.h"
#include "removed_from_play.h"
#include "ojama_trio.h"
#include "cost_down.h"
#include "custom_field_spell.h"
#include "graveyard_effects.h"
#include "elemental_hero_flash.h"
#include "familiar_knight.h"
#include "vampire_baby.h"
#include "ghost_knight_of_jackal.h"
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "royal_knight.h"
#include "elemental_hero_steam_healer.h"
#include "elemental_hero_flame_wingman.h"
#include "elemental_hero_core.h"
#include "elemental_hero_ice_edge.h"
#include "elemental_hero_tempest.h"
#include "elemental_hero_wildedge.h"
#include "elemental_hero_necroshade.h"
#include "elemental_hero_neos_alius.h"
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
#include "absorbing_kid_from_the_sky.h"
#include "airknight_parshath.h"
#include "sasuke_samurai_3.h"
#include "riryoku.h"
#include "mirror_wall.h"
#include "cyber_barrier_dragon.h"
#include "elemental_hero_great_tornado.h"
#include "the_wicked_dreadroot.h"
#include "the_wicked_eraser.h"
#include "the_wicked_avatar.h"
#include "elemental_hero_sunrise.h"
#include "zeriel.h"
#include "shatiel.h"
#include "seraphim_blaster.h"
#include "elemental_hero_gaia.h"
#include "elemental_hero_absolute_zero.h"
#include "elemental_hero_blazeman.h"
#include "elemental_hero_the_shining.h"
#include "monster_effect_usage.h"
#include "skull_invitation.h"
#include "coffin_seller.h"
#include "nightmare_wheel.h"
#include "future_fusion.h"
#include "reaper_on_the_nightmare.h"
#include "spirit_reaper.h"
#include "dark_room_of_nightmare.h"
#include "fire_princess.h"
#include "sasuke_samurai.h"

void DecrementSorlTurns(unsigned char);

extern u8 gSorlSkipDecrementAfterActivation;

static const u8 sSorlRemainPrefix[] APPEND_RODATA =
    "Swords of Revealing Light#0remains in effect for ";
static const u8 sSorlRemainSingular[] APPEND_RODATA = "#0more turn.#1";
static const u8 sSorlRemainPlural[] APPEND_RODATA = "#0more turns.#1";
static const u8 sSorlTurnCountOne[] APPEND_RODATA = "One";
static const u8 sSorlTurnCountTwo[] APPEND_RODATA = "Two";
static const u8 sSorlTurnCountThree[] APPEND_RODATA = "Three";

static const u8 *const sSorlTurnCountWords[] APPEND_RODATA = {
  NULL,
  sSorlTurnCountOne,
  sSorlTurnCountTwo,
  sSorlTurnCountThree,
};

static u8 *AppendSorlAscii(u8 *dest, const u8 *src) {
  while (*src)
    *dest++ = *src++;
  return dest;
}

static void Sorl_ShowTurnsRemainingText(u8 turnsRemaining) {
  u8 buffer[96];
  u8 *write = buffer;
  const u8 *turnWord;

  if (turnsRemaining == 0 || turnsRemaining > 3)
    return;

  turnWord = sSorlTurnCountWords[turnsRemaining];
  if (turnWord == NULL)
    return;

  write = AppendSorlAscii(write, sSorlRemainPrefix);
  write = AppendSorlAscii(write, turnWord);
  if (turnsRemaining == 1)
    write = AppendSorlAscii(write, sSorlRemainSingular);
  else
    write = AppendSorlAscii(write, sSorlRemainPlural);
  *write = 0;

  sub_8041C94(buffer, SWORDS_OF_REVEALING_LIGHT, 0, 0, 0);
}

void Sorl_MarkActivatedThisTurn(void) {
  gSorlSkipDecrementAfterActivation = TRUE;
}

void Sorl_TryDecrementAfterTurnEnd(void) {
  if (gSorlSkipDecrementAfterActivation) {
    gSorlSkipDecrementAfterActivation = FALSE;
    return;
  }

  if (gTurnDuelistBattleState[INACTIVE_DUELIST]->sorlTurns)
    DecrementSorlTurns(INACTIVE_DUELIST);
}

extern u8 gSuppressSkullInvitationDamage;

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct CheckLoserActionData {
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

extern struct CheckLoserActionData sActionData;

u8 TryPayChainEnergyCost(void);
u8 ShouldPayChainEnergyForHandToFieldCopy(const struct DuelCard *dst, const struct DuelCard *src);
void CopyCard(struct DuelCard *dst, struct DuelCard *src);
u8 ShouldApplySliferSummonPenalty(struct DuelCard *dst, struct DuelCard *src);
void MaybeApplySliferSummonPenaltyAfterCopy(struct DuelCard *dst);
void ClearPendingSliferSummonPenalty(void);
void ResolvePendingSliferSummonPenalty(void);
void ResetUltimateOfferingTurnState(void);
void ResetExecutorMakyuraTurnState(void);
void TryUnlockHandForUltimateOfferingExtraSummon(void);
void TryUnlockHandForCourtOfJusticeIgnition(void);
void CourtOfJustice_ResetTurnState(void);
void TryUnlockHandForValhallaHallOfTheFallenIgnition(void);
void UnlockCardsInRow(unsigned char turnRow);
void UnblockTurnSummoning(unsigned char currPlayer);
void BeginDuelBoardTurn(void);

void InitBoard(void);
void PlayerTurnMain(void);
void AI_Main(void);
void UpdateDuelGfxExceptField(void);
void InitButtonMaps(void);
void DisplayCardInfoBar(void);
void sub_8041E70(unsigned char, unsigned char);
void MoveCursorUp(void);
void MoveCursorDown(void);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void HandleAButtonAction(void);
void sub_8042F04(void);

extern unsigned char gIsPlayerTurnOver;
void sub_8041014(void);
void sub_8044B2C(void);
void UpdateAllDuelGfx(void);
void HandleBButtonAction(void);
void TryActivatingTurnEffects(void);
void TryActivatingPermanentEffects(void);
void UpdateFilteredInput_WithRepeat(void);
void DeclareLoser(unsigned char);
void DestroyKarateManAtEndOfTurn(void);
void DecrementSorlTurns(unsigned char);
void CheckLoserFlags(void);

extern u8 gDoubleSummonExtraSummonPending;
extern u8 gDoubleSummonExtraSummonUsed;

void EnableDoubleSummonForTurn(void);
static void TryUnlockHandForDoubleSummon(void);

static struct DuelCard *FindActiveSorlZone(void)
{
  u8 row;
  u8 i;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      struct DuelCard *zone = gFixedZones[row][i];

      if (zone->id == SWORDS_OF_REVEALING_LIGHT
          && zone->isFaceUp == TRUE
          && !IsImperialOrderNegatingSpell(SWORDS_OF_REVEALING_LIGHT))
        return zone;
    }
  }

  return NULL;
}

static u8 GetSorlBlockedDuelistByZone(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[PLAYER_BACKROW][i] == zone)
      return DUEL_OPPONENT;
    if (gFixedZones[OPPONENT_BACKROW][i] == zone)
      return DUEL_PLAYER;
  }

  return 2;
}

extern u16 gRepeatedOrNewButtons;
extern u16 gNewButtons;

static unsigned char ProcessInput__Replacement(void) {
  UpdateFilteredInput_WithRepeat();
  if (gRepeatedOrNewButtons & DPAD_UP)
    return 1;
  if (gRepeatedOrNewButtons & DPAD_DOWN)
    return 2;
  if (gRepeatedOrNewButtons & DPAD_LEFT)
    return 3;
  if (gRepeatedOrNewButtons & DPAD_RIGHT)
    return 4;
  if (gNewButtons & A_BUTTON)
    return 5;
  if (gNewButtons & L_BUTTON)
    return 6;
  if (gNewButtons & R_BUTTON)
    return 7;
  if (gNewButtons & B_BUTTON)
    return 8;
  if (gRepeatedOrNewButtons & START_BUTTON) {
    if (gRuntimeConfig.instant_win_with_start_button == TRUE)
      return 10;
    return 0;
  }
  if (gRepeatedOrNewButtons & SELECT_BUTTON)
    return 0;
  return 0;
}

void Duel_RunPickZoneInputLoop(void)
{
  u8 y;

  if (gDuelCursor.state != DUEL_CURSOR_PICK_ZONE && gPickZoneState.validator != NULL
      && IsDuelOver() != TRUE)
    Duel_EnterPickZoneTargeting();

  if (gDuelCursor.state != DUEL_CURSOR_PICK_ZONE || IsDuelOver() == TRUE)
    return;

  InitButtonMaps();
  while (gDuelCursor.state == DUEL_CURSOR_PICK_ZONE && IsDuelOver() != TRUE) {
    y = gDuelCursor.currentY;
    switch (ProcessInput__Replacement()) {
      case 1:
        MoveCursorUp();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 2:
        MoveCursorDown();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 3:
        MoveCursorLeft();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 4:
        MoveCursorRight();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 5:
        HandleAButtonAction();
        break;
      case 8:
        HandleBButtonAction();
        WaitForVBlank();
        break;
      default:
        WaitForVBlank();
        break;
    }
  }
}

LYN_REPLACE_CHECK(sub_803FBCC);
unsigned char sub_803FBCC__Replacement(unsigned char a, unsigned char b) {
  /* Mirror vanilla advantages/weaknesses (code_803F02C.c). No .rodata tables:
   * static const arrays in LynJump objs get gc'd and break the link. */
  if (gRuntimeConfig.disable_element_system == TRUE)
    return 1;
  if (a == ATTRIBUTE_DIVINE || b == ATTRIBUTE_DIVINE)
    return 1;

  switch (a) {
  case ATTRIBUTE_SHADOW:
    if (b == ATTRIBUTE_LIGHT) return 0;
    if (b == ATTRIBUTE_DREAM) return 2;
    break;
  case ATTRIBUTE_LIGHT:
    if (b == ATTRIBUTE_FIEND) return 0;
    if (b == ATTRIBUTE_SHADOW) return 2;
    break;
  case ATTRIBUTE_FIEND:
    if (b == ATTRIBUTE_DREAM) return 0;
    if (b == ATTRIBUTE_LIGHT) return 2;
    break;
  case ATTRIBUTE_DREAM:
    if (b == ATTRIBUTE_SHADOW) return 0;
    if (b == ATTRIBUTE_FIEND) return 2;
    break;
  case ATTRIBUTE_PYRO:
    if (b == ATTRIBUTE_FOREST) return 0;
    if (b == ATTRIBUTE_AQUA) return 2;
    break;
  case ATTRIBUTE_FOREST:
    if (b == ATTRIBUTE_WIND) return 0;
    if (b == ATTRIBUTE_PYRO) return 2;
    break;
  case ATTRIBUTE_WIND:
    if (b == ATTRIBUTE_EARTH) return 0;
    if (b == ATTRIBUTE_FOREST) return 2;
    break;
  case ATTRIBUTE_EARTH:
    if (b == ATTRIBUTE_THUNDER) return 0;
    if (b == ATTRIBUTE_WIND) return 2;
    break;
  case ATTRIBUTE_THUNDER:
    if (b == ATTRIBUTE_AQUA) return 0;
    if (b == ATTRIBUTE_EARTH) return 2;
    break;
  case ATTRIBUTE_AQUA:
    if (b == ATTRIBUTE_PYRO) return 0;
    if (b == ATTRIBUTE_THUNDER) return 2;
    break;
  default:
    break;
  }
  return 1;
}

LYN_REPLACE_CHECK(InitBoard);
void InitBoard__Replacement(void) {
  unsigned char i, j;

  ResetDelayedDuelEffects();
  Duel_ResetAttackRestrictions();
  ResetYataGarasuSkipDraw();
  ResetFenrirSkipDraw();
  ResetTimeSealSkipDraw();
  ResetRecklessGreedSkipDraw();
  ResetThousandEnergyState();
  ResetTrianglePowerState();
  ResetLimiterRemovalState();
  ResetUltimateOfferingTurnState();
  CourtOfJustice_ResetTurnState();
  ResetExecutorMakyuraTurnState();
  BlastHeldByATribute_ClearAllMarks();
  VengefulBogSpirit_ClearAllMarks();
  WallOfRevealingLight_ClearThreshold();
  WorldSuppression_ClearNegation();
  ResetDynamicEquips();
  ResetTheGrandJupiterEquipState();
  BigBangShot_ResetAllBoosts();
  ResetApophisLinks();
  ClearCostDown();
  ResetCustomFieldSpellState();
  ClearPendingSliferSummonPenalty();
  InitDuelZonePtrs(2);
  GraveyardExpand_Init();
  XyzOverlays_InitBoard();
  RemovedFromPlay_Init();
  SixCardHand_Init();
  ElementalHeroNecroshade_Reset();
  ElementalHeroNeosAlius_Reset();
  gAiSimInBatch = FALSE;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 5; j++)
      ClearZone(&gDuel.board[i][j]);
  for (i = 0; i < 2; i++)
    for (j = 0; j < 5; j++) {
      ClearZone(&gDuel.hands[i][j]);
      TryDrawingCard(i);
    }
  gDuel.field = gRuntimeConfig.duel_start_field < NUM_FIELDS
      ? gRuntimeConfig.duel_start_field
      : gDuelData.duelist.field;
  gDeferGraveyardDrawBattleResolve = FALSE;
  gPendingGraveyardDrawFixedDuelist = PENDING_GRAVEYARD_DRAW_NONE;
  gGraveyardSendWasFromField = FALSE;
  ClearFamiliarKnightBattleDestroyPending();
  ClearElementalHeroFlashBattleDestroyPending();
  ClearVampireBabyPending();
  ClearGhostKnightOfJackalPending();
  ClearMefistDiscardPending();
  ClearReaperDiscardPending();
  ClearSpiritReaperDiscardPending();
  ClearGuardianAngelJoanPending();
  ClearRoyalKnightPending();
  ClearElementalHeroSteamHealerPending();
  ClearElementalHeroFlameWingmanPending();
  ClearElementalHeroCoreBattledPending();
  ClearCyberBarrierDragonTurnState();
  ClearElementalHeroIceEdgeBattledPending();
  gElementalHeroCoreRevivePending = FALSE;
  ClearElementalHeroSunriseOptFlags();
  ClearElementalHeroSunriseDestroyPending();
  ClearElementalHeroBlazemanTurnState();
  ClearCyberneticFusionSupport();
  PowerBond_ClearState();
  ClearTheBigSaturnPending();
  ClearTheWickedEraserPending();
  ClearTheWickedAvatarLock();
  ClearTheSupremacySunState();
  ClearArchlordKristyaState();
  ClearElementalHeroTempestProtection();
  ClearElementalHeroWildedgeState();
  ClearChimeratechOverdragonState();
  ClearLesserFiendPending();
  ClearDarkMagicianOfChaosPending();
  ClearAirknightParshathDrawPending();
  ClearSasukeSamurai3DrawPending();
  ClearNeedleBurrowerPending();
  ClearHyperHammerheadPending();
  ClearNeoSpacianGrandMolePending();
  ClearLightningWarriorPending();
  gPendingNeoSpacianGlowMossDraw = FALSE;
  gPendingNeoSpacianTwinkleMossDraw = FALSE;
  gPendingReptilianneGorgonZeroAtk = FALSE;
  ClearDonZaloogPending();
  ClearRedDragonArchfiendPending();
  ClearReptilianneScyllaPending();
  ClearDesKangarooPending();
  ClearContinuousDestructionPunchPending();
  ClearAbsorbingKidFromTheSkyPending();
  ClearCoffinSellerPending();
  Yubel_ClearBattlePending();
  ClearDarkRoomPending();
  ClearFirePrincessPending();
  ElementalHeroAbsoluteZero_ResetPendingState();
  gSorlSkipDecrementAfterActivation = FALSE;
  for (i = 0; i < 2; i++) {
    gDuel.duelistbattleState[i].sorlTurns = 0;
    gDuel.duelistbattleState[i].defenseBlocked = 0;
    gDuel.duelistbattleState[i].graveyard = CARD_NONE;
    UnblockSummoning(i);
  }
  TimedDuel_ApplySetupIfActive();
  MechanicsTutorial_ApplySetupIfActive();
}

LYN_REPLACE_CHECK(PlayerTurnMain);
void PlayerTurnMain__Replacement(void) {
  if (DebugAiMode_IsBothSides() == TRUE) {
    AI_Main();
    DebugRuleset_TryEnforceMustPlayMonsterRule();
    if (IsDuelOver() == TRUE)
      return;
    DestroyKarateManAtEndOfTurn();
    ClearTheBigSaturnAtkBoostAtEndOfTurn();
    DestroyThousandEnergyMonstersAtEndOfTurn();
    DestroyTrianglePowerMonstersAtEndOfTurn();
    DestroyLimiterRemovalMonstersAtEndOfTurn();
    ResolveDelayedDuelEffectsAtTurnEnd(DUEL_PLAYER);
    UpdateDuelGfxExceptField();
    return;
  }

  gIsPlayerTurnOver = 0;
  UpdateDuelGfxExceptField();
  TryActivatingTurnEffects();
  if (IsDuelOver() == TRUE)
    return;
  TryActivatingPermanentEffects();
  if (IsDuelOver() == TRUE)
    return;
  InitButtonMaps();
  MechanicsTutorial_TryShowIntro();
  while (IsDuelOver() != TRUE && gIsPlayerTurnOver != TRUE) {
    unsigned char y = gDuelCursor.currentY;
    switch (ProcessInput__Replacement()) {
      case 1:
        MoveCursorUp();
        if (gDuelCursor.state == 4)
          RefreshPendingSasukeBattleTarget();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 2:
        MoveCursorDown();
        if (gDuelCursor.state == 4)
          RefreshPendingSasukeBattleTarget();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 3:
        MoveCursorLeft();
        if (gDuelCursor.state == 4)
          RefreshPendingSasukeBattleTarget();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 4:
        MoveCursorRight();
        if (gDuelCursor.state == 4)
          RefreshPendingSasukeBattleTarget();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 5:
        HandleAButtonAction();
        break;
      case 6:
        if (gRuntimeConfig.enable_removed_from_play_zone == TRUE) {
          Duel_RemovedFromPlayViewer_Open(DUEL_PLAYER);
          UpdateAllDuelGfx();
        } else {
          sub_8042F04();
          WaitForVBlank();
          sub_8041014();
        }
        break;
      case 7:
        if (gRuntimeConfig.enable_removed_from_play_zone == TRUE) {
          Duel_RemovedFromPlayViewer_Open(DUEL_OPPONENT);
          UpdateAllDuelGfx();
        } else if (!IsOpponentHandFieldScrollEnabled()) {
          sub_8044B2C();
          UpdateAllDuelGfx();
        } else {
          WaitForVBlank();
        }
        break;
      case 8:
        HandleBButtonAction();
        WaitForVBlank();
        break;
      case 9:
        DeclareLoser(0);
        break;
      case 10:
        DeclareLoser(1);
        break;
      default:
        WaitForVBlank();
        break;
    }
  }

  DebugRuleset_TryEnforceMustPlayMonsterRule();
  if (IsDuelOver() == TRUE)
    return;

  ResolveYubelEndPhaseEffectsAtTurnEnd();
  if (IsDuelOver() == TRUE)
    return;

  TryApplyRedDragonArchfiendEndPhaseEffect();
  if (IsDuelOver() == TRUE)
    return;

  if (gPickZoneState.validator != NULL)
    Duel_RunPickZoneInputLoop();
  if (IsDuelOver() == TRUE)
    return;

  DestroyKarateManAtEndOfTurn();
  ClearTheBigSaturnAtkBoostAtEndOfTurn();
  DestroyThousandEnergyMonstersAtEndOfTurn();
  DestroyTrianglePowerMonstersAtEndOfTurn();
  DestroyLimiterRemovalMonstersAtEndOfTurn();
  ResolveDelayedDuelEffectsAtTurnEnd(DUEL_PLAYER);
  UpdateDuelGfxExceptField();
}

LYN_REPLACE_CHECK(LockMonsterCardsInRow);
void LockMonsterCardsInRow__Replacement(unsigned char turnRow) {
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[turnRow][i]->id != CARD_NONE
        && (GetTypeGroup(gTurnZones[turnRow][i]->id) == TYPE_GROUP_MONSTER
            || EmbodimentOfApophisZoneIsMonsterForm(gTurnZones[turnRow][i])
            || OjamaTrioZoneIsMonsterForm(gTurnZones[turnRow][i])))
      gTurnZones[turnRow][i]->isLocked = TRUE;
  }

  if (turnRow == ACTIVE_DUELIST_HAND)
    TryUnlockHandForUltimateOfferingExtraSummon();
  if (turnRow == ACTIVE_DUELIST_HAND)
    TryUnlockHandForDoubleSummon();
  if (turnRow == ACTIVE_DUELIST_HAND)
    TryUnlockHandForCourtOfJusticeIgnition();
  if (turnRow == ACTIVE_DUELIST_HAND)
    TryUnlockHandForValhallaHallOfTheFallenIgnition();
}

void EnableDoubleSummonForTurn(void) {
  gDoubleSummonExtraSummonPending = TRUE;
  gDoubleSummonExtraSummonUsed = gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked;

  if (gDoubleSummonExtraSummonUsed)
    UnlockCardsInRow(ACTIVE_DUELIST_HAND);
}

static void TryUnlockHandForDoubleSummon(void) {
  if (!gDoubleSummonExtraSummonPending || gDoubleSummonExtraSummonUsed)
    return;

  gDoubleSummonExtraSummonUsed = TRUE;
  UnlockCardsInRow(ACTIVE_DUELIST_HAND);
}

LYN_REPLACE_CHECK(UnblockTurnSummoning);
void UnblockTurnSummoning__Replacement(unsigned char currPlayer) {
  if (gDuelType == DUEL_TYPE_LINK)
    BeginDuelBoardTurn();
  gTurnDuelistBattleState[currPlayer]->summoningBlocked = 0;
  gDoubleSummonExtraSummonPending = FALSE;
  gDoubleSummonExtraSummonUsed = FALSE;
  DebugRuleset_ResetTurnAttack();
  TheDarkDoor_ResetTurnAttack();
  VengefulBogSpirit_ClearAllMarks();
  WorldSuppression_ClearNegation();
}

LYN_REPLACE_CHECK(TryDisplaySorlTurnsRemainingText);
void TryDisplaySorlTurnsRemainingText__Replacement(void) {
  u8 turns = gDuel.duelistbattleState[WhoseTurn()].sorlTurns;

  if (turns == 0)
    return;
  if (FindActiveSorlZone() == NULL)
    return;

  Sorl_ShowTurnsRemainingText(turns);
}

LYN_REPLACE_CHECK(DecrementSorlTurns);
void DecrementSorlTurns__Replacement(unsigned char currPlayer) {
  struct DuelCard *sorlZone = FindActiveSorlZone();
  u8 blockedDuelist;
  u8 turns;

  (void)currPlayer;

  if (sorlZone == NULL) {
    gDuel.duelistbattleState[DUEL_PLAYER].sorlTurns = 0;
    gDuel.duelistbattleState[DUEL_OPPONENT].sorlTurns = 0;
    return;
  }

  blockedDuelist = GetSorlBlockedDuelistByZone(sorlZone);
  if (blockedDuelist >= 2)
    return;

  turns = gDuel.duelistbattleState[blockedDuelist].sorlTurns;
  if (turns == 0)
    return;

  turns--;
  gDuel.duelistbattleState[blockedDuelist].sorlTurns = turns;

  if (turns == 0) {
    ClearZoneAndSendMonToGraveyard(sorlZone,
        blockedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);
  }
}

LYN_REPLACE_CHECK(ClearZone);
void ClearZone__Replacement(struct DuelCard *zone) {
  TryApplySkullInvitationOnFieldLeave(zone);
  TryApplyCoffinSellerOnFieldLeave(zone);
  TryApplyNightmareWheelOnTargetLeave(zone);
  TryApplyFutureFusionOnMonsterLeave(zone);
  FutureFusion_OnZoneCleared(zone);
  OnCustomFieldSpellZoneCleared(zone);
  OnDynamicEquipZoneAboutToClear(zone);
  OnEmbodimentOfApophisZoneAboutToClear(zone);
  ClearRiryokuAtkDeltaForZone(zone);
  PowerBond_ClearAtkBonusForZone(zone);
  MirrorWall_OnZoneCleared(zone);
  ElementalHeroGreatTornado_OnZoneCleared(zone);
  TheWickedDreadroot_OnZoneCleared(zone);
  TheWickedEraser_OnZoneCleared(zone);
  TheWickedAvatar_OnZoneCleared(zone);
  ElementalHeroSunrise_OnZoneCleared(zone);
  Zeriel_OnZoneCleared(zone);
  Shatiel_OnZoneCleared(zone);
  SeraphimBlaster_OnZoneCleared(zone);
  ElementalHeroGaia_OnZoneCleared(zone);
  ElementalHeroAbsoluteZero_OnZoneCleared(zone);
  ElementalHeroBlazeman_OnZoneCleared(zone);
  ElementalHeroTheShining_OnZoneCleared(zone);

  if (zone->id == THE_GRAND_JUPITER)
    ClearTheGrandJupiterEquipsForJupiterZone(zone);
  else {
    u8 fixedRow;
    u8 fixedCol;

    if (Duel_FindFixedZone(zone, &fixedRow, &fixedCol)
        && (fixedRow == OPPONENT_BACKROW || fixedRow == PLAYER_BACKROW)
        && IsGrandJupiterEquipZone(fixedRow, fixedCol))
      ClearTheGrandJupiterEquipSlot(fixedRow, fixedCol);
  }

  if (zone->id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE) {
    u8 blockedDuelist = GetSorlBlockedDuelistByZone(zone);

    if (blockedDuelist < 2)
      gDuel.duelistbattleState[blockedDuelist].sorlTurns = 0;
  }

  zone->id = CARD_NONE;
  zone->isFaceUp = 0;
  zone->isLocked = 0;
  zone->isDefending = 0;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;
  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unk4 = 0;
  zone->willChangeSides = 0;
  ClearCopycatBoardStatsForZone(zone);
  ElementalHeroNeosAlius_ClearZone(zone);
  ClearGreatMajuGarzettBoardStatsForZone(zone);
  ClearMajuGarzettBoardStatsForZone(zone);
  ClearTheTyrantNeptuneBoardStatsForZone(zone);
  ClearChimeratechOverdragonBoardStatsForZone(zone);
  BlastHeldByATribute_ClearZoneMark(zone);
  VengefulBogSpirit_ClearZoneMark(zone);
  RecalculateAllDynamicEquips();
  SixCardHand_OnZoneCleared(zone);
  if (gUnk2023EA0.unk18 == 0 && !gHideEffectText)
    ResolveCoffinSellerBattleEffect();
}

LYN_REPLACE_CHECK(CopyCard);
void CopyCard__Replacement(struct DuelCard *dst, struct DuelCard *src)
{
  u8 checkSliferSummonPenalty = ShouldApplySliferSummonPenalty(dst, src);
  u8 markVengefulBogOnHandSummon = FALSE;
  u8 dstFixedRow;
  u8 dstFixedCol;

  if (dst->id == CARD_NONE && src->id != CARD_NONE
      && GetTypeGroup(src->id) == TYPE_GROUP_MONSTER
      && Duel_ZoneIsHandSlot(src)
      && Duel_FindFixedMonsterZone(dst, &dstFixedRow, &dstFixedCol)) {
    if (!KaiserColosseum_AllowsMonsterPlacement(dstFixedRow))
      return;
    markVengefulBogOnHandSummon = TRUE;
  }

  if (ShouldPayChainEnergyForHandToFieldCopy(dst, src)) {
    if (!TryPayChainEnergyCost())
      return;
  }

  if (ShouldSuppressSkullInvitationDamageOnCopy(dst, src))
    gSuppressSkullInvitationDamage = TRUE;

  dst->id = src->id;
  SetPermStage(dst, PermStage(src));
  ResetTempStage(dst);
  dst->unk4 = src->unk4;
  dst->isFaceUp = src->isFaceUp;
  dst->isLocked = src->isLocked;
  dst->isDefending = src->isDefending;
  dst->unkTwo = src->unkTwo;
  dst->unkThree = src->unkThree;
  dst->willChangeSides = src->willChangeSides;
  dst->effectExhausted = src->effectExhausted;
  dst->effectUsedThisTurn = src->effectUsedThisTurn;
  BlastHeldByATribute_TransferZoneMark(dst, src);
  VengefulBogSpirit_TransferZoneMark(dst, src);
  RecalculateAllDynamicEquips();

  if (checkSliferSummonPenalty)
    MaybeApplySliferSummonPenaltyAfterCopy(dst);

  if (dst->id != CARD_NONE && GetTypeGroup(dst->id) == TYPE_GROUP_MONSTER) {
    Duel_NotifyMonsterZoneChanged(dst);
    TryEnforceBerserkGorillaOnMonsterPlacement(dst);
    TryLevelLimitAreaBOnMonsterPlacement(dst);
    TryLevelLimitAreaAOnMonsterPlacement(dst);
    if (markVengefulBogOnHandSummon)
      TryVengefulBogSpiritOnMonsterPlacement(dst);
    TryRingOfDestructionOnMonsterPlacement(dst);
    TryAmazonessTigerOnMonsterPlacement(dst);
    TryElementalHeroGreatTornadoOnMonsterPlacement(dst);
    TryTheWickedDreadrootOnMonsterPlacement(dst);
    TryTheWickedEraserOnMonsterPlacement(dst);
    TryElementalHeroSunriseOnMonsterPlacement(dst);
    TryElementalHeroAbsoluteZeroOnMonsterPlacement(dst);
    /* Blazeman on-summon runs only from placement paths that update field gfx first. */
  }
}

s8 ComputeFinalStage(const struct DuelCard *zone)
{
  int stage;

  if (zone == NULL)
    return 0;

  stage = zone->permStage + zone->tempStage + GetDynamicEquipStageDelta(zone);

  stage = SplendidVenus_AdjustStage((s8)stage, zone->id);

  /* ponytail: Orichalcos debug — only check field spell ID */
  if (gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_SEAL_OF_ORICHALCOS)
    stage++;

  /* Full guarded check — commented out for debugging
  if (gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_SEAL_OF_ORICHALCOS
      && zone->id != CARD_NONE
      && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
      && gActiveFieldSpellController != FIELD_SPELL_CONTROLLER_NONE
      && GetDuelistForZone(zone) == gActiveFieldSpellController
      && !IsWorldSuppressionNegatingFieldSpell(SEAL_OF_ORICHALCOS))
    stage++;
  */

  if (stage > 127)
    stage = 127;
  if (stage < -128)
    stage = -128;

  return (s8)stage;
}

LYN_REPLACE_CHECK(GetFinalStage);
int GetFinalStage__Replacement(struct DuelCard *zone)
{
  gSetFinalStatZone = zone;
  /* Leave gSetFinalStatZone set for the paired SetFinalStat (battle damage, etc.). */
  return ComputeFinalStage(zone);
}

LYN_REPLACE_CHECK(CheckLoserFlags);
void CheckLoserFlags__Replacement(void)
{
  u8 actionId = sActionData.id;

  if (sActionData.flags & FLAG_LOSER_PLAYER)
    DeclareLoser(DUEL_PLAYER);
  if (sActionData.flags & FLAG_LOSER_OPPONENT)
    DeclareLoser(DUEL_OPPONENT);

  if (actionId == 9 && sActionData.opponentCardAtkOrLifePointsMod > 0)
    TryApplyDarkRoomAfterEffectDamage(DUEL_OPPONENT);
  else if (actionId == 8 && sActionData.playerCardAtkOrLifePointsMod > 0)
    TryApplyDarkRoomAfterEffectDamage(DUEL_PLAYER);
  else if (actionId == 7 && sActionData.playerCardAtkOrLifePointsMod > 0)
    TryApplyFirePrincessAfterLpGain(DUEL_PLAYER);
  else if (actionId == 10 && sActionData.opponentCardAtkOrLifePointsMod > 0)
    TryApplyFirePrincessAfterLpGain(DUEL_OPPONENT);
}

LYN_REPLACE_CHECK(UnlockCardsInRow);
void UnlockCardsInRow__Replacement(unsigned char turnRow)
{
  u8 i;

  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW) {
    ClearElementalHeroWildedgeState();
    ClearChimeratechOverdragonAttacksUsed();
    ClearElementalHeroSunriseOptFlags();
    ClearElementalHeroIceEdgeDirectAttackFlags();
    ClearElementalHeroBlazemanTurnState();
    ClearCyberneticFusionSupport();
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[turnRow][i];

    if (zone->id == CARD_NONE)
      continue;

    zone->effectUsedThisTurn = FALSE;

    if (OjamaTrioZoneIsMonsterForm(zone)) {
      zone->isLocked = TRUE;
      zone->isDefending = TRUE;
      continue;
    }

    zone->isLocked = FALSE;
  }
}
