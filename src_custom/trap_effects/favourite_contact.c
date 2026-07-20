#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sHeroNameAlt[] APPEND_RODATA = "Hero";
static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHeroOrNeosMaterial(u16 cardId)
{
  if (cardId == ELEMENTAL_HERO_NEOS)
    return TRUE;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (Duel_CardNameContains(cardId, sNeoSpacianName))
    return TRUE;
  return Duel_CardNameContains(cardId, sHeroName)
      || Duel_CardNameContains(cardId, sHeroNameAlt);
}

APPEND_TEXT void EffectFAVOURITE_CONTACT(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 returned = 0;
  u8 col;
  u8 i;
  struct DuelSummonOpts opts;
  u16 fusionId = ELEMENTAL_HERO_NEOS; /* Extra Deck not modeled — Neos stand-in */

  Duel_ShowTrapResponseText(FAVOURITE_CONTACT, gTrapEffectData.originCardId);

  /* ponytail: Extra Deck Fusion ignoring summon conditions + materials to
   * Deck bottom need fusion recipe API. Ceiling: return up to 2 HERO/Neos/
   * Neo-Spacian from field/hand/GY to Deck, then SS Neos if zone free. */

  for (col = 0; col < MAX_ZONES_IN_ROW && returned < 2; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsHeroOrNeosMaterial(zone->id)) {
      ClearZone(zone);
      returned++;
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW && returned < 2; i++) {
    if (gTurnHands[INACTIVE_DUELIST][i] != NULL
        && IsHeroOrNeosMaterial(gTurnHands[INACTIVE_DUELIST][i]->id)) {
      ClearZone(gTurnHands[INACTIVE_DUELIST][i]);
      returned++;
    }
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && returned < 2; i--) {
      if (!IsHeroOrNeosMaterial(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
        continue;
      GraveyardExpand_RemoveAtFixed(fixedDuelist, i - 1);
      returned++;
    }
  }

  if (returned > 0 && !ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, fusionId, opts) != DUEL_ACTION_OK)
      Duel_SpecialSummonFromHand(INACTIVE_DUELIST, fusionId, NULL, opts);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
