#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "felis_lightsworn_archer.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);
void RefreshFieldMonsterStatOverlays(void);

static u8 sFelisMillReentry APPEND_DATA = 0;

void TryApplyFelisAfterDeckMill(u8 turnDuelist, u16 cardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 monsterRow;

  if (sFelisMillReentry || cardId != FELIS_LIGHTSWORN_ARCHER || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  monsterRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                             : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  sFelisMillReentry = TRUE;
  Duel_ShowEffectTextTyped(FELIS_LIGHTSWORN_ARCHER, 8);
  if (Duel_SpecialSummonFromGrave(turnDuelist, FELIS_LIGHTSWORN_ARCHER, opts) == DUEL_ACTION_OK)
    RefreshFieldMonsterStatOverlays();
  sFelisMillReentry = FALSE;
}

static u8 IsValidOppMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOppMonsterTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppMonsterTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidOppMonsterTarget(fixedRow, fixedCol) || target == NULL || self == NULL)
    return;

  MarkMonsterEffectUsed(self);
  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyZone(target, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, 3, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

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

  *outRow = OPPONENT_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppMonsterTarget(OPPONENT_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateFELIS_LIGHTSWORN_ARCHER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != FELIS_LIGHTSWORN_ARCHER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != FELIS_LIGHTSWORN_ARCHER)
    return FALSE;

  /* Deck-mill SS via TryApplyFelisAfterDeckMill (any mill; printed is monster-effect only).
   * Ignition tribute self → destroy 1 opp monster → mill 3. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonsterTarget();
}

void ActivateFELIS_LIGHTSWORN_ARCHEREffect(void)
{
  Duel_ShowEffectTextTyped(FELIS_LIGHTSWORN_ARCHER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidOppMonsterTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
