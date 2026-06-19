#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "lesser_fiend.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct LesserFiendActionData {
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

extern struct LesserFiendActionData sActionData;

void ClearLesserFiendPending(void)
{
  gPendingLesserFiendBanishRow = LESSER_FIEND_PENDING_NONE;
  gPendingLesserFiendBanishCol = 0;
}

static void MarkPendingBanish(u8 row, u8 col)
{
  gPendingLesserFiendBanishRow = row;
  gPendingLesserFiendBanishCol = col;
}

static u8 IsMonsterVersusMonsterBattle(void)
{
  if (sActionData.playerCardId == CARD_NONE || sActionData.opponentCardId == CARD_NONE)
    return FALSE;

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

static u8 TryMarkLesserFiendBattleBanish(void)
{
  if (!IsMonsterVersusMonsterBattle())
    return FALSE;

  if (GetTypeGroup(sActionData.playerCardId) != TYPE_GROUP_MONSTER
      || GetTypeGroup(sActionData.opponentCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (sActionData.playerCardId == LESSER_FIEND
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && ZoneMatchesBattleCard(sActionData.playerMonsterRow, sActionData.unkA, LESSER_FIEND)
      && ZoneMatchesBattleCard(sActionData.opponentMonsterRow, sActionData.unk16,
                               sActionData.opponentCardId)) {
    MarkPendingBanish(sActionData.opponentMonsterRow, sActionData.unk16);
    sActionData.flags &= ~FLAG_GRAVEYARD_OPPONENT;
    return TRUE;
  }

  if (sActionData.opponentCardId == LESSER_FIEND
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && ZoneMatchesBattleCard(sActionData.opponentMonsterRow, sActionData.unk16, LESSER_FIEND)
      && ZoneMatchesBattleCard(sActionData.playerMonsterRow, sActionData.unkA,
                               sActionData.playerCardId)) {
    MarkPendingBanish(sActionData.playerMonsterRow, sActionData.unkA);
    sActionData.flags &= ~FLAG_GRAVEYARD_PLAYER;
    return TRUE;
  }

  return FALSE;
}

void ResolveLesserFiendBattleEffect(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  row = gPendingLesserFiendBanishRow;
  if (row == LESSER_FIEND_PENDING_NONE)
    return;

  col = gPendingLesserFiendBanishCol;
  ClearLesserFiendPending();

  zone = gFixedZones[row][col];
  if (zone == NULL || zone->id == CARD_NONE
      || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  Duel_ShowEffectTextTyped(LESSER_FIEND, 3);
  if (IsDuelOver() == TRUE)
    return;

  Duel_BanishZone(zone, TRUE);
}

void ApplyLesserFiendBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkLesserFiendBattleBanish())
    ClearLesserFiendPending();
}
