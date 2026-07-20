#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* 1 stage ~= 500 ATK (same as THOUSAND_ENERGY / NEGATIVE_ENERGY). */
#define AQUA_JET_ATK_STAGES 2

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

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsAquaJetType(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FISH)
      || Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT)
      || Duel_CardHasMonsterType(cardId, TYPE_AQUA);
}

static u8 IsValidAquaJetTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!MonsterIsFaceUp(zone))
    return FALSE;

  return IsAquaJetType(zone->id);
}

static u8 HasAquaJetTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidAquaJetTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateAQUA_JET(void)
{
  return HasAquaJetTarget();
}

static void DestroyAquaJetSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == AQUA_JET)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyAquaJetBoost(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < AQUA_JET_ATK_STAGES; i++)
    IncrementTempStage(zone);

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveAquaJetTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidAquaJetTarget(fixedRow, fixedCol))
    return;

  ApplyAquaJetBoost(zone);
  DestroyAquaJetSpellZone();
}

static void CancelAquaJetTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyAquaJetSpellZone();
}

static u8 AiPickAquaJetTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidAquaJetTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void AQUA_JET_ResolveBody(void)
{
  Duel_ShowEffectText(AQUA_JET);

  if (IsDuelOver() == TRUE || !HasAquaJetTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidAquaJetTarget, ResolveAquaJetTarget, CancelAquaJetTargeting,
                     AiPickAquaJetTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectAQUA_JET(void)
{
  if (!CanActivateAQUA_JET()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AQUA_JET, AQUA_JET_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
