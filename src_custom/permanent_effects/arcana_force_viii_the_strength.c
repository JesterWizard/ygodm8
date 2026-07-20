#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 SummonerFixedMonsterRow(void)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(SelfZone(), &fixedRow, &col))
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
  u8 summonerRow = SummonerTurnMonsterRow();
  u8 rivalRow = RivalTurnMonsterRow();

  return NumEmptyZonesInRow(gTurnZones[summonerRow]) > 0
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[rivalRow]) < MAX_ZONES_IN_ROW;
}

static u8 CanGiveControlOfOwnMonster(void)
{
  u8 summonerRow = SummonerTurnMonsterRow();
  u8 rivalRow = RivalTurnMonsterRow();

  return NumEmptyZonesInRow(gTurnZones[rivalRow]) > 0
      && NumEmptyZonesAndGodCardsInRow(gTurnZones[summonerRow]) < MAX_ZONES_IN_ROW;
}

static u8 IsValidStealTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != RivalFixedMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 IsValidGiveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = SelfZone();

  if (fixedRow != SummonerFixedMonsterRow())
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || zone == self)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FieldHasStealTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidStealTarget(RivalFixedMonsterRow(), col))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasGiveTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidGiveTarget(SummonerFixedMonsterRow(), col))
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

static void GiveControlOfMonsterZone(struct DuelCard *src)
{
  u8 rivalRow = RivalTurnMonsterRow();
  s8 destCol;
  struct DuelCard *dst;
  u8 newFixedRow;

  if (src == NULL || src->id == CARD_NONE || !CanGiveControlOfOwnMonster())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[rivalRow]);
  if (destCol < 0)
    return;

  dst = gTurnZones[rivalRow][destCol];
  newFixedRow = RivalFixedMonsterRow();
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

static void ResolveStealTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidStealTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  TakeControlOfMonsterZone(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void ResolveGiveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidGiveTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  GiveControlOfMonsterZone(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickStealTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;
  u8 rivalRow = RivalFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidStealTarget(rivalRow, col))
      continue;

    zone = gFixedZones[rivalRow][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = rivalRow;
  *outCol = bestCol;
  return TRUE;
}

static u8 AiPickGiveTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;
  u8 ownRow = SummonerFixedMonsterRow();
  struct DuelCard *self = SelfZone();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    zone = gFixedZones[ownRow][col];
    if (zone == self)
      continue;

    if (!IsValidGiveTarget(ownRow, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = ownRow;
  *outCol = bestCol;
  return TRUE;
}

static void BeginStealTargeting(void)
{
  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;
  Duel_SetupPickZone(IsValidStealTarget, ResolveStealTarget, CancelTargeting, AiPickStealTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void BeginGiveTargeting(void)
{
  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;
  Duel_SetupPickZone(IsValidGiveTarget, ResolveGiveTarget, CancelTargeting, AiPickGiveTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

unsigned char ShouldActivateARCANA_FORCE_VIII_THE_STRENGTH(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_VIII_THE_STRENGTH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_VIII_THE_STRENGTH(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_VIII_THE_STRENGTH, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  zone->unk4 = 1;
  heads = RandRangeU8(0, 1) == 1;

  if (heads) {
    if (!CanTakeControlOfRivalMonster() || !FieldHasStealTarget())
      return;

    BeginStealTargeting();
    return;
  }

  if (!CanGiveControlOfOwnMonster() || !FieldHasGiveTarget())
    return;

  BeginGiveTargeting();
}
