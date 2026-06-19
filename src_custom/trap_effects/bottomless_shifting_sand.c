#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card_passives.h"
#include "duel_helpers.h"
#include "bottomless_shifting_sand.h"

void UpdateDuelGfxExceptField(void);

/* ponytail: GBA hand cap is 5; TCG rule uses 4 — scale self-destruct threshold down */
#define BOTTOMLESS_SHIFTING_SAND_HAND_LIMIT 3

static u8 IsEligibleFaceUpMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (zone->isFaceUp == FALSE)
    return FALSE;
  if (IsGodCard(zone->id) == TRUE || IsImmuneToControlSwitch(zone->id) == TRUE)
    return FALSE;

  return TRUE;
}

static struct DuelCard *FindBottomlessShiftingSandOnActiveBackrow(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone != NULL && zone->id == BOTTOMLESS_SHIFTING_SAND)
      return zone;
  }

  return NULL;
}

static u16 FindHighestFaceUpMonsterAtk(void)
{
  u8 row;
  u8 col;
  u16 highestAtk = 0;
  u8 found = FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];
      u16 atk;

      if (!IsEligibleFaceUpMonster(zone))
        continue;

      atk = Duel_GetZoneFinalAtk(zone);
      if (!found || atk > highestAtk) {
        highestAtk = atk;
        found = TRUE;
      }
    }
  }

  return found ? highestAtk : 0;
}

static void DestroyFaceUpMonstersWithAtk(u16 targetAtk)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    u8 graveyardDuelist = (row == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (!IsEligibleFaceUpMonster(zone))
        continue;
      if (Duel_GetZoneFinalAtk(zone) != targetAtk)
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, destroyed) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed)
    UpdateDuelGfxExceptField();
}

void MarkBottomlessShiftingSandJustSet(struct DuelCard *zone)
{
  if (zone != NULL && zone->id == BOTTOMLESS_SHIFTING_SAND)
    zone->unk4 = 1;
}

void AgeBottomlessShiftingSandSetFlags(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (zone->id == BOTTOMLESS_SHIFTING_SAND && zone->unk4 != 0)
      zone->unk4 = 0;
  }
}

void TryBottomlessShiftingSandTurnStart(void)
{
  struct DuelCard *zone = FindBottomlessShiftingSandOnActiveBackrow();
  u16 highestAtk;

  if (zone == NULL || IsDuelOver() == TRUE)
    return;

  if (zone->unk4 != 0)
    return;

  if (!zone->isFaceUp) {
    Duel_ActivateContinuousZone(zone);
    if (IsDuelOver() == TRUE)
      return;
  }

  Duel_ShowEffectText(BOTTOMLESS_SHIFTING_SAND);
  if (IsDuelOver() == TRUE)
    return;

  highestAtk = FindHighestFaceUpMonsterAtk();
  if (highestAtk != 0)
    DestroyFaceUpMonstersWithAtk(highestAtk);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) <= BOTTOMLESS_SHIFTING_SAND_HAND_LIMIT) {
    Duel_ShowEffectTextTyped(BOTTOMLESS_SHIFTING_SAND, 9);
    if (IsDuelOver() == TRUE)
      return;

    Duel_DestroyZone(zone, ACTIVE_DUELIST, TRUE);
  }
}

APPEND_TEXT void EffectBottomlessShiftingSand(void)
{
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BottomlessShiftingSand_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = BOTTOMLESS_SHIFTING_SAND;
  zone.unk4 = 1;
  MarkBottomlessShiftingSandJustSet(&zone);
  if (zone.unk4 != 1)
    __builtin_trap();
}
#endif
