#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGladiatorBeast(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static void ActivateGLADIATOR_NAUMACHIAZone(struct DuelCard *zone)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;
  u8 hasGb = FALSE;
  struct DuelCard *boost = NULL;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 shuffled = FALSE;
  u8 i;

  if (Duel_ActivateContinuousTrapPreamble(zone, GLADIATOR_NAUMACHIA)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: forced attack + destroy-search GB from Deck need battle/destroy
   * hooks. Ceiling: if GB on field, mark opp must-attack; shuffle 1 GB from
   * hand/GY and boost 1 GB by +1 stage (~original DEF stand-in). */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && IsGladiatorBeast(m->id)) {
      hasGb = TRUE;
      boost = m;
      break;
    }
  }

  if (!hasGb)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[oppRow][col];

    if (m != NULL && m->id != CARD_NONE) {
      m->isFaceUp = TRUE;
      m->isDefending = FALSE;
      m->unk4 |= 1; /* must attack */
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && IsGladiatorBeast(gTurnHands[INACTIVE_DUELIST][i]->id)) {
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      shuffled = TRUE;
      break;
    }
  }

  if (!shuffled && GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsGladiatorBeast(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
        GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
        shuffled = TRUE;
        break;
      }
    }
  }

  if (shuffled && boost != NULL)
    IncrementPermStage(boost);

  UpdateDuelGfxExceptField();
}

void TryActivateGLADIATOR_NAUMACHIAOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GLADIATOR_NAUMACHIA,
                                         ActivateGLADIATOR_NAUMACHIAZone);
}

/* ponytail: TryActivateGLADIATOR_NAUMACHIAOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
