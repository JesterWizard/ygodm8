#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "harpie_lady_elegance_lock.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

APPEND_TEXT void EffectHARPIE_LADY_ELEGANCE(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u16 seen[3];
  u8 seenCount = 0;
  u8 summoned = 0;
  u8 i;
  u16 deckId = CARD_NONE;
  u16 gyId = CARD_NONE;

  Duel_ShowTrapResponseText(HARPIE_LADY_ELEGANCE, gTrapEffectData.originCardId);

  /* Shuffle Sisters into Deck, then SS up to 3 different Harpies from hand/Deck/GY.
   * WIND-only SS lock this turn via HarpieLadyElegance_MarkWindOnlyLock.
   * Ceiling: destroy-search Harpie Spell need hooks. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == HARPIE_LADY_SISTERS) {
      ClearZone(zone);
      break;
    }
  }

  if (ArchlordKristya_IsSpecialSummonLocked()) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  HarpieLadyElegance_MarkWindOnlyLock(INACTIVE_DUELIST);

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  /* Hand */
  for (i = 0; i < MAX_ZONES_IN_ROW && summoned < 3; i++) {
    u16 id;
    u8 j;
    u8 dup = FALSE;

    if (gTurnHands[INACTIVE_DUELIST][i] == NULL)
      continue;
    id = gTurnHands[INACTIVE_DUELIST][i]->id;
    if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
      continue;
    for (j = 0; j < seenCount; j++) {
      if (seen[j] == id)
        dup = TRUE;
    }
    if (dup)
      continue;
    if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;
    if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, id, NULL, opts) != DUEL_ACTION_OK)
      continue;
    seen[seenCount++] = id;
    summoned++;
  }

  /* Deck */
  if (summoned < 3 && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

    for (i = top; i < deckSize; i++) {
      u16 id = gDuelDecks[fixedDuelist].cards[i];
      u8 j;
      u8 dup = FALSE;

      if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
        continue;
      for (j = 0; j < seenCount; j++) {
        if (seen[j] == id)
          dup = TRUE;
      }
      if (dup)
        continue;
      deckId = id;
      break;
    }
    if (deckId != CARD_NONE
        && Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, deckId, opts) == DUEL_ACTION_OK) {
      seen[seenCount++] = deckId;
      summoned++;
    }
  }

  /* GY */
  if (summoned < 3 && GraveyardExpand_IsEnabled()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);
      u8 j;
      u8 dup = FALSE;

      if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
        continue;
      for (j = 0; j < seenCount; j++) {
        if (seen[j] == id)
          dup = TRUE;
      }
      if (dup)
        continue;
      gyId = id;
      break;
    }
    if (gyId != CARD_NONE)
      Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, gyId, opts);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
