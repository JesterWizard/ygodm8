#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

#define BIG_EVOLUTION_PILL_OPPONENT_END_PHASES 3

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsDinosaurMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR);
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
  /* unk4 = opponent End Phases elapsed (for turn_effect destroy when wired). */
  spellZone->unk4 = 0;

  /* ponytail: destroy on controller's opponent's 3rd End Phase needs a turn_effect
   * End Phase hook outside this file (no in-file End Phase dispatch).
   * Ceiling: continuous face-up only (unk4 stays 0); upgrade: turn_effect_hooks
   * opponent End Phase → if face-up BIG_EVOLUTION_PILL then unk4++; if
   * unk4 >= BIG_EVOLUTION_PILL_OPPONENT_END_PHASES destroy it. */
  /* ponytail: Normal Summon Level 5+ Dinosaur without Tributing needs a
   * GetNumRequiredTributes gate outside this file (clone Necroshade in
   * tribute_hooks.c). Ceiling: continuous face-up only; upgrade: if face-up
   * BIG_EVOLUTION_PILL for summoner and card is TYPE_DINOSAUR Level >= 5 then
   * return 0 tributes. */
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
