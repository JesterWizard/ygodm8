#ifndef GUARD_DUEL_VOICE_H
#define GUARD_DUEL_VOICE_H

#include "gba/types.h"

/* Show dialogue portrait (top-left) for the next duel textbox. PORTRAIT_NONE skips.
 * Always clears OAM 0-3 (cursor / leftover overworld portrait ghost at y=48).
 * hideBoardSprites: TRUE also hides mini-cards (VO VRAM clash); FALSE keeps them. */
void Duel_ShowPortraitForTextbox(u8 portraitId, u8 hideBoardSprites);
/* Re-place portrait OAM without reloading gfx (same speaker across textbox pages). */
void Duel_PlacePortraitForTextbox(u8 portraitId, u8 hideBoardSprites);

#endif // GUARD_DUEL_VOICE_H
