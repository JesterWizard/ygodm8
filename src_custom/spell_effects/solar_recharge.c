#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define SOLAR_RECHARGE_DRAW_COUNT 2
#define SOLAR_RECHARGE_MILL_COUNT 2

static const char sLightswornArchetypeName[] APPEND_RODATA = "Lightsworn";

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornArchetypeName);
}

static u8 HandHasLightsworn(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLightswornMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateSOLAR_RECHARGE(void)
{
  return HandHasLightsworn(gTurnHands[ACTIVE_DUELIST]);
}

static s8 PickLightswornHandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsLightswornMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLightswornMonster(handRow[i]->id))
      return i;
  }

  return -1;
}

static void SOLAR_RECHARGE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  if (!CanActivateSOLAR_RECHARGE())
    return;

  Duel_ShowEffectText(SOLAR_RECHARGE);

  if (IsDuelOver() == TRUE)
    return;

  handZone = PickLightswornHandZone(handRow);
  if (handZone < 0)
    return;

  ClearZoneAndSendMonToGraveyard(handRow[handZone], ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, SOLAR_RECHARGE_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: mill helper advances deck top only (no expanded-GY push), matching
   * charge_of_the_light_brigade. Ceiling: milled cards may not appear in GY UI. */
  if (Duel_MillTopDeckCards(ACTIVE_DUELIST, SOLAR_RECHARGE_MILL_COUNT, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectSOLAR_RECHARGE(void)
{
  if (!CanActivateSOLAR_RECHARGE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SOLAR_RECHARGE, SOLAR_RECHARGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
