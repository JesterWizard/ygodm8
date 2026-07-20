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

static u16 FindReptileAtkOrLess(u8 turnDuelist, u16 maxAtk)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_CardHasMonsterType(cardId, TYPE_REPTILE))
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;
    SetCardInfo(cardId);
    if (gCardInfo.atk <= maxAtk)
      return cardId;
  }

  return CARD_NONE;
}

APPEND_TEXT void EffectDAMAGE_REPTILE(void)
{
  struct DuelSummonOpts opts;
  u16 cardId;
  u16 maxAtk = 0;

  Duel_ShowTrapResponseText(DAMAGE_REPTILE, gTrapEffectData.originCardId);

  /* ponytail: OPT when take battle damage involving Reptile. Ceiling: when
   * Effect runs, SS Reptile from Deck with ATK ≤ a stand-in damage amount
   * (origin ATK if monster); upgrade: battle-damage hook stores damage. */

  if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
    SetCardInfo(gTrapEffectData.originCardId);
    maxAtk = gCardInfo.atk;
  }

  if (maxAtk == 0)
    maxAtk = 500;

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    cardId = FindReptileAtkOrLess(INACTIVE_DUELIST, maxAtk);
    if (cardId != CARD_NONE) {
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);
    }
  }

  /* Continuous OPT — stay face-up. */
  {
    struct DuelCard *zone =
        gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

    if (zone != NULL)
      Duel_ActivateContinuousZone(zone);
  }

  UpdateDuelGfxExceptField();
}
