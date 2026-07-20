#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
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

static u8 HandHasRoomForSearch(u8 turnDuelist)
{
  return FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

static u8 DeckHasElegantEgotist(u8 turnDuelist)
{
  return Duel_FindDeckCardIndex(turnDuelist, ELEGANT_EGOTIST) >= 0;
}

static s8 FindElegantEgotistGyIndex(u8 fixedDuelist)
{
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == ELEGANT_EGOTIST)
      return 0;
    return -1;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ELEGANT_EGOTIST)
      return (s8)i;
  }

  return -1;
}

static u8 GyHasElegantEgotist(u8 turnDuelist)
{
  return FindElegantEgotistGyIndex(FixedDuelistForTurnDuelist(turnDuelist)) >= 0;
}

static u8 CanActivateHystericSign(void)
{
  if (!HandHasRoomForSearch(ACTIVE_DUELIST))
    return FALSE;

  return DeckHasElegantEgotist(ACTIVE_DUELIST) || GyHasElegantEgotist(ACTIVE_DUELIST);
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for Deck, FALSE for GY. */
static u8 PlayerChoosesDeck(void)
{
  /* ponytail: no dedicated choice UI — A = Deck, B = GY.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u8 AddElegantEgotistFromDeck(void)
{
  return Duel_AddDeckCardToHand(ACTIVE_DUELIST, ELEGANT_EGOTIST, FALSE) == DUEL_ACTION_OK;
}

static u8 AddElegantEgotistFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  gyIndex = FindElegantEgotistGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != ELEGANT_EGOTIST)
      return FALSE;
    cardId = GetGraveCardAndClearGrave(ACTIVE_DUELIST);
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  if (cardId != ELEGANT_EGOTIST)
    return FALSE;

  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
                       cardId);
  return TRUE;
}

static void SearchElegantEgotist(void)
{
  u8 hasDeck = DeckHasElegantEgotist(ACTIVE_DUELIST);
  u8 hasGy = GyHasElegantEgotist(ACTIVE_DUELIST);
  u8 chooseDeck;

  if (!hasDeck && !hasGy)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasDeck && hasGy)
    chooseDeck = PlayerChoosesDeck();
  else if (hasDeck)
    chooseDeck = TRUE;
  else
    chooseDeck = FALSE;

  if (chooseDeck)
    AddElegantEgotistFromDeck();
  else
    AddElegantEgotistFromGy();
}

static void HYSTERIC_SIGN_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(HYSTERIC_SIGN);

  if (IsDuelOver() == TRUE || !CanActivateHystericSign())
    return;

  SearchElegantEgotist();

  /* Continuous: stay face-up on field after on-activate search. */
  if (spellZone != NULL && spellZone->id == HYSTERIC_SIGN)
    Duel_ActivateContinuousZone(spellZone);

  /* ponytail: End Phase "sent from hand/field this turn → add up to 3 different
   * Harpie cards from Deck" needs a GY/sent-this-turn + End Phase hook.
   * Ceiling: only on-activate Elegant Egotist search works; upgrade: turn_effect
   * or GY send tracker that opens a multi-pick Harpie deck search. */

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectHYSTERIC_SIGN(void)
{
  if (!CanActivateHystericSign()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(HYSTERIC_SIGN, HYSTERIC_SIGN_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HYSTERIC_SIGN_SelfCheck(void)
{
  if (ELEGANT_EGOTIST == CARD_NONE)
    while (1)
      ;
}
#endif
