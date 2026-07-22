#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sHeroNameAlt[] APPEND_RODATA = "Hero";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountDarkFusionMentionsInGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == DARK_FUSION)
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (id == DARK_FUSION)
      count++;
    /* Ceiling: "Spells that mention Dark Fusion" not scanned by text. */
  }

  return count;
}

APPEND_TEXT void EffectDARK_SUPREMACY(void)
{
  u8 count = CountDarkFusionMentionsInGy();
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;
  u8 negated = 0;

  Duel_ShowTrapResponseText(DARK_SUPREMACY, gTrapEffectData.originCardId);

  /* Ceiling: GY banish shuffle HERO need GY ignition OPT.
   * Ceiling: negate up to count face-up opp cards (monsters first) via unk4. */

  for (col = 0; col < MAX_ZONES_IN_ROW && negated < count; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id == CARD_NONE)
      continue;
    zone->unk4 |= 0x80;
    negated++;
  }

  if (count == 0) {
    /* Still allow marking one if Dark Fusion not in GY — soft fail. */
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

  (void)sHeroName;
  (void)sHeroNameAlt;
}
