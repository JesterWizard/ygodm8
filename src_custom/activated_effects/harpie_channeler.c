#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpie_channeler.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (!IsHarpieCard(cardId) || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return TRUE;
}

static u8 HandHasHarpieCard(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsHarpieCard(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsDiscardableHarpieCard(u16 cardId)
{
  return IsHarpieCard(cardId);
}

static u16 FindOtherHarpieMonsterInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsHarpieMonster(cardId) && cardId != HARPIE_CHANNELER
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

u8 HarpieChanneler_TreatsNameAsHarpieLady(const struct DuelCard *zone)
{
  /* Printed: name becomes Harpie Lady while on the field or in the GY. */
  return zone != NULL && zone->id == HARPIE_CHANNELER;
}

/* Attack-position summons often keep isFaceUp=0 until EOT flip. */
static u8 MonsterCountsAsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControllerHasFaceUpDragon(const struct DuelCard *channeler)
{
  u8 fixedRow;
  u8 col;
  u8 selfCol;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)channeler, &fixedRow, &selfCol))
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (!MonsterCountsAsFaceUp(zone) || zone == channeler)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.type == TYPE_DRAGON)
      return TRUE;
  }

  return FALSE;
}

void HarpieChanneler_ApplyLevelToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != HARPIE_CHANNELER)
    return;

  if (!ControllerHasFaceUpDragon(zone))
    return;

  gCardInfo.level = 7;
}

unsigned char CanActivateHARPIE_CHANNELER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HARPIE_CHANNELER)
    return FALSE;

  zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HARPIE_CHANNELER)
    return FALSE;

  /* OPT: discard 1 Harpie; SS 1 other Harpie from Deck in face-up DEF.
   * Level→7 while controlling a Dragon is continuous (not this ignition). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!HandHasHarpieCard())
    return FALSE;

  return FindOtherHarpieMonsterInDeck() != CARD_NONE;
}

void ActivateHARPIE_CHANNELEREffect(void)
{
  struct DuelCard *self = gFixedZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(HARPIE_CHANNELER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!HandHasHarpieCard() || FindOtherHarpieMonsterInDeck() == CARD_NONE
      || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, IsDiscardableHarpieCard, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  cardId = FindOtherHarpieMonsterInDeck();
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
