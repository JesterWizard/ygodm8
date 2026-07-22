#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_captain_tenacious.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 sCaptainTenaciousBattleDestroyPending APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 ControlsCaptainTenacious(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monsterRow][col];

    if (zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_CAPTAIN_TENACIOUS)
      return TRUE;
  }

  return FALSE;
}

static s16 FindDestinyHeroGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsDestinyHeroMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDestinyHeroMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonDestinyHeroFromGy(u8 turnDuelist, s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void OnCaptainTenaciousBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || !IsDestinyHeroMonster(ev->cardId))
    return;

  if (ev->controller == DUEL_PLAYER)
    sCaptainTenaciousBattleDestroyPending |= 1;
  else if (ev->controller == DUEL_OPPONENT)
    sCaptainTenaciousBattleDestroyPending |= 2;
}

void DestinyHeroCaptainTenacious_EnsureInit(void)
{
  static u8 inited APPEND_DATA = {0};

  if (inited)
    return;

  inited = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnCaptainTenaciousBattleDestroyed);
}

void TryApplyDestinyHeroCaptainTenaciousStandby(void)
{
  u8 fixed;
  u8 bit;
  u8 turnDuelist;
  s16 gyIndex;

  DestinyHeroCaptainTenacious_EnsureInit();

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    bit = fixed == DUEL_PLAYER ? 1 : 2;

    if ((sCaptainTenaciousBattleDestroyPending & bit) == 0)
      continue;

    turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixed]
        ? ACTIVE_DUELIST
        : INACTIVE_DUELIST;

    if (turnDuelist != ACTIVE_DUELIST)
      continue;

    if (!ControlsCaptainTenacious(turnDuelist))
      continue;

    if (ArchlordKristya_IsSpecialSummonLocked())
      continue;

    gyIndex = FindDestinyHeroGyIndex(fixed);
    if (gyIndex < 0)
      continue;

    sCaptainTenaciousBattleDestroyPending &= (u8)~bit;
    Duel_ShowEffectTextTyped(DESTINY_HERO_CAPTAIN_TENACIOUS, 9);

    if (SpecialSummonDestinyHeroFromGy(turnDuelist, gyIndex) != DUEL_ACTION_OK)
      return;

    UpdateDuelGfxExceptField();
    return;
  }
}
