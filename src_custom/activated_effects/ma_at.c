#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsLightType(u16 cardId, u8 monsterType)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, monsterType))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_LIGHT;
}

static struct DuelCard *FindLightTypeMonster(u8 monsterType, struct DuelCard *skip)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == skip || zone->id == CARD_NONE)
      continue;

    if (IsLightType(zone->id, monsterType))
      return zone;
  }

  return NULL;
}

static u8 DeckCardsRemaining(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  if (deckSize <= top)
    return 0;

  return (u8)(deckSize - top);
}

static void ExcavateTop3AddAnyMillRest(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 remaining = DeckCardsRemaining();
  u8 peek = remaining < 3 ? remaining : 3;
  u16 excavated[3];
  u8 i;
  u8 turnDuelist;

  for (i = 0; i < peek; i++)
    excavated[i] = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn + i];

  for (i = 0; i < peek; i++) {
    u16 cardId = excavated[i];
    s16 deckIndex;
    s8 handZone;

    deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
    if (deckIndex < 0)
      continue;

    handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
    if (handZone >= 0) {
      /* name-3 declare UI missing; add any excavated as stand-in. */
      if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
        continue;

      InitHandSlotFromCard(
          SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
      continue;
    }

    if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
      continue;

    for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
      if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
        GraveyardExpand_PushTurn(turnDuelist, cardId);
        break;
      }
    }
  }
}

unsigned char CanActivateMA_AT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MA_AT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MA_AT)
    return FALSE;

  /* name-3 excavate UI hard. OPT reveal top 3, add any, mill rest. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return DeckCardsRemaining() > 0;
}

void ActivateMA_ATEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(MA_AT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (DeckCardsRemaining() == 0)
    return;

  ExcavateTop3AddAnyMillRest();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonMaAtFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelCard *dragon;
  struct DuelCard *fairy;

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MA_AT)
    return FALSE;

  dragon = FindLightTypeMonster(TYPE_DRAGON, NULL);
  if (dragon == NULL)
    return FALSE;

  fairy = FindLightTypeMonster(TYPE_FAIRY, dragon);
  if (fairy == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonMaAtFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *dragon;
  struct DuelCard *fairy;
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonMaAtFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MA_AT, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  dragon = FindLightTypeMonster(TYPE_DRAGON, NULL);
  fairy = FindLightTypeMonster(TYPE_FAIRY, dragon);
  if (dragon == NULL || fairy == NULL)
    return FALSE;

  ClearZoneAndSendMonToGraveyard2(dragon, fixedDuelist);
  ClearZoneAndSendMonToGraveyard2(fairy, fixedDuelist);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonMaAtFromHand(u8 handZone);
u8 TrySpecialSummonMaAtFromHand(u8 handZone);
#endif
