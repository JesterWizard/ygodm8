#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

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

static u8 IsFaceUpZeroAtkMonster(struct DuelCard *zone)
{
  if (!IsFaceUpMonsterZone(zone))
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return Duel_GetZoneFinalAtk(zone) == 0;
}

static u8 CountFaceUpZeroAtkMonsters(void)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (IsFaceUpZeroAtkMonster(zone))
        count++;
    }
  }

  return count;
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

static u8 TributeFaceUpZeroAtkMonsters(u8 count)
{
  u8 row;
  u8 col;
  u8 tributed = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW && tributed < count; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && tributed < count; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsFaceUpZeroAtkMonster(zone))
        continue;

      if (Duel_DestroyZone(zone, TurnDuelistOwningFixedRow(row), FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;

      tributed++;
    }
  }

  return tributed >= count;
}

static u8 IsValidOppMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return IsFaceUpMonsterZone(zone);
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
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidOppMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
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
    struct DuelCard *zone = gFixedZones[*outRow][col];
    u16 atk;

    if (!IsValidOppMonsterTarget(*outRow, col))
      continue;

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

unsigned char CanActivateREPTILIANNE_VASKII(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != REPTILIANNE_VASKII)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != REPTILIANNE_VASKII)
    return FALSE;

  /* only-SS-by-tribute + unique-on-field need summon/field hooks.
   * OPT destroy 1 face-up opp monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonsterTarget();
}

void ActivateREPTILIANNE_VASKIIEffect(void)
{
  Duel_ShowEffectTextTyped(REPTILIANNE_VASKII, 2);

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

u8 CanSpecialSummonReptilianneVaskiiFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != REPTILIANNE_VASKII)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  /* multi-zone tribute picker not wired; auto-tribute first two 0 ATK. */
  return CountFaceUpZeroAtkMonsters() >= 2;
}

u8 TrySpecialSummonReptilianneVaskiiFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 vaskiiZone;

  if (!CanSpecialSummonReptilianneVaskiiFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(REPTILIANNE_VASKII, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!TributeFaceUpZeroAtkMonsters(2) || IsDuelOver() == TRUE)
    return FALSE;

  NotifyDynamicEquipFieldChanged();

  vaskiiZone = (s8)handZone;
  if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], handZone)->id != REPTILIANNE_VASKII) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (gTurnHands[ACTIVE_DUELIST][i]->id == REPTILIANNE_VASKII) {
        vaskiiZone = (s8)i;
        break;
      }
    }
  }

  if (vaskiiZone < 0)
    return FALSE;

  return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)vaskiiZone, opts) == DUEL_ACTION_OK;
}
