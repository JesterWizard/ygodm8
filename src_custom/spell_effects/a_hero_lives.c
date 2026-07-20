#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_economics.h"
#include "spell_effects.h"

#define A_HERO_LIVES_MAX_LEVEL 4

void UpdateDuelGfxExceptField(void);

static const u8 sAHeroLivesPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsFaceUpMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (MonsterIsFaceUp(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]))
      return TRUE;
  }

  return FALSE;
}

static u8 IsAHeroLivesSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_IsElementalHeroCard(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= A_HERO_LIVES_MAX_LEVEL;
}

static u16 ActiveDuelistHalfLp(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] / 2;

  return gDuelLifePoints[DUEL_OPPONENT] / 2;
}

static s16 FindFirstEligibleDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsAHeroLivesSummonTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

u8 CanActivateA_HERO_LIVES(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (ControlsFaceUpMonster())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindFirstEligibleDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 LoadEligibleDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsAHeroLivesSummonTarget(cardId))
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

static u8 PickEligibleDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleDeckMenu(turnDuelist, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return 0xFF;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    deckIndex = deckIndexMap[0];
    DECKMENU_RESTORE();
    return deckIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sAHeroLivesPickLabels, ARRAY_COUNT(sAHeroLivesPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static enum DuelActionResult SpecialSummonDeckCardAtIndex(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsAHeroLivesSummonTarget(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void A_HERO_LIVES_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 halfLp;
  u8 deckIndex;

  Duel_ShowEffectText(A_HERO_LIVES);
  if (IsDuelOver() == TRUE || !CanActivateA_HERO_LIVES())
    return;

  if (!IsSpellEconomicsActiveForActiveDuelist()) {
    halfLp = ActiveDuelistHalfLp();
    if (halfLp > 0
        && Duel_ChangeLp(ACTIVE_DUELIST, -(s32)halfLp, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (ControlsFaceUpMonster()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0
      || FindFirstEligibleDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickEligibleDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF)
    return;

  if (SpecialSummonDeckCardAtIndex(ACTIVE_DUELIST, deckIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectA_HERO_LIVES(void)
{
  u16 halfLp = ActiveDuelistHalfLp();

  if (!CanActivateA_HERO_LIVES()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(A_HERO_LIVES, halfLp, A_HERO_LIVES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void A_HERO_LIVES_SelfCheck(void)
{
  if (!IsAHeroLivesSummonTarget(ELEMENTAL_HERO_SPARKMAN))
    while (1)
      ;
  if (IsAHeroLivesSummonTarget(ELEMENTAL_HERO_NEOS))
    while (1)
      ;
  if (IsAHeroLivesSummonTarget(ELEMENTAL_HERO_FLAME_WINGMAN))
    while (1)
      ;
}
#endif
