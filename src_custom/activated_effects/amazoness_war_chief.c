#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAmazonessName[] APPEND_RODATA = "Amazoness";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FieldIsEmptyOrOnlyAmazoness(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (!Duel_IsAmazonessCard(zone->id))
      return FALSE;
  }

  return TRUE;
}

static u8 IsAmazonessSpellTrapOrPolymerization(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == POLYMERIZATION)
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName);
}

static u16 FindAmazonessSpellTrapOrPolymerizationInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAmazonessSpellTrapOrPolymerization(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 SetSpellTrapFromDeck(u16 cardId)
{
  s8 empty;
  s16 deckIndex;
  struct DuelCard *slot;

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  slot = gTurnZones[ACTIVE_DUELIST_BACKROW][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

unsigned char CanActivateAMAZONESS_WAR_CHIEF(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_WAR_CHIEF)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_WAR_CHIEF)
    return FALSE;

  /* OPT Set Amazoness S/T / Polymerization; Amazoness-only attack lock on activate. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) < 0)
    return FALSE;

  return FindAmazonessSpellTrapOrPolymerizationInDeck() != CARD_NONE;
}

void ActivateAMAZONESS_WAR_CHIEFEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cardId;

  Duel_ShowEffectTextTyped(AMAZONESS_WAR_CHIEF, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindAmazonessSpellTrapOrPolymerizationInDeck();
  if (cardId == CARD_NONE)
    return;

  if (!SetSpellTrapFromDeck(cardId))
    return;

  /* Amazoness-only attacks for rest of turn: lock non-Amazoness. */
  {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *own = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (own != NULL && own->id != CARD_NONE && !Duel_IsAmazonessCard(own->id))
        own->isLocked = TRUE;
    }
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonAmazonessWarChiefFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_WAR_CHIEF)
    return FALSE;

  if (!FieldIsEmptyOrOnlyAmazoness())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessWarChiefFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonAmazonessWarChiefFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_WAR_CHIEF, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAmazonessWarChiefFromHand(u8 handZone);
u8 TrySpecialSummonAmazonessWarChiefFromHand(u8 handZone);
#endif
