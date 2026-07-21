#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 IsDarkSpellcasterLv7OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER))
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_SHADOW)
    return FALSE;
  if (gCardInfo.level == 0 || gCardInfo.level > 7)
    return FALSE;

  return TRUE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindDeckDarkSpellcaster(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsDarkSpellcasterLv7OrLower(gDuelDecks[fixedDuelist].cards[i])
        && !Duel_CardCannotBeSpecialSummoned(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

APPEND_TEXT void EffectMAGICIAN_NAVIGATION(void)
{
  struct DuelSummonOpts opts;
  u16 deckId;

  Duel_ShowTrapResponseText(MAGICIAN_NAVIGATION, gTrapEffectData.originCardId);

  if (!ArchlordKristya_IsSpecialSummonLocked()) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonFromHand(INACTIVE_DUELIST, DARK_MAGICIAN, NULL, opts);

    deckId = FindDeckDarkSpellcaster(INACTIVE_DUELIST);
    if (deckId != CARD_NONE
        && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0)
      Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, deckId, opts);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
