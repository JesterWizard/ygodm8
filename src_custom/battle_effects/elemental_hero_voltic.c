#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_voltic.h"
#include "removed_from_play.h"

struct ElementalHeroVolticActionData {
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

extern struct ElementalHeroVolticActionData sActionData;
extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static u8 IsPlayerAttackAction(u8 id)
{
  return id == 1 || id == 2 || id == 4;
}

static u8 IsOpponentAttackAction(u8 id)
{
  return id == 5 || id == 6;
}

static u8 DidVolticDealBattleDamage(u8 *attackerTurnDuelist)
{
  u16 damage;

  if (IsPlayerAttackAction(sActionData.id)
      && sActionData.playerCardId == ELEMENTAL_HERO_VOLTIC) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage == 0)
      return FALSE;
    *attackerTurnDuelist = ACTIVE_DUELIST;
    return TRUE;
  }

  if (IsOpponentAttackAction(sActionData.id)
      && sActionData.opponentCardId == ELEMENTAL_HERO_VOLTIC) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage == 0)
      return FALSE;
    *attackerTurnDuelist = INACTIVE_DUELIST;
    return TRUE;
  }

  return FALSE;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

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

static s16 FindBanishedElementalHeroIndex(u8 fixedDuelist)
{
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return -1;

  for (i = 0; i < RemovedFromPlay_GetCount(fixedDuelist); i++) {
    if (Duel_IsElementalHeroCard(RemovedFromPlay_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static void TrySpecialSummonBanishedElementalHero(u8 attackerTurnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(attackerTurnDuelist);
  s16 index;
  u16 cardId;
  struct DuelSummonOpts opts;
  u8 monsterRow;

  monsterRow = attackerTurnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                                     : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  index = FindBanishedElementalHeroIndex(fixedDuelist);
  if (index < 0)
    return;

  cardId = RemovedFromPlay_GetCardAt(fixedDuelist, (u8)index);
  RemoveBanishedAt(fixedDuelist, (u8)index);

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(attackerTurnDuelist, cardId, opts);
}

void ApplyElementalHeroVolticBattleEffect(void)
{
  u8 attackerTurnDuelist;

  if (gHideEffectText)
    return;

  if (!DidVolticDealBattleDamage(&attackerTurnDuelist))
    return;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_VOLTIC, 3);
  if (IsDuelOver() == TRUE)
    return;

  TrySpecialSummonBanishedElementalHero(attackerTurnDuelist);
}
