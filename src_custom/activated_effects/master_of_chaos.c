#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 MonsterHasAttribute(u16 cardId, u16 attribute)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == attribute;
}

static u8 IsLightOrDarkMonster(u16 cardId)
{
  return MonsterHasAttribute(cardId, ATTRIBUTE_LIGHT)
      || MonsterHasAttribute(cardId, ATTRIBUTE_SHADOW);
}

static u8 OwnGyHasLightOrDark(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsLightOrDarkMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightOrDarkMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonLightOrDarkFromGy(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return OwnGyHasLightOrDark(FixedDuelistForActive());
}

static enum DuelActionResult SpecialSummonLightOrDarkFromGy(u8 fixedDuelist)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsLightOrDarkMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsLightOrDarkMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  }

  return DUEL_ACTION_NO_TARGET;
}

static struct DuelCard *FindOwnAttrMonster(u16 attribute, struct DuelCard *skip)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == skip || zone->id == CARD_NONE)
      continue;

    if (MonsterHasAttribute(zone->id, attribute) && !IsGodCard(zone->id))
      return zone;
  }

  return NULL;
}

static u8 OppHasMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER
        && !IsGodCard(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 CanTributeLightDarkBanish(void)
{
  struct DuelCard *light = FindOwnAttrMonster(ATTRIBUTE_LIGHT, NULL);
  struct DuelCard *dark;

  if (light == NULL)
    return FALSE;

  dark = FindOwnAttrMonster(ATTRIBUTE_SHADOW, light);
  if (dark == NULL)
    return FALSE;

  return OppHasMonster();
}

static void BanishAllOppMonsters(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
      continue;

    if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

static void ResolveTributeBanish(struct DuelCard *self)
{
  struct DuelCard *light = FindOwnAttrMonster(ATTRIBUTE_LIGHT, NULL);
  struct DuelCard *dark;
  u8 fixedDuelist = FixedDuelistForActive();

  if (light == NULL)
    return;

  dark = FindOwnAttrMonster(ATTRIBUTE_SHADOW, light);
  if (dark == NULL)
    return;

  ClearZoneAndSendMonToGraveyard2(light, fixedDuelist);
  if (IsDuelOver() == TRUE)
    return;

  ClearZoneAndSendMonToGraveyard2(dark, fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  BanishAllOppMonsters();
  NotifyDynamicEquipFieldChanged();

  if (self != NULL && self->id == MASTER_OF_CHAOS)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateMASTER_OF_CHAOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MASTER_OF_CHAOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MASTER_OF_CHAOS)
    return FALSE;

  /* Fusion SS trigger + destroyed GY Spell add need summon/destroy
   * hooks. OPT SS LIGHT/DARK from GY, else tribute LIGHT+DARK → banish. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanSpecialSummonLightOrDarkFromGy())
    return TRUE;

  return CanTributeLightDarkBanish();
}

void ActivateMASTER_OF_CHAOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();

  Duel_ShowEffectTextTyped(MASTER_OF_CHAOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSpecialSummonLightOrDarkFromGy()) {
    if (SpecialSummonLightOrDarkFromGy(fixedDuelist) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanTributeLightDarkBanish())
    return;

  ResolveTributeBanish(self);
}
