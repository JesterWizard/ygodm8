#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 IsValidMagePowerTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static void ActivateDynamicEquipSpell(struct DuelCard *spellZone)
{
  FlipCardFaceUp(spellZone);
  spellZone->isLocked = TRUE;
}

static void MagePower_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  u8 stages = CountDuelistSpellTrapBackrowCards(GetDuelistForZone(spellZone));

  if (stages > MAX_ZONES_IN_ROW)
    stages = MAX_ZONES_IN_ROW;

  ApplyDynamicEquipStages(target, stages);
  RegisterDynamicEquip(spellZone, target, MAGE_POWER, stages);
  ActivateDynamicEquipSpell(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(MAGE_POWER);
}

APPEND_TEXT void EffectMagePower(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!IsValidMagePowerTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MAGE_POWER, MagePower_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
