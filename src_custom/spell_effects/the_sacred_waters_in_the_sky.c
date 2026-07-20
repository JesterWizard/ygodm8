#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define SACRED_WATERS_LP_PER_MONSTER 500

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);
void SetDuelFieldGfx(u8 field);
void EffectActivateSanctuaryInTheSky(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static const char sSanctuaryMentionNeedle[] APPEND_RODATA = "Sanctuary in the Sky";
static const char sHyperionName[] APPEND_RODATA = "Hyperion";
static const char sTheAgentName[] APPEND_RODATA = "The Agent";

static const u8 sSacredWatersPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CardDescriptionContains(u16 cardId, const char *needle)
{
  const u8 *desc;
  u8 needleLen = 0;
  u16 i;

  if (cardId == CARD_NONE || needle == NULL)
    return FALSE;

  while (needle[needleLen] != 0)
    needleLen++;

  if (needleLen == 0)
    return FALSE;

  SetCardInfo(cardId);
  desc = gCardInfo.description;
  if (desc == NULL)
    return FALSE;

  for (i = 0; desc[i] != 0; i++) {
    u8 j = 0;

    while (j < needleLen && desc[i + j] != 0 && desc[i + j] == (u8)needle[j])
      j++;

    if (j == needleLen)
      return TRUE;
  }

  return FALSE;
}

static u8 IsMonsterMentioningSanctuary(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return CardDescriptionContains(cardId, sSanctuaryMentionNeedle);
}

static u8 IsHyperionOrAgentMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardNameContains(cardId, sHyperionName))
    return TRUE;

  return Duel_CardNameContains(cardId, sTheAgentName);
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

static void InitBackrowSlotFromCard(struct DuelCard *zone, u16 cardId)
{
  zone->id = cardId;
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->unk4 = 0;
  zone->willChangeSides = FALSE;
  ResetPermStage(zone);
  ResetTempStage(zone);
}

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == THE_SANCTUARY_IN_THE_SKY || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS
      || cardId == DRAGON_RAVINE)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *exceptZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == exceptZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static u8 HandHasRoomForDeckSearch(u8 turnDuelist)
{
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0)
    return TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[turnDuelist][i]->id == THE_SACRED_WATERS_IN_THE_SKY)
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasSanctuary(void)
{
  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY) >= 0;
}

static s16 FindFirstMentionMonsterDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsMonsterMentioningSanctuary(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanActivateFieldFromDeck(void)
{
  if (!DeckHasSanctuary())
    return FALSE;

  /* After consuming Sacred Waters there is always a free backrow slot. */
  return TRUE;
}

static u8 CanSearchMentionMonster(void)
{
  if (!HandHasRoomForDeckSearch(ACTIVE_DUELIST))
    return FALSE;

  return FindFirstMentionMonsterDeckIndex(ACTIVE_DUELIST) >= 0;
}

static u8 CanActivateSacredWaters(void)
{
  return CanActivateFieldFromDeck() || CanSearchMentionMonster();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns TRUE for activate Sanctuary from Deck, FALSE for search mention monster. */
static u8 PlayerChoosesActivateSanctuary(void)
{
  /* ponytail: no dedicated choice UI — A = activate Sanctuary, B = search mention.
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

static u8 LoadMentionMonsterDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsMonsterMentioningSanctuary(cardId))
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

static u8 PickMentionMonsterDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMentionMonsterDeckMenu(turnDuelist, deckIndexMap);
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
          sSacredWatersPickLabels, ARRAY_COUNT(sSacredWatersPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF;
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();

  return deckIndex;
}

static u8 AddDeckCardAtIndexToHand(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsMonsterMentioningSanctuary(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static u8 ActivateSanctuaryFromDeck(void)
{
  s16 deckIndex;
  s8 backCol;
  struct DuelCard *zone;
  u16 savedId;
  u8 savedRow;
  u8 savedCol;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY);
  if (deckIndex < 0)
    return FALSE;

  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  zone = gTurnZones[ACTIVE_DUELIST_BACKROW][backCol];
  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return FALSE;

  /* Re-check empty after field-spell cleanup (and Sacred Waters already consumed). */
  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, THE_SANCTUARY_IN_THE_SKY);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  zone = gTurnZones[ACTIVE_DUELIST_BACKROW][backCol];
  InitBackrowSlotFromCard(zone, THE_SANCTUARY_IN_THE_SKY);

  savedId = gSpellEffectData.id;
  savedRow = gSpellEffectData.row1;
  savedCol = gSpellEffectData.col1;
  gSpellEffectData.id = THE_SANCTUARY_IN_THE_SKY;
  gSpellEffectData.row1 = ACTIVE_DUELIST_BACKROW;
  gSpellEffectData.col1 = (u8)backCol;

  EffectActivateSanctuaryInTheSky();

  gSpellEffectData.id = savedId;
  gSpellEffectData.row1 = savedRow;
  gSpellEffectData.col1 = savedCol;
  return TRUE;
}

static void ResolveMentionMonsterSearch(void)
{
  u8 deckIndex;

  if (FindFirstMentionMonsterDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  deckIndex = PickMentionMonsterDeckIndex(ACTIVE_DUELIST);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex);
}

static u8 GyHasSanctuary(u8 fixedDuelist)
{
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == THE_SANCTUARY_IN_THE_SKY;

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_SANCTUARY_IN_THE_SKY)
      return TRUE;
  }

  return FALSE;
}

static u8 SanctuaryOnFieldOrGy(void)
{
  if (gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_SANCTUARY_IN_THE_SKY)
    return TRUE;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return TRUE;

  if (GyHasSanctuary(DUEL_PLAYER) || GyHasSanctuary(DUEL_OPPONENT))
    return TRUE;

  return FALSE;
}

static u8 CountHyperionAndAgentsControlled(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id;

    if (IsHyperionOrAgentMonster(cardId))
      count++;
  }

  return count;
}

static void TryGainLpFromHyperionAgents(void)
{
  u8 count;

  if (!SanctuaryOnFieldOrGy())
    return;

  count = CountHyperionAndAgentsControlled();
  if (count == 0)
    return;

  Duel_ChangeLp(ACTIVE_DUELIST, (s32)count * SACRED_WATERS_LP_PER_MONSTER, FALSE);
}

static void THE_SACRED_WATERS_IN_THE_SKY_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 chooseActivate;
  u8 hasActivate;
  u8 hasSearch;

  Duel_ShowEffectText(THE_SACRED_WATERS_IN_THE_SKY);

  if (IsDuelOver() == TRUE || !CanActivateSacredWaters())
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  hasActivate = CanActivateFieldFromDeck();
  hasSearch = CanSearchMentionMonster();

  if (!hasActivate && !hasSearch)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasActivate && hasSearch)
    chooseActivate = PlayerChoosesActivateSanctuary();
  else if (hasActivate)
    chooseActivate = TRUE;
  else
    chooseActivate = FALSE;

  if (chooseActivate)
    ActivateSanctuaryFromDeck();
  else
    ResolveMentionMonsterSearch();

  if (IsDuelOver() == TRUE)
    return;

  TryGainLpFromHyperionAgents();

  /* ponytail: battle-destruction protection ("banish this from GY instead") needs a
   * battle/destroy redirect hook. Ceiling: activate + LP gain only; upgrade:
   * battle_damage / destroy-protection hook checking GY Sacred Waters. */

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectTHE_SACRED_WATERS_IN_THE_SKY(void)
{
  if (!CanActivateSacredWaters()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_SACRED_WATERS_IN_THE_SKY,
                                       THE_SACRED_WATERS_IN_THE_SKY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_SACRED_WATERS_IN_THE_SKY_SelfCheck(void)
{
  if (!IsHyperionOrAgentMonster(MASTER_HYPERION))
    while (1)
      ;
  if (!IsHyperionOrAgentMonster(THE_AGENT_OF_FORCE_MARS))
    while (1)
      ;
  if (IsHyperionOrAgentMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
