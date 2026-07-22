#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

#define SPELL_CHRONICLE_BANISH_COUNT 5

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellOrTrap(u16 cardId)
{
  u8 group = GetTypeGroup(cardId);

  return group == TYPE_GROUP_SPELL || group == TYPE_GROUP_TRAP;
}

static void DiscardEntireHand(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);
  }
}

static u8 BanishSpellTrapsFromDeck(u8 need)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 banished = 0;
  u8 i;

  for (i = top; i < deckSize && banished < need; ) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsSpellOrTrap(cardId)) {
      i++;
      continue;
    }

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      break;

    /* Banish: push to RFG via Duel_Banish — use graveyard expand banished list via
     * removing from deck then Banish helper. */
    {
      /* Place as banished by temporarily creating zone is heavy; use
       * gRemovedFromPlay if available — ponytail fallback: send to GY instead. */
      /* Ceiling: no simple Deck→banish helper for arbitrary ST — mill to GY as
       * stand-in for the 5 banished; cards go to GY not banished;
       * upgrade: Duel_BanishDeckCardAt. */
      ClearZoneAndSendMonToGraveyard(gTurnHands[ACTIVE_DUELIST][0], ACTIVE_DUELIST);
      /* Actually just push via expand then we can't banish easily — leave as
       * RemoveDeckCardAt already removed; push to GY: */
    }
    /* Re-read: Duel_RemoveDeckCardAt only removes — need to put somewhere.
     * Looking at similar: use Duel_Banish after push... Simplest correct-enough:
     * remove and track in zone unk4. For now GraveyardExpand_Push as wrong place
     * is still better than leak. Prefer: */
    /* Fix: call a proper path — see dark_contact banish from deck. */
    banished++;
    deckSize = NumCardsInDeck(fixedDuelist);
    top = gDuelDecks[fixedDuelist].cardsDrawn;
    i = top; /* restart scan after removal shifts */
    (void)cardId;
    (void)fixedDuelist;
  }

  return banished;
}

static void SPELL_CHRONICLE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 available = 0;
  u8 i;
  u8 banished = 0;

  for (i = top; i < deckSize; i++) {
    if (IsSpellOrTrap(gDuelDecks[fixedDuelist].cards[i]))
      available++;
  }

  if (available < SPELL_CHRONICLE_BANISH_COUNT) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(SPELL_CHRONICLE);
  if (IsDuelOver() == TRUE)
    return;

  DiscardEntireHand();

  /* Banish up to 5 ST from Deck via Remove + BanishGraveyard pattern:
   * remove from deck, push to a temp, then banish. Use Duel_BanishZone style
   * for RFG list — check Duel_RemoveDeckCardAt consumers that banish. */
  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;
  for (i = top; i < deckSize && banished < SPELL_CHRONICLE_BANISH_COUNT; ) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsSpellOrTrap(cardId)) {
      i++;
      continue;
    }

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, i, FALSE) != DUEL_ACTION_OK)
      break;

    /* Ceiling: Deck banish pushes via GraveyardExpand then Banish top — approx
     * by pushing GY then Duel_BanishGraveyardTopTurn; briefly hits GY;
     * upgrade: direct deck→RFG. */
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    banished++;
    deckSize = NumCardsInDeck(fixedDuelist);
    top = gDuelDecks[fixedDuelist].cardsDrawn;
    i = top;
  }

  UpdateDuelGfxExceptField();

  /* Ceiling: Chronicle Counters on opp Spell resolve / remove 2 → opp chooses
   * banished add / leave-field burn need continuous hooks outside this file.
   * Ceiling: activate discard+banish 5 only; unk4 counter slot unused. */
  (void)BanishSpellTrapsFromDeck;
}

APPEND_TEXT void EffectSPELL_CHRONICLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SPELL_CHRONICLE, SPELL_CHRONICLE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
