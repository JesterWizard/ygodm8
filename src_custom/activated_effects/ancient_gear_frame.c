#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearGolemName[] APPEND_RODATA = "Ancient Gear Golem";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGolemOrSpellTrapMentioningGolem(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_FRAME)
    return FALSE;

  if (cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM)
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearGolemName);
}

static u16 FindSearchTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGolemOrSpellTrapMentioningGolem(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateANCIENT_GEAR_FRAME(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_FRAME)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_FRAME)
    return FALSE;

  /* ponytail: attack S/T lock + leave-field SS FALSE.
   * Ceiling: OPT discard 1 → add AG Golem or S/T mentioning Golem from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 1)
    return FALSE;

  return FindSearchTargetInDeck() != CARD_NONE;
}

void ActivateANCIENT_GEAR_FRAMEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_FRAME, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  searchId = FindSearchTargetInDeck();
  if (searchId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
