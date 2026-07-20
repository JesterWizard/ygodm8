#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sCyberDragonName[] APPEND_RODATA = "Cyber Dragon";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 IsCyberDragonCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == CYBER_DRAGON)
    return TRUE;

  return Duel_CardNameContains(cardId, sCyberDragonName);
}

static u8 IsValidCyberDragonTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCyberDragonCard(zone->id);
}

static u8 CountCyberDragonTributes(void)
{
  u8 col;
  u8 count = 0;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCyberDragonTributeZone(row, col))
      count++;
  }

  return count;
}

static u8 HandHasCyberLaserDragon(void)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], CYBER_LASER_DRAGON);
}

static u8 GraveHasCyberLaserDragon(void)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == CYBER_LASER_DRAGON;

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == CYBER_LASER_DRAGON)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonCyberLaserDragon(void)
{
  if (HandHasCyberLaserDragon())
    return TRUE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, CYBER_LASER_DRAGON) >= 0)
    return TRUE;

  return GraveHasCyberLaserDragon();
}

static u8 IsCyberLaserDragon(u16 cardId)
{
  return cardId == CYBER_LASER_DRAGON;
}

static s8 PickCyberLaserDragonHandZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == CYBER_LASER_DRAGON)
      return i;
  }

  return -1;
}

static void SpecialSummonCyberLaserDragonFromGrave(struct DuelSummonOpts opts)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 count;
  u8 i;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CYBER_LASER_DRAGON, opts);
    return;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != CYBER_LASER_DRAGON)
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    if (cardId == CYBER_LASER_DRAGON)
      Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
    return;
  }
}

static void SpecialSummonCyberLaserDragon(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonCyberLaserDragon())
    return;

  if (HandHasCyberLaserDragon()) {
    if (WhoseTurn() == DUEL_PLAYER) {
      Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CYBER_LASER_DRAGON, IsCyberLaserDragon, opts);
      return;
    }

    {
      s8 handZone = PickCyberLaserDragonHandZone();

      if (handZone >= 0)
        Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
    }
    return;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, CYBER_LASER_DRAGON) >= 0) {
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, CYBER_LASER_DRAGON, opts);
    return;
  }

  SpecialSummonCyberLaserDragonFromGrave(opts);
}

u8 CanActivatePHOTON_GENERATOR_UNIT(void)
{
  if (CountCyberDragonTributes() < 2)
    return FALSE;

  return CanSpecialSummonCyberLaserDragon();
}

static void DestroyPhotonSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == PHOTON_GENERATOR_UNIT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishPhotonGeneratorUnit(u8 trib2Row, u8 trib2Col)
{
  u8 trib1Row = gSpellEffectData.row2;
  u8 trib1Col = gSpellEffectData.col2;
  struct DuelCard *trib1;
  struct DuelCard *trib2;

  if (!IsValidCyberDragonTributeZone(trib1Row, trib1Col)
      || !IsValidCyberDragonTributeZone(trib2Row, trib2Col)) {
    DestroyPhotonSpellZone();
    return;
  }

  if (trib1Row == trib2Row && trib1Col == trib2Col) {
    DestroyPhotonSpellZone();
    return;
  }

  if (!CanSpecialSummonCyberLaserDragon()) {
    DestroyPhotonSpellZone();
    return;
  }

  trib1 = gFixedZones[trib1Row][trib1Col];
  trib2 = gFixedZones[trib2Row][trib2Col];

  DestroyPhotonSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(trib1, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyZone(trib2, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonCyberLaserDragon();
}

static void CancelPhotonTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyPhotonSpellZone();
}

static u8 IsValidSecondCyberDragonTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidCyberDragonTributeZone(fixedRow, fixedCol))
    return FALSE;

  return !(fixedRow == gSpellEffectData.row2 && fixedCol == gSpellEffectData.col2);
}

static u8 AiPickCyberDragonTribute(u8 *outRow, u8 *outCol, u8 excludeFirst)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (excludeFirst) {
      if (!IsValidSecondCyberDragonTribute(row, col))
        continue;
    } else if (!IsValidCyberDragonTributeZone(row, col)) {
      continue;
    }

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static u8 AiPickFirstCyberDragon(u8 *outRow, u8 *outCol)
{
  return AiPickCyberDragonTribute(outRow, outCol, FALSE);
}

static u8 AiPickSecondCyberDragon(u8 *outRow, u8 *outCol)
{
  return AiPickCyberDragonTribute(outRow, outCol, TRUE);
}

static void ResolveSecondCyberDragonTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidSecondCyberDragonTribute(fixedRow, fixedCol))
    return;

  FinishPhotonGeneratorUnit(fixedRow, fixedCol);
}

static void BeginSecondCyberDragonPick(void)
{
  Duel_SetupPickZone(IsValidSecondCyberDragonTribute, ResolveSecondCyberDragonTribute,
                     CancelPhotonTargeting, AiPickSecondCyberDragon);
  Duel_EnterPickZoneTargeting();
}

static void ResolveFirstCyberDragonTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidCyberDragonTributeZone(fixedRow, fixedCol))
    return;

  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;

  if (CountCyberDragonTributes() < 2) {
    DestroyPhotonSpellZone();
    return;
  }

  BeginSecondCyberDragonPick();
}

static void ResolvePhotonForAi(void)
{
  u8 row1;
  u8 col1;
  u8 row2;
  u8 col2;

  if (!AiPickFirstCyberDragon(&row1, &col1)) {
    DestroyPhotonSpellZone();
    return;
  }

  gSpellEffectData.row2 = row1;
  gSpellEffectData.col2 = col1;

  if (!AiPickSecondCyberDragon(&row2, &col2)) {
    DestroyPhotonSpellZone();
    return;
  }

  FinishPhotonGeneratorUnit(row2, col2);
}

static void PHOTON_GENERATOR_UNIT_ResolveBody(void)
{
  Duel_ShowEffectText(PHOTON_GENERATOR_UNIT);

  if (IsDuelOver() == TRUE || !CanActivatePHOTON_GENERATOR_UNIT())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolvePhotonForAi();
    return;
  }

  Duel_SetupPickZone(IsValidCyberDragonTributeZone, ResolveFirstCyberDragonTribute,
                     CancelPhotonTargeting, AiPickFirstCyberDragon);
  Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectPHOTON_GENERATOR_UNIT(void)
{
  if (!CanActivatePHOTON_GENERATOR_UNIT()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(PHOTON_GENERATOR_UNIT, PHOTON_GENERATOR_UNIT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void PHOTON_GENERATOR_UNIT_SelfCheck(void)
{
  if (!IsCyberDragonCard(CYBER_DRAGON))
    while (1)
      ;

  if (IsCyberDragonCard(CYBER_LASER_DRAGON))
    while (1)
      ;
}
#endif
