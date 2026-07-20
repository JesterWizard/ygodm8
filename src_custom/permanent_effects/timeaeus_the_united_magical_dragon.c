#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 RivalFixedBackrow(void)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(SelfZone(), &fixedRow, &col))
    return OPPONENT_BACKROW;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsOppSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != RivalFixedBackrow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER;
}

static u8 FieldHasOppSpellTrap(void)
{
  u8 col;
  u8 row = RivalFixedBackrow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = SelfZone();
  u8 graveyardDuelist;

  if (!IsOppSpellTrapTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  graveyardDuelist = (gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? INACTIVE_DUELIST
      : ACTIVE_DUELIST;

  if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    self->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  struct DuelCard *self = SelfZone();

  PlayMusic(SFX_CANCEL);
  if (self != NULL)
    self->unk4 = 1;
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = RivalFixedBackrow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapTarget(row, col)) {
      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char ShouldActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != TIMEAEUS_THE_UNITED_MAGICAL_DRAGON)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  /* ponytail: unaffected-after-SS + battle ATK boost need continuous/battle hooks. */
  return FieldHasOppSpellTrap();
}

void ActivateTIMEAEUS_THE_UNITED_MAGICAL_DRAGON(void)
{
  Duel_ShowEffectTextTyped(TIMEAEUS_THE_UNITED_MAGICAL_DRAGON, 8);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;

  Duel_SetupPickZone(IsOppSpellTrapTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
