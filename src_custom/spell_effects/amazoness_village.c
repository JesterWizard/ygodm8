#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

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
  if (cardId == AMAZONESS_VILLAGE || cardId == HARPIES_HUNTING_GROUND
      || cardId == PSEUDO_SPACE || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER
      || cardId == WETLANDS || cardId == GEARTOWN || cardId == DRAGON_RAVINE
      || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
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

static void AMAZONESS_VILLAGE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AMAZONESS_VILLAGE);

  /* ponytail: +200 ATK for Amazoness monsters needs a field-stat applier outside
   * this file (Duel_TryApplyDynamicZoneStats only covers monster ids registered
   * in duel_helpers.c). Ceiling: face-up field only; upgrade: LynJump/stat overlay
   * → if face-up AMAZONESS_VILLAGE and Duel_IsAmazonessCard(zone) then ATK += 200. */

  /* ponytail: once-per-turn when an Amazoness is destroyed by battle/effect and
   * sent to GY → SS 1 Amazoness from Deck with Level ≤ that GY monster needs a
   * destroy/GY listener + OPT bit outside this file. Ceiling: continuous face-up
   * only; upgrade: after-destroy hook → if face-up AMAZONESS_VILLAGE and
   * Duel_IsAmazonessCard(destroyed) then PickZone deck SS filtered by level. */
}

APPEND_TEXT void EffectAMAZONESS_VILLAGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_VILLAGE, AMAZONESS_VILLAGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_VILLAGE_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(AMAZONESS_VILLAGE))
    while (1)
      ;
}
#endif
