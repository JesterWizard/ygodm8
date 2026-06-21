#include "global.h"
#include "common-chax.h"
#include "burning_land.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "world_suppression.h"
#include "spell_effects.h"

#define BURNING_LAND_STANDBY_DAMAGE 500

void SetDuelFieldGfx(u8 field);

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

u8 IsActivatedBurningLandZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == BURNING_LAND && zone->isFaceUp == TRUE;
}

u8 IsBurningLandActiveOnField(void)
{
  u8 row;
  u8 i;

  if (IsImperialOrderNegatingSpell(BURNING_LAND))
    return FALSE;

  if (IsWorldSuppressionNegatingFieldSpell(BURNING_LAND))
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsActivatedBurningLandZone(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

void TryApplyBurningLandStandbyDamage(void)
{
  if (!IsBurningLandActiveOnField() || IsDuelOver() == TRUE)
    return;

  Duel_ShowEffectText(BURNING_LAND);

  if (Duel_ChangeLp(ACTIVE_DUELIST, -BURNING_LAND_STANDBY_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

APPEND_TEXT void EffectBurningLand(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);

  Duel_ShowEffectText(BURNING_LAND);
}
