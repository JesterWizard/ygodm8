#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpie_perfumer.h"
#include "summon_tribute.h"

static const char sHarpieLadySistersName[] APPEND_RODATA = "Harpie Lady Sisters";
static const char sHarpieName[] APPEND_RODATA = "Harpie";

u8 HarpiePerfumer_TreatsNameAsHarpieLady(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == HARPIE_PERFUMER;
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 MentionsHarpieLadySisters(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == HARPIE_LADY_SISTERS)
    return TRUE;

  return Duel_CardNameContains(cardId, sHarpieLadySistersName);
}

static u8 IsSistersMentionSpellTrap(u16 cardId)
{
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return MentionsHarpieLadySisters(cardId);
}

static u16 FindSistersMentionSpellTrapInDeck(u8 turnDuelist, u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (cardId == excludeId)
      continue;

    if (IsSistersMentionSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsLevel5OrHigherHarpie(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[monsterRow][i];

    if (!MonsterIsFaceUp(zone) || !IsHarpieMonster(zone->id))
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level >= 5)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSearchSistersSpellTraps(u8 turnDuelist)
{
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  return FindSistersMentionSpellTrapInDeck(turnDuelist, CARD_NONE) != CARD_NONE;
}

unsigned char ShouldActivateHARPIE_PERFUMER(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != HARPIE_PERFUMER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* Name=Harpie Lady via HarpiePerfumer_TreatsNameAsHarpieLady + Duel_ZoneEffectCardId. */
  return CanSearchSistersSpellTraps(duelist);
}

void ActivateHARPIE_PERFUMER(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 firstId;
  u16 secondId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(HARPIE_PERFUMER, 8);
  if (IsDuelOver() == TRUE)
    return;

  firstId = FindSistersMentionSpellTrapInDeck(duelist, CARD_NONE);
  if (firstId != CARD_NONE)
    Duel_AddDeckCardToHand(duelist, firstId, TRUE);

  if (ControlsLevel5OrHigherHarpie(duelist)
      && FirstEmptyZoneInRow(gTurnHands[duelist]) >= 0) {
    secondId = FindSistersMentionSpellTrapInDeck(duelist, firstId);
    if (secondId != CARD_NONE)
      Duel_AddDeckCardToHand(duelist, secondId, TRUE);
  }

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
}
