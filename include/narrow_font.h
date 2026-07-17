#ifndef GUARD_NARROW_FONT_H
#define GUARD_NARROW_FONT_H

#include "gba/types.h"

/* Emerald small_narrow VWF for card descriptions.
 * 5 text rows × 16px (2 tiles) × 14 cols = 140 tiles (same budget as vanilla desc). */

#define NARROW_DESC_COLS 14
#define NARROW_DESC_ROWS 5
#define NARROW_DESC_TILES (NARROW_DESC_COLS * NARROW_DESC_ROWS * 2)
#define NARROW_ROW_PX 112

u8 NarrowFontCharWidth(u8 c);
u8 NarrowFontMeasure(const u8 *text);
u8 NarrowFontWrapProse(const u8 *prose, u8 *out, u16 outCap,
                       const u8 *pageStarts[], u8 maxPages);
void NarrowFontRenderPage(u8 *destTiles, const u8 *pageText, u8 pageIndex,
                          u8 pageCount);
void NarrowFontApplyDescriptionTilemap(void);

#endif /* GUARD_NARROW_FONT_H */
