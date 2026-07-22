#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "horus_end_phase.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

typedef struct {
  u16 fromId;
  u16 toId;
} HorusEvolveEntry;

static const HorusEvolveEntry sHorusEvolve[] APPEND_RODATA = {
  { HORUS_THE_BLACK_FLAME_DRAGON_LV4, HORUS_THE_BLACK_FLAME_DRAGON_LV6 },
  { HORUS_THE_BLACK_FLAME_DRAGON_LV6, HORUS_THE_BLACK_FLAME_DRAGON_LV8 },
};

struct HorusBdActionData {
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

extern struct HorusBdActionData sActionData;
static u8 sHorusPending APPEND_DATA = {0};

static u8 HandHasHorus(u8 turnDuelist, u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnHands[turnDuelist][col]->id == cardId)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonHorus(u8 turnDuelist, u8 monsterRow, u16 cardId)
{
  u8 fixedDuelist;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  fixedDuelist = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
      ? DUEL_PLAYER
      : DUEL_OPPONENT;

  return HandHasHorus(turnDuelist, cardId)
      || Duel_FindDeckCardIndex(fixedDuelist, cardId) >= 0;
}

static const u8 sHorusPendingBits[][2] APPEND_RODATA = {
  { 1, 2 }, /* LV4 destroyed opp: player / opponent */
  { 4, 8 }, /* LV6 destroyed opp: player / opponent */
};

static void MarkHorusPendingIfDestroyedOpponent(u16 cardId, u8 entryIndex)
{
  if (sActionData.playerCardId == cardId && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
    sHorusPending |= sHorusPendingBits[entryIndex][0];
  if (sActionData.opponentCardId == cardId && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    sHorusPending |= sHorusPendingBits[entryIndex][1];
}

void ApplyHorusBattleDestroyPending(void)
{
  MarkHorusPendingIfDestroyedOpponent(HORUS_THE_BLACK_FLAME_DRAGON_LV4, 0);
  MarkHorusPendingIfDestroyedOpponent(HORUS_THE_BLACK_FLAME_DRAGON_LV6, 1);
}

void TryApplyHorusEndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 side = fixed == DUEL_PLAYER ? 0 : 1;
  u8 turnDuelist;
  u8 monsterRow;
  u8 i;
  u8 col;
  struct DuelCard *self = NULL;
  struct DuelSummonOpts opts;
  u16 nextId;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixed]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  for (i = 0; i < ARRAY_COUNT(sHorusEvolve); i++) {
    u8 evolveBit = sHorusPendingBits[i][side];

    if ((sHorusPending & evolveBit) == 0)
      continue;

    self = NULL;
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[monsterRow][col];

      if (zone != NULL && zone->id == sHorusEvolve[i].fromId && zone->isFaceUp) {
        self = zone;
        break;
      }
    }

    if (self == NULL)
      continue;

    nextId = sHorusEvolve[i].toId;
    if (!CanSpecialSummonHorus(turnDuelist, monsterRow, nextId))
      continue;

    sHorusPending &= (u8)~evolveBit;
    Duel_ShowEffectTextTyped(sHorusEvolve[i].fromId, 9);
    ClearZone(self);
    if (IsDuelOver() == TRUE)
      return;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (HandHasHorus(turnDuelist, nextId))
      Duel_SpecialSummonFromHand(turnDuelist, nextId, NULL, opts);
    else
      Duel_SpecialSummonFromDeck(turnDuelist, nextId, opts);

    UpdateDuelGfxExceptField();
    return;
  }
}
