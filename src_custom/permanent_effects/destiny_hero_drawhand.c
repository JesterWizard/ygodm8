#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 OpponentDuelist(u8 duelist)
{
  return duelist == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 DeckHasCard(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);

  return deckSize > gDuelDecks[fixedDuelist].cardsDrawn;
}

static u8 CanPlayerDrawOne(u8 turnDuelist)
{
  return DeckHasCard(turnDuelist)
      && FirstEmptyZoneInRow(gTurnHands[turnDuelist]) >= 0;
}

static u8 CanBothPlayersDrawOne(void)
{
  u8 duelist;
  u8 opp;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  opp = OpponentDuelist(duelist);

  return CanPlayerDrawOne(duelist) || CanPlayerDrawOne(opp);
}

unsigned char ShouldActivateDESTINY_HERO_DRAWHAND(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != DESTINY_HERO_DRAWHAND)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  /* ponytail: next Standby GY revive via TryApplyDestinyHeroDrawhandStandby. */
  return CanBothPlayersDrawOne();
}

void ActivateDESTINY_HERO_DRAWHAND(void)
{
  u8 duelist;
  u8 opp;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  opp = OpponentDuelist(duelist);

  Duel_ShowEffectTextTyped(DESTINY_HERO_DRAWHAND, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (CanPlayerDrawOne(duelist))
    Duel_DrawCards(duelist, 1, FALSE);

  if (CanPlayerDrawOne(opp))
    Duel_DrawCards(opp, 1, FALSE);

  UpdateDuelGfxExceptField();

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: HERO-effect SS gate not checked; on-summon mutual draw stand-in. */
}
