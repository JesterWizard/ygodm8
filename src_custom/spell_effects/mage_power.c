#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void MagePower_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u8 stages = CountDuelistSpellTrapBackrowCards(GetDuelistForZone(spellZone));

  Duel_ResolveEquipStatBoost(target, spellZone, MAGE_POWER, stages);
}

APPEND_TEXT void EffectMagePower(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MAGE_POWER, MagePower_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
