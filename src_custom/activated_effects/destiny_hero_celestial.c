#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpOppSpell(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
    return FALSE;

  return zone->isFaceUp || IsCardFaceUp(zone);
}

static u8 FieldHasFaceUpOppSpell(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppSpell(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroySpell(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpOppSpell(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

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
  u8 col;

  *outRow = OPPONENT_BACKROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppSpell(OPPONENT_BACKROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateDESTINY_HERO_CELESTIAL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_CELESTIAL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_CELESTIAL)
    return FALSE;

  /* Ceiling: attack-declare destroy + GY draw-if-no-hand need battle/GY hooks.
   * Ceiling: OPT destroy 1 face-up opp Spell + burn 500. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpOppSpell();
}

void ActivateDESTINY_HERO_CELESTIALEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_CELESTIAL, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpOppSpell, ResolveDestroySpell, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
