#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 IsFishSeaAquaLv4OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.level == 0 || gCardInfo.level > 4)
    return FALSE;

  return gCardInfo.type == TYPE_FISH
      || gCardInfo.type == TYPE_SEA_SERPENT
      || gCardInfo.type == TYPE_AQUA;
}

static void ActivateFORGOTTEN_TEMPLE_OF_THE_DEEPZone(struct DuelCard *zone)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *target = NULL;

  if (Duel_ActivateContinuousTrapPreamble(zone, FORGOTTEN_TEMPLE_OF_THE_DEEP)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: name-becomes-Umi + End Phase return need field-name/turn hooks.
   * Ceiling: once on activate, banish one Lv4- Fish/SS/Aqua you control. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && IsFishSeaAquaLv4OrLower(m->id)) {
      target = m;
      break;
    }
  }

  if (target != NULL)
    Duel_BanishZone(target, FALSE);
}

void TryActivateFORGOTTEN_TEMPLE_OF_THE_DEEPOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(FORGOTTEN_TEMPLE_OF_THE_DEEP,
                                         ActivateFORGOTTEN_TEMPLE_OF_THE_DEEPZone);
}

/* ponytail: TryActivateFORGOTTEN_TEMPLE_OF_THE_DEEPOnOpponentTurnStart must be
 * called from turn_effect_hooks. Ceiling: body ready, not wired. */
