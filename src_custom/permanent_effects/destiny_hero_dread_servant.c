#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_dread_servant.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct DreadServantActionData {
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

extern struct DreadServantActionData sActionData;

void UpdateDuelGfxExceptField(void);

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void DestroyOneOwnSpellTrap(u8 ownerFixed)
{
  u8 backrow = ownerFixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 turn = TurnDuelistForFixed(ownerFixed);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backrow][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    Duel_ShowEffectTextTyped(DESTINY_HERO_DREAD_SERVANT, 2);
    Duel_DestroyZone(zone, turn, TRUE);
    UpdateDuelGfxExceptField();
    return;
  }
}

void ApplyDestinyHeroDreadServantBattleEffect(void)
{
  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.playerCardId == DESTINY_HERO_DREAD_SERVANT) {
    DestroyOneOwnSpellTrap(DUEL_PLAYER);
    return;
  }
  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == DESTINY_HERO_DREAD_SERVANT)
    DestroyOneOwnSpellTrap(DUEL_OPPONENT);
}

unsigned char ShouldActivateDESTINY_HERO_DREAD_SERVANT(void)
{
  /* Battle-destroy S/T via ApplyDestinyHeroDreadServantBattleEffect.
   * ponytail: NS Clock Tower counters need summon hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DREAD_SERVANT(void)
{
}
