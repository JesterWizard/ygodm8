# This controls building executables in the `tools` folder.
# Can be invoked through the `Makefile` or standalone.

MAKEFLAGS += --no-print-directory

# Inclusive list. If you don't want a tool to be built, don't add it here.
TOOL_NAMES := gbagfx preproc

TOOLDIRS := $(TOOL_NAMES:%=tools/%)

tools-rules: tools/gbagfx/gbagfx tools/preproc/preproc

tools/gbagfx/gbagfx:
	@$(MAKE) -C tools/gbagfx

tools/preproc/preproc:
	@$(MAKE) -C tools/preproc

clean-tools:
	@$(foreach tooldir,$(TOOLDIRS),$(MAKE) clean -C $(tooldir);)
