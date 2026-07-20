#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

unsigned char CanActivateRINYAN_LIGHTSWORN_ROGUE(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 i;

  if (gMonEffect.id != RINYAN_LIGHTSWORN_ROGUE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RINYAN_LIGHTSWORN_ROGUE)
    return FALSE;

  /* ponytail: FLIP trigger needs flip hook. Ceiling: once via usage if LS in GY. */
  if (!CanUseMonsterEffect(zone) || !GraveyardExpand_IsEnabled())
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

void ActivateRINYAN_LIGHTSWORN_ROGUEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u16 cardId = CARD_NONE;
  u8 deckSize;

  Duel_ShowEffectTextTyped(RINYAN_LIGHTSWORN_ROGUE, 2);

  if (self == NULL || IsDuelOver() == TRUE || !GraveyardExpand_IsEnabled())
    return;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
      break;
    }
  }

  if (cardId != CARD_NONE) {
    deckSize = NumCardsInDeck(fixedDuelist);
    /* Insert into undrawn portion of deck. */
    if (gDuelDecks[fixedDuelist].cardsDrawn <= deckSize) {
      u8 pos = gDuelDecks[fixedDuelist].cardsDrawn;
      u8 k;

      for (k = deckSize; k > pos; k--)
        gDuelDecks[fixedDuelist].cards[k] = gDuelDecks[fixedDuelist].cards[k - 1];
      gDuelDecks[fixedDuelist].cards[pos] = cardId;
    }

    Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE);
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
