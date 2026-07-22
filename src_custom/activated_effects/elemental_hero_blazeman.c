#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_blazeman.h"
#include "exchange_hand_selection.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);

#define BLAZEMAN_COPY_NONE 0xFF

void ClearElementalHeroBlazemanTurnState(void)
{
  gElementalHeroBlazemanCopySourceId = CARD_NONE;
  gElementalHeroBlazemanCopyRow = BLAZEMAN_COPY_NONE;
  gElementalHeroBlazemanCopyCol = BLAZEMAN_COPY_NONE;
}

void ElementalHeroBlazeman_OnZoneCleared(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_BLAZEMAN)
    return;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return;

  if (fixedRow != gElementalHeroBlazemanCopyRow || col != gElementalHeroBlazemanCopyCol)
    return;

  gElementalHeroBlazemanCopySourceId = CARD_NONE;
  gElementalHeroBlazemanCopyRow = BLAZEMAN_COPY_NONE;
  gElementalHeroBlazemanCopyCol = BLAZEMAN_COPY_NONE;
}

static u8 IsFaceUpBlazemanSummon(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_BLAZEMAN)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 IsHandElementalHero(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_IsElementalHeroCard(cardId);
}

static u8 HandHasElementalHero(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandElementalHero(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 FindBestHandHeroZone(struct DuelCard **handRow)
{
  s8 bestZone = -1;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = handRow[i]->id;
    u16 atk;

    if (!IsHandElementalHero(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestZone < 0 || atk > bestAtk) {
      bestZone = (s8)i;
      bestAtk = atk;
    }
  }

  return bestZone;
}

static u8 DiscardHandHeroForCopy(u16 *outCardId)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 zone;
  u16 cardId;

  if (WhoseTurn() == DUEL_PLAYER)
    zone = SelectHandCardMatchingPredicate(handRow, IsHandElementalHero);
  else
    zone = FindBestHandHeroZone(handRow);

  if (zone < 0)
    return FALSE;

  cardId = handRow[zone]->id;
  ClearZoneAndSendMonToGraveyard(handRow[zone], ACTIVE_DUELIST);

  if (outCardId != NULL)
    *outCardId = cardId;

  return IsDuelOver() != TRUE;
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

static u8 AddPolymerizationFromDeck(u8 turnDuelist)
{
  u8 fixedDuelist;
  s16 deckIndex;
  s8 handZone;
  u16 cardId;

  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixedDuelist = DUEL_PLAYER;
  else
    fixedDuelist = DUEL_OPPONENT;

  deckIndex = Duel_FindDeckCardIndex(turnDuelist, POLYMERIZATION);
  if (deckIndex < 0)
    return FALSE;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(turnDuelist);
  InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)(handZone)), cardId);
  return TRUE;
}

u8 ElementalHeroBlazeman_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u16 sourceId;
  u16 atk;
  u16 def;
  u8 attr;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_BLAZEMAN)
    return FALSE;

  sourceId = gElementalHeroBlazemanCopySourceId;
  if (sourceId == CARD_NONE)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  if (fixedRow != gElementalHeroBlazemanCopyRow || col != gElementalHeroBlazemanCopyCol)
    return FALSE;

  SetCardInfo(sourceId);
  atk = gCardInfo.atk;
  def = gCardInfo.def;
  attr = gCardInfo.attribute;
  Duel_WriteCardInfoStats(zone->id, atk, def);
  gCardInfo.attribute = attr;
  return TRUE;
}

void TryElementalHeroBlazemanOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;
  u8 turnDuelist;

  if (!IsFaceUpBlazemanSummon(zone))
    return;

  if (zone->effectUsedThisTurn)
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  turnDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  if (Duel_FindDeckCardIndex(turnDuelist, POLYMERIZATION) < 0)
    return;

  /* On-summon does not consume effectUsedThisTurn — that flag is only for
   * the menu activated effect (popup_2). Otherwise popup_2 can never fire the turn
   * Blazeman is summoned. */

  /* popup_1 only after Blazeman is drawn on the field. */
  UpdateDuelGfxExceptField();

  Duel_ShowCardEffectText(ELEMENTAL_HERO_BLAZEMAN,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_BLAZEMAN_POPUP_1);

  if (IsDuelOver() == TRUE)
    return;

  if (!AddPolymerizationFromDeck(turnDuelist))
    return;

  UpdateDuelGfxExceptField();
}

unsigned char CanActivateElementalHeroBlazeman(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_BLAZEMAN)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_BLAZEMAN)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!IsFaceUpBlazemanSummon(zone))
    return FALSE;

  return HandHasElementalHero(ACTIVE_DUELIST);
}

void ActivateElementalHeroBlazemanEffect(void)
{
  /* Match ActivateMonsterEffect: gMonEffect.row/zone are fixed-POV. */
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  u16 discardedId;
  u8 fixedRow;
  u8 col;

  /* popup_2: only from the monster effect menu (ActivateMonsterEffect). */
  Duel_ShowCardEffectText(ELEMENTAL_HERO_BLAZEMAN,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_BLAZEMAN_POPUP_2);

  if (IsDuelOver() == TRUE)
    return;

  if (!DiscardHandHeroForCopy(&discardedId))
    return;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &col)) {
    gElementalHeroBlazemanCopySourceId = discardedId;
    gElementalHeroBlazemanCopyRow = fixedRow;
    gElementalHeroBlazemanCopyCol = col;
  }

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroBlazeman_SelfCheck(void)
{
  if (!IsHandElementalHero(ELEMENTAL_HERO_SPARKMAN))
    __builtin_trap();

  if (IsHandElementalHero(POLYMERIZATION))
    __builtin_trap();
}
#endif
