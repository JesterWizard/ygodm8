#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "gladiator_beast_battled.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

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

static u8 OwnGyHasOtherGladiatorBeast(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsGladiatorBeastMonster(cardId) && cardId != GLADIATOR_BEAST_DARIUS;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsGladiatorBeastMonster(cardId) && cardId != GLADIATOR_BEAST_DARIUS)
      return TRUE;
  }

  return FALSE;
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

static void MarkSummonedMonsterNegated(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= 0x80;
      return;
    }
  }
}

static enum DuelActionResult SpecialSummonGyGladiatorBeastNegated(u8 fixedDuelist)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsGladiatorBeastMonster(cardId) || cardId == GLADIATOR_BEAST_DARIUS)
      return DUEL_ACTION_NO_TARGET;

    if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) != DUEL_ACTION_OK)
      return DUEL_ACTION_NO_TARGET;

    MarkSummonedMonsterNegated(cardId);
    return DUEL_ACTION_OK;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsGladiatorBeastMonster(cardId) || cardId == GLADIATOR_BEAST_DARIUS)
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      return DUEL_ACTION_NO_TARGET;

    MarkSummonedMonsterNegated(cardId);
    return DUEL_ACTION_OK;
  }

  return DUEL_ACTION_NO_TARGET;
}

static u8 CanTagOut(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindOtherGladiatorBeastInDeck(GLADIATOR_BEAST_DARIUS) != CARD_NONE;
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

  tagId = FindOtherGladiatorBeastInDeck(GLADIATOR_BEAST_DARIUS);
  if (tagId == CARD_NONE)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, tagId, opts);
  GladiatorBeast_MarkTagSummonedZone(tagId);
}

unsigned char CanActivateGLADIATOR_BEAST_DARIUS(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != GLADIATOR_BEAST_DARIUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_DARIUS)
    return FALSE;

  /* GB-tag SS revive + leave-field shuffle need summon/leave hooks. Ceiling: OPT
   * SS GB from GY negated; tag-out via GladiatorBeast_CanActivateTagOutEffect. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0
      && OwnGyHasOtherGladiatorBeast(fixedDuelist))
    return TRUE;

  if (!GladiatorBeast_CanActivateTagOutEffect(zone))
    return FALSE;

  return CanTagOut();
}

void ActivateGLADIATOR_BEAST_DARIUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_DARIUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0
      && OwnGyHasOtherGladiatorBeast(fixedDuelist)) {
    if (SpecialSummonGyGladiatorBeastNegated(fixedDuelist) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanTagOut() || !GladiatorBeast_CanActivateTagOutEffect(self))
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfTagOut(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
