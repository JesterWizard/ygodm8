#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 IsSpellcasterAtk2000OrLess(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.atk <= 2000;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindDeckSpellcaster(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSpellcasterAtk2000OrLess(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

APPEND_TEXT void EffectMAGICIANS_CIRCLE(void)
{
  struct DuelSummonOpts opts;
  u16 myId;
  u16 oppId;

  Duel_ShowTrapResponseText(MAGICIANS_CIRCLE, gTrapEffectData.originCardId);

  /* ponytail: printed trigger is Spellcaster attack declare. Ceiling: when
   * Effect runs, each player Deck SS Spellcaster ≤2000 ATK; upgrade: attack
   * declare hook when attacker is Spellcaster. */

  if (!ArchlordKristya_IsSpecialSummonLocked()) {
    opts = Duel_DefaultSpecialSummonOpts(FALSE);
    myId = FindDeckSpellcaster(INACTIVE_DUELIST);
    if (myId != CARD_NONE
        && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0)
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, myId, opts);

    oppId = FindDeckSpellcaster(ACTIVE_DUELIST);
    if (oppId != CARD_NONE
        && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0)
      Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, oppId, opts);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
