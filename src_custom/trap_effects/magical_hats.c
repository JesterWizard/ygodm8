#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

APPEND_TEXT void EffectMAGICAL_HATS(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 spellTrapIds[2];
  u8 spellTrapIdx[2];
  u8 found = 0;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *monster = NULL;
  u8 col;
  s8 empty;

  Duel_ShowTrapResponseText(MAGICAL_HATS, gTrapEffectData.originCardId);

  for (i = top; i < deckSize && found < 2; i++) {
    u16 id = gDuelDecks[fixedDuelist].cards[i];
    u8 tg = GetTypeGroup(id);

    if (tg == TYPE_GROUP_SPELL || tg == TYPE_GROUP_TRAP) {
      spellTrapIds[found] = id;
      spellTrapIdx[found] = i;
      found++;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER) {
      monster = zone;
      break;
    }
  }

  if (monster != NULL) {
    monster->isFaceUp = FALSE;
    monster->isDefending = TRUE;
  }

  for (i = 0; i < found; i++) {
    empty = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
    if (empty < 0 || ArchlordKristya_IsSpecialSummonLocked())
      break;
    /* Indices shift after remove — re-find by id each time from top. */
    {
      u8 j;
      u8 idx = 0xFF;
      u8 ds = NumCardsInDeck(fixedDuelist);
      u8 tp = gDuelDecks[fixedDuelist].cardsDrawn;

      for (j = tp; j < ds; j++) {
        if (gDuelDecks[fixedDuelist].cards[j] == spellTrapIds[i]) {
          idx = j;
          break;
        }
      }
      if (idx == 0xFF)
        continue;
      if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, idx, FALSE) != DUEL_ACTION_OK)
        continue;
    }
    {
      struct DuelCard *slot = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][empty];

      slot->id = spellTrapIds[i];
      slot->isFaceUp = FALSE;
      slot->isDefending = TRUE;
      slot->isLocked = FALSE;
      slot->unk4 = 1; /* hat token mark — destroy EoBP */
      ResetPermStage(slot);
      ResetTempStage(slot);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
