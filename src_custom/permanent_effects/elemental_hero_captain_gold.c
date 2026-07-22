#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "constants/custom_field_spells.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

static u8 SkyscraperIsOnField(void)
{
  return gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_SKYSCRAPER;
}

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

static u8 AddSkyscraperFromDeckToHand(void)
{
  u8 fixedDuelist;
  s16 deckIndex;
  s8 handZone;
  u16 cardId;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, SKYSCRAPER);
  if (deckIndex < 0)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)(handZone)), cardId);
  return TRUE;
}

u8 CanActivateElementalHeroCaptainGoldFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ELEMENTAL_HERO_CAPTAIN_GOLD)
    return FALSE;

  /* With Skyscraper active, prefer normal summon as a 2100 beater. Hand/field
   * Skyscraper search + destroy wired above. */
  if (SkyscraperIsOnField())
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, SKYSCRAPER) >= 0;
}

u8 TryActivateElementalHeroCaptainGoldFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateElementalHeroCaptainGoldFromHand(handZone))
    return FALSE;

  Duel_ShowCardEffectText(ELEMENTAL_HERO_CAPTAIN_GOLD,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_CAPTAIN_GOLD_POPUP_1);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  AddSkyscraperFromDeckToHand();
  return TRUE;
}

unsigned char ShouldActivateElementalHeroCaptainGold(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ELEMENTAL_HERO_CAPTAIN_GOLD)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_CAPTAIN_GOLD)
    return FALSE;

  if (!zone->isFaceUp)
    return FALSE;

  return !SkyscraperIsOnField();
}

void ActivateElementalHeroCaptainGold(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  u8 graveyardDuelist;

  Duel_ShowCardEffectText(ELEMENTAL_HERO_CAPTAIN_GOLD,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_CAPTAIN_GOLD_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  graveyardDuelist = (gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;

  Duel_DestroyZone(zone, graveyardDuelist, TRUE);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroCaptainGold_SelfCheck(void)
{
  u8 savedField = gActiveCustomFieldSpellId;

  gActiveCustomFieldSpellId = CUSTOM_FIELD_SPELL_NONE;
  if (SkyscraperIsOnField())
    __builtin_trap();

  gActiveCustomFieldSpellId = CUSTOM_FIELD_SPELL_SKYSCRAPER;
  if (!SkyscraperIsOnField())
    __builtin_trap();

  gActiveCustomFieldSpellId = savedField;
}
#endif
