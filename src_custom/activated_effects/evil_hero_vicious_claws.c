#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

extern const CardData gCardData_NEW[];

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sClawsInit APPEND_DATA = {0};
static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sEvilHeroName[] APPEND_RODATA = "Evil HERO";

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static struct DuelCard *FindHeroOnField(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && IsHeroMonster(zone->id))
        return zone;
    }
  }

  return NULL;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static s8 FindClawsInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == EVIL_HERO_VICIOUS_CLAWS)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == EVIL_HERO_VICIOUS_CLAWS)
      return (s8)i;
  }
  return -1;
}

static u8 GyHasMonsterMentioningDarkFusion(u8 fixedDuelist)
{
  u8 i;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
        && gCardData_NEW[cardId].color == FUSION_CARD
        && Duel_CardNameContains(cardId, sEvilHeroName);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (gCardData_NEW[cardId].color != FUSION_CARD)
      continue;
    if (Duel_CardNameContains(cardId, sEvilHeroName))
      return TRUE;
  }
  return FALSE;
}

static void TryDestroyOneFieldCard(u8 turnDuelist)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || zone->id == EVIL_HERO_VICIOUS_CLAWS)
        continue;

      Duel_DestroyZone(zone, turnDuelist, FALSE);
      return;
    }
  }
}

static void TryClawsGySs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monRow = turnDuelist == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                            : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  s8 gyIndex;

  /* Printed remainder omitted by this ruleset. */
  if (EffectOpt_IsUsed(EVIL_HERO_VICIOUS_CLAWS))
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monRow]) < 0)
    return;

  gyIndex = FindClawsInGy(fixedDuelist);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(EVIL_HERO_VICIOUS_CLAWS, 8);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, EVIL_HERO_VICIOUS_CLAWS, opts)
      != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(EVIL_HERO_VICIOUS_CLAWS);

  if (GyHasMonsterMentioningDarkFusion(fixedDuelist))
    TryDestroyOneFieldCard(turnDuelist);

  UpdateDuelGfxExceptField();
}

static void OnMonsterDestroyedWhileClawsInGy(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId == CARD_NONE || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (ev->cardId == EVIL_HERO_VICIOUS_CLAWS)
    return;
  if (GetTypeGroup(ev->cardId) != TYPE_GROUP_MONSTER)
    return;
  if (FindClawsInGy(ev->controller) < 0)
    return;

  TryClawsGySs(ev->controller);
}

void EvilHeroViciousClaws_EnsureInit(void)
{
  if (sClawsInit)
    return;

  sClawsInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnMonsterDestroyedWhileClawsInGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnMonsterDestroyedWhileClawsInGy);
}

unsigned char CanActivateEVIL_HERO_VICIOUS_CLAWS(void)
{
  if (gMonEffect.id != EVIL_HERO_VICIOUS_CLAWS)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  return FALSE;
}

void ActivateEVIL_HERO_VICIOUS_CLAWSEffect(void)
{
  Duel_ShowEffectTextTyped(EVIL_HERO_VICIOUS_CLAWS, 2);
}

u8 CanSpecialSummonEvilHeroViciousClawsFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != EVIL_HERO_VICIOUS_CLAWS)
    return FALSE;

  if (FindHeroOnField() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonEvilHeroViciousClawsFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *hero;

  if (!CanSpecialSummonEvilHeroViciousClawsFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(EVIL_HERO_VICIOUS_CLAWS, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  hero = FindHeroOnField();
  if (hero == NULL)
    return FALSE;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  /* +300 ≈ +1 tempStage (~500). */
  if (hero->tempStage < 127)
    hero->tempStage = (s8)(hero->tempStage + 1);

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonEvilHeroViciousClawsFromHand(u8 handZone);
u8 TrySpecialSummonEvilHeroViciousClawsFromHand(u8 handZone);
#endif
