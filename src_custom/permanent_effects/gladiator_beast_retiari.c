#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 OpponentFixedDuelistForTurnDuelist(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  return fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
}

static u8 OpponentGyHasCard(u8 turnDuelist)
{
  u8 oppFixed = OpponentFixedDuelistForTurnDuelist(turnDuelist);

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[oppFixed].graveyard != CARD_NONE;

  return GraveyardExpand_GetCount(oppFixed) > 0;
}

static u8 BanishOneFromOpponentGy(u8 turnDuelist)
{
  u8 oppFixed = OpponentFixedDuelistForTurnDuelist(turnDuelist);
  u8 turnDuelistOpp = turnDuelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[oppFixed].graveyard == CARD_NONE)
      return FALSE;

    Duel_BanishGraveyardTopTurn(turnDuelistOpp);
    return TRUE;
  }

  if (GraveyardExpand_GetCount(oppFixed) == 0)
    return FALSE;

  if (Duel_BanishGraveyardAtFixed(oppFixed, GraveyardExpand_GetCount(oppFixed) - 1) == CARD_NONE)
    return FALSE;

  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

unsigned char ShouldActivateGLADIATOR_BEAST_RETIARI(void)
{
  struct DuelCard *zone;
  u8 turnDuelist;

  if (gActiveEffect.cardId != GLADIATOR_BEAST_RETIARI)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  turnDuelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return OpponentGyHasCard(turnDuelist);
}

void ActivateGLADIATOR_BEAST_RETIARI(void)
{
  struct DuelCard *zone;
  u8 turnDuelist;

  turnDuelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_RETIARI, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (!BanishOneFromOpponentGy(turnDuelist))
    return;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  /* ponytail: GB tag-out after battle needs battle-end hook. */
}
