#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

/* no Lekunga Token card id — MOON_TOKEN stand-in.
 * Ceiling: wrong Type/Attribute/stats (Fairy/LIGHT 0/0 vs Plant/WATER 700/700);
 * upgrade: add LEKUNGA_TOKEN card data + art, then swap this define. */
#define LEKUNGA_TOKEN_ID MOON_TOKEN
#define LEKUNGA_BANISH_COUNT 2

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsWaterMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_WATER;
}

static u8 CountWaterInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsWaterMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard) ? 1 : 0;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsWaterMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 BanishWaterFromGy(u8 need)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (need > 1 || !IsWaterMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < need; i--) {
    if (!IsWaterMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    banished++;
  }

  return banished >= need;
}

unsigned char CanActivateLEKUNGA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LEKUNGA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LEKUNGA)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return CountWaterInGy() >= LEKUNGA_BANISH_COUNT;
}

void ActivateLEKUNGAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(LEKUNGA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!BanishWaterFromGy(LEKUNGA_BANISH_COUNT))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  opts.lockMonster = TRUE;
  opts.markSpecialSummon = FALSE;

  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, LEKUNGA_TOKEN_ID, opts);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
