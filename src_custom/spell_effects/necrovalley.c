#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define NECROVALLEY_GRAVEKEEPER_STAT_BONUS 500

void SetDuelFieldGfx(u8 field);

static const char sGravekeeperArchetypeName[] APPEND_RODATA = "Gravekeeper";

u8 Necrovalley_IsActive(void)
{
  return Duel_IsBackrowCardOnField(NECROVALLEY, TRUE);
}

u8 Necrovalley_IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeeperArchetypeName);
}

void Necrovalley_ApplyGravekeeperStatBonusToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || !Necrovalley_IsActive()
      || !Necrovalley_IsGravekeeperMonster(zone->id))
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + NECROVALLEY_GRAVEKEEPER_STAT_BONUS);
  gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def + NECROVALLEY_GRAVEKEEPER_STAT_BONUS);
}

u8 Necrovalley_BlocksGraveyardBanish(void)
{
  return Necrovalley_IsActive();
}

u8 Necrovalley_BlocksGraveyardMove(void)
{
  return Necrovalley_IsActive();
}

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == NECROVALLEY || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == NEO_SPACE)
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

static void NECROVALLEY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(NECROVALLEY);

  /* ponytail: GY Type-Attribute change still needs SetCardInfo-in-GY gates.
   * Ceiling: banish/move blocked via Necrovalley_Blocks*; upgrade: GY type/attr mutate → negate. */
}

APPEND_TEXT void EffectNECROVALLEY(void)
{
  if (Duel_TryResolveSpellThroughTraps(NECROVALLEY, NECROVALLEY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NECROVALLEY_SelfCheck(void)
{
  if (!IsFieldSpellCardOnField(NECROVALLEY))
    while (1)
      ;
  if (IsFieldSpellCardOnField(POT_OF_GREED))
    while (1)
      ;
}
#endif
