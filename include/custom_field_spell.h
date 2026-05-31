#ifndef GUARD_CUSTOM_FIELD_SPELL_H
#define GUARD_CUSTOM_FIELD_SPELL_H

#include "card.h"
#include "constants/custom_field_spells.h"
#include "duel.h"

struct CustomFieldGfxAsset
{
  const u8 *tiles;
  const u16 (*tilemap)[31];
  const u16 *palette;
};

typedef void (*CustomFieldSpellEffectFn)(void);

extern u8 gActiveCustomFieldSpellId;
extern u8 gActiveFieldSpellZoneRow;
extern u8 gActiveFieldSpellZoneCol;
extern u8 gActiveFieldSpellController;

#define FIELD_SPELL_CONTROLLER_NONE 0xFF

#if NUM_CUSTOM_FIELDS > 0
extern const u8 gCustomFieldStatMods[NUM_CUSTOM_FIELDS][NUM_CARD_TYPES];
#endif

void ResetCustomFieldSpellState(void);
u8 TryActivateCustomFieldSpell(u16 cardId);
u8 TryActivateVanillaFieldSpell(u16 cardId, u8 spellEffect);
void ActivateCustomFieldSpell(u8 spellId);
void OnCustomFieldSpellZoneCleared(struct DuelCard *zone);
void RevertCustomFieldToArena(void);
u8 GetCustomFieldIdForSpellId(u8 spellId);
const struct CustomFieldGfxAsset *GetCustomFieldGfxAsset(u8 field);
const u16 *GetCustomFieldPalette(u8 field);

#endif // GUARD_CUSTOM_FIELD_SPELL_H
