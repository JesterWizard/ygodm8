#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

extern int NumCardsInDeck(unsigned char);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 RemainingDeckCards(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return (u8)(deckSize - top);
}

u8 CanActivateTHAT_GRASS_LOOKS_GREENER(void)
{
  return RemainingDeckCards(ACTIVE_DUELIST) > RemainingDeckCards(INACTIVE_DUELIST);
}

static void THAT_GRASS_LOOKS_GREENER_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 myRemaining;
  u8 oppRemaining;
  u8 millCount;

  Duel_ShowEffectText(THAT_GRASS_LOOKS_GREENER);

  if (IsDuelOver() == TRUE || !CanActivateTHAT_GRASS_LOOKS_GREENER())
    return;

  myRemaining = RemainingDeckCards(ACTIVE_DUELIST);
  oppRemaining = RemainingDeckCards(INACTIVE_DUELIST);
  millCount = (u8)(myRemaining - oppRemaining);

  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, millCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectTHAT_GRASS_LOOKS_GREENER(void)
{
  if (!CanActivateTHAT_GRASS_LOOKS_GREENER()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THAT_GRASS_LOOKS_GREENER,
                                       THAT_GRASS_LOOKS_GREENER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
