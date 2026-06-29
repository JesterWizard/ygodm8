#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_magician_of_chaos.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DarkMagicianOfChaosActionData {
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

extern struct DarkMagicianOfChaosActionData sActionData;

void ClearDarkMagicianOfChaosPending(void)
{
  gPendingDarkMagicianOfChaosBanishRow = DARK_MAGICIAN_OF_CHAOS_PENDING_NONE;
  gPendingDarkMagicianOfChaosBanishCol = 0;
}

static void MarkPendingBanish(u8 row, u8 col)
{
  gPendingDarkMagicianOfChaosBanishRow = row;
  gPendingDarkMagicianOfChaosBanishCol = col;
}

static u8 IsMonsterVersusMonsterBattle(void)
{
  if (sActionData.playerCardId == CARD_NONE || sActionData.opponentCardId == CARD_NONE)
    return FALSE;

  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 5;
}

static u8 BattleZoneIsDarkMagicianOfChaos(u8 row, u8 col)
{
  struct DuelCard *zone;

  if (row >= 5 || col >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[row][col];
  return zone != NULL && zone->id == DARK_MAGICIAN_OF_CHAOS;
}

static u8 BattleZoneIsMonster(u8 row, u8 col)
{
  struct DuelCard *zone;

  if (row >= 5 || col >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[row][col];
  return zone != NULL && zone->id != CARD_NONE
      && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 TryMarkDarkMagicianOfChaosBattleBanish(void)
{
  if (!IsMonsterVersusMonsterBattle())
    return FALSE;

  if (BattleZoneIsDarkMagicianOfChaos(sActionData.playerMonsterRow, sActionData.unkA)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && BattleZoneIsMonster(sActionData.opponentMonsterRow, sActionData.unk16)) {
    MarkPendingBanish(sActionData.opponentMonsterRow, sActionData.unk16);
    sActionData.flags &= ~FLAG_GRAVEYARD_OPPONENT;
    return TRUE;
  }

  if (BattleZoneIsDarkMagicianOfChaos(sActionData.opponentMonsterRow, sActionData.unk16)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && BattleZoneIsMonster(sActionData.playerMonsterRow, sActionData.unkA)) {
    MarkPendingBanish(sActionData.playerMonsterRow, sActionData.unkA);
    sActionData.flags &= ~FLAG_GRAVEYARD_PLAYER;
    return TRUE;
  }

  return FALSE;
}

u8 DarkMagicianOfChaosBattleZoneIsPendingBanish(u8 row, u8 col)
{
  return row == gPendingDarkMagicianOfChaosBanishRow
      && col == gPendingDarkMagicianOfChaosBanishCol
      && row != DARK_MAGICIAN_OF_CHAOS_PENDING_NONE;
}

void ResolveDarkMagicianOfChaosBattleEffect(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  row = gPendingDarkMagicianOfChaosBanishRow;
  if (row == DARK_MAGICIAN_OF_CHAOS_PENDING_NONE)
    return;

  col = gPendingDarkMagicianOfChaosBanishCol;
  ClearDarkMagicianOfChaosPending();

  zone = gFixedZones[row][col];
  if (zone == NULL || zone->id == CARD_NONE
      || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  Duel_BanishZone(zone, TRUE);
}

void ApplyDarkMagicianOfChaosBattleEffect(void)
{
  if (!TryMarkDarkMagicianOfChaosBattleBanish())
    ClearDarkMagicianOfChaosPending();
}
