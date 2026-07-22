#include "global.h"
#include "gravekeepers_headman.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLevel4GravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sGravekeepersName))
    return FALSE;

  return gCardData_NEW[cardId].level == 4;
}

static s16 FindLevel4GravekeeperGyIndexFor(u8 fixedDuelist, u8 turnDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

    if (IsLevel4GravekeeperMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return 0;

    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLevel4GravekeeperMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return (s16)i;
  }

  return -1;
}

static s16 FindLevel4GravekeeperGyIndex(void)
{
  return FindLevel4GravekeeperGyIndexFor(FixedDuelistForActive(), ACTIVE_DUELIST);
}

static enum DuelActionResult SpecialSummonLevel4GravekeeperFromGyFor(u8 turnDuelist,
                                                                     u8 fixedDuelist,
                                                                     s16 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                            : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;
    if (!IsLevel4GravekeeperMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsLevel4GravekeeperMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static enum DuelActionResult SpecialSummonLevel4GravekeeperFromGy(s16 gyIndex)
{
  return SpecialSummonLevel4GravekeeperFromGyFor(ACTIVE_DUELIST, FixedDuelistForActive(), gyIndex);
}

void TryGravekeepersHeadmanOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s16 gyIndex;

  if (zone == NULL || zone->id != GRAVEKEEPERS_HEADMAN)
    return;

  if (EffectOpt_IsUsed(GRAVEKEEPERS_HEADMAN) || ArchlordKristya_IsSpecialSummonLocked())
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
                    ? ACTIVE_DUELIST
                    : INACTIVE_DUELIST;

  gyIndex = FindLevel4GravekeeperGyIndexFor(fixedDuelist, turnDuelist);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_HEADMAN, 8);

  if (SpecialSummonLevel4GravekeeperFromGyFor(turnDuelist, fixedDuelist, gyIndex)
      != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(GRAVEKEEPERS_HEADMAN);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateGRAVEKEEPERS_HEADMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_HEADMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_HEADMAN)
    return FALSE;

  /* On-Summon SS via TryGravekeepersHeadmanOnMonsterPlacement (EffectOpt).
   * OPT SS 1 Lv4 Gravekeeper's from GY in ATK (shares EffectOpt). */
  if (EffectOpt_IsUsed(GRAVEKEEPERS_HEADMAN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindLevel4GravekeeperGyIndex() >= 0;
}

void ActivateGRAVEKEEPERS_HEADMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s16 gyIndex;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_HEADMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  gyIndex = FindLevel4GravekeeperGyIndex();
  if (gyIndex < 0)
    return;

  if (SpecialSummonLevel4GravekeeperFromGy(gyIndex) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(GRAVEKEEPERS_HEADMAN);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
