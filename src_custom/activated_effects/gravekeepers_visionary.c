#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "gravekeepers_visionary.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
u8 GetDuelistForZone(struct DuelCard *zone);

#define VISIONARY_ATK_PER_GK 200

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u8 CountGkInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsGravekeeperMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsGravekeeperMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }
  return count;
}

u8 GravekeepersVisionary_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 me;
  u16 atk;

  if (zone == NULL || zone->id != GRAVEKEEPERS_VISIONARY)
    return FALSE;

  me = GetDuelistForZone(zone);
  if (me > DUEL_OPPONENT)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(CountGkInGy(me), VISIONARY_ATK_PER_GK, gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
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

  /* ATK overlay via GravekeepersVisionary_ApplyDynamicZoneStats.
   * destroy-replace needs destroy gate. Ceiling: OPT discard GK stand-in. */
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
