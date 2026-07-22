#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_dreamer.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindDreamerInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DESTINY_HERO_DREAMER)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DREAMER)
      return (s16)i;
  }

  return -1;
}

u8 DestinyHeroDreamer_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_DREAMER;
}

unsigned char CanActivateDESTINY_HERO_DREAMER(void)
{
  if (gMonEffect.id != DESTINY_HERO_DREAMER)
    return FALSE;

  /* Battle protect via DestinyHeroDreamer_PreventsBattleDestroy.
   * ponytail: banish-on-leave need GY hook. Ceiling: GY ignition SS. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindDreamerInGy() < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateDESTINY_HERO_DREAMEREffect(void)
{
  s16 gyIndex;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREAMER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindDreamerInGy();
  if (gyIndex < 0)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
