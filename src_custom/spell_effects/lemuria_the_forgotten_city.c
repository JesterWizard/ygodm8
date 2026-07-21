#include "global.h"
#include "card.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/card_enums.h"
#include "constants/duel_fields.h"
#include "constants/music_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "lemuria_the_forgotten_city.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static u8 IsWaterMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

static u8 IsWaterMonsterWithoutCardInfo(u16 cardId)
{
  const CardData *card;

  if (cardId >= NUM_TOTAL_CARDS || gRuntimeConfig.disable_element_system == TRUE)
    return FALSE;

  card = &gCardData_NEW[cardId];
  if (card->color != NORMAL_CARD && card->color != EFFECT_CARD
      && card->color != FUSION_CARD && card->color != RITUAL_CARD)
    return FALSE;

  return card->attribute == ATTRIBUTE_WATER;
}

u8 Lemuria_IsActive(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == LEMURIA_THE_FORGOTTEN_CITY && zone->isFaceUp)
        return TRUE;
    }
  }

  return FALSE;
}

void ApplyLemuriaFieldStatBoostForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u32 boosted;

  if (zone == NULL || zone->id == CARD_NONE || !Lemuria_IsActive()
      || !Duel_FindFixedMonsterZone(zone, &fixedRow, &col)
      || !IsWaterMonsterWithoutCardInfo(zone->id))
    return;

  if (gCardInfo.atk != 0xFFFF) {
    boosted = (u32)gCardInfo.atk + 200;
    gCardInfo.atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }

  if (gCardInfo.def != 0xFFFF) {
    boosted = (u32)gCardInfo.def + 200;
    gCardInfo.def = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
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
  if (cardId == LEMURIA_THE_FORGOTTEN_CITY || cardId == HARPIES_HUNTING_GROUND
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

static u8 CountControlledWaterMonsters(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (IsWaterMonster(zone->id))
      count++;
  }

  return count;
}

static u8 CanActivateLemuriaIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != LEMURIA_THE_FORGOTTEN_CITY || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return CountControlledWaterMonsters() > 0;
}

static void ResolveLemuriaIgnition(struct DuelCard *zone)
{
  u8 waterCount;

  if (!CanActivateLemuriaIgnition(zone))
    return;

  Duel_ShowEffectText(LEMURIA_THE_FORGOTTEN_CITY);

  if (IsDuelOver() == TRUE)
    return;

  waterCount = CountControlledWaterMonsters();
  if (waterCount == 0)
    return;

  /* ponytail: no per-zone Level overlay API — levels come from SetCardInfo /
   * Legendary Ocean adjusters only. Ceiling: OPT marks used + shows text;
   * Levels unchanged. Upgrade: turn-scoped level bonus on each controlled WATER
   * (= waterCount) cleared at End Phase (card_hooks GetLegendaryOcean-style). */
  (void)waterCount;

  zone->effectUsedThisTurn = TRUE;
}

static void ApplyLemuriaAsUmiField(void)
{
  gDuel.field = FIELD_UMI;

  if (!gHideEffectText)
    SetDuelFieldGfx(FIELD_UMI);
}

static void LEMURIA_THE_FORGOTTEN_CITY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up field (OPT Main Phase Level gain). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateLemuriaIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveLemuriaIgnition(zone);
    return;
  }

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  /* Name treated as Umi → apply Umi terrain while this stays face-up. */
  ApplyLemuriaAsUmiField();
  Duel_ActivateContinuousZone(zone);

  if (CanActivateLemuriaIgnition(zone))
    ResolveLemuriaIgnition(zone);
  else
    Duel_ShowEffectText(LEMURIA_THE_FORGOTTEN_CITY);
}

APPEND_TEXT void EffectLEMURIA_THE_FORGOTTEN_CITY(void)
{
if (Duel_TryResolveSpellThroughTraps(LEMURIA_THE_FORGOTTEN_CITY,
                                       LEMURIA_THE_FORGOTTEN_CITY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LEMURIA_THE_FORGOTTEN_CITY_SelfCheck(void)
{
  SetCardInfo(TORPEDO_FISH);
  if (gCardInfo.attribute != ATTRIBUTE_WATER)
    while (1)
      ;
  SetCardInfo(BLUE_EYES_WHITE_DRAGON);
  if (gCardInfo.attribute == ATTRIBUTE_WATER)
    while (1)
      ;
}
#endif
