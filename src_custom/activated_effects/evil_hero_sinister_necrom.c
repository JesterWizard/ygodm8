#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sEvilHeroArchetypeName[] APPEND_RODATA = "Evil HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsEvilHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == EVIL_HERO_SINISTER_NECROM)
    return FALSE;

  return Duel_CardNameContains(cardId, sEvilHeroArchetypeName);
}

static s16 FindSinisterNecromInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == EVIL_HERO_SINISTER_NECROM)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == EVIL_HERO_SINISTER_NECROM)
      return (s16)i;
  }

  return -1;
}

static u8 HandHasEvilHero(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsEvilHeroMonster(SixCardHand_ZoneAtHandRow(handRow, i)->id))
      return TRUE;
  }

  return FALSE;
}

static s16 FindEvilHeroDeckIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsEvilHeroMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static s8 PickEvilHeroHandZoneForAi(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsEvilHeroMonster(SixCardHand_ZoneAtHandRow(handRow, i)->id))
      return (s8)i;
  }

  return -1;
}

unsigned char CanActivateEVIL_HERO_SINISTER_NECROM(void)
{
  if (gMonEffect.id != EVIL_HERO_SINISTER_NECROM)
    return FALSE;

  /* Ceiling: GY ignition needs GY-menu wire; allow when Sinister Necrom
   * in GY + Evil HERO in hand or Deck (callable if gMonEffect set). */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindSinisterNecromInGy() < 0)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasEvilHero() || FindEvilHeroDeckIndex() >= 0;
}

void ActivateEVIL_HERO_SINISTER_NECROMEffect(void)
{
  s16 gyIndex;
  s8 handZone;
  s16 deckIndex;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(EVIL_HERO_SINISTER_NECROM, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindSinisterNecromInGy();
  if (gyIndex < 0)
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (HandHasEvilHero()) {
    if (WhoseTurn() == DUEL_PLAYER)
      handZone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsEvilHeroMonster);
    else
      handZone = PickEvilHeroHandZoneForAi();

    if (handZone >= 0) {
      Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
      UpdateDuelGfxExceptField();
      return;
    }
  }

  deckIndex = FindEvilHeroDeckIndex();
  if (deckIndex < 0)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, gDuelDecks[fixedDuelist].cards[deckIndex], opts);
  UpdateDuelGfxExceptField();
}
