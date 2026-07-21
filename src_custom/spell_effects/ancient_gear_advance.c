#include "global.h"
#include "common-chax.h"
#include "ancient_gear_advance.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";
static const char sAncientGearGolemName[] APPEND_RODATA = "Ancient Gear Golem";

static u8 sAncientGearAdvanceTributeFreeActive APPEND_DATA = {0};
static u8 sAncientGearAdvanceCannotSet APPEND_DATA = {0};

static const u8 sAgPickLabels[] APPEND_RODATA = {
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

static int LookupRequiredTributes(u8 level)
{
  if (level <= 4)
    return 0;
  if (level <= 6)
    return 1;
  if (level <= 8)
    return 2;
  return 3;
}

static int BaseRequiredTributesForCard(u16 cardId)
{
  SetCardInfo(cardId);
  return LookupRequiredTributes(gCardInfo.level);
}

static u8 QualifiesForAdvanceTributeFreeSummon(u16 cardId)
{
  if (cardId == ANCIENT_GEAR_GOLEM)
    return TRUE;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.level < 5)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearGolemName);
}

void AncientGearAdvance_OnTurnBoundary(void)
{
  sAncientGearAdvanceTributeFreeActive = FALSE;
  sAncientGearAdvanceCannotSet = FALSE;
}

u8 AncientGearAdvance_CanNormalSummonWithoutTribute(u16 cardId)
{
  if (!sAncientGearAdvanceTributeFreeActive)
    return FALSE;

  if (!QualifiesForAdvanceTributeFreeSummon(cardId))
    return FALSE;

  return BaseRequiredTributesForCard(cardId) > 0;
}

u8 AncientGearAdvance_TryConsumeOnNormalSummon(u16 cardId)
{
  if (!AncientGearAdvance_CanNormalSummonWithoutTribute(cardId))
    return FALSE;

  sAncientGearAdvanceTributeFreeActive = FALSE;
  return TRUE;
}

u8 AncientGearAdvance_CannotSetThisTurn(void)
{
  return sAncientGearAdvanceCannotSet;
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

static u8 IsAncientGearSpellTrapExceptAdvance(u16 cardId)
{
  u8 group;

  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_ADVANCE)
    return FALSE;

  group = GetTypeGroup(cardId);
  if (group != TYPE_GROUP_SPELL && group != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 LoadAgStDeckMenu(u8 *deckIndexOut)
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

    if (!IsAncientGearSpellTrapExceptAdvance(cardId))
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

static void SearchAncientGearSpellTrap(void)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 pick;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return;

  menuCount = LoadAgStDeckMenu(deckIndexMap);
  if (menuCount == 0)
    return;

  DECKMENU_SAVE();
  if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
    pick = 0;
  } else {
    DeckMenu_BeginDuelTrunkView();
    if (!DeckMenuMainPickConfirmWithLabels(sAgPickLabels, ARRAY_COUNT(sAgPickLabels))) {
      DECKMENU_RESTORE();
      DeckMenu_EndDuelTrunkView();
      return;
    }
    pick = gDeckMenu.currentPos;
    DeckMenu_EndDuelTrunkView();
  }
  DECKMENU_RESTORE();
  AddDeckCardToHand(deckIndexMap[pick]);
}

static u8 IsValidAdvanceTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasAdvanceTributeTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidAdvanceTributeTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateAncientGearAdvanceIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ANCIENT_GEAR_ADVANCE || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return HasAdvanceTributeTarget();
}

static void FinishAncientGearAdvanceIgnition(struct DuelCard *zone)
{
  if (zone == NULL)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  sAncientGearAdvanceTributeFreeActive = TRUE;
  sAncientGearAdvanceCannotSet = TRUE;
  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void ResolveAdvanceIgnitionTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidAdvanceTributeTarget(fixedRow, fixedCol) || tributeZone == NULL)
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  FinishAncientGearAdvanceIgnition(zone);
}

static void CancelAdvanceIgnitionTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickAdvanceIgnitionTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u16 bestAtk = 0xFFFF;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidAdvanceTributeTarget(fixedRow, col))
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

static void BeginAncientGearAdvanceIgnition(struct DuelCard *zone)
{
  if (!CanActivateAncientGearAdvanceIgnition(zone)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(ANCIENT_GEAR_ADVANCE);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    u8 row;
    u8 col;

    if (AiPickAdvanceIgnitionTribute(&row, &col))
      ResolveAdvanceIgnitionTribute(row, col);
    return;
  }

  Duel_SetupPickZone(IsValidAdvanceTributeTarget, ResolveAdvanceIgnitionTribute,
                     CancelAdvanceIgnitionTargeting, AiPickAdvanceIgnitionTribute);
  Duel_EnterPickZoneTargeting();
}

static void ANCIENT_GEAR_ADVANCE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    BeginAncientGearAdvanceIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(ANCIENT_GEAR_ADVANCE);
  SearchAncientGearSpellTrap();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectANCIENT_GEAR_ADVANCE(void)
{
  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_ADVANCE, ANCIENT_GEAR_ADVANCE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_ADVANCE_SelfCheck(void)
{
  if (!QualifiesForAdvanceTributeFreeSummon(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (QualifiesForAdvanceTributeFreeSummon(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
