#include "global.h"
#include "configs/runtime.h"
#include "event_system.h"
#include "gfx_reg_buffers.h"
#include "overworld.h"

typedef void (*VoidFunc)(void);

static inline void CallThumbVoid(u32 addr) {
  ((VoidFunc)(addr | 1))();
}

LYN_REPLACE_CHECK(StartCutscene);
APPEND_TEXT void StartCutscene__Replacement (unsigned char cutscene) {
  switch (cutscene) {
    case 0:
      CallThumbVoid(0x080009BC);
      break;
    case 1:
      CallThumbVoid(0x08001C70);
      break;
    case 2:
      CreditsMain();
      break;
    case 3:
      CallThumbVoid(0x08001B88);
      break;
    case 4:
      CallThumbVoid(0x08001BFC);
      break;
    case 5:
      CallThumbVoid(0x08001CE4);
      break;
    case 6:
      CallThumbVoid(0x08001DD4);
      break;
    case 7:
      CallThumbVoid(0x08001D58);
      break;
    case 8:
      /* Story queue marks map_09 complete once enter begins; block Joey replay FMV. */
      if (gStorySequenceCount != 0 && gStorySequenceProgress >= 1)
        break;
      if (gRuntimeConfig.skip_opening_sequence == TRUE)
        SetFlag(EVENT_FLAG_SAW_INTRO_CUTSCENE);
      else
        CallThumbVoid(0x08001AD8);
      break;
  }
  if (gRuntimeConfig.enable_custom_events == TRUE && gStorySequenceCount != 0)
    EventSystem_ApplyEnterFadeBlack();
  REG_DISPCNT = 0;
}
