#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "contact_fusion_end_phase.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "instant_neo_space.h"
#include "neo_space.h"

void ClearZone(struct DuelCard *zone);
void ExtraDeck_AddCard(u16 cardId);
void UpdateDuelGfxExceptField(void);

static const char sNeosName[] APPEND_RODATA = "Neos";

static u8 IsContactFusionNeos(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == ELEMENTAL_HERO_NEOS)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeosName);
}

static u8 ShouldKeepOnField(const struct DuelCard *zone)
{
  if (NeoSpace_PreventsEndPhaseExtraDeckReturn(zone))
    return TRUE;
  if (InstantNeoSpace_PreventsEndPhaseExtraDeckReturn(zone))
    return TRUE;
  return FALSE;
}

static void ReturnZoneToExtraDeck(struct DuelCard *zone)
{
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  cardId = zone->id;
  ClearZone(zone);
  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_LEAVE_FIELD, cardId, NULL);
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (gRuntimeConfig.enable_extra_deck)
    ExtraDeck_AddCard(cardId);
}

void TryReturnContactFusionsAtEndPhase(void)
{
  u8 fixed;
  u8 col;
  u8 returned = FALSE;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || !IsContactFusionNeos(zone->id))
        continue;
      if (ShouldKeepOnField(zone))
        continue;

      Duel_ShowEffectTextTyped(zone->id, 8);
      if (IsDuelOver() == TRUE)
        return;

      ReturnZoneToExtraDeck(zone);
      returned = TRUE;
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  if (returned)
    UpdateDuelGfxExceptField();
}
