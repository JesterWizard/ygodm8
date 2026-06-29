#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_flame_wingman.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ElementalHeroFlameWingmanActionData {
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

extern struct ElementalHeroFlameWingmanActionData sActionData;

void ClearElementalHeroFlameWingmanPending(void)
{
  gPendingElementalHeroFlameWingmanDuelist = ELEMENTAL_HERO_FLAME_WINGMAN_PENDING_NONE;
  gPendingElementalHeroFlameWingmanDestroyedAtk = 0;
  gPendingElementalHeroFlameWingmanEffectCardId = CARD_NONE;
}

static u8 IsElementalHeroBattleBurnCard(u16 cardId)
{
  return cardId == ELEMENTAL_HERO_FLAME_WINGMAN
      || cardId == ELEMENTAL_HERO_SHINING_FLARE_WINGMAN;
}

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u16 GetOriginalCardAtk(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static void MarkPendingBurn(u8 attackingDuelist, u16 destroyedCardId, u16 effectCardId)
{
  u16 destroyedAtk = GetOriginalCardAtk(destroyedCardId);

  if (destroyedAtk == 0)
    return;

  gPendingElementalHeroFlameWingmanDuelist = attackingDuelist;
  gPendingElementalHeroFlameWingmanDestroyedAtk = destroyedAtk;
  gPendingElementalHeroFlameWingmanEffectCardId = effectCardId;
}

void ResolveElementalHeroFlameWingmanBattleEffect(void)
{
  u8 attackingDuelist;
  u8 burnTarget;
  u16 destroyedAtk;

  attackingDuelist = gPendingElementalHeroFlameWingmanDuelist;
  if (attackingDuelist == ELEMENTAL_HERO_FLAME_WINGMAN_PENDING_NONE)
    return;

  destroyedAtk = gPendingElementalHeroFlameWingmanDestroyedAtk;
  burnTarget = attackingDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (gPendingElementalHeroFlameWingmanEffectCardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(gPendingElementalHeroFlameWingmanEffectCardId, 3);
  ClearElementalHeroFlameWingmanPending();

  if (Duel_ChangeLp(burnTarget, -(s32)destroyedAtk, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void ApplyElementalHeroFlameWingmanBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (IsElementalHeroBattleBurnCard(sActionData.playerCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    MarkPendingBurn(DUEL_PLAYER, sActionData.opponentCardId, sActionData.playerCardId);
  } else if (IsElementalHeroBattleBurnCard(sActionData.opponentCardId)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    MarkPendingBurn(DUEL_OPPONENT, sActionData.playerCardId, sActionData.opponentCardId);
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveElementalHeroFlameWingmanBattleEffect();
}
