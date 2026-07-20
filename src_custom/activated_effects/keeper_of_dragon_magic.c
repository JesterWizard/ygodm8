#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void FlipCardFaceDown(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sFusionName[] APPEND_RODATA = "Fusion";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsPolyOrFusionNormalSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  if (GetSpellType(cardId) != SPELL_TYPE_NORMAL)
    return FALSE;

  if (cardId == POLYMERIZATION)
    return TRUE;

  return Duel_CardNameContains(cardId, sFusionName);
}

static u16 FindPolyOrFusionInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0)
    return POLYMERIZATION;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsPolyOrFusionNormalSpell(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 HandHasDiscardable(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static s16 FindAnyMonsterGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static u8 CanDiscardAddPoly(void)
{
  if (!HandHasDiscardable())
    return FALSE;

  /* Discard frees a hand slot for the search. */
  return FindPolyOrFusionInDeck() != CARD_NONE;
}

static u8 CanSsGyFaceDown(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindAnyMonsterGyIndex() >= 0;
}

static u8 DoDiscardAddPoly(void)
{
  u16 cardId;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  if (IsDuelOver() == TRUE)
    return FALSE;

  cardId = FindPolyOrFusionInDeck();
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_AddDeckCardToHand(ACTIVE_DUELIST, cardId, TRUE) == DUEL_ACTION_OK;
}

static u8 DoSsGyFaceDown(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForActive();
  s8 emptyZone;
  s16 gyIndex;
  u16 cardId;
  enum DuelActionResult result;
  struct DuelCard *zone;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  gyIndex = FindAnyMonsterGyIndex();
  if (emptyZone < 0 || gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts);
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    opts.mode = DUEL_SUMMON_NORMAL_SET;
    result = Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  }

  if (result != DUEL_ACTION_OK)
    return FALSE;

  zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone];
  if (zone != NULL && zone->id != CARD_NONE) {
    zone->unk4 = 2;
    zone->isFaceUp = FALSE;
    zone->isDefending = TRUE;
    FlipCardFaceDown(zone);
  }

  return TRUE;
}

unsigned char CanActivateKEEPER_OF_DRAGON_MAGIC(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != KEEPER_OF_DRAGON_MAGIC)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != KEEPER_OF_DRAGON_MAGIC)
    return FALSE;

  /* ponytail: reveal Fusion Extra material-name SS FALSE; any GY face-down stand-in.
   * Ceiling: OPT discard → add Poly/Fusion Normal; else OPT SS any from GY face-down DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanDiscardAddPoly() || CanSsGyFaceDown();
}

void ActivateKEEPER_OF_DRAGON_MAGICEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(KEEPER_OF_DRAGON_MAGIC, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanDiscardAddPoly()) {
    if (!DoDiscardAddPoly())
      return;
  } else if (!DoSsGyFaceDown()) {
    return;
  }

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
