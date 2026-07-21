#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define MIRAGE_HAND_TARGET 4

static u8 IsActivatedMirageZone(struct DuelCard *zone)
{
  return zone != NULL && zone->id == MIRAGE_OF_NIGHTMARE && zone->isFaceUp != FALSE
      && zone->isLocked != FALSE;
}

static void ResolveMirageOpponentStandbyDraw(struct DuelCard *spellZone, u8 controller)
{
  u8 before;
  u8 after;
  u8 drawn;

  if (!IsActivatedMirageZone(spellZone))
    return;

  /* Once per opponent Standby — effectUsedThisTurn marks draw already done. */
  if (spellZone->effectUsedThisTurn)
    return;

  before = Duel_CountCardsInHand(gTurnHands[controller]);
  if (before >= MIRAGE_HAND_TARGET)
    return;

  Duel_ShowEffectText(MIRAGE_OF_NIGHTMARE);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCardsUntilHandSize(controller, MIRAGE_HAND_TARGET, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  after = Duel_CountCardsInHand(gTurnHands[controller]);
  drawn = (after > before) ? (u8)(after - before) : 0;
  if (drawn == 0)
    return;

  spellZone->unk4 = drawn;
  spellZone->effectUsedThisTurn = TRUE;
}

static void ResolveMirageControllerStandbyDiscard(struct DuelCard *spellZone, u8 controller)
{
  u8 discardCount;

  if (!IsActivatedMirageZone(spellZone))
    return;

  discardCount = spellZone->unk4;
  if (discardCount == 0)
    return;

  Duel_ShowEffectText(MIRAGE_OF_NIGHTMARE);
  if (IsDuelOver() == TRUE)
    return;

  /* Printed: randomly discard drawn count, or entire hand if fewer remain. */
  Duel_DiscardRandomFromHand(controller, discardCount, TRUE);
  spellZone->unk4 = 0;
}

/* Wire from turn_effect_hooks Standby (clone TryApplyNightmareWheelStandbyDamage). */
void TryApplyMirageOfNightmareStandby(void)
{
  u8 i;
  struct DuelCard *spellZone;

  if (IsDuelOver() == TRUE)
    return;

  /* Controller's Standby: pending discard from a prior opponent-Standby draw. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    ResolveMirageControllerStandbyDiscard(spellZone, ACTIVE_DUELIST);
    if (IsDuelOver() == TRUE)
      return;
  }

  /* Opponent's Standby (from Mirage controller's POV): draw until 4. */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    spellZone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    ResolveMirageOpponentStandbyDraw(spellZone, INACTIVE_DUELIST);
    if (IsDuelOver() == TRUE)
      return;
  }
}

static void MIRAGE_OF_NIGHTMARE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL) {
    zone->unk4 = 0;
    zone->effectUsedThisTurn = FALSE;
  }

  Duel_ShowEffectText(MIRAGE_OF_NIGHTMARE);
}

APPEND_TEXT void EffectMIRAGE_OF_NIGHTMARE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MIRAGE_OF_NIGHTMARE, MIRAGE_OF_NIGHTMARE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MIRAGE_OF_NIGHTMARE_SelfCheck(void)
{
  if (MIRAGE_HAND_TARGET != 4)
    while (1)
      ;
}
#endif
