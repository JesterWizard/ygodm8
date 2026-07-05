#include "global.h"
#include "common-chax.h"
#include "ai_spell_targets.h"
#include "card.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "duel.h"
#include "monster_reborn.h"

static u8 TurnBackrowHasAnyCard(u8 turnBackrowRow)
{
  return NumEmptyZonesInRow(gTurnZones[turnBackrowRow]) != MAX_ZONES_IN_ROW;
}

static u8 FieldHasDestroyableSpellTrapBoardState(void)
{
  return NumEmptyZonesAndGodCardsInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW])
             == MAX_ZONES_IN_ROW
      && (NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
              != MAX_ZONES_IN_ROW
          || TurnBackrowHasAnyCard(INACTIVE_DUELIST_BACKROW)
          || TurnBackrowHasAnyCard(ACTIVE_DUELIST_BACKROW));
}

/* Match vanilla AI target checks for board-wipe normals (see src/duel/ai.c). */
u8 AiNormalSpellHasActivationTargets(u16 cardId)
{
  SetCardInfo(cardId);

  switch (gCardInfo.spellEffect) {
  case SPELL_EFFECT_RAIGEKI:
    return NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
        != MAX_ZONES_IN_ROW;
  case SPELL_EFFECT_DARK_HOLE:
    return NumEmptyZonesAndGodCardsInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW])
            == MAX_ZONES_IN_ROW
        && NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
            != MAX_ZONES_IN_ROW;
  case SPELL_EFFECT_HEAVY_STORM:
    return NumEmptyZonesAndGodCardsInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW])
            == MAX_ZONES_IN_ROW
        && FieldHasDestroyableSpellTrapBoardState();
  case SPELL_EFFECT_HARPIES_FEATHER_DUSTER:
    return TurnBackrowHasAnyCard(INACTIVE_DUELIST_BACKROW);
  case SPELL_EFFECT_CHANGE_OF_HEART:
  case SPELL_EFFECT_BRAIN_CONTROL:
    return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) > 0
        && NumEmptyZonesAndGodCardsInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW])
            != MAX_ZONES_IN_ROW;
  case SPELL_EFFECT_MONSTER_REBORN:
    return CanActivateMonsterReborn();
  default:
    return TRUE;
  }
}
