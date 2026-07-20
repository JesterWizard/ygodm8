#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
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

APPEND_TEXT void EffectTHAT_GRASS_LOOKS_GREENER(void)
{
  const struct EffectScript *script =
      EffectScript_Find(THAT_GRASS_LOOKS_GREENER, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}
