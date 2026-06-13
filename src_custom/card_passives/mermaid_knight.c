#include "global.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "mermaid_knight.h"
#include "the_dark_door.h"

void TryUnlockMermaidKnightForSecondAttack(struct DuelCard *attacker) {
  if (attacker == NULL)
    return;

  if (attacker->id != MERMAID_KNIGHT)
    return;

  if (gDuel.field != FIELD_UMI)
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}
