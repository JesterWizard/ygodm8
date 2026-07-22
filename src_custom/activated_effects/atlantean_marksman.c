#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "atlantean_marksman.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

struct MarksmanActionData {
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

extern struct MarksmanActionData sActionData;

static const char sAtlanteanName[] APPEND_RODATA = "Atlantean";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsAtlanteanSeaSerpent(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT))
    return FALSE;
  return Duel_CardNameContains(cardId, sAtlanteanName);
}

static u16 FindDeckTarget(u8 turnDuelist)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == ATLANTEAN_MARKSMAN)
      continue;
    if (!IsAtlanteanSeaSerpent(cardId))
      continue;
    if (gCardData_NEW[cardId].level == 0 || gCardData_NEW[cardId].level > 4)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;
    return cardId;
  }
  return CARD_NONE;
}

static u8 DidMarksmanDealBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != ATLANTEAN_MARKSMAN)
      return FALSE;
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != ATLANTEAN_MARKSMAN)
      return FALSE;
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

static void TryMarksmanSs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  u16 cardId;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  cardId = FindDeckTarget(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(ATLANTEAN_MARKSMAN, 2);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void ApplyAtlanteanMarksmanBattleEffect(void)
{
  if (DidMarksmanDealBattleDamage(DUEL_PLAYER)) {
    TryMarksmanSs(DUEL_PLAYER);
    return;
  }
  if (DidMarksmanDealBattleDamage(DUEL_OPPONENT))
    TryMarksmanSs(DUEL_OPPONENT);
}

unsigned char CanActivateATLANTEAN_MARKSMAN(void)
{
  if (gMonEffect.id != ATLANTEAN_MARKSMAN)
    return FALSE;

  /* Battle-damage Deck SS via ApplyAtlanteanMarksmanBattleEffect.
   * ponytail: sent-for-WATER destroy Set S/T needs send hook. */
  return FALSE;
}

void ActivateATLANTEAN_MARKSMANEffect(void)
{
  Duel_ShowEffectTextTyped(ATLANTEAN_MARKSMAN, 2);
}
