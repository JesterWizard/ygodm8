#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
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

static u8 CountDeckGladiatorBeasts(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 count = 0;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      count++;
  }

  return count;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void SpecialSummonUpToTwoGladiatorBeasts(u16 excludeId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 summoned = 0;

  while (summoned < 2) {
    u8 fixedDuelist = FixedDuelistForActive();
    u8 deckSize = NumCardsInDeck(fixedDuelist);
    u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
    u16 cardId = CARD_NONE;
    u8 i;

    if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
      break;

    for (i = top; i < deckSize; i++) {
      u16 id = gDuelDecks[fixedDuelist].cards[i];

      if (IsGladiatorBeastMonster(id) && id != excludeId) {
        cardId = id;
        break;
      }
    }

    if (cardId == CARD_NONE)
      break;

    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
      break;

    summoned++;
    if (IsDuelOver() == TRUE)
      return;
  }
}

static u8 CanTagOut(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Self leaves the field — need at least 1 Deck GB; room opens on ClearZone. */
  return CountDeckGladiatorBeasts(GLADIATOR_BEAST_DOMITIANUS) > 0;
}

static void ShuffleSelfTagOut(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonUpToTwoGladiatorBeasts(GLADIATOR_BEAST_DOMITIANUS);
}

unsigned char CanActivateGLADIATOR_BEAST_DOMITIANUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_DOMITIANUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_DOMITIANUS)
    return FALSE;

  /* OPT tag-out → SS 1–2 GB from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanTagOut();
}

void ActivateGLADIATOR_BEAST_DOMITIANUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_DOMITIANUS, 2);

  if (self == NULL || IsDuelOver() == TRUE || !CanTagOut())
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfTagOut(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
