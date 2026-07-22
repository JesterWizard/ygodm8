#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 IsLv5PlusGladiatorBeast(u16 cardId)
{
  if (!IsGladiatorBeastMonster(cardId))
    return FALSE;

  if (cardId == GLADIATOR_BEAST_TAMER_EDITOR)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 5;
}

static u16 FindLv5PlusGbInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLv5PlusGladiatorBeast(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateGLADIATOR_BEAST_TAMER_EDITOR(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_TAMER_EDITOR)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_TAMER_EDITOR)
    return FALSE;

  /* Ceiling: OPT SS Lv≥5 GB from Deck (Extra stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindLv5PlusGbInDeck() != CARD_NONE;
}

void ActivateGLADIATOR_BEAST_TAMER_EDITOREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 ssId;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_TAMER_EDITOR, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  ssId = FindLv5PlusGbInDeck();
  if (ssId == CARD_NONE)
    return;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, ssId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
