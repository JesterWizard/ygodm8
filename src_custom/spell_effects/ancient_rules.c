#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define ANCIENT_RULES_MIN_SUMMON_LEVEL 5

static u8 IsAncientRulesSummonTarget(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);

  if (gCardInfo.color != COLOR_NORMAL)
    return FALSE;

  return gCardInfo.level >= ANCIENT_RULES_MIN_SUMMON_LEVEL;
}

static u8 HandHasAncientRulesTarget(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsAncientRulesSummonTarget(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonWithAncientRules(void)
{
  if (!HandHasAncientRulesTarget(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
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

static s8 PickAncientRulesHandZone(struct DuelCard **handRow, u8 pickHighestAtk)
{
  u8 i;
  s8 chosenZone = -1;
  u16 bestAtk = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;

    if (!IsAncientRulesSummonTarget(cardId))
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

static void SpecialSummonAncientRulesTarget(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;
  s8 monsterZone;
  u16 monsterId;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonWithAncientRules())
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(handRow, IsAncientRulesSummonTarget);
  else
    handZone = PickAncientRulesHandZone(handRow, TRUE);

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (handZone < 0 || monsterZone < 0)
    return;

  monsterId = handRow[handZone]->id;
  ClearZone(handRow[handZone]);

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  summonZone->id = monsterId;
  InitSummonedMonsterZone(summonZone);
}

APPEND_TEXT void EffectAncientRules(void)
{
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = ANCIENT_RULES;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonAncientRulesTarget();
}
