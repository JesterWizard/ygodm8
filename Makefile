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
ELF          := $(ROM:.gba=.elf)
MAP          := $(ROM:.gba=.map)
LDSCRIPT     := ldscript.ld

C_SRCS := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
HOOK_SRCS := $(wildcard $(C_SUBDIR)/hooks/*.c)
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

ALL_OBJS := $(C_OBJS) $(CONFIGS_OBJS) $(ASM_OBJS) $(DATA_ASM_OBJS) $(HOOK_OBJS)

SUBDIRS := $(sort $(dir $(ALL_OBJS)))


#### Recipes ####
$(shell mkdir -p $(SUBDIRS))

all: $(ROM)

include make_tools.mk
include graphics.mk

$(ROM): $(ELF) $(LYNJUMP_EVENTS) tools/apply_lynjump.py tools/validate_lynjump.py
	python3 tools/validate_lynjump.py
	$(OBJCOPY) -O binary --pad-to 0x9000000 $< $@
	python3 tools/apply_lynjump.py $(ELF) $@

$(ELF): $(ALL_OBJS) $(LDSCRIPT)
	cd $(BUILD_DIR) && $(LD) -T ../$(LDSCRIPT) -Map ../$(MAP) -o ../$@ $(patsubst $(BUILD_DIR)/%,%,$(ALL_OBJS)) $(LIB)

$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c | tools-rules graphics-rules
	$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/$*.i
	@$(PREPROC) $(C_BUILDDIR)/$*.i charmap.txt | $(CC1) $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo ".text\\n\\t.align\\t2, 0\\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) $(C_BUILDDIR)/$*.s -o $@

$(CONFIGS_BUILDDIR)/%.o: $(CONFIGS_SUBDIR)/%.c | tools-rules graphics-rules
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
	rm -f $(ROM) $(ELF) $(MAP)
	rm -r $(BUILD_DIR)/

compare: all
	sha1sum -c $(BUILD_NAME).sha1

.PHONY: graphics-rules tools-rules validate-lynjump
