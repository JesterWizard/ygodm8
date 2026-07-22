#include "global.h"
#include "common-chax.h"
#include "beast_king_barbaros.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "summon_tribute.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define BEAST_KING_BARBAROS_NO_TRIBUTE_ATK 1900

u8 BeastKingBarbaros_CanNormalSummonWithoutTribute(u16 cardId)
{
  return cardId == BEAST_KING_BARBAROS;
}

u8 BeastKingBarbaros_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BEAST_KING_BARBAROS)
    return FALSE;

  if (zone->permStage != 1)
    return FALSE;

  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, BEAST_KING_BARBAROS_NO_TRIBUTE_ATK, gCardInfo.def);
  return TRUE;
}

void TryBeastKingBarbarosOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BEAST_KING_BARBAROS)
    return;

  if (GetPendingSummonTributeCount() == 0)
    zone->permStage = 1;
}

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

void TryBeastKingBarbarosOnTributeSummonDestroy(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BEAST_KING_BARBAROS)
    return;

  if (GetPendingSummonTributeCount() < 3)
    return;

  if (!OpponentControlsCard())
    return;

  Duel_ShowEffectTextTyped(BEAST_KING_BARBAROS, 2);
  DestroyAllOpponentCards();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateBEAST_KING_BARBAROS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BEAST_KING_BARBAROS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BEAST_KING_BARBAROS)
    return FALSE;

  /* No-tribute 1900 ATK via BeastKingBarbaros_ApplyDynamicZoneStats + tribute hook.
   * OPT stand-in for 3-Tribute destroy. */
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

#if defined(DUEL_HELPERS_SELF_CHECK)
void BeastKingBarbaros_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = BEAST_KING_BARBAROS;
  zone.permStage = 1;
  if (!BeastKingBarbaros_ApplyDynamicZoneStats(&zone))
    while (1)
      ;
  if (gCardInfo.atk != BEAST_KING_BARBAROS_NO_TRIBUTE_ATK)
    while (1)
      ;
}
#endif
