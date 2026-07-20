#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

static const char sDarkFusionName[] APPEND_RODATA = "Dark Fusion";

static u8 IsDarkFusionOrRelated(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId == EVIL_HERO_ADUSTED_GOLD)
    return FALSE;

  if (cardId == DARK_FUSION || cardId == SUPREME_KINGS_CASTLE)
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sDarkFusionName);
}

static u16 FindDarkFusionSearchTarget(void)
{
  u8 fixedDuelist;
  u8 deckSize;
  u8 top;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_FUSION) >= 0)
    return DARK_FUSION;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, SUPREME_KINGS_CASTLE) >= 0)
    return SUPREME_KINGS_CASTLE;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDarkFusionOrRelated(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateEVIL_HERO_ADUSTED_GOLD(void)
{
  if (gMonEffect.id != EVIL_HERO_ADUSTED_GOLD)
    return FALSE;

  /* ponytail: cannot attack without Fusion Monster needs attack gate hook.
   * Ceiling: not field-ignition activatable; discard search uses FromHand path. */
  return FALSE;
}

void ActivateEVIL_HERO_ADUSTED_GOLDEffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_ADUSTED_GOLD, 2);
}

u8 CanActivateEvilHeroAdustedGoldFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != EVIL_HERO_ADUSTED_GOLD)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  /* ponytail: once-per-turn not tracked without turn hook. */
  return FindDarkFusionSearchTarget() != CARD_NONE;
}

u8 TryActivateEvilHeroAdustedGoldFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u16 searchId;

  if (!CanActivateEvilHeroAdustedGoldFromHand(handZone))
    return FALSE;

  searchId = FindDarkFusionSearchTarget();
  if (searchId == CARD_NONE)
    return FALSE;

  Duel_ShowEffectTextTyped(EVIL_HERO_ADUSTED_GOLD, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE);
  return TRUE;
}
