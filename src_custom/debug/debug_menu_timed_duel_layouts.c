#include "global.h"
#include "configs/runtime.h"
#include "timed_duel.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "debug_menu_timed_duel_macros.h"

/* One struct TimedDuelLayout per puzzle. Board rows: opponent backrow, opponent monsters,
 * player monsters, player backrow (see FixedRow in include/duel.h).
 * hands[0] = player, hands[1] = opponent. graveyard[*] = bottom-to-top stacks (CARD_NONE padded). */

const struct TimedDuelLayout sTimedDuelLayout_01 APPEND_RODATA = {
  {
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK(BLUE_EYES_WHITE_DRAGON), TD_ATK(BLUE_EYES_WHITE_DRAGON), TD_ATK(BLUE_EYES_WHITE_DRAGON), TD_EMPTY, TD_EMPTY },
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
  3000,
  9000,
  FIELD_NONE,
  0,
  BLUE_EYES_SHINING_DRAGON,
};

const struct TimedDuelLayout sTimedDuelLayout_02 APPEND_RODATA = {
  {
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_ATK_STAGE(EXODIA_NECROSS, 4), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { TD_FACEUP(MONSTER_REBORN), TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
    { TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY, TD_EMPTY },
  },
  {
    { CARD_NONE },
    { EXODIA_THE_FORBIDDEN_ONE, CARD_NONE },
  },
  1000,
  1000,
  FIELD_NONE,
  0,
  THE_UNSTOPPABLE_EXODIA_INCARNATE,
};
