#include "global.h"
#include "common-chax.h"
#include "wave_motion_cannon.h"

extern const unsigned char g89A7ADE[][64];
extern const unsigned char g89A8A1E[];
extern u16 g8E116BC[];

u8 IsChargedWaveMotionCannon(const struct DuelCard *zone)
{
  return zone != NULL
      && zone->id == WAVE_MOTION_CANNON
      && zone->isFaceUp == TRUE
      && zone->isLocked == TRUE;
}

static void DrawWaveMotionCannonCounter(u8 *tileBase, const struct DuelCard *zone)
{
  u8 turns = zone->permStage;
  u8 tens;
  u8 ones;

  if (!IsChargedWaveMotionCannon(zone) || turns == 0)
    return;

  if (turns <= 3) {
    CpuCopy16(g89A7ADE[turns], tileBase, 64);
    return;
  }

  if (turns <= 9) {
    CpuCopy16(g89A8A1E + turns * 64, tileBase, 64);
    return;
  }

  if (turns > 99)
    turns = 99;

  tens = turns / 10;
  ones = turns % 10;
  CpuCopy16(g89A8A1E + tens * 64, tileBase, 64);
  CpuCopy16(g89A8A1E + ones * 64, tileBase + 0x40, 64);
}

void RefreshAllWaveMotionCannonFieldCounters(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    DrawWaveMotionCannonCounter(
        gBgVram.cbb0 + 0x10000 + g8E116BC[i] * 32,
        gFixedZones[OPPONENT_BACKROW][i]);
    DrawWaveMotionCannonCounter(
        gBgVram.cbb0 + 0x10000 + g8E116BC[i + 15] * 32,
        gFixedZones[PLAYER_BACKROW][i]);
  }
}

void sub_8057808(void);

void AgeWaveMotionCannonTurns(void)
{
  u8 i;
  u8 changed = FALSE;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];
    if (IsChargedWaveMotionCannon(zone)) {
      IncrementPermStage(zone);
      changed = TRUE;
    }
  }

  if (changed) {
    RefreshAllWaveMotionCannonFieldCounters();
    sub_8057808();
  }
}
