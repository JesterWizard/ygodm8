#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 AllOwnMonstersAreFaceUpReptiles(void)
{
  u8 col;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (!IsFaceUpMonsterZone(zone) || !IsReptileMonster(zone->id))
      return FALSE;

    found = TRUE;
  }

  return found;
}

static u8 IsValidOppFaceUpTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return IsFaceUpMonsterZone(zone);
}

static u8 FieldHasOppFaceUpTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppFaceUpTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ZeroAtk(struct DuelCard *zone)
{
  u16 atk = gCardData_NEW[zone->id].atk;

  zone->tempStage = (s8)(-((s32)atk + 499) / 500);
}

unsigned char CanActivateREPTILIANNE_LAMIA(void)
{
  if (gMonEffect.id != REPTILIANNE_LAMIA)
    return FALSE;

  /* GY synchro-material ATK-0 need synchro hook. Ceiling: remains.
   * FromHand ATK-0 + SS via TrySpecialSummonReptilianneLamiaFromHand; not field-ignition. */
  return FALSE;
}

void ActivateREPTILIANNE_LAMIAEffect(void)
{
  Duel_ShowEffectTextTyped(REPTILIANNE_LAMIA, 2);
}

u8 CanSpecialSummonReptilianneLamiaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != REPTILIANNE_LAMIA)
    return FALSE;

  if (!AllOwnMonstersAreFaceUpReptiles())
    return FALSE;

  if (!FieldHasOppFaceUpTarget())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonReptilianneLamiaFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;
  u16 originalAtk;
  struct DuelCard *target;

  if (!CanSpecialSummonReptilianneLamiaFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(REPTILIANNE_LAMIA, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* FromHand targeting not wired; auto-pick highest original ATK opp. */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (!IsValidOppFaceUpTarget(INACTIVE_DUELIST_MONSTER_ROW, col))
      continue;

    atk = gCardData_NEW[zone->id].atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  target = gFixedZones[INACTIVE_DUELIST_MONSTER_ROW][bestCol];
  originalAtk = gCardData_NEW[target->id].atk;
  ZeroAtk(target);
  RefreshFieldMonsterStatOverlays();

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (originalAtk > 0) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)originalAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
      return TRUE;
  }

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonReptilianneLamiaFromHand(u8 handZone);
u8 TrySpecialSummonReptilianneLamiaFromHand(u8 handZone);
#endif
