#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define PLASMA_TRIBUTE_COST 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountOwnFieldMonsters(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

static u8 PayThreeTributes(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 col;
  u8 paid = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW && paid < PLASMA_TRIBUTE_COST; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == CARD_NONE)
      continue;

    ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
    paid++;

    if (IsDuelOver() == TRUE)
      return FALSE;
  }

  return paid >= PLASMA_TRIBUTE_COST;
}

static u8 IsOppMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOppMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppMonsterTarget(OPPONENT_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  /* Printed remainder omitted by this ruleset. */
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
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsOppMonsterTarget(OPPONENT_MONSTER_ROW, col))
      continue;

    zone = gFixedZones[OPPONENT_MONSTER_ROW][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = OPPONENT_MONSTER_ROW;
  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateDESTINY_HERO_PLASMA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_PLASMA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_PLASMA)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOppMonster();
}

void ActivateDESTINY_HERO_PLASMAEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_PLASMA, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOppMonsterTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

u8 CanSpecialSummonDestinyHeroPlasmaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DESTINY_HERO_PLASMA)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return CountOwnFieldMonsters() >= PLASMA_TRIBUTE_COST;
}

u8 TrySpecialSummonDestinyHeroPlasmaFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDestinyHeroPlasmaFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_PLASMA, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!PayThreeTributes())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDestinyHeroPlasmaFromHand(u8 handZone);
u8 TrySpecialSummonDestinyHeroPlasmaFromHand(u8 handZone);
#endif
