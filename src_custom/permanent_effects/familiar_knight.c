#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "exchange_hand_selection.h"
#include "familiar_knight.h"
#include "graveyard_effects.h"

#define FAMILIAR_KNIGHT_MAX_SUMMON_LEVEL 4

u8 gFamiliarKnightBattleDestroyPending;

static u8 IsFamiliarKnightSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);

  return gCardInfo.level <= FAMILIAR_KNIGHT_MAX_SUMMON_LEVEL;
}

static u8 HandHasFamiliarKnightTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsFamiliarKnightSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonForDuelist(u8 duelist)
{
  if (!HandHasFamiliarKnightTarget(gTurnHands[duelist]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[duelist == ACTIVE_DUELIST
          ? ACTIVE_DUELIST_MONSTER_ROW
          : INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static u8 TurnDuelistToFixed(u8 duelist)
{
  if (gTurnDuelistBattleState[duelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitSummonedMonsterZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static s8 PickFamiliarKnightHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsFamiliarKnightSummonTarget(cardId))
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

static void TrySpecialSummonForDuelist(u8 duelist)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  struct DuelCard **monsterRow = gTurnZones[duelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW];
  s8 handZone;
  s8 monsterZone;
  u16 monsterId;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonForDuelist(duelist))
    return;

  if (TurnDuelistToFixed(duelist) == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(handRow, IsFamiliarKnightSummonTarget);
  else
    handZone = PickFamiliarKnightHandZone(handRow, TRUE);

  monsterZone = FirstEmptyZoneInRow(monsterRow);
  if (handZone < 0 || monsterZone < 0)
    return;

  monsterId = handRow[handZone]->id;
  ClearZone(handRow[handZone]);

  summonZone = monsterRow[monsterZone];
  summonZone->id = monsterId;
  InitSummonedMonsterZone(summonZone);
}

void MarkFamiliarKnightBattleDestruction(u16 cardId)
{
  if (cardId == FAMILIAR_KNIGHT)
    gFamiliarKnightBattleDestroyPending = TRUE;
}

void ClearFamiliarKnightBattleDestroyPending(void)
{
  gFamiliarKnightBattleDestroyPending = FALSE;
}

unsigned char ShouldActivateFamiliarKnight(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gFamiliarKnightBattleDestroyPending)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != FAMILIAR_KNIGHT)
    return FALSE;

  if (gActiveEffect.turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == FAMILIAR_KNIGHT;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == FAMILIAR_KNIGHT;
}

void ActivateFamiliarKnight(void)
{
  u8 hideEffectText;
  u8 duelist;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = FAMILIAR_KNIGHT;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;

  GetGraveCardAndClearGrave2(gActiveEffect.turnRow == 6
      ? TurnDuelistToFixed(ACTIVE_DUELIST)
      : TurnDuelistToFixed(INACTIVE_DUELIST));
  ClearFamiliarKnightBattleDestroyPending();

  for (duelist = 0; duelist < 2; duelist++) {
    TrySpecialSummonForDuelist(duelist);
    if (IsDuelOver() == TRUE)
      return;
  }
}
