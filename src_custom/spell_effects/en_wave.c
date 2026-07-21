#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "en_wave.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "spell_effects.h"

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

/* The generic leave-field event has no material-use or destination provenance.
 * Parent hooks must filter those semantic events before subscribing these. */
void EN_WAVE_OnFusionMaterialLeave(const struct EffectEvent *ev)
{
  (void)ev;
}

void EN_WAVE_OnShuffleIntoDeck(const struct EffectEvent *ev)
{
  (void)ev;
}

APPEND_TEXT void EffectEN_WAVE(void)
{
  const struct EffectScript *script = EffectScript_Find(EN_WAVE, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
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
