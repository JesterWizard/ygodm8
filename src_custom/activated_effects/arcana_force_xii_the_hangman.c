#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
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

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 IsDestroyableMonsterZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasOwnMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDestroyableMonsterZone(ACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasOppMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsDestroyableMonsterZone(INACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static u8 DestroyMonsterAndBurn(u8 fixedRow, u8 burnTarget)
{
  u8 col;
  u8 bestCol = 0xFF;
  u16 bestAtk = 0;
  struct DuelCard *zone;
  u16 originalAtk;
  u8 owner;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 atk;

    if (!IsDestroyableMonsterZone(fixedRow, col))
      continue;

    atk = gCardData_NEW[gFixedZones[fixedRow][col]->id].atk;
    if (bestCol == 0xFF || atk > bestAtk) {
      bestCol = col;
      bestAtk = atk;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  zone = gFixedZones[fixedRow][bestCol];
  originalAtk = gCardData_NEW[zone->id].atk;
  owner = (fixedRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  if (Duel_DestroyZone(zone, owner, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (originalAtk > 0)
    Duel_ChangeLp(burnTarget, -(s32)originalAtk, TRUE);

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

  /* Ceiling: on-Summon coin should fire at summon; OPT stand-in here.
   * Ceiling: OPT coin → destroy+burn (heads own / tails opp). FromHand SS AF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOwnMonster() || FieldHasOppMonster();
}

void ActivateARCANA_FORCE_XII_THE_HANGMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 heads;
  u8 targetRow;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_XII_THE_HANGMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  heads = RandRangeU8(0, 1) == 1;

  if (heads) {
    if (!FieldHasOwnMonster())
      return;
    targetRow = ACTIVE_DUELIST_MONSTER_ROW;
  } else {
    if (!FieldHasOppMonster())
      return;
    targetRow = INACTIVE_DUELIST_MONSTER_ROW;
  }

  /* Ceiling: coin targeting uses auto-pick highest ATK; upgrade: PickZone. */
  if (!DestroyMonsterAndBurn(targetRow, heads ? ACTIVE_DUELIST : INACTIVE_DUELIST))
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
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
