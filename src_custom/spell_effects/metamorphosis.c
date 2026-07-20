#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidMetamorphosisTributeZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasMetamorphosisTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMetamorphosisTributeZone(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMETAMORPHOSIS(void)
{
  return HasMetamorphosisTribute();
}

static void DestroyMetamorphosisSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == METAMORPHOSIS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishMetamorphosis(u8 tributeRow, u8 tributeCol)
{
  struct DuelCard *tributeZone;
  u8 tributeLevel;

  if (!IsValidMetamorphosisTributeZone(tributeRow, tributeCol)) {
    DestroyMetamorphosisSpellZone();
    return;
  }

  tributeZone = gFixedZones[tributeRow][tributeCol];
  SetCardInfo(tributeZone->id);
  tributeLevel = gCardInfo.level;

  DestroyMetamorphosisSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  /* ponytail: Extra Deck Special Summon (Fusion of matching Level) needs a duel-time
   * Extra Deck browser + SS path. Trunk ExtraDeck_* APIs are deck-builder only and
   * must not be used mid-duel. Ceiling: tribute-only; upgrade: ExtraDeck duel pick
   * filtered by COLOR_FUSION + level == tributeLevel, then Duel_SpecialSummonMonsterId. */
  (void)tributeLevel;
  (void)COLOR_FUSION;
}

static void CancelMetamorphosisTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMetamorphosisSpellZone();
}

static u8 AiPickMetamorphosisTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidMetamorphosisTributeZone(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveMetamorphosisTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidMetamorphosisTributeZone(fixedRow, fixedCol))
    return;

  FinishMetamorphosis(fixedRow, fixedCol);
}

static void METAMORPHOSIS_ResolveBody(void)
{
  Duel_ShowEffectText(METAMORPHOSIS);

  if (IsDuelOver() == TRUE || !CanActivateMETAMORPHOSIS())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMetamorphosisTributeZone, ResolveMetamorphosisTribute,
                     CancelMetamorphosisTargeting, AiPickMetamorphosisTribute);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMETAMORPHOSIS(void)
{
  if (!CanActivateMETAMORPHOSIS()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(METAMORPHOSIS, METAMORPHOSIS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void METAMORPHOSIS_SelfCheck(void)
{
  if (COLOR_FUSION == COLOR_NORMAL)
    while (1)
      ;
}
#endif
