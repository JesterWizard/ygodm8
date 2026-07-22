#include "global.h"
#include "common-chax.h"
#include "ancient_sacred_wyvern.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define WYVERN_SS_COST 1000

u8 GetDuelistForZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

struct WyvernActionData {
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

extern struct WyvernActionData sActionData;

u8 AncientSacredWyvern_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 me;
  u8 opp;
  s32 diff;
  u16 base;
  u16 atk;

  if (zone == NULL || zone->id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  me = GetDuelistForZone(zone);
  if (me > DUEL_OPPONENT)
    return FALSE;

  opp = me == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  diff = (s32)gDuelLifePoints[me] - (s32)gDuelLifePoints[opp];
  if (diff < 0)
    diff = -diff;

  SetCardInfo(zone->id);
  base = gCardInfo.atk;
  if ((s32)gDuelLifePoints[me] >= (s32)gDuelLifePoints[opp])
    atk = Duel_ClampStat((u32)base + (u32)diff);
  else
    atk = (base > (u16)diff) ? (u16)(base - (u16)diff) : 0;

  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static void TryWyvernSs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;

  if (gDuelLifePoints[fixedDuelist] < WYVERN_SS_COST)
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  Duel_ShowEffectTextTyped(ANCIENT_SACRED_WYVERN, 2);
  if (Duel_ChangeLp(turnDuelist, -(s32)WYVERN_SS_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromGrave(turnDuelist, ANCIENT_SACRED_WYVERN, opts);
  UpdateDuelGfxExceptField();
}

void ApplyAncientSacredWyvernBattleDestroySs(void)
{
  /* After ClearZone — self is in GY. */
  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.playerCardId == ANCIENT_SACRED_WYVERN) {
    TryWyvernSs(DUEL_PLAYER);
    return;
  }
  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == ANCIENT_SACRED_WYVERN)
    TryWyvernSs(DUEL_OPPONENT);
}

unsigned char CanActivateANCIENT_SACRED_WYVERN(void)
{
  if (gMonEffect.id != ANCIENT_SACRED_WYVERN)
    return FALSE;

  /* LP→ATK overlay + battle-destroy SS via ApplyAncientSacredWyvernBattleDestroySs. */
  return FALSE;
}

void ActivateANCIENT_SACRED_WYVERNEffect(void)
{
  Duel_ShowEffectTextTyped(ANCIENT_SACRED_WYVERN, 2);
}
