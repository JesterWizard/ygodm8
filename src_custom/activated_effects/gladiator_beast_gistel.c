#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";
static const char sGladiatorName[] APPEND_RODATA = "Gladiator";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 IsGladiatorSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorName);
}

static u16 FindGladiatorSpellTrapInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindOtherGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 CanTagOut(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindOtherGladiatorBeastInDeck(GLADIATOR_BEAST_GISTEL) != CARD_NONE;
}

static void ShuffleSelfTagOut(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 tagId;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  tagId = FindOtherGladiatorBeastInDeck(GLADIATOR_BEAST_GISTEL);
  if (tagId == CARD_NONE)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, tagId, opts);
}

static u8 CanSearch(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindGladiatorSpellTrapInDeck() != CARD_NONE;
}

static s8 FindOtherGladiatorBeastHandZone(u8 excludeZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == excludeZone)
      continue;

    if (IsGladiatorBeastMonster(
            SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return (s8)i;
  }

  return -1;
}

unsigned char CanActivateGLADIATOR_BEAST_GISTEL(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_GISTEL)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_GISTEL)
    return FALSE;

  /* ponytail: on-GB-SS search + end-BP battled tag gate need summon/battle hooks.
   * Ceiling: OPT search Gladiator S/T, else tag-out. FromHand: reveal+SS both. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSearch() || CanTagOut();
}

void ActivateGLADIATOR_BEAST_GISTELEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_GISTEL, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSearch()) {
    searchId = FindGladiatorSpellTrapInDeck();
    if (searchId == CARD_NONE)
      return;

    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanTagOut())
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfTagOut(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonGladiatorBeastGistelFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 otherZone;

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GLADIATOR_BEAST_GISTEL)
    return FALSE;

  otherZone = FindOtherGladiatorBeastHandZone(handZone);
  if (otherZone < 0)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Need two empty monster zones for both. */
  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 2;
}

u8 TrySpecialSummonGladiatorBeastGistelFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  s8 otherZone;
  u8 gistelZone = handZone;

  if (!CanSpecialSummonGladiatorBeastGistelFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_GISTEL, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  otherZone = FindOtherGladiatorBeastHandZone(handZone);
  if (otherZone < 0)
    return FALSE;

  /* SS other GB first so gistel hand index stays stable if lower. */
  if ((u8)otherZone < gistelZone)
    gistelZone--;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)otherZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], gistelZone)->id
      != GLADIATOR_BEAST_GISTEL) {
    u8 i;
    u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

    gistelZone = 0xFF;
    for (i = 0; i < max; i++) {
      if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id
          == GLADIATOR_BEAST_GISTEL) {
        gistelZone = i;
        break;
      }
    }
    if (gistelZone == 0xFF)
      return FALSE;
  }

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, gistelZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGladiatorBeastGistelFromHand(u8 handZone);
u8 TrySpecialSummonGladiatorBeastGistelFromHand(u8 handZone);
#endif
