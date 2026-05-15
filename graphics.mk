CARD_ARTWORK_PNGS := $(wildcard graphics/cards/artwork/*.png)
CARD_ARTWORK_TILES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.8bpp,$(CARD_ARTWORK_PNGS))
CARD_ARTWORK_PALETTES := $(patsubst graphics/cards/artwork/%.png,graphics/cards/artwork/%.gbapal,$(CARD_ARTWORK_PNGS))

CARD_TYPE_PNGS := $(wildcard graphics/cards/types/*.png)
CARD_TYPE_TILES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.4bpp,$(CARD_TYPE_PNGS))
CARD_TYPE_PALETTES := $(patsubst graphics/cards/types/%.png,graphics/cards/types/%.gbapal,$(CARD_TYPE_PNGS))

CARD_ATTRIBUTE_PNGS := $(wildcard graphics/cards/attributes/*.png)
CARD_ATTRIBUTE_TILES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.4bpp,$(CARD_ATTRIBUTE_PNGS))
CARD_ATTRIBUTE_PALETTES := $(patsubst graphics/cards/attributes/%.png,graphics/cards/attributes/%.gbapal,$(CARD_ATTRIBUTE_PNGS))

CUSTOM_CARD_80_PNGS := $(wildcard src/hooks/assets/cards/80x80/*_80x80.png)
CUSTOM_CARD_80_8BPP := $(patsubst src/hooks/assets/cards/80x80/%.png,src/hooks/assets/cards/80x80/%.8bpp,$(CUSTOM_CARD_80_PNGS))
CUSTOM_CARD_80_PALETTES := $(patsubst src/hooks/assets/cards/80x80/%.png,src/hooks/assets/cards/80x80/%.gbapal,$(CUSTOM_CARD_80_PNGS))
CUSTOM_CARD_80_HUFFS := $(patsubst src/hooks/assets/cards/80x80/%.png,src/hooks/assets/cards/80x80/%.huff,$(CUSTOM_CARD_80_PNGS))

CUSTOM_CARD_24_PNGS := $(wildcard src/hooks/assets/cards/24x24/*_24x24.png)
CUSTOM_CARD_24_LZS := $(patsubst src/hooks/assets/cards/24x24/%.png,src/hooks/assets/cards/24x24/%.lz,$(CUSTOM_CARD_24_PNGS))

OVERWORLD_ENTITY_PNGS := $(wildcard src/overworld/entities/*.png)
OVERWORLD_ENTITY_TILES := $(patsubst src/overworld/entities/%.png,src/overworld/entities/%.4bpp,$(OVERWORLD_ENTITY_PNGS))

graphics-rules: $(CARD_TYPE_TILES) \
                $(CARD_TYPE_PALETTES) \
                $(CARD_ATTRIBUTE_TILES) \
                $(CARD_ATTRIBUTE_PALETTES) \
                $(CUSTOM_CARD_80_8BPP) \
                $(CUSTOM_CARD_80_PALETTES) \
                $(CUSTOM_CARD_80_HUFFS) \
                $(CUSTOM_CARD_24_LZS) \
                $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal

clean-graphics:
	rm -f graphics/cards/artwork/*.8bpp
	rm -f graphics/cards/attributes/*.4bpp
	rm -f graphics/cards/attributes/*.gbapal
	rm -f graphics/cards/types/*.4bpp
	rm -f graphics/cards/types/*.gbapal
	rm -f src/hooks/assets/cards/80x80/*.gbapal
	rm -f src/hooks/assets/cards/80x80/*.8bpp
	rm -f src/hooks/assets/cards/80x80/*.huff
	rm -f src/hooks/assets/cards/24x24/*.lz
	rm -f src/overworld/entities/*.4bpp
	rm -f src/overworld/entities/*.gbapal

%.4bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
%.8bpp: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
%.gbapal: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src/hooks/assets/cards/80x80/%.8bpp: src/hooks/assets/cards/80x80/%.png | tools-rules
	tools/gbagfx/gbagfx $< $@
src/hooks/assets/cards/80x80/%.huff: src/hooks/assets/cards/80x80/%.8bpp | tools-rules
	tools/gbagfx/gbagfx $< $@ -depth 8 -ygodm
%.lz: %.png | tools-rules
	tools/gbagfx/gbagfx $< $@
