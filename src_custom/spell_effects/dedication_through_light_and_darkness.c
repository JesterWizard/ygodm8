#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dedication_through_light_and_darkness.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static u8 FindDarkMagicianCol(u8 *outCol)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id == DARK_MAGICIAN) {
      *outCol = i;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 HandHasDarkMagicianOfChaos(void)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], DARK_MAGICIAN_OF_CHAOS);
}

static u8 GraveHasDarkMagicianOfChaos(void)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DARK_MAGICIAN_OF_CHAOS;

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_MAGICIAN_OF_CHAOS)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonDarkMagicianOfChaos(void)
{
  if (HandHasDarkMagicianOfChaos())
    return TRUE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN_OF_CHAOS) >= 0)
    return TRUE;

  return GraveHasDarkMagicianOfChaos();
}

static u8 IsDarkMagicianOfChaos(u16 cardId)
{
  return cardId == DARK_MAGICIAN_OF_CHAOS;
}

static s8 PickDarkMagicianOfChaosHandZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == DARK_MAGICIAN_OF_CHAOS)
      return i;
  }

  return -1;
}

static u8 FindGraveyardDarkMagicianOfChaosIndex(u8 fixedDuelist, u8 *outIndex)
{
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_MAGICIAN_OF_CHAOS) {
      *outIndex = i;
      return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateDedicationThroughLightAndDarkness(void)
{
  u8 darkMagicianCol;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!FindDarkMagicianCol(&darkMagicianCol))
    return FALSE;

  return CanSpecialSummonDarkMagicianOfChaos();
}

static void TributeDarkMagician(void)
{
  u8 darkMagicianCol;

  if (!FindDarkMagicianCol(&darkMagicianCol))
    return;

  Duel_DestroyZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][darkMagicianCol], ACTIVE_DUELIST, FALSE);
}

static void ClearDarkMagicianOfChaosSpecialSummonLock(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone->id == DARK_MAGICIAN_OF_CHAOS) {
  /* Special-face-up sets unk4=2 and blocks DMoC's on-summon effect. */
  zone->unk4 = 0;
      return;
    }
  }
}

static void SpecialSummonDarkMagicianOfChaosFromGrave(struct DuelSummonOpts opts)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 graveIndex;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, DARK_MAGICIAN_OF_CHAOS, opts) == DUEL_ACTION_OK)
      ClearDarkMagicianOfChaosSpecialSummonLock();
    return;
  }

  if (!FindGraveyardDarkMagicianOfChaosIndex(fixedDuelist, &graveIndex))
    return;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, graveIndex);
  if (cardId != DARK_MAGICIAN_OF_CHAOS)
    return;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) == DUEL_ACTION_OK)
    ClearDarkMagicianOfChaosSpecialSummonLock();
}

static void SpecialSummonDarkMagicianOfChaos(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonDarkMagicianOfChaos())
    return;

  if (HandHasDarkMagicianOfChaos()) {
    if (WhoseTurn() == DUEL_PLAYER) {
      if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, DARK_MAGICIAN_OF_CHAOS, IsDarkMagicianOfChaos, opts)
          == DUEL_ACTION_OK)
        ClearDarkMagicianOfChaosSpecialSummonLock();
      return;
    }

    {
      s8 handZone = PickDarkMagicianOfChaosHandZone();

      if (handZone >= 0
          && Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK)
        ClearDarkMagicianOfChaosSpecialSummonLock();
    }
    return;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN_OF_CHAOS) >= 0) {
    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, DARK_MAGICIAN_OF_CHAOS, opts) == DUEL_ACTION_OK)
      ClearDarkMagicianOfChaosSpecialSummonLock();
    return;
  }

  SpecialSummonDarkMagicianOfChaosFromGrave(opts);
}

APPEND_TEXT void EffectDEDICATION_THROUGH_LIGHT_AND_DARKNESS(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(DEDICATION_THROUGH_LIGHT_AND_DARKNESS);

  if (IsDuelOver() == TRUE || !CanActivateDedicationThroughLightAndDarkness())
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  TributeDarkMagician();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonDarkMagicianOfChaos();
}
