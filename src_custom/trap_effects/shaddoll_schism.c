#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static void ActivateSHADDOLL_SCHISMZone(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 banished = 0;
  u8 i;
  struct DuelSummonOpts opts;
  u16 fusionId = EL_SHADDOLL_WINDA;

  if (Duel_ActivateContinuousTrapPreamble(zone, SHADDOLL_SCHISM) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: full Fusion Summon from Extra by banishing listed materials +
   * Attribute-match send need fusion recipe picker. Ceiling: banish up to 2
   * Shaddoll from GY/field then SS El Shaddoll Winda stand-in; no direct
   * attack mark via unk4. */

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (GraveyardExpand_IsEnabled()) {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < 2; i--) {
      if (!IsShaddollMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
        continue;
      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
    }
  }

  if (banished < 1)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, fusionId, opts) != DUEL_ACTION_OK
      && Duel_SpecialSummonFromHand(INACTIVE_DUELIST, fusionId, NULL, opts)
         != DUEL_ACTION_OK) {
    /* Extra Deck not modeled — leave continuous face-up only. */
    return;
  }

  /* Mark cannot attack directly */
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *m = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][i];

    if (m != NULL && m->id == fusionId)
      m->unk4 |= 0x40;
  }
}

void TryActivateSHADDOLL_SCHISMOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(SHADDOLL_SCHISM, ActivateSHADDOLL_SCHISMZone);
}

