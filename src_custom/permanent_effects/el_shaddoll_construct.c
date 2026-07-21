#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "el_shaddoll_construct.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define SPECIAL_SUMMON_MARK 2

struct ElShaddollConstructActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct ElShaddollConstructActionData sActionData;

static u8 ZoneIsSpecialSummonMarked(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  return zone != NULL && zone->id != CARD_NONE && zone->unk4 == SPECIAL_SUMMON_MARK;
}

void ApplyElShaddollConstructBattleEffect(void)
{
  /* Start of Damage Step: destroy battling Special Summoned monster. */
  if (gHideEffectText)
    return;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == EL_SHADDOLL_CONSTRUCT
      && ZoneIsSpecialSummonMarked(sActionData.opponentMonsterRow, sActionData.unk16)) {
    sActionData.flags |= FLAG_GRAVEYARD_OPPONENT;
    return;
  }

  if (sActionData.opponentCardId == EL_SHADDOLL_CONSTRUCT
      && ZoneIsSpecialSummonMarked(sActionData.playerMonsterRow, sActionData.unkA)) {
    sActionData.flags |= FLAG_GRAVEYARD_PLAYER;
  }
}

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 TurnDuelistFromGraveyardRow(u8 turnRow)
{
  if (turnRow == 7)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static u8 IsShaddollSpellTrap(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static s16 FindDeckShaddollIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsShaddollCard(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 MillOneShaddollFromDeck(u8 turnDuelist)
{
  s16 deckIndex = FindDeckShaddollIndex(turnDuelist);
  u16 cardId;

  if (deckIndex < 0)
    return FALSE;

  cardId = gDuelDecks[FixedDuelistForTurnDuelist(turnDuelist)].cards[deckIndex];
  if (Duel_RemoveDeckCardAt(turnDuelist, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static s16 FindShaddollSpellTrapGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsShaddollSpellTrap(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u8 CanAddShaddollSpellTrapFromGy(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindShaddollSpellTrapGyIndex(fixedDuelist) >= 0;
}

static u8 AddShaddollSpellTrapFromGyToHand(u8 turnDuelist, s16 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsShaddollSpellTrap(cardId))
    return FALSE;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
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
  return TRUE;
}

static u8 IsConstructOnSummonTrigger(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != EL_SHADDOLL_CONSTRUCT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return FindDeckShaddollIndex(duelist) >= 0;
}

static u8 IsConstructGraveyardTrigger(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != EL_SHADDOLL_CONSTRUCT)
    return FALSE;

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != EL_SHADDOLL_CONSTRUCT)
      return FALSE;
  } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != EL_SHADDOLL_CONSTRUCT) {
    return FALSE;
  }

  return CanAddShaddollSpellTrapFromGy(turnDuelist);
}

unsigned char ShouldActivateEL_SHADDOLL_CONSTRUCT(void)
{
  /* Battle vs SS destroy live via ApplyElShaddollConstructBattleEffect. */
  if (IsConstructOnSummonTrigger())
    return TRUE;

  return IsConstructGraveyardTrigger();
}

void ActivateEL_SHADDOLL_CONSTRUCT(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;
  s16 gyIndex;
  struct DuelCard *zone;

  if (IsConstructOnSummonTrigger()) {
    turnDuelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

    Duel_ShowEffectTextTyped(EL_SHADDOLL_CONSTRUCT, 8);
    if (IsDuelOver() == TRUE)
      return;

    MillOneShaddollFromDeck(turnDuelist);

    zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
    if (zone != NULL)
      zone->unk4 = 1;

    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  turnDuelist = TurnDuelistFromGraveyardRow(gActiveEffect.turnRow);
  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  Duel_ShowEffectTextTyped(EL_SHADDOLL_CONSTRUCT, 8);
  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindShaddollSpellTrapGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  if (!AddShaddollSpellTrapFromGyToHand(turnDuelist, gyIndex))
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
