#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"
#include "ghost_knight_of_jackal.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct GhostKnightOfJackalActionData {
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

extern struct GhostKnightOfJackalActionData sActionData;

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 duelist;

  for (duelist = 0; duelist < 2; duelist++) {
    if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[fixedDuelist])
      return duelist;
  }

  return ACTIVE_DUELIST;
}

static u8 ControllerHasOpenMonsterZone(u8 controller)
{
  u8 turnDuelist = FixedDuelistToTurnDuelist(controller);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

void ClearGhostKnightOfJackalPending(void)
{
  gGhostKnightOfJackalPendingController = GHOST_KNIGHT_OF_JACKAL_PENDING_NONE;
  gGhostKnightOfJackalPendingGraveyardDuelist = GHOST_KNIGHT_OF_JACKAL_PENDING_NONE;
}

static void TryMarkJackalDestruction(u8 controller, u8 graveyardDuelist, u16 destroyedCardId)
{
  if (destroyedCardId == CARD_NONE)
    return;

  if (GetTypeGroup(destroyedCardId) != TYPE_GROUP_MONSTER)
    return;

  gGhostKnightOfJackalPendingController = controller;
  gGhostKnightOfJackalPendingGraveyardDuelist = graveyardDuelist;
  gDeferGraveyardDrawBattleResolve = TRUE;
}

void ApplyGhostKnightOfJackalBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == GHOST_KNIGHT_OF_JACKAL
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    TryMarkJackalDestruction(
        DUEL_PLAYER, DUEL_OPPONENT, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == GHOST_KNIGHT_OF_JACKAL
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    TryMarkJackalDestruction(
        DUEL_OPPONENT, DUEL_PLAYER, sActionData.playerCardId);
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveGhostKnightOfJackalBattleEffect();
}

void ResolveGhostKnightOfJackalBattleEffect(void)
{
  u8 controller;
  u8 graveyardDuelist;
  u8 graveyardTurnDuelist;
  u8 controllerTurnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (gGhostKnightOfJackalPendingController == GHOST_KNIGHT_OF_JACKAL_PENDING_NONE)
    return;

  controller = gGhostKnightOfJackalPendingController;
  graveyardDuelist = gGhostKnightOfJackalPendingGraveyardDuelist;
  ClearGhostKnightOfJackalPending();

  Duel_ShowEffectTextTyped(GHOST_KNIGHT_OF_JACKAL, 3);

  if (IsDuelOver() == TRUE)
    return;

  if (!ControllerHasOpenMonsterZone(controller))
    return;

  graveyardTurnDuelist = FixedDuelistToTurnDuelist(graveyardDuelist);
  if (gTurnDuelistBattleState[graveyardTurnDuelist]->graveyard == CARD_NONE)
    return;

  controllerTurnDuelist = FixedDuelistToTurnDuelist(controller);

  cardId = GetGraveCardAndClearGrave(graveyardTurnDuelist);
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonMonsterId(controllerTurnDuelist, cardId, opts);
}
