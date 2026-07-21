#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "spell_effects.h"

static u16 EffectOptKeyForController(u16 cardId, u8 fixedDuelist)
{
  return (u16)(cardId | (fixedDuelist == DUEL_OPPONENT ? 0x8000 : 0));
}

static u8 ControlsFaceUpSpellcaster(u8 fixedDuelist)
{
  u8 col;
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone != NULL && zone->id != CARD_NONE
        && (IsCardFaceUp(zone) || zone->isDefending == FALSE)
        && Duel_CardHasMonsterType(zone->id, TYPE_SPELLCASTER))
      return TRUE;
  }

  return FALSE;
}

u8 MagiciansLeftHand_ShouldNegateTrap(u8 activatingFixedDuelist)
{
  u8 controller;

  if (activatingFixedDuelist != DUEL_PLAYER && activatingFixedDuelist != DUEL_OPPONENT)
    return FALSE;

  controller = activatingFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  if (EffectOpt_IsUsed(EffectOptKeyForController(MAGICIANS_LEFT_HAND, controller)))
    return FALSE;

  return Duel_FindBackrowCard(controller, MAGICIANS_LEFT_HAND, TRUE) != NULL
         && ControlsFaceUpSpellcaster(controller);
}

void MagiciansLeftHand_MarkTrapNegationUsed(u8 activatingFixedDuelist)
{
  u8 controller = activatingFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (activatingFixedDuelist == DUEL_PLAYER || activatingFixedDuelist == DUEL_OPPONENT)
    EffectOpt_MarkUsed(EffectOptKeyForController(MAGICIANS_LEFT_HAND, controller));
}

static void MAGICIANS_LEFT_HAND_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MAGICIANS_LEFT_HAND);
}

APPEND_TEXT void EffectMAGICIANS_LEFT_HAND(void)
{
  if (Duel_TryResolveSpellThroughTraps(MAGICIANS_LEFT_HAND, MAGICIANS_LEFT_HAND_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
