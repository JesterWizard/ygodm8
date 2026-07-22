#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "evil_hero_darkest_knight.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sDarkestKnightInit APPEND_DATA = {0};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
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

static enum DuelActionResult SpecialSummonFiendOrWarriorFromGyFor(u8 fixedDuelist, u8 turnDuelist,
                                                                  s8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                            : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsFiendOrWarrior(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsFiendOrWarrior(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static enum DuelActionResult SpecialSummonFiendOrWarriorFromGy(s8 gyIndex)
{
  return SpecialSummonFiendOrWarriorFromGyFor(FixedDuelistForActive(), ACTIVE_DUELIST, gyIndex);
}

static void OnDarkestKnightLeaveField(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  s8 gyIndex;

  if (ev == NULL || ev->cardId != EVIL_HERO_DARKEST_KNIGHT)
    return;
  if (ev->controller > DUEL_OPPONENT || gHideEffectText)
    return;
  if (EffectOpt_IsUsed(EVIL_HERO_DARKEST_KNIGHT) || ArchlordKristya_IsSpecialSummonLocked())
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  gyIndex = FindFiendOrWarriorGyIndex(ev->controller);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(EVIL_HERO_DARKEST_KNIGHT, 8);

  if (SpecialSummonFiendOrWarriorFromGyFor(ev->controller, turnDuelist, gyIndex)
      != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(EVIL_HERO_DARKEST_KNIGHT);
  UpdateDuelGfxExceptField();
}

void EvilHeroDarkestKnight_EnsureInit(void)
{
  if (sDarkestKnightInit)
    return;

  sDarkestKnightInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnDarkestKnightLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnDarkestKnightLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnDarkestKnightLeaveField);
}

static u32 SumMaterialOriginalAtk(const u16 *materialIds, u8 materialCount)
{
  u32 atkSum = 0;
  u8 i;

  if (materialIds == NULL)
    return 0;

  for (i = 0; i < materialCount; i++) {
    u16 cardId = materialIds[i];

    if (cardId < NUM_TOTAL_CARDS)
      atkSum += gCardData_NEW[cardId].atk;
  }

  return atkSum;
}

void EvilHeroDarkestKnight_OnFusionSummoned(struct DuelCard *zone, const u16 *materialIds,
                                            u8 materialCount)
{
  u32 atkSum;

  if (zone == NULL || zone->id != EVIL_HERO_DARKEST_KNIGHT)
    return;

  zone->unk4 = 2;

  atkSum = SumMaterialOriginalAtk(materialIds, materialCount);
  zone->permStage = (s8)((atkSum + 499) / 500);
  if (zone->permStage < 1)
    zone->permStage = 1;

  RefreshFieldMonsterStatOverlays();
}

void ApplyEvilHeroDarkestKnightOppAtkPenalty(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 zoneOwner;
  u8 row;
  u8 col;
  u16 computedAtk;
  u16 drainAtk;

  if (zone == NULL || zone->id == CARD_NONE || !ZoneShowsCombatStats(zone))
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &fixedCol))
    return;

  zoneOwner = Duel_FixedDuelistForMonsterRow(fixedRow);
  if (zoneOwner > DUEL_OPPONENT)
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *knight = gFixedZones[row][col];
      u8 knightOwner;
      s8 stages;

      if (knight == NULL || knight->id != EVIL_HERO_DARKEST_KNIGHT || !knight->isFaceUp)
        continue;

      knightOwner = Duel_FixedDuelistForMonsterRow(row);
      if (knightOwner == zoneOwner)
        continue;

      stages = knight->permStage;
      if (stages <= 0)
        continue;

      computedAtk = gCardInfo.atk;
      drainAtk = (u16)(stages * 500);
      gCardInfo.atk = (computedAtk > drainAtk) ? (u16)(computedAtk - drainAtk) : 0;
      return;
    }
  }
}

unsigned char CanActivateEVIL_HERO_DARKEST_KNIGHT(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_DARKEST_KNIGHT)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_DARKEST_KNIGHT)
    return FALSE;

  /* Fusion double attack + material ATK drain via EvilHeroDarkestKnight_OnFusionSummoned.
   * Leave-field SS via EvilHeroDarkestKnight_EnsureInit.
   * OPT SS 1 Fiend/Warrior from GY (shares EffectOpt with leave-field). */
  if (EffectOpt_IsUsed(EVIL_HERO_DARKEST_KNIGHT))
    return FALSE;

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

  EffectOpt_MarkUsed(EVIL_HERO_DARKEST_KNIGHT);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
