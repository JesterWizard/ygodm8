#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card.h"
#include "duel.h"
#include "duel_helpers.h"
#include "harpie_lady_3.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct HL3ActionData {
  unsigned short playerCardId;
  unsigned short opponentCardId;
  unsigned char playerMonsterRow;
  unsigned char opponentMonsterRow;
  unsigned char unkA;
  unsigned char unk16;
  unsigned char id;
  unsigned char flags;
};

extern struct HL3ActionData sActionData;

/* Harpie Lady 3 restrict turns layout:
 *   [0..4] = player monster row (fixed row 2)
 *   [5..9] = opponent monster row (fixed row 1)
 */
#define PLAYER_ROW_OFFSET 0
#define OPPONENT_ROW_OFFSET 5

static u8 ZoneIsActiveMonster(u8 fixedRow, u8 col)
{
  struct DuelCard *zone;

  if (fixedRow < 1 || fixedRow > 2)
    return FALSE;
  if (col >= MAX_ZONES_IN_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][col];
  return zone != NULL && zone->id != CARD_NONE;
}

void ApplyHarpieLady3AttackLock(void)
{
  u8 offset;
  u8 targetCol;
  u8 targetRow;

  if (gHideEffectText)
    return;

  /* Only monster vs monster battles */
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return;

  /* Player's HL3 battled opponent's monster → lock opponent's monster col */
  if (sActionData.playerCardId == HARPIE_LADY_3) {
    targetRow = sActionData.opponentMonsterRow;
    targetCol = sActionData.unk16;
    if (targetRow == 1 || targetRow == 2) {
      offset = (targetRow == 1) ? OPPONENT_ROW_OFFSET : PLAYER_ROW_OFFSET;
      if (ZoneIsActiveMonster(targetRow, targetCol))
        gHarpieLady3RestrictTurns[offset + targetCol] = 2;
    }
    return;
  }

  /* Opponent's HL3 battled player's monster → lock player's monster col */
  if (sActionData.opponentCardId == HARPIE_LADY_3) {
    targetRow = sActionData.playerMonsterRow;
    targetCol = sActionData.unkA;
    if (targetRow == 1 || targetRow == 2) {
      offset = (targetRow == 1) ? OPPONENT_ROW_OFFSET : PLAYER_ROW_OFFSET;
      if (ZoneIsActiveMonster(targetRow, targetCol))
        gHarpieLady3RestrictTurns[offset + targetCol] = 2;
    }
  }
}

void HarpieLady3_RefreshAttackRestrictions(void)
{
  u8 fixedRow;
  u8 col;
  u8 offset;
  u8 opponentDuelist;

  /* Decrement active turn counters and unlock expired ones.
   * Only process once per turn change. */
  opponentDuelist = (WhoseTurn() + 1) & 1;

  /* The opponent's monsters are in fixed row 1 (opponent) */
  fixedRow = (opponentDuelist == 0) ? 2 : 1;
  offset = (fixedRow == 1) ? OPPONENT_ROW_OFFSET : PLAYER_ROW_OFFSET;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gHarpieLady3RestrictTurns[offset + col] == 0)
      continue;

    if (gHarpieLady3RestrictTurns[offset + col] < 0xFF)
      gHarpieLady3RestrictTurns[offset + col]--;
  }
}
