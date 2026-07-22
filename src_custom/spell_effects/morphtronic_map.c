#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "effect.h"
#include "expanded_graveyard.h"
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
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 IsActiveMorphtronicMap(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MORPHTRONIC_MAP && zone->isFaceUp == TRUE;
}

void MorphtronicMap_OnBattlePositionChanged(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (IsActiveMorphtronicMap(zone) && zone->unk4 < 0xFF)
        zone->unk4++;
    }
  }
}

void ApplyMorphtronicMapAtkBonusToCardInfo(const struct DuelCard *zone)
{
  const struct DuelCard *mapZone;
  u32 bonus;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  mapZone = Duel_FindBackrowCardOnField(MORPHTRONIC_MAP, TRUE);
  if (mapZone == NULL)
    return;

  if (!IsMorphtronicMonster(zone->id))
    return;

  bonus = (u32)mapZone->unk4 * MORPHTRONIC_MAP_ATK_PER_COUNTER;
  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + bonus);
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
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u16 FindMorphtronicInGy(u8 fixedDuelist)
{
  if (GraveyardExpand_IsEnabled()) {
    u8 i;
    u8 count = GraveyardExpand_GetCount(fixedDuelist);

    for (i = 0; i < count; i++) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (IsMorphtronicMonster(cardId))
        return cardId;
    }
    return CARD_NONE;
  }

  {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsMorphtronicMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

u8 Cond_MorphtronicMapOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != MORPHTRONIC_MAP)
    return FALSE;

  fixedDuelist = ev->controller;
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
                                         ? ACTIVE_DUELIST_MONSTER_ROW
                                         : INACTIVE_DUELIST_MONSTER_ROW])
      < 0)
    return FALSE;

  return FindMorphtronicInGy(fixedDuelist) != CARD_NONE;
}

enum DuelActionResult Op_MorphtronicMapOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  fixedDuelist = ev->controller;
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  cardId = FindMorphtronicInGy(fixedDuelist);
  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShowEffectText(MORPHTRONIC_MAP);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
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
