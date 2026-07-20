#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "custom_decks/custom_decks.h"
#include "duel.h"
#include "duel_main.h"
#include "expanded_graveyard.h"
#include "duel_status.h"
#include "guardian_treasure.h"
#include "jar_of_greed.h"
#include "six_card_hand.h"
#include "royal_decree.h"
#include "ojama_trio.h"
#include "robbin_goblin.h"
#include "call_of_the_haunted.h"
#include "robbin_zombie.h"
#include "secret_barrel.h"
#include "just_deserts.h"
#include "gift_of_the_mystical_elf.h"
#include "time_seal.h"
#include "reckless_greed.h"
#include "skull_invitation.h"
#include "self_destruct_button.h"
#include "blasting_the_ruins.h"
#include "curse_of_darkness.h"
#include "solar_ray.h"
#include "level_limit_area_a.h"
#include "angels_tear.h"
#include "yata_garasu.h"
#include "fenrir.h"
#include "life_points.h"
#include "text.h"
#include "summon_tribute.h"
#include "duel_attack_restrictions.h"
#include "vengeful_bog_spirit.h"
#include "world_suppression.h"
#include "timed_duel.h"
#include "mechanics_tutorial.h"
#include "the_wicked_avatar.h"

void sub_8041B38(void);
void sub_8041014(void);
void RunTextRenderTask(struct DuelTextbox *);
void OpponentTurnTextAndVoice__Replacement(void);
void HandleOutcome(void);

void UnblockTurnSummoning(unsigned char);
void BeginDuelBoardTurn(void);
void UpdateDuelZonePtrs(unsigned char);
void CheckWinConditionExodia(unsigned char);
void TryEvolveMothCards(void);
void PlayerTurnMain(void);
void AI_Main(void);
void FlipAtkPosCardsFaceUp(unsigned char);
void SwitchTurn(void);
void DecrementSorlTurns(unsigned char);
void UnlockCardsInRow(unsigned char);
void SetDuelType(unsigned char);
void ClearDuelDecks(void);
void InitDuelDeck(unsigned char, u16);
void ShuffleDuelDeck(unsigned char);
void InitBoard(void);
void sub_8041090(void);
void SetVBlankCallback(void (*)(void));
void LoadPalettes(void);
void UpdateDuelGfxExceptField(void);
void AdjustBackgroundBeforeTurnStart(unsigned char);
void sub_8041DF0(unsigned char);
void sub_8057808(void);
void sub_804078C(void);
void sub_8040FDC(void);
void ReturnMonstersToOwner(void);
void TryReturnSphereModeAtTurnEnd(void);
void TryDisplaySorlTurnsRemainingText(void);
void TryDrawingCard(u32);
u16 LfsrNextWord(void);

extern struct Duelist *gUnk8E00B30[];
extern struct DuelCard *gTurnZones[5][MAX_ZONES_IN_ROW];
extern u16 gNewButtons;

int GetCardsDrawn(u8);

#define DUEL_RETRY_YES_ROW_TILE 28
#define DUEL_RETRY_NO_ROW_TILE 56
#define DUEL_TEXTBOX_TILE_SELECTED 0x7281
#define DUEL_TEXTBOX_TILE_BLANK 0x4081

static const u8 sText_DuelRetryPrompt[] APPEND_RODATA = "Retry duel?#0  Yes#0  No";

static void WriteDuelTextboxTile(u16 tileCursor, u16 tile) {
  if (tileCursor % 2)
    sub_8020968(gBgVram.cbb0 + 0x88C0 + tileCursor / 2 * 128, tile, 0x101);
  else
    sub_8020968(gBgVram.cbb0 + 0x88A0 + tileCursor / 2 * 128, tile, 0x101);
}

static void HighlightDuelRetryOption(u8 selectYes) {
  WriteDuelTextboxTile(DUEL_RETRY_YES_ROW_TILE,
                       selectYes == TRUE ? DUEL_TEXTBOX_TILE_SELECTED : DUEL_TEXTBOX_TILE_BLANK);
  WriteDuelTextboxTile(DUEL_RETRY_NO_ROW_TILE,
                       selectYes == FALSE ? DUEL_TEXTBOX_TILE_SELECTED : DUEL_TEXTBOX_TILE_BLANK);
}

static void RestoreDuelPromptTextboxDisplay(void) {
  REG_WINOUT = 30;
  REG_WIN1H = 0x3ED;
  REG_WIN1V = 0x438D;
  *(vu8 *)(REG_BASE + 0x49) = 54;
  REG_BLDY = 7;
  REG_DISPCNT = DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON;
}

static void ShowDuelRetryPromptText(void) {
  struct DuelTextbox textbox;

  textbox.textCursor = 0;
  textbox.tileCursor = 0;
  textbox.mode = 0;
  textbox.textBuffer = (u8 *)sText_DuelRetryPrompt;
  textbox.blinkFrameCounter = 0;
  textbox.glyphOffset = 0;
  textbox.unk14 = 0;
  textbox.unk16 = 0;
  textbox.unk18 = 0;
  textbox.unk1A = 0;

  sub_8041B38();
  RunTextRenderTask(&textbox);
  RestoreDuelPromptTextboxDisplay();
  sub_8041014();
}

static void EnsureVBlankInterruptEnabled(void) {
  /* ponytail: Defensive re-enable of the VBlank IRQ before WaitForVBlank polls.
   * The WaitForVBlank loop (0x8008234-0x800823C) spins on a software flag that
   * the VBlank ISR sets via sub_8008208.  If the VBlank interrupt enable (IE bit 0)
   * got lost between matches — e.g. the ISR never restored it because a callback
   * or m4aSoundVSync() hung — the flag never fires and we black-screen forever.
   * Upgrade: if per-match IRQ routing is ever configurable, stash & restore the
   * full IE value instead of blindly setting bit 0. */
  REG_IME = 0;
  REG_IE |= 1;
  REG_IME = 1;
}

static bool8 PromptDuelRetry(void) {
  u8 selectYes = TRUE;
  u8 keepProcessing = TRUE;
  bool8 retry = FALSE;

  ShowDuelRetryPromptText();
  HighlightDuelRetryOption(selectYes);
  sub_8041014();

  while (keepProcessing) {
    if (gNewButtons & (DPAD_UP | DPAD_LEFT) && selectYes == FALSE) {
      selectYes = TRUE;
      PlayMusic(SFX_MOVE_CURSOR);
      HighlightDuelRetryOption(selectYes);
    }
    if (gNewButtons & (DPAD_DOWN | DPAD_RIGHT) && selectYes == TRUE) {
      selectYes = FALSE;
      PlayMusic(SFX_MOVE_CURSOR);
      HighlightDuelRetryOption(selectYes);
    }
    if (gNewButtons & A_BUTTON) {
      retry = selectYes;
      PlayMusic(SFX_SELECT);
      keepProcessing = FALSE;
    }
    if (gNewButtons & B_BUTTON) {
      retry = FALSE;
      PlayMusic(SFX_CANCEL);
      keepProcessing = FALSE;
    }

    EnsureVBlankInterruptEnabled();
    RestoreDuelPromptTextboxDisplay();
    WaitForVBlank();
    sub_8041014();
  }

  return retry;
}

static void InitDuelMetaDataForRetry(void) {
  u8 i;

  gDuelData.moneyReward = 0;
  gDuelData.duelMusic = 0;
  for (i = 0; i < 10; i++)
    gDuelData.unk14[i] = 0;
  gDuelData.capacityYield = 0;
  gDuelData.unk2A = 0;
  gDuelData.winner = DUEL_WINNER_OPPONENT;
  gDuelData.unk2c = 0;
  gDuelData.unk2d = 1;
  gDuelData.duelist = *gUnk8E00B30[0];
}

static void ResetIngameDuelForRetry(void) {
  u8 i;

  SetDuelType(0);
  InitDuelMetaDataForRetry();
  gDuelData.duelist = *gUnk8E00B30[gDuelData.opponent];
  gDuelData.winner = DUEL_WINNER_OPPONENT;
  gDuelData.unk2A = 1;
  gDuelData.duelMusic = gUnk8E00B30[gDuelData.opponent]->duelMusic;
  gDuelData.winMusic = gUnk8E00B30[gDuelData.opponent]->winMusic;
  gDuelData.lossMusic = gUnk8E00B30[gDuelData.opponent]->lossMusic;
  ClearDuelDecks();
  InitDuelDeck(DUEL_PLAYER, 0);
  InitDuelDeck(DUEL_OPPONENT, gDuelData.opponent);
  for (i = 0; i < 2; i++)
    ShuffleDuelDeck(i);
  if (!RandRangeU8(0, 1))
    gWhoseTurn = DUEL_PLAYER;
  else
    gWhoseTurn = DUEL_OPPONENT;
  if (TimedDuel_IsActive() == TRUE)
    gWhoseTurn = DUEL_PLAYER;
  if (MechanicsTutorial_IsActive() == TRUE)
    gWhoseTurn = DUEL_PLAYER;
  InitBoard();
  InitDuelLifePoints();
  InitDuelistStatus();
  gHideEffectText = 0;
  sub_8041090();
  PlayMusic(gDuelData.duelMusic);
}



static void FadeDuelToBlack(void) {
  u16 i, j;
  struct PlttData *pltt;

  EnsureVBlankInterruptEnabled();

  for (i = 0; i < 32; i++) {
    for (j = 0; j < 512; j++) {
      pltt = (struct PlttData *)&gPaletteBuffer[j];
      if (pltt->r)
        pltt->r--;
      if (pltt->g)
        pltt->g--;
      if (pltt->b)
        pltt->b--;
    }
    SetVBlankCallback(LoadPalettes);
    EnsureVBlankInterruptEnabled();
    WaitForVBlank();
  }
  /* ponytail: Clear residual display hardware state so nothing leaks between
   * matches.  MosaicEffect leaves REG_MOSAIC=0x0F0F and BGCNT mosaic flags on
   * BG0/BG1/BG3; the duel blend (0xD4) is never explicitly cleared on the loss
   * path.  The overworld may mask these, but a fresh match needs a clean slate.
   * Upgrade: if per-match BLDCNT/MOSAIC values are ever configurable, move
   * these to the beginning of ResetIngameDuelForRetry instead. */
  REG_BLDCNT = 0;
  REG_BLDY = 0;
  REG_MOSAIC = 0;
}

static void AdvanceDuelRandomState(void) {
  LfsrNextWord();
}

static void ShowDuelLossMessages(void) {
  struct DuelText duelText;

  if (!gDuelLifePoints[DUEL_PLAYER]) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_PLAYER_OUT_OF_LP;
    DisplayDuelText(&duelText);
  } else if (NumCardsInDeck(DUEL_PLAYER) < GetCardsDrawn(DUEL_PLAYER)) {
    FadeOutMusic(4);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_PLAYER_DECK_OUT;
    DisplayDuelText(&duelText);
  }
  if (gDuelData.unk2d) {
    PlayMusic(gDuelData.lossMusic);
    ResetDuelTextData(&duelText);
    duelText.textId = DUEL_TEXT_DUEL_LOSS;
    DisplayDuelText(&duelText);
  }
}

static void ApplyDuelLossPenalties(void) {
  if (gAnte != CARD_NONE)
    RemoveCardQtyFromTrunk(gAnte, 1);
  if (gDuelType == DUEL_TYPE_INGAME)
    CapLifePointsAfterDuel();
  CustomDecks_ClearPendingCardShopDuel();
}

static bool8 RunDuelTurnLoop(void) {
  struct DuelText duelText;

  while (1) {
    unsigned char turn;

    BeginDuelBoardTurn();
    turn = WhoseTurn();

    if (gRuntimeConfig.expand_graveyard == TRUE)
      GraveyardExpand_SyncFromTurnStart();
    UpdateDuelGfxExceptField();
    if (turn == DUEL_PLAYER)
      AdjustBackgroundBeforeTurnStart(gDuelCursor.currentY);
    else
      AdjustBackgroundBeforeTurnStart(1);
    sub_8057808();
    sub_804078C();
    WaitForVBlank();
    sub_8040FDC();
    ResetDuelTextData(&duelText);
    if (turn == DUEL_PLAYER) {
      duelText.textId = DUEL_TEXT_PLAYER_TURN;
      DisplayDuelText(&duelText);
    } else {
      OpponentTurnTextAndVoice__Replacement();
    }
    UnblockTurnSummoning(ACTIVE_DUELIST);
    ResetNumTributes();
    ClearPendingTributeSummonCardId();
    UpdateDuelZonePtrs(turn);
    Duel_CheckLevelLimitAreaBAfterFieldChange();
    Duel_CheckLevelLimitAreaAAfterFieldChange();
    Duel_RefreshAttackRestrictions();
    if (!IsRoyalDecreeActiveOnField()) {
    TryActivateJarOfGreedOnOpponentTurnStart();
    TryActivateOjamaTrioOnOpponentTurnStart();
    TryActivateRobbinGoblinOnOpponentTurnStart();
    TryActivateRobbinZombieOnOpponentTurnStart();
    TryActivateCallOfTheHauntedOnOpponentTurnStart();
    TryActivateSecretBarrelOnOpponentTurnStart();
    TryActivateJustDesertsOnOpponentTurnStart();
    TryActivateGiftOfTheMysticalElfOnOpponentTurnStart();
    TryActivateTimeSealOnOpponentTurnStart();
    TryActivateRecklessGreedOnOpponentTurnStart();
    TryActivateSkullInvitationOnOpponentTurnStart();
    TryActivateSelfDestructButtonOnOpponentTurnStart();
    TryActivateBlastingTheRuinsOnOpponentTurnStart();
    TryActivateCurseOfDarknessOnOpponentTurnStart();
    TryActivateSolarRayOnOpponentTurnStart();
    TryActivateLevelLimitAreaAOnOpponentTurnStart();
    TryActivateAngelsTearOnOpponentTurnStart();
    }
    if (IsDuelOver() == TRUE)
      return TRUE;
    if (ShouldSkipDrawPhaseForYataGarasu(turn)) {
      ConsumeYataGarasuSkipDraw(turn);
      if (!gHideEffectText) {
        gCardEffectTextData.cardId = YATA_GARASU;
        ActivateCardEffectText();
      }
    } else if (ShouldSkipDrawPhaseForFenrir(turn)) {
      ConsumeFenrirSkipDraw(turn);
      if (!gHideEffectText)
        Duel_ShowEffectText(FENRIR);
    } else if (ShouldSkipDrawPhaseForTimeSeal(turn)) {
      ConsumeTimeSealSkipDraw(turn);
    } else if (ShouldSkipDrawPhaseForRecklessGreed(turn)) {
      ConsumeRecklessGreedSkipDraw(turn);
    } else if (TimedDuel_ShouldSkipDrawPhase(turn)) {
      /* ponytail: board and hand are pre-seeded; skip the draw phase. */
    } else if (MechanicsTutorial_ShouldSkipDrawPhase(turn)) {
      /* ponytail: board and hand are pre-seeded; skip the draw phase. */
    } else if (SixCardHand_HasDrawRoom(turn)
               || NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_HAND]) > 0) {
      PerformGuardianTreasureDrawPhaseDraws(turn);
      if (IsDuelOver() == TRUE)
        return TRUE;
      PlayMusic(SFX_DRAW_CARD);
      if (turn == DUEL_PLAYER && gRuntimeConfig.move_cursor_to_hand_on_draw == TRUE) {
        gDuelCursor.currentY = PLAYER_HAND;
        gDuelCursor.destY = PLAYER_HAND;
        gDuelCursor.currentX = 0;
        gDuelCursor.destX = 0;
        sub_8041DF0(PLAYER_HAND);
      }
    }
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(turn);
    if (IsDuelOver() == TRUE)
      return TRUE;
    TryDisplaySorlTurnsRemainingText();
    TryEvolveMothCards();
    if (turn == DUEL_PLAYER)
      PlayerTurnMain();
    else
      AI_Main();
    if (IsDuelOver() == TRUE)
      return TRUE;
    if (TimedDuel_IsActive() == TRUE && turn == DUEL_PLAYER)
      TimedDuel_OnPlayerTurnEnded();
    if (IsDuelOver() == TRUE)
      return TRUE;
    if (TimedDuel_IsActive() == TRUE) {
      const struct TimedDuelLayout *layout;

      layout = TimedDuel_GetActiveLayout();
      /* Timer mode: one player turn then exit. Turn-limit mode: keep going while turns remain. */
      if (TimedDuel_UsesTurnLimit(layout) != TRUE || TimedDuel_HasTurnsRemaining() != TRUE)
        return TRUE;
      continue;
    }
    TryReturnSphereModeAtTurnEnd();
    ExpandedHand_EnforceSizeLimit(turn);
    FlipAtkPosCardsFaceUp(2);
    EndFirstTurnAttackBan();
    SwitchTurn();
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked)
      gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked = 0;
    Sorl_TryDecrementAfterTurnEnd();
    TheWickedAvatar_TryDecrementLockAtTurnEnd();
    UnlockCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);
    UnlockCardsInRow(ACTIVE_DUELIST_HAND);
    VengefulBogSpirit_ClearAllMarks();
    WorldSuppression_ClearNegation();
  }
}

static bool8 TryRetryDuelAfterDefeat(void) {
  if (gRuntimeConfig.offer_duel_retry_after_defeat != TRUE)
    return FALSE;

  ShowDuelLossMessages();
  if (PromptDuelRetry() != TRUE)
    return FALSE;

  FadeDuelToBlack();
  AdvanceDuelRandomState();
  ResetIngameDuelForRetry();
  return TRUE;
}

static void FinishDuel(bool8 playerLostWithRetryOffer) {
  if (gDuelistStatus[DUEL_OPPONENT] == DUELIST_STATUS_DEFEAT)
    gDuelData.winner = DUEL_WINNER_PLAYER;
  else
    gDuelData.winner = DUEL_WINNER_OPPONENT;

  if (gDuelData.winner == DUEL_WINNER_PLAYER) {
    HandleOutcome();
    FadeOutMusic(2);
    FadeDuelToBlack();
    return;
  }

  if (playerLostWithRetryOffer) {
    ApplyDuelLossPenalties();
    FadeOutMusic(2);
    FadeDuelToBlack();
    return;
  }

  HandleOutcome();
  FadeOutMusic(2);
  FadeDuelToBlack();
}

LYN_REPLACE_CHECK(DisplayDuelText);
void DisplayDuelText__Replacement(struct DuelText *arg0) {
  if (arg0->textId == 0xFF)
    return;

  sub_8041C94(gDuelTextStrings[arg0->textId], arg0->unk0, arg0->unk2, arg0->rewardAmount, 0);
}

LYN_REPLACE_CHECK(DuelMain);
void DuelMain__Replacement(void) {
  bool8 retryDuel;
  bool8 fadedIn = FALSE;
  bool8 skipInit = FALSE;

  do {
    retryDuel = FALSE;
    if (fadedIn == FALSE) {
      EnsureVBlankInterruptEnabled();
      MosaicEffect();
      fadedIn = TRUE;
    }
    if (skipInit == FALSE)
      ResetIngameDuelForRetry();
    else
      skipInit = FALSE;

    if (RunDuelTurnLoop() != TRUE)
      continue;

    if (gDuelistStatus[DUEL_OPPONENT] == DUELIST_STATUS_DEFEAT)
      gDuelData.winner = DUEL_WINNER_PLAYER;
    else
      gDuelData.winner = DUEL_WINNER_OPPONENT;

    if (gDuelData.winner == DUEL_WINNER_OPPONENT
        && (TimedDuel_IsActive() == TRUE
            || gRuntimeConfig.offer_duel_retry_after_defeat == TRUE)) {
      retryDuel = TryRetryDuelAfterDefeat();
      if (retryDuel == TRUE) {
        fadedIn = TRUE;
        skipInit = TRUE;
        continue;
      }
      FinishDuel(TimedDuel_IsActive() == TRUE ? FALSE : TRUE);
      return;
    }

    FinishDuel(FALSE);
  } while (retryDuel == TRUE);
}
