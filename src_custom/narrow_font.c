#include "global.h"
#include "configs/runtime.h"
#include "duel.h"
#include "narrow_font.h"

#include "generated/narrow_font_data.inc"

/* Tilemap: screen rows 10..19, cols 15..28, palette bank 15, base tile 148. */
#define NARROW_TILE_BASE 148
#define NARROW_TILEMAP_ATTR 0xF000
#define NARROW_TILEMAP_ROW0 10
#define NARROW_TILEMAP_COL0 15
#define NARROW_ARROW_GAP 1 /* px between text and page arrow */

/* Row 0 reserves up-arrow when pageIndex > 0; last row reserves down-arrow when
 * more pages follow (wrap always reserves last-row space so words never collide). */
static u8 RowTextBudget(u8 pageIndex, u8 row, u8 reserveDownArrow) {
  u8 budget = NARROW_ROW_PX;

  if (pageIndex > 0 && row == 0) {
    u8 take = (u8)(sNarrowArrowUpWidth + NARROW_ARROW_GAP);
    if (budget > take)
      budget = (u8)(budget - take);
  }
  if (reserveDownArrow && row == NARROW_DESC_ROWS - 1) {
    u8 take = (u8)(sNarrowArrowDownWidth + NARROW_ARROW_GAP);
    if (budget > take)
      budget = (u8)(budget - take);
  }
  return budget;
}

u8 NarrowFontCharWidth(u8 c) {
  if (c < 32 || c > 126)
    return 5;
  return sNarrowFontWidths[c - 32];
}

u8 NarrowFontMeasure(const u8 *text) {
  u8 w = 0;
  while (*text && *text != '^' && *text != '\n') {
    if (*text > 127) {
      text += 2;
      w = (u8)(w + 5);
      continue;
    }
    w = (u8)(w + NarrowFontCharWidth(*text++));
  }
  return w;
}

static void BlitGlyphColumn(u8 *destTiles, u8 row, u8 pixelX, const u8 *glyph4,
                            u8 width) {
  u8 x;
  u8 tileRowBase = (u8)(row * (NARROW_DESC_COLS * 2));

  for (x = 0; x < width && (u16)(pixelX + x) < NARROW_ROW_PX; x++) {
    u8 absX = (u8)(pixelX + x);
    u8 col = absX / 8;
    u8 srcX = x;
    u8 y;

    for (y = 0; y < 16; y++) {
      u8 tileQuad = (y < 8 ? 0 : 2) + (srcX < 8 ? 0 : 1);
      u8 srcPx = srcX & 7;
      u8 srcPy = y & 7;
      u8 srcByte = glyph4[tileQuad * 32 + srcPy * 4 + srcPx / 2];
      u8 val = (srcPx & 1) ? (srcByte >> 4) : (srcByte & 0xF);
      u8 dstTile;
      u8 *dst;
      u8 dstPx;
      u8 dstByteOff;
      u8 dstByte;

      if (!val)
        continue;

      dstTile = (u8)(tileRowBase + (y < 8 ? col : (u8)(col + NARROW_DESC_COLS)));
      dst = destTiles + dstTile * 32;
      dstPx = absX & 7;
      dstByteOff = (u8)((y & 7) * 4 + dstPx / 2);
      dstByte = dst[dstByteOff];
      if (dstPx & 1)
        dst[dstByteOff] = (u8)((dstByte & 0x0F) | (val << 4));
      else
        dst[dstByteOff] = (u8)((dstByte & 0xF0) | val);
    }
  }
}

static void BlitChar(u8 *destTiles, u8 row, u8 pixelX, u8 c) {
  const u8 *glyph;
  u8 width;

  if (c < 32 || c > 126) {
    glyph = sNarrowFontGlyphs['?' - 32];
    width = sNarrowFontWidths['?' - 32];
  } else {
    glyph = sNarrowFontGlyphs[c - 32];
    width = sNarrowFontWidths[c - 32];
  }
  BlitGlyphColumn(destTiles, row, pixelX, glyph, width);
}

u8 NarrowFontWrapProse(const u8 *prose, u8 *out, u16 outCap,
                       const u8 *pageStarts[], u8 maxPages) {
  u16 prosePos = 0;
  u16 outPos = 0;
  u8 pageCount = 0;

  while (prose[prosePos] == ' ')
    prosePos++;

  if (prose[prosePos] == '\0') {
    pageStarts[0] = out;
    out[0] = '^';
    out[1] = '\0';
    return 1;
  }

  while (prose[prosePos] != '\0' && pageCount < maxPages) {
    u8 row;

    pageStarts[pageCount] = &out[outPos];

    for (row = 0; row < NARROW_DESC_ROWS; row++) {
      u8 used = 0;
      /* Always reserve down-arrow on last row so a word never sits under it;
       * last page just leaves a few unused pixels (no arrow drawn). */
      u8 budget = RowTextBudget(pageCount, row, TRUE);

      while (prose[prosePos] == ' ')
        prosePos++;
      if (prose[prosePos] == '\0')
        break;

      while (prose[prosePos] != '\0' && prose[prosePos] != ' ') {
        u16 wlen = 0;
        u8 wordPx = 0;
        u8 need;
        u16 i;

        while (prose[prosePos + wlen] != '\0' && prose[prosePos + wlen] != ' ') {
          u8 ch = prose[prosePos + wlen];
          if (ch > 127) {
            wordPx = (u8)(wordPx + 5);
            wlen = (u16)(wlen + 2);
          } else {
            wordPx = (u8)(wordPx + NarrowFontCharWidth(ch));
            wlen++;
          }
        }

        need = used == 0 ? wordPx : (u8)(wordPx + NarrowFontCharWidth(' '));
        if (need > (u8)(budget - used)) {
          if (used == 0) {
            /* ponytail: hard-split overlong tokens by pixel budget. */
            while (wlen && used < budget) {
              u8 ch = prose[prosePos];
              u8 cw;
              if (ch > 127) {
                cw = 5;
                if (used + cw > budget)
                  break;
                if (outPos + 3 >= outCap)
                  goto done;
                out[outPos++] = ch;
                out[outPos++] = prose[prosePos + 1];
                prosePos = (u16)(prosePos + 2);
                used = (u8)(used + cw);
                wlen = (u16)(wlen - 2);
              } else {
                cw = NarrowFontCharWidth(ch);
                if (used + cw > budget)
                  break;
                if (outPos + 2 >= outCap)
                  goto done;
                out[outPos++] = ch;
                prosePos++;
                used = (u8)(used + cw);
                wlen--;
              }
            }
          }
          break;
        }

        if (outPos + wlen + 3 >= outCap)
          goto done;
        if (used > 0) {
          out[outPos++] = ' ';
          used = (u8)(used + NarrowFontCharWidth(' '));
        }
        for (i = 0; i < wlen; i++)
          out[outPos++] = prose[prosePos++];
        used = (u8)(used + wordPx);

        while (prose[prosePos] == ' ')
          prosePos++;
      }

      if (outPos + 2 >= outCap)
        goto done;
      out[outPos++] = '\n';
      if (prose[prosePos] == '\0')
        break;
    }

    if (outPos + 2 >= outCap)
      goto done;
    out[outPos++] = '^';
    pageCount++;
  }

done:
  if (pageCount == 0) {
    pageStarts[0] = out;
    out[0] = '^';
    out[1] = '\0';
    return 1;
  }
  out[outPos] = '\0';
  return pageCount;
}

void NarrowFontRenderPage(u8 *destTiles, const u8 *pageText, u8 pageIndex,
                          u8 pageCount) {
  u8 row = 0;
  u8 x = 0;
  u8 reserveDown = (u8)(pageIndex + 1 < pageCount);
  u8 budget = RowTextBudget(pageIndex, 0, reserveDown);
  const u8 *p = pageText;

  CpuFastFill16(0, destTiles, NARROW_DESC_TILES * 32);

  while (*p && *p != '^' && row < NARROW_DESC_ROWS) {
    if (*p == '\n') {
      row++;
      if (row >= NARROW_DESC_ROWS)
        break;
      x = 0;
      budget = RowTextBudget(pageIndex, row, reserveDown);
      p++;
      continue;
    }
    if (*p > 127) {
      u8 cw = NarrowFontCharWidth('?');
      if ((u16)x + cw > budget)
        break;
      BlitChar(destTiles, row, x, '?');
      x = (u8)(x + cw);
      p += 2;
      continue;
    }
    {
      u8 cw = NarrowFontCharWidth(*p);
      if ((u16)x + cw > budget)
        break;
      BlitChar(destTiles, row, x, *p);
      x = (u8)(x + cw);
      p++;
    }
  }

  if (pageIndex > 0)
    BlitGlyphColumn(destTiles, 0, (u8)(NARROW_ROW_PX - sNarrowArrowUpWidth),
                    sNarrowArrowUp, sNarrowArrowUpWidth);
  if (reserveDown)
    BlitGlyphColumn(destTiles, NARROW_DESC_ROWS - 1,
                    (u8)(NARROW_ROW_PX - sNarrowArrowDownWidth),
                    sNarrowArrowDown, sNarrowArrowDownWidth);
}

void NarrowFontApplyDescriptionTilemap(void) {
  u8 textRow;
  u8 col;
  u16 tile = NARROW_TILE_BASE;

  for (textRow = 0; textRow < NARROW_DESC_ROWS; textRow++) {
    u8 screenTop = (u8)(NARROW_TILEMAP_ROW0 + textRow * 2);
    for (col = 0; col < NARROW_DESC_COLS; col++) {
      gBgVram.sbb1E[screenTop][NARROW_TILEMAP_COL0 + col] =
          (u16)(NARROW_TILEMAP_ATTR | tile);
      tile++;
    }
    for (col = 0; col < NARROW_DESC_COLS; col++) {
      gBgVram.sbb1E[screenTop + 1][NARROW_TILEMAP_COL0 + col] =
          (u16)(NARROW_TILEMAP_ATTR | tile);
      tile++;
    }
  }
}
