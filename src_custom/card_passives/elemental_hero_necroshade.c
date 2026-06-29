#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "cost_down.h"
#include "a_legendary_ocean.h"
#include "duel.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "elemental_hero_necroshade.h"

extern u8 gElementalHeroNecroshadeUsed;

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_OPPONENT])
    return DUEL_OPPONENT;
  return DUEL_PLAYER;
}

static int LookupRequiredTributes(u8 level)
{
  if (level <= 4)
    return 0;
  if (level <= 6)
    return 1;
  if (level <= 8)
    return 2;
  return 3;
}

static u8 NecroshadeInActiveGraveyard(void)
{
  u8 fixedDuelist = TurnDuelistToFixed(ACTIVE_DUELIST);
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ELEMENTAL_HERO_NECROSHADE)
      return TRUE;
  }

  return FALSE;
}

static u8 QualifiesForNecroshadeSummon(u16 cardId)
{
  if (!Duel_IsElementalHeroCard(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 5;
}

static int BaseRequiredTributesForCard(u16 cardId)
{
  SetCardInfo(cardId);

  if (ShouldApplyCostDownLevelForTribute(cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  gCardInfo.level = GetLegendaryOceanAdjustedLevel(cardId, gCardInfo.level);
  return LookupRequiredTributes(gCardInfo.level);
}

static int BaseRequiredTributesForHandSlot(u8 handSlot, u16 cardId)
{
  SetCardInfo(cardId);

  if (ShouldApplyCostDownForHandSlot(handSlot, cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  gCardInfo.level = GetLegendaryOceanAdjustedLevel(cardId, gCardInfo.level);
  return LookupRequiredTributes(gCardInfo.level);
}

static u8 CanApplyNecroshadeDiscount(int baseTributes)
{
  if (gElementalHeroNecroshadeUsed)
    return FALSE;

  if (baseTributes <= 0)
    return FALSE;

  return NecroshadeInActiveGraveyard();
}

void ElementalHeroNecroshade_Reset(void)
{
  gElementalHeroNecroshadeUsed = FALSE;
}

u8 ElementalHeroNecroshade_CanNormalSummonWithoutTribute(u16 cardId)
{
  if (!QualifiesForNecroshadeSummon(cardId))
    return FALSE;

  return CanApplyNecroshadeDiscount(BaseRequiredTributesForCard(cardId));
}

u8 ElementalHeroNecroshade_CanNormalSummonWithoutTributeForHandSlot(u8 handSlot, u16 cardId)
{
  if (!QualifiesForNecroshadeSummon(cardId))
    return FALSE;

  return CanApplyNecroshadeDiscount(BaseRequiredTributesForHandSlot(handSlot, cardId));
}

u8 ElementalHeroNecroshade_TryConsumeOnNormalSummon(u16 cardId)
{
  if (!ElementalHeroNecroshade_CanNormalSummonWithoutTribute(cardId))
    return FALSE;

  gElementalHeroNecroshadeUsed = TRUE;
  return TRUE;
}

#if !defined(__GNUC__)
#error Elemental HERO Necroshade self-check requires GCC
#elif __GNUC__
void ElementalHeroNecroshade_SelfCheck(void)
{
  if (LookupRequiredTributes(5) != 1)
    while (1)
      ;
}
#endif
