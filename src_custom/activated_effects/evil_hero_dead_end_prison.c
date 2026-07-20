#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHeroName[] APPEND_RODATA = "HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFusionMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == FUSION_CARD;
}

static u8 ControlsFusionMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsFusionMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u16 FindHeroInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsHeroMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 MillHeroFromDeck(u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s16 deckIndex;
  u8 turnDuelist;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
      GraveyardExpand_PushTurn(turnDuelist, cardId);
      break;
    }
  }

  return TRUE;
}

unsigned char CanActivateEVIL_HERO_DEAD_END_PRISON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_DEAD_END_PRISON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_DEAD_END_PRISON)
    return FALSE;

  /* ponytail: Dark Fusion Fusion gate + Fusion-substitute name marker FALSE.
   * Ceiling: OPT mill 1 HERO from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindHeroInDeck() != CARD_NONE;
}

void ActivateEVIL_HERO_DEAD_END_PRISONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 heroId;

  Duel_ShowEffectTextTyped(EVIL_HERO_DEAD_END_PRISON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  heroId = FindHeroInDeck();
  if (heroId == CARD_NONE)
    return;

  if (!MillHeroFromDeck(heroId))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonEvilHeroDeadEndPrisonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != EVIL_HERO_DEAD_END_PRISON)
    return FALSE;

  /* ponytail: Dark Fusion Fusion markers missing; any Fusion Monster stand-in. */
  if (!ControlsFusionMonster())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonEvilHeroDeadEndPrisonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonEvilHeroDeadEndPrisonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(EVIL_HERO_DEAD_END_PRISON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonEvilHeroDeadEndPrisonFromHand(u8 handZone);
u8 TrySpecialSummonEvilHeroDeadEndPrisonFromHand(u8 handZone);
#endif
