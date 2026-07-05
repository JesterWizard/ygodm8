#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "spell_effects.h"
#include "valhalla_hall_of_the_fallen.h"

void UnlockCardsInRow(unsigned char turnRow);

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u8 ControlsNoMonsters(void)
{
  return Duel_CountMonstersOnTurnRow(ACTIVE_DUELIST_MONSTER_ROW) == 0;
}

static u8 HandHasFairyMonster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsFairyMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateValhallaHallOfTheFallenIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != VALHALLA_HALL_OF_THE_FALLEN || zone->isFaceUp == FALSE)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!ControlsNoMonsters())
    return FALSE;

  if (!HandHasFairyMonster(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void ResolveValhallaIgnition(struct DuelCard *zone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanActivateValhallaHallOfTheFallenIgnition(zone))
    return;

  Duel_ShowEffectText(VALHALLA_HALL_OF_THE_FALLEN);

  if (IsDuelOver() == TRUE || !ControlsNoMonsters())
    return;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsFairyMonster, opts)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(zone);
}

APPEND_TEXT void EffectValhallaHallOfTheFallen(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    if (!CanActivateValhallaHallOfTheFallenIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveValhallaIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);

  if (CanActivateValhallaHallOfTheFallenIgnition(zone)) {
    ResolveValhallaIgnition(zone);
    return;
  }

  Duel_ShowEffectText(VALHALLA_HALL_OF_THE_FALLEN);
}

void TryUnlockHandForValhallaHallOfTheFallenIgnition(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (CanActivateValhallaHallOfTheFallenIgnition(gTurnZones[ACTIVE_DUELIST_BACKROW][i])) {
      UnlockCardsInRow(ACTIVE_DUELIST_HAND);
      return;
    }
  }
}

void TryEnableValhallaHallOfTheFallenIgnitionAfterPlacement(void)
{
  TryUnlockHandForValhallaHallOfTheFallenIgnition();
}
