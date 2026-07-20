#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static u8 FixedDuelistYouControl(void)
{
  return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static struct DuelCard *FindFaceUpUmiYouControl(void)
{
  return Duel_FindBackrowCard(FixedDuelistYouControl(), UMI, TRUE);
}

static struct DuelCard *FindFaceUpLegendaryOceanYouControl(void)
{
  return Duel_FindBackrowCard(FixedDuelistYouControl(), A_LEGENDARY_OCEAN, TRUE);
}

static u8 FixedRowForZone(struct DuelCard *zone, u8 *fixedRow)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void ResetFieldToArenaAfterUmiCost(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);

  Duel_CheckRivalryOfWarlordsAfterFieldChange();
  Duel_CheckLevelLimitAreaBAfterFieldChange();
  Duel_CheckLevelLimitAreaAAfterFieldChange();
  Duel_CheckAmazonessTigerAfterFieldChange();
}

static u8 CanPayNeoDaedalusCost(void)
{
  if (FindFaceUpUmiYouControl() != NULL)
    return TRUE;

  if (FindFaceUpLegendaryOceanYouControl() != NULL)
    return TRUE;

  return gDuel.field == FIELD_UMI;
}

static u8 PayNeoDaedalusCost(void)
{
  struct DuelCard *costZone = FindFaceUpUmiYouControl();
  u8 fixedRow;
  u8 wasUmiField = gDuel.field == FIELD_UMI;

  if (costZone == NULL)
    costZone = FindFaceUpLegendaryOceanYouControl();

  if (costZone != NULL) {
    if (!FixedRowForZone(costZone, &fixedRow))
      return FALSE;

    if (Duel_DestroyZone(costZone, TurnDuelistForFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    if (wasUmiField || costZone->id == UMI)
      ResetFieldToArenaAfterUmiCost();

    return TRUE;
  }

  if (wasUmiField) {
    ResetFieldToArenaAfterUmiCost();
    return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindLeviaDragonDaedalusYouControl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == LEVIA_DRAGON_DAEDALUS)
      return zone;
  }

  return NULL;
}

static void DestroyAllOtherCardsExceptSelf(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;

  if (Duel_DestroyAllHandCards(ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_DestroyAllHandCards(INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  for (row = 0; row < 4; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateOCEAN_DRAGON_LORD_NEO_DAEDALUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != OCEAN_DRAGON_LORD_NEO_DAEDALUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != OCEAN_DRAGON_LORD_NEO_DAEDALUS)
    return FALSE;

  if (!CanPayNeoDaedalusCost())
    return FALSE;

  return CanUseMonsterEffect(zone);
}

void ActivateOCEAN_DRAGON_LORD_NEO_DAEDALUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(OCEAN_DRAGON_LORD_NEO_DAEDALUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!PayNeoDaedalusCost())
    return;

  if (IsDuelOver() == TRUE)
    return;

  DestroyAllOtherCardsExceptSelf(self);

  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonOceanDragonLordNeoDaedalusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != OCEAN_DRAGON_LORD_NEO_DAEDALUS)
    return FALSE;

  if (FindLeviaDragonDaedalusYouControl() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonOceanDragonLordNeoDaedalusFromHand(u8 handZone)
{
  struct DuelCard *tribute = FindLeviaDragonDaedalusYouControl();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonOceanDragonLordNeoDaedalusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(OCEAN_DRAGON_LORD_NEO_DAEDALUS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (tribute != NULL)
    ClearZone(tribute);

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}
