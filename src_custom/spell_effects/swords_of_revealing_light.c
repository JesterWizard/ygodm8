#include "global.h"
#include "spell_effects.h"

APPEND_TEXT void EffectSwordsOfRevealingLight(void)
{
  u8 i;

  InitSorlTurns(INACTIVE_DUELIST);
  FlipCardFaceUp(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->isFaceUp = TRUE;
  }

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = SWORDS_OF_REVEALING_LIGHT;
    ActivateCardEffectText();
  }
}
