#include "src_custom/generated/maps/tileset_graveyard.inc"
#include "src_custom/generated/maps/ground_tilemap_graveyard.inc"
#include "src_custom/generated/maps/palette_graveyard.inc"
#include "src_custom/generated/maps/collision_graveyard.inc"
// Custom map pointer tables (1 maps)
static const u8* const sCustomTilesets[] __attribute__((section(".append_rodata"), aligned(4))) = {
  sCustomTileset_graveyard,
};
static const u16* const sCustomGroundTilemaps[]__attribute__((section(".append_rodata"), aligned(4))) = {
  sCustomGroundTilemap_graveyard,
};
static const u16* const sCustomRoofTilemaps[]__attribute__((section(".append_rodata"), aligned(4))) = {
  NULL,
};
static const u16* const sCustomPalettes[]__attribute__((section(".append_rodata"), aligned(4))) = {
  sCustomPalette_graveyard,
};
static const u16* const sCustomCollisions[]__attribute__((section(".append_rodata"), aligned(4))) = {
  sCustomCollision_graveyard,
};
static const u8 sCustomTileTypes[]__attribute__((section(".append_rodata"), aligned(4))) = {
  0,
};
