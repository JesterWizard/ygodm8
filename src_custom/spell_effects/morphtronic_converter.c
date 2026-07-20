#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static const u8 sMorphConvPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */
static u16 sMorphConverterExcludeId APPEND_DATA = {0};

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

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 IsMachineMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 IsValidMachineTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsMachineMonster(zone->id);
}

static u8 HasMachineTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMachineTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void PlaceCardOnDeckTop(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 LoadMorphDeckMenu(u16 excludeId, u8 *deckIndexOut)
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

    if (!IsMorphtronicMonster(cardId))
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

static u16 PickMorphFromDeck(u16 excludeId)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u16 cardId;

  DECKMENU_SAVE();
  menuCount = LoadMorphDeckMenu(excludeId, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sMorphConvPickLabels, ARRAY_COUNT(sMorphConvPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return gDuelDecks[FixedDuelistForTurnDuelist(ACTIVE_DUELIST)].cards[deckIndexMap[0]];
  }

  cardId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return cardId;
}

static u8 IsLv4OrLowerMachine(u16 cardId)
{
  if (!IsMachineMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= 4;
}

static void ResolveAttackPosition(struct DuelCard *zone)
{
  u16 excludeId = zone->id;
  u16 summonId;
  struct DuelSummonOpts opts;

  summonId = PickMorphFromDeck(excludeId);
  if (summonId == CARD_NONE) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, summonId, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  PlaceCardOnDeckTop(ACTIVE_DUELIST, excludeId);
  ClearZone(zone);
}

static void ResolveDefensePosition(struct DuelCard *zone)
{
  s8 handZone;
  struct DuelSummonOpts opts;

  zone->isDefending = FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsLv4OrLowerMachine);
  else {
    u8 i;

    handZone = -1;
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsLv4OrLowerMachine(gTurnHands[ACTIVE_DUELIST][i]->id)) {
        handZone = (s8)i;
        break;
      }
    }
  }

  if (handZone < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
}

static void MorphConverterOnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_ClearPickZone();
  if (zone == NULL)
    return;

  if (zone->isDefending)
    ResolveDefensePosition(zone);
  else
    ResolveAttackPosition(zone);

  EffectOpt_MarkUsed(MORPHTRONIC_CONVERTER);
  UpdateDuelGfxExceptField();
}

static void MorphConverterCancel(void)
{
  Duel_ClearPickZone();
}

static u8 MorphConverterValidate(u8 fixedRow, u8 fixedCol)
{
  return IsValidMachineTarget(fixedRow, fixedCol);
}

static u8 MorphConverterAiPick(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidMachineTarget(row, col))
      continue;
    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateMORPHTRONIC_CONVERTER(void)
{
  if (EffectOpt_IsUsed(MORPHTRONIC_CONVERTER))
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasMachineTarget();
}

static void MORPHTRONIC_CONVERTER_ResolveBody(void)
{
  if (!CanActivateMORPHTRONIC_CONVERTER()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(MORPHTRONIC_CONVERTER);
  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(MorphConverterValidate, MorphConverterOnTarget,
                     MorphConverterCancel, MorphConverterAiPick);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  (void)sMorphConverterExcludeId;
}

APPEND_TEXT void EffectMORPHTRONIC_CONVERTER(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_CONVERTER, MORPHTRONIC_CONVERTER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
