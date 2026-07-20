#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsFaceUpFieldCard(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && zone->isDefending == FALSE)
    return TRUE;

  return FALSE;
}

static u8 TurnDuelistOwningFixedRow(u8 fixedRow)
{
  u8 fixedOwner;

  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    fixedOwner = DUEL_PLAYER;
  else
    fixedOwner = DUEL_OPPONENT;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedOwner])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  return zone != NULL && zone->id != CARD_NONE && IsFaceUpFieldCard(zone);
}

static u8 FieldHasTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
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
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateDARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT)
    return FALSE;

  return CanUseMonsterEffect(zone) && Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0
      && FieldHasTarget();
}

void ActivateDARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE || !FieldHasTarget())
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
