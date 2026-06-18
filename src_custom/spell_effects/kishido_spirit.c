#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "kishido_spirit.h"
#include "spell_effects.h"

u8 IsActivatedKishidoSpiritZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == KISHIDO_SPIRIT && zone->isFaceUp == TRUE;
}

u8 IsKishidoSpiritActiveForDuelist(u8 duelist)
{
  u8 backrow = (duelist == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 i;

  if (IsImperialOrderNegatingSpell(KISHIDO_SPIRIT))
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsActivatedKishidoSpiritZone(gFixedZones[backrow][i]))
      return TRUE;
  }

  return FALSE;
}

APPEND_TEXT void EffectKishidoSpirit(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(KISHIDO_SPIRIT);
}
