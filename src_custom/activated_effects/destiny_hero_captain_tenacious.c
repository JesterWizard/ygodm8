#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static s16 FindDestinyHeroGyIndex(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (IsDestinyHeroMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDestinyHeroMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static enum DuelActionResult SpecialSummonDestinyHeroFromGy(s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateDESTINY_HERO_CAPTAIN_TENACIOUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_CAPTAIN_TENACIOUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_CAPTAIN_TENACIOUS)
    return FALSE;

  /* Standby GY SS via TryApplyDestinyHeroCaptainTenaciousStandby when a D-HERO
   * was battle-destroyed since last Standby. OPT SS 1 D-HERO from your GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindDestinyHeroGyIndex() >= 0;
}

void ActivateDESTINY_HERO_CAPTAIN_TENACIOUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(DESTINY_HERO_CAPTAIN_TENACIOUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindDestinyHeroGyIndex();
  if (gyIndex < 0)
    return;

  if (SpecialSummonDestinyHeroFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
