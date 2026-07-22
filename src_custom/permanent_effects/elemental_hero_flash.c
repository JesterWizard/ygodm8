#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_flash.h"
#include "graveyard_effects.h"

void MarkElementalHeroFlashBattleDestruction(u16 cardId)
{
  if (cardId == ELEMENTAL_HERO_FLASH)
    gElementalHeroFlashBattleDestroyPending = TRUE;
}

void ClearElementalHeroFlashBattleDestroyPending(void)
{
  gElementalHeroFlashBattleDestroyPending = FALSE;
}

unsigned char ShouldActivateElementalHeroFlash(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gElementalHeroFlashBattleDestroyPending)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != ELEMENTAL_HERO_FLASH)
    return FALSE;

  if (gActiveEffect.turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == ELEMENTAL_HERO_FLASH;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == ELEMENTAL_HERO_FLASH;
}

void ActivateElementalHeroFlash(void)
{
  u8 turnDuelist = (gActiveEffect.turnRow == 6) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  Duel_ShowEffectText(ELEMENTAL_HERO_FLASH);
  GetGraveCardAndClearGrave(turnDuelist);
  ClearElementalHeroFlashBattleDestroyPending();

  /* no banished-zone + no multi-card GY search yet — banish 3 E-Heroes
   * and add Normal Spell from GY deferred until banish + GY targeting exist.
   * Battle-destruction GY trigger wired above. */
}
