#include "global.h"
#include "ameba.h"
#include "arcana_force_vii_the_chariot.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define ARCANA_FORCE_VII_THE_CHARIOT_COIN_HEADS 1
#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ArcanaForceViiChariotActionData {
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

extern struct ArcanaForceViiChariotActionData sActionData;

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 SummonerFixedMonsterRow(void)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(SelfZone(), &fixedRow, &col))
    return PLAYER_MONSTER_ROW;

  return fixedRow;
}

static u8 RivalFixedMonsterRow(void)
{
  u8 row = SummonerFixedMonsterRow();

  return row == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 SummonerTurnMonsterRow(void)
{
  return gActiveEffect.turnRow;
}

static u8 RivalTurnMonsterRow(void)
{
  return gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 CanGiveSelfToOpponent(void)
{
  return FirstEmptyZoneInRow(gTurnZones[RivalTurnMonsterRow()]) >= 0;
}

static void GiveSelfToOpponent(struct DuelCard *self)
{
  u8 rivalRow = RivalTurnMonsterRow();
  s8 destCol;
  struct DuelCard *dst;
  u8 newFixedRow;

  if (self == NULL || self->id == CARD_NONE || !CanGiveSelfToOpponent())
    return;

  destCol = FirstEmptyZoneInRow(gTurnZones[rivalRow]);
  if (destCol < 0)
    return;

  dst = gTurnZones[rivalRow][destCol];
  newFixedRow = RivalFixedMonsterRow();
  {
    u16 cardId = self->id;

    CopyCard(dst, self);
    dst->isFaceUp = TRUE;
    dst->isLocked = FALSE;
    dst->isDefending = FALSE;
    dst->unkTwo = 0;
    dst->unk4 = 2;
    dst->willChangeSides = TRUE;
    ClearZone(self);
    Duel_NotifyMonsterZoneChanged(dst);
    Duel_NotifyMonsterControlSwitched(cardId, newFixedRow);
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
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

static u8 ChariotHasHeads(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  return zone != NULL && zone->id == ARCANA_FORCE_VII_THE_CHARIOT
      && zone->unk4 == ARCANA_FORCE_VII_THE_CHARIOT_COIN_HEADS;
}

void ClearArcanaForceViiChariotPending(void)
{
  gArcanaForceViiChariotPendingController = ARCANA_FORCE_VII_THE_CHARIOT_PENDING_NONE;
  gArcanaForceViiChariotPendingGraveyardDuelist = ARCANA_FORCE_VII_THE_CHARIOT_PENDING_NONE;
}

static void TryMarkChariotSteal(u8 controller, u8 graveyardDuelist, u16 destroyedCardId)
{
  if (destroyedCardId == CARD_NONE)
    return;
  if (GetTypeGroup(destroyedCardId) != TYPE_GROUP_MONSTER)
    return;

  gArcanaForceViiChariotPendingController = controller;
  gArcanaForceViiChariotPendingGraveyardDuelist = graveyardDuelist;
  gDeferGraveyardDrawBattleResolve = TRUE;
}

void ApplyArcanaForceViiChariotBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == ARCANA_FORCE_VII_THE_CHARIOT
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && ChariotHasHeads(sActionData.playerMonsterRow, sActionData.unkA)) {
    TryMarkChariotSteal(DUEL_PLAYER, DUEL_OPPONENT, sActionData.opponentCardId);
  } else if (sActionData.opponentCardId == ARCANA_FORCE_VII_THE_CHARIOT
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && ChariotHasHeads(sActionData.opponentMonsterRow, sActionData.unk16)) {
    TryMarkChariotSteal(DUEL_OPPONENT, DUEL_PLAYER, sActionData.playerCardId);
  } else {
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveArcanaForceViiChariotBattleEffect();
}

void ResolveArcanaForceViiChariotBattleEffect(void)
{
  u8 controller;
  u8 graveyardDuelist;
  u8 graveyardTurnDuelist;
  u8 controllerTurnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (gArcanaForceViiChariotPendingController == ARCANA_FORCE_VII_THE_CHARIOT_PENDING_NONE)
    return;

  controller = gArcanaForceViiChariotPendingController;
  graveyardDuelist = gArcanaForceViiChariotPendingGraveyardDuelist;
  ClearArcanaForceViiChariotPending();

  Duel_ShowEffectTextTyped(ARCANA_FORCE_VII_THE_CHARIOT, 3);

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
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  Duel_SpecialSummonMonsterId(controllerTurnDuelist, cardId, opts);
}

unsigned char ShouldActivateARCANA_FORCE_VII_THE_CHARIOT(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_VII_THE_CHARIOT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_VII_THE_CHARIOT(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_VII_THE_CHARIOT, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? ARCANA_FORCE_VII_THE_CHARIOT_COIN_HEADS : 2;

  if (heads)
    return;

  GiveSelfToOpponent(zone);
}
