#include "global.h"
#include "andro_sphinx.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "pyramid_of_light.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define ANDRO_SPHINX_LP_COST 500
#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct AndroActionData {
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

extern struct AndroActionData sActionData;

#define ANDRO_SPHINX_LP_COST 500

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanPayAndroSphinxCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] >= ANDRO_SPHINX_LP_COST;
}

unsigned char CanActivateANDRO_SPHINX(void)
{
  if (gMonEffect.id != ANDRO_SPHINX)
    return FALSE;

  /* Battle burn via ApplyAndroSphinxBattleEffect.
   * ponytail: GY SS ban needs summon gate. */
  return FALSE;
}

void ActivateANDRO_SPHINXEffect(void)
{
  Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);
}

static void BurnFixed(u8 fixedDuelist, u16 damage)
{
  if (damage == 0)
    return;
  if (gDuelLifePoints[fixedDuelist] <= damage) {
    gDuelLifePoints[fixedDuelist] = 0;
    sActionData.flags |= fixedDuelist == DUEL_PLAYER ? FLAG_LOSER_PLAYER : FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[fixedDuelist] -= damage;
  }
  gUnk2023EA0.unk0[fixedDuelist].lifePointsAfterDamage = gDuelLifePoints[fixedDuelist];
  if (fixedDuelist == DUEL_PLAYER)
    sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  else
    sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

void ApplyAndroSphinxBattleEffect(void)
{
  u16 burn;

  /* id 2 / 5: attack vs Defense Position. */
  if (sActionData.playerCardId == ANDRO_SPHINX
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.id == 2) {
    burn = gCardData_NEW[sActionData.opponentCardId].atk / 2;
    if (burn != 0) {
      Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);
      BurnFixed(DUEL_OPPONENT, burn);
    }
    return;
  }

  if (sActionData.opponentCardId == ANDRO_SPHINX
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.id == 5) {
    burn = gCardData_NEW[sActionData.playerCardId].atk / 2;
    if (burn != 0) {
      Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);
      BurnFixed(DUEL_PLAYER, burn);
    }
  }
}

u8 CanSpecialSummonAndroSphinxFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ANDRO_SPHINX)
    return FALSE;

  if (!IsPyramidOfLightActiveOnField())
    return FALSE;

  if (!CanPayAndroSphinxCost())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAndroSphinxFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *summoned;
  u8 col;

  if (!CanSpecialSummonAndroSphinxFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ANDRO_SPHINX, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)ANDRO_SPHINX_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  /* Cannot attack the turn it is Summoned (unk4 stand-in). */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    summoned = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (summoned != NULL && summoned->id == ANDRO_SPHINX) {
      summoned->unk4 |= 0x80;
      break;
    }
  }

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAndroSphinxFromHand(u8 handZone);
u8 TrySpecialSummonAndroSphinxFromHand(u8 handZone);
#endif
