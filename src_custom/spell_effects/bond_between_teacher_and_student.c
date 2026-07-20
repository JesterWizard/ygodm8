#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

enum {
  BOND_MODE_SUMMON_DARK_MAGICIAN = 0,      /* control DMG → SS Dark Magician */
  BOND_MODE_SUMMON_DARK_MAGICIAN_GIRL = 1, /* control DM → SS Dark Magician Girl */
};

static const char sDarkMagicianGirlName[] APPEND_RODATA = "Dark Magician Girl";

/* ponytail: Dark Magic Twin Burst is not in trunk/card_ids — Set list is the
 * three in-game Dark Magician support Spells only.
 * Ceiling: misses Twin Burst; upgrade: add DARK_MAGIC_TWIN_BURST card + id. */
static const u16 sBondSetSpellIds[] APPEND_RODATA = {
  DARK_MAGIC_ATTACK,
  DARK_BURNING_ATTACK,
  DARK_BURNING_MAGIC,
};

static const u8 sBondSetPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkMagicianGirlMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == DARK_MAGICIAN_GIRL)
    return TRUE;

  return Duel_CardNameContains(cardId, sDarkMagicianGirlName);
}

static u8 ControlsDarkMagician(void)
{
  return RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], DARK_MAGICIAN);
}

static u8 ControlsDarkMagicianGirl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDarkMagicianGirlMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 HandHasCardId(u16 cardId)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], cardId);
}

static u8 GraveHasCardId(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == cardId;

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonCardId(u16 cardId)
{
  if (HandHasCardId(cardId))
    return TRUE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId) >= 0)
    return TRUE;

  return GraveHasCardId(cardId);
}

static u8 IsBondSetSpell(u16 cardId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sBondSetSpellIds); i++) {
    if (cardId == sBondSetSpellIds[i])
      return TRUE;
  }

  return FALSE;
}

static s16 FindFirstBondSetSpellDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsBondSetSpell(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 CanSummonDarkMagicianBranch(void)
{
  return ControlsDarkMagicianGirl() && CanSpecialSummonCardId(DARK_MAGICIAN);
}

static u8 CanSummonDarkMagicianGirlBranch(void)
{
  return ControlsDarkMagician() && CanSpecialSummonCardId(DARK_MAGICIAN_GIRL);
}

u8 CanActivateBOND_BETWEEN_TEACHER_AND_STUDENT(void)
{
  /* ponytail: once-per-turn not tracked after this normal spell leaves the field
   * (no shared turn-flag RAM editable from this file alone).
   * Ceiling: multiple Bond per turn; upgrade: duel-state OPT bit. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return CanSummonDarkMagicianBranch() || CanSummonDarkMagicianGirlBranch();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = summon Dark Magician (need DMG); FALSE = summon Dark Magician Girl (need DM). */
static u8 PlayerChoosesSummonDarkMagician(void)
{
  /* ponytail: no dedicated choice UI — A = SS Dark Magician, B = SS Dark Magician Girl.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
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

static u8 ChooseBondMode(void)
{
  u8 canDm = CanSummonDarkMagicianBranch();
  u8 canDmg = CanSummonDarkMagicianGirlBranch();

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && canDm && canDmg)
    return PlayerChoosesSummonDarkMagician() ? BOND_MODE_SUMMON_DARK_MAGICIAN
                                             : BOND_MODE_SUMMON_DARK_MAGICIAN_GIRL;

  if (canDm)
    return BOND_MODE_SUMMON_DARK_MAGICIAN;

  return BOND_MODE_SUMMON_DARK_MAGICIAN_GIRL;
}

static s8 PickHandZoneWithId(u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return (s8)i;
  }

  return -1;
}

static u8 FindGraveyardCardIndex(u8 fixedDuelist, u16 cardId, u8 *outIndex)
{
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId) {
      *outIndex = i;
      return TRUE;
    }
  }

  return FALSE;
}

static void SpecialSummonCardIdFromGrave(u16 cardId, struct DuelSummonOpts opts)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 graveIndex;
  u16 removed;

  if (!GraveyardExpand_IsEnabled()) {
    Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
    return;
  }

  if (!FindGraveyardCardIndex(fixedDuelist, cardId, &graveIndex))
    return;

  removed = GraveyardExpand_RemoveAtFixed(fixedDuelist, graveIndex);
  if (removed != cardId)
    return;

  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

/* Prefer hand → Deck → GY (same order as Dedication Through Light and Darkness). */
static void SpecialSummonCardId(u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonCardId(cardId))
    return;

  if (HandHasCardId(cardId)) {
    if (WhoseTurn() == DUEL_PLAYER) {
      Duel_SpecialSummonFromHand(ACTIVE_DUELIST, cardId, NULL, opts);
      return;
    }

    {
      s8 handZone = PickHandZoneWithId(cardId);

      if (handZone >= 0)
        Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
    }
    return;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId) >= 0) {
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
    return;
  }

  SpecialSummonCardIdFromGrave(cardId, opts);
}

static void InitSetBackrowSlot(struct DuelCard *zone, u16 cardId)
{
  zone->id = cardId;
  zone->isFaceUp = FALSE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->unk4 = 0;
  zone->willChangeSides = FALSE;
  ResetPermStage(zone);
  ResetTempStage(zone);
}

static u8 LoadBondSetSpellDeckMenu(u8 turnDuelist, u8 *deckIndexOut)
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

    if (!IsBondSetSpell(cardId))
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

static u8 PickBondSetSpellDeckIndex(u8 turnDuelist)
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadBondSetSpellDeckMenu(turnDuelist, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sBondSetPickLabels,
                                         ARRAY_COUNT(sBondSetPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return 0xFF; /* optional Set — cancel skips */
  }

  deckIndex = deckIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return deckIndex;
}

static u8 SetBondSpellFromDeckAtIndex(u8 turnDuelist, u8 deckIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 backCol;
  u16 cardId;

  if (deckIndex < gDuelDecks[fixedDuelist].cardsDrawn
      || deckIndex >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  backCol = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (backCol < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsBondSetSpell(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitSetBackrowSlot(gTurnZones[ACTIVE_DUELIST_BACKROW][backCol], cardId);
  return TRUE;
}

static void TryOptionalSetBondSpell(void)
{
  u8 deckIndex;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) < 0)
    return;

  if (FindFirstBondSetSpellDeckIndex(ACTIVE_DUELIST) < 0)
    return;

  /* AI always Sets when able; player may cancel the deck pick. */
  deckIndex = PickBondSetSpellDeckIndex(ACTIVE_DUELIST);
  if (deckIndex != 0xFF)
    SetBondSpellFromDeckAtIndex(ACTIVE_DUELIST, deckIndex);
}

static void BOND_BETWEEN_TEACHER_AND_STUDENT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 mode;

  Duel_ShowEffectText(BOND_BETWEEN_TEACHER_AND_STUDENT);

  if (IsDuelOver() == TRUE || !CanActivateBOND_BETWEEN_TEACHER_AND_STUDENT())
    return;

  mode = ChooseBondMode();

  if (spellZone != NULL && spellZone->id == BOND_BETWEEN_TEACHER_AND_STUDENT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  if (mode == BOND_MODE_SUMMON_DARK_MAGICIAN)
    SpecialSummonCardId(DARK_MAGICIAN);
  else
    SpecialSummonCardId(DARK_MAGICIAN_GIRL);

  if (IsDuelOver() == TRUE)
    return;

  TryOptionalSetBondSpell();
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectBOND_BETWEEN_TEACHER_AND_STUDENT(void)
{
  if (!CanActivateBOND_BETWEEN_TEACHER_AND_STUDENT()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(BOND_BETWEEN_TEACHER_AND_STUDENT,
                                       BOND_BETWEEN_TEACHER_AND_STUDENT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BOND_BETWEEN_TEACHER_AND_STUDENT_SelfCheck(void)
{
  if (!IsDarkMagicianGirlMonster(DARK_MAGICIAN_GIRL))
    while (1)
      ;
  if (IsDarkMagicianGirlMonster(DARK_MAGICIAN))
    while (1)
      ;
  if (!IsBondSetSpell(DARK_MAGIC_ATTACK))
    while (1)
      ;
  if (IsBondSetSpell(DARK_MAGICIAN))
    while (1)
      ;
}
#endif
