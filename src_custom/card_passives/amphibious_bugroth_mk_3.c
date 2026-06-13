#include "global.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "amphibious_bugroth_mk_3.h"

u8 CanAmphibiousBugrothMk3AttackDirectly(u16 cardId) {
  return cardId == AMPHIBIOUS_BUGROTH_MK_3 && gDuel.field == FIELD_UMI;
}
