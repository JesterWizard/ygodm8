#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "reptilanne_rage.h"
#include "riryoku.h"
#include "spell_effects.h"

#define REPTILANNE_RAGE_ATK_BOOST 800

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 IsValidReptilanneRageTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsReptileMonster(zone->id);
}

static u8 HasReptilanneRageTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidReptilanneRageTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateREPTILANNE_RAGE(void)
{
  return HasReptilanneRageTarget();
}

static void EquipReptilanneRage(struct DuelCard *spellZone, struct DuelCard *target)
{
  AddRiryokuAtkDelta(target, REPTILANNE_RAGE_ATK_BOOST);
  if (!RegisterDynamicEquip(spellZone, target, REPTILANNE_RAGE, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();

  /* ponytail: "becomes Reptile-Type" needs a temp-type overlay outside this file
   * (DuelCard has no type field; type lives in ROM via SetCardInfo).
   * Ceiling: equip-only-to-Reptile (already TYPE_REPTILE); upgrade: type overlay
   * → treat equipped target as TYPE_REPTILE while link is active. */

  /* ponytail: destroy→GY target opp face-up monster -800 ATK needs a field/
   * destroy hook outside this file (OnDynamicEquipZoneAboutToClear / GY send).
   * Ceiling: equip-only works; GY trigger not wired from this file.
   * Upgrade: destroy-hook → PickZone opp face-up monster → apply -800 ATK
   * overlay (or -2 stages). */
}

void ApplyReptilanneRageAtkBonusToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || !DynamicEquipTargetsMonsterWithSpell(zone, REPTILANNE_RAGE))
    return;
  /* Exact +800 already applied via AddRiryokuAtkDelta; Riryoku overlay path covers it. */
  (void)zone;
}

static void ResolveReptilanneRageTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidReptilanneRageTarget(fixedRow, fixedCol))
    return;

  EquipReptilanneRage(spellZone, target);
}

static void CancelReptilanneRageTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == REPTILANNE_RAGE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static u8 AiPickReptilanneRageTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidReptilanneRageTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void REPTILANNE_RAGE_ResolveBody(void)
{
  Duel_ShowEffectText(REPTILANNE_RAGE);

  if (IsDuelOver() == TRUE || !CanActivateREPTILANNE_RAGE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidReptilanneRageTarget, ResolveReptilanneRageTarget,
                     CancelReptilanneRageTargeting, AiPickReptilanneRageTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectREPTILANNE_RAGE(void)
{
  if (!CanActivateREPTILANNE_RAGE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(REPTILANNE_RAGE, REPTILANNE_RAGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void REPTILANNE_RAGE_SelfCheck(void)
{
  if (REPTILANNE_RAGE_ATK_STAGES != 2)
    while (1)
      ;
  if (!IsReptileMonster(REPTILIANNE_NAGA))
    while (1)
      ;
  if (IsReptileMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
