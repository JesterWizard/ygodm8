#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect.h"
#include "morphtronic_monitron.h"

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static void ActivateMORPHTRONIC_MONITRONZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, MORPHTRONIC_MONITRON)
      == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateMORPHTRONIC_MONITRONOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(MORPHTRONIC_MONITRON,
                                         ActivateMORPHTRONIC_MONITRONZone);
}

u8 Cond_MorphtronicMonitronOnSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return FALSE;

  ev = ctx->event;
  if (!Duel_CardNameContains(ev->cardId, sMorphtronicName))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, MORPHTRONIC_MONITRON, TRUE) != NULL;
}

enum DuelActionResult Op_MorphtronicMonitronOnSummon(struct EffectCtx *ctx)
{
  struct DuelCard *zone;

  if (ctx == NULL || ctx->event == NULL || ctx->event->zone == NULL)
    return DUEL_ACTION_INVALID;

  zone = ctx->event->zone;
  zone->isDefending = TRUE;
  zone->isFaceUp = TRUE;
  Duel_ShowEffectText(MORPHTRONIC_MONITRON);
  Duel_NotifyMonsterZoneChanged(zone);
  return DUEL_ACTION_OK;
}
