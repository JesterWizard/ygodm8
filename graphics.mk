CARD_ARTWORK_PNGS := $(wildcard graphics/cards/artwork/*.png)
CARD_ARTWORK_TILES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.8bpp,$(CARD_ARTWORK_PNGS))
CARD_ARTWORK_PALETTES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.gbapal,$(CARD_ARTWORK_PNGS))

CARD_TYPE_PNGS := $(wildcard graphics/cards/types/*.png)
CARD_TYPE_TILES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.4bpp,$(CARD_TYPE_PNGS))
CARD_TYPE_PALETTES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.gbapal,$(CARD_TYPE_PNGS))

CARD_ATTRIBUTE_PNGS := $(wildcard graphics/cards/attributes/*.png)
CARD_ATTRIBUTE_TILES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.4bpp,$(CARD_ATTRIBUTE_PNGS))
CARD_ATTRIBUTE_PALETTES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.gbapal,$(CARD_ATTRIBUTE_PNGS))

CUSTOM_CARD_512_PNGS := $(wildcard src_custom/assets/cards/512x512/*.png)
CUSTOM_CARD_80_PNGS := $(wildcard src_custom/assets/cards/80x80/*.png)
CUSTOM_CARD_24_PNGS := $(wildcard src_custom/assets/cards/24x24/*.png)
BATCH_80X80 := tools/batch_80x80.py

OVERWORLD_ENTITY_PNGS := $(wildcard src/overworld/entities/*.png)
OVERWORLD_ENTITY_TILES := $(patsubst src/overworld/entities/%.png,src/overworld/entities/%.4bpp,$(OVERWORLD_ENTITY_PNGS))

DEBUG_MENU_PNG := src_custom/assets/menus/debug_menu.png
DEBUG_MENU_4BPP := src_custom/assets/menus/debug_menu.4bpp
DEBUG_MENU_LZ := src_custom/assets/menus/debug_menu.lz
DEBUG_MENU_PAL := src_custom/assets/menus/debug_menu.gbapal

THOUGHT_BUBBLE_PNGS := $(shell find src_custom/assets/thought_bubbles -type f -name '*.png' | sort)
THOUGHT_BUBBLE_DUMPS := $(patsubst src_custom/assets/thought_bubbles/%.png,src_custom/assets/thought_bubbles/%.dmp,$(THOUGHT_BUBBLE_PNGS))
THOUGHT_BUBBLE_PALETTES := $(patsubst src_custom/assets/thought_bubbles/%.png,src_custom/assets/thought_bubbles/%.gbapal,$(THOUGHT_BUBBLE_PNGS))

CG_PNGS := $(shell find src_custom/assets/cgs -type f -name '*.png' 2>/dev/null | sort)
CG_BUILDS := $(patsubst src_custom/assets/cgs/%.png,build/cgs/%.lz,$(CG_PNGS))
CG_PALETTES := $(patsubst src_custom/assets/cgs/%.png,build/cgs/%.gbapal,$(CG_PNGS))
CG_BUILD_ARTIFACTS := $(CG_BUILDS) $(CG_PALETTES)

OPENING_SCREEN_PNGS := src_custom/assets/opening_screens/opening_screen_1.png \
                       src_custom/assets/opening_screens/opening_screen_2.png \
                       src_custom/assets/opening_screens/opening_screen_3.png
TITLE_SCREEN_PNGS := src_custom/assets/title_screens/title_screen.png
FIELD_SPELL_STEM_PNGS := $(wildcard src_custom/assets/field_spells/*.png)
FIELD_SPELL_DIR_PNGS := $(shell find src_custom/assets/field_spells -mindepth 2 -maxdepth 2 -type f -name 'field.png' 2>/dev/null | sort)
FIELD_SPELL_PNGS := $(sort $(FIELD_SPELL_STEM_PNGS) $(FIELD_SPELL_DIR_PNGS))
FIELD_SPELL_HUFFS := $(shell find src_custom/assets/field_spells -mindepth 2 -type f -name 'field.huff' 2>/dev/null | sort)
FIELD_SPELL_PALETTES := $(shell find src_custom/assets/field_spells -mindepth 2 -type f -name 'field.gbapal' 2>/dev/null | sort)

DUEL_ICON_PNG := src_custom/assets/icons/duel.png
DUEL_ICON_4BPP := src_custom/assets/icons/duel.4bpp
DUEL_ICON_PAL := src_custom/assets/icons/duel.gbapal

CURSOR_PNGS := $(wildcard src_custom/assets/cursors/*.png)
CURSOR_4BPP := $(CURSOR_PNGS:.png=.4bpp)
CURSOR_PAL := $(CURSOR_PNGS:.png=.gbapal)

src_custom/assets/menus/debug_menu.lz: src_custom/assets/menus/debug_menu.4bpp | tools-rules
	tools/gbagfx/gbagfx $< $@

graphics-rules: $(CARD_TYPE_TILES) \
                $(CARD_TYPE_PALETTES) \
                $(CARD_ATTRIBUTE_TILES) \
                $(CARD_ATTRIBUTE_PALETTES) \
                $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal \
                $(THOUGHT_BUBBLE_DUMPS) \
                $(THOUGHT_BUBBLE_PALETTES) \
                $(DEBUG_MENU_LZ) \
                $(DEBUG_MENU_PAL) \
                $(DUEL_ICON_4BPP) \
                $(DUEL_ICON_PAL) \
                $(CURSOR_4BPP) \
                $(CURSOR_PAL)

clean-graphics:
	rm -f graphics/cards/artwork/*.8bpp
	rm -f graphics/cards/attributes/*.4bpp
	rm -f graphics/cards/attributes/*.gbapal
	rm -f graphics/cards/types/*.4bpp
	rm -f graphics/cards/types/*.gbapal
	rm -rf build/cards/
	rm -f src_custom/assets/cards/80x80/*.8bpp
	rm -f src_custom/assets/cards/80x80/*.gbapal
	rm -f src_custom/assets/cards/80x80/*.huff
	rm -f src_custom/assets/cards/24x24/*.8bpp
	rm -f src_custom/assets/cards/24x24/*.lz
	find src_custom/assets/menus -type f \( -name '*.4bpp' -o -name '*.lz' -o -name '*.gbapal' \) -delete 2>/dev/null || true
	find src_custom/assets/thought_bubbles -type f \( -name '*.4bpp' -o -name '*.obj.4bpp' -o -name '*.dmp' -o -name '*.gbapal' -o -name '*.lz' \) -delete
	find src_custom/assets/field_spells -type f \( -name '*.4bpp' -o -name '*.8bpp' -o -name '*.gbapal' -o -name '*.huff' -o -name '*.tilemap.bin' -o -name 'field.tilemap.c' \) -delete 2>/dev/null || true
	rm -rf build/cgs/ build/opening_screens/ build/title_screens/ build/videos/
	find src_custom/assets/cgs -type f \( -name '*.lz' -o -name '*.gbapal' -o -name '*.8bpp' \) -delete 2>/dev/null || true
	find src_custom/assets/opening_screens -type f \( -name '*.8bpp' -o -name '*.lz' -o -name '*.gbapal' -o -name '*.tilemap.bin' \) -delete 2>/dev/null || true
	find src_custom/assets/title_screens -type f \( -name '*.8bpp' -o -name '*.lz' -o -name '*.gbapal' -o -name '*.tilemap.bin' \) -delete 2>/dev/null || true
	rm -f src/overworld/entities/*.4bpp
	rm -f src/overworld/entities/*.gbapal
	rm -f src_custom/assets/icons/*.4bpp
	rm -f src_custom/assets/icons/*.gbapal
	rm -f src_custom/assets/cursors/*.4bpp
	rm -f src_custom/assets/cursors/*.gbapal
	rm -rf src_custom/generated/maps/

%.4bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
%.8bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
# Cursor pals padded to 16 colors so MenuCursor_LoadPalette can always copy 32 bytes.
src_custom/assets/cursors/%.gbapal: src_custom/assets/cursors/%.png | tools-rules
	tools/gbagfx/gbagfx $< $@
	python3 -c "from pathlib import Path; p=Path('$@'); p.write_bytes(p.read_bytes().ljust(32, b'\0'))"
%.gbapal: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src_custom/assets/thought_bubbles/%.dmp: src_custom/assets/thought_bubbles/%.png tools/repack_128x64_obj.py | tools-rules
	tmp_tiles=$$(mktemp /tmp/thought_bubble_tiles.XXXXXX.4bpp); \
	tmp_obj=$$(mktemp /tmp/thought_bubble_obj.XXXXXX.4bpp); \
	tools/gbagfx/gbagfx $< $$tmp_tiles; \
	python3 tools/repack_128x64_obj.py $$tmp_tiles $$tmp_obj; \
	tools/gbagfx/gbagfx $$tmp_obj $(@:.dmp=.lz); \
	rm -f $$tmp_tiles $$tmp_obj; \
	mv $(@:.dmp=.lz) $@
