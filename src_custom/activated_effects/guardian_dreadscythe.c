#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyHasGuardianEatos(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard == GUARDIAN_EATOS;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == GUARDIAN_EATOS)
      return TRUE;
  }

  return FALSE;
}

static u8 CountAllGyMonsters(void)
{
  u8 fixed;
  u8 count = 0;
  u8 i;

  for (fixed = 0; fixed < 2; fixed++) {
    if (!GraveyardExpand_IsEnabled()) {
      if (GetTypeGroup(gDuel.duelistbattleState[fixed].graveyard) == TYPE_GROUP_MONSTER)
        count++;
      continue;
    }

    for (i = 0; i < GraveyardExpand_GetCount(fixed); i++) {
      if (GetTypeGroup(GraveyardExpand_GetCardAt(fixed, i)) == TYPE_GROUP_MONSTER)
        count++;
    }
  }

  return count;
}

static u8 ReaperScytheStagesFromGyCount(void)
{
  u8 stages = CountAllGyMonsters();

  if (stages > 126)
    stages = 126;

  return stages;
}

static u8 SetReaperScytheFromDeck(void)
{
  s8 empty;
  s16 deckIndex;
  struct DuelCard *slot;

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, REAPER_SCYTHE_DREADSCYTHE);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  slot = gTurnZones[ACTIVE_DUELIST_BACKROW][empty];
  slot->id = REAPER_SCYTHE_DREADSCYTHE;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

static u8 EquipReaperScytheToDreadscythe(struct DuelCard *dreadscythe)
{
  u8 stages;
  struct DuelCard *spellZone;
  u8 col;

  if (dreadscythe == NULL || dreadscythe->id != GUARDIAN_DREADSCYTHE)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (spellZone != NULL && spellZone->id == REAPER_SCYTHE_DREADSCYTHE)
      break;

    spellZone = NULL;
  }

  if (spellZone == NULL) {
    if (!SetReaperScytheFromDeck())
      return FALSE;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      spellZone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

      if (spellZone != NULL && spellZone->id == REAPER_SCYTHE_DREADSCYTHE)
        break;

      spellZone = NULL;
    }
  }

  if (spellZone == NULL)
    return FALSE;

  stages = ReaperScytheStagesFromGyCount();
  ApplyDynamicEquipStages(dreadscythe, stages);
  if (!RegisterDynamicEquip(spellZone, dreadscythe, REAPER_SCYTHE_DREADSCYTHE, stages))
    return FALSE;

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  RefreshFieldMonsterStatOverlays();
  return TRUE;
}

static u8 CanEquipReaperScytheFromDeck(void)
{
  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, REAPER_SCYTHE_DREADSCYTHE) < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) >= 0;
}

unsigned char CanActivateGUARDIAN_DREADSCYTHE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GUARDIAN_DREADSCYTHE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GUARDIAN_DREADSCYTHE)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT equip/add Reaper Scythe from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanEquipReaperScytheFromDeck();
}

void ActivateGUARDIAN_DREADSCYTHEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GUARDIAN_DREADSCYTHE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!EquipReaperScytheToDreadscythe(self))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonGuardianDreadscytheFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GUARDIAN_DREADSCYTHE)
    return FALSE;

  if (!GyHasGuardianEatos())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonGuardianDreadscytheFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *summoned;

  if (!CanSpecialSummonGuardianDreadscytheFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GUARDIAN_DREADSCYTHE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  summoned = NULL;
  {
    u8 col;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

      if (zone != NULL && zone->id == GUARDIAN_DREADSCYTHE) {
        summoned = zone;
        break;
      }
    }
  }

  EquipReaperScytheToDreadscythe(summoned);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGuardianDreadscytheFromHand(u8 handZone);
u8 TrySpecialSummonGuardianDreadscytheFromHand(u8 handZone);
#endif
