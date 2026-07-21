#include "global.h"
#include "common-chax.h"
#include "alector_sovereign_of_birds.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

u32 NumFaceUpMatchingAttributeInRow(u8, u8);

#define ALECTOR_NEGATE_MARK 0x80

void Alector_ClearNegateMarksAtTurnBoundary(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && (zone->unk4 & ALECTOR_NEGATE_MARK))
        zone->unk4 = (u8)(zone->unk4 & (u8)~ALECTOR_NEGATE_MARK);
    }
  }

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && (zone->unk4 & ALECTOR_NEGATE_MARK))
        zone->unk4 = (u8)(zone->unk4 & (u8)~ALECTOR_NEGATE_MARK);
    }
  }
}

static u8 OpponentHasTwoFaceUpSameAttribute(void)
{
  u8 attribute;

  for (attribute = ATTRIBUTE_SHADOW; attribute <= ATTRIBUTE_DIVINE; attribute++) {
    if (NumFaceUpMatchingAttributeInRow(INACTIVE_DUELIST_MONSTER_ROW, attribute) >= 2)
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasFaceUpAlector(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == ALECTOR_SOVEREIGN_OF_BIRDS && IsCardFaceUp(zone))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 IsValidNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsCardFaceUp(zone);
}

static u8 FieldHasNegateTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col))
        return TRUE;
    }
  }

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveNegateTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidNegateTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* Negate mark cleared at turn boundary via Alector_ClearNegateMarksAtTurnBoundary. */
  zone->unk4 |= ALECTOR_NEGATE_MARK;

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

static u8 AiPickNegateTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = PLAYER_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidNegateTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateALECTOR_SOVEREIGN_OF_BIRDS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ALECTOR_SOVEREIGN_OF_BIRDS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ALECTOR_SOVEREIGN_OF_BIRDS)
    return FALSE;

  /* Hand SS when opp has 2+ same Attribute uses FromHand path. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasNegateTarget();
}

void ActivateALECTOR_SOVEREIGN_OF_BIRDSEffect(void)
{
  Duel_ShowEffectTextTyped(ALECTOR_SOVEREIGN_OF_BIRDS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidNegateTarget, ResolveNegateTarget, CancelTargeting,
                     AiPickNegateTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

u8 CanSpecialSummonAlectorSovereignOfBirdsFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ALECTOR_SOVEREIGN_OF_BIRDS)
    return FALSE;

  if (!OpponentHasTwoFaceUpSameAttribute())
    return FALSE;

  if (FieldHasFaceUpAlector())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAlectorSovereignOfBirdsFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAlectorSovereignOfBirdsFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ALECTOR_SOVEREIGN_OF_BIRDS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAlectorSovereignOfBirdsFromHand(u8 handZone);
u8 TrySpecialSummonAlectorSovereignOfBirdsFromHand(u8 handZone);
#endif
