#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOppSpellTrapTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER;
}

static u8 FieldHasOppSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapTarget(OPPONENT_BACKROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!IsOppSpellTrapTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
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
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  PlayMusic(SFX_CANCEL);
  if (self != NULL)
    self->unk4 = 1;
}

static u8 AiPickBanishTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppSpellTrapTarget(OPPONENT_BACKROW, col)) {
      *outRow = OPPONENT_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char ShouldActivateDRAGON_SPIRIT_OF_WHITE(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != DRAGON_SPIRIT_OF_WHITE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  /* ponytail: Quick Tribute → SS Blue-Eyes from hand needs tribute/summon hooks. */
  return FieldHasOppSpellTrap();
}

void ActivateDRAGON_SPIRIT_OF_WHITE(void)
{
  Duel_ShowEffectTextTyped(DRAGON_SPIRIT_OF_WHITE, 8);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;

  Duel_SetupPickZone(IsOppSpellTrapTarget, ResolveBanishTarget, CancelTargeting,
                     AiPickBanishTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
