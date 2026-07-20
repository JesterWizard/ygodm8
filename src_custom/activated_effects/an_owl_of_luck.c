#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(cardId) == SPELL_TYPE_INVALID;
}

static u16 FindDeckFieldSpellIndex(u8 fixedDuelist, u8 *outIndex)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFieldSpell(cardId)) {
      *outIndex = i;
      return cardId;
    }
  }

  return CARD_NONE;
}

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 MoveDeckFieldSpellToTop(u8 fixedDuelist, u8 deckIndex, u16 cardId)
{
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  PlaceCardOnDeckTop(fixedDuelist, cardId);
  return TRUE;
}

unsigned char CanActivateAN_OWL_OF_LUCK(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 deckIndex;
  u8 necrovalley;

  if (gMonEffect.id != AN_OWL_OF_LUCK)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AN_OWL_OF_LUCK)
    return FALSE;

  /* ponytail: FLIP trigger needs flip hook. Ceiling: once via usage if Field Spell in Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  if (FindDeckFieldSpellIndex(fixedDuelist, &deckIndex) == CARD_NONE)
    return FALSE;

  necrovalley = Duel_IsBackrowCardOnField(NECROVALLEY, TRUE);
  if (necrovalley && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return TRUE;
}

void ActivateAN_OWL_OF_LUCKEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckIndex;
  u16 fieldSpellId;

  Duel_ShowEffectTextTyped(AN_OWL_OF_LUCK, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  fieldSpellId = FindDeckFieldSpellIndex(fixedDuelist, &deckIndex);
  if (fieldSpellId == CARD_NONE)
    return;

  if (Duel_IsBackrowCardOnField(NECROVALLEY, TRUE)) {
    if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
      return;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, fieldSpellId, TRUE) != DUEL_ACTION_OK)
      return;
  } else if (!MoveDeckFieldSpellToTop(fixedDuelist, deckIndex, fieldSpellId)) {
    return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
