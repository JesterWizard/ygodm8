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

APPEND_TEXT void EffectDAMAGE_EQUALS_REPTILE(void)
{
  struct DuelSummonOpts opts;
  u16 cardId;
  u16 maxAtk = 500;
  struct DuelCard *zone;

  Duel_ShowTrapResponseText(DAMAGE_EQUALS_REPTILE, gTrapEffectData.originCardId);

  /* Same printed text as Damage = Reptile; OPT battle-damage trigger. */
  if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
    SetCardInfo(gTrapEffectData.originCardId);
    maxAtk = gCardInfo.atk;
  }

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    cardId = FindReptileAtkOrLess(INACTIVE_DUELIST, maxAtk);
    if (cardId != CARD_NONE) {
      opts = Duel_DefaultSpecialSummonOpts(TRUE);
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);
    }
  }

  zone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (zone != NULL)
    Duel_ActivateContinuousZone(zone);

  UpdateDuelGfxExceptField();

  /* ponytail: battle-damage involving Reptile trigger + OPT. */
}
