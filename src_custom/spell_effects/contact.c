#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define CONTACT_MAX_UNIQUE_NEOS 5

static const char sChrysalisName[] APPEND_RODATA = "Chrysalis";

static u8 IsChrysalisMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sChrysalisName);
}

/* Printed Chrysalis → Neo-Spacian pairs (same as COCOON_REBIRTH). */
static u16 NeoSpacianForChrysalis(u16 chrysalisId)
{
  switch (chrysalisId) {
  case CHRYSALIS_CHICKY:
    return NEO_SPACIAN_AIR_HUMMINGBIRD;
  case CHRYSALIS_DOLPHIN:
    return NEO_SPACIAN_AQUA_DOLPHIN;
  case CHRYSALIS_MOLE:
    return NEO_SPACIAN_GRAND_MOLE;
  case CHRYSALIS_PANTAIL:
    return NEO_SPACIAN_DARK_PANTHER;
  case CHRYSALIS_PINNY:
    return NEO_SPACIAN_GLOW_MOSS;
  default:
    /* ponytail: only the five Chrysalis in-trunk pairs are mapped. */
    return CARD_NONE;
  }
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

static u8 CollectUniqueNeoIdsFromField(u16 *out, u8 maxOut)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 neoId;
    u16 chrysalisId = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]->id;

    if (!IsChrysalisMonster(chrysalisId))
      continue;

    neoId = NeoSpacianForChrysalis(chrysalisId);
    if (neoId == CARD_NONE)
      continue;

    if (IdAlreadySeen(out, count, neoId))
      continue;

    if (count >= maxOut)
      break;

    out[count++] = neoId;
  }

  return count;
}

static u8 HandHasCardId(u16 cardId)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], cardId);
}

static u8 NeoAvailableInHandOrDeck(u16 neoId)
{
  if (HandHasCardId(neoId))
    return TRUE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, neoId) >= 0;
}

static u8 AnyMappedNeoAvailable(const u16 *neoIds, u8 neoCount)
{
  u8 i;

  for (i = 0; i < neoCount; i++) {
    if (NeoAvailableInHandOrDeck(neoIds[i]))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateCONTACT(void)
{
  u16 neoIds[CONTACT_MAX_UNIQUE_NEOS];
  u8 neoCount;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  neoCount = CollectUniqueNeoIdsFromField(neoIds, CONTACT_MAX_UNIQUE_NEOS);
  if (neoCount == 0)
    return FALSE;

  return AnyMappedNeoAvailable(neoIds, neoCount);
}

static s8 PickHandZoneWithId(u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == cardId)
      return (s8)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonNeoFromHandOrDeck(u16 neoId, u8 updateGfx)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(updateGfx);
  s8 handZone;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (HandHasCardId(neoId)) {
    if (WhoseTurn() == DUEL_PLAYER)
      return Duel_SpecialSummonFromHand(ACTIVE_DUELIST, neoId, NULL, opts);

    handZone = PickHandZoneWithId(neoId);
    if (handZone < 0)
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts);
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, neoId) >= 0)
    return Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, neoId, opts);

  return DUEL_ACTION_NO_TARGET;
}

static void SendAllChrysalisToGraveyard(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || !IsChrysalisMonster(zone->id))
      continue;

    if (Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;

    if (IsDuelOver() == TRUE)
      return;
  }
}

static void CONTACT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 neoIds[CONTACT_MAX_UNIQUE_NEOS];
  u8 neoCount;
  u8 i;

  Duel_ShowEffectText(CONTACT);

  if (IsDuelOver() == TRUE || !CanActivateCONTACT())
    return;

  neoCount = CollectUniqueNeoIdsFromField(neoIds, CONTACT_MAX_UNIQUE_NEOS);
  if (neoCount == 0)
    return;

  if (spellZone != NULL && spellZone->id == CONTACT)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  SendAllChrysalisToGraveyard();

  if (IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()) {
    UpdateDuelGfxExceptField();
    return;
  }

  for (i = 0; i < neoCount; i++) {
    if (!NeoAvailableInHandOrDeck(neoIds[i]))
      continue;

    if (SpecialSummonNeoFromHandOrDeck(neoIds[i], i + 1 == neoCount) == DUEL_ACTION_DUEL_OVER)
      return;

    if (IsDuelOver() == TRUE)
      return;
  }

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectCONTACT(void)
{
  if (!CanActivateCONTACT()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CONTACT, CONTACT_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CONTACT_SelfCheck(void)
{
  if (NeoSpacianForChrysalis(CHRYSALIS_CHICKY) != NEO_SPACIAN_AIR_HUMMINGBIRD)
    while (1)
      ;
  if (NeoSpacianForChrysalis(CHRYSALIS_PINNY) != NEO_SPACIAN_GLOW_MOSS)
    while (1)
      ;
}
#endif
