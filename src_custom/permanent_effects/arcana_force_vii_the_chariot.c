#include "global.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define ARCANA_FORCE_VII_THE_CHARIOT_COIN_HEADS 1

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

static u8 CanGiveSelfToOpponent(void)
{
  return FirstEmptyZoneInRow(gTurnZones[RivalTurnMonsterRow()]) >= 0;
}

static void GiveSelfToOpponent(struct DuelCard *self)
{
  u8 rivalRow = RivalTurnMonsterRow();
  s8 destCol;
  struct DuelCard *dst;
  u8 newFixedRow;

  if (self == NULL || self->id == CARD_NONE || !CanGiveSelfToOpponent())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[rivalRow]);
  if (destCol < 0)
    return;

  dst = gTurnZones[rivalRow][destCol];
  newFixedRow = RivalFixedMonsterRow();
  {
    u16 cardId = self->id;

    CopyCard(dst, self);
    dst->isFaceUp = TRUE;
    dst->isLocked = FALSE;
    dst->isDefending = FALSE;
    dst->unkTwo = 0;
    dst->unk4 = 2;
    dst->willChangeSides = TRUE;
    ClearZone(self);
    Duel_NotifyMonsterZoneChanged(dst);
    Duel_NotifyMonsterControlSwitched(cardId, newFixedRow);
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char ShouldActivateARCANA_FORCE_VII_THE_CHARIOT(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_VII_THE_CHARIOT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_VII_THE_CHARIOT(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_VII_THE_CHARIOT, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = ARCANA_FORCE_VII_THE_CHARIOT_COIN_HEADS;

  if (heads) {
    /* ponytail: battle SS destroyed monster needs battle-end hook; unk4=1 only. */
    return;
  }

  GiveSelfToOpponent(zone);
  /* ponytail: tails control switch is immediate; heads steal not wired. */
}
