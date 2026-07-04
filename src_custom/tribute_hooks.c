#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "mask_of_restrict.h"
#include "soul_exchange.h"
#include "cost_down.h"
#include "a_legendary_ocean.h"
#include "debug_ruleset.h"
#include "elemental_hero_necroshade.h"
#include "tribute.h"
#include "summon_tribute.h"
#include "ai_actions.h"

extern unsigned char gNumTributes;

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;
unsigned char GetKaiserSeaHorseTributeCount(u16 cardId);
u8 DoubleCostonCoversDarkTributeSummon(u16 summonCardId, u16 tributeCardId);

void ResetNumTributes(void);
int GetNumRequiredTributes(unsigned short cardId);

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

static u8 CountActiveDuelistHandCards(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id != CARD_NONE)
      count++;
  }

  return count;
}

static u8 SwiftGaiaCanSummonWithoutTribute(u16 cardId)
{
  return cardId == SWIFT_GAIA_THE_FIERCE_KNIGHT
      && CountActiveDuelistHandCards() == 1;
}

/* Cyber Dragon: if only opponent controls a monster, you can Special Summon this card. */
static u8 CyberDragonCanSummonWithoutTribute(u16 cardId)
{
  u8 i;
  u8 playerHasMonster = FALSE;
  u8 opponentHasMonster = FALSE;

  if (cardId != CYBER_DRAGON)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      playerHasMonster = TRUE;
    if (gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      opponentHasMonster = TRUE;
  }

  return !playerHasMonster && opponentHasMonster;
}

static int GetBaseRequiredTributes(u16 cardId)
{
  if (SwiftGaiaCanSummonWithoutTribute(cardId))
    return 0;

  if (CyberDragonCanSummonWithoutTribute(cardId))
    return 0;

  if (ElementalHeroNecroshade_CanNormalSummonWithoutTribute(cardId))
    return 0;

  /* Can Tribute Summon by Tributing 1 monster (printed Level 10 would need 3). */
  if (cardId == THE_TYRANT_NEPTUNE)
    return 1;

  if (ShouldApplyCostDownLevelForTribute(cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  gCardInfo.level = GetLegendaryOceanAdjustedLevel(cardId, gCardInfo.level);

  return LookupRequiredTributes(gCardInfo.level);
}

int GetNumRequiredTributesWithCostDown(u16 cardId)
{
  SetCardInfo(cardId);
  return GetBaseRequiredTributes(cardId);
}

int GetNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId)
{
  SetCardInfo(cardId);

  if (SwiftGaiaCanSummonWithoutTribute(cardId))
    return 0;

  if (CyberDragonCanSummonWithoutTribute(cardId))
    return 0;

  if (ElementalHeroNecroshade_CanNormalSummonWithoutTributeForHandSlot(handSlot, cardId))
    return 0;

  if (cardId == THE_TYRANT_NEPTUNE)
    return 1;

  if (ShouldApplyCostDownForHandSlot(handSlot, cardId))
    gCardInfo.level = GetCostDownAdjustedLevel(cardId, gCardInfo.level);

  gCardInfo.level = GetLegendaryOceanAdjustedLevel(cardId, gCardInfo.level);

  return LookupRequiredTributes(gCardInfo.level);
}

LYN_REPLACE_CHECK(GetNumRequiredTributes);
int GetNumRequiredTributes__Replacement(unsigned short cardId)
{
  return GetNumRequiredTributesWithCostDown(cardId);
}

LYN_REPLACE_CHECK(ResetNumTributes);
void ResetNumTributes__Replacement(void)
{
  gNumTributes = 0;
  ClearDoubleCostonDarkBonusPaid();
  ClearSoulExchangeTributeCredit();
  ClearSoulExchange();
}

LYN_REPLACE_CHECK(IncrementNumTributes);
void IncrementNumTributes__Replacement(void)
{
  gNumTributes++;
}

static u8 AiUsesDoubleCostonForOneTributeDarkSummon(u16 summonCardId)
{
  u8 tributeRow;
  u8 tributeCol;
  u16 tributeCardId;

  if (sAI_Command.action != AI_ACTION_1_TRIBUTE_SUMMON
      && sAI_Command.action != AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON)
    return FALSE;

  if (gTurnZones[sAI_Command.zone1Position >> 4][sAI_Command.zone1Position & 0xF]->id
      != summonCardId)
    return FALSE;

  tributeRow = sAI_Command.zone2Position >> 4;
  tributeCol = sAI_Command.zone2Position & 0xF;
  tributeCardId = gTurnZones[tributeRow][tributeCol]->id;

  return DoubleCostonCoversDarkTributeSummon(summonCardId, tributeCardId);
}

int AdjustRequiredTributesForDoubleCoston(u16 cardId, int requiredTributes)
{
  if (requiredTributes == 2 && AiUsesDoubleCostonForOneTributeDarkSummon(cardId))
    return 1;

  return requiredTributes;
}

static int SubtractPaidTributesForCard(int requiredTributes, u16 summonCardId)
{
  int paidTributes = (int)gNumTributes;

  if (gSoulExchangeTributeCredit)
    paidTributes++;

  if (GetDoubleCostonDarkBonusPaid() > 0 && summonCardId != CARD_NONE
      && CardQualifiesForDoubleCostonDarkBonus(summonCardId))
    paidTributes += GetDoubleCostonDarkBonusPaid();

  requiredTributes -= paidTributes;

  if (requiredTributes < 0)
    requiredTributes = 0;

  if (requiredTributes > 0 && IsMaskOfRestrictActiveOnField())
    return MASK_OF_RESTRICT_TRIBUTE_BLOCK;

  return (unsigned char)requiredTributes;
}

static int SubtractPaidTributes(int requiredTributes)
{
  return SubtractPaidTributesForCard(requiredTributes, CARD_NONE);
}

int GetMonsterNumRequiredTributesForHandSlot(u8 handSlot, u16 cardId)
{
  int requiredTributes;

  if (DebugRuleset_IsDuelistKingdom())
    return SubtractPaidTributes(0);

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  if (gCostDownActive && ShouldApplyCostDownForHandSlot(handSlot, cardId))
    requiredTributes = GetNumRequiredTributesForHandSlot(handSlot, cardId);
  else
    requiredTributes = GetNumRequiredTributesWithCostDown(cardId);

  return AdjustRequiredTributesForDoubleCoston(cardId,
      SubtractPaidTributesForCard(requiredTributes, cardId));
}

LYN_REPLACE_CHECK(GetMonsterNumRequiredTributes);
int GetMonsterNumRequiredTributes__Replacement(unsigned short cardId)
{
  int requiredTributes;

  if (DebugRuleset_IsDuelistKingdom())
    return SubtractPaidTributes(0);

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return 0;

  requiredTributes = GetNumRequiredTributesWithCostDown(cardId);

  return AdjustRequiredTributesForDoubleCoston(cardId,
      SubtractPaidTributesForCard(requiredTributes, cardId));
}
