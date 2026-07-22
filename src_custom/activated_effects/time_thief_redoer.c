#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void ShuffleDeckForFixedDuelist(u8 fixedDuelist)
{
  u8 turnDuelist;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    turnDuelist = ACTIVE_DUELIST;
  else
    turnDuelist = INACTIVE_DUELIST;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

static u8 IsOppFaceUpMonster(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 OppHasFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppFaceUpMonster(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static void ResolveReturnToDeck(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist;
  u16 cardId;

  if (!IsOppFaceUpMonster(fixedRow, fixedCol) || zone == NULL)
    return;

  fixedDuelist = (gTurnDuelistBattleState[INACTIVE_DUELIST]
                  == &gDuel.duelistbattleState[DUEL_PLAYER])
                     ? DUEL_PLAYER
                     : DUEL_OPPONENT;
  cardId = zone->id;
  ClearZone(zone);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  ShuffleDeckForFixedDuelist(fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickBounce(u8 *outRow, u8 *outCol)
{
  u8 col;

  *outRow = INACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppFaceUpMonster(INACTIVE_DUELIST_MONSTER_ROW, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void DoDraw(struct DuelCard *self)
{
  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateTIME_THIEF_REDOER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TIME_THIEF_REDOER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TIME_THIEF_REDOER)
    return FALSE;

  /* detach materials + banish-until-EP FALSE.
   * Ceiling: OPT draw 1 OR return 1 face-up opp monster to Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (OppHasFaceUpMonster())
    return TRUE;

  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

void ActivateTIME_THIEF_REDOEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(TIME_THIEF_REDOER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (OppHasFaceUpMonster()) {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
    Duel_SetupPickZone(IsOppFaceUpMonster, ResolveReturnToDeck, CancelTargeting, AiPickBounce);

    if (WhoseTurn() == DUEL_PLAYER)
      Duel_EnterPickZoneTargeting();
    else
      Duel_ResolvePickZoneForAi();
    return;
  }

  DoDraw(self);
}
