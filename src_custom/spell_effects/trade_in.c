#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define TRADE_IN_DRAW_COUNT 2
#define TRADE_IN_DISCARD_LEVEL 8

static u8 IsLevel8Monster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == TRADE_IN_DISCARD_LEVEL;
}

static u8 HandHasLevel8Monster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLevel8Monster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateTradeIn(void)
{
  return HandHasLevel8Monster(gTurnHands[ACTIVE_DUELIST]);
}

static s8 PickLevel8HandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsLevel8Monster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLevel8Monster(handRow[i]->id))
      return i;
  }

  return -1;
}

static void TradeIn_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  if (!CanActivateTradeIn())
    return;

  Duel_ShowEffectText(TRADE_IN);

  if (IsDuelOver() == TRUE)
    return;

  handZone = PickLevel8HandZone(handRow);
  if (handZone < 0)
    return;

  ClearZoneAndSendMonToGraveyard(handRow[handZone], ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, TRADE_IN_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectTRADE_IN(void)
{
  if (Duel_TryResolveSpellThroughTraps(TRADE_IN, TradeIn_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
