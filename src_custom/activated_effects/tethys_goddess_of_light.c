#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "six_card_hand.h"
#include "tethys_goddess_of_light.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 cardId);

static u8 HasEmptyHandSlot(u8 duelist)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[duelist][i].id == CARD_NONE)
      return TRUE;
  }

  if (IsExpandedCardHandEnabled()) {
    for (i = 0; i < MAX_HAND_EXTRA; i++) {
      if (gHandExtraSlots[duelist][i].id == CARD_NONE)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 HasFaceUpTethysOnField(u8 duelist)
{
  u8 i;
  u8 monsterRow = Duel_FixedMonsterRowForDuelist(duelist);
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[monsterRow][i];
    if (zone->id == TETHYS_GODDESS_OF_LIGHT && zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

void TryApplyTethysGoddessOfLightOnDraw(u8 duelist, u16 cardDrawn, u8 handSlot)
{
  struct DuelCard *drawnCard;

  /* opening hand is seeded before duel gfx; skip like Solemn Wishes. */
  if (gDuelDecks[duelist].cardsDrawn <= MAX_ZONES_IN_ROW)
    return;

  /* unk18 != 0 means battle/damage resolution is active. */
  if (gUnk2023EA0.unk18 != 0)
    return;

  if (!HasFaceUpTethysOnField(duelist))
    return;

  if (!Duel_CardHasMonsterType(cardDrawn, TYPE_FAIRY))
    return;

  if (IsSkillDrainActiveOnField() && TryActivateSkillDrainAndNegateCardId(TETHYS_GODDESS_OF_LIGHT))
    return;

  drawnCard = SixCardHand_GetFixed(duelist, handSlot);
  if (drawnCard == NULL || drawnCard->id != cardDrawn)
    return;

  Duel_ShowEffectTextTyped(TETHYS_GODDESS_OF_LIGHT, 2);
  if (IsDuelOver() == TRUE)
    return;

  drawnCard->isFaceUp = TRUE;

  if (!HasEmptyHandSlot(duelist))
    return;

  TryDrawingCard(duelist);
}
