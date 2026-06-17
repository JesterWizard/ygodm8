#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "precious_cards_from_beyond.h"
#include "imperial_order.h"
#include "summon_tribute.h"
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

u8 IsActivatedPreciousCardsFromBeyondZone(const struct DuelCard *zone)
{
  return zone != NULL
      && zone->id == PRECIOUS_CARDS_FROM_BEYOND
      && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE;
}

void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist)
{
  u8 paidTributes;

  if (summonCardId == CARD_NONE)
    return;

  if (GetTypeGroup(summonCardId) != TYPE_GROUP_MONSTER)
    return;

  paidTributes = GetPendingSummonTributeCount();

  if (GetNumRequiredTributes(summonCardId) < PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES)
    return;

  if (GetDoubleCostonDarkBonusPaid() > 0
      && CardQualifiesForDoubleCostonDarkBonus(summonCardId))
    paidTributes += GetDoubleCostonDarkBonusPaid();

  if (paidTributes < PRECIOUS_CARDS_FROM_BEYOND_MIN_TRIBUTES)
    return;

  if (!IsPreciousCardsFromBeyondActiveForDuelist(duelist))
    return;

  if (Duel_DrawCards(duelist, PRECIOUS_CARDS_FROM_BEYOND_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectText(PRECIOUS_CARDS_FROM_BEYOND);
}

APPEND_TEXT void EffectPreciousCardsFromBeyond(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(PRECIOUS_CARDS_FROM_BEYOND);
}

#if !defined(__GNUC__)
void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);
void EffectPreciousCardsFromBeyond(void);
#endif
