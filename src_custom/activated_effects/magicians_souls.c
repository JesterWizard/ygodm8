#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpellTrapCard(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 CountSendableSpellTraps(void)
{
  u8 count = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsSpellTrapCard(gTurnHands[ACTIVE_DUELIST][col]->id))
      count++;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsSpellTrapCard(gTurnZones[ACTIVE_DUELIST_BACKROW][col]->id))
      count++;
  }

  return count;
}

static u8 SendOneSpellTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][col];

    if (zone != NULL && IsSpellTrapCard(zone->id)) {
      if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone != NULL && IsSpellTrapCard(zone->id)) {
      if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 IsLevel6PlusSpellcaster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 6;
}

static s16 FindLevel6PlusSpellcasterDeckIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsLevel6PlusSpellcaster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 MillLevel6PlusSpellcasterFromDeck(void)
{
  s16 deckIndex = FindLevel6PlusSpellcasterDeckIndex();
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;
  u8 turnDuelist;

  if (deckIndex < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[(u8)deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist]) {
      GraveyardExpand_PushTurn(turnDuelist, cardId);
      break;
    }
  }

  return TRUE;
}

unsigned char CanActivateMAGICIANS_SOULS(void)
{
  struct DuelCard *zone;
  u8 sendable;

  if (gMonEffect.id != MAGICIANS_SOULS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAGICIANS_SOULS)
    return FALSE;

  /* ponytail: Continuous Spell placement + DM/DMG GY SS branch need placement/
   * GY hooks. Ceiling: OPT send 1–2 S/T from hand/field → draw that many. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  sendable = CountSendableSpellTraps();
  return sendable > 0;
}

void ActivateMAGICIANS_SOULSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 sendable;
  u8 toSend;
  u8 sent = 0;

  Duel_ShowEffectTextTyped(MAGICIANS_SOULS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  sendable = CountSendableSpellTraps();
  if (sendable == 0)
    return;

  toSend = sendable >= 2 ? 2 : 1;
  while (sent < toSend) {
    if (!SendOneSpellTrap())
      break;
    sent++;
    if (IsDuelOver() == TRUE)
      return;
  }

  if (sent == 0)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, sent, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonMagiciansSoulsFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MAGICIANS_SOULS)
    return FALSE;

  if (FindLevel6PlusSpellcasterDeckIndex() < 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonMagiciansSoulsFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonMagiciansSoulsFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MAGICIANS_SOULS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!MillLevel6PlusSpellcasterFromDeck())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonMagiciansSoulsFromHand(u8 handZone);
u8 TrySpecialSummonMagiciansSoulsFromHand(u8 handZone);
#endif
