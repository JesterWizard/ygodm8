#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "thousand_energy.h"

#define THOUSAND_ENERGY_MAX_LEVEL 2
#define THOUSAND_ENERGY_STAGE_BOOST 2

static u8 MonsterRowForDuelist(u8 duelist)
{
  return duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 DuelistForFixedMonsterRow(u8 row)
{
  return row == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;
}

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
  gThousandEnergyDestroyMask = 0;
  gThousandEnergyFixedMonsterRow = 0;
}

void DestroyThousandEnergyMonstersAtEndOfTurn(void)
{
  u8 i;
  u8 row;
  u8 duelist;

  if (gThousandEnergyDestroyMask == 0)
    return;

  row = gThousandEnergyFixedMonsterRow;
  duelist = DuelistForFixedMonsterRow(row);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone;

    if (!(gThousandEnergyDestroyMask & (1 << i)))
      continue;

    zone = gFixedZones[row][i];
    if (zone->id != CARD_NONE)
      ClearZoneAndSendMonToGraveyard(zone, duelist);
  }

  ResetThousandEnergyState();
}

APPEND_TEXT void EffectThousandEnergy(void)
{
  u8 i;
  u8 monsterRow;
  u8 duelist = WhoseTurn();

  ResetThousandEnergyState();
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  monsterRow = MonsterRowForDuelist(duelist);
  gThousandEnergyFixedMonsterRow = monsterRow;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];

    if (!MonsterQualifiesForThousandEnergy(zone->id))
      continue;

    BoostMonsterStages(zone);
    gThousandEnergyDestroyMask |= (1 << i);
  }

  RefreshFieldMonsterStatOverlays();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = THOUSAND_ENERGY;
    ActivateCardEffectText();
  }
}
