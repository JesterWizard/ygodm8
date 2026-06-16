#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

#define MARAUDING_CAPTAIN_MAX_SUMMON_LEVEL 4

static u8 IsMaraudingCaptainSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);

  return gCardInfo.level <= MARAUDING_CAPTAIN_MAX_SUMMON_LEVEL;
}

static u8 HandHasMaraudingCaptainTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMaraudingCaptainSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 CanSpecialSummonForDuelist(u8 duelist)
{
  u8 monsterRow = duelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (!HandHasMaraudingCaptainTarget(gTurnHands[duelist]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return TRUE;
}

static s8 PickMaraudingCaptainHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsMaraudingCaptainSummonTarget(cardId))
      continue;

    if (!pickHighestAtk)
      return i;

    SetCardInfo(cardId);
    if (chosenZone < 0 || gCardInfo.atk > bestAtk) {
      chosenZone = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenZone;
}

static void TrySpecialSummonForDuelist(u8 duelist)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  s8 handZone;

  if (!CanSpecialSummonForDuelist(duelist))
    return;

  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    handZone = SelectHandCardMatchingPredicate(handRow, IsMaraudingCaptainSummonTarget);
  else
    handZone = PickMaraudingCaptainHandZone(handRow, TRUE);

  if (handZone < 0)
    return;

  Duel_SpecialSummonFromHandZone(duelist, handZone, opts);
}

unsigned char ShouldActivateMaraudingCaptain(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != MARAUDING_CAPTAIN)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return CanSpecialSummonForDuelist(duelist);
}

void ActivateMaraudingCaptain(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectText(MARAUDING_CAPTAIN);
  TrySpecialSummonForDuelist(duelist);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  zone->unk4 = 1;
}
