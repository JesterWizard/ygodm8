#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectSNAKE_WHISTLE(void)
{
  u8 fixedDuelist;
  u8 deckSize;
  u8 top;
  u8 i;
  struct DuelSummonOpts opts;

  Duel_ShowTrapResponseText(SNAKE_WHISTLE, gTrapEffectData.originCardId);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  fixedDuelist =
      (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_CardHasMonsterType(cardId, TYPE_REPTILE))
      continue;
    SetCardInfo(cardId);
    if (gCardInfo.level == 0 || gCardInfo.level > 4)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);
    break;
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
