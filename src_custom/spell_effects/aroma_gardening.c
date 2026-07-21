#include "global.h"
#include "common-chax.h"
#include "aroma_gardening.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define AROMA_GARDENING_LP_GAIN 1000

static const char sAromaArchetypeName[] APPEND_RODATA = "Aroma";

static const u8 sAromaGardeningPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaArchetypeName);
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindFirstAromaInDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAromaMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 LoadMatchingAromaDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsAromaMonster(cardId))
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

static u16 PickAromaDeckCardId(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  DECKMENU_SAVE();

  menuCount = LoadMatchingAromaDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return CARD_NONE;
  }

  if (menuCount == 1 || fixedDuelist != DUEL_PLAYER || gHideEffectText) {
    cardId = gDuelDecks[fixedDuelist].cards[deckIndexMap[0]];
    DECKMENU_RESTORE();
    return cardId;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sAromaGardeningPickLabels,
                                         ARRAY_COUNT(sAromaGardeningPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  cardId = gDuelDecks[fixedDuelist].cards[deckIndexMap[gDeckMenu.currentPos]];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return cardId;
}

static u8 CanApplyAromaGardeningAttackDeclare(void)
{
  u8 defenderFixed = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 attackerFixed = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (Duel_FindBackrowCard(defenderFixed, AROMA_GARDENING, TRUE) == NULL)
    return FALSE;

  if (EffectOpt_IsUsed(AROMA_GARDENING))
    return FALSE;

  if (gDuelLifePoints[defenderFixed] >= gDuelLifePoints[attackerFixed])
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindFirstAromaInDeck(defenderFixed) != CARD_NONE;
}

void ApplyAromaGardeningAttackDeclare(void)
{
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!CanApplyAromaGardeningAttackDeclare())
    return;

  cardId = PickAromaDeckCardId(INACTIVE_DUELIST);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectText(AROMA_GARDENING);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(AROMA_GARDENING);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);
}

u8 Cond_AromaGardeningOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!IsAromaMonster(ev->cardId))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, AROMA_GARDENING, TRUE) != NULL;
}

enum DuelActionResult Op_AromaGardeningOnSummon(struct EffectCtx *ctx)
{
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  turnDuelist = TurnDuelistForFixed(ctx->event->controller);
  Duel_ShowEffectText(AROMA_GARDENING);
  return Duel_ChangeLp(turnDuelist, AROMA_GARDENING_LP_GAIN, TRUE);
}

static void AROMA_GARDENING_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AROMA_GARDENING);
}

APPEND_TEXT void EffectAROMA_GARDENING(void)
{
  if (Duel_TryResolveSpellThroughTraps(AROMA_GARDENING, AROMA_GARDENING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AROMA_GARDENING_SelfCheck(void)
{
  if (AROMA_GARDENING_LP_GAIN != 1000)
    while (1)
      ;
  if (!IsAromaMonster(AROMA_JAR))
    while (1)
      ;
  if (IsAromaMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
