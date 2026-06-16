#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "spell_effects.h"

APPEND_TEXT void EffectSwordsOfRevealingLight(void)
{
  u8 i;
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  InitSorlTurns(INACTIVE_DUELIST);
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->id != CARD_NONE)
      gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i]->isFaceUp = TRUE;
  }

  Duel_ShowEffectText(SWORDS_OF_REVEALING_LIGHT);
}
