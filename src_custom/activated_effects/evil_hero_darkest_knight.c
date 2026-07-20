#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
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

static u8 IsFiendOrWarrior(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FIEND)
      || Duel_CardHasMonsterType(cardId, TYPE_WARRIOR);
}

static s8 FindFiendOrWarriorGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsFiendOrWarrior(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsFiendOrWarrior(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonFiendOrWarriorFromGy(s8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsFiendOrWarrior(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsFiendOrWarrior(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateEVIL_HERO_DARKEST_KNIGHT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_DARKEST_KNIGHT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_DARKEST_KNIGHT)
    return FALSE;

  /* ponytail: opp ATK loss by materials + double attack need fusion/battle hooks.
   * Ceiling: OPT SS 1 Fiend/Warrior from GY (leave-field stand-in). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindFiendOrWarriorGyIndex(FixedDuelistForActive()) >= 0;
}

void ActivateEVIL_HERO_DARKEST_KNIGHTEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 gyIndex;

  Duel_ShowEffectTextTyped(EVIL_HERO_DARKEST_KNIGHT, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  gyIndex = FindFiendOrWarriorGyIndex(FixedDuelistForActive());
  if (gyIndex < 0)
    return;

  if (SpecialSummonFiendOrWarriorFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
