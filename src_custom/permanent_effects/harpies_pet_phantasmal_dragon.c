#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpies_pet_phantasmal_dragon.h"
#include "xyz_duel.h"

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 PhantasmalHasMaterial(u8 fixedDuelist, u8 col)
{
  return XyzOverlays_GetCount(fixedDuelist, col) > 0;
}

static u8 FindFaceUpPhantasmalWithMaterial(u8 controller, u8 *outCol)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id != HARPIES_PET_PHANTASMAL_DRAGON)
      continue;
    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;
    if (!PhantasmalHasMaterial(controller, col))
      continue;

    if (outCol != NULL)
      *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 IsHarpieMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

u8 HarpiesPetPhantasmalDragon_CanAttackDirectly(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 controller;

  if (zone == NULL || zone->id != HARPIES_PET_PHANTASMAL_DRAGON)
    return FALSE;

  /* Attack-position summons often keep isFaceUp=0 until EOT flip. */
  if (!IsCardFaceUp((struct DuelCard *)zone) && zone->isDefending)
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return FALSE;

  controller = Duel_FixedDuelistForMonsterRow(fixedRow);
  return PhantasmalHasMaterial(controller, col);
}

/* Opponent cannot attack Harpie monsters while you control Phantasmal with material. */
u8 HarpiesPetPhantasmalDragon_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 defender;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;
  if (!IsHarpieMonsterId(zone->id))
    return TRUE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return TRUE;

  defender = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (!FindFaceUpPhantasmalWithMaterial(defender, NULL))
    return TRUE;

  return FALSE;
}

u8 HarpiesPetPhantasmalDragon_IsTargetImmune(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 defender;
  u8 activeFixed;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (!IsHarpieMonsterId(zone->id))
    return FALSE;
  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  defender = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (!FindFaceUpPhantasmalWithMaterial(defender, NULL))
    return FALSE;

  activeFixed = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
                    ? DUEL_PLAYER
                    : DUEL_OPPONENT;
  if (activeFixed == defender)
    return FALSE;

  return TRUE;
}

void TryApplyHarpiesPetPhantasmalDragonEndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  if (!FindFaceUpPhantasmalWithMaterial(fixed, &col))
    return;

  Duel_ShowEffectTextTyped(HARPIES_PET_PHANTASMAL_DRAGON, 2);
  XyzOverlays_DetachToGraveyard(fixed, col, turn);
}

unsigned char ShouldActivateHARPIES_PET_PHANTASMAL_DRAGON(void)
{
  (void)gActiveEffect;
  return FALSE;
}

void ActivateHARPIES_PET_PHANTASMAL_DRAGON(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HarpiesPetPhantasmalDragon_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = HARPIES_PET_PHANTASMAL_DRAGON;
  zone.isFaceUp = TRUE;
  zone.isDefending = FALSE;
  if (HarpiesPetPhantasmalDragon_CanAttackDirectly(&zone) == TRUE)
    __builtin_trap(); /* no materials → cannot apply */
}
#endif
