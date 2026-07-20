#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "riryoku.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidMystikWokTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 HasMystikWokTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMystikWokTribute(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMYSTIK_WOK(void)
{
  return HasMystikWokTribute();
}

static void DestroyMystikWokSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MYSTIK_WOK)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void GetZoneFinalAtkDef(struct DuelCard *zone, u16 *outAtk, u16 *outDef)
{
  if (zone == NULL || zone->id == CARD_NONE) {
    *outAtk = 0;
    *outDef = 0;
    return;
  }

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  *outAtk = gCardInfo.atk;
  *outDef = gCardInfo.def;
  gSetFinalStatZone = NULL;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = gain ATK, FALSE = gain DEF. */
static u8 PlayerChoosesAtk(void)
{
  /* ponytail: no dedicated ATK/DEF choice UI — A = ATK, B = DEF.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static void FinishMystikWok(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];
  u16 atk;
  u16 def;
  u16 gain;
  u8 chooseAtk;

  if (!IsValidMystikWokTribute(fixedRow, fixedCol)) {
    DestroyMystikWokSpellZone();
    return;
  }

  GetZoneFinalAtkDef(tributeZone, &atk, &def);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chooseAtk = PlayerChoosesAtk();
  else
    chooseAtk = atk >= def; /* AI prefers the larger heal */

  gain = chooseAtk ? atk : def;

  PlayMusic(SFX_TRIBUTE);
  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();

  if (gain > 0) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, (s32)gain, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  DestroyMystikWokSpellZone();
}

static void CancelMystikWokTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMystikWokSpellZone();
}

static u8 AiPickMystikWokTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestGain = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;
    u16 def;
    u16 gain;

    if (!IsValidMystikWokTribute(row, col))
      continue;

    zone = gFixedZones[row][col];
    GetZoneFinalAtkDef(zone, &atk, &def);
    gain = atk >= def ? atk : def;
    if (!found || gain > bestGain) {
      found = TRUE;
      bestGain = gain;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveMystikWokTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidMystikWokTribute(fixedRow, fixedCol))
    return;

  FinishMystikWok(fixedRow, fixedCol);
}

static void MYSTIK_WOK_ResolveBody(void)
{
  Duel_ShowEffectText(MYSTIK_WOK);

  if (IsDuelOver() == TRUE || !CanActivateMYSTIK_WOK())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMystikWokTribute, ResolveMystikWokTribute,
                     CancelMystikWokTargeting, AiPickMystikWokTribute);

  if (WhoseTurn() != DUEL_PLAYER)
    Duel_ResolvePickZoneForAi();
  else
    Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectMYSTIK_WOK(void)
{
  if (!CanActivateMYSTIK_WOK()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MYSTIK_WOK, MYSTIK_WOK_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
