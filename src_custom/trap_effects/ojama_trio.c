#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "ojama_trio.h"
#include "graveyard_effects.h"
#include "riryoku.h"

#define OJAMA_TRIO_SUMMON_COUNT 3
#define OJAMA_TRIO_TOKEN_ATK 0
#define OJAMA_TRIO_TOKEN_DEF 1000
#define OJAMA_TRIO_DESTRUCTION_DAMAGE 300

static u8 OjamaTrioZoneIsOnMonsterRow(const struct DuelCard *zone)
{
  u8 i;

  if (zone == NULL)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gFixedZones[OPPONENT_MONSTER_ROW][i] == zone
        || gFixedZones[PLAYER_MONSTER_ROW][i] == zone)
      return TRUE;
  }

  return FALSE;
}

u8 OjamaTrioZoneIsMonsterForm(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == OJAMA_TRIO && OjamaTrioZoneIsOnMonsterRow(zone);
}

void ApplyOjamaTrioCardInfoOverridesForStatMod(struct StatMod *ptr)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  if (ptr == NULL || ptr->card != OJAMA_TRIO)
    return;

  zone = gSetFinalStatZone;
  if (zone != NULL && OjamaTrioZoneIsMonsterForm(zone))
    goto apply_token_stats;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++)
  {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
    {
      zone = gFixedZones[row][col];
      if (!OjamaTrioZoneIsMonsterForm(zone))
        continue;
      if (ComputeFinalStage(zone) != ptr->stage)
        continue;

      goto apply_token_stats;
    }
  }

  return;

apply_token_stats:
  gCardInfo.atk = OJAMA_TRIO_TOKEN_ATK;
  gCardInfo.def = OJAMA_TRIO_TOKEN_DEF;
  gCardInfo.type = TYPE_BEAST;
  gCardInfo.color = COLOR_NORMAL;
}

void ApplyOjamaTrioDestructionDamage(struct DuelCard *zone)
{
  u8 i;
  u8 fixedTarget;

  if (!OjamaTrioZoneIsMonsterForm(zone))
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gFixedZones[OPPONENT_MONSTER_ROW][i] == zone)
    {
      fixedTarget = DUEL_OPPONENT;
      goto apply_damage;
    }

    if (gFixedZones[PLAYER_MONSTER_ROW][i] == zone)
    {
      fixedTarget = DUEL_PLAYER;
      goto apply_damage;
    }
  }

  return;

apply_damage:
  {
    u8 turnDuelist = (fixedTarget == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER)
        ? ACTIVE_DUELIST : INACTIVE_DUELIST;

    Duel_ChangeLp(turnDuelist, -OJAMA_TRIO_DESTRUCTION_DAMAGE, FALSE);
  }
}

void SendOjamaTrioZoneToGraveyardIfNeeded(struct DuelCard *zone, u8 turn)
{
  if (!OjamaTrioZoneIsMonsterForm(zone))
    return;

  MarkGraveyardSendFromField();
  gDuel.duelistbattleState[turn].graveyard = zone->id;
}

static void SpecialSummonOjamaTriosToOpponent(void)
{
  u8 i;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  opts.markSpecialSummon = FALSE;
  opts.lockMonster = TRUE;

  for (i = 0; i < OJAMA_TRIO_SUMMON_COUNT; i++)
  {
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, OJAMA_TRIO, opts) != DUEL_ACTION_OK)
      break;
  }
}

static void ActivateOjamaTrioZone(struct DuelCard *zone)
{
  Duel_ActivateContinuousZone(zone);

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(OJAMA_TRIO, 3);

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonOjamaTriosToOpponent();
}

void TryActivateOjamaTrioOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != OJAMA_TRIO || zone->isFaceUp != FALSE)
      continue;

    if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      continue;

    ActivateOjamaTrioZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }
}
