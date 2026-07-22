#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sHeroName[] APPEND_RODATA = "HERO";

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

unsigned char CanActivateEVIL_HERO_VICIOUS_CLAWS(void)
{
  if (gMonEffect.id != EVIL_HERO_VICIOUS_CLAWS)
    return FALSE;

  /* Ceiling: GY destroy-revive + Dark Fusion destroy branch need GY/destroy hooks.
   * Ceiling: FromHand target HERO → SS DEF +300 ATK stand-in. */
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

  /* Ceiling: +300 ≈ +1 tempStage (~500). */
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
