#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMorphtronic(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

APPEND_TEXT void EffectMORPHTRONIC_IMPACT_RETURN(void)
{
  u8 handCol = 0xFF;
  u8 i;
  u8 oppBack = WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 shuffled = 0;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);

  Duel_ShowTrapResponseText(MORPHTRONIC_IMPACT_RETURN, gTrapEffectData.originCardId);

  /* ponytail: GY banish SS Morphtronic need GY ignition. Ceiling: shuffle 1
   * Morphtronic from hand into Deck, shuffle up to 2 opp S/T into Deck. */

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && IsMorphtronic(gTurnHands[INACTIVE_DUELIST][i]->id)) {
      handCol = i;
      break;
    }
  }

  if (handCol == 0xFF) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  /* Return Morphtronic to deck (bottom of undrawn pile). */
  {
    u16 cardId = gTurnHands[INACTIVE_DUELIST][handCol]->id;
    u8 deckSize = NumCardsInDeck(fixedDuelist);

    ClearZone(gTurnHands[INACTIVE_DUELIST][handCol]);
    if (deckSize < 40) {
      gDuelDecks[fixedDuelist].cards[deckSize] = cardId;
      /* cardsDrawn unchanged — card sits as undrawn if we prepend carefully.
       * ponytail: naive append as undrawn only if cardsDrawn==deckSize was wrong;
       * place before drawn cursor by shifting. */
      if (gDuelDecks[fixedDuelist].cardsDrawn > 0) {
        /* Insert at cardsDrawn position so it remains in deck. */
        u8 pos = gDuelDecks[fixedDuelist].cardsDrawn;
        u8 k;

        for (k = deckSize; k > pos; k--)
          gDuelDecks[fixedDuelist].cards[k] = gDuelDecks[fixedDuelist].cards[k - 1];
        gDuelDecks[fixedDuelist].cards[pos] = cardId;
      }
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW && shuffled < 2; i++) {
    struct DuelCard *zone = gFixedZones[oppBack][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL
        && GetTypeGroup(zone->id) != TYPE_GROUP_TRAP)
      continue;
    /* Shuffle into Deck stand-in: clear without GY. */
    ClearZone(zone);
    shuffled++;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
