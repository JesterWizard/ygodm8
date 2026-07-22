#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsWarriorOrDark(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardHasMonsterType(cardId, TYPE_WARRIOR))
    return TRUE;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].attribute == ATTRIBUTE_SHADOW;
}

static u8 CountWarriorOrDarkInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsWarriorOrDark(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsWarriorOrDark(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 BanishWarriorOrDarkFromGy(u8 need)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (need > 1)
      return FALSE;

    if (!IsWarriorOrDark(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  while (banished < need) {
    u8 i;
    u8 found = FALSE;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 cardId;

      if (!IsWarriorOrDark(GraveyardExpand_GetCardAt(fixedDuelist, i)))
        continue;

      cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      RemovedFromPlay_PushFixed(fixedDuelist, cardId);
      banished++;
      found = TRUE;
      break;
    }

    if (!found)
      break;
  }

  return banished >= need;
}

unsigned char CanActivateDESTINY_HERO_DESTROY_DOGMA(void)
{
  if (gMonEffect.id != DESTINY_HERO_DESTROY_DOGMA)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateDESTINY_HERO_DESTROY_DOGMAEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DESTROY_DOGMA, 2);
}

u8 CanSpecialSummonDestinyHeroDestroyDogmaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DESTINY_HERO_DESTROY_DOGMA)
    return FALSE;

  if (CountWarriorOrDarkInGy() < 3)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDestinyHeroDestroyDogmaFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDestinyHeroDestroyDogmaFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DESTROY_DOGMA, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishWarriorOrDarkFromGy(3))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -2000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDestinyHeroDestroyDogmaFromHand(u8 handZone);
u8 TrySpecialSummonDestinyHeroDestroyDogmaFromHand(u8 handZone);
#endif
