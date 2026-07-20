#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDarkSpellcaster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 IsSpellcasterMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

APPEND_TEXT void EffectDARK_RENEWAL(void)
{
  u8 col;
  u8 myRow = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *mySpellcaster = NULL;
  struct DuelCard *oppSummoned;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u16 ssId = CARD_NONE;
  u8 i;

  Duel_ShowTrapResponseText(DARK_RENEWAL, gTrapEffectData.originCardId);

  /* ponytail: on opp NS/SS. Ceiling: send origin + your Spellcaster → GY, then
   * SS DARK Spellcaster from Deck/GY; upgrade: summon trigger wire. */

  oppSummoned = gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[myRow][col];

    if (zone != NULL && IsSpellcasterMonster(zone->id)) {
      mySpellcaster = zone;
      break;
    }
  }

  if (oppSummoned != NULL && GetTypeGroup(oppSummoned->id) == TYPE_GROUP_MONSTER)
    Duel_DestroyZone(oppSummoned, ACTIVE_DUELIST, FALSE);
  if (mySpellcaster != NULL)
    Duel_DestroyZone(mySpellcaster, INACTIVE_DUELIST, FALSE);

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);

    /* Prefer GY then Deck. */
    if (GraveyardExpand_IsEnabled()) {
      for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
        if (IsDarkSpellcaster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
          ssId = GraveyardExpand_GetCardAt(fixedDuelist, i);
          break;
        }
      }
    }

    if (ssId != CARD_NONE)
      Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, ssId, opts);
    else {
      u8 deckSize = NumCardsInDeck(fixedDuelist);
      u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

      for (i = top; i < deckSize; i++) {
        if (IsDarkSpellcaster(gDuelDecks[fixedDuelist].cards[i])) {
          ssId = gDuelDecks[fixedDuelist].cards[i];
          break;
        }
      }
      if (ssId != CARD_NONE)
        Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, ssId, opts);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
