#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "harpie_lady_2.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct HL2ActionData {
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

extern struct HL2ActionData sActionData;

void ApplyHarpieLady2FlipNegation(void)
{
  if (gHideEffectText)
    return;

  /* Only monster vs monster battles */
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return;

  /* Player destroyed opponent's monster by battle */
  if ((sActionData.playerCardId == HARPIE_LADY_2
       || sActionData.playerCardId == ANCIENT_GEAR_BEAST)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    gHarpieLady2NegatedCardId = sActionData.opponentCardId;
    return;
  }

  /* Opponent destroyed player's monster by battle */
  if ((sActionData.opponentCardId == HARPIE_LADY_2
       || sActionData.opponentCardId == ANCIENT_GEAR_BEAST)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    gHarpieLady2NegatedCardId = sActionData.playerCardId;
  }
}

void HarpieLady2_ClearNegatedCard(void)
{
  gHarpieLady2NegatedCardId = CARD_NONE;
}
