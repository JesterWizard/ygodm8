#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sNeosName[] APPEND_RODATA = "Neos";
static const char sHeroName[] APPEND_RODATA = "HERO";

static u8 IsNeosRelatedSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  if (Duel_CardNameContains(cardId, sNeosName))
    return TRUE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u16 FindNeosRelatedSpellTrapInDeck(void)
{
  u8 fixedDuelist;
  u8 deckSize;
  u8 top;
  u8 i;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsNeosRelatedSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateELEMENTAL_HERO_BRAVE_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_BRAVE_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_BRAVE_NEOS)
    return FALSE;

  /* ponytail: +100 ATK per Neo-Spacian/HERO in GY + battle-destroy search gate
   * need stat/battle hooks. Ceiling: OPT add 1 Neos/HERO Spell/Trap from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindNeosRelatedSpellTrapInDeck() != CARD_NONE;
}

void ActivateELEMENTAL_HERO_BRAVE_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_BRAVE_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  searchId = FindNeosRelatedSpellTrapInDeck();
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
