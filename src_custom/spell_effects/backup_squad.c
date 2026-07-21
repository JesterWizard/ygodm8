#include "global.h"
#include "common-chax.h"
#include "backup_squad.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "spell_effects.h"

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CanDrawBackupSquadAfterDamage(s32 damage, u8 damagedFixedDuelist)
{
  u8 turnDuelist;
  u8 fixedDuelist;

  if (damage < BACKUP_SQUAD_DAMAGE_THRESHOLD)
    return FALSE;

  if (Duel_FindBackrowCard(damagedFixedDuelist, BACKUP_SQUAD, TRUE) == NULL)
    return FALSE;

  if (EffectOpt_IsUsed(BACKUP_SQUAD))
    return FALSE;

  turnDuelist = TurnDuelistForFixed(damagedFixedDuelist);
  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  return TRUE;
}

void ApplyBackupSquadAfterDamage(s32 damage, u8 damagedFixedDuelist)
{
  u8 turnDuelist;

  if (gHideEffectText || IsDuelOver() == TRUE)
    return;

  if (!CanDrawBackupSquadAfterDamage(damage, damagedFixedDuelist))
    return;

  turnDuelist = TurnDuelistForFixed(damagedFixedDuelist);

  Duel_ShowEffectText(BACKUP_SQUAD);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(BACKUP_SQUAD);
  Duel_DrawCards(turnDuelist, 1, TRUE);
}

static void BACKUP_SQUAD_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(BACKUP_SQUAD);
}

APPEND_TEXT void EffectBACKUP_SQUAD(void)
{
  if (Duel_TryResolveSpellThroughTraps(BACKUP_SQUAD, BACKUP_SQUAD_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BACKUP_SQUAD_SelfCheck(void)
{
  if (BACKUP_SQUAD_DAMAGE_THRESHOLD != 1000)
    while (1)
      ;
}
#endif
