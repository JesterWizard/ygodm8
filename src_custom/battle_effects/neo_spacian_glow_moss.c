#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card.h"
#include "duel_helpers.h"
#include "neo_spacian_glow_moss.h"

void LockMonsterCardsInRow(unsigned char turnRow);

struct NeoSpacianGlowMossActionData {
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

extern struct NeoSpacianGlowMossActionData sActionData;
extern u8 gPendingNeoSpacianGlowMossDraw;

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

u8 CanNeoSpacianGlowMossAttackDirectly(const struct DuelCard *zone)
{
  return zone != NULL
      && (zone->id == NEO_SPACIAN_GLOW_MOSS || zone->id == NEO_SPACIAN_TWINKLE_MOSS)
      && zone->unkTwo;
}

void ApplyNeoSpacianMossDrawnTypeEffect(u16 drawnCardId, u8 mossFixedRow, u8 mossFixedCol,
                                        u16 effectCardId)
{
  struct DuelCard *mossZone;
  u8 typeGroup;

  if (drawnCardId == CARD_NONE)
    return;

  mossZone = gFixedZones[mossFixedRow][mossFixedCol];
  typeGroup = GetTypeGroup(drawnCardId);

  if (typeGroup == TYPE_GROUP_TRAP) {
    if (mossZone != NULL && mossZone->id != CARD_NONE) {
      mossZone->isDefending = TRUE;
      if (!mossZone->isFaceUp)
        FlipCardFaceUp(mossZone);
    }
    return;
  }

  if (typeGroup == TYPE_GROUP_MONSTER) {
    /* End the Battle Phase — lock remaining attackers for the turn player. */
    LockMonsterCardsInRow(ACTIVE_DUELIST_MONSTER_ROW);
    (void)effectCardId;
    return;
  }

  /* Spell: grant optional direct attack for remaining attacks this turn. */
  if (typeGroup == TYPE_GROUP_SPELL && mossZone != NULL && mossZone->id != CARD_NONE)
    mossZone->unkTwo = TRUE;
}

static void TryGlowMossDrawAndBranch(u8 drawDuelist, u8 mossFixedRow, u8 mossFixedCol,
                                     u16 effectCardId)
{
  u16 drawnCardId;
  u8 turnDuelist = FixedToTurnDuelist(drawDuelist);

  drawnCardId = PeekTopDeckCard(turnDuelist);
  if (drawnCardId == CARD_NONE)
    return;

  if (Duel_DrawCards(turnDuelist, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  ApplyNeoSpacianMossDrawnTypeEffect(drawnCardId, mossFixedRow, mossFixedCol, effectCardId);
}

void ResolveNeoSpacianGlowMossBattleEffect(void)
{
  if (!gPendingNeoSpacianGlowMossDraw)
    return;

  gPendingNeoSpacianGlowMossDraw = FALSE;

  if (sActionData.playerCardId == NEO_SPACIAN_GLOW_MOSS) {
    Duel_ShowEffectText(NEO_SPACIAN_GLOW_MOSS);
    TryGlowMossDrawAndBranch(
        DUEL_OPPONENT, sActionData.playerMonsterRow, sActionData.unkA,
        NEO_SPACIAN_GLOW_MOSS);
  } else if (sActionData.opponentCardId == NEO_SPACIAN_GLOW_MOSS) {
    Duel_ShowEffectText(NEO_SPACIAN_GLOW_MOSS);
    TryGlowMossDrawAndBranch(
        DUEL_PLAYER, sActionData.opponentMonsterRow, sActionData.unk16,
        NEO_SPACIAN_GLOW_MOSS);
  }
}

void ApplyNeoSpacianGlowMossBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMossBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId != NEO_SPACIAN_GLOW_MOSS
      && sActionData.opponentCardId != NEO_SPACIAN_GLOW_MOSS)
    return;

  gPendingNeoSpacianGlowMossDraw = TRUE;

  if (gUnk2023EA0.unk18 == 0)
    ResolveNeoSpacianGlowMossBattleEffect();
}
