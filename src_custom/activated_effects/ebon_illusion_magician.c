#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellcasterNormal(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == COLOR_NORMAL;
}

static s8 FindSpellcasterNormalHandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsSpellcasterNormal(slot->id)
        && !Duel_CardCannotBeSpecialSummoned(slot->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindSpellcasterNormalInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSpellcasterNormal(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateEBON_ILLUSION_MAGICIAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EBON_ILLUSION_MAGICIAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EBON_ILLUSION_MAGICIAN)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT SS Spellcaster Normal from hand/Deck (detach stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindSpellcasterNormalHandZone() >= 0)
    return TRUE;

  return FindSpellcasterNormalInDeck() != CARD_NONE;
}

void ActivateEBON_ILLUSION_MAGICIANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 handZone;
  u16 deckId;

  Duel_ShowEffectTextTyped(EBON_ILLUSION_MAGICIAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  handZone = FindSpellcasterNormalHandZone();
  if (handZone >= 0) {
    if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)handZone, opts) != DUEL_ACTION_OK)
      return;
  } else {
    deckId = FindSpellcasterNormalInDeck();
    if (deckId == CARD_NONE)
      return;

    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, deckId, opts) != DUEL_ACTION_OK)
      return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
