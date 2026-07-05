#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "zeriel.h"

extern void UpdateDuelGfxExceptField(void);

#define ZERIEL_FAIRY_ATK_BOOST 500

static u8 IsActiveFaceUpZeriel(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ZERIEL)
    return FALSE;

  if (IsCardFaceUp((struct DuelCard *)zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 RowHasActiveZeriel(u8 fixedMonsterRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsActiveFaceUpZeriel(gFixedZones[fixedMonsterRow][col]))
      return TRUE;
  }

  return FALSE;
}

void ApplyZerielFairyAtkBoost(const struct DuelCard *zone)
{
  u8 row;
  u8 col;
  u32 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  /* ponytail: GetTypeGroup/SetCardInfo would clobber gCardInfo.atk already computed. */
  if (gCardInfo.id != zone->id || gCardInfo.type >= TYPE_SPELL)
    return;

  if (gCardInfo.type != TYPE_FAIRY)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    u8 zoneOnRow = FALSE;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone)
        zoneOnRow = TRUE;
    }

    if (!zoneOnRow || !RowHasActiveZeriel(row))
      continue;

    atk = (u32)gCardInfo.atk + ZERIEL_FAIRY_ATK_BOOST;
    gCardInfo.atk = Duel_ClampStat(atk);
    return;
  }
}

void Zeriel_OnZoneCleared(const struct DuelCard *zone)
{
  if (zone != NULL && zone->id == ZERIEL)
    UpdateDuelGfxExceptField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Zeriel_SelfCheck(void)
{
  if (ZERIEL_FAIRY_ATK_BOOST != 500)
    while (1)
      ;
}
#endif
