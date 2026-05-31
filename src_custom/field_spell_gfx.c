#include "global.h"
#include "configs/runtime.h"
#include "custom_field_spell.h"

#include "generated/field_spell_gfx_generated.inc"
#include "generated/field_spell_tilemaps_generated.inc"
#include "generated/field_spell_gfx_tables_generated.inc"

const struct CustomFieldGfxAsset *GetCustomFieldGfxAsset(u8 field)
{
#if NUM_CUSTOM_FIELDS > 0
  if (IsCustomField(field))
    return &sCustomFieldGfxAssets[field - FIRST_CUSTOM_FIELD];
#endif
  return NULL;
}

const u16 *GetCustomFieldPalette(u8 field)
{
  const struct CustomFieldGfxAsset *asset = GetCustomFieldGfxAsset(field);

  if (asset == NULL)
    return NULL;

  return asset->palette;
}
