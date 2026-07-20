#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActiveTurn(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 GraveyardContainsFearMonger(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_FEAR_MONGER;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_FEAR_MONGER)
      return TRUE;
  }

  return FALSE;
}

static s16 FindOtherDestinyHeroGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsDestinyHeroMonster(top) && top != DESTINY_HERO_FEAR_MONGER)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDestinyHeroMonster(cardId) && cardId != DESTINY_HERO_FEAR_MONGER)
      return (s16)i;
  }

  return -1;
}

static u8 CanSpecialSummonOtherDestinyHero(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

u8 ShouldActivateDestinyHeroFearMongerTurnEffect(void)
{
  u8 fixedDuelist;

  if (gActiveEffect.cardId != DESTINY_HERO_FEAR_MONGER)
    return FALSE;

  if (gActiveEffect.turnRow != 6)
    return FALSE;

  fixedDuelist = FixedDuelistForActiveTurn();

  /* ponytail: no destroyed-by-battle-since-last-Standby tracking; any GY Fear Monger qualifies. */
  if (!GraveyardContainsFearMonger(fixedDuelist))
    return FALSE;

  return FindOtherDestinyHeroGyIndex(fixedDuelist) >= 0
      && CanSpecialSummonOtherDestinyHero(ACTIVE_DUELIST);
}

void ActivateDestinyHeroFearMongerTurnEffect(void)
{
  u8 fixedDuelist = FixedDuelistForActiveTurn();
  s16 gyIndex;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!ShouldActivateDestinyHeroFearMongerTurnEffect())
    return;

  gyIndex = FindOtherDestinyHeroGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_FEAR_MONGER, 9);
  if (IsDuelOver() == TRUE)
    return;

  if (GraveyardExpand_IsEnabled()) {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  } else {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  }

  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}
