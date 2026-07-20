#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static void EN_WAVE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(EN_WAVE);

  /* ponytail: OPT "E-HERO used as Fusion material → GY/banish (not Damage Step):
   * SS 1 Neo-Spacian or ELEMENTAL_HERO_NEOS from Deck" needs a fusion-material
   * send listener outside this file. Ceiling: continuous face-up only; upgrade:
   * after Fusion material leave → if face-up EN_WAVE and OPT clear, DeckMenu
   * Neo-Spacian / NEOS → Duel_SpecialSummonFromDeck. */

  /* ponytail: OPT "Neo-Spacian or ELEMENTAL_HERO_NEOS shuffled from field/GY into
   * Deck/Extra Deck (not Damage Step): SS 1 Elemental HERO from GY" needs a
   * shuffle-into-deck listener + GY pick outside this file. Ceiling: continuous
   * face-up only; upgrade: on shuffle → if face-up EN_WAVE and OPT clear,
   * PickZone/DeckMenu E-HERO in GY → Duel_SpecialSummonFromGrave. */

  (void)sNeoSpacianName;
  (void)ELEMENTAL_HERO_NEOS;
}

APPEND_TEXT void EffectEN_WAVE(void)
{
  if (Duel_TryResolveSpellThroughTraps(EN_WAVE, EN_WAVE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void EN_WAVE_SelfCheck(void)
{
  if (!Duel_CardNameContains(NEO_SPACIAN_AQUA_DOLPHIN, sNeoSpacianName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, sNeoSpacianName))
    while (1)
      ;
  if (ELEMENTAL_HERO_NEOS == CARD_NONE)
    while (1)
      ;
}
#endif
