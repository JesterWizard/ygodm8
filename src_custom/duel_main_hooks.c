#include "global.h"
#include "common-chax.h"
#include "duel.h"
#include "duel_main.h"

void sub_8041C94(u8 *, u16, u16, u16, u16);

LYN_REPLACE_CHECK(DisplayDuelText);
void DisplayDuelText__Replacement(struct DuelText *arg0) {
  if (arg0->textId == 0xFF)
    return;

  sub_8041C94(gDuelTextStrings[arg0->textId], arg0->unk0, arg0->unk2, arg0->rewardAmount, 0);
}
