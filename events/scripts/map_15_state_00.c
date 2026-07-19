#include "event_macros.h"
#include "overworld.h"
#include "constants/music_ids.h"

/* map_15_state_00: map 15 state 0 */

EVENT_SCRIPT_REPLACEMENT(0x08F04064, map_15_state_00_08F04064, 0x08F04244, EVENT_NOP)
  SET_FLAG(EVENT_FLAG_LEAVING_THE_DUEL_EXPRESS_LEADS_TO_DOMINO_STATION)
  FALLTHROUGH()
END_EVENT_SCRIPT()
