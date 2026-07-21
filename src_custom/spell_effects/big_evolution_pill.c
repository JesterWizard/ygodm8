#include "global.h"
#include "common-chax.h"
#include "big_evolution_pill.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static int LookupRequiredTributes(u8 level)
{
  if (level <= 4)
    return 0;
  if (level <= 6)
    return 1;
  if (level <= 8)
    return 2;
  return 3;
}

static int BaseRequiredTributesForCard(u16 cardId)
{
  SetCardInfo(cardId);
  return LookupRequiredTributes(gCardInfo.level);
}

static u8 IsDinosaurMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR);
}

static u8 QualifiesForPillTributeFreeSummon(u16 cardId)
{
  if (!IsDinosaurMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 5;
}

static u8 IsValidDinosaurTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsDinosaurMonster(zone->id);
}

static u8 HasDinosaurTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDinosaurTribute(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateBIG_EVOLUTION_PILL(void)
{
  return HasDinosaurTribute();
}

u8 BigEvolutionPill_CanNormalSummonWithoutTribute(u16 cardId)
{
  if (!QualifiesForPillTributeFreeSummon(cardId))
    return FALSE;

  if (Duel_FindBackrowCard(FixedDuelistForActive(), BIG_EVOLUTION_PILL, TRUE) == NULL)
    return FALSE;

  return BaseRequiredTributesForCard(cardId) > 0;
}

u8 BigEvolutionPill_TryConsumeOnNormalSummon(u16 cardId)
{
  return BigEvolutionPill_CanNormalSummonWithoutTribute(cardId);
}

static void TickBigEvolutionPillForController(u8 controllerFixed, u8 endedFixedDuelist)
{
  u8 backrow;
  u8 col;
  u8 turnDuelist;
  struct DuelCard *zone;

  if (endedFixedDuelist == controllerFixed)
    return;

  backrow = controllerFixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  turnDuelist = TurnDuelistForFixed(controllerFixed);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gFixedZones[backrow][col];
    if (zone == NULL || zone->id != BIG_EVOLUTION_PILL || !zone->isFaceUp)
      continue;

    zone->unk4++;
    if (zone->unk4 < BIG_EVOLUTION_PILL_OPPONENT_END_PHASES)
      continue;

    Duel_ShowEffectText(BIG_EVOLUTION_PILL);
    if (IsDuelOver() == TRUE)
      return;

    Duel_DestroyZone(zone, turnDuelist, TRUE);
  }
}

void BigEvolutionPill_OnOpponentEndPhase(u8 endedFixedDuelist)
{
  if (endedFixedDuelist != DUEL_PLAYER && endedFixedDuelist != DUEL_OPPONENT)
    return;

  if (IsDuelOver() == TRUE)
    return;

  TickBigEvolutionPillForController(DUEL_PLAYER, endedFixedDuelist);
  if (IsDuelOver() == TRUE)
    return;

  TickBigEvolutionPillForController(DUEL_OPPONENT, endedFixedDuelist);
}

static void DestroyBigEvolutionPillSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == BIG_EVOLUTION_PILL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void CancelBigEvolutionPillTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyBigEvolutionPillSpellZone();
}

static u8 AiPickDinosaurTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidDinosaurTribute(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void FinishBigEvolutionPill(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidDinosaurTribute(fixedRow, fixedCol)) {
    DestroyBigEvolutionPillSpellZone();
    return;
  }

  PlayMusic(SFX_TRIBUTE);
  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return;

  if (spellZone == NULL || spellZone->id != BIG_EVOLUTION_PILL) {
    UpdateDuelGfxExceptField();
    return;
  }

  Duel_ActivateContinuousZone(spellZone);
  spellZone->unk4 = 0;
}

static void ResolveDinosaurTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidDinosaurTribute(fixedRow, fixedCol))
    return;

  FinishBigEvolutionPill(fixedRow, fixedCol);
}

static void BIG_EVOLUTION_PILL_ResolveBody(void)
{
  Duel_ShowEffectText(BIG_EVOLUTION_PILL);

  if (IsDuelOver() == TRUE || !CanActivateBIG_EVOLUTION_PILL())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidDinosaurTribute, ResolveDinosaurTribute,
                     CancelBigEvolutionPillTargeting, AiPickDinosaurTribute);

  if (WhoseTurn() != DUEL_PLAYER)
    Duel_ResolvePickZoneForAi();
  else
    Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectBIG_EVOLUTION_PILL(void)
{
  if (!CanActivateBIG_EVOLUTION_PILL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(BIG_EVOLUTION_PILL, BIG_EVOLUTION_PILL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BIG_EVOLUTION_PILL_SelfCheck(void)
{
  if (!IsDinosaurMonster(TWO_HEADED_KING_REX))
    while (1)
      ;
  if (IsDinosaurMonster(DARK_MAGICIAN))
    while (1)
      ;
  if (BIG_EVOLUTION_PILL_OPPONENT_END_PHASES != 3)
    while (1)
      ;
}
#endif
