#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(void);

extern const CardData gCardData_NEW[];

static u8 FixedDuelistForOwner(void)
{
  if (gMonEffect.row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  return DUEL_OPPONENT;
}

static u8 IsLevel2OrLowerMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return gCardData_NEW[cardId].level >= 1 && gCardData_NEW[cardId].level <= 2;
}

static u8 HasLevel2OrLowerInGraveyard(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsLevel2OrLowerMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLevel2OrLowerMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }
  return FALSE;
}

static u8 IsValidTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target validation */
  (void)fixedRow;
  (void)fixedCol;
  return FALSE;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  /* TODO: implement target resolution */
  (void)fixedRow;
  (void)fixedCol;
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  /* TODO: implement AI target selection */
  (void)outRow;
  (void)outCol;
  return FALSE;
}

unsigned char CanActivateJUNK_SYNCHRON(void)
{
  if (gMonEffect.id != JUNK_SYNCHRON)
    return FALSE;
  return HasLevel2OrLowerInGraveyard(FixedDuelistForOwner());
}

void ActivateJUNK_SYNCHRONEffect(void)
{
  Duel_ShowEffectTextTyped(JUNK_SYNCHRON, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidTarget, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
