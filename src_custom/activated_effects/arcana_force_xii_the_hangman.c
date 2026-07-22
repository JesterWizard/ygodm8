#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "arcana_force_coin.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static u8 sHangmanTargetRow APPEND_DATA = {0};
static u8 sHangmanBurnTarget APPEND_DATA = {0};
static struct DuelCard *sHangmanSelf APPEND_DATA = {NULL};

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 IsDestroyableMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 ActiveFixedMonsterRow(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return PLAYER_MONSTER_ROW;

  return OPPONENT_MONSTER_ROW;
}

static u8 InactiveFixedMonsterRow(void)
{
  return ActiveFixedMonsterRow() == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW
                                                       : PLAYER_MONSTER_ROW;
}

static u8 FieldHasOwnMonster(void)
{
  u8 col;
  u8 row = ActiveFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDestroyableMonsterZone(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasOppMonster(void)
{
  u8 col;
  u8 row = InactiveFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDestroyableMonsterZone(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHangmanCoinTarget(u8 fixedRow, u8 fixedCol)
{
  return fixedRow == sHangmanTargetRow && IsDestroyableMonsterZone(fixedRow, fixedCol);
}

static void CancelHangmanTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickHangmanTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 atk;

    if (!IsHangmanCoinTarget(sHangmanTargetRow, col))
      continue;

    atk = gCardData_NEW[gFixedZones[sHangmanTargetRow][col]->id].atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outRow = sHangmanTargetRow;
  *outCol = bestCol;
  return TRUE;
}

static void ResolveHangmanTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u16 originalAtk;
  u8 owner;

  if (!IsHangmanCoinTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  originalAtk = gCardData_NEW[zone->id].atk;
  owner = (fixedRow == ActiveFixedMonsterRow()) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (sHangmanSelf != NULL)
    MarkMonsterEffectUsed(sHangmanSelf);

  if (Duel_DestroyZone(zone, owner, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (originalAtk > 0)
    Duel_ChangeLp(sHangmanBurnTarget, -(s32)originalAtk, TRUE);

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void SetCursorAtZone(struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (zone == NULL)
    return;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gFixedZones[row][col] == zone) {
        gDuelCursor.destY = row;
        gDuelCursor.destX = col;
        return;
      }
    }
  }
}

static u8 ResolveArcanaForceXiiTheHangmanCoin(struct DuelCard *self, u8 blockingPick)
{
  u8 heads;

  if (IsDuelOver() == TRUE)
    return FALSE;

  heads = RandRangeU8(0, 1) == 1;
  ArcanaForce_AnnounceCoinResult(ARCANA_FORCE_XII_THE_HANGMAN, heads);

  if (heads) {
    if (!FieldHasOwnMonster())
      return FALSE;
    sHangmanTargetRow = ActiveFixedMonsterRow();
    sHangmanBurnTarget = ACTIVE_DUELIST;
  } else {
    if (!FieldHasOppMonster())
      return FALSE;
    sHangmanTargetRow = InactiveFixedMonsterRow();
    sHangmanBurnTarget = INACTIVE_DUELIST;
  }

  sHangmanSelf = self;

  if (self != NULL)
    SetCursorAtZone(self);
  else {
    gDuelCursor.destY = gMonEffect.row;
    gDuelCursor.destX = gMonEffect.zone;
  }

  Duel_SetupPickZone(IsHangmanCoinTarget, ResolveHangmanTarget, CancelHangmanTargeting,
                     AiPickHangmanTarget);

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    if (blockingPick)
      Duel_RunPickZoneInputLoop();
    else
      Duel_EnterPickZoneTargeting();
  } else {
    Duel_ResolvePickZoneForAi();
  }

  return TRUE;
}

static s8 FindArcanaForceHandZone(u8 preferExclude)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  s8 fallback = -1;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id;

    if (!IsArcanaForceMonster(cardId))
      continue;

    if (i == preferExclude) {
      fallback = (s8)i;
      continue;
    }

    return (s8)i;
  }

  return fallback;
}

unsigned char CanActivateARCANA_FORCE_XII_THE_HANGMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARCANA_FORCE_XII_THE_HANGMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARCANA_FORCE_XII_THE_HANGMAN)
    return FALSE;

  /* OPT coin → destroy+burn (heads own / tails opp). Hand SS Arcana Force. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOwnMonster() || FieldHasOppMonster();
}

void ActivateARCANA_FORCE_XII_THE_HANGMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XII_THE_HANGMAN, 2);

  (void)ResolveArcanaForceXiiTheHangmanCoin(self, FALSE);
}

void TryArcanaForceXiiTheHangmanOnMonsterPlacement(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ARCANA_FORCE_XII_THE_HANGMAN)
    return;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XII_THE_HANGMAN, 2);
  (void)ResolveArcanaForceXiiTheHangmanCoin(NULL, TRUE);
}

u8 CanActivateArcanaForceXiiTheHangmanFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ARCANA_FORCE_XII_THE_HANGMAN)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindArcanaForceHandZone(0xFF) >= 0;
}

u8 TryActivateArcanaForceXiiTheHangmanFromHand(u8 handZone)
{
  struct DuelSummonOpts opts;
  s8 ssZone;

  if (!CanActivateArcanaForceXiiTheHangmanFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XII_THE_HANGMAN, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* Reveal Hangman (no cost); SS 1 Arcana Force from hand in DEF (prefer other). */
  ssZone = FindArcanaForceHandZone(handZone);
  if (ssZone < 0)
    ssZone = (s8)handZone;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, (u8)ssZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateArcanaForceXiiTheHangmanFromHand(u8 handZone);
u8 TryActivateArcanaForceXiiTheHangmanFromHand(u8 handZone);
#endif
