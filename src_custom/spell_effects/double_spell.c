#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);
void ActivateSpellEffect(void);

static const u8 sDoubleSpellPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 HandHasSpell(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsSpellCard(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 OppGyHasSpell(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static s8 FindFirstSpellGyIndex(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsSpellCard(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadSpellGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount;
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsSpellCard(top)) {
      gDeckMenu.cardCount = 0;
      return 0;
    }

    gyIndexMap[0] = 0;
    gDeckMenu.cards[0] = top;
    gDeckMenu.cost = 0;
    gDeckMenu.currentPos = 0;
    gDeckMenu.sortMode = 0;
    gDeckMenu.displayMode = 1;
    gDeckMenu.cardCount = 1;
    return 1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsSpellCard(cardId))
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

static s8 PlayerPickSpellGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadSpellGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sDoubleSpellPickLabels,
                                         ARRAY_COUNT(sDoubleSpellPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u16 TakeSpellFromOppGy(u8 fixedDuelist, u8 gyIndex)
{
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = GetGraveCardAndClearGrave(INACTIVE_DUELIST);
    if (!IsSpellCard(cardId))
      return CARD_NONE;
    return cardId;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsSpellCard(cardId))
    return CARD_NONE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return cardId;
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

u8 CanActivateDOUBLE_SPELL(void)
{
  u8 oppFixed = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);

  return HandHasSpell(gTurnHands[ACTIVE_DUELIST]) && OppGyHasSpell(oppFixed);
}

static void DestroyDoubleSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == DOUBLE_SPELL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void PlaceAndActivateCopiedSpell(u16 cardId)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 row = gSpellEffectData.row1;
  u8 col = gSpellEffectData.col1;
  u16 savedId;
  u8 savedRow;
  u8 savedCol;

  if (spellZone == NULL || cardId == CARD_NONE)
    return;

  /* Free Double Spell's zone (send to GY), then place the copied spell there. */
  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  InitBackrowSlotFromCard(gTurnZones[row][col], cardId);

  savedId = gSpellEffectData.id;
  savedRow = gSpellEffectData.row1;
  savedCol = gSpellEffectData.col1;
  gSpellEffectData.id = cardId;
  gSpellEffectData.row1 = row;
  gSpellEffectData.col1 = col;
  ActivateSpellEffect();
  gSpellEffectData.id = savedId;
  gSpellEffectData.row1 = savedRow;
  gSpellEffectData.col1 = savedCol;
}

static void DOUBLE_SPELL_ResolveBody(void)
{
  u8 oppFixed = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  s8 gyIndex;
  u16 cardId;

  Duel_ShowEffectText(DOUBLE_SPELL);

  if (IsDuelOver() == TRUE || !CanActivateDOUBLE_SPELL())
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsSpellCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (!OppGyHasSpell(oppFixed)) {
    DestroyDoubleSpellZone();
    return;
  }

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickSpellGyIndex(oppFixed);
  } else {
    gyIndex = FindFirstSpellGyIndex(oppFixed);
  }

  if (gyIndex < 0) {
    DestroyDoubleSpellZone();
    return;
  }

  cardId = TakeSpellFromOppGy(oppFixed, (u8)gyIndex);
  if (cardId == CARD_NONE) {
    DestroyDoubleSpellZone();
    return;
  }

  PlaceAndActivateCopiedSpell(cardId);
}

APPEND_TEXT void EffectDOUBLE_SPELL(void)
{
  if (!CanActivateDOUBLE_SPELL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DOUBLE_SPELL, DOUBLE_SPELL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DOUBLE_SPELL_SelfCheck(void)
{
  if (!IsSpellCard(POT_OF_GREED))
    while (1)
      ;
  if (!IsSpellCard(DOUBLE_SPELL))
    while (1)
      ;
  if (IsSpellCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
