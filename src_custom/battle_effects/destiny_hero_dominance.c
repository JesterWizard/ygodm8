#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_dominance.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define DOMINANCE_SS_MAX 3

struct DominanceActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct DominanceActionData sActionData;

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 NameAlreadyPicked(u16 cardId, const u16 *picked, u8 pickedCount)
{
  u8 i;

  for (i = 0; i < pickedCount; i++) {
    if (picked[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

static enum DuelActionResult SpecialSummonDestinyHeroFromGy(u8 turnDuelist, u8 gyIndex)
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

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void TryDrawWhenDominanceDestroys(u16 attackerId, u8 attackerFixed)
{
  u8 turnDuelist;

  if (attackerId != DESTINY_HERO_DOMINANCE)
    return;

  turnDuelist = TurnDuelistForFixed(attackerFixed);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOMINANCE, 3);
  Duel_DrawCards(turnDuelist, 1, TRUE);
}

static s8 FindNextDestinyHeroGyIndex(u8 fixedDuelist, const u16 *picked, u8 pickedCount)
{
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return -1;
    if (NameAlreadyPicked(cardId, picked, pickedCount))
      return -1;

    return 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;
    if (NameAlreadyPicked(cardId, picked, pickedCount))
      continue;

    return (s8)i;
  }

  return -1;
}

static void TrySsDestinyHeroesWhenDominanceDestroyed(u8 destroyedFixed)
{
  u8 turnDuelist = TurnDuelistForFixed(destroyedFixed);
  u8 fixedDuelist = destroyedFixed;
  u16 picked[DOMINANCE_SS_MAX];
  u8 pickedCount = 0;
  u8 ss;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  for (ss = 0; ss < DOMINANCE_SS_MAX; ss++) {
    s8 gyIndex = FindNextDestinyHeroGyIndex(fixedDuelist, picked, pickedCount);
    u16 cardId;

    if (gyIndex < 0)
      break;

    cardId = GraveyardExpand_IsEnabled()
        ? GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex)
        : gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (pickedCount == 0) {
      Duel_ShowEffectTextTyped(DESTINY_HERO_DOMINANCE, 4);
      if (IsDuelOver() == TRUE)
        return;
    }

    if (SpecialSummonDestinyHeroFromGy(turnDuelist, (u8)gyIndex) != DUEL_ACTION_OK)
      return;

    picked[pickedCount++] = cardId;
    if (IsDuelOver() == TRUE)
      return;
  }
}

void ApplyDestinyHeroDominanceBattleEffects(void)
{
  if (gHideEffectText)
    return;

  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId != CARD_NONE
      && GetTypeGroup(sActionData.opponentCardId) == TYPE_GROUP_MONSTER) {
    if (sActionData.playerCardId == DESTINY_HERO_DOMINANCE)
      TryDrawWhenDominanceDestroys(sActionData.playerCardId, DUEL_PLAYER);
    else if (sActionData.opponentCardId == DESTINY_HERO_DOMINANCE)
      TryDrawWhenDominanceDestroys(sActionData.opponentCardId, DUEL_OPPONENT);
  }

  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER) && sActionData.playerCardId == DESTINY_HERO_DOMINANCE)
    TrySsDestinyHeroesWhenDominanceDestroyed(DUEL_PLAYER);

  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == DESTINY_HERO_DOMINANCE)
    TrySsDestinyHeroesWhenDominanceDestroyed(DUEL_OPPONENT);
}
