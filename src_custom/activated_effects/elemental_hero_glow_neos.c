#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "elemental_hero_glow_neos.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpOppCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return IsCardFaceUp(zone)
      || (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && zone->isDefending == FALSE);
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpOppCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ApplyTypeBonus(struct DuelCard *self, u8 typeGroup)
{
  if (self == NULL)
    return;

  if (typeGroup == TYPE_GROUP_MONSTER) {
    self->unk4 |= ELEMENTAL_HERO_GLOW_NEOS_CANNOT_ATTACK_MARK;
  } else if (typeGroup == TYPE_GROUP_SPELL) {
    self->unk4 |= ELEMENTAL_HERO_GLOW_NEOS_DIRECT_ATTACK_MARK;
  } else if (typeGroup == TYPE_GROUP_TRAP) {
    self->isDefending = TRUE;
    self->isFaceUp = TRUE;
  }
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 typeGroup;

  if (!IsFaceUpOppCard(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  typeGroup = GetTypeGroup(zone->id);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ApplyTypeBonus(self, typeGroup);

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

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpOppCard(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateELEMENTAL_HERO_GLOW_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_GLOW_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_GLOW_NEOS)
    return FALSE;

  /* EP Extra return via TryReturnContactFusionsAtEndPhase; cannot-attack/direct
   * via ElementalHeroGlowNeos_* attack gates. OPT destroy 1 face-up
   * opp + type-branch marks. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasTarget();
}

void ActivateELEMENTAL_HERO_GLOW_NEOSEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_GLOW_NEOS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpOppCard, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
