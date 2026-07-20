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

void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";
static const char sGladiatorName[] APPEND_RODATA = "Gladiator";

static const u8 sFlavianPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 AnyHandCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
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

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS
      || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS || cardId == PANDEMONIUM
      || cardId == MYSTIC_MINE || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == AMAZONESS_VILLAGE
      || cardId == NECROVALLEY || cardId == CHICKEN_GAME)
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

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
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

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static s16 FindFirstMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (pred(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 HandHasDiscardCost(void)
{
  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0;
}

static u8 CanActivateFlavianSearch(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS
      || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (!HandHasDiscardCost())
    return FALSE;

  return FindFirstMatchingDeckIndex(ACTIVE_DUELIST, IsGladiatorBeastMonster) >= 0;
}

static u8 LoadMatchingDeckMenu(u8 turnDuelist, u8 (*pred)(u16), u8 *deckIndexOut)
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

    if (!pred(cardId))
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

static u8 PickMatchingDeckIndex(u8 turnDuelist, u8 (*pred)(u16))
{
  u8 deckIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 deckIndex;

  DECKMENU_SAVE();

  menuCount = LoadMatchingDeckMenu(turnDuelist, pred, deckIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sFlavianPickLabels,
                                         ARRAY_COUNT(sFlavianPickLabels))) {
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
  if (!IsGladiatorBeastMonster(cardId))
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone), cardId);
  return TRUE;
}

static void ResolveFlavianSearch(struct DuelCard *zone)
{
  u8 deckIndex;

  if (!CanActivateFlavianSearch(zone))
    return;

  Duel_ShowEffectText(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, AnyHandCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  deckIndex = PickMatchingDeckIndex(ACTIVE_DUELIST, IsGladiatorBeastMonster);
  if (deckIndex != 0xFF)
    AddDeckCardAtIndexToHand(ACTIVE_DUELIST, deckIndex);

  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up field (OPT search ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateFlavianSearch(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveFlavianSearch(zone);
    return;
  }

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);

  if (CanActivateFlavianSearch(zone))
    ResolveFlavianSearch(zone);
  else
    Duel_ShowEffectText(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS);

  /* ponytail: when opponent declares an attack → OPT SS 1 Gladiator Beast from
   * Deck (cannot be destroyed by battle) needs an attack-declaration hook
   * outside this file. Ceiling: face-up field + search ignition only; upgrade:
   * on attack declare → if face-up FLAVIAN and !OPT2 then
   * Duel_SpecialSummonFromDeck(GB) + battle-destroy protect flag. */

  /* ponytail: End Phase Set 1 Gladiator Trap from Deck if a GB was SS from Deck
   * this turn needs End Phase + summon-from-Deck tracking outside this file.
   * Ceiling: no End Phase Set; upgrade: turn_effect End Phase → if face-up
   * FLAVIAN && ssFromDeckFlag && !OPT3 then DeckMenu Set trap with name
   * containing "Gladiator" and TYPE_GROUP_TRAP. */

  /* ponytail: not in GetSpellType NORMAL/FIELD override — face-up OPT
   * re-activation may need card_hooks GetSpellType + FLAVIAN listed
   * (same as DRAGON_RAVINE / CHICKEN_GAME). */

  (void)sGladiatorName;
}

APPEND_TEXT void EffectFLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS(void)
{
  if (Duel_TryResolveSpellThroughTraps(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS,
                                       FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS_SelfCheck(void)
{
  if (!IsGladiatorBeastMonster(GLADIATOR_BEAST_ANDAL))
    while (1)
      ;
  if (IsGladiatorBeastMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS))
    while (1)
      ;
}
#endif
