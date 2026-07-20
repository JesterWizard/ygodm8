#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 sTrapTrickUsedThisTurn APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsNormalTrapExceptTrick(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == TRAP_TRICK)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  /* ponytail: no Continuous/Counter trap type split — treat all traps as Normal. */
  return TRUE;
}

static s8 FirstEmptyBackrow(void)
{
  return FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_BACKROW]);
}

APPEND_TEXT void EffectTRAP_TRICK(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 banishedId = CARD_NONE;
  u8 banishIdx = 0;
  u16 setId = CARD_NONE;
  u8 setIdx = 0;
  s8 empty;
  struct DuelCard *slot;

  Duel_ShowTrapResponseText(TRAP_TRICK, gTrapEffectData.originCardId);

  if (sTrapTrickUsedThisTurn) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  for (i = top; i < deckSize; i++) {
    if (IsNormalTrapExceptTrick(gDuelDecks[fixedDuelist].cards[i])) {
      banishedId = gDuelDecks[fixedDuelist].cards[i];
      banishIdx = i;
      break;
    }
  }

  if (banishedId == CARD_NONE) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, banishIdx, FALSE) != DUEL_ACTION_OK) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  /* Banish via GY push then banish top. */
  GraveyardExpand_PushTurn(INACTIVE_DUELIST, banishedId);
  Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);

  /* Find same name in deck to Set. */
  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;
  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == banishedId) {
      setId = banishedId;
      setIdx = i;
      break;
    }
  }

  empty = FirstEmptyBackrow();
  if (setId != CARD_NONE && empty >= 0) {
    if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, setIdx, FALSE) == DUEL_ACTION_OK) {
      slot = gTurnZones[INACTIVE_DUELIST_BACKROW][empty];
      slot->id = setId;
      slot->isFaceUp = FALSE;
      slot->isLocked = FALSE;
      /* ponytail: "can activate this turn" — leave unlocked. */
    }
  }

  sTrapTrickUsedThisTurn = TRUE;
  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  /* ponytail: only 1 Trap activate rest of turn + OPT reset need gates. */
}
