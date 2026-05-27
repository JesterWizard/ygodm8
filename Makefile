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
BUILD_UPS ?= 0
CUSTOM_CODE ?= 1
CUSTOM_EVENTS ?= $(CUSTOM_CODE)
CUSTOM_CARD_MANIFEST ?= $(CUSTOM_CODE)

CC1      := tools/agbcc/bin/agbcc$(EXE)
CC1_OLD  := tools/agbcc/bin/old_agbcc$(EXE)

PREPROC  := tools/preproc/preproc$(EXE)

CPPFLAGS := -I tools/agbcc/include -I tools/agbcc -iquote . -iquote include -Wno-trigraphs
CFLAGS   := -mthumb-interwork -Wimplicit -Werror -O2 -fhex-asm -fshort-enums -fprologue-bugfix
ASFLAGS  := -mcpu=arm7tdmi


C_SUBDIR = src
C_SUBDIR_CUSTOM = src_custom
CONFIGS_SUBDIR = configs
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data
BUILD_DIR = build

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

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
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
CARD_IDS_GENERATED := include/constants/card_ids.h
CARD_COUNTS_GENERATED := include/constants/card_counts.h generated/card_counts.ld generated/card_memory_sizes.inc
CARD_ART_GENERATED := src_custom/generated/card_art_generated.inc src_custom/generated/card_name_generated.inc src_custom/generated/card_data_generated.inc
CARD_TRUNK_GENERATED := src_custom/generated/card_trunk_generated.inc
CARD_DATA_GENERATED_SRC := src_custom/generated/card_data_hooks.c
CARD_ACTIVATION_TEXT_GENERATED := src_custom/generated/card_activation_text_generated.inc
CARD_ACTIVATION_TEXT_LOOKUP_GENERATED := src_custom/generated/card_activation_text_lookup_generated.inc
EVENTS_YAML := events/vanilla/vanilla_events.yaml
EVENTS_CATALOG := events/vanilla/vanilla_event_catalog.md
EVENTS_C_DIR := events/scripts
EVENT_REPLACEMENTS_GENERATED := src_custom/generated/event_script_replacements.inc
CARD_IDS_STAMP := $(BUILD_DIR)/.card_ids.stamp
CARD_GENERATED_STAMP := $(BUILD_DIR)/.card_generated.stamp
CARD_RENDER_ASSETS = $(CARD_TYPE_TILES) $(CARD_TYPE_PALETTES) $(CARD_ATTRIBUTE_TILES) $(CARD_ATTRIBUTE_PALETTES)

ifeq ($(CUSTOM_EVENTS),1)
LYNJUMP_EVENTS := $(shell find . -name 'LynJump.event')
EVENTS_C_SRCS := $(wildcard $(EVENTS_C_DIR)/*.c)
else
LYNJUMP_EVENTS :=
EVENTS_C_SRCS :=
endif

ALL_OBJS := $(C_OBJS) $(CONFIGS_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(CUSTOM_OBJS)

SUBDIRS := $(sort $(dir $(ALL_OBJS)))


#### Recipes ####
$(shell mkdir -p $(SUBDIRS))

ifeq ($(BUILD_UPS),1)
ALL_TARGETS := $(ROM) $(UPS)
else
ALL_TARGETS := $(ROM)
endif

all: $(ALL_TARGETS)

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

event-test: $(EVENTS_C_SRCS) tools/vanilla_events.py
	python3 tools/vanilla_events.py test-c $(EVENTS_C_SRCS)

event-validate: $(EVENTS_YAML) baserom.gba tools/vanilla_events.py
	python3 tools/vanilla_events.py validate $(EVENTS_YAML) --rom baserom.gba

include make_tools.mk
include graphics.mk

ifeq ($(CUSTOM_CODE),1)
$(ROM): $(ELF) $(LYNJUMP_EVENTS) tools/apply_lynjump.py tools/validate_lynjump.py
	@echo "VALIDATE tools/validate_lynjump.py"
	python3 tools/validate_lynjump.py
	@echo "OBJCOPY $@"
	$(OBJCOPY) -O binary --pad-to 0x9000000 $< $@
	@echo "PATCH   tools/apply_lynjump.py"
	python3 tools/apply_lynjump.py $(ELF) $@
else
$(ROM): $(ELF)
	@echo "OBJCOPY $@"
	$(OBJCOPY) -O binary --pad-to 0x9000000 $< $@
endif

$(UPS): $(ROM) baserom.gba tools/make_ups.py
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

$(CARD_GENERATED_STAMP): $(CARD_DATA_MANIFEST) $(CARD_ART_GENERATOR) configs/runtime.c $(CUSTOM_CARD_80_HUFFS) $(CUSTOM_CARD_80_PALETTES) $(CUSTOM_CARD_24_LZS) $(CARD_IDS_GENERATED)
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR)
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

$(CARD_DESCRIPTION_GENERATED) $(CARD_ART_GENERATED) $(CARD_DATA_GENERATED_SRC) $(CARD_TRUNK_GENERATED) $(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED): $(CARD_GENERATED_STAMP)
	@test -f $@

$(DUELIST_REWARDS_GENERATED): $(DUELIST_REWARD_MANIFEST) $(DUELIST_REWARD_GENERATOR)
	@echo "REWARDS $@"
	python3 $(DUELIST_REWARD_GENERATOR) $(DUELIST_REWARD_MANIFEST) --out $@

define compile_c_object_rule
$1/%.o: $2/%.c $(CARD_IDS_GENERATED) | $(CARD_IDS_STAMP) tools/preproc/preproc
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

$(C_BUILDDIR)/card.o: $(CARD_RENDER_ASSETS)
$(eval $(call custom_object_dep,card_asset_hooks,$(CARD_ART_GENERATED)))
$(eval $(call custom_object_dep,card_hooks,$(CARD_ART_GENERATED)))
$(eval $(call custom_object_dep,code_801EF30_hooks,$(DUELIST_REWARDS_GENERATED)))
$(eval $(call custom_object_dep,effect_text_hooks,$(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED)))
$(eval $(call custom_object_dep,event_system_hooks,$(EVENT_REPLACEMENTS_GENERATED)))
$(eval $(call custom_object_dep,generated/card_data_hooks,$(CARD_ART_GENERATED) $(CARD_DESCRIPTION_GENERATED)))
$(eval $(call custom_object_dep,trunk_hooks,$(CARD_TRUNK_GENERATED)))
$(C_BUILDDIR)/overworld/entities/entities.o: $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal
$(eval $(call custom_object_dep,overworld_hooks,$(THOUGHT_BUBBLE_DUMPS) $(THOUGHT_BUBBLE_PALETTES)))
src_custom/assets/portraits/player.8bpp: src_custom/assets/portraits/player.png
	@echo "PORTRAIT $<"
	tools/gbagfx/gbagfx $< $@ -num_tiles 64 -Werror=num_tiles

src_custom/assets/portraits/player.shifted.8bpp: src_custom/assets/portraits/player.8bpp tools/offset_portrait_8bpp.py
	@echo "PALOFF  $<"
	python3 tools/offset_portrait_8bpp.py $< $@

src_custom/assets/portraits/player.lz: src_custom/assets/portraits/player.shifted.8bpp
	@echo "LZ      $<"
	tools/gbagfx/gbagfx $< $@

src_custom/assets/portraits/player.gbapal: src_custom/assets/portraits/player.png
	@echo "PAL     $<"
	tools/gbagfx/gbagfx $< $@

$(eval $(call custom_object_dep,portrait_hooks,src_custom/assets/portraits/player.lz src_custom/assets/portraits/player.gbapal))

$(ASM_BUILDDIR)/ram_map.o: generated/card_memory_sizes.inc

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	@echo "AS      $<"
	$(AS) $(ASFLAGS) $< -o $@

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	@echo "AS      $<"
	$(AS) $(ASFLAGS) $< -o $@

validate-lynjump:
	python3 tools/validate_lynjump.py

memory-report: $(ELF)
	python3 tools/memory_report.py $(ELF) --nm $(NM)

clean: clean-tools clean-graphics
	rm -f $(ROM) $(UPS) $(ELF) $(MAP)
	rm -r $(BUILD_DIR)/

compare: all
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: graphics-rules tools-rules validate-lynjump memory-report
