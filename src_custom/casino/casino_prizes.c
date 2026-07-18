#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "gba/types.h"

/* Stub prize pools — fill later. Primary for normal antes; secondary for low-level list. */

const u16 gCasinoPrizePoolPrimary[] APPEND_RODATA = {
  BLUE_EYES_WHITE_DRAGON,
  DARK_MAGICIAN,
  RED_EYES_B_DRAGON,
  SUMMONED_SKULL,
  GAIA_THE_FIERCE_KNIGHT,
};

const u16 gCasinoPrizePoolPrimaryCount APPEND_RODATA = 5;

const u16 gCasinoPrizePoolSecondary[] APPEND_RODATA = {
  SKULL_SERVANT,
  MYSTICAL_ELF,
  BEAVER_WARRIOR,
  CURSE_OF_DRAGON,
  GIANT_SOLDIER_OF_STONE,
};

const u16 gCasinoPrizePoolSecondaryCount APPEND_RODATA = 5;
