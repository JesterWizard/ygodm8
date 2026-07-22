#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 PandemoniumOnField(void)
{
  return Duel_IsBackrowCardOnField(PANDEMONIUM, FALSE);
}

static struct DuelCard *FindFaceUpWarriorOfZera(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == WARRIOR_OF_ZERA && zone->isFaceUp)
      return zone;
  }

  return NULL;
}

unsigned char CanActivateMAZERA_DEVILLE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAZERA_DEVILLE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAZERA_DEVILLE)
    return FALSE;

  /* on-SS-with-Pandemonium discard-3 needs summon hook. Ceiling: OPT
   * discard 1 random opp + mill 3. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return FALSE;

  return TRUE;
}

void ActivateMAZERA_DEVILLEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MAZERA_DEVILLE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardRandomFromHand(INACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, 3, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonMazeraDevilleFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MAZERA_DEVILLE)
    return FALSE;

  if (!PandemoniumOnField())
    return FALSE;

  if (FindFaceUpWarriorOfZera() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonMazeraDevilleFromHand(u8 handZone)
{
  struct DuelCard *zera;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonMazeraDevilleFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MAZERA_DEVILLE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  zera = FindFaceUpWarriorOfZera();
  if (zera == NULL)
    return FALSE;

  ClearZoneAndSendMonToGraveyard2(zera, fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonMazeraDevilleFromHand(u8 handZone);
u8 TrySpecialSummonMazeraDevilleFromHand(u8 handZone);
#endif
