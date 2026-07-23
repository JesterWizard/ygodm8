#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "effect.h"
#include "harpies_hunting_ground.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);

static u8 sHarpiesHuntingGroundSummonController APPEND_DATA = {0xFF};

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  /* Name=Harpie Lady while on field/GY (Perfumer / Queen / …). */
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS
      || cardId == CYBER_SLASH_HARPIE_LADY || cardId == CYBER_SLASH_HARPY_LADY
      || cardId == HARPIE_PERFUMER || cardId == HARPIE_QUEEN || cardId == HARPIE_DANCER
      || cardId == HARPIE_ORACLE || cardId == HARPIE_CONDUCTOR || cardId == HARPIE_CHANNELER
      || cardId == HARPIE_HARPIST;
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
  if (cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE || cardId == SKYSCRAPER_2_HERO_CITY
      || cardId == SKYSCRAPER || cardId == WETLANDS || cardId == GEARTOWN || cardId == DRAGON_RAVINE
      || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS)
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

void ApplyHarpiesHuntingGroundStatBonusToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || !Duel_CardHasMonsterType(zone->id, TYPE_WINGED_BEAST))
    return;
  if (Duel_FindBackrowCardOnField(HARPIES_HUNTING_GROUND, TRUE) == NULL)
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + HARPIES_HUNTING_GROUND_STAT_BONUS);
  gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def + HARPIES_HUNTING_GROUND_STAT_BONUS);
}

static u8 IsHarpiesHuntingGroundDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if ((fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
      || fixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id != CARD_NONE && !Duel_ZoneIsImmuneToSpellEffects(zone);
}

static u8 HasHarpiesHuntingGroundDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsHarpiesHuntingGroundDestroyTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveHarpiesHuntingGroundDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_ClearPickZone();
  if (!IsHarpiesHuntingGroundDestroyTarget(fixedRow, fixedCol))
    return;

  Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(fixedRow), FALSE);
  UpdateDuelGfxExceptField();
}

static u8 AiPickHarpiesHuntingGroundDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsHarpiesHuntingGroundDestroyTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

u8 Cond_HarpiesHuntingGroundOnHarpieSummon(struct EffectCtx *ctx)
{
  if (ctx == NULL || ctx->event == NULL)
    return FALSE;
  if (ctx->event->controller > DUEL_OPPONENT || !IsHarpieLadyOrSisters(ctx->event->cardId))
    return FALSE;
  if (Duel_FindBackrowCardOnField(HARPIES_HUNTING_GROUND, TRUE) == NULL)
    return FALSE;

  return HasHarpiesHuntingGroundDestroyTarget();
}

enum DuelActionResult Op_HarpiesHuntingGroundOnHarpieSummon(struct EffectCtx *ctx)
{
  struct DuelCard *huntingGround;
  u8 row;
  u8 col;

  if (!Cond_HarpiesHuntingGroundOnHarpieSummon(ctx))
    return DUEL_ACTION_NO_TARGET;

  huntingGround = Duel_FindBackrowCardOnField(HARPIES_HUNTING_GROUND, TRUE);
  if (huntingGround == NULL || !Duel_FindFixedZone(huntingGround, &row, &col))
    return DUEL_ACTION_NO_TARGET;

  sHarpiesHuntingGroundSummonController = ctx->event->controller;
  Duel_ShowEffectText(HARPIES_HUNTING_GROUND);
  gDuelCursor.destY = row;
  gDuelCursor.destX = col;
  Duel_SetupPickZone(IsHarpiesHuntingGroundDestroyTarget,
                     ResolveHarpiesHuntingGroundDestroyTarget,
                     Duel_ClearPickZone,
                     AiPickHarpiesHuntingGroundDestroyTarget);
  if (sHarpiesHuntingGroundSummonController == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  return DUEL_ACTION_OK;
}

static void HARPIES_HUNTING_GROUND_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(HARPIES_HUNTING_GROUND);
}

APPEND_TEXT void EffectHARPIES_HUNTING_GROUND(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIES_HUNTING_GROUND,
                                       HARPIES_HUNTING_GROUND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HARPIES_HUNTING_GROUND_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(HARPIE_LADY, TYPE_WINGED_BEAST))
    while (1)
      ;
  if (Duel_CardHasMonsterType(DARK_MAGICIAN, TYPE_WINGED_BEAST))
    while (1)
      ;
  if (!IsHarpieLadyOrSisters(HARPIE_LADY_1))
    while (1)
      ;
}
#endif
