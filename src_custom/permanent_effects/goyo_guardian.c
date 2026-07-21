#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "goyo_guardian.h"
#include "graveyard_effects.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct GoyoGuardianActionData {
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

extern struct GoyoGuardianActionData sActionData;

void ClearGoyoGuardianPending(void)
{
  gGoyoGuardianPendingController = GOYO_GUARDIAN_PENDING_NONE;
  gGoyoGuardianPendingGraveyardDuelist = GOYO_GUARDIAN_PENDING_NONE;
}

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

static void TryMarkGoyo(u8 controller, u8 graveyardDuelist, u16 destroyedCardId)
{
  if (destroyedCardId == CARD_NONE)
    return;
  if (GetTypeGroup(destroyedCardId) != TYPE_GROUP_MONSTER)
    return;

  gGoyoGuardianPendingController = controller;
  gGoyoGuardianPendingGraveyardDuelist = graveyardDuelist;
  gDeferGraveyardDrawBattleResolve = TRUE;
}

void ApplyGoyoGuardianBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.playerCardId == GOYO_GUARDIAN
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    TryMarkGoyo(DUEL_PLAYER, DUEL_OPPONENT, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == GOYO_GUARDIAN
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    TryMarkGoyo(DUEL_OPPONENT, DUEL_PLAYER, sActionData.playerCardId);
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveGoyoGuardianBattleEffect();
}

void ResolveGoyoGuardianBattleEffect(void)
{
  u8 controller;
  u8 graveyardDuelist;
  u8 graveyardTurnDuelist;
  u8 controllerTurnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (gGoyoGuardianPendingController == GOYO_GUARDIAN_PENDING_NONE)
    return;

  controller = gGoyoGuardianPendingController;
  graveyardDuelist = gGoyoGuardianPendingGraveyardDuelist;
  ClearGoyoGuardianPending();

  Duel_ShowEffectTextTyped(GOYO_GUARDIAN, 3);
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

unsigned char ShouldActivateGOYO_GUARDIAN(void)
{
  (void)gActiveEffect;
  return FALSE;
}

void ActivateGOYO_GUARDIAN(void)
{
}
