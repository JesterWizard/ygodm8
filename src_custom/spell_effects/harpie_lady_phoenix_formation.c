#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "harpie_lady_phoenix_formation.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_SISTERS
      || cardId == CYBER_SLASH_HARPIE_LADY;
}

static u8 CountHarpieLadyOrSisters(void)
{
  u8 count = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsHarpieLadyOrSisters(zone->id))
      count++;
  }

  return count;
}

static u8 OppMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

u8 CanActivateHARPIE_LADY_PHOENIX_FORMATION(void)
{
  u8 col;

  if (EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION))
    return FALSE;
  if (CountHarpieLadyOrSisters() < 3)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[OppMonsterFixedRow()][col];

    if (zone != NULL && zone->id != CARD_NONE && Duel_SpellMayTargetMonsterZone(zone))
      return TRUE;
  }

  return FALSE;
}

u8 HarpieLadyPhoenixFormation_CannotSpecialSummonFromMainOrExtraDeck(void)
{
  return EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION);
}

u8 HarpieLadyPhoenixFormation_CannotConductBattlePhase(void)
{
  return EffectOpt_IsUsed(HARPIE_LADY_PHOENIX_FORMATION);
}

static void HARPIE_LADY_PHOENIX_FORMATION_ResolveBody(void)
{
  u8 maxTargets = CountHarpieLadyOrSisters();
  u8 destroyed = 0;
  u16 highestAtk = 0;
  u8 col;
  u8 row = OppMonsterFixedRow();

  if (!CanActivateHARPIE_LADY_PHOENIX_FORMATION()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(HARPIE_LADY_PHOENIX_FORMATION);
  if (IsDuelOver() == TRUE)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW && destroyed < maxTargets; col++) {
    struct DuelCard *zone = gFixedZones[row][col];
    u16 atk;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (!Duel_SpellMayTargetMonsterZone(zone))
      continue;

    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (atk > highestAtk)
      highestAtk = atk;

    Duel_DestroyZone(zone, Duel_FixedDuelistForMonsterRow(row), FALSE);
    destroyed++;
    if (IsDuelOver() == TRUE)
      return;
  }

  if (destroyed > 0 && highestAtk > 0) {
    if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)highestAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  EffectOpt_MarkUsed(HARPIE_LADY_PHOENIX_FORMATION);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectHARPIE_LADY_PHOENIX_FORMATION(void)
{
  if (Duel_TryResolveSpellThroughTraps(HARPIE_LADY_PHOENIX_FORMATION,
                                       HARPIE_LADY_PHOENIX_FORMATION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
