#include "global.h"
#include "common-chax.h"
#include "aromalilith_magnolia.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define MAGNOLIA_LP_COST 2000

static u8 ControllerHasFaceUpMagnoliaWithLpAdvantage(u8 controller)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row;
  u8 col;

  if (gDuelLifePoints[controller] <= gDuelLifePoints[opp])
    return FALSE;

  row = Duel_FixedMonsterRowForDuelist(controller);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMALILITH_MAGNOLIA)
      return TRUE;
  }

  return FALSE;
}

u8 AromalilithMagnolia_PreventsDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || !zone->isFaceUp || !Duel_CardHasMonsterType(zone->id, TYPE_PLANT))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return ControllerHasFaceUpMagnoliaWithLpAdvantage(controller);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAromaWindsTrap(u16 cardId)
{
  return cardId == HUMID_WINDS || cardId == DRIED_WINDS || cardId == BLESSED_WINDS;
}

static u8 CountOwnWindsTraps(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone != NULL && IsAromaWindsTrap(zone->id))
      count++;
  }

  return count;
}

static u8 FieldHasBanishTarget(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      return TRUE;
    }
  }

  return FALSE;
}

static void BanishUpToNFieldCards(struct DuelCard *self, u8 maxCount)
{
  u8 row;
  u8 col;
  u8 banished = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW && banished < maxCount; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW && banished < maxCount; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      banished++;
    }
  }

  if (banished > 0) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

unsigned char CanActivateAROMALILITH_MAGNOLIA(void)
{
  struct DuelCard *zone;
  u8 winds;

  if (gMonEffect.id != AROMALILITH_MAGNOLIA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMALILITH_MAGNOLIA)
    return FALSE;

  /* LP-higher Plant effect-destroy immunity via AromalilithMagnolia_PreventsDestroy.
   * ponytail: LP-gain ATK need LP hook. Ceiling: OPT pay 2000 → banish up to
   * Humid/Dried/Blessed Winds count. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gDuelLifePoints[FixedDuelistForActive()] < MAGNOLIA_LP_COST)
    return FALSE;

  winds = CountOwnWindsTraps();
  if (winds == 0)
    return FALSE;

  return FieldHasBanishTarget(zone);
}

void ActivateAROMALILITH_MAGNOLIAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 winds;

  Duel_ShowEffectTextTyped(AROMALILITH_MAGNOLIA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  winds = CountOwnWindsTraps();
  if (winds == 0)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MAGNOLIA_LP_COST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: no multi-select UI — auto-banish up to winds count (opp rows first). */
  BanishUpToNFieldCards(self, winds);

  MarkMonsterEffectUsed(self);
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
