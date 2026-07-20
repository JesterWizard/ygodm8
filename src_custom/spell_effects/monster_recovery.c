#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

/* willChangeSides marks opponent-owned cards (return-at-end / stolen). */
static u8 ZoneOwnedByController(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return zone->willChangeSides == FALSE;
}

static u8 HandHasOpponentOwnedCard(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (zone->id == CARD_NONE)
      continue;
    if (zone->willChangeSides)
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidMonsterRecoveryTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return ZoneOwnedByController(zone);
}

static u8 HasMonsterRecoveryTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidMonsterRecoveryTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateMONSTER_RECOVERY(void)
{
  if (HandHasOpponentOwnedCard())
    return FALSE;

  return HasMonsterRecoveryTarget();
}

static void ReturnCardToDeck(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void DestroyMonsterRecoverySpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MONSTER_RECOVERY)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void CancelMonsterRecoveryTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMonsterRecoverySpellZone();
}

static u8 AiPickMonsterRecoveryTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u16 bestAtk = 0xFFFF;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidMonsterRecoveryTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void FinishMonsterRecovery(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];
  u8 handCount = 0;
  u8 i;
  u16 monsterId;

  if (!IsValidMonsterRecoveryTarget(fixedRow, fixedCol)) {
    DestroyMonsterRecoverySpellZone();
    return;
  }

  /* Target must still be on field (printed condition). */
  monsterId = target->id;
  ClearZone(target);
  NotifyDynamicEquipFieldChanged();
  Duel_NotifyFixedMonsterRowChanged(fixedRow);
  ReturnCardToDeck(ACTIVE_DUELIST, monsterId);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *handCard = gTurnHands[ACTIVE_DUELIST][i];
    u16 cardId;

    if (handCard->id == CARD_NONE)
      continue;

    cardId = handCard->id;
    ClearZone(handCard);
    ReturnCardToDeck(ACTIVE_DUELIST, cardId);
    handCount++;
  }

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  if (handCount > 0) {
    if (Duel_DrawCards(ACTIVE_DUELIST, handCount, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  DestroyMonsterRecoverySpellZone();
}

static void ResolveMonsterRecoveryTarget(u8 fixedRow, u8 fixedCol)
{
  FinishMonsterRecovery(fixedRow, fixedCol);
}

static void MONSTER_RECOVERY_ResolveBody(void)
{
  Duel_ShowEffectText(MONSTER_RECOVERY);

  if (IsDuelOver() == TRUE || !CanActivateMONSTER_RECOVERY())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidMonsterRecoveryTarget, ResolveMonsterRecoveryTarget,
                     CancelMonsterRecoveryTargeting, AiPickMonsterRecoveryTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMONSTER_RECOVERY(void)
{
  if (!CanActivateMONSTER_RECOVERY()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MONSTER_RECOVERY, MONSTER_RECOVERY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MONSTER_RECOVERY_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = BLUE_EYES_WHITE_DRAGON;
  zone.willChangeSides = FALSE;
  if (!ZoneOwnedByController(&zone))
    while (1)
      ;

  zone.willChangeSides = TRUE;
  if (ZoneOwnedByController(&zone))
    while (1)
      ;
}
#endif
