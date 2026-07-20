#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"

#define ALLURE_OF_DARKNESS_DRAW_COUNT 2

static u8 IsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 HandHasDarkMonster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDarkMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 PickDarkMonsterHandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsDarkMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDarkMonster(handRow[i]->id))
      return i;
  }

  return -1;
}

static void ALLURE_OF_DARKNESS_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  Duel_ShowEffectText(ALLURE_OF_DARKNESS);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, ALLURE_OF_DARKNESS_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (HandHasDarkMonster(handRow)) {
    handZone = PickDarkMonsterHandZone(handRow);
    if (handZone < 0)
      return;

    if (Duel_BanishZone(handRow[handZone], TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    if (Duel_DestroyAllHandCards(ACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectALLURE_OF_DARKNESS(void)
{
  if (Duel_TryResolveSpellThroughTraps(ALLURE_OF_DARKNESS, ALLURE_OF_DARKNESS_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
