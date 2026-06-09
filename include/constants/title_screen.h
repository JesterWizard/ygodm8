#ifndef GUARD_TITLE_SCREEN_H
#define GUARD_TITLE_SCREEN_H

#define TITLE_SCREEN_TILE_BYTES 0x9600
#define TITLE_SCREEN_PALETTE_BYTES 512
#define TITLE_SCREEN_MAP_WIDTH 30
#define TITLE_SCREEN_MAP_HEIGHT 20

/*
 * Thumb entry points in vanilla title_screen.o (base 0x0803525C).
 * Used by hooks without exporting static vanilla symbols.
 */
#define TITLE_SCREEN_TEXT_BASE               0x0803525C
#define TITLE_SCREEN_CopySpriteTilesAndPalette (TITLE_SCREEN_TEXT_BASE + 0x6FC)
#define TITLE_SCREEN_sub_80357C0             (TITLE_SCREEN_TEXT_BASE + 0x564)
#define TITLE_SCREEN_VBlankCbInitGfxRegs     (TITLE_SCREEN_TEXT_BASE + 0x7B4)
#define TITLE_SCREEN_sub_80357F8             (TITLE_SCREEN_TEXT_BASE + 0x59C)
#define TITLE_SCREEN_VBlankCbTryStartNewGame (TITLE_SCREEN_TEXT_BASE + 0x888)
#define TITLE_SCREEN_VBlankCbTryStartNewGameEnd (TITLE_SCREEN_TEXT_BASE + 0x8AC)

#endif
