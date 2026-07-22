#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsWindMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].attribute == ATTRIBUTE_WIND;
}

static u8 IsWindMonsterHand(u16 cardId)
{
  return IsWindMonsterId(cardId);
}

static u8 OwnMonsterRowHasWindTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[gMonEffect.row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (IsWindMonsterId(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != gMonEffect.row)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsWindMonsterId(zone->id);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = gMonEffect.row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTarget(*outRow, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void TryNormalSummonWindFromHand(void)
{
  struct DuelSummonOpts opts = Duel_DefaultNormalSummonOpts(TRUE);
  u8 savedBlocked = gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked;

  /* Granted NS after bounce — clear summoningBlocked like Necrovalley Throne. */
  gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = 0;
  if (Duel_NormalSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsWindMonsterHand, opts)
      != DUEL_ACTION_OK)
    gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = savedBlocked;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsValidTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  TryNormalSummonWindFromHand();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

unsigned char CanActivateHARPIE_DANCER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_DANCER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_DANCER)
    return FALSE;

  /* Name=Harpie Lady via HarpiePerfumer_TreatsNameAsHarpieLady + Duel_ZoneEffectCardId. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OwnMonsterRowHasWindTarget();
}

void ActivateHARPIE_DANCEREffect(void)
{
  Duel_ShowEffectTextTyped(HARPIE_DANCER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
