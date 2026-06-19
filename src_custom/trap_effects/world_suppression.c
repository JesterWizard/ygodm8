#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "world_suppression.h"

void SetDuelFieldGfx(u8 field);

u8 gWorldSuppressionNegatesFieldSpells;

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

u8 WorldSuppression_IsFieldSpellCard(u16 cardId)
{
  if (cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

u8 IsWorldSuppressionNegatingFieldSpells(void)
{
  return gWorldSuppressionNegatesFieldSpells != 0;
}

u8 IsWorldSuppressionNegatingFieldSpell(u16 cardId)
{
  return IsWorldSuppressionNegatingFieldSpells() && WorldSuppression_IsFieldSpellCard(cardId);
}

void WorldSuppression_ClearNegation(void)
{
  gWorldSuppressionNegatesFieldSpells = 0;
}

void WorldSuppression_SetNegatingFieldSpells(void)
{
  gWorldSuppressionNegatesFieldSpells = 1;
  RevertCustomFieldToArena();

  if (gDuel.field != FIELD_ARENA) {
    gDuel.field = FIELD_ARENA;
    if (!gHideEffectText)
      SetDuelFieldGfx(gDuel.field);
  }
}

u8 WorldSuppression_ShouldActivateTrapOnFieldSpell(u16 originCardId)
{
  return WorldSuppression_IsFieldSpellCard(originCardId);
}

static struct DuelCard *GetSpellOriginZone(void)
{
  u8 row = gTrapEffectData.originRow;
  u8 col = gTrapEffectData.originCol;

  if (col >= MAX_ZONES_IN_ROW)
    return NULL;

  if (row <= PLAYER_HAND)
    return gFixedZones[row][col];

  if (row < 5)
    return gTurnZones[row][col];

  return NULL;
}

APPEND_TEXT void EffectWorldSuppression(void)
{
  struct DuelCard *spellZone = GetSpellOriginZone();

  WorldSuppression_SetNegatingFieldSpells();
  Duel_DestroyZone(gTurnZones[0][gTrapEffectData.trapZoneCol], INACTIVE_DUELIST, FALSE);

  if (spellZone != NULL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  Duel_ShowTrapResponseText(WORLD_SUPPRESSION, gTrapEffectData.originCardId);
}
