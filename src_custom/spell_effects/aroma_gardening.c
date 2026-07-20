#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define AROMA_GARDENING_LP_GAIN 1000

static void AROMA_GARDENING_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AROMA_GARDENING);

  /* ponytail: OPT "NS/SS Aroma → +1000 LP" needs a summon hook outside this file
   * (no in-file Normal/Special Summon dispatch). Ceiling: continuous face-up only;
   * upgrade: after NS/SS (not Damage Step), if face-up AROMA_GARDENING and OPT bit
   * clear and summoned monster name contains "Aroma", Duel_ChangeLp(+1000) and mark
   * OPT. */

  /* ponytail: OPT "opp attack declare while LP lower → SS Aroma from Deck" needs
   * an attack-declare hook + deck pick outside this file. Ceiling: continuous
   * face-up only; upgrade: on opp attack declare, if controller LP < opp LP and
   * OPT clear and empty monster zone, PickZone/DeckMenu Aroma monster →
   * Duel_SpecialSummonFromDeck. */

  (void)AROMA_GARDENING_LP_GAIN;
}

APPEND_TEXT void EffectAROMA_GARDENING(void)
{
  if (Duel_TryResolveSpellThroughTraps(AROMA_GARDENING, AROMA_GARDENING_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AROMA_GARDENING_SelfCheck(void)
{
  static const char aromaName[] = "Aroma";

  if (AROMA_GARDENING_LP_GAIN != 1000)
    while (1)
      ;
  if (!Duel_CardNameContains(AROMA_JAR, aromaName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, aromaName))
    while (1)
      ;
}
#endif
