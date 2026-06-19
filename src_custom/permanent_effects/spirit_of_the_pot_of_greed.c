#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spirit_of_the_pot_of_greed.h"

extern unsigned char IsSkillDrainActiveOnField(void);

static u8 IsFaceUpAttackSpiritOfThePotOfGreed(const struct DuelCard *zone)
{
  /* ponytail: normal hand summon copies isFaceUp=0; attack-position monsters still count */
  return zone != NULL
      && zone->id == SPIRIT_OF_THE_POT_OF_GREED
      && zone->isDefending == FALSE;
}

static void ShowSpiritOfThePotOfGreedActivationText(void)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  gCardEffectTextData.cardId = SPIRIT_OF_THE_POT_OF_GREED;
  gCardEffectTextData.cardId2 = POT_OF_GREED;
  ActivateCardEffectText();
}

static void TrySpiritOnMonsterRow(u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (!IsFaceUpAttackSpiritOfThePotOfGreed(zone))
      continue;

    ShowSpiritOfThePotOfGreedActivationText();

    if (IsDuelOver() == TRUE)
      return;

    if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

void TrySpiritOfThePotOfGreedAfterPotOfGreed(void)
{
  if (IsSkillDrainActiveOnField())
    return;

  TrySpiritOnMonsterRow(INACTIVE_DUELIST_MONSTER_ROW);
  if (IsDuelOver() == TRUE)
    return;

  TrySpiritOnMonsterRow(ACTIVE_DUELIST_MONSTER_ROW);
}
