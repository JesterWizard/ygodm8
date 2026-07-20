#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static void DestroyAllOpponentCards(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE)
        continue;

      if (IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

static u8 OpponentControlsCard(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateBEAST_KING_BARBAROS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BEAST_KING_BARBAROS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BEAST_KING_BARBAROS)
    return FALSE;

  /* ponytail: no-tribute 1900 ATK + tribute-3 summon gate need summon hooks.
   * Ceiling: once via usage destroy all opp cards (tribute-3 stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OpponentControlsCard();
}

void ActivateBEAST_KING_BARBAROSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(BEAST_KING_BARBAROS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!OpponentControlsCard())
    return;

  DestroyAllOpponentCards();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
