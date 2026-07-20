#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

/* 1 stage ~= 500 ATK. Printed +700; nearest stage unit is +500. */
#define LIGHTSWORN_SABRE_ATK_STAGES 1

static const char sLightswornArchetypeName[] APPEND_RODATA = "Lightsworn";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornArchetypeName);
}

static u8 IsValidLightswornSabreTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsLightswornMonster(zone->id);
}

static u8 HasLightswornSabreTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidLightswornSabreTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateLIGHTSWORN_SABRE(void)
{
  return HasLightswornSabreTarget();
}

static void EquipLightswornSabre(struct DuelCard *spellZone, struct DuelCard *target)
{
  /* ponytail: stage unit is 500 ATK — applied +500, not printed +700.
   * Ceiling: no fractional stages; upgrade: exact-ATK overlay like H_HEATED_HEART
   * (ApplyHeatedHeartAtkBonusToCardInfo) after listing LIGHTSWORN_SABRE in
   * IsActiveDynamicEquipSpellZone. */

  ApplyDynamicEquipStages(target, LIGHTSWORN_SABRE_ATK_STAGES);
  if (!RegisterDynamicEquip(spellZone, target, LIGHTSWORN_SABRE, LIGHTSWORN_SABRE_ATK_STAGES))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone — PickZone
   * instead of vanilla equip targeting; link cleanup may not treat this as active
   * equip. Ceiling: add LIGHTSWORN_SABRE to card_hooks GetSpellType EQUIP list and
   * dynamic_equip IsActiveDynamicEquipSpellZone; upgrade path: same as H_HEATED_HEART. */

  /* ponytail: Deck-to-GY re-equip (when milled) needs a mill/send-from-deck hook
   * outside this file. Ceiling: equip-from-hand/field only; upgrade: mill path →
   * if LIGHTSWORN_SABRE sent from Deck to GY then PickZone Lightsworn and
   * RegisterDynamicEquip again. */
}

static void ResolveLightswornSabreTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidLightswornSabreTarget(fixedRow, fixedCol))
    return;

  EquipLightswornSabre(spellZone, target);
}

static void CancelLightswornSabreTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == LIGHTSWORN_SABRE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickLightswornSabreTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidLightswornSabreTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void LIGHTSWORN_SABRE_ResolveBody(void)
{
  Duel_ShowEffectText(LIGHTSWORN_SABRE);

  if (IsDuelOver() == TRUE || !CanActivateLIGHTSWORN_SABRE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidLightswornSabreTarget, ResolveLightswornSabreTarget,
                     CancelLightswornSabreTargeting, AiPickLightswornSabreTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectLIGHTSWORN_SABRE(void)
{
  if (!CanActivateLIGHTSWORN_SABRE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(LIGHTSWORN_SABRE, LIGHTSWORN_SABRE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LightswornSabre_SelfCheck(void)
{
  if (!IsLightswornMonster(JAIN_LIGHTSWORN_PALADIN))
    while (1)
      ;
  if (IsLightswornMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
