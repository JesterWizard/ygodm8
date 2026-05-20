#include "global.h"
#include "common-chax.h"
#include "thought_bubble.h"

extern unsigned char gFlags[];
extern u8 g8E0FD44[];

static u16 sLatestThoughtBubbleEventFlag APPEND_DATA = THOUGHT_BUBBLE_EVENT_FLAG_NONE;

u16 GetLatestThoughtBubbleEventFlag(void) {
  return sLatestThoughtBubbleEventFlag;
}

LYN_REPLACE_CHECK(InitFlags);
void InitFlags__Replacement(void) {
  u8 i;

  for (i = 0; i < 50; i++)
    gFlags[i] = 0;

  sLatestThoughtBubbleEventFlag = THOUGHT_BUBBLE_EVENT_FLAG_NONE;
}

LYN_REPLACE_CHECK(SetFlag);
void SetFlag__Replacement(u32 flag) {
  if (flag >= 400)
    return;

  gFlags[flag >> 3] |= g8E0FD44[flag & 7];
  sLatestThoughtBubbleEventFlag = (u16)flag;
}
