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
  if (cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS || cardId == MYSTIC_MINE
      || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
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

static void COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS);

  /* ponytail: Counter on Special Summon from Deck needs a summon-listener outside
   * this file (no in-file SS-from-Deck dispatch). Ceiling: face-up field + unk4
   * counter slot (never rises alone); upgrade: after SS from Deck → if face-up
   * COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS then zone->unk4++. */

  /* ponytail: +100 ATK/DEF per counter for all Gladiator Beast monsters needs a
   * field-stat applier outside this file (Duel_TryApplyDynamicZoneStats only covers
   * monster ids registered in duel_helpers.c). Ceiling: face-up field only;
   * upgrade: LynJump/stat overlay → if face-up COLOSSEUM and name contains
   * "Gladiator Beast" then ATK/DEF += 100 * zone->unk4. */

  /* ponytail: discard another Colosseum to prevent destroy by card effect needs a
   * destroy-protection / replacement hook outside this file. Ceiling: no protect;
   * upgrade: OnWouldDestroySpell → if hand has COLOSSEUM_CAGE then optional discard
   * and skip destroy. */
}

APPEND_TEXT void EffectCOLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS(void)
{
  if (Duel_TryResolveSpellThroughTraps(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS,
                                       COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_SelfCheck(void)
{
  static const char gbName[] = "Gladiator Beast";

  if (!Duel_CardNameContains(GLADIATOR_BEAST_ANDAL, gbName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, gbName))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS))
    while (1)
      ;
}
#endif
