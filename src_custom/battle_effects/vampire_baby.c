#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"
#include "vampire_baby.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct VampireBabyActionData {
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

extern struct VampireBabyActionData sActionData;

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

static u8 VampireBabySurvivedBattle(u16 playerCardId, u16 opponentCardId, u8 flags)
{
  if (playerCardId == VAMPIRE_BABY && !(flags & FLAG_GRAVEYARD_PLAYER))
    return TRUE;

  if (opponentCardId == VAMPIRE_BABY && !(flags & FLAG_GRAVEYARD_OPPONENT))
    return TRUE;

  return FALSE;
}

void ClearVampireBabyPending(void)
{
  gVampireBabyPendingController = VAMPIRE_BABY_PENDING_NONE;
  gVampireBabyPendingGraveyardDuelist = VAMPIRE_BABY_PENDING_NONE;
  gVampireBabyPendingCardId = CARD_NONE;
}

static void TryMarkVampireBabyDestruction(u8 controller, u8 graveyardDuelist, u16 destroyedCardId)
{
  if (destroyedCardId == CARD_NONE)
    return;

  if (GetTypeGroup(destroyedCardId) != TYPE_GROUP_MONSTER)
    return;

  gVampireBabyPendingController = controller;
  gVampireBabyPendingGraveyardDuelist = graveyardDuelist;
  gVampireBabyPendingCardId = destroyedCardId;
  gDeferGraveyardDrawBattleResolve = TRUE;
}

void MarkVampireBabyBattleDestruction(u16 playerCardId, u16 opponentCardId, u8 flags)
{
  if (gHideEffectText)
    return;

  if (!VampireBabySurvivedBattle(playerCardId, opponentCardId, flags))
    return;

  if ((flags & FLAG_GRAVEYARD_OPPONENT) != 0 && playerCardId == VAMPIRE_BABY)
    TryMarkVampireBabyDestruction(
        DUEL_PLAYER, DUEL_OPPONENT, gDuel.duelistbattleState[DUEL_OPPONENT].graveyard);

  if ((flags & FLAG_GRAVEYARD_PLAYER) != 0 && opponentCardId == VAMPIRE_BABY)
    TryMarkVampireBabyDestruction(
        DUEL_OPPONENT, DUEL_PLAYER, gDuel.duelistbattleState[DUEL_PLAYER].graveyard);

  if (gVampireBabyPendingController != VAMPIRE_BABY_PENDING_NONE && gUnk2023EA0.unk18 == 0)
    ResolveVampireBabyBattleEffect();
}

void ResolveVampireBabyBattleEffect(void)
{
  u8 controller;
  u8 graveyardDuelist;
  u8 graveyardTurnDuelist;
  u8 controllerTurnDuelist;
  u16 cardId;

  if (gVampireBabyPendingController == VAMPIRE_BABY_PENDING_NONE)
    return;

  controller = gVampireBabyPendingController;
  graveyardDuelist = gVampireBabyPendingGraveyardDuelist;
  ClearVampireBabyPending();

  Duel_ShowEffectTextTyped(VAMPIRE_BABY, 3);

  if (!ControllerHasOpenMonsterZone(controller))
    return;

  graveyardTurnDuelist = FixedDuelistToTurnDuelist(graveyardDuelist);
  if (gTurnDuelistBattleState[graveyardTurnDuelist]->graveyard == CARD_NONE)
    return;

  controllerTurnDuelist = FixedDuelistToTurnDuelist(controller);

  cardId = GetGraveCardAndClearGrave(graveyardTurnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_SpecialSummonMonsterId(controllerTurnDuelist, cardId,
                              Duel_DefaultSpecialSummonOpts(FALSE));
}
