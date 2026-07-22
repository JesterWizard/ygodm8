#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "gladiator_beast_battled.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

struct GladiatorBeastBattledActionData {
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

extern struct GladiatorBeastBattledActionData sActionData;

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static void MarkBattledZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone != NULL && zone->id != CARD_NONE)
    zone->unk4 |= GLADIATOR_BEAST_BATTLED_MARK;
}

static void MarkGladiatorFromBattle(u16 cardId, u8 fixedRow, u8 fixedCol)
{
  if (!IsGladiatorBeastMonster(cardId))
    return;

  MarkBattledZone(fixedRow, fixedCol);
}

u8 GladiatorBeast_ZoneBattledThisBattlePhase(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return (zone->unk4 & GLADIATOR_BEAST_BATTLED_MARK) != 0;
}

void ApplyGladiatorBeastBattledMarks(void)
{
  if (sActionData.id == 0)
    return;

  MarkGladiatorFromBattle(sActionData.playerCardId, sActionData.playerMonsterRow,
                          sActionData.unkA);
  MarkGladiatorFromBattle(sActionData.opponentCardId, sActionData.opponentMonsterRow,
                          sActionData.unk16);
}

void ClearGladiatorBeastBattledMarks(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL)
        zone->unk4 &= (u8)~GLADIATOR_BEAST_BATTLED_MARK;
    }
  }
}

#if !defined(__GNUC__)
void GladiatorBeastBattled_SelfCheck(void);
#endif

void GladiatorBeastBattled_SelfCheck(void)
{
  struct DuelCard fake;

  fake.id = GLADIATOR_BEAST_HOPLOMUS;
  fake.unk4 = GLADIATOR_BEAST_BATTLED_MARK;
  if (!GladiatorBeast_ZoneBattledThisBattlePhase(&fake))
    return;
}
