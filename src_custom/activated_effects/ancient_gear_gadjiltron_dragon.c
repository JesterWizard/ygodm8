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

#define GADJILTRON_BURN 700

static u8 IsOppDefMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return zone->isDefending == TRUE;
}

static u8 OppHasDefMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDefMonster(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroyDef(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppDefMonster(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
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

static u8 AiPickDef(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppDefMonster(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void DoBurn(struct DuelCard *self)
{
  if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)GADJILTRON_BURN, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateANCIENT_GEAR_GADJILTRON_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_GADJILTRON_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_GADJILTRON_DRAGON)
    return FALSE;

  /* Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap.
   * ponytail: pierce/burn/draw FALSE.
   * Ceiling: OPT destroy 1 DEF opp (pierce stand-in) OR OPT burn 700. */
  return CanUseMonsterEffect(zone);
}

void ActivateANCIENT_GEAR_GADJILTRON_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GADJILTRON_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (OppHasDefMonster()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsOppDefMonster, ResolveDestroyDef, CancelTargeting, AiPickDef);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  DoBurn(self);
}
