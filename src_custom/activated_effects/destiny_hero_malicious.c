#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindMaliciousInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DESTINY_HERO_MALICIOUS)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_MALICIOUS)
      return (s16)i;
  }

  return -1;
}

unsigned char CanActivateDESTINY_HERO_MALICIOUS(void)
{
  if (gMonEffect.id != DESTINY_HERO_MALICIOUS)
    return FALSE;

  /* ponytail: GY ignition needs GY-menu wire. Ceiling: allow when Malicious in
   * GY + another in Deck (callable if gMonEffect set to Malicious). */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindMaliciousInGy() < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, DESTINY_HERO_MALICIOUS) < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateDESTINY_HERO_MALICIOUSEffect(void)
{
  s16 gyIndex;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(DESTINY_HERO_MALICIOUS, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindMaliciousInGy();
  if (gyIndex < 0)
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, DESTINY_HERO_MALICIOUS, opts);
  UpdateDuelGfxExceptField();
}
