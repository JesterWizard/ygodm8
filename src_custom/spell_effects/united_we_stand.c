#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void UnitedWeStand_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u8 stages = CountDuelistMonsterRowCards(GetDuelistForZone(spellZone));

  Duel_ResolveEquipStatBoost(target, spellZone, UNITED_WE_STAND, stages);
}

APPEND_TEXT void EffectUnitedWeStand(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(UNITED_WE_STAND, UnitedWeStand_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
