#include "global.h"
#include "common-chax.h"
#include "ancient_gear_engineer_battle.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AncientGearEngineerActionData {
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

extern struct AncientGearEngineerActionData sActionData;

void UpdateDuelGfxExceptField(void);

static u8 OppBackrowFixedForEngineer(u8 engineerFixedRow)
{
  return engineerFixedRow == PLAYER_MONSTER_ROW ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsSetSpellTrapOnBackrow(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || zone->isFaceUp)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 DestroyFirstSetSpellTrap(u8 engineerFixedRow)
{
  u8 back = OppBackrowFixedForEngineer(engineerFixedRow);
  u8 col;
  u8 graveyardDuelist = back == OPPONENT_BACKROW ? DUEL_OPPONENT : DUEL_PLAYER;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[back][col];

    if (!IsSetSpellTrapOnBackrow(back, col))
      continue;

    if (Duel_DestroyZone(zone, graveyardDuelist, TRUE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
    return TRUE;
  }

  return FALSE;
}

static u8 EngineerAttackedAndDestroyedMonster(u8 *outFixedRow)
{
  if (sActionData.playerCardId == ANCIENT_GEAR_ENGINEER
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    *outFixedRow = sActionData.playerMonsterRow;
    return TRUE;
  }

  if (sActionData.opponentCardId == ANCIENT_GEAR_ENGINEER
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    *outFixedRow = sActionData.opponentMonsterRow;
    return TRUE;
  }

  return FALSE;
}

void ApplyAncientGearEngineerBattleEffect(void)
{
  u8 engineerFixedRow;

  if (gHideEffectText)
    return;

  if (!EngineerAttackedAndDestroyedMonster(&engineerFixedRow))
    return;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_ENGINEER, 2);
  DestroyFirstSetSpellTrap(engineerFixedRow);
}
