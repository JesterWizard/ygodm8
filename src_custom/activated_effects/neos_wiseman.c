#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "neos_wiseman.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct NeosWisemanActionData {
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

extern struct NeosWisemanActionData sActionData;

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static struct DuelCard *FindFaceUpCard(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && zone->id == cardId)
      return zone;
  }

  return NULL;
}

unsigned char CanActivateNEOS_WISEMAN(void)
{
  if (gMonEffect.id != NEOS_WISEMAN)
    return FALSE;

  /* Battle burn/heal via ApplyNeosWisemanBattleEffect; effect-destroy immunity
   * via NeosWiseman_PreventsDestroy. */
  return FALSE;
}

u8 NeosWiseman_PreventsDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->isFaceUp && zone->id == NEOS_WISEMAN;
}

void ActivateNEOS_WISEMANEffect(void)
{
  Duel_ShowEffectTextTyped(NEOS_WISEMAN, 2);
}

static void BurnAndHealFromBattledMonster(u16 battledCardId, u8 burnFixed, u8 healFixed)
{
  u16 burn;
  u16 heal;

  if (battledCardId == CARD_NONE)
    return;

  SetCardInfo(battledCardId);
  burn = gCardInfo.atk;
  heal = gCardInfo.def;

  Duel_ShowEffectTextTyped(NEOS_WISEMAN, 2);

  if (burn > 0) {
    if (gDuelLifePoints[burnFixed] <= burn) {
      gDuelLifePoints[burnFixed] = 0;
      sActionData.flags |= burnFixed == DUEL_PLAYER ? FLAG_LOSER_PLAYER : FLAG_LOSER_OPPONENT;
    } else {
      gDuelLifePoints[burnFixed] -= burn;
    }
  }

  if (heal > 0)
    gDuelLifePoints[healFixed] += heal;

  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

void ApplyNeosWisemanBattleEffect(void)
{
  /* End of Damage Step after battling an opponent's monster. */
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == NEOS_WISEMAN && sActionData.opponentCardId != CARD_NONE) {
    BurnAndHealFromBattledMonster(sActionData.opponentCardId, DUEL_OPPONENT, DUEL_PLAYER);
    return;
  }

  if (sActionData.opponentCardId == NEOS_WISEMAN && sActionData.playerCardId != CARD_NONE)
    BurnAndHealFromBattledMonster(sActionData.playerCardId, DUEL_PLAYER, DUEL_OPPONENT);
}

u8 CanSpecialSummonNeosWisemanFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != NEOS_WISEMAN)
    return FALSE;

  if (FindFaceUpCard(ELEMENTAL_HERO_NEOS) == NULL)
    return FALSE;

  if (FindFaceUpCard(YUBEL) == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonNeosWisemanFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *neos;
  struct DuelCard *yubel;
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonNeosWisemanFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(NEOS_WISEMAN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  neos = FindFaceUpCard(ELEMENTAL_HERO_NEOS);
  yubel = FindFaceUpCard(YUBEL);
  if (neos == NULL || yubel == NULL)
    return FALSE;

  ClearZoneAndSendMonToGraveyard2(neos, fixedDuelist);
  ClearZoneAndSendMonToGraveyard2(yubel, fixedDuelist);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonNeosWisemanFromHand(u8 handZone);
u8 TrySpecialSummonNeosWisemanFromHand(u8 handZone);
#endif
