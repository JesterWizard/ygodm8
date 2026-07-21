#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "shining_sarcophagus.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* Cards whose text mentions Shining Sarcophagus (manifest scan). */
static const u16 sShiningSarcophagusMentions[] APPEND_RODATA = {
  DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE,
  DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC,
  GANDORA_G_THE_DRAGON_OF_DESTRUCTION,
  DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE,
  DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS,
  SILENT_SWORDSMAN_ZERO,
};

static const u8 sSarcPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sShiningSarcophagusSearchUsed APPEND_DATA = {0};

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

static u8 IsShiningSarcophagusMention(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE || cardId == SHINING_SARCOPHAGUS)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sShiningSarcophagusMentions); i++) {
    if (cardId == sShiningSarcophagusMentions[i])
      return TRUE;
  }

  return FALSE;
}

static u8 LoadMentionDeckMenu(u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsShiningSarcophagusMention(cardId))
      continue;

    deckIndexOut[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static void AddDeckCardToHand(u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 empty;
  u16 cardId;
  u8 i;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (empty < 0)
    return;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  for (i = deckIndex; i > gDuelDecks[fixedDuelist].cardsDrawn; i--)
    gDuelDecks[fixedDuelist].cards[i] = gDuelDecks[fixedDuelist].cards[i - 1];
  gDuelDecks[fixedDuelist].cardsDrawn++;

  InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
}

static void TrySearchMentionOnActivate(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;

  if (sShiningSarcophagusSearchUsed)
    return;
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return;

  menuCount = LoadMentionDeckMenu(deckIndexMap);
  if (menuCount == 0)
    return;

  /* One Deck search when this continuous is activated (printed: Main Phase OPT). */
  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sSarcPickLabels, ARRAY_COUNT(sSarcPickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }
  DECKMENU_RESTORE();

  AddDeckCardToHand(deckIndexMap[pick]);
  sShiningSarcophagusSearchUsed = TRUE;
  UpdateDuelGfxExceptField();
}

static void SHINING_SARCOPHAGUS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SHINING_SARCOPHAGUS);

  TrySearchMentionOnActivate();
}

static u8 IsSpellHandCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

u8 Cond_ShiningSarcophagusOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 sarcController;
  u8 summonController;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return FALSE;

  ev = ctx->event;
  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (ev->controller > DUEL_OPPONENT)
    return FALSE;

  summonController = ev->controller;
  if (Duel_FindBackrowCard(DUEL_PLAYER, SHINING_SARCOPHAGUS, TRUE) != NULL)
    sarcController = DUEL_PLAYER;
  else if (Duel_FindBackrowCard(DUEL_OPPONENT, SHINING_SARCOPHAGUS, TRUE) != NULL)
    sarcController = DUEL_OPPONENT;
  else
    return FALSE;

  if (summonController == sarcController)
    return FALSE;

  /* Need a Spell in sarcophagus controller's hand to discard. */
  {
    u8 turn = Duel_TurnDuelistForFixedDuelist(sarcController);
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnHands[turn][i] != NULL && IsSpellHandCard(gTurnHands[turn][i]->id))
        return TRUE;
    }
  }

  return FALSE;
}

enum DuelActionResult Op_ShiningSarcophagusOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 sarcController;
  u8 turn;
  u8 i;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  if (Duel_FindBackrowCard(DUEL_PLAYER, SHINING_SARCOPHAGUS, TRUE) != NULL)
    sarcController = DUEL_PLAYER;
  else
    sarcController = DUEL_OPPONENT;

  turn = Duel_TurnDuelistForFixedDuelist(sarcController);
  if (Duel_DiscardFromHand(turn, 1, IsSpellHandCard, TRUE) != DUEL_ACTION_OK)
    return DUEL_ACTION_BLOCKED;

  Duel_ShowEffectText(SHINING_SARCOPHAGUS);
  Duel_DestroyZone(ev->zone, Duel_TurnDuelistForFixedDuelist(ev->controller), FALSE);
  return IsDuelOver() == TRUE ? DUEL_ACTION_DUEL_OVER : DUEL_ACTION_OK;
}

u8 ShiningSarcophagus_PreventsDestroy(const struct DuelCard *zone)
{
  /* Blocks all card-effect destroys (no destroy-source tag in Duel_DestroyZone). */
  return zone != NULL && zone->id == SHINING_SARCOPHAGUS && zone->isFaceUp;
}

APPEND_TEXT void EffectSHINING_SARCOPHAGUS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SHINING_SARCOPHAGUS, SHINING_SARCOPHAGUS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
