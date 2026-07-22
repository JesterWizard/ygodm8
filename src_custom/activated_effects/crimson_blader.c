#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "crimson_blader.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct CrimsonBladerActionData {
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

extern struct CrimsonBladerActionData sActionData;

/* Locked fixed duelist cannot NS/SS Lv5+ on their next turn. 0xFF = none. */
static u8 sCrimsonLockFixed APPEND_DATA = 0xFF;
static u8 sCrimsonLockArmed APPEND_DATA = 0;

void ApplyCrimsonBladerBattleEffect(void)
{
  if (sActionData.playerCardId == CRIMSON_BLADER
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    sCrimsonLockFixed = DUEL_OPPONENT;
    sCrimsonLockArmed = FALSE;
    Duel_ShowEffectTextTyped(CRIMSON_BLADER, 2);
    return;
  }
  if (sActionData.opponentCardId == CRIMSON_BLADER
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    sCrimsonLockFixed = DUEL_PLAYER;
    sCrimsonLockArmed = FALSE;
    Duel_ShowEffectTextTyped(CRIMSON_BLADER, 2);
  }
}

u8 CrimsonBlader_BlocksLevel5PlusSummon(u8 turnDuelist, u16 cardId)
{
  u8 fixed;

  if (sCrimsonLockFixed > DUEL_OPPONENT || cardId == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (gCardData_NEW[cardId].level < 5)
    return FALSE;

  fixed = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
      ? DUEL_PLAYER
      : DUEL_OPPONENT;
  if (fixed != sCrimsonLockFixed)
    return FALSE;
  /* Active during the locked player's turn once it begins. */
  if (!sCrimsonLockArmed)
    return FALSE;
  return TRUE;
}

void CrimsonBlader_ClearOnTurnBoundary(void)
{
  u8 ending = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;

  if (sCrimsonLockFixed > DUEL_OPPONENT)
    return;

  if (!sCrimsonLockArmed) {
    /* Arm when the locked player's turn is about to start (boundary into it). */
    if (ending != sCrimsonLockFixed)
      sCrimsonLockArmed = TRUE;
    return;
  }

  /* Clear after the locked player's turn ends. */
  if (ending == sCrimsonLockFixed) {
    sCrimsonLockFixed = 0xFF;
    sCrimsonLockArmed = FALSE;
  }
}

unsigned char CanActivateCRIMSON_BLADER(void)
{
  if (gMonEffect.id != CRIMSON_BLADER)
    return FALSE;

  /* Battle-destroy summon lock via ApplyCrimsonBladerBattleEffect. */
  return FALSE;
}

void ActivateCRIMSON_BLADEREffect(void)
{
  Duel_ShowEffectTextTyped(CRIMSON_BLADER, 2);
}
