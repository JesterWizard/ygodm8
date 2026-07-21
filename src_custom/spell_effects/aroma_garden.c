#include "global.h"
#include "common-chax.h"
#include "aroma_garden.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define AROMA_GARDEN_LP_GAIN 500
#define AROMA_GARDEN_DESTROY_LP_GAIN 1000
#define AROMA_GARDEN_STAT_STAGES 1

static const char sAromaArchetypeName[] APPEND_RODATA = "Aroma";

/* Mask of fixed monster cols that keep +1 temp stage until opp next EP. */
static u8 sAromaGardenBoostMaskPlayer APPEND_DATA = {0};
static u8 sAromaGardenBoostMaskOpponent APPEND_DATA = {0};
static u8 sAromaGardenBoostTurnsLeft APPEND_DATA = {0};
static u8 sAromaGardenBoostController APPEND_DATA = {0xFF};
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

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void BoostOwnMonstersTempStages(void)
{
  u8 i;
  u8 s;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 *mask;

  if (fixedDuelist == DUEL_PLAYER)
    mask = &sAromaGardenBoostMaskPlayer;
  else
    mask = &sAromaGardenBoostMaskOpponent;

  *mask = 0;
  sAromaGardenBoostController = fixedDuelist;
  /* Clear on End Phase of opponent's next turn: this EP + opp EP = 2. */
  sAromaGardenBoostTurnsLeft = 2;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    for (s = 0; s < AROMA_GARDEN_STAT_STAGES; s++)
      IncrementTempStage(zone);

    *mask |= (u8)(1 << i);
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

  BoostOwnMonstersTempStages();
  zone->effectUsedThisTurn = TRUE;
}

void AromaGarden_ReapplyTempBoostAfterReset(void)
{
  u8 col;
  u8 row;
  u8 *mask;

  if (sAromaGardenBoostTurnsLeft == 0)
    return;

  if (sAromaGardenBoostController == DUEL_PLAYER) {
    mask = &sAromaGardenBoostMaskPlayer;
    row = PLAYER_MONSTER_ROW;
  } else if (sAromaGardenBoostController == DUEL_OPPONENT) {
    mask = &sAromaGardenBoostMaskOpponent;
    row = OPPONENT_MONSTER_ROW;
  } else {
    return;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!(*mask & (1 << col)))
      continue;

    zone = gFixedZones[row][col];
    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    IncrementTempStage(zone);
  }
}

void AromaGarden_OnEndPhase(void)
{
  if (sAromaGardenBoostTurnsLeft == 0)
    return;

  sAromaGardenBoostTurnsLeft--;
  if (sAromaGardenBoostTurnsLeft > 0)
    return;

  sAromaGardenBoostMaskPlayer = 0;
  sAromaGardenBoostMaskOpponent = 0;
  sAromaGardenBoostController = 0xFF;
}

u8 Cond_AromaGardenOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!IsAromaMonster(ev->cardId))
    return FALSE;

  return Duel_FindBackrowCard(ev->controller, AROMA_GARDEN, TRUE) != NULL;
}

enum DuelActionResult Op_AromaGardenOnDestroy(struct EffectCtx *ctx)
{
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  turnDuelist = TurnDuelistForFixed(ctx->event->controller);
  Duel_ShowEffectText(AROMA_GARDEN);
  return Duel_ChangeLp(turnDuelist, AROMA_GARDEN_DESTROY_LP_GAIN, TRUE);
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
}

APPEND_TEXT void EffectAROMA_GARDEN(void)
{
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
  if (AROMA_GARDEN_DESTROY_LP_GAIN != 1000)
    while (1)
      ;
}
#endif
