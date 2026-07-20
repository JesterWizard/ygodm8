#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
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

static u16 FindLv4OrLowerAmazoness(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_IsAmazonessCard(cardId))
      continue;
    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;
    SetCardInfo(cardId);
    if (gCardInfo.level > 0 && gCardInfo.level <= 4)
      return cardId;
  }

  return CARD_NONE;
}

APPEND_TEXT void EffectQUEENS_PAWN(void)
{
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowTrapResponseText(QUEENS_PAWN, gTrapEffectData.originCardId);

  /* ponytail: activate when Amazoness destroys by battle. Ceiling: when Effect
   * runs, Deck SS Lv≤4 Amazoness; upgrade: battle-destroy hook when attacker
   * passes Duel_IsAmazonessCard. */

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    cardId = FindLv4OrLowerAmazoness(INACTIVE_DUELIST);
    if (cardId != CARD_NONE) {
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
