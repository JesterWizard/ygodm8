#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sBlueEyesName[] APPEND_RODATA = "Blue-Eyes";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsBlueEyesFusionMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(cardId, sBlueEyesName);
}

static u16 FindBlueEyesFusionInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsBlueEyesFusionMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 SendBlueEyesFusionFromDeck(u16 cardId)
{
  s16 deckIndex;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  return TRUE;
}

unsigned char CanActivateNEO_BLUE_EYES_ULTIMATE_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NEO_BLUE_EYES_ULTIMATE_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NEO_BLUE_EYES_ULTIMATE_DRAGON)
    return FALSE;

  /* Restricted timing and negation protection are omitted; deck sending grants
   * the current extra-attack marker. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FindBlueEyesFusionInDeck() != CARD_NONE;
}

void ActivateNEO_BLUE_EYES_ULTIMATE_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 sendId;

  Duel_ShowEffectTextTyped(NEO_BLUE_EYES_ULTIMATE_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  sendId = FindBlueEyesFusionInDeck();
  if (sendId == CARD_NONE)
    return;

  if (!SendBlueEyesFusionFromDeck(sendId))
    return;

  /* unk4=2 is the current extra-attack marker. */
  self->unk4 = 2;
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
