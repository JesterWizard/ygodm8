#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "knights_title.h"
#include "spell_effects.h"

static u8 IsFaceUpMonster(struct DuelCard *zone)
{
  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  /* Attack-position monsters stay isFaceUp=0 until end-of-turn flip. */
  return zone->isDefending == FALSE;
}

static u8 FindFaceUpDarkMagicianCol(u8 *outCol)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone->id != DARK_MAGICIAN)
      continue;

    if (!IsFaceUpMonster(zone))
      continue;

    *outCol = i;
    return TRUE;
  }

  return FALSE;
}

static u8 HandHasDarkMagicianKnight(void)
{
  return RowHasCardMatch(gTurnHands[ACTIVE_DUELIST], DARK_MAGICIAN_KNIGHT);
}

static u8 GraveHasDarkMagicianKnight(void)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DARK_MAGICIAN_KNIGHT;
}

static u8 CanSpecialSummonDarkMagicianKnight(void)
{
  if (HandHasDarkMagicianKnight())
    return TRUE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN_KNIGHT) >= 0)
    return TRUE;

  return GraveHasDarkMagicianKnight();
}

static u8 IsDarkMagicianKnight(u16 cardId)
{
  return cardId == DARK_MAGICIAN_KNIGHT;
}

static s8 PickDarkMagicianKnightHandZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == DARK_MAGICIAN_KNIGHT)
      return i;
  }

  return -1;
}

u8 CanActivateKnightsTitle(void)
{
  u8 darkMagicianCol;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!FindFaceUpDarkMagicianCol(&darkMagicianCol))
    return FALSE;

  return CanSpecialSummonDarkMagicianKnight();
}

static void TributeFaceUpDarkMagician(void)
{
  u8 darkMagicianCol;

  if (!FindFaceUpDarkMagicianCol(&darkMagicianCol))
    return;

  Duel_DestroyZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][darkMagicianCol], ACTIVE_DUELIST, FALSE);
}

void KnightsTitle_ClearDarkMagicianKnightSpecialSummonLock(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone->id == DARK_MAGICIAN_KNIGHT) {
      /* Special face-up summons set unk4=2; DMK needs its summon effect enabled. */
      zone->unk4 = 0;
      return;
    }
  }
}

static void SpecialSummonDarkMagicianKnight(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonDarkMagicianKnight())
    return;

  if (HandHasDarkMagicianKnight()) {
    if (WhoseTurn() == DUEL_PLAYER) {
      if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, DARK_MAGICIAN_KNIGHT, IsDarkMagicianKnight, opts)
          == DUEL_ACTION_OK)
        KnightsTitle_ClearDarkMagicianKnightSpecialSummonLock();
      return;
    }

    {
      s8 handZone = PickDarkMagicianKnightHandZone();

      if (handZone >= 0
          && Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK)
        KnightsTitle_ClearDarkMagicianKnightSpecialSummonLock();
    }
    return;
  }

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN_KNIGHT) >= 0) {
    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, DARK_MAGICIAN_KNIGHT, opts) == DUEL_ACTION_OK)
      KnightsTitle_ClearDarkMagicianKnightSpecialSummonLock();
    return;
  }

  if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, DARK_MAGICIAN_KNIGHT, opts) == DUEL_ACTION_OK)
    KnightsTitle_ClearDarkMagicianKnightSpecialSummonLock();
}

APPEND_TEXT void EffectKnightsTitle(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(KNIGHTS_TITLE);

  if (IsDuelOver() == TRUE || !CanActivateKnightsTitle())
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  TributeFaceUpDarkMagician();

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonDarkMagicianKnight();
}
