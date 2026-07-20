#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define KNIGHT_OF_PENTACLES_COIN_HEADS 1
#define KNIGHT_OF_PENTACLES_COIN_TAILS 2

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

u8 KnightOfPentacles_ProtectsBattleZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id != KNIGHT_OF_PENTACLES)
    return FALSE;

  return zone->unk4 == KNIGHT_OF_PENTACLES_COIN_HEADS;
}

u8 KnightOfPentacles_CanAttackMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != KNIGHT_OF_PENTACLES)
    return TRUE;

  if (zone->unk4 == KNIGHT_OF_PENTACLES_COIN_TAILS)
    return FALSE;

  return TRUE;
}

unsigned char ShouldActivateKNIGHT_OF_PENTACLES(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != KNIGHT_OF_PENTACLES)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateKNIGHT_OF_PENTACLES(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(KNIGHT_OF_PENTACLES, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? KNIGHT_OF_PENTACLES_COIN_HEADS : KNIGHT_OF_PENTACLES_COIN_TAILS;
  /* ponytail: Tails "destroy when attacked" needs battle-step hook; unk4 tails = no attack only. */
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void KnightOfPentacles_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = KNIGHT_OF_PENTACLES;
  zone.unk4 = KNIGHT_OF_PENTACLES_COIN_TAILS;
  if (KnightOfPentacles_CanAttackMonsterZone(&zone) != FALSE)
    while (1)
      ;
}
#endif
