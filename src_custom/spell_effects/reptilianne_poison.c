#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sReptilianneName[] APPEND_RODATA = "Reptilianne";

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 InactiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

/* Attack-position summons keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsReptilianneMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sReptilianneName);
}

static u8 ControlsFaceUpReptilianne(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (!MonsterIsFaceUp(zone))
      continue;

    if (IsReptilianneMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidDefenseTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return zone->isDefending == TRUE;
}

static u8 HasDefenseTarget(void)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDefenseTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateREPTILIANNE_POISON(void)
{
  return ControlsFaceUpReptilianne() && HasDefenseTarget();
}

static void DestroyReptiliannePoisonSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == REPTILIANNE_POISON)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void SetZoneAtkToZero(struct DuelCard *zone)
{
  u16 atk;
  s32 stages;

  atk = Duel_GetZoneFinalAtk(zone);
  if (atk == 0)
    return;

  /* 1 stage ~= 500 ATK; subtract enough perm stages so final ATK clamps to 0. */
  stages = (s32)((atk + 499) / 500);
  while (stages > 0) {
    DecrementPermStage(zone);
    stages--;
  }

  Duel_NotifyMonsterZoneChanged(zone);
  Duel_RefreshMonsterStatOverlays();
}

static void ResolveDefenseTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidDefenseTarget(fixedRow, fixedCol))
    return;

  zone->isFaceUp = TRUE;
  zone->isDefending = FALSE;
  SetZoneAtkToZero(zone);
  DestroyReptiliannePoisonSpellZone();
}

static void CancelReptiliannePoisonTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyReptiliannePoisonSpellZone();
}

static u8 AiPickDefenseTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidDefenseTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void REPTILIANNE_POISON_ResolveBody(void)
{
  Duel_ShowEffectText(REPTILIANNE_POISON);

  if (IsDuelOver() == TRUE || !CanActivateREPTILIANNE_POISON())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidDefenseTarget, ResolveDefenseTarget,
                     CancelReptiliannePoisonTargeting, AiPickDefenseTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectREPTILIANNE_POISON(void)
{
  if (!CanActivateREPTILIANNE_POISON()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(REPTILIANNE_POISON, REPTILIANNE_POISON_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
