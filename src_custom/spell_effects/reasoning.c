#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern int NumCardsInDeck(unsigned char);
extern u16 gNewButtons;
extern u16 gPressedButtons;

#define REASONING_MIN_LEVEL 1
#define REASONING_MAX_LEVEL 12

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

/* Normal Summonable/Set: Normal/Effect monsters (not Fusion/Ritual/etc.). */
static u8 IsNormalSummonableMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == COLOR_NORMAL || gCardInfo.color == COLOR_EFFECT;
}

static u8 DeckHasRemainingCards(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  return gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist);
}

u8 CanActivateREASONING(void)
{
  return DeckHasRemainingCards();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Opponent declares Level 1–12. Human: Left/Right cycle, A confirm. */
static u8 PlayerDeclareLevel(void)
{
  u8 level = 4;

  /* ponytail: no Level-declare UI — D-Pad cycles, A confirms (unlabeled).
   * Ceiling: no on-screen Level readout; upgrade: effect-text Level picker. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & DPAD_LEFT) {
      PlayMusic(SFX_SELECT);
      if (level <= REASONING_MIN_LEVEL)
        level = REASONING_MAX_LEVEL;
      else
        level--;
    } else if (gNewButtons & DPAD_RIGHT) {
      PlayMusic(SFX_SELECT);
      if (level >= REASONING_MAX_LEVEL)
        level = REASONING_MIN_LEVEL;
      else
        level++;
    } else if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return level;
    }

    WaitForVBlank();
  }
}

static u8 OpponentDeclaresLevel(void)
{
  /* Activator is ACTIVE; opponent declares. */
  if (WhoseTurn() == DUEL_PLAYER) {
    /* AI opponent: random Level. */
    return RandRangeU8(REASONING_MIN_LEVEL, REASONING_MAX_LEVEL);
  }

  /* Player is the opponent of the AI activator. */
  if (!gHideEffectText)
    return PlayerDeclareLevel();

  return RandRangeU8(REASONING_MIN_LEVEL, REASONING_MAX_LEVEL);
}

/*
 * Excavate until Normal Summonable. If Level matches declared → all to GY.
 * Else Special Summon the match and send the rest (already milled) to GY.
 */
static enum DuelActionResult ExcavateReasoning(u8 declaredLevel)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 foundId = CARD_NONE;
  u8 foundLevel = 0;

  while (gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist)) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];

    gDuelDecks[fixedDuelist].cardsDrawn++;

    if (IsNormalSummonableMonster(cardId)) {
      foundId = cardId;
      SetCardInfo(cardId);
      foundLevel = gCardInfo.level;
      break;
    }

    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  }

  if (foundId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  if (foundLevel == declaredLevel) {
    /* Match: send excavated monster to GY too (no Special Summon). */
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, foundId);
    return DUEL_ACTION_OK;
  }

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, foundId);
    return DUEL_ACTION_BLOCKED;
  }

  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, foundId, opts);
}

static void DestroyReasoningSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == REASONING)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void REASONING_ResolveBody(void)
{
  u8 declaredLevel;

  Duel_ShowEffectText(REASONING);

  if (IsDuelOver() == TRUE || !CanActivateREASONING())
    return;

  declaredLevel = OpponentDeclaresLevel();
  ExcavateReasoning(declaredLevel);
  DestroyReasoningSpellZone();
}

APPEND_TEXT void EffectREASONING(void)
{
  if (!CanActivateREASONING()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(REASONING, REASONING_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void REASONING_SelfCheck(void)
{
  if (!IsNormalSummonableMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsNormalSummonableMonster(POLYMERIZATION))
    while (1)
      ;
  if (REASONING_MIN_LEVEL != 1 || REASONING_MAX_LEVEL != 12)
    while (1)
      ;
}
#endif
