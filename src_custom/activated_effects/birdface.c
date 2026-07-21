#include "global.h"
#include "common-chax.h"
#include "birdface.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"

void UpdateDuelGfxExceptField(void);

static u8 sBirdfaceInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void TryBirdfaceSearch(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;
  if (Duel_FindDeckCardIndex(turnDuelist, HARPIE_LADY) < 0)
    return;

  Duel_ShowEffectTextTyped(BIRDFACE, 2);
  if (IsDuelOver() == TRUE)
    return;

  Duel_AddDeckCardToHand(turnDuelist, HARPIE_LADY, TRUE);
  UpdateDuelGfxExceptField();
}

static void OnBirdfaceBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != BIRDFACE)
    return;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TryBirdfaceSearch(ev->controller);
}

void Birdface_EnsureInit(void)
{
  if (sBirdfaceInit)
    return;
  sBirdfaceInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnBirdfaceBattleDestroyed);
}

unsigned char CanActivateBIRDFACE(void)
{
  if (gMonEffect.id != BIRDFACE)
    return FALSE;

  /* Battle-destroy search via Birdface_EnsureInit. */
  return FALSE;
}

void ActivateBIRDFACEEffect(void)
{
  Duel_ShowEffectTextTyped(BIRDFACE, 2);
}
