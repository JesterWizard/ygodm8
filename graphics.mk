CARD_ARTWORK_PNGS := $(wildcard graphics/cards/artwork/*.png)
CARD_ARTWORK_TILES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.8bpp,$(CARD_ARTWORK_PNGS))
CARD_ARTWORK_PALETTES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.gbapal,$(CARD_ARTWORK_PNGS))

CARD_TYPE_PNGS := $(wildcard graphics/cards/types/*.png)
CARD_TYPE_TILES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.4bpp,$(CARD_TYPE_PNGS))
CARD_TYPE_PALETTES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.gbapal,$(CARD_TYPE_PNGS))

CARD_ATTRIBUTE_PNGS := $(wildcard graphics/cards/attributes/*.png)
CARD_ATTRIBUTE_TILES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.4bpp,$(CARD_ATTRIBUTE_PNGS))
CARD_ATTRIBUTE_PALETTES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.gbapal,$(CARD_ATTRIBUTE_PNGS))

CUSTOM_CARD_80_PNGS := $(wildcard src_custom/assets/cards/80x80/*.png)
CUSTOM_CARD_80_8BPP := $(patsubst src_custom/assets/cards/80x80/%.png,src_custom/assets/cards/80x80/%.8bpp,$(CUSTOM_CARD_80_PNGS))
CUSTOM_CARD_80_PALETTES := $(patsubst src_custom/assets/cards/80x80/%.png,src_custom/assets/cards/80x80/%.gbapal,$(CUSTOM_CARD_80_PNGS))
CUSTOM_CARD_80_HUFFS := $(patsubst src_custom/assets/cards/80x80/%.png,src_custom/assets/cards/80x80/%.huff,$(CUSTOM_CARD_80_PNGS))

CUSTOM_CARD_24_PNGS := $(wildcard src_custom/assets/cards/24x24/*.png)
CUSTOM_CARD_24_4BPPS := $(patsubst src_custom/assets/cards/24x24/%.png,src_custom/assets/cards/24x24/%.4bpp,$(CUSTOM_CARD_24_PNGS))
CUSTOM_CARD_24_LZS := $(patsubst src_custom/assets/cards/24x24/%.png,src_custom/assets/cards/24x24/%.lz,$(CUSTOM_CARD_24_PNGS))

OVERWORLD_ENTITY_PNGS := $(wildcard src/overworld/entities/*.png)
OVERWORLD_ENTITY_TILES := $(patsubst src/overworld/entities/%.png,src/overworld/entities/%.4bpp,$(OVERWORLD_ENTITY_PNGS))

THOUGHT_BUBBLE_PNGS := $(shell find src_custom/assets/thought_bubbles -type f -name '*.png' | sort)
THOUGHT_BUBBLE_DUMPS := $(patsubst src_custom/assets/thought_bubbles/%.png,src_custom/assets/thought_bubbles/%.dmp,$(THOUGHT_BUBBLE_PNGS))
THOUGHT_BUBBLE_PALETTES := $(patsubst src_custom/assets/thought_bubbles/%.png,src_custom/assets/thought_bubbles/%.gbapal,$(THOUGHT_BUBBLE_PNGS))

graphics-rules: $(CARD_TYPE_TILES) \
                $(CARD_TYPE_PALETTES) \
                $(CARD_ATTRIBUTE_TILES) \
                $(CARD_ATTRIBUTE_PALETTES) \
                $(CUSTOM_CARD_80_8BPP) \
                $(CUSTOM_CARD_80_PALETTES) \
                $(CUSTOM_CARD_80_HUFFS) \
                $(CUSTOM_CARD_24_4BPPS) \
                $(CUSTOM_CARD_24_LZS) \
                $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal \
                $(THOUGHT_BUBBLE_DUMPS) \
                $(THOUGHT_BUBBLE_PALETTES)

clean-graphics:
	rm -f graphics/cards/artwork/*.8bpp
	rm -f graphics/cards/attributes/*.4bpp
	rm -f graphics/cards/attributes/*.gbapal
	rm -f graphics/cards/types/*.4bpp
	rm -f graphics/cards/types/*.gbapal
	rm -f src_custom/assets/cards/80x80/*.gbapal
	rm -f src_custom/assets/cards/80x80/*.8bpp
	rm -f src_custom/assets/cards/80x80/*.huff
	rm -f src_custom/assets/cards/24x24/*.4bpp
	rm -f src_custom/assets/cards/24x24/*.lz
	find src_custom/assets/thought_bubbles -type f \( -name '*.4bpp' -o -name '*.obj.4bpp' -o -name '*.dmp' -o -name '*.gbapal' -o -name '*.lz' \) -delete
	rm -f src/overworld/entities/*.4bpp
	rm -f src/overworld/entities/*.gbapal

%.4bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
%.8bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
%.gbapal: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src_custom/assets/cards/80x80/%.8bpp: src_custom/assets/cards/80x80/%.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src_custom/assets/cards/80x80/%.huff: src_custom/assets/cards/80x80/%.8bpp | tools-rules
	tools/gbagfx/gbagfx $< $@ -depth 8 -ygodm
src_custom/assets/cards/24x24/%.4bpp: src_custom/assets/cards/24x24/%.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src_custom/assets/cards/24x24/%.lz: src_custom/assets/cards/24x24/%.4bpp | tools-rules
	tools/gbagfx/gbagfx $< $@
src_custom/assets/thought_bubbles/%.dmp: src_custom/assets/thought_bubbles/%.png tools/repack_128x64_obj.py | tools-rules
	tmp_tiles=$$(mktemp /tmp/thought_bubble_tiles.XXXXXX.4bpp); \
	tmp_obj=$$(mktemp /tmp/thought_bubble_obj.XXXXXX.4bpp); \
	tools/gbagfx/gbagfx $< $$tmp_tiles; \
	python3 tools/repack_128x64_obj.py $$tmp_tiles $$tmp_obj; \
	tools/gbagfx/gbagfx $$tmp_obj $(@:.dmp=.lz); \
	rm -f $$tmp_tiles $$tmp_obj; \
	mv $(@:.dmp=.lz) $@
