ifeq ($(OS),Windows_NT)
NPROC ?= 4
else
NPROC := $(shell nproc 2>/dev/null || echo 4)
endif
MAKEFLAGS ?= -j$(NPROC)

PREFIX := arm-none-eabi-
CC := $(PREFIX)gcc
CPP := $(CC) -E
OBJCOPY := $(PREFIX)objcopy
AS := $(PREFIX)as
LD := $(PREFIX)ld
NM := $(PREFIX)nm


ifeq ($(OS),Windows_NT)
EXE := .exe
else ifneq ($(wildcard tools/agbcc/bin/agbcc.exe),)
EXE := .exe
else
EXE :=
endif


BUILD_NAME := ygodm8
FALSE := 0
TRUE  := 1

BUILD_UPS ?= $(FALSE)
CUSTOM_CODE ?= $(TRUE)
CUSTOM_EVENTS ?= $(CUSTOM_CODE)
CUSTOM_CARD_MANIFEST ?= $(CUSTOM_CODE)

METE0_VIDEO ?= $(FALSE)

CC1      := tools/agbcc/bin/agbcc$(EXE)
CC1_OLD  := tools/agbcc/bin/old_agbcc$(EXE)

PREPROC  := tools/preproc/preproc$(EXE)

CPPFLAGS := -I tools/agbcc/include -I tools/agbcc -iquote . -iquote include -Wno-trigraphs
CFLAGS   := -mthumb-interwork -Wimplicit -Werror -O2 -fhex-asm -fshort-enums -fprologue-bugfix
ASFLAGS  := -mcpu=arm7tdmi -I asm


C_SUBDIR = src
C_SUBDIR_CUSTOM = src_custom
CONFIGS_SUBDIR = configs
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data
BUILD_DIR = build
CACHE_DIR = .cache
VOICE_DPCM_CACHE_DIR = $(CACHE_DIR)/voice_dpcm

C_BUILDDIR = $(BUILD_DIR)/$(C_SUBDIR)
C_BUILDDIR_CUSTOM = $(BUILD_DIR)/$(C_SUBDIR_CUSTOM)
CONFIGS_BUILDDIR = $(BUILD_DIR)/$(CONFIGS_SUBDIR)
ASM_BUILDDIR = $(BUILD_DIR)/$(ASM_SUBDIR)
DATA_ASM_BUILDDIR = $(BUILD_DIR)/$(DATA_ASM_SUBDIR)


#### Files/Directories ####

ROM          := $(BUILD_NAME).gba
UPS          := $(BUILD_NAME).ups
ELF          := $(ROM:.gba=.elf)
MAP          := $(ROM:.gba=.map)
LDSCRIPT     := ldscript.ld

C_SRCS := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_SRCS := $(filter-out $(C_SUBDIR)/hooks/generated/card_data_hooks.c,$(C_SRCS))
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))

ifeq ($(CUSTOM_CODE),1)
CUSTOM_SRCS := $(wildcard $(C_SUBDIR_CUSTOM)/*.c $(C_SUBDIR_CUSTOM)/*/*.c $(C_SUBDIR_CUSTOM)/*/*/*.c)
CUSTOM_OBJS := $(patsubst $(C_SUBDIR_CUSTOM)/%.c,$(C_BUILDDIR_CUSTOM)/%.o,$(CUSTOM_SRCS))
else
CUSTOM_SRCS :=
CUSTOM_OBJS :=
endif

CONFIGS_SRCS := $(wildcard $(CONFIGS_SUBDIR)/*.c)
CONFIGS_OBJS := $(patsubst $(CONFIGS_SUBDIR)/%.c,$(CONFIGS_BUILDDIR)/%.o,$(CONFIGS_SRCS))

RAM_MAP_FRAGMENTS := $(ASM_SUBDIR)/ram_map_iwram.s $(ASM_SUBDIR)/ram_map_ewram.s $(ASM_SUBDIR)/ram_map_sram.s
ASM_SRCS := $(filter-out $(RAM_MAP_FRAGMENTS),$(wildcard $(ASM_SUBDIR)/*.s))
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

LIB := -L ../tools/agbcc/lib -lc -lgcc

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_SUBDIR)/*.s)
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))
CARD_DESCRIPTION_GENERATED := src_custom/card_description_data_generated.inc
CARD_DATA_MANIFEST := tools/card_data_manifest.json
CARD_ART_GENERATOR := tools/add_card_art.py
DUELIST_REWARD_MANIFEST := tools/duelist_reward_manifest.json
DUELIST_REWARD_GENERATOR := tools/generate_duelist_rewards.py
DUELIST_REWARDS_GENERATED := src_custom/generated/duelist_rewards_generated.inc
DUELIST_DECK_MANIFEST := tools/duelist_deck_manifest.json
DUELIST_DECK_GENERATOR := tools/generate_duelist_decks.py
DUELIST_DECKS_GENERATED := src_custom/generated/duelist_decks_generated.inc
SHINY_ZONE_MANIFEST := tools/shiny_zone_manifest.json
SHINY_ZONE_GENERATOR := tools/generate_shiny_zones.py
SHINY_ZONES_GENERATED := src_custom/generated/shiny_zones_generated.inc
MATCH_SETTER_GENERATOR := tools/generate_match_setter.py
MATCH_SETTER_GENERATED := src_custom/generated/match_setter_table_generated.inc
DEBUG_MENU_SCENE_GENERATOR := tools/generate_debug_menu_scene_table.py
DEBUG_MENU_SCENE_TABLE := src_custom/debug/debug_menu_scene_table.inc
VOICE_GENERATOR := tools/generate_voices.py
VOICE_MANIFEST := tools/voice_manifest.json
VOICE_WAV_DEPS := $(wildcard src_custom/assets/voices/**/*.wav)
VOICE_STAMP := $(BUILD_DIR)/.voice_generated.stamp
VOICE_GENERATED := src_custom/generated/voice_triggers_generated.inc src_custom/generated/voice_turn_text_generated.inc src_custom/generated/voice_wave_loader_generated.inc src_custom/generated/debug_menu_voice_custom.inc src_custom/generated/voice_song_headers_generated.inc include/constants/custom_voices_generated.h src_custom/generated/voice_rom_patches.json src_custom/assets/voices/VOICES.md
VOICE_ASSETS_S := src_custom/generated/voice_assets_generated.s
VOICE_ASSETS_OBJ := $(C_BUILDDIR_CUSTOM)/generated/voice_assets_generated.o
MUSIC_GENERATOR := tools/generate_music.py
MUSIC_MANIFEST := tools/music_manifest.json
MUSIC_WAV_DEPS := $(wildcard src_custom/assets/music/**/*.wav)
MUSIC_STAMP := $(BUILD_DIR)/.music_generated.stamp
MUSIC_GENERATED := include/constants/custom_music_generated.h src_custom/generated/music_rom_patches.json src_custom/generated/debug_menu_music_custom.inc src_custom/assets/music/MUSIC.md
MUSIC_ASSETS_S := src_custom/generated/music_assets_generated.s
MUSIC_ASSETS_OBJ := $(C_BUILDDIR_CUSTOM)/generated/music_assets_generated.o
AI_ACTION_TABLE_GENERATOR := tools/generate_ai_action_table.py
AI_ACTION_TABLE_GENERATED := src_custom/generated/ai_action_table_generated.inc

# Meteo COMET video blob (post-link pointer fix)
METE0_INTEGRATE := tools/meteo_integrate.py
METE0_GENERATED := src_custom/generated/meteo_video_assets_generated.inc
METE0_VIDEO_SRC := src_custom/assets/videos/intro.bin
METE0_ASM_SRC := src_custom/meteo_player_stub.s
METE0_ASM_OBJ := $(C_BUILDDIR_CUSTOM)/meteo_player_stub.o
FIELD_SPELL_GFX_GENERATOR := tools/build_field_spell_gfx.py
FIELD_SPELL_GFX_GENERATED := src_custom/generated/field_spell_gfx_generated.inc src_custom/generated/field_spell_tilemaps_generated.inc src_custom/generated/field_spell_card_lookup_generated.inc src_custom/generated/field_spell_gfx_tables_generated.inc src_custom/generated/field_spell_effect_table_generated.inc src_custom/generated/field_spell_stat_mods_generated.inc src_custom/generated/field_spell_mapping_generated.inc include/constants/custom_field_spells_generated.h include/constants/custom_fields_generated.h
FIELD_SPELL_STEM_PNGS := $(wildcard src_custom/assets/field_spells/*.png)
FIELD_SPELL_DIR_PNGS := $(shell find src_custom/assets/field_spells -mindepth 2 -maxdepth 2 -type f -name '*.png' 2>/dev/null | sort)
FIELD_SPELL_PNGS := $(sort $(FIELD_SPELL_STEM_PNGS) $(FIELD_SPELL_DIR_PNGS))
FIELD_SPELL_GFX_STAMP := $(BUILD_DIR)/.field_spell_gfx.stamp
FIELD_SPELL_CACHE_DIR = $(CACHE_DIR)/field_spells
CARD_IDS_GENERATED := include/constants/card_ids.h
CARD_COUNTS_GENERATED := include/constants/card_counts.h generated/card_counts.ld generated/card_memory_sizes.inc
CARD_ART_GENERATED := src_custom/generated/card_art_generated.inc src_custom/generated/card_name_generated.inc src_custom/generated/card_data_generated.inc
CARD_TRUNK_GENERATED := src_custom/generated/card_trunk_generated.inc
CARD_DATA_GENERATED_SRC := src_custom/generated/card_data_hooks.c
CARD_ACTIVATION_TEXT_GENERATED := src_custom/generated/card_activation_text_generated.inc
CARD_ACTIVATION_TEXT_LOOKUP_GENERATED := src_custom/generated/card_activation_text_lookup_generated.inc
CARD_EFFECT_TEXTS_H := include/constants/card_effect_texts.h
EVENTS_YAML := events/vanilla/vanilla_events.yaml
EVENTS_CATALOG := events/vanilla/vanilla_event_catalog.md
EVENTS_C_DIR := events/scripts
EVENT_REPLACEMENTS_GENERATED := src_custom/generated/event_script_replacements.inc
CG_GENERATOR := tools/generate_cg_assets.py
CG_GENERATED := include/constants/event_cg_generated.h src_custom/generated/event_cg_assets_generated.inc
OPENING_SCREEN_GENERATOR := tools/generate_opening_screen_assets.py
OPENING_SCREEN_GENERATED := src_custom/generated/opening_screen_assets_generated.inc
OPENING_SCREEN_PLACEHOLDER_GENERATOR := tools/generate_opening_screen_placeholders.py
OPENING_SCREEN_PNGS := src_custom/assets/opening_screens/opening_screen_1.png \
                       src_custom/assets/opening_screens/opening_screen_2.png \
                       src_custom/assets/opening_screens/opening_screen_3.png
CG_BUILD_GENERATOR := tools/build_cg.py
OPENING_SCREEN_BUILD_GENERATOR := tools/build_opening_screen.py
OPENING_SCREEN_STAMP := $(BUILD_DIR)/.opening_screens.stamp
TITLE_SCREEN_GENERATOR := tools/generate_title_screen_assets.py
TITLE_SCREEN_GENERATED := src_custom/generated/title_screen_assets_generated.inc
TITLE_SCREEN_RESERVED_GENERATED := src_custom/generated/title_screen_palette_reservations_generated.inc
TITLE_SCREEN_PLACEHOLDER_GENERATOR := tools/generate_title_screen_placeholders.py
TITLE_SCREEN_PNGS := src_custom/assets/title_screens/title_screen.png
TITLE_SCREEN_BUILD_GENERATOR := tools/build_title_screen.py
TITLE_SCREEN_STAMP := $(BUILD_DIR)/.title_screens.stamp
CARD_IDS_STAMP := $(BUILD_DIR)/.card_ids.stamp
CARD_GENERATED_STAMP := $(BUILD_DIR)/.card_generated.stamp
CARD_ART_STAMP := $(BUILD_DIR)/.card_art.stamp
CARD_RENDER_ASSETS = $(CARD_TYPE_TILES) $(CARD_TYPE_PALETTES) $(CARD_ATTRIBUTE_TILES) $(CARD_ATTRIBUTE_PALETTES)

ifeq ($(CUSTOM_EVENTS),1)
LYNJUMP_EVENTS := $(shell find . -name 'LynJump.event')
EVENTS_C_SRCS := $(wildcard $(EVENTS_C_DIR)/*.c)
else
LYNJUMP_EVENTS :=
EVENTS_C_SRCS :=
endif

ifeq ($(CUSTOM_CODE),1)
LYNJUMP_VALIDATE_STAMP := $(BUILD_DIR)/.lynjump_validated.stamp
LYNJUMP_VALIDATE_DEPS := $(LYNJUMP_EVENTS) tools/validate_lynjump.py
endif

ALL_OBJS := $(C_OBJS) $(CONFIGS_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(CUSTOM_OBJS) $(MUSIC_ASSETS_OBJ) $(VOICE_ASSETS_OBJ) $(METE0_ASM_OBJ)

SUBDIRS := $(sort $(dir $(ALL_OBJS)))


#### Recipes ####
$(shell mkdir -p $(SUBDIRS))

ifeq ($(BUILD_UPS),1)
ALL_TARGETS := $(ROM) $(UPS)
else
ALL_TARGETS := $(ROM)
endif

all: $(ALL_TARGETS)

baserom.gba:
	@test -f $@ || (echo "error: baserom.gba is required — place a clean retail ROM dump in the project root" >&2; exit 1)

$(ALL_TARGETS): | tools-rules

.PHONY: event-extract event-catalog event-compile event-export-c event-test event-validate

event-extract: baserom.gba tools/vanilla_events.py
	python3 tools/vanilla_events.py extract --rom baserom.gba --out $(EVENTS_YAML) --catalog $(EVENTS_CATALOG)

event-catalog: $(EVENTS_YAML) tools/vanilla_events.py
	python3 tools/vanilla_events.py catalog $(EVENTS_YAML) --out $(EVENTS_CATALOG)

ifeq ($(CUSTOM_EVENTS),1)
$(EVENT_REPLACEMENTS_GENERATED): $(EVENTS_C_SRCS) tools/vanilla_events.py
	@echo "EVENT  $(EVENT_REPLACEMENTS_GENERATED)"
	@echo "INPUTS $(filter %.c,$?)"
	@if [ -n "$(EVENTS_C_SRCS)" ]; then \
		python3 tools/vanilla_events.py compile-c $(EVENTS_C_SRCS) --out $(EVENT_REPLACEMENTS_GENERATED); \
	else \
		test -f $(EVENTS_YAML); \
		python3 tools/vanilla_events.py compile $(EVENTS_YAML) --out $(EVENT_REPLACEMENTS_GENERATED); \
	fi

event-compile: $(EVENT_REPLACEMENTS_GENERATED)
	@echo "BUILD   $(ROM)"
	@$(MAKE) $(ROM)
else
$(EVENT_REPLACEMENTS_GENERATED):
	@mkdir -p $(dir $@)
	@touch $@

event-compile:
	@echo "BUILD   $(ROM)"
	@$(MAKE) $(ROM)
endif

event-export-c: $(EVENTS_YAML) tools/vanilla_events.py
	python3 tools/vanilla_events.py export-c $(EVENTS_YAML) --out-dir $(EVENTS_C_DIR)

event-test: $(EVENTS_C_SRCS) tools/vanilla_events.py $(CG_GENERATED)
	python3 tools/vanilla_events.py test-c $(EVENTS_C_SRCS)

event-validate: $(EVENTS_YAML) baserom.gba tools/vanilla_events.py
	python3 tools/vanilla_events.py validate $(EVENTS_YAML) --rom baserom.gba

include make_tools.mk
include graphics.mk

ifeq ($(CUSTOM_CODE),1)
$(LYNJUMP_VALIDATE_STAMP): $(LYNJUMP_VALIDATE_DEPS)
	@mkdir -p $(dir $@)
	@echo "VALIDATE tools/validate_lynjump.py"
	python3 tools/validate_lynjump.py
	@touch $@

$(ROM): $(ELF) $(LYNJUMP_VALIDATE_STAMP) tools/apply_lynjump.py
	@echo "OBJCOPY $@"
	$(OBJCOPY) -O binary --pad-to 0x9000020 $< $@
	@echo "PATCH   tools/apply_lynjump.py"
	python3 tools/apply_lynjump.py $(ELF) $@
ifeq ($(METE0_VIDEO),1)
	@echo "PATCH   tools/meteo_integrate.py"
	python3 $(METE0_INTEGRATE) --rom $@ --map $(MAP)
endif
else
$(ROM): $(ELF)
	@echo "OBJCOPY $@"
	$(OBJCOPY) -O binary --pad-to 0x9000020 $< $@
endif

$(UPS): $(ROM) baserom.gba tools/make_ups.py
	@echo "UPS     $@"
	python3 tools/make_ups.py baserom.gba $(ROM) $@

$(ELF): $(ALL_OBJS) $(LDSCRIPT)
	@echo "LINK    $@"
	cd $(BUILD_DIR) && $(LD) -T ../$(LDSCRIPT) -T ../generated/card_counts.ld -Map ../$(MAP) -o ../$@ $(patsubst $(BUILD_DIR)/%,%,$(ALL_OBJS)) $(LIB)

ifeq ($(CUSTOM_CARD_MANIFEST),1)
$(CARD_IDS_STAMP): $(CARD_DATA_MANIFEST) $(CARD_ART_GENERATOR)
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR) --card-ids
	touch $@

$(CARD_IDS_GENERATED) $(CARD_COUNTS_GENERATED): $(CARD_IDS_STAMP)
	@test -f $@

# Manifest is a dep so pre-existing 80x80 PNGs bind when a card entry is added.
# --skip-art rewrites art tables from build/ artifacts only; without this, new
# manifest cards whose PNGs were already on disk get [id] = 0 pointers.
$(CARD_ART_STAMP): $(CARD_ART_GENERATOR) $(CARD_DATA_MANIFEST) $(CUSTOM_CARD_80_PNGS) $(CUSTOM_CARD_24_PNGS) src_custom/assets/cards/mini.pal
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR) --art-only
	touch $@

$(CARD_GENERATED_STAMP): $(CARD_DATA_MANIFEST) $(CARD_ART_GENERATOR) configs/runtime.c $(CARD_IDS_GENERATED) $(CARD_ART_STAMP)
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR) --skip-art
	touch $@
else
$(CARD_IDS_STAMP):
	@mkdir -p $(dir $@)
	@touch $@

$(CARD_IDS_GENERATED): $(CARD_IDS_STAMP)
	@test -f $@

$(CARD_GENERATED_STAMP):
	@mkdir -p $(dir $@)
	@touch $@
endif

src_custom/generated/card_art_generated.inc: $(CARD_ART_STAMP)
	@test -f $@

$(CARD_DESCRIPTION_GENERATED) src_custom/generated/card_name_generated.inc src_custom/generated/card_data_generated.inc $(CARD_DATA_GENERATED_SRC) $(CARD_TRUNK_GENERATED) $(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED) $(CARD_EFFECT_TEXTS_H): $(CARD_GENERATED_STAMP)
	@test -f $@

$(DUELIST_REWARDS_GENERATED): $(DUELIST_REWARD_MANIFEST) $(DUELIST_REWARD_GENERATOR)
	@echo "REWARDS $@"
	python3 $(DUELIST_REWARD_GENERATOR) $(DUELIST_REWARD_MANIFEST) --out $@

$(DUELIST_DECKS_GENERATED): $(DUELIST_DECK_MANIFEST) $(DUELIST_DECK_GENERATOR)
	@echo "DECKS   $@"
	python3 $(DUELIST_DECK_GENERATOR) $(DUELIST_DECK_MANIFEST) --out $@

$(AI_ACTION_TABLE_GENERATED): src/duel/ai.c $(AI_ACTION_TABLE_GENERATOR)
	@echo "AIACT   $@"
	python3 $(AI_ACTION_TABLE_GENERATOR)

$(SHINY_ZONES_GENERATED): $(SHINY_ZONE_MANIFEST) $(SHINY_ZONE_GENERATOR) $(CARD_DATA_MANIFEST) $(CARD_IDS_GENERATED) include/overworld.h include/shiny_zones.h
	@echo "SHINY   $@"
	python3 $(SHINY_ZONE_GENERATOR) $(SHINY_ZONE_MANIFEST) --out $@

$(MATCH_SETTER_GENERATED): events/vanilla/vanilla_event_catalog.md $(MATCH_SETTER_GENERATOR) src_custom/debug/debug_menu_portrait_table.inc include/overworld.h
	@echo "MATCH   $@"
	python3 $(MATCH_SETTER_GENERATOR) --out $@

$(DEBUG_MENU_SCENE_TABLE): $(DEBUG_MENU_SCENE_GENERATOR) $(wildcard events/scripts/map_*_state_*.c)
	@echo "SCENES  $@"
	python3 $(DEBUG_MENU_SCENE_GENERATOR) --out $@

$(VOICE_STAMP): $(VOICE_MANIFEST) $(VOICE_GENERATOR) $(VOICE_WAV_DEPS)
	@mkdir -p $(dir $@)
	@echo "VOICE   custom duelist voice clips"
	@mkdir -p $(VOICE_DPCM_CACHE_DIR)
	python3 $(VOICE_GENERATOR) $(VOICE_MANIFEST) --stamp $@ --dpcm-cache-dir $(VOICE_DPCM_CACHE_DIR)

$(VOICE_GENERATED) $(VOICE_ASSETS_S): $(VOICE_STAMP)
	@test -f $(VOICE_STAMP)

$(MUSIC_STAMP): $(MUSIC_MANIFEST) $(MUSIC_GENERATOR) $(MUSIC_WAV_DEPS) $(VOICE_STAMP)
	@echo "MUSIC   custom background tracks"
	@mkdir -p $(CACHE_DIR)
	python3 $(MUSIC_GENERATOR) $(MUSIC_MANIFEST) --stamp $@

$(MUSIC_GENERATED) $(MUSIC_ASSETS_S): $(MUSIC_STAMP)
	@test -f $(MUSIC_STAMP)
	@test -f $@

$(FIELD_SPELL_GFX_STAMP): src_custom/field_spell_table.inc $(FIELD_SPELL_GFX_GENERATOR) $(FIELD_SPELL_PNGS) $(CARD_DATA_MANIFEST) | tools-rules
	@echo "FIELD   custom field spell gfx"
	@mkdir -p $(FIELD_SPELL_CACHE_DIR)
	python3 $(FIELD_SPELL_GFX_GENERATOR) --stamp $@ --cache-dir $(FIELD_SPELL_CACHE_DIR)

$(FIELD_SPELL_GFX_GENERATED): $(FIELD_SPELL_GFX_STAMP)
	@test -f $@

define compile_c_object_rule
$1/%.o: $2/%.c $(CARD_IDS_GENERATED) configs/runtime.h | $(CARD_IDS_STAMP) tools/preproc/preproc
	@echo "CC      $$<"
	$(CPP) $(CPPFLAGS) $$< -o $1/$$*.i
	@$(PREPROC) $1/$$*.i charmap.txt | $(CC1) $(CFLAGS) -o $1/$$*.s
	@echo ".text\\n\\t.align\\t2, 0\\n" >> $1/$$*.s
	@echo "AS      $$@"
	$(AS) $(ASFLAGS) $1/$$*.s -o $$@
endef

define custom_object_dep
$(C_BUILDDIR_CUSTOM)/$1.o: $2
endef

$(eval $(call compile_c_object_rule,$(C_BUILDDIR),$(C_SUBDIR)))
$(eval $(call compile_c_object_rule,$(C_BUILDDIR_CUSTOM),$(C_SUBDIR_CUSTOM)))
$(eval $(call compile_c_object_rule,$(CONFIGS_BUILDDIR),$(CONFIGS_SUBDIR)))

$(C_BUILDDIR)/duel/trap_effects.o: src/duel/trap_effects.c $(CARD_IDS_GENERATED) | $(CARD_IDS_STAMP) tools/preproc/preproc
	@echo "CC      $<"
	$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/duel/trap_effects.i
	@$(PREPROC) $(C_BUILDDIR)/duel/trap_effects.i charmap.txt | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/duel/trap_effects.s
	@echo ".text\\n\\t.align\\t2, 0\\n" >> $(C_BUILDDIR)/duel/trap_effects.s
	@echo "AS      $@"
	$(AS) $(ASFLAGS) $(C_BUILDDIR)/duel/trap_effects.s -o $(C_BUILDDIR)/duel/trap_effects.o
	$(OBJCOPY) --globalize-symbols=tools/trap_effects_exports.sym $@

$(C_BUILDDIR)/card.o: $(CARD_RENDER_ASSETS)
$(eval $(call custom_object_dep,card_asset_hooks,$(CARD_ART_GENERATED)))
$(eval $(call custom_object_dep,card_hooks,$(CARD_ART_GENERATED) $(FIELD_SPELL_GFX_STAMP)))
$(eval $(call custom_object_dep,code_801EF30_hooks,$(DUELIST_REWARDS_GENERATED)))
$(eval $(call custom_object_dep,duel_util_hooks,$(DUELIST_DECKS_GENERATED)))
$(eval $(call custom_object_dep,ai_hooks,$(AI_ACTION_TABLE_GENERATED)))
$(eval $(call custom_object_dep,ai_decision/ai_action_decode,$(AI_ACTION_TABLE_GENERATED)))
$(eval $(call custom_object_dep,effect_text_hooks,$(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED) $(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,battle_effects/elemental_hero_core,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,battle_effects/elemental_hero_ice_edge,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,activated_effects/elemental_hero_ice_edge,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,activated_effects/elemental_hero_blazeman,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,activated_effects/elemental_hero_stratos,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,permanent_effects/elemental_hero_core,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,permanent_effects/elemental_hero_sunrise,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,permanent_effects/elemental_hero_captain_gold,$(CARD_EFFECT_TEXTS_H)))
$(eval $(call custom_object_dep,event_system_hooks,$(EVENT_REPLACEMENTS_GENERATED)))
$(eval $(call custom_object_dep,generated/card_data_hooks,$(CARD_ART_GENERATED) $(CARD_DESCRIPTION_GENERATED)))
$(eval $(call custom_object_dep,duel_voice_hooks,$(VOICE_STAMP)))
$(eval $(call custom_object_dep,voice_dpcm,$(VOICE_STAMP)))
$(eval $(call custom_object_dep,custom_music,$(MUSIC_STAMP)))
$(eval $(call custom_object_dep,debug/debug_menu_voice,$(VOICE_STAMP)))
$(eval $(call custom_object_dep,debug/debug_menu_music,$(MUSIC_STAMP)))
$(eval $(call custom_object_dep,debug/debug_menu,$(DEBUG_MENU_LZ) $(DEBUG_MENU_PAL)))
$(eval $(call custom_object_dep,shiny_zones,$(SHINY_ZONES_GENERATED)))
$(eval $(call custom_object_dep,match_setter_hooks,$(MATCH_SETTER_GENERATED)))
$(eval $(call custom_object_dep,debug/debug_menu_match_setter,$(MATCH_SETTER_GENERATED)))
$(eval $(call custom_object_dep,debug/debug_menu_scene,$(DEBUG_MENU_SCENE_TABLE)))
$(eval $(call custom_object_dep,trunk_hooks,$(CARD_TRUNK_GENERATED)))
$(C_BUILDDIR)/overworld/entities/entities.o: $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal
$(eval $(call custom_object_dep,overworld_hooks,$(THOUGHT_BUBBLE_DUMPS) $(THOUGHT_BUBBLE_PALETTES)))
$(eval $(call custom_object_dep,field_spell_gfx,$(FIELD_SPELL_GFX_STAMP) $(FIELD_SPELL_HUFFS) $(FIELD_SPELL_PALETTES)))
$(eval $(call custom_object_dep,field_spell_gfx_hooks,$(FIELD_SPELL_GFX_STAMP) $(FIELD_SPELL_HUFFS) $(FIELD_SPELL_PALETTES)))
$(eval $(call custom_object_dep,field_spell_effect_hooks,$(FIELD_SPELL_GFX_STAMP)))
$(eval $(call custom_object_dep,code_803F02C_hooks,$(FIELD_SPELL_GFX_STAMP)))
PORTRAIT_NORM = $(BUILD_DIR)/portraits/player.normalized.png

$(BUILD_DIR)/portraits:
	@mkdir -p $@

$(PORTRAIT_NORM): src_custom/assets/portraits/player.png tools/normalize_portrait_png.py | $(BUILD_DIR)/portraits
	@echo "PNGNORM $<"
	python3 tools/normalize_portrait_png.py $< $@

src_custom/assets/portraits/player.8bpp: $(PORTRAIT_NORM) | tools-rules
	@echo "PORTRAIT $<"
	tools/gbagfx/gbagfx $< $@ -num_tiles 64 -Werror=num_tiles

src_custom/assets/portraits/player.shifted.8bpp: src_custom/assets/portraits/player.8bpp tools/offset_portrait_8bpp.py
	@echo "PALOFF  $<"
	python3 tools/offset_portrait_8bpp.py $< $@

src_custom/assets/portraits/player.lz: src_custom/assets/portraits/player.shifted.8bpp | tools-rules
	@echo "LZ      $<"
	tools/gbagfx/gbagfx $< $@

src_custom/assets/portraits/player.gbapal: $(PORTRAIT_NORM) | tools-rules
	@echo "PAL     $<"
	tools/gbagfx/gbagfx $< $@

$(eval $(call custom_object_dep,portrait_hooks,src_custom/assets/portraits/player.lz src_custom/assets/portraits/player.gbapal))

build/cgs/%.lz build/cgs/%.gbapal: src_custom/assets/cgs/%.png $(CG_BUILD_GENERATOR) tools/build_cg_palette.py tools/offset_cg_8bpp.py tools/validate_cg.py | tools-rules
	@echo "CGBUILD $<"
	python3 $(CG_BUILD_GENERATOR) $<

$(CG_GENERATED): $(CG_GENERATOR) $(CG_BUILD_ARTIFACTS) | tools-rules
	@echo "CGGEN   $<"
	python3 $(CG_GENERATOR)

$(eval $(call custom_object_dep,cg_hooks,$(CG_GENERATED) $(CG_BUILD_ARTIFACTS)))
$(eval $(call custom_object_dep,script_cg_hooks,))

$(OPENING_SCREEN_PNGS): $(OPENING_SCREEN_PLACEHOLDER_GENERATOR)
	@for path in $(OPENING_SCREEN_PNGS); do \
		if [ ! -f $$path ]; then \
			echo "PLACE  opening screen placeholders"; \
			python3 $(OPENING_SCREEN_PLACEHOLDER_GENERATOR); \
			break; \
		fi; \
	done

$(OPENING_SCREEN_STAMP): $(OPENING_SCREEN_PNGS) $(OPENING_SCREEN_GENERATOR) $(OPENING_SCREEN_BUILD_GENERATOR) tools/build_opening_palette.py tools/validate_opening_screen.py | tools-rules
	@echo "OPENGEN opening screens"
	@mkdir -p $(dir $@)
	python3 $(OPENING_SCREEN_GENERATOR)
	touch $@

$(OPENING_SCREEN_GENERATED): $(OPENING_SCREEN_STAMP)
	@test -f $@

$(eval $(call custom_object_dep,copyright_screens_hooks,$(OPENING_SCREEN_GENERATED)))

$(TITLE_SCREEN_PNGS): $(TITLE_SCREEN_PLACEHOLDER_GENERATOR)
	@if [ ! -f $(TITLE_SCREEN_PNGS) ]; then \
		echo "PLACE  title screen placeholder"; \
		python3 $(TITLE_SCREEN_PLACEHOLDER_GENERATOR); \
	fi

$(TITLE_SCREEN_STAMP): $(TITLE_SCREEN_PNGS) $(TITLE_SCREEN_GENERATOR) $(TITLE_SCREEN_BUILD_GENERATOR) tools/build_opening_palette.py tools/validate_title_screen.py tools/extract_title_screen_palette_reservations.py | tools-rules
	@echo "TITLEGEN title screen"
	@mkdir -p $(dir $@)
	python3 $(TITLE_SCREEN_GENERATOR)
	touch $@

$(TITLE_SCREEN_GENERATED): $(TITLE_SCREEN_STAMP)
	@test -f $@

$(TITLE_SCREEN_RESERVED_GENERATED): $(TITLE_SCREEN_STAMP)
	@test -f $@

$(eval $(call custom_object_dep,title_screen_hooks,$(TITLE_SCREEN_GENERATED) $(TITLE_SCREEN_RESERVED_GENERATED)))

# Build rule for the Meteo ARM stub
$(METE0_ASM_OBJ): $(METE0_ASM_SRC)
	@echo "AS      $<"
	$(AS) $(ASFLAGS) $< -o $@

# video_player.c — passes -DMETE0_VIDEO_ENABLED for compile-time toggle.
# Overrides the pattern rule to inject the flag.
$(C_BUILDDIR_CUSTOM)/video_player.o: src_custom/video_player.c $(METE0_GENERATED) $(CARD_IDS_GENERATED) | $(CARD_IDS_STAMP) tools/preproc/preproc
	@echo "CC      $<"
	$(CPP) $(CPPFLAGS) -DMETE0_VIDEO_ENABLED=$(METE0_VIDEO) $< -o $(C_BUILDDIR_CUSTOM)/video_player.i
	@$(PREPROC) $(C_BUILDDIR_CUSTOM)/video_player.i charmap.txt | $(CC1) $(CFLAGS) -o $(C_BUILDDIR_CUSTOM)/video_player.s
	@echo ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR_CUSTOM)/video_player.s
	@echo "AS      $@"
	$(AS) $(ASFLAGS) $(C_BUILDDIR_CUSTOM)/video_player.s -o $@

# Post-link: fix Meteo blob pointers after LynJump patching
ifeq ($(METE0_VIDEO),1)
$(ROM): $(METE0_INTEGRATE)
endif

$(ASM_BUILDDIR)/ram_map.o: generated/card_memory_sizes.inc $(RAM_MAP_FRAGMENTS)
$(ASM_BUILDDIR)/m4a_hq_mixer.o: $(ASM_SUBDIR)/m4a_hq_mixer_config.inc

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	@echo "AS      $<"
	$(AS) $(ASFLAGS) $< -o $@

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	@echo "AS      $<"
	$(AS) $(ASFLAGS) $< -o $@

$(C_BUILDDIR_CUSTOM)/generated/voice_assets_generated.o: $(VOICE_ASSETS_S) $(VOICE_STAMP)
	@echo "AS      $<"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(C_BUILDDIR_CUSTOM)/generated/music_assets_generated.o: $(MUSIC_ASSETS_S) $(MUSIC_STAMP)
	@echo "AS      $<"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

ifeq ($(CUSTOM_CODE),1)
validate-lynjump: $(LYNJUMP_VALIDATE_STAMP)
else
validate-lynjump:
	python3 tools/validate_lynjump.py
endif

memory-report: $(ELF)
	python3 tools/memory_report.py $(ELF) --nm $(NM)

clean-build clean-quick:
	rm -f $(ROM) $(UPS) $(ELF) $(MAP)
	rm -rf $(BUILD_DIR)/

clean-cache:
	rm -rf $(CACHE_DIR)/

clean: clean-build clean-tools clean-graphics

compare: all
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: test update-goldens test-host test-cards test-cards-build test-cards-link add-card card-cost

test-cards: tools-rules
	python3 tools/card_art_progress.py
	PYTHONPATH=$(CURDIR) python3 -m unittest tests.host.test_cards_manifest tests.host.test_add_custom_card tests.host.test_ram_map_layout -v
	python3 tools/validate_trunk_sort.py
	python3 tools/validate_trunk_qty.py

test-cards-build: test-cards
	$(MAKE) all

# Quick check: manifest + wiring sanity only, no full ROM link.
# Use after adding effect hook files or wiring dispatchers.
test-cards-link: test-cards
	$(MAKE) -j$$(nproc) all 2>&1 | tail -20
	@echo "--- Link check passed ---"

add-card:
	@test -n "$(CARD)" || (echo "Usage: make add-card CARD='Card Name' [WRITE=1] [RUNTIME_HAND=1]" && exit 1)
	python3 tools/add_custom_card.py "$(CARD)" \
		$(if $(PASSCODE),--passcode $(PASSCODE),) \
		$(if $(WRITE),--write,) \
		$(if $(RUNTIME_HAND),--runtime-hand $(RUNTIME_HAND),)

card-cost:
	python3 tools/suggest_card_cost.py \
		$(if $(LEVEL),--level $(LEVEL),) \
		$(if $(ATK),--atk $(ATK),) \
		$(if $(or $(DEFENSE),$(DEF)),--defense $(or $(DEFENSE),$(DEF)),) \
		$(if $(COLOR),--color $(COLOR),)

test-host: tools-rules
	PYTHONPATH=$(CURDIR) python3 -m unittest discover -s tests/host -v
	python3 tools/validate_portrait.py
	python3 tools/validate_cg.py
	python3 tools/validate_opening_screen.py
	python3 tools/validate_ram_map.py
	python3 tools/validate_duel_popup_textbox.py
	python3 tools/validate_duel_shop_drops.py
	python3 tools/validate_duel_b_menu.py
	python3 tools/validate_player_decks.py
	python3 tools/validate_trunk_sort.py
	python3 tools/validate_trunk_qty.py
	python3 tools/validate_lynjump.py
	python3 tools/validate_ups.py
ifneq ($(strip $(EVENTS_C_SRCS)),)
	@echo "EVENT-TEST tools/vanilla_events.py"
	python3 tools/vanilla_events.py test-c $(EVENTS_C_SRCS)
endif

test: test-host
	$(MAKE) all
ifeq ($(BUILD_UPS),1)
	python3 tools/validate_ups.py
endif
	python3 tools/validate_duel_popup_textbox.py --elf $(ELF) --nm $(NM)
	python3 tools/validate_player_decks.py --elf $(ELF) --nm $(NM)
	python3 tools/memory_report.py $(ELF) --nm $(NM)

update-goldens:
	UPDATE_GOLDENS=1 PYTHONPATH=$(CURDIR) python3 -m unittest discover -s tests/host -v

.PHONY: all clean clean-build clean-quick clean-cache clean-tools clean-graphics graphics-rules tools-rules validate-lynjump memory-report compare event-extract event-catalog event-compile event-export-c event-test event-validate test test-host test-cards test-cards-build add-card card-cost update-goldens
