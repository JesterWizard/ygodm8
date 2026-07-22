#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsFaceUpMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->isFaceUp;
}

static u8 FieldHasFaceUpMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonsterTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTunerMark(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* real Tuner flag / Equip double-attack need Synchro/equip hooks.
   * OPT PickZone mark unk4 as Tuner stand-in. */
  zone->unk4 |= 0x40;

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonsterTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

void TryMorphtronicEarfonOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode)
{
  if (zone == NULL || zone->id != MORPHTRONIC_EARFON || !SummonModeIsSpecial(mode))
    return;

  /* Equip 2-attacks FALSE. On-SS mark self as Tuner (unk4). */
  zone->unk4 |= 0x40;
  Duel_ShowEffectTextTyped(MORPHTRONIC_EARFON, 8);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateMORPHTRONIC_EARFON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_EARFON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_EARFON)
    return FALSE;

  /* On-SS Tuner mark via TryMorphtronicEarfonOnMonsterPlacement.
   * Equip 2-attacks FALSE.
   * OPT PickZone treat face-up as Tuner (unk4). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpMonster();
}

void ActivateMORPHTRONIC_EARFONEffect(void)
{
  Duel_ShowEffectTextTyped(MORPHTRONIC_EARFON, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpMonsterTarget, ResolveTunerMark, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
