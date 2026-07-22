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

static u8 IsFaceUpMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != OPPONENT_MONSTER_ROW && fixedRow != PLAYER_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!IsCardFaceUp(zone) && zone->isDefending)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasFaceUpMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonsterTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ReturnMonsterToDeck(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist;
  u16 cardId;

  if (!IsFaceUpMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  fixedDuelist = (fixedRow == PLAYER_MONSTER_ROW) ? DUEL_PLAYER : DUEL_OPPONENT;
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

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= OPPONENT_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonsterTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpMonsterTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateCASTEL_THE_SKY_BLASTER_MUSKETEER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CASTEL_THE_SKY_BLASTER_MUSKETEER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CASTEL_THE_SKY_BLASTER_MUSKETEER)
    return FALSE;

  /* Ceiling: detach/material + face-down branch need overlay engine. Ceiling:
   * OPT return 1 face-up monster to the Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasFaceUpMonster();
}

void ActivateCASTEL_THE_SKY_BLASTER_MUSKETEEREffect(void)
{
  Duel_ShowEffectTextTyped(CASTEL_THE_SKY_BLASTER_MUSKETEER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpMonsterTarget, ReturnMonsterToDeck, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
