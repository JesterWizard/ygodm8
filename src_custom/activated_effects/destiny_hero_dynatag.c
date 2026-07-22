#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_dynatag.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct DestinyHeroDynatagActionData {
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

extern struct DestinyHeroDynatagActionData sActionData;

static u8 BattleDestroysDynatag(void)
{
  if (sActionData.flags & FLAG_GRAVEYARD_PLAYER) {
    struct DuelCard *zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];

    if (zone != NULL && zone->id == DESTINY_HERO_DYNATAG)
      return TRUE;
  }

  if (sActionData.flags & FLAG_GRAVEYARD_OPPONENT) {
    struct DuelCard *zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

    if (zone != NULL && zone->id == DESTINY_HERO_DYNATAG)
      return TRUE;
  }

  return FALSE;
}

void ApplyDestinyHeroDynatagNoBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (!BattleDestroysDynatag())
    return;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
  }

  if (opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

unsigned char CanActivateDESTINY_HERO_DYNATAG(void)
{
  if (gMonEffect.id != DESTINY_HERO_DYNATAG)
    return FALSE;

  /* No battle damage via ApplyDestinyHeroDynatagNoBattleDamage; FromHand path
   * for 1000 burn. Ceiling: not field-ignition activatable here. */
  return FALSE;
}

void ActivateDESTINY_HERO_DYNATAGEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DYNATAG, 2);
}

u8 CanActivateDestinyHeroDynatagFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  return SixCardHand_ZoneAtHandRow(handRow, handZone)->id == DESTINY_HERO_DYNATAG;
}

u8 TryActivateDestinyHeroDynatagFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateDestinyHeroDynatagFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DYNATAG, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* ponytail: GY banish ATK boost not wired; both players 1000 on FromHand. */
  if (Duel_ChangeLp(ACTIVE_DUELIST, -1000, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -1000, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateDestinyHeroDynatagFromHand(u8 handZone);
u8 TryActivateDestinyHeroDynatagFromHand(u8 handZone);
#endif
