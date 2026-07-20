#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define GUARDIAN_EATOS_MAX_BANISH 3

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GyHasMonster(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedDuelist, i)) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

static u8 OppGyMonsterCount(void)
{
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[DUEL_OPPONENT].graveyard;

    return (cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(DUEL_OPPONENT); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(DUEL_OPPONENT, i)) == TYPE_GROUP_MONSTER)
      count++;
  }

  return count;
}

static struct DuelCard *FindEquipSpellForEatos(struct DuelCard *eatosZone, u8 *outRow, u8 *outCol)
{
  u8 i;
  u8 eatosRow;
  u8 eatosCol;

  if (!Duel_FindFixedMonsterZone(eatosZone, &eatosRow, &eatosCol))
    return NULL;

  for (i = 0; i < MAX_DYNAMIC_EQUIP_SLOTS; i++) {
    struct DynamicEquipLink *link = &gDynamicEquipLinks[i];
    struct DuelCard *spellZone;

    if (!link->active)
      continue;

    if (link->targetFixedRow != eatosRow || link->targetFixedCol != eatosCol)
      continue;

    spellZone = gFixedZones[link->spellFixedRow][link->spellFixedCol];
    if (spellZone == NULL || spellZone->id == CARD_NONE)
      continue;

    *outRow = link->spellFixedRow;
    *outCol = link->spellFixedCol;
    return spellZone;
  }

  return NULL;
}

static u8 EatosHasEquip(struct DuelCard *eatosZone)
{
  u8 row;
  u8 col;

  return FindEquipSpellForEatos(eatosZone, &row, &col) != NULL;
}

static u8 BanishUpToThreeOppGyMonsters(void)
{
  u8 fixedDuelist = DUEL_OPPONENT;
  u8 banished = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      return 0;

    Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < GUARDIAN_EATOS_MAX_BANISH;
       i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1) == CARD_NONE)
      continue;

    banished++;
  }

  return banished;
}

unsigned char CanActivateGUARDIAN_EATOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GUARDIAN_EATOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GUARDIAN_EATOS)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return EatosHasEquip(zone) && OppGyMonsterCount() > 0;
}

void ActivateGUARDIAN_EATOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *spellZone;
  u8 spellRow;
  u8 spellCol;
  u8 banished;
  u8 owner;

  Duel_ShowEffectTextTyped(GUARDIAN_EATOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  spellZone = FindEquipSpellForEatos(self, &spellRow, &spellCol);
  if (spellZone == NULL)
    return;

  owner = (spellRow == PLAYER_BACKROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  if (Duel_DestroyZone(spellZone, owner, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  banished = BanishUpToThreeOppGyMonsters();
  if (banished > 0 && self->tempStage < 127 - (s8)banished)
    self->tempStage += (s8)banished;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonGuardianEatosFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != GUARDIAN_EATOS)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (GyHasMonster(fixedDuelist))
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonGuardianEatosFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonGuardianEatosFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GUARDIAN_EATOS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGuardianEatosFromHand(u8 handZone);
u8 TrySpecialSummonGuardianEatosFromHand(u8 handZone);
#endif
