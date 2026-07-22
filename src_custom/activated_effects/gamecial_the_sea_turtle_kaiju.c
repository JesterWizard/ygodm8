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

static const char sKaijuName[] APPEND_RODATA = "Kaiju";

static u8 FixedDuelistForInactive(void)
{
  if (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsKaijuMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sKaijuName);
}

static struct DuelCard *FindOppMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && !IsGodCard(zone->id))
      return zone;
  }

  return NULL;
}

static u8 OppControlsKaiju(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsKaijuMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateGAMECIAL_THE_SEA_TURTLE_KAIJU(void)
{
  if (gMonEffect.id != GAMECIAL_THE_SEA_TURTLE_KAIJU)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

u8 CanSpecialSummonGamecialTheSeaTurtleKaijuFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GAMECIAL_THE_SEA_TURTLE_KAIJU)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (OppControlsKaiju())
    return TRUE;

  return FindOppMonster() != NULL;
}

u8 TrySpecialSummonGamecialTheSeaTurtleKaijuFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *tribute;

  if (!CanSpecialSummonGamecialTheSeaTurtleKaijuFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GAMECIAL_THE_SEA_TURTLE_KAIJU, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!OppControlsKaiju()) {
    tribute = FindOppMonster();
    if (tribute == NULL)
      return FALSE;

    ClearZoneAndSendMonToGraveyard2(tribute, FixedDuelistForInactive());
    NotifyDynamicEquipFieldChanged();

    if (IsDuelOver() == TRUE)
      return TRUE;
  }

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

void ActivateGAMECIAL_THE_SEA_TURTLE_KAIJUEffect(void)
{
  Duel_ShowEffectTextTyped(GAMECIAL_THE_SEA_TURTLE_KAIJU, 2);
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGamecialTheSeaTurtleKaijuFromHand(u8 handZone);
u8 TrySpecialSummonGamecialTheSeaTurtleKaijuFromHand(u8 handZone);
#endif
