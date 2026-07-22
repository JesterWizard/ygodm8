#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dark_blade_the_dragon_knight.h"
#include "expanded_graveyard.h"

struct DarkBladeActionData {
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

extern struct DarkBladeActionData sActionData;

void UpdateDuelGfxExceptField(void);

static u8 DidDarkBladeDealBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != DARK_BLADE_THE_DRAGON_KNIGHT)
      return FALSE;
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != DARK_BLADE_THE_DRAGON_KNIGHT)
      return FALSE;
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void BanishUpTo3OppMonstersFromGy(u8 oppFixed)
{
  u8 banished = 0;
  u8 i;
  u8 oppTurn = TurnDuelistForFixed(oppFixed);

  if (!GraveyardExpand_IsEnabled()) {
    if (GetTypeGroup(gDuel.duelistbattleState[oppFixed].graveyard) == TYPE_GROUP_MONSTER) {
      Duel_ShowEffectTextTyped(DARK_BLADE_THE_DRAGON_KNIGHT, 2);
      Duel_BanishGraveyardTopTurn(oppTurn);
      UpdateDuelGfxExceptField();
    }
    return;
  }

  for (i = GraveyardExpand_GetCount(oppFixed); i > 0 && banished < 3; i--) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(oppFixed, i - 1)) != TYPE_GROUP_MONSTER)
      continue;
    if (banished == 0)
      Duel_ShowEffectTextTyped(DARK_BLADE_THE_DRAGON_KNIGHT, 2);
    Duel_BanishGraveyardAtFixed(oppFixed, i - 1);
    banished++;
  }

  if (banished > 0)
    UpdateDuelGfxExceptField();
}

void ApplyDarkBladeTheDragonKnightBattleEffect(void)
{
  if (DidDarkBladeDealBattleDamage(DUEL_PLAYER)) {
    BanishUpTo3OppMonstersFromGy(DUEL_OPPONENT);
    return;
  }
  if (DidDarkBladeDealBattleDamage(DUEL_OPPONENT))
    BanishUpTo3OppMonstersFromGy(DUEL_PLAYER);
}

unsigned char CanActivateDARK_BLADE_THE_DRAGON_KNIGHT(void)
{
  if (gMonEffect.id != DARK_BLADE_THE_DRAGON_KNIGHT)
    return FALSE;

  /* Battle-damage GY banish via ApplyDarkBladeTheDragonKnightBattleEffect. */
  return FALSE;
}

void ActivateDARK_BLADE_THE_DRAGON_KNIGHTEffect(void)
{
  Duel_ShowEffectTextTyped(DARK_BLADE_THE_DRAGON_KNIGHT, 2);
}
