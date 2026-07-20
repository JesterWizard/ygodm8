#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define ANCIENT_GEAR_FACTORY_MAX_GY 15

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 MonsterLevel(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.level;
}

static u8 IsRevealableAncientGear(u16 cardId)
{
  if (!IsAncientGearMonster(cardId))
    return FALSE;

  return MonsterLevel(cardId) >= 5;
}

static u8 CollectGyAncientGearCandidates(u8 fixedDuelist, u8 *outGyIndex, u8 *outLevels,
                                         u8 maxOut)
{
  u8 gyCount;
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount && count < maxOut; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsAncientGearMonster(cardId))
      continue;

    outGyIndex[count] = i;
    outLevels[count] = MonsterLevel(cardId);
    count++;
  }

  return count;
}

static u8 FindExactLevelMask(u8 targetLevel, u8 candCount, const u8 *levels, u16 *outMask)
{
  u16 mask;
  u16 maxMask;

  if (candCount == 0 || candCount > 15 || targetLevel == 0)
    return FALSE;

  maxMask = (u16)(1u << candCount);
  for (mask = 1; mask < maxMask; mask++) {
    u8 sum = 0;
    u8 i;

    for (i = 0; i < candCount; i++) {
      if (mask & (1u << i))
        sum += levels[i];
    }

    if (sum == targetLevel) {
      *outMask = mask;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 HandRevealHasGyCost(u16 revealId)
{
  u8 gyIndex[ANCIENT_GEAR_FACTORY_MAX_GY];
  u8 levels[ANCIENT_GEAR_FACTORY_MAX_GY];
  u8 candCount;
  u16 mask;
  u8 need;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!IsRevealableAncientGear(revealId))
    return FALSE;

  need = (u8)(MonsterLevel(revealId) * 2);
  candCount = CollectGyAncientGearCandidates(fixedDuelist, gyIndex, levels,
                                             ANCIENT_GEAR_FACTORY_MAX_GY);
  return FindExactLevelMask(need, candCount, levels, &mask);
}

static u8 CanActivateAncientGearFactory(void)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (HandRevealHasGyCost(cardId))
      return TRUE;
  }

  return FALSE;
}

static s8 PickRevealHandZone(void)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST],
                                           HandRevealHasGyCost);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (HandRevealHasGyCost(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static void BanishGyMask(u8 fixedDuelist, const u8 *gyIndex, u8 candCount, u16 mask)
{
  s8 i;

  /* Banish high indices first so lower indices stay valid. */
  for (i = (s8)candCount - 1; i >= 0; i--) {
    if (!(mask & (1u << i)))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex[i]);
  }

  GraveyardExpand_RefreshDisplay();
}

static void ANCIENT_GEAR_FACTORY_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 gyIndex[ANCIENT_GEAR_FACTORY_MAX_GY];
  u8 levels[ANCIENT_GEAR_FACTORY_MAX_GY];
  u8 candCount;
  u16 mask;
  s8 handZone;
  u16 revealId;
  u8 need;

  if (!CanActivateAncientGearFactory())
    return;

  Duel_ShowEffectText(ANCIENT_GEAR_FACTORY);

  if (IsDuelOver() == TRUE)
    return;

  handZone = PickRevealHandZone();
  if (handZone < 0)
    return;

  revealId = gTurnHands[ACTIVE_DUELIST][handZone]->id;
  if (!HandRevealHasGyCost(revealId))
    return;

  need = (u8)(MonsterLevel(revealId) * 2);
  candCount = CollectGyAncientGearCandidates(fixedDuelist, gyIndex, levels,
                                             ANCIENT_GEAR_FACTORY_MAX_GY);
  /* ponytail: no multi-select GY UI — auto-pick an exact Level-sum mask.
   * Ceiling: no player choice among valid GY sets; upgrade: DeckMenu multi-pick
   * until sum == 2× revealed Level. */
  if (!FindExactLevelMask(need, candCount, levels, &mask))
    return;

  BanishGyMask(fixedDuelist, gyIndex, candCount, mask);

  /* ponytail: "Normal Summon the revealed monster this turn without Tributing"
   * needs a turn-scoped tribute-bypass (clone Necroshade) outside this file.
   * Ceiling: reveal + GY banish only; upgrade: mark revealId + consume on NS. */

  if (spellZone != NULL && spellZone->id == ANCIENT_GEAR_FACTORY)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectANCIENT_GEAR_FACTORY(void)
{
  if (!CanActivateAncientGearFactory()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ANCIENT_GEAR_FACTORY,
                                       ANCIENT_GEAR_FACTORY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ANCIENT_GEAR_FACTORY_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  SetCardInfo(ANCIENT_GEAR_GOLEM);
  if (gCardInfo.level < 5)
    while (1)
      ;
}
#endif
