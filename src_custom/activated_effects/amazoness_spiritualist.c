#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

static struct DuelCard *FindBounceAmazoness(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || zone->id == AMAZONESS_SPIRITUALIST)
      continue;

    if (Duel_IsAmazonessCard(zone->id))
      return zone;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (Duel_IsAmazonessCard(zone->id))
      return zone;
  }

  return NULL;
}

static u8 BounceAmazonessToHand(struct DuelCard *zone)
{
  u8 typeGroup;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  if (typeGroup == TYPE_GROUP_MONSTER)
    return Duel_ReturnMonsterZoneToOwnerHand(zone, FALSE) == DUEL_ACTION_OK;

  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP) {
    s8 empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
    u16 cardId;

    if (empty < 0)
      return FALSE;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 AddPolymerizationFromDeck(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) < 0)
    return FALSE;

  return Duel_AddDeckCardToHand(ACTIVE_DUELIST, POLYMERIZATION, TRUE) == DUEL_ACTION_OK;
}

unsigned char CanActivateAMAZONESS_SPIRITUALIST(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_SPIRITUALIST)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_SPIRITUALIST)
    return FALSE;

  /* Field OPT add Polymerization from Deck.
   * Ceiling: hand/GY bounce→SS + ED lock need GY/ED hooks. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0;
}

void ActivateAMAZONESS_SPIRITUALISTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AMAZONESS_SPIRITUALIST, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!AddPolymerizationFromDeck())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonAmazonessSpiritualistFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AMAZONESS_SPIRITUALIST)
    return FALSE;

  if (FindBounceAmazoness() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonAmazonessSpiritualistFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *bounce;

  if (!CanSpecialSummonAmazonessSpiritualistFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AMAZONESS_SPIRITUALIST, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  bounce = FindBounceAmazoness();
  if (bounce == NULL)
    return FALSE;

  if (!BounceAmazonessToHand(bounce))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  /* Prefer: after SS, OPT search Polymerization when available. */
  AddPolymerizationFromDeck();

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonAmazonessSpiritualistFromHand(u8 handZone);
u8 TrySpecialSummonAmazonessSpiritualistFromHand(u8 handZone);
#endif
