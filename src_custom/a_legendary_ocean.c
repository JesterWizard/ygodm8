#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "a_legendary_ocean.h"
#include "constants/custom_field_spells.h"
#include "custom_field_spell.h"
#include "card.h"
#include "duel_helpers.h"

u8 IsLegendaryOceanActive(void)
{
  return gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_A_LEGENDARY_OCEAN;
}

static u8 IsWaterMonster(u16 cardId)
{
  const CardData *card;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  card = &gCardData_NEW[cardId];

  if (card->color != NORMAL_CARD && card->color != EFFECT_CARD
      && card->color != FUSION_CARD && card->color != RITUAL_CARD)
    return FALSE;

  if (gRuntimeConfig.disable_element_system == TRUE)
    return FALSE;

  // ponytail: never GetTypeGroup/SetCardInfo here — callers may have computed gCardInfo.atk/def.
  return card->attribute == ATTRIBUTE_WATER;
}

u8 GetLegendaryOceanAdjustedLevel(u16 cardId, u8 baseLevel)
{
  if (!IsLegendaryOceanActive() || !IsWaterMonster(cardId) || baseLevel <= 1)
    return baseLevel;

  return baseLevel - 1;
}

void ApplyLegendaryOceanFieldStatBoost(u16 cardId, u16 *atk, u16 *def)
{
  u32 boosted;

  if (!IsLegendaryOceanActive() || !IsWaterMonster(cardId))
    return;

  if (*atk != 0xFFFF) {
    boosted = (u32)*atk + 200;
    *atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }

  if (*def != 0xFFFF) {
    boosted = (u32)*def + 200;
    *def = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
}

void ApplyLegendaryOceanFieldStatBoostForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  ApplyLegendaryOceanFieldStatBoost(zone->id, &gCardInfo.atk, &gCardInfo.def);
}
