#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);

static u8 CardIsDragon(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_DRAGON;
}

static u8 HandHasDragon(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (CardIsDragon(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 DuelistForMonsterRow(u8 row)
{
  if (row == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (row == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static s8 PickDragonHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!CardIsDragon(cardId))
      continue;

    if (!pickHighestAtk)
      return i;

    SetCardInfo(cardId);
    if (chosenZone < 0 || gCardInfo.atk > bestAtk) {
      chosenZone = i;
      bestAtk = gCardInfo.atk;
    }
  }

  return chosenZone;
}

unsigned char CanActivateKaibaman(void)
{
  if (gMonEffect.id != KAIBAMAN)
    return FALSE;

  return HandHasDragon(gTurnHands[ACTIVE_DUELIST]);
}

void ActivateKaibamanEffect(void)
{
  struct DuelCard *kaibamanZone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 duelist = DuelistForMonsterRow(gMonEffect.row);
  s8 handZone;
  u16 dragonId;

  Duel_ShowEffectTextTyped(KAIBAMAN, 2);

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingType(handRow, TYPE_DRAGON);
  else
    handZone = PickDragonHandZone(handRow, TRUE);

  if (handZone < 0)
    return;

  dragonId = handRow[handZone]->id;

  ClearZone(handRow[handZone]);
  if (Duel_DestroyZone(kaibamanZone, duelist, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: tribute-replacement in same zone; not a marked special summon (unk4 stays 0) */
  kaibamanZone->id = dragonId;
  kaibamanZone->isFaceUp = TRUE;
  kaibamanZone->isLocked = TRUE;
  kaibamanZone->isDefending = FALSE;
  kaibamanZone->permStage = 0;
  kaibamanZone->tempStage = 0;
  kaibamanZone->unk4 = 0;
  kaibamanZone->unkTwo = 0;
  kaibamanZone->willChangeSides = 0;

  gDuelCursor.currentX = gMonEffect.zone;
  gDuelCursor.currentY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  gDuelCursor.destY = gMonEffect.row;
  DisplayCardInfoBar();
  sub_8041E70(PLAYER_HAND, gMonEffect.row);
}
