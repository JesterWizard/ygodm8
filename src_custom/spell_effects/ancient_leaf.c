#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define ANCIENT_LEAF_LP_REQUIRE 9000
#define ANCIENT_LEAF_LP_COST 2000
#define ANCIENT_LEAF_DRAW_COUNT 2

static u8 CanActivateAncientLeaf(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= ANCIENT_LEAF_LP_REQUIRE;

  return gDuelLifePoints[DUEL_OPPONENT] >= ANCIENT_LEAF_LP_REQUIRE;
}

static void ANCIENT_LEAF_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(ANCIENT_LEAF);

  if (IsDuelOver() == TRUE || !CanActivateAncientLeaf())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -ANCIENT_LEAF_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, ANCIENT_LEAF_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectANCIENT_LEAF(void)
{
  if (!CanActivateAncientLeaf()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANCIENT_LEAF, ANCIENT_LEAF_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
