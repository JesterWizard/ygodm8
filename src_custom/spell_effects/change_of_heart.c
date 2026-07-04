#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static void ChangeOfHeart_ResolveBody(void)
{
  u16 takenCardId = CARD_NONE;
  u8 newFixedRow = Duel_FixedMonsterRowForDuelist(ACTIVE_DUELIST);

  if (NumEmptyZonesInRow(gTurnZones[2])
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[1]) != MAX_ZONES_IN_ROW) {
    u8 emptyZone = FirstEmptyZoneInRow(gTurnZones[2]);
    u8 highestAtkZone = HighestAtkMonInRowExceptGodCards(gTurnZones[1]);

    takenCardId = gTurnZones[1][highestAtkZone]->id;
    gTurnZones[2][emptyZone]->id = takenCardId;
    gTurnZones[2][emptyZone]->isFaceUp = 1;
    gTurnZones[2][emptyZone]->isLocked = 0;
    gTurnZones[2][emptyZone]->isDefending = 0;
    gTurnZones[2][emptyZone]->unkTwo = gTurnZones[1][highestAtkZone]->unkTwo;
    gTurnZones[2][emptyZone]->unk4 = 2;
    SetPermStage(gTurnZones[2][emptyZone], PermStage(gTurnZones[1][highestAtkZone]));
    gTurnZones[2][emptyZone]->willChangeSides = 0;
    ClearZone(gTurnZones[1][highestAtkZone]);

    if (takenCardId != CARD_NONE)
      Duel_NotifyMonsterControlSwitched(takenCardId, newFixedRow);
  }

  ClearZoneAndSendMonToGraveyard(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1],
                                 ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = CHANGE_OF_HEART;
    ActivateCardEffectText();
  }
}

LYN_REPLACE_CHECK(EffectChangeOfHeart);
APPEND_TEXT void EffectChangeOfHeart__Replacement(void)
{
  ChangeOfHeart_ResolveBody();
}
