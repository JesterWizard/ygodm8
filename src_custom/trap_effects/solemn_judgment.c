#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

APPEND_TEXT void EffectSOLEMN_JUDGMENT(void)
{
  u8 fixedCtrl;
  u16 lp;
  s32 pay;

  Duel_ShowTrapResponseText(SOLEMN_JUDGMENT, gTrapEffectData.originCardId);

  fixedCtrl =
      (gTurnDuelistBattleState[INACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  lp = gDuelLifePoints[fixedCtrl];
  pay = (s32)(lp / 2);
  if (pay > 0)
    Duel_ChangeLp(INACTIVE_DUELIST, -pay, FALSE);

  /* Destroy the summon/activation origin if present. */
  {
    struct DuelCard *origin =
        gTurnZones[gTrapEffectData.originRow][gTrapEffectData.originCol];

    if (origin != NULL && origin->id != CARD_NONE)
      Duel_DestroyZone(origin, ACTIVE_DUELIST, FALSE);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

}
