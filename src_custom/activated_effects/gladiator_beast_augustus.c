#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static s8 FindGladiatorBeastHandZone(u16 excludeId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][col]->id;

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return (s8)col;
  }

  return -1;
}

unsigned char CanActivateGLADIATOR_BEAST_AUGUSTUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_AUGUSTUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_AUGUSTUS)
    return FALSE;

  /* Ceiling: OPT SS 1 other GB from hand in DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindGladiatorBeastHandZone(GLADIATOR_BEAST_AUGUSTUS) >= 0;
}

void ActivateGLADIATOR_BEAST_AUGUSTUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  s8 handZone;

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_AUGUSTUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  handZone = FindGladiatorBeastHandZone(GLADIATOR_BEAST_AUGUSTUS);
  if (handZone < 0 || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
