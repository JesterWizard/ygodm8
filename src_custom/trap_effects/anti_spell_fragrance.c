#include "global.h"
#include "common-chax.h"
#include "anti_spell_fragrance.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static void ActivateANTI_SPELL_FRAGRANCEZone(struct DuelCard *zone)
{
  if (Duel_ActivateContinuousTrapPreamble(zone, ANTI_SPELL_FRAGRANCE) == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateANTI_SPELL_FRAGRANCEOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ANTI_SPELL_FRAGRANCE, ActivateANTI_SPELL_FRAGRANCEZone);
}

u8 AntiSpellFragrance_BlocksSpellActivation(struct DuelCard *spellZone)
{
  u8 row;
  u8 col;

  if (spellZone == NULL || spellZone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(spellZone->id) != TYPE_GROUP_SPELL)
    return FALSE;

  if (Duel_FindBackrowCard(DUEL_PLAYER, ANTI_SPELL_FRAGRANCE, TRUE) == NULL
      && Duel_FindBackrowCard(DUEL_OPPONENT, ANTI_SPELL_FRAGRANCE, TRUE) == NULL)
    return FALSE;

  /* Face-down Set Spells on backrow may activate. Continuous face-up re-activate OK. */
  if (Duel_FindFixedZone(spellZone, &row, &col)) {
    if (row == PLAYER_BACKROW || row == OPPONENT_BACKROW) {
      if (spellZone->isFaceUp == FALSE)
        return FALSE;
      if (spellZone->isLocked)
        return FALSE;
    }
  }

  /* Printed remainder omitted by this ruleset. */
  return TRUE;
}
