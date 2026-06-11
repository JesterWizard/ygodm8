#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "ojama_trio.h"
#include "graveyard_effects.h"
#include "riryoku.h"

#define OJAMA_TRIO_SUMMON_COUNT 3
#define OJAMA_TRIO_TOKEN_ATK 0
#define OJAMA_TRIO_TOKEN_DEF 1000
#define OJAMA_TRIO_DESTRUCTION_DAMAGE 300

void UpdateDuelGfxExceptField(void);
void HandleAtkAndLifePointsAction(void);
void CheckLoserFlags(void);

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
      if (GetFinalStage(zone) != ptr->stage)
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

  if (!OjamaTrioZoneIsMonsterForm(zone))
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    if (gFixedZones[OPPONENT_MONSTER_ROW][i] == zone)
    {
      SetOpponentLifePointsToSubtract(OJAMA_TRIO_DESTRUCTION_DAMAGE);
      HandleAtkAndLifePointsAction();
      CheckLoserFlags();
      return;
    }

    if (gFixedZones[PLAYER_MONSTER_ROW][i] == zone)
    {
      SetPlayerLifePointsToSubtract(OJAMA_TRIO_DESTRUCTION_DAMAGE);
      HandleAtkAndLifePointsAction();
      CheckLoserFlags();
      return;
    }
  }
}

void SendOjamaTrioZoneToGraveyardIfNeeded(struct DuelCard *zone, u8 turn)
{
  if (!OjamaTrioZoneIsMonsterForm(zone))
    return;

  MarkGraveyardSendFromField();
  gDuel.duelistbattleState[turn].graveyard = zone->id;
}

static void InitOjamaTrioTokenZone(struct DuelCard *zone)
{
  zone->id = OJAMA_TRIO;
  zone->isFaceUp = TRUE;
  zone->isLocked = TRUE;
  zone->isDefending = TRUE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void SpecialSummonOjamaTriosToOpponent(void)
{
  u8 i;
  s8 monsterZone;
  struct DuelCard *summonZone;

  for (i = 0; i < OJAMA_TRIO_SUMMON_COUNT; i++)
  {
    monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
    if (monsterZone < 0)
      break;

    summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
    InitOjamaTrioTokenZone(summonZone);
  }
}

static void ActivateOjamaTrioZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  ClearZoneAndSendMonToGraveyard(zone, INACTIVE_DUELIST);

  if (!gHideEffectText)
  {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = OJAMA_TRIO;
    ActivateCardEffectText();
  }

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
