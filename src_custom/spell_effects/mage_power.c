#include "global.h"
#include "common-chax.h"
#include "spell_effects.h"

extern void ActivateTrapEffect(u16 lp);

static u8 IsValidMagePowerTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 CountActiveDuelistSpellTrapBackrowCards(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 id = gTurnZones[ACTIVE_DUELIST_BACKROW][i]->id;

    if (id == CARD_NONE)
      continue;

    if (GetTypeGroup(id) == TYPE_GROUP_SPELL || GetTypeGroup(id) == TYPE_GROUP_TRAP)
      count++;
  }

  return count;
}

APPEND_TEXT void EffectMagePower(void)
{
  struct DuelCard *target = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 stages = CountActiveDuelistSpellTrapBackrowCards();

  if (!IsValidMagePowerTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  gTrapEffectData.originRow = gSpellEffectData.row2;
  gTrapEffectData.originCol = gSpellEffectData.col2;
  gTrapEffectData.originCardId = gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id;

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    while (stages--)
      IncrementPermStage(target);

    ClearZoneAndSendMonToGraveyard(
        gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2], ACTIVE_DUELIST);

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = MAGE_POWER;
      ActivateCardEffectText();
    }
  } else {
    while (stages--)
      DecrementPermStage(target);
    ActivateTrapEffect(0);
  }
}
