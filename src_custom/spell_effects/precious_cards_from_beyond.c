#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "precious_cards_from_beyond.h"
#include "imperial_order.h"
#include "tribute.h"
#include "spell_effects.h"

#define PRECIOUS_CARDS_FROM_BEYOND_DRAW_COUNT 2
#define PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES 2

static u8 BackrowForDuelist(u8 duelist)
{
  return (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

u8 IsPreciousCardsFromBeyondActiveForDuelist(u8 duelist)
{
  u8 i;
  u8 backrow = BackrowForDuelist(duelist);

  if (IsImperialOrderNegatingSpell(PRECIOUS_CARDS_FROM_BEYOND))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[backrow][i]->id == PRECIOUS_CARDS_FROM_BEYOND
        && gFixedZones[backrow][i]->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static void DrawCardsForDuelist(u8 duelist, u8 count)
{
  while (count > 0) {
    if (IsDuelOver() == TRUE)
      return;

    TryDrawingCard(duelist);
    count--;
  }
}

void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist)
{
  if (summonCardId == CARD_NONE)
    return;

  if (GetTypeGroup(summonCardId) != TYPE_GROUP_MONSTER)
    return;

  if (GetNumRequiredTributes(summonCardId) < PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES)
    return;

  if (!IsPreciousCardsFromBeyondActiveForDuelist(duelist))
    return;

  DrawCardsForDuelist(duelist, PRECIOUS_CARDS_FROM_BEYOND_DRAW_COUNT);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = PRECIOUS_CARDS_FROM_BEYOND;
    ActivateCardEffectText();
  }
}

APPEND_TEXT void EffectPreciousCardsFromBeyond(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = PRECIOUS_CARDS_FROM_BEYOND;
    ActivateCardEffectText();
  }
}

#if !defined(__GNUC__)
void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);
void EffectPreciousCardsFromBeyond(void);
#endif
