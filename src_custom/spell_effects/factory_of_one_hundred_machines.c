#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* 1 stage ~= 500 ATK. Printed +200 per banished Morphtronic. */
#define FACTORY_ATK_STAGES_PER_BANISH 1

static const char sMorphtronicArchetypeName[] APPEND_RODATA = "Morphtronic";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicArchetypeName);
}

static u8 IsFaceUpMachineMonster(struct DuelCard *zone)
{
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!MonsterIsFaceUp(zone))
    return FALSE;

  return Duel_CardHasMonsterType(zone->id, TYPE_MACHINE);
}

static u8 IsValidFactoryTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  return IsFaceUpMachineMonster(gFixedZones[fixedRow][fixedCol]);
}

static u8 HasFactoryTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidFactoryTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasMorphtronic(u8 fixedDuelist)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled())
    return IsMorphtronicMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsMorphtronicMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateFACTORY_OF_ONE_HUNDRED_MACHINES(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  return HasFactoryTarget() && GyHasMorphtronic(fixedDuelist);
}

static void DestroyFactorySpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == FACTORY_OF_ONE_HUNDRED_MACHINES)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 BanishAllMorphtronicsFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 banished = 0;
  s8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsMorphtronicMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return 1;
  }

  for (i = (s8)GraveyardExpand_GetCount(fixedDuelist) - 1; i >= 0; i--) {
    if (!IsMorphtronicMonster(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)i);
    banished++;
  }

  GraveyardExpand_RefreshDisplay();
  return banished;
}

static void ApplyFactoryAtkBoost(struct DuelCard *zone, u8 banished)
{
  u8 i;
  u8 stages;

  /* ponytail: stage unit is 500 ATK — applied +500×banished, not printed +200×.
   * Ceiling: no fractional temp stages; upgrade: exact-ATK overlay cleared at
   * End Phase (tempStage already clears EOT). */
  stages = banished * FACTORY_ATK_STAGES_PER_BANISH;
  for (i = 0; i < stages; i++)
    IncrementTempStage(zone);

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveFactoryTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u8 banished;

  if (!IsValidFactoryTarget(fixedRow, fixedCol))
    return;

  banished = BanishAllMorphtronicsFromGy();
  if (banished > 0)
    ApplyFactoryAtkBoost(zone, banished);

  DestroyFactorySpellZone();
}

static void CancelFactoryTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyFactorySpellZone();
}

static u8 AiPickFactoryTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidFactoryTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void FACTORY_OF_ONE_HUNDRED_MACHINES_ResolveBody(void)
{
  Duel_ShowEffectText(FACTORY_OF_ONE_HUNDRED_MACHINES);

  if (IsDuelOver() == TRUE || !CanActivateFACTORY_OF_ONE_HUNDRED_MACHINES())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidFactoryTarget, ResolveFactoryTarget, CancelFactoryTargeting,
                     AiPickFactoryTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectFACTORY_OF_ONE_HUNDRED_MACHINES(void)
{
  if (!CanActivateFACTORY_OF_ONE_HUNDRED_MACHINES()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(FACTORY_OF_ONE_HUNDRED_MACHINES,
                                       FACTORY_OF_ONE_HUNDRED_MACHINES_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void FactoryOfOneHundredMachines_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!Duel_CardHasMonsterType(MORPHTRONIC_CELFON, TYPE_MACHINE))
    while (1)
      ;
}
#endif
