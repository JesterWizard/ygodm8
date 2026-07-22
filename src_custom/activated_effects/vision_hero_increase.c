#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sVisionHeroName[] APPEND_RODATA = "Vision HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsVisionHeroLvLe4(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == VISION_HERO_INCREASE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sVisionHeroName))
    return FALSE;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].level > 0 && gCardData_NEW[cardId].level <= 4;
}

static u16 FindVisionHeroLvLe4InDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsVisionHeroLvLe4(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateVISION_HERO_INCREASE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != VISION_HERO_INCREASE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VISION_HERO_INCREASE)
    return FALSE;

  /* Ceiling: GY Continuous Trap place + tribute HERO SS-self FALSE. OPT SS Vision
   * HERO Lv≤4 from Deck (ST-zone SS stand-in; EffectOpt). */
  if (EffectOpt_IsUsed(VISION_HERO_INCREASE))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindVisionHeroLvLe4InDeck() != CARD_NONE;
}

void ActivateVISION_HERO_INCREASEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(VISION_HERO_INCREASE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(VISION_HERO_INCREASE))
    return;

  cardId = FindVisionHeroLvLe4InDeck();
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(VISION_HERO_INCREASE);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
