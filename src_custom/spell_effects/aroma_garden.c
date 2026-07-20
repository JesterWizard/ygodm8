#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define AROMA_GARDEN_LP_GAIN 500
#define AROMA_GARDEN_STAT_STAGES 1

static const char sAromaArchetypeName[] APPEND_RODATA = "Aroma";

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaArchetypeName);
}

static u8 ControlsAromaMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsAromaMonster(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateAromaGardenIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != AROMA_GARDEN || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return ControlsAromaMonster();
}

static void BoostOwnMonstersTempStages(void)
{
  u8 i;
  u8 s;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    for (s = 0; s < AROMA_GARDEN_STAT_STAGES; s++)
      IncrementTempStage(zone);

    Duel_NotifyMonsterZoneChanged(zone);
  }

  Duel_RefreshMonsterStatOverlays();
}

static void ResolveAromaGardenIgnition(struct DuelCard *zone)
{
  if (!CanActivateAromaGardenIgnition(zone))
    return;

  Duel_ShowEffectText(AROMA_GARDEN);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, AROMA_GARDEN_LP_GAIN, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: printed "until end of opponent's next turn (even if this card
   * leaves)" needs a multi-turn temp-stage / overlay tracker outside this file.
   * Ceiling: +500 ATK/DEF via 1 temp stage (~clears at next ResetTempStages /
   * EOT), not opponent's next End Phase; upgrade: stamp expiry turn counter on
   * zones and skip ResetTempStages until that turn's End Phase. */
  BoostOwnMonstersTempStages();

  zone->effectUsedThisTurn = TRUE;
}

static void AROMA_GARDEN_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateAromaGardenIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveAromaGardenIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);

  if (CanActivateAromaGardenIgnition(zone))
    ResolveAromaGardenIgnition(zone);
  else
    Duel_ShowEffectText(AROMA_GARDEN);

  /* ponytail: "If a face-up Aroma you control is destroyed by battle or card
   * effect and sent to the GY: Gain 1000 LP" needs a destroy→GY hook outside
   * this file. Ceiling: OPT LP/+500 only; upgrade: on ClearZoneAndSendMonTo-
   * Graveyard / battle destroy, if controller has face-up AROMA_GARDEN and
   * destroyed card IsAromaMonster, Duel_ChangeLp(+1000). */
}

APPEND_TEXT void EffectAROMA_GARDEN(void)
{
  /* ponytail: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up
   * OPT re-activation may need card_hooks GetSpellType + AROMA_GARDEN listed.
   * Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list. */
  if (Duel_TryResolveSpellThroughTraps(AROMA_GARDEN, AROMA_GARDEN_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AROMA_GARDEN_SelfCheck(void)
{
  if (!IsAromaMonster(AROMAGE_JASMINE))
    while (1)
      ;
  if (IsAromaMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (AROMA_GARDEN_LP_GAIN != 500)
    while (1)
      ;
}
#endif
