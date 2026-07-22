#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sTheAgentName[] APPEND_RODATA = "The Agent";
static const char sHyperionName[] APPEND_RODATA = "Hyperion";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 SanctuaryOnFieldOrGy(void)
{
  u8 fixed;
  u8 i;

  if (Duel_IsBackrowCardOnField(THE_SANCTUARY_IN_THE_SKY, FALSE))
    return TRUE;

  for (fixed = 0; fixed < 2; fixed++) {
    if (!GraveyardExpand_IsEnabled()) {
      if (gDuel.duelistbattleState[fixed].graveyard == THE_SANCTUARY_IN_THE_SKY)
        return TRUE;
      continue;
    }

    for (i = 0; i < GraveyardExpand_GetCount(fixed); i++) {
      if (GraveyardExpand_GetCardAt(fixed, i) == THE_SANCTUARY_IN_THE_SKY)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 IsTheAgentExceptNeptune(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == THE_AGENT_OF_LIFE_NEPTUNE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u8 IsHyperionMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHyperionName);
}

static u8 HasAgentOrHyperionTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 allowHyperion = SanctuaryOnFieldOrGy();

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if (IsTheAgentExceptNeptune(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;

    if (allowHyperion && IsHyperionMonster(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsTheAgentExceptNeptune(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;

    if (allowHyperion && IsHyperionMonster(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;

    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsTheAgentExceptNeptune(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;

    if (allowHyperion && IsHyperionMonster(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;
  }

  return FALSE;
}

static u8 SpecialSummonAgentOrHyperion(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 allowHyperion = SanctuaryOnFieldOrGy();

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if ((IsTheAgentExceptNeptune(cardId)
         || (allowHyperion && IsHyperionMonster(cardId)))
        && !Duel_CardCannotBeSpecialSummoned(cardId)) {
      return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, i, opts) == DUEL_ACTION_OK;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if ((IsTheAgentExceptNeptune(cardId)
         || (allowHyperion && IsHyperionMonster(cardId)))
        && !Duel_CardCannotBeSpecialSummoned(cardId)) {
      return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_OK;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if ((IsTheAgentExceptNeptune(cardId)
         || (allowHyperion && IsHyperionMonster(cardId)))
        && !Duel_CardCannotBeSpecialSummoned(cardId)) {
      cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_OK;
    }
  }

  return FALSE;
}

unsigned char CanActivateTHE_AGENT_OF_LIFE_NEPTUNE(void)
{
  if (gMonEffect.id != THE_AGENT_OF_LIFE_NEPTUNE)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateTHE_AGENT_OF_LIFE_NEPTUNEEffect(void)
{
  Duel_ShowEffectTextTyped(THE_AGENT_OF_LIFE_NEPTUNE, 2);
}

u8 CanSpecialSummonTheAgentOfLifeNeptuneFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_AGENT_OF_LIFE_NEPTUNE)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasAgentOrHyperionTarget();
}

u8 TrySpecialSummonTheAgentOfLifeNeptuneFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanSpecialSummonTheAgentOfLifeNeptuneFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_LIFE_NEPTUNE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!SpecialSummonAgentOrHyperion())
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonTheAgentOfLifeNeptuneFromHand(u8 handZone);
u8 TrySpecialSummonTheAgentOfLifeNeptuneFromHand(u8 handZone);
#endif
