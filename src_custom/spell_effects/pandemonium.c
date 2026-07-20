#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static const char sArchfiendName[] APPEND_RODATA = "Archfiend";

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == PANDEMONIUM || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS
      || cardId == FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS || cardId == MYSTIC_MINE
      || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == AMAZONESS_VILLAGE
      || cardId == NECROVALLEY || cardId == CHICKEN_GAME)
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

static void PANDEMONIUM_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(PANDEMONIUM);

  /* ponytail: skip Archfiend Standby LP maintenance costs needs a Standby /
   * maintenance-cost gate outside this file. Ceiling: face-up field only;
   * upgrade: Archfiend maintenance pay → if face-up PANDEMONIUM on field then
   * skip LP cost for that Archfiend. */

  /* ponytail: when an Archfiend is destroyed (not by battle) → that player may
   * add 1 lower-Level Archfiend from Deck needs a destroy/GY listener outside
   * this file. Ceiling: continuous face-up only; upgrade: after-destroy hook →
   * if face-up PANDEMONIUM and destroyed name contains "Archfiend" (not battle)
   * then DeckMenu search Level < destroyed.level. */

  (void)sArchfiendName;
}

APPEND_TEXT void EffectPANDEMONIUM(void)
{
  if (Duel_TryResolveSpellThroughTraps(PANDEMONIUM, PANDEMONIUM_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void PANDEMONIUM_SelfCheck(void)
{
  if (!Duel_CardNameContains(RED_DRAGON_ARCHFIEND, sArchfiendName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, sArchfiendName))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(PANDEMONIUM))
    while (1)
      ;
}
#endif
