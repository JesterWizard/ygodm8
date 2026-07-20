#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

/* ponytail: OPT flags never clear without a turn-end hook outside this file.
 * Ceiling: once per duel after first field use; upgrade: turn_effect_hooks
 * End Phase / turn-start → sEnShuffleFieldUsedThisTurn = 0. */
static u8 sEnShuffleFieldUsedThisTurn APPEND_DATA = {0};
static u16 sEnShuffleExcludeId APPEND_DATA = {0};

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sEnShufflePickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static u8 IsElementalHeroOrNeoSpacian(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_IsElementalHeroCard(cardId))
    return TRUE;

  return IsNeoSpacianMonster(cardId);
}

static u8 IsValidEnShuffleFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsElementalHeroOrNeoSpacian(zone->id);
}

static u8 HasEnShuffleFieldTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidEnShuffleFieldTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasDifferentNameSummon(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsElementalHeroOrNeoSpacian(cardId))
      continue;
    if (cardId == excludeId)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    return TRUE;
  }

  return FALSE;
}

static u8 CanActivateEnShuffle(void)
{
  if (sEnShuffleFieldUsedThisTurn)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!HasEnShuffleFieldTarget())
    return FALSE;

  /* Need a different-name summon after shuffle — scan deck for any legal SS.
   * Exact exclude id is unknown until target pick; any E-HERO/Neo in deck is enough. */
  return DeckHasDifferentNameSummon(CARD_NONE);
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 LoadSummonDeckMenu(u16 excludeId, u8 *deckIndexOut)
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

    if (!IsElementalHeroOrNeoSpacian(cardId))
      continue;
    if (cardId == excludeId)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
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

static u16 PickSummonCardId(u16 excludeId)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 cardId;

  DECKMENU_SAVE();

  menuCount = LoadSummonDeckMenu(excludeId, deckIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return CARD_NONE;
  }

  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    cardId = gDeckMenu.cards[0];
    DECKMENU_RESTORE();
    return cardId;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sEnShufflePickLabels,
                                         ARRAY_COUNT(sEnShufflePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    /* Activation committed — auto first legal. */
    cardId = gDuelDecks[FixedDuelistForTurnDuelist(ACTIVE_DUELIST)].cards[deckIndexMap[0]];
    return cardId;
  }

  cardId = gDeckMenu.cards[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return cardId;
}

static void DestroyEnShuffleSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == EN_SHUFFLE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishEnShuffle(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  u16 shuffledId;
  u16 summonId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!IsValidEnShuffleFieldTarget(fixedRow, fixedCol)) {
    DestroyEnShuffleSpellZone();
    return;
  }

  shuffledId = target->id;
  ClearZone(target);
  ReturnCardToDeck(ACTIVE_DUELIST, shuffledId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  sEnShuffleFieldUsedThisTurn = TRUE;

  if (IsDuelOver() == TRUE)
    return;

  sEnShuffleExcludeId = shuffledId;
  summonId = PickSummonCardId(shuffledId);
  sEnShuffleExcludeId = 0;

  DestroyEnShuffleSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  if (summonId == CARD_NONE || summonId == shuffledId)
    return;
  if (!IsElementalHeroOrNeoSpacian(summonId))
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, summonId, opts);
}

static void CancelEnShuffleTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyEnShuffleSpellZone();
}

static u8 AiPickEnShuffleTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEnShuffleFieldTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveEnShuffleTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidEnShuffleFieldTarget(fixedRow, fixedCol))
    return;

  FinishEnShuffle(fixedRow, fixedCol);
}

static void EN_SHUFFLE_ResolveBody(void)
{
  Duel_ShowEffectText(EN_SHUFFLE);

  if (IsDuelOver() == TRUE || !CanActivateEnShuffle())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidEnShuffleFieldTarget, ResolveEnShuffleTarget,
                     CancelEnShuffleTargeting, AiPickEnShuffleTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  /* ponytail: GY ignition (banish this; shuffle E-HERO+Neo OR Neos from GY →
   * Deck, draw 1) needs a GY-activate spell path outside this file.
   * Ceiling: on-field shuffle+SS only; upgrade: GY activate → banish EN_SHUFFLE
   * → return pair/Neos → Duel_DrawCards(1). */
}

APPEND_TEXT void EffectEN_SHUFFLE(void)
{
  if (!CanActivateEnShuffle()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(EN_SHUFFLE, EN_SHUFFLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void EN_SHUFFLE_SelfCheck(void)
{
  if (!IsElementalHeroOrNeoSpacian(ELEMENTAL_HERO_NEOS))
    while (1)
      ;
  if (!IsElementalHeroOrNeoSpacian(NEO_SPACIAN_AIR_HUMMINGBIRD))
    while (1)
      ;
  if (IsElementalHeroOrNeoSpacian(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
