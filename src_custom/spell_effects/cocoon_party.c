#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sChrysalisName[] APPEND_RODATA = "Chrysalis";
static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u16 sNeoSpacianIds[] APPEND_RODATA = {
  NEO_SPACIAN_AIR_HUMMINGBIRD,
  NEO_SPACIAN_AQUA_DOLPHIN,
  NEO_SPACIAN_DARK_PANTHER,
  NEO_SPACIAN_FLARE_SCARAB,
  NEO_SPACIAN_GLOW_MOSS,
  NEO_SPACIAN_GRAND_MOLE,
  NEO_SPACIAN_MARINE_DOLPHIN,
  NEO_SPACIAN_TWINKLE_MOSS,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsChrysalisMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sChrysalisName);
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardNameContains(cardId, sNeoSpacianName))
    return TRUE;

  for (i = 0; i < ARRAY_COUNT(sNeoSpacianIds); i++) {
    if (cardId == sNeoSpacianIds[i])
      return TRUE;
  }

  return FALSE;
}

static u8 IdAlreadySeen(const u16 *seen, u8 seenCount, u16 cardId)
{
  u8 i;

  for (i = 0; i < seenCount; i++) {
    if (seen[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

static u8 CountUniqueNeoSpaciansInGy(u8 fixedDuelist)
{
  u16 seen[ARRAY_COUNT(sNeoSpacianIds)];
  u8 seenCount = 0;
  u8 i;
  u8 gyCount;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsNeoSpacianMonster(top) ? 1 : 0;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsNeoSpacianMonster(cardId))
      continue;
    if (IdAlreadySeen(seen, seenCount, cardId))
      continue;
    if (seenCount >= ARRAY_COUNT(seen))
      break;

    seen[seenCount++] = cardId;
  }

  return seenCount;
}

static s16 FindFirstChrysalisDeckIndex(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsChrysalisMonster(gDuelDecks[fixedDuelist].cards[i]))
      return (s16)i;
  }

  return -1;
}

static u8 DeckHasChrysalis(u8 turnDuelist)
{
  return FindFirstChrysalisDeckIndex(turnDuelist) >= 0;
}

static u8 CanActivateCocoonParty(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) == 0)
    return FALSE;

  if (CountUniqueNeoSpaciansInGy(fixedDuelist) == 0)
    return FALSE;

  return DeckHasChrysalis(ACTIVE_DUELIST);
}

static enum DuelActionResult SpecialSummonChrysalisFromDeck(u8 updateGfx)
{
  s16 deckIndex;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(updateGfx);

  deckIndex = FindFirstChrysalisDeckIndex(ACTIVE_DUELIST);
  if (deckIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  cardId = gDuelDecks[fixedDuelist].cards[deckIndex];
  if (!IsChrysalisMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void SpecialSummonChrysalisForNeos(u8 uniqueNeoCount)
{
  u8 i;
  u8 empty;
  u8 summonCount;

  empty = (u8)NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  summonCount = uniqueNeoCount;
  if (summonCount > empty)
    summonCount = empty;

  for (i = 0; i < summonCount; i++) {
    if (!DeckHasChrysalis(ACTIVE_DUELIST))
      break;

    if (SpecialSummonChrysalisFromDeck(i + 1 == summonCount) != DUEL_ACTION_OK)
      break;

    if (IsDuelOver() == TRUE)
      break;
  }
}

static void COCOON_PARTY_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 uniqueNeos;

  Duel_ShowEffectText(COCOON_PARTY);

  if (IsDuelOver() == TRUE || !CanActivateCocoonParty())
    return;

  uniqueNeos = CountUniqueNeoSpaciansInGy(fixedDuelist);
  if (uniqueNeos == 0)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonChrysalisForNeos(uniqueNeos);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectCOCOON_PARTY(void)
{
  if (!CanActivateCocoonParty()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(COCOON_PARTY, COCOON_PARTY_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void COCOON_PARTY_SelfCheck(void)
{
  if (!IsChrysalisMonster(CHRYSALIS_CHICKY))
    while (1)
      ;
  if (!IsNeoSpacianMonster(NEO_SPACIAN_AIR_HUMMINGBIRD))
    while (1)
      ;
  if (IsChrysalisMonster(NEO_SPACIAN_GRAND_MOLE))
    while (1)
      ;
}
#endif
