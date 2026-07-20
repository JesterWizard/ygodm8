#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

/* 1 stage ~= 500 ATK; printed +300 ATK per Morph Counter ≈ nearest stage. */
#define MORPHTRONIC_MAP_ATK_PER_COUNTER 300

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == MORPHTRONIC_MAP || cardId == NEO_SPACE || cardId == PSEUDO_SPACE
      || cardId == HARPIES_HUNTING_GROUND || cardId == SKYSCRAPER_2_HERO_CITY
      || cardId == SKYSCRAPER || cardId == WETLANDS || cardId == GEARTOWN
      || cardId == DRAGON_RAVINE || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS
      || cardId == FUSION_GATE || cardId == MYSTIC_MINE
      || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS)
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

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static void MORPHTRONIC_MAP_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0; /* Morph Counter slot */

  Duel_ShowEffectText(MORPHTRONIC_MAP);

  /* ponytail: Morph Counter on battle-position change needs a position-change
   * hook outside this file (no in-file Flip/ChangeBattlePosition dispatch).
   * Ceiling: face-up field + unk4 counter slot (never rises alone); upgrade:
   * after battle position change → if face-up MORPHTRONIC_MAP then zone->unk4++. */

  /* ponytail: +300 ATK per Morph Counter for Morphtronic monsters needs a
   * field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only
   * covers monster ids registered in duel_helpers.c).
   * Ceiling: face-up field only; upgrade: LynJump/stat overlay → if face-up
   * MORPHTRONIC_MAP and IsMorphtronicMonster(id) then ATK += 300 * zone->unk4
   * (stage-approx: (300*n + 250)/500 if forced through IncrementTempStage). */

  /* ponytail: destroy→GY → optional SS Morphtronic from GY needs a destroy hook
   * + PickZone/GY menu outside this file. Ceiling: field face-up only; upgrade:
   * on ClearZoneAndSendMonToGraveyard of face-up MORPHTRONIC_MAP → PickZone
   * Morphtronic in GY → Duel_SpecialSummonFromGrave. */

  (void)MORPHTRONIC_MAP_ATK_PER_COUNTER;
  (void)IsMorphtronicMonster;
}

APPEND_TEXT void EffectMORPHTRONIC_MAP(void)
{
  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_MAP, MORPHTRONIC_MAP_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MORPHTRONIC_MAP_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(MORPHTRONIC_MAP))
    while (1)
      ;
  if (MORPHTRONIC_MAP_ATK_PER_COUNTER != 300)
    while (1)
      ;
}
#endif
