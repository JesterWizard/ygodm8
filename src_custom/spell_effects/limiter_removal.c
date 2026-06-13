#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "limiter_removal.h"
#include "mini_card.h"
#include "riryoku.h"
#include "spell_effects.h"

static u8 MonsterRowForDuelist(u8 duelist)
{
  return duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 DuelistForFixedMonsterRow(u8 row)
{
  return row == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 MonsterQualifiesForLimiterRemoval(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_MACHINE;
}

static u16 GetMonsterCurrentAtk(struct DuelCard *zone)
{
  u16 atk;

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;
  gSetFinalStatZone = NULL;
  return atk;
}

void ResetLimiterRemovalState(void)
{
  gLimiterRemovalDestroyMask = 0;
  gLimiterRemovalFixedMonsterRow = 0;
}

void DestroyLimiterRemovalMonstersAtEndOfTurn(void)
{
  u8 i;
  u8 row;
  u8 duelist;

  if (gLimiterRemovalDestroyMask == 0)
    return;

  row = gLimiterRemovalFixedMonsterRow;
  duelist = DuelistForFixedMonsterRow(row);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone;

    if (!(gLimiterRemovalDestroyMask & (1 << i)))
      continue;

    zone = gFixedZones[row][i];
    if (zone->id != CARD_NONE)
      ClearZoneAndSendMonToGraveyard(zone, duelist);
  }

  ResetLimiterRemovalState();
}

APPEND_TEXT void EffectLimiterRemoval(void)
{
  u8 i;
  u8 monsterRow;
  u8 duelist = WhoseTurn();

  ResetLimiterRemovalState();
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  monsterRow = MonsterRowForDuelist(duelist);
  gLimiterRemovalFixedMonsterRow = monsterRow;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];
    u16 atk;

    if (!MonsterQualifiesForLimiterRemoval(zone->id))
      continue;

    atk = GetMonsterCurrentAtk(zone);
    if (atk > 0)
      AddRiryokuAtkDelta(zone, (s16)atk);

    gLimiterRemovalDestroyMask |= (1 << i);
  }

  RefreshFieldMonsterStatOverlays();

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = LIMITER_REMOVAL;
    ActivateCardEffectText();
  }
}
