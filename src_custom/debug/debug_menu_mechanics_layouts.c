#include "global.h"
#include "configs/runtime.h"
#include "timed_duel.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "debug_menu_timed_duel_macros.h"

/* Boss Cut-Ins: three monsters (tribute two for Yubel) + Yubel in hand. */

const struct TimedDuelLayout sMechanicsLayout_01 APPEND_RODATA = {
  {
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK(KURIBOH), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK(MYSTICAL_ELF), TD_ATK(MYSTICAL_ELF), TD_ATK(MYSTICAL_ELF), TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { TD_ATK(YUBEL), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { CARD_NONE },
    { CARD_NONE },
  },
  8000,
  1000,
  FIELD_NONE,
  0,
  0,
  CARD_NONE,
};

/* Type Elements: Kuriboh (Shadow) vs Blue-Eyes (Light); LP so a direct attack finishes. */

const struct TimedDuelLayout sMechanicsLayout_02 APPEND_RODATA = {
  {
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK(BLUE_EYES_WHITE_DRAGON), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK(KURIBOH), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { CARD_NONE },
    { CARD_NONE },
  },
  8000,
  300,
  FIELD_NONE,
  0,
  2,
  CARD_NONE,
};
