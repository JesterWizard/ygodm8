#include "global.h"
#include "common-chax.h"
#include "aroma_gardening.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define AROMA_GARDENING_LP_GAIN 1000

static const char sAromaArchetypeName[] APPEND_RODATA = "Aroma";

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaArchetypeName);
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

u8 Cond_AromaGardeningOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!IsAromaMonster(ev->cardId))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, AROMA_GARDENING, TRUE) != NULL;
}

enum DuelActionResult Op_AromaGardeningOnSummon(struct EffectCtx *ctx)
{
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  turnDuelist = TurnDuelistForFixed(ctx->event->controller);
  Duel_ShowEffectText(AROMA_GARDENING);
  return Duel_ChangeLp(turnDuelist, AROMA_GARDENING_LP_GAIN, TRUE);
}

static void AROMA_GARDENING_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AROMA_GARDENING);

  /* ponytail: OPT "opp attack declare while LP lower → SS Aroma from Deck" needs
   * an attack-declare hook + deck pick outside this file. Ceiling: summon LP wired;
   * upgrade: on opp attack declare, if controller LP < opp LP and OPT clear and
   * empty monster zone, PickZone/DeckMenu Aroma monster → Duel_SpecialSummonFromDeck. */
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
  if (AROMA_GARDENING_LP_GAIN != 1000)
    while (1)
      ;
  if (!IsAromaMonster(AROMA_JAR))
    while (1)
      ;
  if (IsAromaMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
