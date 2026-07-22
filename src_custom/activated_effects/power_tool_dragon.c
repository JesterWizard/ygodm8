#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsEquipSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(cardId) == SPELL_TYPE_EQUIP;
}

static u16 FindDeckEquipSpell(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsEquipSpell(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivatePOWER_TOOL_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != POWER_TOOL_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != POWER_TOOL_DRAGON)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDeckEquipSpell() != CARD_NONE;
}

void ActivatePOWER_TOOL_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 equipId;

  Duel_ShowEffectTextTyped(POWER_TOOL_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  equipId = FindDeckEquipSpell();
  if (equipId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, equipId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
