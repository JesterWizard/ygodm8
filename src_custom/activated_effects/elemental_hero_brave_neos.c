#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_brave_neos.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);
u8 GetDuelistForZone(struct DuelCard *zone);

#define BRAVE_NEOS_ATK_PER 100
#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct BraveNeosActionData {
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

extern struct BraveNeosActionData sActionData;

static const char sNeosName[] APPEND_RODATA = "Neos";
static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static u8 IsNeoSpacianOrHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sNeoSpacianName)
      || Duel_CardNameContains(cardId, sHeroName);
}

static u8 CountNeoSpacianOrHeroInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsNeoSpacianOrHeroMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsNeoSpacianOrHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }
  return count;
}

u8 ElementalHeroBraveNeos_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 me;
  u16 atk;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_BRAVE_NEOS)
    return FALSE;

  me = GetDuelistForZone(zone);
  if (me > DUEL_OPPONENT)
    return FALSE;

  SetCardInfo(zone->id);
  atk = Duel_StatFromCount(CountNeoSpacianOrHeroInGy(me), BRAVE_NEOS_ATK_PER, gCardInfo.atk);
  Duel_WriteCardInfoStats(zone->id, atk, gCardInfo.def);
  return TRUE;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 IsNeosRelatedSpellTrap(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;
  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;
  return Duel_CardNameContains(cardId, sNeosName)
      || Duel_CardNameContains(cardId, sHeroName);
}

static u16 FindNeosRelatedSpellTrapInDeck(u8 turnDuelist)
{
  u8 fixedDuelist =
      gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsNeosRelatedSpellTrap(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }
  return CARD_NONE;
}

static void TryBraveNeosSearch(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  cardId = FindNeosRelatedSpellTrapInDeck(turnDuelist);
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_BRAVE_NEOS, 2);
  Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE);
  UpdateDuelGfxExceptField();
}

void ApplyElementalHeroBraveNeosBattleEffect(void)
{
  if (sActionData.playerCardId == ELEMENTAL_HERO_BRAVE_NEOS
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    TryBraveNeosSearch(DUEL_PLAYER);
    return;
  }
  if (sActionData.opponentCardId == ELEMENTAL_HERO_BRAVE_NEOS
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    TryBraveNeosSearch(DUEL_OPPONENT);
}

unsigned char CanActivateELEMENTAL_HERO_BRAVE_NEOS(void)
{
  if (gMonEffect.id != ELEMENTAL_HERO_BRAVE_NEOS)
    return FALSE;

  /* ATK overlay + battle-destroy search via ApplyElementalHeroBraveNeosBattleEffect. */
  return FALSE;
}

void ActivateELEMENTAL_HERO_BRAVE_NEOSEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_BRAVE_NEOS, 2);
}
