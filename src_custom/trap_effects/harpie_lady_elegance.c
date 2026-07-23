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

static u8 NameAlreadySeen(u16 *seen, u8 seenCount, u16 id)
{
  u8 j;

  for (j = 0; j < seenCount; j++) {
    if (seen[j] == id)
      return TRUE;
  }
  return FALSE;
}

/* TCG: 1 each from hand / Deck / GY, different original names. */
APPEND_TEXT void EffectHARPIE_LADY_ELEGANCE(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  struct DuelSummonOpts opts;
  u16 seen[3];
  u8 seenCount = 0;
  u8 i;
  u16 handId = CARD_NONE;
  u16 deckId = CARD_NONE;
  u16 gyId = CARD_NONE;

  Duel_ShowTrapResponseText(HARPIE_LADY_ELEGANCE, gTrapEffectData.originCardId);

  /* Shuffle 1 Sisters from Monster Zone into Deck. */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == HARPIE_LADY_SISTERS) {
      if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
        gDuelDecks[fixedDuelist].cardsDrawn--;
      gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = HARPIE_LADY_SISTERS;
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

  /* 1 from hand */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 id;

    if (gTurnHands[INACTIVE_DUELIST][i] == NULL)
      continue;
    id = gTurnHands[INACTIVE_DUELIST][i]->id;
    if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
      continue;
    handId = id;
    break;
  }
  if (handId != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0
      && Duel_SpecialSummonFromHand(INACTIVE_DUELIST, handId, NULL, opts) == DUEL_ACTION_OK) {
    seen[seenCount++] = handId;
  }

  /* 1 from Deck */
  if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

    for (i = top; i < deckSize; i++) {
      u16 id = gDuelDecks[fixedDuelist].cards[i];

      if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
        continue;
      if (NameAlreadySeen(seen, seenCount, id))
        continue;
      deckId = id;
      break;
    }
    if (deckId != CARD_NONE
        && Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, deckId, opts) == DUEL_ACTION_OK) {
      seen[seenCount++] = deckId;
    }
  }

  /* 1 from GY */
  if (GraveyardExpand_IsEnabled()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (!IsHarpieMonster(id) || id == HARPIE_LADY_SISTERS)
        continue;
      if (NameAlreadySeen(seen, seenCount, id))
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
