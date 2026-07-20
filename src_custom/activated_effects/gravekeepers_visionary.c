#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 HandHasGravekeeperMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsGravekeeperMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHandGravekeeperMonster(u16 cardId)
{
  return IsGravekeeperMonster(cardId);
}

unsigned char CanActivateGRAVEKEEPERS_VISIONARY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_VISIONARY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_VISIONARY)
    return FALSE;

  /* ponytail: +200 ATK per GK in GY + destroy-replace need stat/destroy hooks.
   * Ceiling: OPT discard 1 GK monster from hand once via usage (save stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasGravekeeperMonster();
}

void ActivateGRAVEKEEPERS_VISIONARYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_VISIONARY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsHandGravekeeperMonster, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
