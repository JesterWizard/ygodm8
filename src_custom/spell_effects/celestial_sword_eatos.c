#include "global.h"
#include "common-chax.h"
#include "celestial_sword_eatos.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "removed_from_play.h"
#include "spell_effects.h"

static u8 sCelestialSwordLeaveBanishCount APPEND_DATA = {0};
static u8 sCelestialSwordLeaveController APPEND_DATA = {0};

static u8 ActiveMonsterFixedRowForController(u8 fixedDuelist)
{
  return fixedDuelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidEatosBoostTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRowForController(sCelestialSwordLeaveController))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return zone->id == GUARDIAN_EATOS;
}

static u8 CountBanishedMonsters(void)
{
  u8 total = 0;
  u8 fixedDuelist;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (fixedDuelist = 0; fixedDuelist < 2; fixedDuelist++) {
    for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER)
        total++;
    }
  }

  return total;
}

static void ApplyEatosBanishBoost(struct DuelCard *zone, u8 banishedMonsterCount)
{
  u8 i;
  u8 j;

  if (zone == NULL || zone->id != GUARDIAN_EATOS || banishedMonsterCount == 0)
    return;

  for (i = 0; i < banishedMonsterCount; i++) {
    for (j = 0; j < CELESTIAL_SWORD_EATOS_GY_ATK_PER_BANISH_STAGES; j++)
      IncrementPermStage(zone);
  }

  RefreshFieldMonsterStatOverlays();
}

static void ResolveEatosBoostTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidEatosBoostTarget(fixedRow, fixedCol))
    return;

  Duel_ShowEffectText(CELESTIAL_SWORD_EATOS);
  if (IsDuelOver() == TRUE)
    return;

  ApplyEatosBanishBoost(zone, sCelestialSwordLeaveBanishCount);
}

static u8 AiPickEatosBoostTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRowForController(sCelestialSwordLeaveController);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidEatosBoostTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 HasEatosBoostTarget(u8 fixedDuelist)
{
  u8 row;
  u8 col;

  sCelestialSwordLeaveController = fixedDuelist;
  return AiPickEatosBoostTarget(&row, &col);
}

static void BeginCelestialSwordLeaveBoost(u8 controllerFixedDuelist)
{
  u8 row;
  u8 col;

  sCelestialSwordLeaveBanishCount = CountBanishedMonsters();
  sCelestialSwordLeaveController = controllerFixedDuelist;

  if (!HasEatosBoostTarget(controllerFixedDuelist))
    return;

  if (WhoseTurn() == DUEL_PLAYER && controllerFixedDuelist == DUEL_PLAYER && !gHideEffectText) {
    gDuelCursor.destY = 0;
    gDuelCursor.destX = 0;
    Duel_SetupPickZone(IsValidEatosBoostTarget, ResolveEatosBoostTarget, NULL,
                       AiPickEatosBoostTarget);
    Duel_EnterPickZoneTargeting();
    return;
  }

  if (AiPickEatosBoostTarget(&row, &col))
    ResolveEatosBoostTarget(row, col);
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidCelestialSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return Duel_SpellMayTargetMonsterZone(zone);
}

static u8 HasCelestialSwordTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCelestialSwordTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateCELESTIAL_SWORD_EATOS(void)
{
  return HasCelestialSwordTarget();
}

static void EquipCelestialSword(struct DuelCard *spellZone, struct DuelCard *target)
{
  ApplyDynamicEquipStages(target, CELESTIAL_SWORD_EATOS_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, CELESTIAL_SWORD_EATOS,
                            CELESTIAL_SWORD_EATOS_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: always treated as a Noble Arms card needs a name/archetype tag
   * outside this file. Ceiling: equip +ATK only; upgrade: treat-as / name contains
   * "Noble Arms" for Noble Arms support. */
}

static void ResolveCelestialSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidCelestialSwordTarget(fixedRow, fixedCol))
    return;

  EquipCelestialSword(spellZone, target);
}

static void CancelCelestialSwordTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == CELESTIAL_SWORD_EATOS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickCelestialSwordTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidCelestialSwordTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

void ApplyCelestialSwordEatosOnLeave(struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id != CELESTIAL_SWORD_EATOS)
    return;

  controller = GetDuelistForZone(zone);
  if (controller == 0xFF)
    return;

  BeginCelestialSwordLeaveBoost(controller);
}

u8 Cond_CelestialSwordEatosOnLeave(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != CELESTIAL_SWORD_EATOS)
    return FALSE;

  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  return HasEatosBoostTarget(ev->controller);
}

enum DuelActionResult Op_CelestialSwordEatosOnLeave(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  if (ev->cardId != CELESTIAL_SWORD_EATOS)
    return DUEL_ACTION_NO_TARGET;

  if (!HasEatosBoostTarget(ev->controller))
    return DUEL_ACTION_NO_TARGET;

  BeginCelestialSwordLeaveBoost(ev->controller);
  return DUEL_ACTION_OK;
}

static void CELESTIAL_SWORD_EATOS_ResolveBody(void)
{
  Duel_ShowEffectText(CELESTIAL_SWORD_EATOS);

  if (IsDuelOver() == TRUE || !CanActivateCELESTIAL_SWORD_EATOS())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidCelestialSwordTarget, ResolveCelestialSwordTarget,
                     CancelCelestialSwordTargeting, AiPickCelestialSwordTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectCELESTIAL_SWORD_EATOS(void)
{
  if (!CanActivateCELESTIAL_SWORD_EATOS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CELESTIAL_SWORD_EATOS, CELESTIAL_SWORD_EATOS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CELESTIAL_SWORD_EATOS_SelfCheck(void)
{
  if (CELESTIAL_SWORD_EATOS_ATK_STAGES != 1)
    while (1)
      ;
  if (GUARDIAN_EATOS == CARD_NONE)
    while (1)
      ;
}
#endif
