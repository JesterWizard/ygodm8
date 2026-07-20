#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "reptilianne_scylla.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

extern const CardData gCardData_NEW[];

struct ReptilianneScyllaActionData {
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

extern struct ReptilianneScyllaActionData sActionData;

void ClearReptilianneScyllaPending(void)
{
  gPendingReptilianneScyllaController = REPTILIANNE_SCYLLA_PENDING_NONE;
  gPendingReptilianneScyllaGraveyardDuelist = REPTILIANNE_SCYLLA_PENDING_NONE;
}

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
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

static u16 GetOriginalCardAtk(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static void TryMarkScyllaRevive(u8 controller, u8 graveyardDuelist, u16 destroyedCardId)
{
  if (destroyedCardId == CARD_NONE)
    return;

  if (GetTypeGroup(destroyedCardId) != TYPE_GROUP_MONSTER)
    return;

  if (GetOriginalCardAtk(destroyedCardId) != 0)
    return;

  if (!ControllerHasOpenMonsterZone(controller))
    return;

  gPendingReptilianneScyllaController = controller;
  gPendingReptilianneScyllaGraveyardDuelist = graveyardDuelist;
}

void ApplyReptilianneScyllaBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.playerCardId == REPTILIANNE_SCYLLA
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    TryMarkScyllaRevive(DUEL_PLAYER, DUEL_OPPONENT, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == REPTILIANNE_SCYLLA
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    TryMarkScyllaRevive(DUEL_OPPONENT, DUEL_PLAYER, sActionData.playerCardId);
  } else {
    return;
  }

  if (gPendingReptilianneScyllaController == REPTILIANNE_SCYLLA_PENDING_NONE)
    return;

  if (gUnk2023EA0.unk18 == 0)
    ResolveReptilianneScyllaBattleEffect();
}

void ResolveReptilianneScyllaBattleEffect(void)
{
  u8 controller;
  u8 graveyardDuelist;
  u8 controllerTurnDuelist;
  u8 graveyardTurnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;
  struct DuelCard *zone;

  controller = gPendingReptilianneScyllaController;
  if (controller == REPTILIANNE_SCYLLA_PENDING_NONE)
    return;

  graveyardDuelist = gPendingReptilianneScyllaGraveyardDuelist;
  ClearReptilianneScyllaPending();

  Duel_ShowEffectTextTyped(REPTILIANNE_SCYLLA, 3);

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

  {
    u8 monsterRow = Duel_TurnMonsterRowForDuelist(controllerTurnDuelist);
    s8 emptyCol = FirstEmptyZoneInRow(gTurnZones[monsterRow]);

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
    if (Duel_SpecialSummonMonsterId(controllerTurnDuelist, cardId, opts) != DUEL_ACTION_OK)
      return;

    zone = gTurnZones[monsterRow][emptyCol];
    if (zone != NULL && zone->id == cardId)
      zone->unk4 = 1;
  }
}
