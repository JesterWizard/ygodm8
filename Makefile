PREFIX := arm-none-eabi-
CC := $(PREFIX)gcc
CPP := $(CC) -E
OBJCOPY := $(PREFIX)objcopy
AS := $(PREFIX)as
LD := $(PREFIX)ld


ifeq ($(OS),Windows_NT)
EXE := .exe
else ifneq ($(wildcard tools/agbcc/bin/agbcc.exe),)
EXE := .exe
else
EXE :=
endif


BUILD_NAME := ygodm8
BUILD_UPS ?= 0

CC1      := tools/agbcc/bin/agbcc$(EXE)
CC1_OLD  := tools/agbcc/bin/old_agbcc$(EXE)

PREPROC  := tools/preproc/preproc$(EXE)

CPPFLAGS := -I tools/agbcc/include -I tools/agbcc -iquote . -iquote include -Wno-trigraphs
CFLAGS   := -mthumb-interwork -Wimplicit -Werror -O2 -fhex-asm -fshort-enums -fprologue-bugfix
ASFLAGS  := -mcpu=arm7tdmi


C_SUBDIR = src
CONFIGS_SUBDIR = configs
ASM_SUBDIR = asm
DATA_ASM_SUBDIR = data
BUILD_DIR = build

C_BUILDDIR = $(BUILD_DIR)/$(C_SUBDIR)
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
HOOK_SRCS := $(wildcard $(C_SUBDIR)/hooks/*.c) $(C_SUBDIR)/hooks/generated/card_data_hooks.c
C_SRCS := $(filter-out $(HOOK_SRCS),$(C_SRCS))
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))
HOOK_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(HOOK_SRCS))

CONFIGS_SRCS := $(wildcard $(CONFIGS_SUBDIR)/*.c)
CONFIGS_OBJS := $(patsubst $(CONFIGS_SUBDIR)/%.c,$(CONFIGS_BUILDDIR)/%.o,$(CONFIGS_SRCS))

ASM_SRCS := $(wildcard $(ASM_SUBDIR)/*.s)
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

LIB := -L ../tools/agbcc/lib -lc -lgcc

DATA_ASM_SRCS := $(wildcard $(DATA_ASM_SUBDIR)/*.s)
DATA_ASM_OBJS := $(patsubst $(DATA_ASM_SUBDIR)/%.s,$(DATA_ASM_BUILDDIR)/%.o,$(DATA_ASM_SRCS))
LYNJUMP_EVENTS := $(shell find . -name 'LynJump.event')
CARD_DESCRIPTION_GENERATED := src/hooks/card_description_data_generated.inc
CARD_DATA_MANIFEST := tools/card_data_manifest.json
CARD_ART_GENERATOR := tools/add_card_art.py
CARD_IDS_GENERATED := include/constants/card_ids.h
CARD_ART_GENERATED := src/hooks/generated/card_art_generated.inc src/hooks/generated/card_name_generated.inc src/hooks/generated/card_data_generated.inc
CARD_TRUNK_GENERATED := src/hooks/generated/card_trunk_generated.inc
CARD_DATA_GENERATED_SRC := src/hooks/generated/card_data_hooks.c
CARD_ACTIVATION_TEXT_GENERATED := src/hooks/generated/card_activation_text_generated.inc
CARD_ACTIVATION_TEXT_LOOKUP_GENERATED := src/hooks/generated/card_activation_text_lookup_generated.inc
EVENTS_YAML := events/vanilla/vanilla_events.yaml
EVENTS_CATALOG := events/vanilla/vanilla_event_catalog.md
EVENTS_C_DIR := events/scripts
EVENTS_C_SRCS := $(wildcard $(EVENTS_C_DIR)/*.c)
EVENT_REPLACEMENTS_GENERATED := src/hooks/generated/event_script_replacements.inc
CARD_IDS_STAMP := $(BUILD_DIR)/.card_ids.stamp
CARD_GENERATED_STAMP := $(BUILD_DIR)/.card_generated.stamp
CARD_RENDER_ASSETS := $(CARD_TYPE_TILES) $(CARD_TYPE_PALETTES) $(CARD_ATTRIBUTE_TILES) $(CARD_ATTRIBUTE_PALETTES)

ALL_OBJS := $(C_OBJS) $(CONFIGS_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(HOOK_OBJS)

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

event-compile: $(EVENTS_C_SRCS) tools/vanilla_events.py
	@if [ -n "$(EVENTS_C_SRCS)" ]; then \
		python3 tools/vanilla_events.py compile-c $(EVENTS_C_SRCS) --out $(EVENT_REPLACEMENTS_GENERATED); \
	else \
		test -f $(EVENTS_YAML); \
		python3 tools/vanilla_events.py compile $(EVENTS_YAML) --out $(EVENT_REPLACEMENTS_GENERATED); \
	fi

event-export-c: $(EVENTS_YAML) tools/vanilla_events.py
	python3 tools/vanilla_events.py export-c $(EVENTS_YAML) --out-dir $(EVENTS_C_DIR)

event-test: $(EVENTS_C_SRCS) tools/vanilla_events.py
	python3 tools/vanilla_events.py test-c $(EVENTS_C_SRCS)

event-validate: $(EVENTS_YAML) baserom.gba tools/vanilla_events.py
	python3 tools/vanilla_events.py validate $(EVENTS_YAML) --rom baserom.gba

include make_tools.mk
include graphics.mk

$(ROM): $(ELF) $(LYNJUMP_EVENTS) tools/apply_lynjump.py tools/validate_lynjump.py
	python3 tools/validate_lynjump.py
	$(OBJCOPY) -O binary --pad-to 0x9000000 $< $@
	python3 tools/apply_lynjump.py $(ELF) $@

$(UPS): $(ROM) baserom.gba tools/make_ups.py
	python3 tools/make_ups.py baserom.gba $(ROM) $@

$(ELF): $(ALL_OBJS) $(LDSCRIPT)
	cd $(BUILD_DIR) && $(LD) -T ../$(LDSCRIPT) -Map ../$(MAP) -o ../$@ $(patsubst $(BUILD_DIR)/%,%,$(ALL_OBJS)) $(LIB)

$(CARD_IDS_STAMP): $(CARD_DATA_MANIFEST) $(CARD_ART_GENERATOR)
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR) --card-ids
	touch $@

$(CARD_IDS_GENERATED): $(CARD_IDS_STAMP)
	@test -f $@

$(CARD_GENERATED_STAMP): $(CARD_DATA_MANIFEST) $(CARD_ART_GENERATOR) configs/runtime.c $(CUSTOM_CARD_80_HUFFS) $(CUSTOM_CARD_80_PALETTES) $(CUSTOM_CARD_24_LZS) $(CARD_IDS_GENERATED)
	@mkdir -p $(dir $@)
	python3 $(CARD_ART_GENERATOR)
	touch $@

$(CARD_DESCRIPTION_GENERATED) $(CARD_ART_GENERATED) $(CARD_DATA_GENERATED_SRC) $(CARD_TRUNK_GENERATED) $(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED): $(CARD_GENERATED_STAMP)
	@test -f $@

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c $(CARD_IDS_GENERATED) | $(CARD_IDS_STAMP) tools/preproc/preproc
	$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/$*.i
	@$(PREPROC) $(C_BUILDDIR)/$*.i charmap.txt | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo ".text\\n\\t.align\\t2, 0\\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) $(C_BUILDDIR)/$*.s -o $@

$(C_BUILDDIR)/card.o: $(CARD_RENDER_ASSETS)
$(C_BUILDDIR)/hooks/card_asset_hooks.o: $(CARD_ART_GENERATED)
$(C_BUILDDIR)/hooks/card_hooks.o: $(CARD_ART_GENERATED)
$(C_BUILDDIR)/hooks/effect_text_hooks.o: $(CARD_ACTIVATION_TEXT_GENERATED) $(CARD_ACTIVATION_TEXT_LOOKUP_GENERATED)
$(C_BUILDDIR)/hooks/event_system_hooks.o: $(EVENT_REPLACEMENTS_GENERATED)
$(C_BUILDDIR)/hooks/generated/card_data_hooks.o: $(CARD_ART_GENERATED) $(CARD_DESCRIPTION_GENERATED)
$(C_BUILDDIR)/hooks/trunk_hooks.o: $(CARD_TRUNK_GENERATED)
$(C_BUILDDIR)/overworld/entities/entities.o: $(OVERWORLD_ENTITY_TILES) src/overworld/entities/palette.gbapal
$(C_BUILDDIR)/hooks/overworld_hooks.o: $(THOUGHT_BUBBLE_DUMPS) $(THOUGHT_BUBBLE_PALETTES)

$(CONFIGS_BUILDDIR)/%.o: $(CONFIGS_SUBDIR)/%.c $(CARD_IDS_GENERATED) | $(CARD_IDS_STAMP) tools/preproc/preproc
	$(CPP) $(CPPFLAGS) $< -o $(CONFIGS_BUILDDIR)/$*.i
	@$(PREPROC) $(CONFIGS_BUILDDIR)/$*.i charmap.txt | $(CC1) $(CFLAGS) -o $(CONFIGS_BUILDDIR)/$*.s
	@echo ".text\\n\\t.align\\t2, 0\\n" >> $(CONFIGS_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) $(CONFIGS_BUILDDIR)/$*.s -o $@

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

$(DATA_ASM_BUILDDIR)/%.o: $(DATA_ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

validate-lynjump:
	python3 tools/validate_lynjump.py

clean: clean-tools clean-graphics
	rm -f $(ROM) $(UPS) $(ELF) $(MAP)
	rm -r $(BUILD_DIR)/

compare: all
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: graphics-rules tools-rules validate-lynjump
