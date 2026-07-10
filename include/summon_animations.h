#ifndef GUARD_SUMMON_ANIMATIONS_H
#define GUARD_SUMMON_ANIMATIONS_H

#include "global.h"

/* Phase 1 -- call BEFORE card placement.
 * Looks up the card's registered popup graphic; if found, records it and
 * returns TRUE. Performs no VRAM save so the post-placement draw is
 * captured correctly in phase 2.                                */
bool32 TryPlaySummonAnimation(u16 cardId);

/* Phase 2 -- call AFTER card placement + UpdateDuelGfx / MaybeUpdateGfx
 * has drawn the new card on screen.  Saves the live duel display (cbb5,
 * palette, DISPCNT, window + blend regs), plays the full-screen 8bpp BG0
 * popup over the dimmed-but-intact duel board, then restores the duel
 * display and resumes.                                            */
void FinishSummonAnimation(void);

#endif // GUARD_SUMMON_ANIMATIONS_H
