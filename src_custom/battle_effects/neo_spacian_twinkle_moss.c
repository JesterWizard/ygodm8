#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "neo_spacian_glow_moss.h"
#include "neo_spacian_twinkle_moss.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct NeoSpacianTwinkleMossActionData {
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

extern struct NeoSpacianTwinkleMossActionData sActionData;

extern u8 gPendingNeoSpacianTwinkleMossDraw;

static u8 IsMossBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 FixedToTurnDuelist(u8 fixedDuelist)
{
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 PeekTopDeckCard(u8 turnDuelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 deckSize = NumCardsInDeck(fixedDuelist);

  if (top >= deckSize)
    return CARD_NONE;

  return gDuelDecks[fixedDuelist].cards[top];
}

static void TryTwinkleMossDrawAndBranch(u8 drawDuelist, u8 mossFixedRow, u8 mossFixedCol)
{
  u16 drawnCardId;
  u8 turnDuelist = FixedToTurnDuelist(drawDuelist);

  drawnCardId = PeekTopDeckCard(turnDuelist);
  if (drawnCardId == CARD_NONE)
    return;

  if (Duel_DrawCards(turnDuelist, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ApplyNeoSpacianMossDrawnTypeEffect(
      drawnCardId, mossFixedRow, mossFixedCol, NEO_SPACIAN_TWINKLE_MOSS);
}

void ResolveNeoSpacianTwinkleMossBattleEffect(void)
{
  if (!gPendingNeoSpacianTwinkleMossDraw)
    return;

  gPendingNeoSpacianTwinkleMossDraw = FALSE;

  if (sActionData.playerCardId == NEO_SPACIAN_TWINKLE_MOSS) {
    Duel_ShowEffectText(NEO_SPACIAN_TWINKLE_MOSS);
    TryTwinkleMossDrawAndBranch(
        DUEL_PLAYER, sActionData.playerMonsterRow, sActionData.unkA);
  } else if (sActionData.opponentCardId == NEO_SPACIAN_TWINKLE_MOSS) {
    Duel_ShowEffectText(NEO_SPACIAN_TWINKLE_MOSS);
    TryTwinkleMossDrawAndBranch(
        DUEL_OPPONENT, sActionData.opponentMonsterRow, sActionData.unk16);
  }
}

void ApplyNeoSpacianTwinkleMossBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMossBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId != NEO_SPACIAN_TWINKLE_MOSS
      && sActionData.opponentCardId != NEO_SPACIAN_TWINKLE_MOSS)
    return;

  gPendingNeoSpacianTwinkleMossDraw = TRUE;

  if (gUnk2023EA0.unk18 == 0)
    ResolveNeoSpacianTwinkleMossBattleEffect();
}
