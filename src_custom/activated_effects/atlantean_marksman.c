#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAtlanteanName[] APPEND_RODATA = "Atlantean";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAtlanteanSeaSerpent(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT))
    return FALSE;

  return Duel_CardNameContains(cardId, sAtlanteanName);
}

static u16 FindDeckTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == ATLANTEAN_MARKSMAN)
      continue;

    if (!IsAtlanteanSeaSerpent(cardId))
      continue;

    if (gCardData_NEW[cardId].level == 0 || gCardData_NEW[cardId].level > 4)
      continue;

    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateATLANTEAN_MARKSMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ATLANTEAN_MARKSMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ATLANTEAN_MARKSMAN)
    return FALSE;

  /* ponytail: battle-damage trigger + sent-for-WATER destroy Set S/T need
   * battle/send hooks. Ceiling: OPT SS Lv≤4 Atlantean Sea Serpent from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindDeckTarget() != CARD_NONE;
}

void ActivateATLANTEAN_MARKSMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;

  Duel_ShowEffectTextTyped(ATLANTEAN_MARKSMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckTarget();
  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
