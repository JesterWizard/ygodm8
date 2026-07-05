#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "book_of_life.h"
#include "duel_helpers.h"

static u8 IsZombieMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_ZOMBIE;
}

static u8 IsMonsterCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

u8 CanActivateBookOfLife(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!IsZombieMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
    return FALSE;

  if (!IsMonsterCard(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
    return FALSE;

  return TRUE;
}

static void BookOfLife_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  Duel_ShowEffectText(BOOK_OF_LIFE);

  if (IsDuelOver() == TRUE || !CanActivateBookOfLife())
    return;

  if (Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  // ponytail: single-card GY model — banish removes opponent's top graveyard card
  if (IsMonsterCard(gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard))
    GetGraveCardAndClearGrave(INACTIVE_DUELIST);

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectBookOfLife(void)
{
  if (Duel_TryResolveSpellThroughTraps(BOOK_OF_LIFE, BookOfLife_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
