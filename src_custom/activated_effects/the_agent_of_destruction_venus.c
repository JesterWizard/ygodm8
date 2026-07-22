#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

#define VENUS_LP_UNIT 500

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindCreationVenusGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == THE_AGENT_OF_CREATION_VENUS)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == THE_AGENT_OF_CREATION_VENUS)
      return (s16)i;
  }

  return -1;
}

static u8 BanishCreationVenusFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  s16 gyIndex = FindCreationVenusGyIndex();
  u16 cardId;

  if (gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  RemovedFromPlay_PushFixed(fixedDuelist, cardId);
  return TRUE;
}

/* no RemovedFromPlay_RemoveAt — shift RFP array in place after SS. */
static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  if (index >= count)
    return;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
}

static s16 FindShineBallBanishedIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return -1;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    if (RemovedFromPlay_GetCardAt(fixedDuelist, i) == MYSTICAL_SHINE_BALL)
      return (s16)i;
  }

  return -1;
}

static s16 FindShineBallGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == MYSTICAL_SHINE_BALL)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == MYSTICAL_SHINE_BALL)
      return (s16)i;
  }

  return -1;
}

static u8 CountAvailableShineBalls(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (RemovedFromPlay_IsEnabled()) {
    for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
      if (RemovedFromPlay_GetCardAt(fixedDuelist, i) == MYSTICAL_SHINE_BALL)
        count++;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == MYSTICAL_SHINE_BALL)
      count++;
  } else {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == MYSTICAL_SHINE_BALL)
        count++;
    }
  }

  return count;
}

static u8 SpecialSummonOneShineBall(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  s16 banishedIndex;
  s16 gyIndex;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  banishedIndex = FindShineBallBanishedIndex();
  if (banishedIndex >= 0) {
    RemoveBanishedAt(fixedDuelist, (u8)banishedIndex);
    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, MYSTICAL_SHINE_BALL, opts)
        == DUEL_ACTION_OK;
  }

  gyIndex = FindShineBallGyIndex();
  if (gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, MYSTICAL_SHINE_BALL, opts)
        == DUEL_ACTION_OK;

  GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, MYSTICAL_SHINE_BALL, opts)
      == DUEL_ACTION_OK;
}

unsigned char CanActivateTHE_AGENT_OF_DESTRUCTION_VENUS(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 emptyZones;
  u8 available;
  u8 maxByLp;

  if (gMonEffect.id != THE_AGENT_OF_DESTRUCTION_VENUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_DESTRUCTION_VENUS)
    return FALSE;

  /* leave-field Deck bottom for Shine Balls needs leave hook.
   * Ceiling: OPT pay 500×N → SS N Mystical Shine Ball from banished/GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gDuelLifePoints[fixedDuelist] < VENUS_LP_UNIT)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  emptyZones = (u8)NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (emptyZones == 0)
    return FALSE;

  available = CountAvailableShineBalls();
  if (available == 0)
    return FALSE;

  maxByLp = (u8)(gDuelLifePoints[fixedDuelist] / VENUS_LP_UNIT);
  return maxByLp > 0;
}

void ActivateTHE_AGENT_OF_DESTRUCTION_VENUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 emptyZones;
  u8 available;
  u8 maxByLp;
  u8 n;
  u8 i;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_DESTRUCTION_VENUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  emptyZones = (u8)NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  available = CountAvailableShineBalls();
  maxByLp = (u8)(gDuelLifePoints[fixedDuelist] / VENUS_LP_UNIT);

  n = emptyZones;
  if (available < n)
    n = available;
  if (maxByLp < n)
    n = maxByLp;

  if (n == 0)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)(n * VENUS_LP_UNIT), TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  for (i = 0; i < n; i++) {
    if (!SpecialSummonOneShineBall())
      break;

    if (IsDuelOver() == TRUE)
      return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonTheAgentOfDestructionVenusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_AGENT_OF_DESTRUCTION_VENUS)
    return FALSE;

  if (FindCreationVenusGyIndex() < 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonTheAgentOfDestructionVenusFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonTheAgentOfDestructionVenusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(THE_AGENT_OF_DESTRUCTION_VENUS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishCreationVenusFromGy())
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonTheAgentOfDestructionVenusFromHand(u8 handZone);
u8 TrySpecialSummonTheAgentOfDestructionVenusFromHand(u8 handZone);
#endif
