#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDivaDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT))
    return FALSE;
  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 1 && gCardInfo.level <= 3;
}

static u16 FindDeckDivaTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsDivaDeckTarget(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

unsigned char CanActivateDEEP_SEA_DIVA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DEEP_SEA_DIVA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DEEP_SEA_DIVA)
    return FALSE;

  /* ponytail: Normal Summon trigger needs summon hook. Ceiling: once via usage
   * while face-up if Lv≤3 Sea Serpent in Deck. */
  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FindDeckDivaTarget() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateDEEP_SEA_DIVAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(DEEP_SEA_DIVA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckDivaTarget();
  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
