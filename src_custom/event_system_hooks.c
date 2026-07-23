#include "global.h"
#include "event_system.h"
#include "configs/runtime.h"
#include "debug_save_anywhere.h"
#include "overworld.h"
#include "overworld_debug_overlay.h"
#include "cg.h"

#include "generated/event_script_replacements.inc"

extern const u32 g82AD2D0[];
extern u16 g82AD48C[];

void sub_80526D0__Replacement(struct ScriptCtx *scriptCtx);
void sub_804EEE0(void);
void OverworldSetRegDispcnt(void);

/* Map 25 dealer/patron A+R scripts replaced for Blackjack/Concentration. */
static const u32 sCasinoMinigameScriptAddrs[] APPEND_RODATA = {
  0x08E99588, 0x08E99594, 0x08E995A0, 0x08E995AC, /* state 01 */
  0x08E995B8, 0x08E995DC, 0x08E995E8, 0x08E995F4, /* state 02 */
  0x08E99600, 0x08E9960C, 0x08E99618,             /* state 03 */
};

static u8 CasinoMinigameScript_IsGated(const struct Script *script) {
  unsigned i;

  for (i = 0; i < ARRAY_COUNT(sCasinoMinigameScriptAddrs); i++)
    if ((u32)script == sCasinoMinigameScriptAddrs[i])
      return TRUE;
  return FALSE;
}

const struct Script *EventSystem_ResolveScript(const struct Script *script) {
  unsigned i;

  if (gRuntimeConfig.enable_custom_events != TRUE)
    return script;

  for (i = 0; i < gEventScriptReplacementCount; i++) {
    if (gEventScriptReplacements[i].vanilla != script)
      continue;
    if (CasinoMinigameScript_IsGated(script) == TRUE &&
        gRuntimeConfig.enable_casino_minigames != TRUE)
      return script; /* keep vanilla dialogue */
    return gEventScriptReplacements[i].replacement;
  }

  return script;
}

struct Script *EventSystem_GetHouseSavePromptScript(void) {
  return &sEventScript_map_09_state_00_08E621E4Node;
}

LYN_REPLACE_CHECK(InitiateScript);
void InitiateScript__Replacement(struct Script *script) {
  struct ScriptCtx scriptCtx;
  bool8 saveAnywhereDialog = (gDebugSaveAnywherePendingCapture == TRUE);

  script = (struct Script *)EventSystem_ResolveScript(script);

  EventCg_ForceClose();
  LZ77UnCompWram(g82AD2D0, (void *)gBgVram.sbb1B);
  CpuCopy16(g82AD48C, (void *)gBgVram.sbb1D, 0x500);
  REG_BLDCNT = 0;
  REG_BLDALPHA = 0;
  REG_BLDY = 0;

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk1E = 0;
  scriptCtx.unk8 = 0;
  scriptCtx.unkC = 0;
  scriptCtx.unkD = 1;
  scriptCtx.unk1C = 0;
  scriptCtx.unk78 = 0;
  scriptCtx.unk74 = 0;
  scriptCtx.unk76 = 0;
  scriptCtx.unk7A = 0x1D;
  scriptCtx.unk7C = 1;
  scriptCtx.unk7E = 3;
  scriptCtx.unk80 = 1;
  scriptCtx.unk82 = 0;
  scriptCtx.unk86 = 0;
  /* No CallThumb into statics — MyBoy dies on that pattern. */
  SetCurrentScript(&scriptCtx, script);
  sub_80532A8(&scriptCtx);
  sub_80526D0__Replacement(&scriptCtx);

  if (saveAnywhereDialog != TRUE)
    DebugSaveAnywhere_ApplySavedCoords();

  if (saveAnywhereDialog == TRUE) {
    gDebugSaveAnywherePendingCapture = FALSE;
    OverworldLoadGraphics();
    sub_804EEE0();
  } else {
    EventCg_ForceClose();
    /* Exit scripts fade to black then set MAP_TRANSITION; clearing blend
     * here would flash the old map before OverworldLoadGraphics. */
    if (!(gOverworld.flags & OVERWORLD_FLAG_MAP_TRANSITION)) {
      OverworldOverlay_RestoreDisplayRegs();
      OverworldSetRegDispcnt();
    }
  }

  if (gRuntimeConfig.show_player_screen_pixel_coords == TRUE && saveAnywhereDialog != TRUE)
    OverworldOverlay_Refresh();

  scriptCtx.portraitId = PORTRAIT_NONE;
  scriptCtx.pointer = 0;
  scriptCtx.unk8 = 0;
}
