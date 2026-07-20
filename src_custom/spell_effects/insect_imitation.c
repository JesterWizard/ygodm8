#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const u8 sInsectImitationPickLabels[] APPEND_RODATA = {
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

static u8 ZoneIsTributeableMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

/* Needed Insect Level is stashed in gSpellEffectData.row2 during resolve. */
static u8 IsInsectSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_INSECT))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == gSpellEffectData.row2;
}

static s16 FindFirstInsectDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsInsectSummonTarget(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 FieldHasMatchingTribute(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u8 savedNeeded = gSpellEffectData.row2;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (!ZoneIsTributeableMonster(fixedRow, col))
      continue;

    SetCardInfo(zone->id);
    gSpellEffectData.row2 = gCardInfo.level + 1;
    if (gSpellEffectData.row2 == 0)
      continue;

    if (FindFirstInsectDeckIndex(ACTIVE_DUELIST) >= 0) {
      gSpellEffectData.row2 = savedNeeded;
      return TRUE;
    }
  }

  gSpellEffectData.row2 = savedNeeded;
  return FALSE;
}

static u8 LoadInsectDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsInsectSummonTarget(cardId))
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

static u8 PickInsectDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadInsectDeckMenu(turnDuelist, deckIndexMap);
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
          sInsectImitationPickLabels, ARRAY_COUNT(sInsectImitationPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static enum DuelActionResult SpecialSummonInsectAtDeckIndex(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsInsectSummonTarget(cardId))
    return DUEL_ACTION_NO_TARGET;

  return Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
}

static void ResolveInsectImitationTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];
  u8 deckIndex;

  if (!ZoneIsTributeableMonster(fixedRow, fixedCol))
    return;

  SetCardInfo(tributeZone->id);
  gSpellEffectData.row2 = gCardInfo.level + 1;
  if (gSpellEffectData.row2 == 0 || FindFirstInsectDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickInsectDeckIndex(ACTIVE_DUELIST);
  if (deckIndex == 0xFF)
    return;

  if (SpecialSummonInsectAtDeckIndex(ACTIVE_DUELIST, deckIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
}

static void CancelInsectImitationTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == INSECT_IMITATION)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 IsValidInsectImitationTribute(u8 fixedRow, u8 fixedCol)
{
  u8 savedNeeded = gSpellEffectData.row2;
  u8 ok;

  if (!ZoneIsTributeableMonster(fixedRow, fixedCol))
    return FALSE;

  SetCardInfo(gFixedZones[fixedRow][fixedCol]->id);
  gSpellEffectData.row2 = gCardInfo.level + 1;
  ok = gSpellEffectData.row2 != 0 && FindFirstInsectDeckIndex(ACTIVE_DUELIST) >= 0;
  gSpellEffectData.row2 = savedNeeded;
  return ok;
}

static u8 AiPickInsectImitationTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0xFFFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidInsectImitationTribute(fixedRow, col))
      continue;

    zone = gFixedZones[fixedRow][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = fixedRow;
      *outCol = col;
    }
  }

  return found;
}

u8 CanActivateINSECT_IMITATION(void)
{
  return FieldHasMatchingTribute();
}

static void INSECT_IMITATION_ResolveBody(void)
{
  Duel_ShowEffectText(INSECT_IMITATION);

  if (IsDuelOver() == TRUE || !CanActivateINSECT_IMITATION())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidInsectImitationTribute, ResolveInsectImitationTribute,
                     CancelInsectImitationTargeting, AiPickInsectImitationTribute);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectINSECT_IMITATION(void)
{
  if (!CanActivateINSECT_IMITATION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(INSECT_IMITATION, INSECT_IMITATION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
