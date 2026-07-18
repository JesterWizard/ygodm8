#include "global.h"
#include "configs/runtime.h"
#include "mechanics_tutorial.h"
#include "debug_menu_mechanics_layouts.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "duel.h"
#include "duel_main.h"
#include "duel_status.h"
#include "duel_voice.h"
#include "expanded_graveyard.h"
#include "overworld.h"

#define MECHANICS_TUTORIAL_ENTRY(layoutSym, opponent, titleSym, introSym, outroSym, winCard) \
  { (opponent), (titleSym), &(layoutSym), (introSym), (outroSym), (winCard) },

extern void ClearZone(struct DuelCard *zone);
extern void sub_8041C94(u8 *textPtr, u16, u16, u16, u16);
extern void DeclareLoser(unsigned char);
extern void UpdateDuelGfxExceptField(void);

#include "debug/debug_menu_mechanics_scripts.inc"

static const struct MechanicsTutorialEntry sMechanicsTutorials[] APPEND_RODATA = {
#include "debug/debug_menu_mechanics_table.inc"
};

#undef MECHANICS_TUTORIAL_ENTRY

static const struct MechanicsTutorialEntry *MechanicsTutorial_EntryForIndex(u8 index) {
  if (index >= ARRAY_COUNT(sMechanicsTutorials))
    return NULL;
  return &sMechanicsTutorials[index];
}

u8 MechanicsTutorial_GetCount(void) {
  return ARRAY_COUNT(sMechanicsTutorials);
}

const struct MechanicsTutorialEntry *MechanicsTutorial_GetEntry(u8 index) {
  return MechanicsTutorial_EntryForIndex(index);
}

const struct MechanicsTutorialEntry *MechanicsTutorial_GetActiveEntry(void) {
  if (gMechanicsTutorialActiveId == 0)
    return NULL;
  return MechanicsTutorial_EntryForIndex(gMechanicsTutorialActiveId - 1);
}

const struct TimedDuelLayout *MechanicsTutorial_GetActiveLayout(void) {
  const struct MechanicsTutorialEntry *entry;

  entry = MechanicsTutorial_GetActiveEntry();
  if (entry == NULL)
    return NULL;
  return entry->layout;
}

void MechanicsTutorial_FormatMenuTitle(u8 index, u8 *out) {
  const struct MechanicsTutorialEntry *entry;
  u8 i;

  entry = MechanicsTutorial_EntryForIndex(index);
  if (entry == NULL || entry->title == NULL) {
    out[0] = '\0';
    return;
  }
  for (i = 0; i < 15 && entry->title[i] != '\0'; i++)
    out[i] = entry->title[i];
  out[i] = '\0';
}

u8 MechanicsTutorial_IsActive(void) {
  return gMechanicsTutorialActiveId != 0;
}

static void MechanicsTutorial_PlayLines(const struct MechanicsTutorialLine *lines) {
  u8 i;
  u8 loadedPortrait = 0xFF;

  if (lines == NULL)
    return;
  for (i = 0; lines[i].text != NULL; i++) {
    /* Mini-cards stay on screen (only OAM 102 hidden for portrait VRAM clash).
     * Textbox end wipes OAM (and may clobber portrait VRAM) — full Show restores
     * between same-speaker pages; Place only when tiles are still warm. */
    if (lines[i].portraitId != PORTRAIT_NONE) {
      if (lines[i].portraitId != loadedPortrait) {
        Duel_ShowPortraitForTextbox(lines[i].portraitId, FALSE);
        loadedPortrait = lines[i].portraitId;
      } else {
        Duel_PlacePortraitForTextbox(lines[i].portraitId, FALSE);
      }
    }
    sub_8041C94((u8 *)lines[i].text, 0, 0, 0, 0);
    loadedPortrait = 0xFF; /* VRAM may be gone after UpdateDuelGfxExceptField */
    if (lines[i + 1].text != NULL
        && lines[i + 1].portraitId == lines[i].portraitId
        && lines[i].portraitId != PORTRAIT_NONE) {
      Duel_ShowPortraitForTextbox(lines[i].portraitId, FALSE);
      loadedPortrait = lines[i].portraitId;
    }
  }
}

static void MechanicsTutorial_ApplyCardSlot(struct DuelCard *slot,
                                           const struct TimedDuelCardSlot *spec) {
  ClearZone(slot);
  if (spec->cardId == CARD_NONE)
    return;
  slot->id = spec->cardId;
  slot->isFaceUp = spec->faceUp;
  slot->isDefending = spec->defending;
  slot->permStage = spec->permStage;
}

static void MechanicsTutorial_ApplyGraveyardStacks(const struct TimedDuelLayout *layout) {
  u8 duelist;

  if (GraveyardExpand_IsEnabled() == TRUE) {
    GraveyardExpand_LoadStacks((const u16 *)layout->graveyard);
    GraveyardExpand_SyncAllLegacyTops();
    GraveyardExpand_RefreshDisplay();
    return;
  }

  for (duelist = 0; duelist < 2; duelist++) {
    u8 i;
    u16 top = CARD_NONE;

    for (i = 0; i < TIMED_DUEL_GRAVEYARD_SLOTS; i++) {
      if (layout->graveyard[duelist][i] == CARD_NONE)
        break;
      top = layout->graveyard[duelist][i];
    }
    gDuel.duelistbattleState[duelist].graveyard = top;
  }
}

void MechanicsTutorial_ApplySetupIfActive(void) {
  const struct MechanicsTutorialEntry *entry;
  const struct TimedDuelLayout *layout;
  u8 row;
  u8 col;

  entry = MechanicsTutorial_GetActiveEntry();
  if (entry == NULL || entry->layout == NULL)
    return;

  layout = entry->layout;
  gWhoseTurn = DUEL_PLAYER;
  gDuel.field = layout->field < NUM_FIELDS ? layout->field : FIELD_NONE;

  for (row = 0; row < TIMED_DUEL_BOARD_ROWS; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      MechanicsTutorial_ApplyCardSlot(&gDuel.board[row][col], &layout->board[row][col]);
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    MechanicsTutorial_ApplyCardSlot(&gDuel.hands[DUEL_PLAYER][col],
                                    &layout->hands[DUEL_PLAYER][col]);
    MechanicsTutorial_ApplyCardSlot(&gDuel.hands[DUEL_OPPONENT][col],
                                    &layout->hands[DUEL_OPPONENT][col]);
  }

  MechanicsTutorial_ApplyGraveyardStacks(layout);
  MechanicsTutorial_ApplyLifePointsIfActive();
}

void MechanicsTutorial_ApplyLifePointsIfActive(void) {
  const struct TimedDuelLayout *layout;

  if (!MechanicsTutorial_IsActive())
    return;
  layout = MechanicsTutorial_GetActiveLayout();
  if (layout == NULL)
    return;

  gDuelLifePoints[DUEL_PLAYER] = layout->playerLp;
  gDuelLifePoints[DUEL_OPPONENT] = layout->opponentLp;
  gUnk2023EA0.unk0[DUEL_PLAYER].initialLifePoints = layout->playerLp;
  gUnk2023EA0.unk0[DUEL_PLAYER].lifePointsAfterDamage = layout->playerLp;
  gUnk2023EA0.unk0[DUEL_OPPONENT].initialLifePoints = layout->opponentLp;
  gUnk2023EA0.unk0[DUEL_OPPONENT].lifePointsAfterDamage = layout->opponentLp;
}

u8 MechanicsTutorial_ShouldSkipDrawPhase(u8 turnDuelist) {
  if (!MechanicsTutorial_IsActive())
    return FALSE;
  return turnDuelist == DUEL_PLAYER;
}

void MechanicsTutorial_TryShowIntro(void) {
  const struct MechanicsTutorialEntry *entry;

  if (!MechanicsTutorial_IsActive())
    return;
  if (gMechanicsTutorialIntroDone != 0)
    return;

  gMechanicsTutorialIntroDone = 1;
  entry = MechanicsTutorial_GetActiveEntry();
  if (entry == NULL)
    return;
  MechanicsTutorial_PlayLines(entry->intro);
}

void MechanicsTutorial_NoteSummonAnim(u16 cardId) {
  if (!MechanicsTutorial_IsActive())
    return;
  gMechanicsTutorialPendingCardId = cardId;
}

void MechanicsTutorial_OnSummonAnimFinished(void) {
  const struct MechanicsTutorialEntry *entry;
  u16 cardId;

  if (!MechanicsTutorial_IsActive())
    return;

  cardId = gMechanicsTutorialPendingCardId;
  gMechanicsTutorialPendingCardId = CARD_NONE;
  if (cardId == CARD_NONE)
    return;

  entry = MechanicsTutorial_GetActiveEntry();
  if (entry == NULL || entry->winOnSummonCardId == CARD_NONE)
    return;
  if (cardId != entry->winOnSummonCardId)
    return;

  /* Cut-in clears OAM; rebuild mini-cards before the next textbox. */
  UpdateDuelGfxExceptField();
  MechanicsTutorial_PlayLines(entry->outro);
  DeclareLoser(DUEL_OPPONENT);
}

void MechanicsTutorial_HandleWin(void) {
  const struct MechanicsTutorialEntry *entry;

  entry = MechanicsTutorial_GetActiveEntry();
  /* Summon-complete path already played outro before DeclareLoser. */
  if (entry != NULL && entry->winOnSummonCardId == CARD_NONE)
    MechanicsTutorial_PlayLines(entry->outro);
  MechanicsTutorial_OnDuelEnd();
}

void MechanicsTutorial_OnDuelEnd(void) {
  gMechanicsTutorialActiveId = 0;
  gMechanicsTutorialIntroDone = 0;
  gMechanicsTutorialPendingCardId = CARD_NONE;
}

void MechanicsTutorial_RunAtIndex(u8 index) {
  const struct MechanicsTutorialEntry *entry;
  u8 savedSummonAnims;

  entry = MechanicsTutorial_GetEntry(index);
  if (entry == NULL)
    return;

  gMechanicsTutorialActiveId = index + 1;
  gMechanicsTutorialIntroDone = 0;
  gMechanicsTutorialPendingCardId = CARD_NONE;
  gDuelData.opponent = entry->opponentId;
  gDuelData.unk2A = 0;
  gDuelData.moneyReward = 0;
  gDuelData.capacityYield = 0;

  savedSummonAnims = gRuntimeConfig.enable_summon_animations;
  gRuntimeConfig.enable_summon_animations = TRUE;
  DuelMain();
  gRuntimeConfig.enable_summon_animations = savedSummonAnims;
  MechanicsTutorial_OnDuelEnd();
}
