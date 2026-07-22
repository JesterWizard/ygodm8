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

static u8 IsFaceUpOppMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 FieldHasFaceUpOppMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppMonster(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpOppMonster(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

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
  s8 bestCol = -1;
  u16 bestAtk = 0;

  *outRow = OPPONENT_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsFaceUpOppMonster(OPPONENT_MONSTER_ROW, col))
      continue;

    zone = gFixedZones[OPPONENT_MONSTER_ROW][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol < 0 || atk > bestAtk) {
      bestCol = (s8)col;
      bestAtk = atk;
    }
  }

  if (bestCol < 0)
    return FALSE;

  *outCol = (u8)bestCol;
  return TRUE;
}

unsigned char CanActivateHELSHADDOLL_HOLLOW(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HELSHADDOLL_HOLLOW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HELSHADDOLL_HOLLOW)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT banish 1 face-up opp monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpOppMonster();
}

void ActivateHELSHADDOLL_HOLLOWEffect(void)
{
  Duel_ShowEffectTextTyped(HELSHADDOLL_HOLLOW, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpOppMonster, ResolveBanishTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
