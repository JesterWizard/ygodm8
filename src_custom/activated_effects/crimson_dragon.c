#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sCrimsonDragonName[] APPEND_RODATA = "Crimson Dragon";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 MentionsCrimsonDragonSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sCrimsonDragonName);
}

static u16 FindCrimsonMentionInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (MentionsCrimsonDragonSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 FindDragonInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    if (!Duel_CardHasMonsterType(cardId, TYPE_DRAGON))
      continue;

    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

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

static u8 CanShuffleSelfSsDragon(struct DuelCard *self)
{
  (void)self;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindDragonInDeck() != CARD_NONE;
}

static void ShuffleSelfSsDragon(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 dragonId;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  dragonId = FindDragonInDeck();
  if (dragonId == CARD_NONE)
    return;

  /* Ceiling: Extra Deck Synchro SS FALSE; Deck Dragon stand-in. */
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, dragonId, opts);
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 AddCrimsonMentionFromDeckFor(u8 turnDuelist)
{
  u16 searchId;
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  for (i = top; i < deckSize; i++) {
    searchId = gDuelDecks[fixedDuelist].cards[i];
    if (!MentionsCrimsonDragonSpellTrap(searchId))
      continue;

    return Duel_AddDeckCardToHand(turnDuelist, searchId, TRUE) == DUEL_ACTION_OK;
  }

  return FALSE;
}

void TryCrimsonDragonOnMonsterPlacement(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != CRIMSON_DRAGON || !SummonModeIsSpecial(mode))
    return;

  if (EffectOpt_IsUsed(CRIMSON_DRAGON))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  Duel_ShowEffectTextTyped(CRIMSON_DRAGON, 8);

  if (!AddCrimsonMentionFromDeckFor(turnDuelist))
    return;

  EffectOpt_MarkUsed(CRIMSON_DRAGON);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateCRIMSON_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CRIMSON_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != CRIMSON_DRAGON)
    return FALSE;

  /* On-SS search via TryCrimsonDragonOnMonsterPlacement (EffectOpt).
   * OPT search mentioning Crimson Dragon S/T (shares EffectOpt).
   * Ceiling: Extra Deck Synchro SS FALSE; Deck Dragon stand-in. */
  if (!EffectOpt_IsUsed(CRIMSON_DRAGON)
      && FindCrimsonMentionInDeck() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0
      && CanUseMonsterEffect(zone))
    return TRUE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanShuffleSelfSsDragon(zone);
}

void ActivateCRIMSON_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(CRIMSON_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  searchId = FindCrimsonMentionInDeck();
  if (!EffectOpt_IsUsed(CRIMSON_DRAGON)
      && searchId != CARD_NONE
      && FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0) {
    if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
      return;

    EffectOpt_MarkUsed(CRIMSON_DRAGON);
    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanShuffleSelfSsDragon(self))
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfSsDragon(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
