#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 TurnDuelistFromGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 MonsterRowForTurnDuelist(u8 turnDuelist)
{
  return turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 HandHasCardId(u8 turnDuelist, u16 cardId)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == cardId)
      return TRUE;
  }

  return FALSE;
}


static u8 MatchDarkMagician(u16 cardId)
{
  return cardId == DARK_MAGICIAN;
}

static u8 MatchDarkMagicianGirl(u16 cardId)
{
  return cardId == DARK_MAGICIAN_GIRL;
}

static u8 CanSpecialSummonFromAnywhere(u8 turnDuelist, u16 cardId)
{
  if (HandHasCardId(turnDuelist, cardId))
    return TRUE;

  if (Duel_FindDeckCardIndex(turnDuelist, cardId) >= 0)
    return TRUE;

  if (GraveyardExpand_IsEnabled()) {
    u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
    u8 i;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId)
        return TRUE;
    }
  } else if (gTurnDuelistBattleState[turnDuelist]->graveyard == cardId) {
    return TRUE;
  }

  return FALSE;
}

static u8 TrySpecialSummonOne(u8 turnDuelist, u16 cardId, u8 (*handPred)(u16))
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 monsterRow = MonsterRowForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  if (HandHasCardId(turnDuelist, cardId)) {
    if (Duel_SpecialSummonFromHand(turnDuelist, cardId, handPred, opts) == DUEL_ACTION_OK)
      return TRUE;
  }

  if (Duel_FindDeckCardIndex(turnDuelist, cardId) >= 0) {
    if (Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts) == DUEL_ACTION_OK)
      return TRUE;
  }

  if (Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts) == DUEL_ACTION_OK)
    return TRUE;

  return FALSE;
}

static u8 CanSpecialSummonDarkMagicianPair(u8 turnDuelist)
{
  u8 monsterRow = MonsterRowForTurnDuelist(turnDuelist);
  u8 emptyZones = NumEmptyZonesInRow(gTurnZones[monsterRow]);
  u8 canDm;
  u8 canDmg;

  if (emptyZones == 0)
    return FALSE;

  canDm = CanSpecialSummonFromAnywhere(turnDuelist, DARK_MAGICIAN);
  canDmg = CanSpecialSummonFromAnywhere(turnDuelist, DARK_MAGICIAN_GIRL);

  if (emptyZones >= 2)
    return canDm || canDmg;

  return canDm || canDmg;
}

static u8 IsDarkMagiciansGraveyardTrigger(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != THE_DARK_MAGICIANS)
    return FALSE;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != THE_DARK_MAGICIANS)
      return FALSE;
  } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != THE_DARK_MAGICIANS) {
    return FALSE;
  }

  return CanSpecialSummonDarkMagicianPair(turnDuelist);
}

unsigned char ShouldActivateTHE_DARK_MAGICIANS(void)
{
  /* ponytail: OPT draw on S/T activation needs chain/OPT hooks. */
  return IsDarkMagiciansGraveyardTrigger();
}

void ActivateTHE_DARK_MAGICIANS(void)
{
  u8 turnDuelist;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(THE_DARK_MAGICIANS, 8);
  if (IsDuelOver() == TRUE)
    return;

  GetGraveCardAndClearGrave(turnDuelist);

  TrySpecialSummonOne(turnDuelist, DARK_MAGICIAN, MatchDarkMagician);
  TrySpecialSummonOne(turnDuelist, DARK_MAGICIAN_GIRL, MatchDarkMagicianGirl);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  /* ponytail: Deck-first SS order; hand/GY picker not wired. */
}
