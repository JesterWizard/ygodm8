#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "duel_helpers.h"
#include "field_barrier.h"
#include "spell_effects.h"

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

u8 FieldBarrier_IsFieldSpellCard(u16 cardId)
{
  if (cardId == FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS
      || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS || cardId == PANDEMONIUM
      || cardId == MYSTIC_MINE || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == AMAZONESS_VILLAGE
      || cardId == NECROVALLEY || cardId == CHICKEN_GAME)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 FixedDuelistForZone(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;

  if (zone == NULL || !Duel_FindFixedZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return 0xFF;

  return fixedRow == PLAYER_BACKROW || fixedRow == PLAYER_MONSTER_ROW ? DUEL_PLAYER
                                                                        : DUEL_OPPONENT;
}

u8 FieldBarrier_PreventsFieldSpellDestroy(const struct DuelCard *zone)
{
  u8 fixedDuelist;

  if (zone == NULL || !FieldBarrier_IsFieldSpellCard(zone->id))
    return FALSE;

  fixedDuelist = FixedDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  return Duel_FindBackrowCard(fixedDuelist, FIELD_BARRIER, TRUE) != NULL;
}

u8 FieldBarrier_BlocksNewFieldSpellActivation(u8 activatorFixed)
{
  if (activatorFixed != DUEL_PLAYER && activatorFixed != DUEL_OPPONENT)
    return FALSE;

  return Duel_FindBackrowCardOnField(FIELD_BARRIER, TRUE) != NULL;
}

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 ControllerAlreadyHasFaceUpFieldBarrier(struct DuelCard *activatingZone)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == activatingZone || zone == NULL || zone->id != FIELD_BARRIER)
      continue;

    if (zone->isFaceUp == TRUE)
      return TRUE;
  }

  return FALSE;
}

static void FIELD_BARRIER_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (ControllerAlreadyHasFaceUpFieldBarrier(zone)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(FIELD_BARRIER);
}

APPEND_TEXT void EffectFIELD_BARRIER(void)
{
  if (Duel_TryResolveSpellThroughTraps(FIELD_BARRIER, FIELD_BARRIER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
