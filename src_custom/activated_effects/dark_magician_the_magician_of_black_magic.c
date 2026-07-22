#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);

static u8 sDmDestroyInit APPEND_DATA = {0};
static u16 sPendingDmCardId APPEND_DATA = {CARD_NONE};
static u8 sPendingDmController APPEND_DATA = {0xFF};

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

/* Approximate "mentions Dark Magician" S/T via name or known support IDs. */
static const u16 sDmMentionSupport[] APPEND_RODATA = {
  DARK_MAGIC_CURTAIN,
  THOUSAND_KNIVES,
  SAGES_STONE,
  DEDICATION_THROUGH_LIGHT_AND_DARKNESS,
  DARK_MAGIC_ATTACK,
  DARK_MAGIC_VEIL,
  DARK_MAGICAL_CIRCLE,
  BOND_BETWEEN_TEACHER_AND_STUDENT,
  DARK_BURNING_ATTACK,
  DARK_BURNING_MAGIC,
  ILLUSION_MAGIC,
  MAGICIAN_NAVIGATION,
  SECRETS_OF_DARK_MAGIC,
  ETERNAL_SOUL,
  DARK_MAGIC_RITUAL,
  DARK_MAGIC_INHERITANCE,
  SHINING_SARCOPHAGUS,
};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 FieldHasLevel5OrHigher(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;
      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;
      if (gCardData_NEW[zone->id].level >= 5)
        return TRUE;
    }
  }
  return FALSE;
}

static u8 MentionsDarkMagicianSpellTrap(u16 cardId)
{
  u8 i;
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sDmMentionSupport); i++) {
    if (cardId == sDmMentionSupport[i])
      return TRUE;
  }
  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u16 FindDmMentionSpellTrapInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
                        ? DUEL_PLAYER
                        : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (MentionsDarkMagicianSpellTrap(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }
  return CARD_NONE;
}

static u8 SetSpellTrapFromDeck(u8 turnDuelist, u16 cardId)
{
  s8 empty;
  s16 deckIndex;
  struct DuelCard *slot;
  u8 backRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_BACKROW
                                             : INACTIVE_DUELIST_BACKROW;

  empty = FirstEmptyZoneInRow(gTurnZones[backRow]);
  if (empty < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);

  slot = gTurnZones[backRow][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

static s8 FindCardInGy(u8 fixedDuelist, u16 cardId)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == cardId)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId)
      return (s8)i;
  }
  return -1;
}

static void OnDmEffectDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || gHideEffectText)
    return;
  if (ev->cardId != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC
      && ev->cardId != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(ev->cardId))
    return;
  if (!FieldHasLevel5OrHigher())
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  sPendingDmCardId = ev->cardId;
  sPendingDmController = ev->controller;
}

static void OnDmFieldChange(const struct EffectEvent *ev)
{
  u16 cardId;
  u8 controller;
  u8 turnDuelist;
  u8 monRow;
  struct DuelSummonOpts opts;
  u16 setId;

  (void)ev;
  if (sPendingDmCardId == CARD_NONE || sPendingDmController > DUEL_OPPONENT)
    return;
  if (gHideEffectText) {
    sPendingDmCardId = CARD_NONE;
    sPendingDmController = 0xFF;
    return;
  }

  cardId = sPendingDmCardId;
  controller = sPendingDmController;
  sPendingDmCardId = CARD_NONE;
  sPendingDmController = 0xFF;

  if (EffectOpt_IsUsed(cardId))
    return;

  turnDuelist = TurnDuelistForFixed(controller);
  monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                         : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return;
  if (FindCardInGy(controller, cardId) < 0)
    return;

  Duel_ShowEffectTextTyped(cardId, 8);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(cardId);

  setId = FindDmMentionSpellTrapInDeck(turnDuelist);
  if (setId != CARD_NONE)
    SetSpellTrapFromDeck(turnDuelist, setId);

  UpdateDuelGfxExceptField();
}

void DarkMagicianDestroyRevive_EnsureInit(void)
{
  if (sDmDestroyInit)
    return;

  sDmDestroyInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnDmEffectDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_FIELD_CHANGE, OnDmFieldChange);
}

static u8 FieldHasShiningSarcophagus(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == SHINING_SARCOPHAGUS)
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC(void)
{
  if (gMonEffect.id != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateDARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGICEffect(void)
{
  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC, 2);
}

u8 CanSpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id
      != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC)
    return FALSE;

  if (!FieldHasShiningSarcophagus())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(u8 handZone);
u8 TrySpecialSummonDarkMagicianTheMagicianOfBlackMagicFromHand(u8 handZone);
#endif
