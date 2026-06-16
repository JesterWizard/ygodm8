#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "fairy_box.h"

#define FAIRY_BOX_LP_COST 500

struct FairyBoxActionData {
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

extern struct FairyBoxActionData sActionData;

static struct DuelCard *FindFairyBoxOnDefenderBackrow(void)
{
  u8 i;
  u8 backrow = (WhoseTurn() == DUEL_PLAYER) ? OPPONENT_BACKROW : PLAYER_BACKROW;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[backrow][i];
    if (zone->id == FAIRY_BOX)
      return zone;
  }

  return NULL;
}

static u8 IsMonsterAttackAction(void)
{
  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4
      || sActionData.id == 5 || sActionData.id == 6;
}

static u16 *GetActiveAttackerAtkField(u16 *attackerCardId)
{
  if (WhoseTurn() == DUEL_PLAYER) {
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return NULL;

    *attackerCardId = sActionData.playerCardId;
    return &sActionData.playerCardAtkOrLifePointsMod;
  }

  if (sActionData.id != 1 && sActionData.id != 5 && sActionData.id != 6)
    return NULL;

  *attackerCardId = sActionData.opponentCardId;
  return &sActionData.opponentCardAtkOrLifePointsMod;
}

static u8 ActiveDuelistCanPayFairyBoxCost(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= FAIRY_BOX_LP_COST;

  return gDuelLifePoints[DUEL_OPPONENT] >= FAIRY_BOX_LP_COST;
}

u8 IsActivatedFairyBoxZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == FAIRY_BOX && zone->isFaceUp == TRUE;
}

void MarkFairyBoxJustSet(struct DuelCard *zone)
{
  if (zone->id == FAIRY_BOX)
    zone->unk4 = 1;
}

void AgeFairyBoxSetFlags(void)
{
  u8 i;
  struct DuelCard *zone;

  /* ponytail: age both fixed backrows so a trap set last turn is live when the other duelist attacks */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gFixedZones[PLAYER_BACKROW][i];
    if (zone->id == FAIRY_BOX && zone->unk4 != 0)
      zone->unk4 = 0;
    zone = gFixedZones[OPPONENT_BACKROW][i];
    if (zone->id == FAIRY_BOX && zone->unk4 != 0)
      zone->unk4 = 0;
  }
}

unsigned char ShouldActivateFairyBoxTurnEffect(void)
{
  return FALSE;
}

void ActivateFairyBoxTurnEffect(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
  Duel_ShowEffectTextTyped(FAIRY_BOX, 9);
}

unsigned char ShouldActivateFairyBoxUpkeep(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_BACKROW)
    return FALSE;
  if (gActiveEffect.col != GetFirstCardMatchZoneId(gTurnZones[ACTIVE_DUELIST_BACKROW], FAIRY_BOX))
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->id == FAIRY_BOX && zone->isFaceUp == TRUE;
}

void ActivateFairyBoxUpkeep(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  if (ActiveDuelistCanPayFairyBoxCost()) {
    Duel_ChangeLp(ACTIVE_DUELIST, -FAIRY_BOX_LP_COST, TRUE);
    return;
  }

  if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_ShowEffectTextTyped(FAIRY_BOX, 9);
}

void TryApplyFairyBoxToPendingAction(void)
{
  u16 *attackerAtk;
  u16 attackerCardId;
  struct DuelCard *fairyBox;

  if (!IsMonsterAttackAction())
    return;

  fairyBox = FindFairyBoxOnDefenderBackrow();
  if (fairyBox == NULL || fairyBox->unk4 != 0)
    return;

  attackerAtk = GetActiveAttackerAtkField(&attackerCardId);
  if (attackerAtk == NULL || attackerCardId == CARD_NONE)
    return;

  if (!fairyBox->isFaceUp) {
    FlipCardFaceUp(fairyBox);
    fairyBox->isLocked = TRUE;
  }

  if (RandRangeU8(0, 1) != 0)
    return;

  *attackerAtk = 0;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = FAIRY_BOX;
    gCardEffectTextData.cardId2 = attackerCardId;
    ActivateCardEffectText();
  }
}
