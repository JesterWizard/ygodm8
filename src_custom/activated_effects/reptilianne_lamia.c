#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 sLamiaHandZone APPEND_DATA = {0};

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

static u8 InactiveFixedMonsterRow(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return OPPONENT_MONSTER_ROW;

  return PLAYER_MONSTER_ROW;
}

static u8 IsValidOppFaceUpTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveFixedMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return IsFaceUpMonsterZone(zone);
}

static u8 FieldHasOppFaceUpTarget(void)
{
  u8 col;
  u8 row = InactiveFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOppFaceUpTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static void ZeroAtk(struct DuelCard *zone)
{
  u16 atk = gCardData_NEW[zone->id].atk;

  zone->tempStage = (s8)(-((s32)atk + 499) / 500);
}

static void CancelLamiaTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickLamiaTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;
  u8 row = InactiveFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidOppFaceUpTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    atk = gCardData_NEW[zone->id].atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = row;
  *outCol = bestCol;
  return TRUE;
}

static void ResolveLamiaTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *target;
  u16 originalAtk;

  if (!IsValidOppFaceUpTarget(fixedRow, fixedCol))
    return;

  target = gFixedZones[fixedRow][fixedCol];
  originalAtk = gCardData_NEW[target->id].atk;
  ZeroAtk(target);
  RefreshFieldMonsterStatOverlays();

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, sLamiaHandZone, opts) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (originalAtk > 0) {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)originalAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateREPTILIANNE_LAMIA(void)
{
  if (gMonEffect.id != REPTILIANNE_LAMIA)
    return FALSE;

  /* GY synchro-material ATK-0 need synchro hook. Remains.
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
  if (!CanSpecialSummonReptilianneLamiaFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(REPTILIANNE_LAMIA, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  sLamiaHandZone = handZone;
  gDuelCursor.destY = PLAYER_HAND;
  gDuelCursor.destX = handZone;

  Duel_SetupPickZone(IsValidOppFaceUpTarget, ResolveLamiaTarget, CancelLamiaTargeting,
                     AiPickLamiaTarget);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    Duel_RunPickZoneInputLoop();
  else
    Duel_ResolvePickZoneForAi();

  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonReptilianneLamiaFromHand(u8 handZone);
u8 TrySpecialSummonReptilianneLamiaFromHand(u8 handZone);
#endif
