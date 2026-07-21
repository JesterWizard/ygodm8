#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"
#include "triangle_ecstasy_spark.h"

#define TRIANGLE_ECSTASY_SPARK_ATK 2700
#define TRIANGLE_ECSTASY_BOARD_CELLS 20

static u8 sTriangleEcstasyOppTrapLock APPEND_DATA = {FALSE};
static u8 sTriangleSistersBoostCells[TRIANGLE_ECSTASY_BOARD_CELLS] APPEND_DATA = {0};

static u8 IsHarpieLadySisters(u16 cardId)
{
  return cardId == HARPIE_LADY_SISTERS;
}

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + TRIANGLE_ECSTASY_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

static void MarkSistersExactAtk(struct DuelCard *zone)
{
  u16 cell;

  if (zone == NULL || !IsHarpieLadySisters(zone->id))
    return;

  cell = GetDuelBoardCellIndex(zone);
  if (cell < TRIANGLE_ECSTASY_BOARD_CELLS)
    sTriangleSistersBoostCells[cell] = TRUE;
}

static void BoostAllHarpieLadySisters(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++)
      MarkSistersExactAtk(gFixedZones[row][col]);
  }
}

void ApplyTriangleEcstasySparkAtkToCardInfo(const struct DuelCard *zone)
{
  u16 cell;

  if (zone == NULL || !IsHarpieLadySisters(zone->id))
    return;

  cell = GetDuelBoardCellIndex(zone);
  if (cell >= TRIANGLE_ECSTASY_BOARD_CELLS || !sTriangleSistersBoostCells[cell])
    return;

  gCardInfo.atk = TRIANGLE_ECSTASY_SPARK_ATK;
}

static void TRIANGLE_ECSTASY_SPARK_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  BoostAllHarpieLadySisters();

  Duel_ShowEffectText(TRIANGLE_ECSTASY_SPARK);
  Duel_RefreshMonsterStatOverlays();

  TriangleEcstasySpark_ArmOppTrapLock();
}

void TriangleEcstasySpark_ArmOppTrapLock(void)
{
  sTriangleEcstasyOppTrapLock = TRUE;
}

u8 TriangleEcstasySpark_BlocksOppTrap(void)
{
  return sTriangleEcstasyOppTrapLock;
}

void TriangleEcstasySpark_ClearOnTurnBoundary(void)
{
  u8 i;

  sTriangleEcstasyOppTrapLock = FALSE;
  for (i = 0; i < TRIANGLE_ECSTASY_BOARD_CELLS; i++)
    sTriangleSistersBoostCells[i] = FALSE;
}

APPEND_TEXT void EffectTRIANGLE_ECSTASY_SPARK(void)
{
  if (Duel_TryResolveSpellThroughTraps(TRIANGLE_ECSTASY_SPARK,
                                       TRIANGLE_ECSTASY_SPARK_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TRIANGLE_ECSTASY_SPARK_SelfCheck(void)
{
  if (!IsHarpieLadySisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (IsHarpieLadySisters(HARPIE_LADY))
    while (1)
      ;
}
#endif
