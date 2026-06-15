#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "fenrir.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct FenrirActionData {
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

extern struct FenrirActionData sActionData;

void ResetFenrirSkipDraw(void)
{
  gFenrirSkipDrawDuelist = FENRIR_SKIP_DRAW_NONE;
}

u8 ShouldSkipDrawPhaseForFenrir(u8 turn)
{
  return gFenrirSkipDrawDuelist == turn;
}

void ConsumeFenrirSkipDraw(u8 turn)
{
  if (gFenrirSkipDrawDuelist == turn)
    gFenrirSkipDrawDuelist = FENRIR_SKIP_DRAW_NONE;
}

void ApplyFenrirBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == FENRIR) {
    if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
      return;

    gFenrirSkipDrawDuelist = DUEL_OPPONENT;
    return;
  }

  if (sActionData.opponentCardId == FENRIR) {
    if (!(sActionData.flags & FLAG_GRAVEYARD_PLAYER))
      return;

    gFenrirSkipDrawDuelist = DUEL_PLAYER;
  }
}
