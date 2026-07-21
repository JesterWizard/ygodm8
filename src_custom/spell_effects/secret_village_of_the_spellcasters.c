#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "secret_village_of_the_spellcasters.h"
#include "spell_effects.h"

static u8 ControlsSpellcaster(u8 fixedDuelist)
{
  u8 col;
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id != CARD_NONE
        && Duel_CardHasMonsterType(zone->id, TYPE_SPELLCASTER))
      return TRUE;
  }

  return FALSE;
}

u8 SecretVillage_BlocksSpellActivation(u8 activatingFixedDuelist)
{
  u8 opp;

  if (Duel_FindBackrowCard(DUEL_PLAYER, SECRET_VILLAGE_OF_THE_SPELLCASTERS, TRUE) == NULL
      && Duel_FindBackrowCard(DUEL_OPPONENT, SECRET_VILLAGE_OF_THE_SPELLCASTERS, TRUE) == NULL)
    return FALSE;

  if (activatingFixedDuelist > DUEL_OPPONENT)
    return FALSE;

  opp = activatingFixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  if (ControlsSpellcaster(activatingFixedDuelist))
    return FALSE;
  if (ControlsSpellcaster(opp))
    return TRUE;

  return FALSE;
}

static void SECRET_VILLAGE_OF_THE_SPELLCASTERS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SECRET_VILLAGE_OF_THE_SPELLCASTERS);
}

APPEND_TEXT void EffectSECRET_VILLAGE_OF_THE_SPELLCASTERS(void)
{
  if (Duel_TryResolveSpellThroughTraps(SECRET_VILLAGE_OF_THE_SPELLCASTERS,
                                       SECRET_VILLAGE_OF_THE_SPELLCASTERS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
