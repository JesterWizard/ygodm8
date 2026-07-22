#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_dusktopia.h"
#include "duel_helpers.h"

static u8 ControllerHasFaceUpDusktopia(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_DUSKTOPIA)
      return TRUE;
  }

  return FALSE;
}

static u8 IsDusktopiaProtected(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 fixedDuelist;

  if (zone == NULL || !(zone->unk4 & DESTINY_HERO_DUSKTOPIA_PROTECT_MARK))
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  return ControllerHasFaceUpDusktopia(fixedDuelist);
}

u8 DestinyHeroDusktopia_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return IsDusktopiaProtected(zone);
}

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DestinyHeroDusktopiaActionData {
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

extern struct DestinyHeroDusktopiaActionData sActionData;

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

void ApplyDestinyHeroDusktopiaNoBattleDamage(void)
{
  struct DuelCard *playerMon = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  struct DuelCard *oppMon = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
  u16 playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  u16 oppDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  if (playerDamage > 0 && IsDusktopiaProtected(playerMon)) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
  }

  if (oppDamage > 0 && IsDusktopiaProtected(oppMon)) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

void TryClearDestinyHeroDusktopiaProtectionEndPhase(void)
{
  u8 fixedRow;
  u8 col;

  for (fixedRow = OPPONENT_MONSTER_ROW; fixedRow <= PLAYER_MONSTER_ROW; fixedRow++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[fixedRow][col];

      if (zone != NULL && (zone->unk4 & DESTINY_HERO_DUSKTOPIA_PROTECT_MARK))
        zone->unk4 &= (u8)~DESTINY_HERO_DUSKTOPIA_PROTECT_MARK;
    }
  }
}
