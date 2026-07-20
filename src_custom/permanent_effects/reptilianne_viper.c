#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "summon_tribute.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 SummonerFixedMonsterRow(void)
{
  u8 fixedRow;
  u8 col;
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!Duel_FindFixedMonsterZone(self, &fixedRow, &col))
    return PLAYER_MONSTER_ROW;

  return fixedRow;
}

static u8 RivalFixedMonsterRow(void)
{
  u8 row = SummonerFixedMonsterRow();

  return row == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 SummonerTurnMonsterRow(void)
{
  return gActiveEffect.turnRow;
}

static u8 RivalTurnMonsterRow(void)
{
  return gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 CanTakeControlOfRivalMonster(void)
{
  return NumEmptyZonesInRow(gTurnZones[SummonerTurnMonsterRow()]) > 0
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[RivalTurnMonsterRow()]) < MAX_ZONES_IN_ROW;
}

static u8 IsValidTakeControlTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != RivalFixedMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (!IsCardFaceUp(zone))
    return FALSE;

  return Duel_GetZoneFinalAtk(zone) == 0;
}

static u8 FieldHasTakeControlTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTakeControlTarget(RivalFixedMonsterRow(), col))
      return TRUE;
  }

  return FALSE;
}

static void TakeControlOfMonsterZone(struct DuelCard *src)
{
  u8 summonerRow = SummonerTurnMonsterRow();
  s8 destCol;
  struct DuelCard *dst;
  u8 newFixedRow;

  if (src == NULL || src->id == CARD_NONE || !CanTakeControlOfRivalMonster())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[summonerRow]);
  if (destCol < 0)
    return;

  dst = gTurnZones[summonerRow][destCol];
  newFixedRow = SummonerFixedMonsterRow();
  {
    u16 cardId = src->id;

    CopyCard(dst, src);
    dst->isFaceUp = TRUE;
    dst->isLocked = FALSE;
    dst->isDefending = FALSE;
    dst->unkTwo = 0;
    dst->unk4 = 2;
    dst->willChangeSides = TRUE;
    ClearZone(src);
    Duel_NotifyMonsterZoneChanged(dst);
    Duel_NotifyMonsterControlSwitched(cardId, newFixedRow);
  }
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (!IsValidTakeControlTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  TakeControlOfMonsterZone(zone);

  if (self != NULL)
    self->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  struct DuelCard *self = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  PlayMusic(SFX_CANCEL);
  if (self != NULL)
    self->unk4 = 1;
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 rivalRow = RivalFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidTakeControlTarget(rivalRow, col))
      continue;

    *outRow = rivalRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

unsigned char ShouldActivateREPTILIANNE_VIPER(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != REPTILIANNE_VIPER)
    return FALSE;

  if (GetPendingTributeSummonCardId() != REPTILIANNE_VIPER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return CanTakeControlOfRivalMonster() && FieldHasTakeControlTarget();
}

void ActivateREPTILIANNE_VIPER(void)
{
  Duel_ShowEffectTextTyped(REPTILIANNE_VIPER, 8);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;

  Duel_SetupPickZone(IsValidTakeControlTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
