#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "thousand_energy.h"

#define THOUSAND_ENERGY_MAX_LEVEL 2
#define THOUSAND_ENERGY_STAGE_BOOST 2

extern u8 gThousandEnergyDestroyMask;
extern u8 gThousandEnergyFixedMonsterRow;

static u8 MonsterQualifiesForThousandEnergy(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= THOUSAND_ENERGY_MAX_LEVEL;
}

static void BoostMonsterStages(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < THOUSAND_ENERGY_STAGE_BOOST; i++)
    IncrementPermStage(zone);
}

void ResetThousandEnergyState(void)
{
  Duel_ResetDestroyMaskState(&gThousandEnergyDestroyMask, &gThousandEnergyFixedMonsterRow);
}

void DestroyThousandEnergyMonstersAtEndOfTurn(void)
{
  Duel_DestroyMaskedMonstersFromState(&gThousandEnergyDestroyMask, &gThousandEnergyFixedMonsterRow);
}

APPEND_TEXT void EffectThousandEnergy(void)
{
  u8 i;
  u8 monsterRow;
  u8 duelist = WhoseTurn();

  Duel_ResetDestroyMaskState(&gThousandEnergyDestroyMask, &gThousandEnergyFixedMonsterRow);
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  monsterRow = Duel_FixedMonsterRowForDuelist(duelist);
  gThousandEnergyFixedMonsterRow = monsterRow;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];

    if (!MonsterQualifiesForThousandEnergy(zone->id))
      continue;

    BoostMonsterStages(zone);
    gThousandEnergyDestroyMask |= (1 << i);
  }

  Duel_ShowEffectText(THOUSAND_ENERGY);
  RefreshFieldMonsterStatOverlays();
}
