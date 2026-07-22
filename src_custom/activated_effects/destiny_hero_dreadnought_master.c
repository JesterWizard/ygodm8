#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u16 FindDestinyHeroInDeckFor(u8 turnDuelist)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDestinyHeroMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindDestinyHeroInDeck(void)
{
  return FindDestinyHeroInDeckFor(ACTIVE_DUELIST);
}

static u8 AddUpToTwoDestinyHeroFromDeckFor(u8 turnDuelist)
{
  u8 added = 0;
  u16 cardId;

  while (added < 2 && FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0) {
    cardId = FindDestinyHeroInDeckFor(turnDuelist);
    if (cardId == CARD_NONE)
      break;

    if (Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE) != DUEL_ACTION_OK)
      break;

    added++;
  }

  return added > 0;
}

void TryDestinyHeroDreadnoughtMasterOnMonsterPlacement(struct DuelCard *zone,
                                                       enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != DESTINY_HERO_DREADNOUGHT_MASTER || !SummonModeIsSpecial(mode))
    return;

  if (EffectOpt_IsUsed(DESTINY_HERO_DREADNOUGHT_MASTER))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  if (FindDestinyHeroInDeckFor(turnDuelist) == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_MASTER, 8);

  if (!AddUpToTwoDestinyHeroFromDeckFor(turnDuelist))
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DREADNOUGHT_MASTER);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateDESTINY_HERO_DREADNOUGHT_MASTER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DREADNOUGHT_MASTER)
    return FALSE;

  /* On-SS add via TryDestinyHeroDreadnoughtMasterOnMonsterPlacement (EffectOpt).
   * Ceiling: cards-mentioning-D-HERO FALSE.
   * OPT add up to 2 Destiny HERO from Deck (shares EffectOpt). */
  if (EffectOpt_IsUsed(DESTINY_HERO_DREADNOUGHT_MASTER))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindDestinyHeroInDeck() != CARD_NONE;
}

void ActivateDESTINY_HERO_DREADNOUGHT_MASTEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_MASTER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!AddUpToTwoDestinyHeroFromDeckFor(ACTIVE_DUELIST))
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DREADNOUGHT_MASTER);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
