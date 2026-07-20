#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void UpdateDuelGfxExceptField(void);

static const char sVenomName[] APPEND_RODATA = "Venom";

static u8 IsVenomMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sVenomName);
}

static u8 HandHasVenom(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsVenomMonster(gTurnHands[INACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

APPEND_TEXT void EffectSNAKE_DEITYS_COMMAND(void)
{
  s8 handZone;

  Duel_ShowTrapResponseText(SNAKE_DEITYS_COMMAND, gTrapEffectData.originCardId);

  if (!HandHasVenom()
      || GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_SPELL) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  /* Reveal cost: pick Venom in hand (shown via selection). */
  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], IsVenomMonster);
  else {
    u8 i;

    handZone = -1;
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsVenomMonster(gTurnHands[INACTIVE_DUELIST][i]->id)) {
        handZone = (s8)i;
        break;
      }
    }
  }

  (void)handZone;

  /* Destroy the activating Spell (origin). */
  {
    struct DuelCard *origin =
        gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];

    if (origin != NULL)
      Duel_DestroyZone(origin, ACTIVE_DUELIST, FALSE);
  }

  /* ponytail: full Spell negate (prevent resolve) needs negation gate like Magic
   * Jammer. Ceiling: destroys origin Spell zone; upgrade: trapEffect counter +
   * cancel spell resolve. */

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
