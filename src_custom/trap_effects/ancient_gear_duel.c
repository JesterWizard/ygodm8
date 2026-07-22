#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static void ActivateANCIENT_GEAR_DUELZone(struct DuelCard *zone)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;
  u8 hasGolem = FALSE;
  u8 oppHasMonster = FALSE;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 banished = 0;
  u8 i;
  struct DuelSummonOpts opts;

  if (Duel_ActivateContinuousTrapPreamble(zone, ANCIENT_GEAR_DUEL)
      == DUEL_ACTION_DUEL_OVER)
    return;

  /* unaffected by opp monster effects + Extra Deck Fusion + 3 attacks
   * need protection/fusion/battle hooks; mark AG Golem/mentioners
   * (unk4); if opp has monster + we control Golem, banish Golem + 1 AG from GY
   * and SS Ultimate Ancient Gear Golem stand-in from Deck/hand. */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m == NULL)
      continue;
    if (m->id == ANCIENT_GEAR_GOLEM || m->id == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
        || m->id == ULTIMATE_ANCIENT_GEAR_GOLEM) {
      hasGolem = TRUE;
      m->unk4 |= 0x80; /* protection mark */
    } else if (IsAncientGearMonster(m->id)) {
      m->unk4 |= 0x40; /* mentioner mark stand-in */
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[oppRow][col] != NULL && gFixedZones[oppRow][col]->id != CARD_NONE)
      oppHasMonster = TRUE;
  }

  if (!hasGolem || !oppHasMonster || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  /* Banish Golem from field */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && m->id == ANCIENT_GEAR_GOLEM) {
      Duel_BanishZone(m, FALSE);
      banished++;
      break;
    }
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < 2; i--) {
      if (!IsAncientGearMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
        continue;
      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
    }
  }

  if (banished < 1)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, ULTIMATE_ANCIENT_GEAR_GOLEM, opts)
      != DUEL_ACTION_OK)
    Duel_SpecialSummonFromHand(INACTIVE_DUELIST, ULTIMATE_ANCIENT_GEAR_GOLEM, NULL, opts);

  UpdateDuelGfxExceptField();
}

void TryActivateANCIENT_GEAR_DUELOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ANCIENT_GEAR_DUEL,
                                         ActivateANCIENT_GEAR_DUELZone);
}

