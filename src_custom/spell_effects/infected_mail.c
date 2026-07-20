#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

#define INFECTED_MAIL_MAX_LEVEL 4

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsLevel4OrLowerMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].level > 0
      && gCardData_NEW[cardId].level <= INFECTED_MAIL_MAX_LEVEL;
}

static u8 IsValidInfectedMailTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsLevel4OrLowerMonster(zone->id);
}

static u8 HasInfectedMailTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidInfectedMailTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateInfectedMailIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != INFECTED_MAIL || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return HasInfectedMailTarget();
}

static void GrantDirectAttackThisTurn(struct DuelCard *target)
{
  /* ponytail: direct-attack grant needs a Can*AttackDirectly hook in
   * code_8043EF4_hooks / ai_attack_hooks (Ice Edge / Jowls pattern).
   * Ceiling: marks zone->unkTwo only; upgrade: CanInfectedMailMonsterAttackDirectly
   * → zone->unkTwo && controller has face-up INFECTED_MAIL. */
  target->unkTwo = TRUE;

  /* ponytail: "Send it to the Graveyard at the end of the Battle Phase" needs an
   * end-of-BP hook outside this file. Ceiling: mark only; upgrade: BP-end → if
   * zone still marked, Duel_DestroyZone to controller GY. */
}

static void ResolveInfectedMailTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidInfectedMailTarget(fixedRow, fixedCol))
    return;

  GrantDirectAttackThisTurn(target);

  if (spellZone != NULL && spellZone->id == INFECTED_MAIL)
    spellZone->effectUsedThisTurn = TRUE;
}

static void CancelInfectedMailTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  /* Continuous stays on field; ignition cancelled without OPT spend. */
}

static u8 AiPickInfectedMailTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidInfectedMailTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void BeginInfectedMailIgnition(struct DuelCard *zone)
{
  if (!CanActivateInfectedMailIgnition(zone))
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidInfectedMailTarget, ResolveInfectedMailTarget,
                     CancelInfectedMailTargeting, AiPickInfectedMailTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void INFECTED_MAIL_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up continuous (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateInfectedMailIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    Duel_ShowEffectText(INFECTED_MAIL);
    if (IsDuelOver() == TRUE)
      return;

    BeginInfectedMailIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(INFECTED_MAIL);

  if (IsDuelOver() == TRUE)
    return;

  if (CanActivateInfectedMailIgnition(zone))
    BeginInfectedMailIgnition(zone);

  /* ponytail: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up
   * OPT re-activation may need card_hooks GetSpellType + INFECTED_MAIL listed.
   * Ceiling: first-activation OPT works; upgrade: add to NORMAL spell-type list. */
}

APPEND_TEXT void EffectINFECTED_MAIL(void)
{
  if (Duel_TryResolveSpellThroughTraps(INFECTED_MAIL, INFECTED_MAIL_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void INFECTED_MAIL_SelfCheck(void)
{
  if (!IsLevel4OrLowerMonster(AMAZONESS_ARCHER))
    while (1)
      ;
  if (IsLevel4OrLowerMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
