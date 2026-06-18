#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "d_d_warrior.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DDWarriorActionData {
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

extern struct DDWarriorActionData sActionData;

void ClearDDWarriorPending(void)
{
  gPendingDDWarriorWarriorRow = D_D_WARRIOR_PENDING_NONE;
  gPendingDDWarriorWarriorCol = 0;
  gPendingDDWarriorOtherRow = D_D_WARRIOR_PENDING_NONE;
  gPendingDDWarriorOtherCol = 0;
}

static void MarkPendingBanish(u8 warriorRow, u8 warriorCol, u8 otherRow, u8 otherCol)
{
  gPendingDDWarriorWarriorRow = warriorRow;
  gPendingDDWarriorWarriorCol = warriorCol;
  gPendingDDWarriorOtherRow = otherRow;
  gPendingDDWarriorOtherCol = otherCol;
}

static u8 IsMonsterVersusMonsterBattle(void)
{
  if (sActionData.playerCardId == CARD_NONE || sActionData.opponentCardId == CARD_NONE)
    return FALSE;

  /* id 1 = atk vs atk (player or opponent turn), 2 = player vs def, 5 = opponent vs def */
  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 5;
}

static u8 ZoneMatchesBattleCard(u8 fixedRow, u8 fixedCol, u16 cardId)
{
  struct DuelCard *zone;

  if (cardId == CARD_NONE || fixedRow >= 5 || fixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  return zone != NULL && zone->id == cardId;
}

static u8 ValidateDDWarriorBattleContext(void)
{
  if (!IsMonsterVersusMonsterBattle())
    return FALSE;

  if (GetTypeGroup(sActionData.playerCardId) != TYPE_GROUP_MONSTER
      || GetTypeGroup(sActionData.opponentCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (sActionData.playerCardId == D_D_WARRIOR) {
    return ZoneMatchesBattleCard(sActionData.playerMonsterRow, sActionData.unkA, D_D_WARRIOR)
        && ZoneMatchesBattleCard(sActionData.opponentMonsterRow, sActionData.unk16,
                                 sActionData.opponentCardId);
  }

  if (sActionData.opponentCardId == D_D_WARRIOR) {
    return ZoneMatchesBattleCard(sActionData.opponentMonsterRow, sActionData.unk16, D_D_WARRIOR)
        && ZoneMatchesBattleCard(sActionData.playerMonsterRow, sActionData.unkA,
                                 sActionData.playerCardId);
  }

  return FALSE;
}

static u8 TryMarkDDWarriorBattleBanish(void)
{
  if (!ValidateDDWarriorBattleContext())
    return FALSE;

  if (sActionData.playerCardId == D_D_WARRIOR) {
    MarkPendingBanish(sActionData.playerMonsterRow, sActionData.unkA,
                      sActionData.opponentMonsterRow, sActionData.unk16);
    return TRUE;
  }

  MarkPendingBanish(sActionData.opponentMonsterRow, sActionData.unk16,
                    sActionData.playerMonsterRow, sActionData.unkA);
  return TRUE;
}

void ResolveDDWarriorBattleEffect(void)
{
  u8 warriorRow;
  u8 warriorCol;
  u8 otherRow;
  u8 otherCol;
  struct DuelCard *warriorZone;
  struct DuelCard *otherZone;

  warriorRow = gPendingDDWarriorWarriorRow;
  if (warriorRow == D_D_WARRIOR_PENDING_NONE)
    return;

  warriorCol = gPendingDDWarriorWarriorCol;
  otherRow = gPendingDDWarriorOtherRow;
  otherCol = gPendingDDWarriorOtherCol;
  ClearDDWarriorPending();

  warriorZone = gFixedZones[warriorRow][warriorCol];
  otherZone = gFixedZones[otherRow][otherCol];

  if (warriorZone->id != D_D_WARRIOR
      || otherZone->id == CARD_NONE
      || GetTypeGroup(otherZone->id) != TYPE_GROUP_MONSTER)
    return;

  Duel_ShowEffectTextTyped(D_D_WARRIOR, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (otherZone->id != CARD_NONE)
    Duel_BanishZone(otherZone, FALSE);
  if (warriorZone->id != CARD_NONE)
    Duel_BanishZone(warriorZone, TRUE);
}

void ApplyDDWarriorBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkDDWarriorBattleBanish()) {
    ClearDDWarriorPending();
    return;
  }

  sActionData.flags &= ~(FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT);
}
