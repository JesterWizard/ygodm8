#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "dynamic_equip.h"
#include "junk_synchron.h"

extern const CardData gCardData_NEW[];

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsLevel2OrLowerMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].level >= 1 && gCardData_NEW[cardId].level <= 2;
}

static s8 FindBestGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsLevel2OrLowerMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return 0;
    return -1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    if (IsLevel2OrLowerMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
      return (s8)(i - 1);
  }

  return -1;
}

static void MarkSummonedMonsterNegated(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= 0x80;
      return;
    }
  }
}

void TryJunkSynchronOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 gyIndex;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (zone == NULL || zone->id != JUNK_SYNCHRON || SummonModeIsSpecial(mode))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;
  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;

  gyIndex = FindBestGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;

  Duel_ShowEffectTextTyped(JUNK_SYNCHRON, 9);

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;

    if (!IsLevel2OrLowerMonster(cardId))
      return;

    if (Duel_SpecialSummonFromGrave(turnDuelist, CARD_NONE, opts) != DUEL_ACTION_OK)
      return;

    MarkSummonedMonsterNegated(cardId);
    return;
  }

  {
    u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);

    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    if (Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts) != DUEL_ACTION_OK)
      return;

    MarkSummonedMonsterNegated(cardId);
  }
}
