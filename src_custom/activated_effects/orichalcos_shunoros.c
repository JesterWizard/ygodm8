#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/monster_effects.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "orichalcos_shunoros.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

u8 GetDuelistForZone(struct DuelCard *zone);

#define SHUNOROS_ATK_PER_OPP_MONSTER 1000
#define SHUNOROS_LV4_NORMAL 4

static u8 CountOpponentMonsters(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(
      controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id != CARD_NONE)
      count++;
  }

  return count;
}

static struct DuelCard *FindFaceUpShunoros(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp && zone->id == ORICHALCOS_SHUNOROS)
        return zone;
    }
  }

  return NULL;
}

static u8 IsFaceUpLevel4NormalMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.monsterEffect == MONSTER_EFFECT_NONE
      && gCardInfo.level == SHUNOROS_LV4_NORMAL;
}

static u8 IsNormalMonsterId(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.monsterEffect == MONSTER_EFFECT_NONE;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

u8 OrichalcosShunoros_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 controller;
  u16 atk;

  if (zone == NULL || zone->id != ORICHALCOS_SHUNOROS)
    return FALSE;

  controller = GetDuelistForZone(zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  atk = Duel_StatFromCount(
      CountOpponentMonsters(controller),
      SHUNOROS_ATK_PER_OPP_MONSTER,
      gCardData_NEW[zone->id].atk);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardData_NEW[zone->id].def);
  return TRUE;
}

u8 OrichalcosShunoros_PreventsBattleDestroy(const struct DuelCard *zone)
{
  if (FindFaceUpShunoros() == NULL)
    return FALSE;

  return IsFaceUpLevel4NormalMonster(zone);
}

unsigned char CanActivateORICHALCOS_SHUNOROS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ORICHALCOS_SHUNOROS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ORICHALCOS_SHUNOROS)
    return FALSE;

  /* ATK overlay + Lv4 Normal protect + Normal BD SS wired via shared helpers.
   * OPT +2 tempStage per opp monster (~1000 ATK each). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountOpponentMonsters(GetDuelistForZone(zone)) > 0;
}

void ActivateORICHALCOS_SHUNOROSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 controller;
  u8 oppCount;
  s8 stages;

  Duel_ShowEffectTextTyped(ORICHALCOS_SHUNOROS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  controller = GetDuelistForZone(self);
  if (controller > DUEL_OPPONENT)
    return;

  oppCount = CountOpponentMonsters(controller);
  if (oppCount == 0)
    return;

  stages = (s8)(oppCount * 2);
  if (self->tempStage <= 127 - stages)
    self->tempStage += stages;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 FindShunorosHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i)->id == ORICHALCOS_SHUNOROS)
      return i;
  }

  return 0xFF;
}

void TryOrichalcosShunorosSsAfterNormalMonsterBd(u8 fixedDuelist, u16 cardId)
{
  u8 handZone;
  u8 turnDuelist;

  if (!IsNormalMonsterId(cardId))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
          ? ACTIVE_DUELIST_MONSTER_ROW
          : INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  handZone = FindShunorosHandZone(turnDuelist);
  if (handZone == 0xFF)
    return;

  TrySpecialSummonOrichalcosShunorosFromHand(handZone);
}

u8 CanSpecialSummonOrichalcosShunorosFromHand(u8 handZone)
{
  /* Hand SS only on Normal Monster battle destroy — TryOrichalcosShunorosSsAfterNormalMonsterBd. */
  (void)handZone;
  return FALSE;
}

u8 TrySpecialSummonOrichalcosShunorosFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  if (handZone >= max)
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ORICHALCOS_SHUNOROS)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  Duel_ShowEffectTextTyped(ORICHALCOS_SHUNOROS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonOrichalcosShunorosFromHand(u8 handZone);
u8 TrySpecialSummonOrichalcosShunorosFromHand(u8 handZone);
#endif
