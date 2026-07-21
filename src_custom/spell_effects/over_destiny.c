#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "over_destiny.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 sOverDestinyStampRow APPEND_DATA = {0xFF};
static u8 sOverDestinyStampCol APPEND_DATA = {0xFF};
static u16 sOverDestinyStampId APPEND_DATA = {CARD_NONE};

static const char sDestinyHeroArchetypeName[] APPEND_RODATA = "Destiny HERO";

static const u8 sOverDestinyPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroArchetypeName);
}

/* Max summon Level stashed in gSpellEffectData.row2 after GY target pick. */
static u8 IsOverDestinySummonTarget(u16 cardId)
{
  if (!IsDestinyHeroMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= gSpellEffectData.row2;
}

static u8 MaxSummonLevelFromGyTarget(u16 gyCardId)
{
  u8 half;

  if (!IsDestinyHeroMonster(gyCardId))
    return 0;

  SetCardInfo(gyCardId);
  half = gCardInfo.level / 2;
  return half;
}

static s16 FindFirstEligibleDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsOverDestinySummonTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 GyTargetHasDeckMatch(u16 gyCardId)
{
  u8 savedMax = gSpellEffectData.row2;
  u8 maxLevel = MaxSummonLevelFromGyTarget(gyCardId);
  u8 ok;

  if (maxLevel == 0)
    return FALSE;

  gSpellEffectData.row2 = maxLevel;
  ok = FindFirstEligibleDeckIndex(ACTIVE_DUELIST) >= 0;
  gSpellEffectData.row2 = savedMax;
  return ok;
}

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (GyTargetHasDeckMatch(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GyTargetHasDeckMatch(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

u8 CanActivateOVER_DESTINY(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindFirstEligibleGyIndex(fixedDuelist) >= 0;
}

static u8 LoadEligibleGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!GyTargetHasDeckMatch(cardId))
      continue;

    gyIndexMap[menuCount] = i;
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

static s8 PlayerPickGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sOverDestinyPickLabels, ARRAY_COUNT(sOverDestinyPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
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

    if (!IsOverDestinySummonTarget(cardId))
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
          sOverDestinyPickLabels, ARRAY_COUNT(sOverDestinyPickLabels))) {
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
  enum DuelActionResult result;
  u8 col;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsOverDestinySummonTarget(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  result = Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  if (result == DUEL_ACTION_OK) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (zone != NULL && zone->id == cardId) {
        OverDestiny_StampSummonedZone(zone);
        break;
      }
    }
  }

  return result;
}

void OverDestiny_StampSummonedZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || zone->id == CARD_NONE)
    return;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  sOverDestinyStampRow = fixedRow;
  sOverDestinyStampCol = fixedCol;
  sOverDestinyStampId = zone->id;
}

void TryApplyOverDestinyEndPhase(void)
{
  struct DuelCard *zone;

  if (sOverDestinyStampRow > PLAYER_MONSTER_ROW || sOverDestinyStampCol >= MAX_ZONES_IN_ROW) {
    sOverDestinyStampRow = 0xFF;
    sOverDestinyStampCol = 0xFF;
    sOverDestinyStampId = CARD_NONE;
    return;
  }

  zone = gFixedZones[sOverDestinyStampRow][sOverDestinyStampCol];
  if (zone != NULL && zone->id == sOverDestinyStampId && zone->id != CARD_NONE)
    Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(sOverDestinyStampRow), TRUE);

  sOverDestinyStampRow = 0xFF;
  sOverDestinyStampCol = 0xFF;
  sOverDestinyStampId = CARD_NONE;
}

static u16 GyCardIdAtIndex(u8 fixedDuelist, s8 gyIndex)
{
  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

  return GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
}

static void OVER_DESTINY_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;
  u16 gyCardId;
  u8 maxLevel;
  u8 deckIndex;

  Duel_ShowEffectText(OVER_DESTINY);

  if (IsDuelOver() == TRUE || !CanActivateOVER_DESTINY())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstEligibleGyIndex(fixedDuelist);
  }

  if (gyIndex < 0)
    return;

  gyCardId = GyCardIdAtIndex(fixedDuelist, gyIndex);
  maxLevel = MaxSummonLevelFromGyTarget(gyCardId);
  if (maxLevel == 0)
    return;

  gSpellEffectData.row2 = maxLevel;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0
      || FindFirstEligibleDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickEligibleDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF)
    return;

  if (SpecialSummonDeckCardAtIndex(ACTIVE_DUELIST, deckIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  /* Parent: TryApplyOverDestinyEndPhase from turn_effect_hooks End Phase. */
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectOVER_DESTINY(void)
{
  if (!CanActivateOVER_DESTINY()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(OVER_DESTINY, OVER_DESTINY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void OVER_DESTINY_SelfCheck(void)
{
  if (!IsDestinyHeroMonster(DESTINY_HERO_DIAMOND_DUDE))
    while (1)
      ;
  if (IsDestinyHeroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;

  /* Diamond Dude is Level 4 → half = 2; Dogma is Level 8 → half = 4. */
  SetCardInfo(DESTINY_HERO_DIAMOND_DUDE);
  if (gCardInfo.level / 2 != 2)
    while (1)
      ;
  SetCardInfo(DESTINY_HERO_DOGMA);
  if (gCardInfo.level / 2 != 4)
    while (1)
      ;
}
#endif
