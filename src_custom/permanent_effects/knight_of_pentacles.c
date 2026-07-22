#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "knight_of_pentacles.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct KnightOfPentaclesActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct KnightOfPentaclesActionData sActionData;

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

static u8 IsMonsterVersusMonsterBattleId(u8 id)
{
  return id == 1 || id == 2 || id == 5;
}

void ApplyKnightOfPentaclesTailsWhenAttacked(void)
{
  struct DuelCard *playerMon;
  struct DuelCard *oppMon;

  if (!IsMonsterVersusMonsterBattleId(sActionData.id))
    return;

  playerMon = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  oppMon = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

  if (playerMon != NULL && playerMon->id == KNIGHT_OF_PENTACLES
      && playerMon->unk4 == KNIGHT_OF_PENTACLES_COIN_TAILS
      && sActionData.opponentCardId != CARD_NONE)
    sActionData.flags |= FLAG_GRAVEYARD_PLAYER;

  if (oppMon != NULL && oppMon->id == KNIGHT_OF_PENTACLES
      && oppMon->unk4 == KNIGHT_OF_PENTACLES_COIN_TAILS
      && sActionData.playerCardId != CARD_NONE)
    sActionData.flags |= FLAG_GRAVEYARD_OPPONENT;
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
