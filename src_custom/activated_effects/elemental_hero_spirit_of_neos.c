#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sElementalHeroName[] APPEND_RODATA = "Elemental HERO";
static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sNeosName[] APPEND_RODATA = "Neos";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static u8 IsSearchTarget(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == POLYMERIZATION)
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  if (Duel_CardNameContains(cardId, sElementalHeroName))
    return TRUE;

  if (Duel_CardNameContains(cardId, sNeosName))
    return TRUE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u16 FindSearchTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0)
    return POLYMERIZATION;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsSearchTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 IsNormalElementalHero(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_IsElementalHeroCard(cardId))
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == NORMAL_CARD;
}

static u16 FindNormalElementalHeroInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsNormalElementalHero(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanShuffleSwap(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindNormalElementalHeroInDeck() != CARD_NONE;
}

static void ShuffleSelfSummonNormalHero(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;
  u16 summonId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  summonId = FindNormalElementalHeroInDeck();
  if (summonId == CARD_NONE)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, summonId, opts);
}

unsigned char CanActivateELEMENTAL_HERO_SPIRIT_OF_NEOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_SPIRIT_OF_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_SPIRIT_OF_NEOS)
    return FALSE;

  /* ponytail: attack-hand SS FALSE. Ceiling: OPT search Poly/E-HERO S/T, else
   * OPT shuffle self → SS Normal E-HERO from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0
      && FindSearchTargetInDeck() != CARD_NONE)
    return TRUE;

  return CanShuffleSwap();
}

void ActivateELEMENTAL_HERO_SPIRIT_OF_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_SPIRIT_OF_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  searchId = FindSearchTargetInDeck();
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0 && searchId != CARD_NONE) {
    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanShuffleSwap())
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfSummonNormalHero(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
