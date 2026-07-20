#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define HARPIES_FEATHER_REST_RETURN_COUNT 3

void UpdateDuelGfxExceptField(void);

static const char sHarpieName[] APPEND_RODATA = "Harpie";

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS;
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 CountHarpieLadyOrSistersInGy(u8 fixedDuelist)
{
  u8 count = 0;
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsHarpieLadyOrSisters(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsHarpieLadyOrSisters(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ControlsLevel5OrHigherHarpie(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (!MonsterIsFaceUp(zone) || !IsHarpieMonster(zone->id))
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level >= 5)
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateHarpiesFeatherRest(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (EffectOpt_IsUsed(HARPIES_FEATHER_REST))
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  return CountHarpieLadyOrSistersInGy(fixedDuelist) >= HARPIES_FEATHER_REST_RETURN_COUNT;
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

/* Collect most-recent matching GY indices (high→low). */
static u8 CollectRecentHarpieLadyGyIndices(u8 fixedDuelist, u8 *outIndices)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 found = 0;
  s8 i;

  for (i = (s8)gyCount - 1; i >= 0 && found < HARPIES_FEATHER_REST_RETURN_COUNT; i--) {
    if (!IsHarpieLadyOrSisters(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
      continue;

    outIndices[found++] = (u8)i;
  }

  return found;
}

static void ShuffleHarpieLadyFromGraveToDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 indices[HARPIES_FEATHER_REST_RETURN_COUNT];
  u8 found;
  u8 i;

  /* ponytail: no multi-select GY UI — return 3 most recent Harpie Lady /
   * Harpie Lady Sisters. Ceiling: no targeting; upgrade: DeckMenu multi-pick. */
  found = CollectRecentHarpieLadyGyIndices(fixedDuelist, indices);
  if (found < HARPIES_FEATHER_REST_RETURN_COUNT)
    return;

  for (i = 0; i < HARPIES_FEATHER_REST_RETURN_COUNT; i++) {
    u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, indices[i]);

    ReturnCardToDeck(turnDuelist, cardId);
  }

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  Duel_ShuffleDeckFromDrawn(turnDuelist);
}

static void HARPIES_FEATHER_REST_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 drawCount;
  u8 hadLevel5Harpie;

  if (!CanActivateHarpiesFeatherRest())
    return;

  /* Condition checked at activation (before shuffle). */
  hadLevel5Harpie = ControlsLevel5OrHigherHarpie();
  drawCount = hadLevel5Harpie ? 2 : 1;

  Duel_ShowEffectText(HARPIES_FEATHER_REST);

  if (IsDuelOver() == TRUE)
    return;

  ShuffleHarpieLadyFromGraveToDeck(ACTIVE_DUELIST);

  if (Duel_DrawCards(ACTIVE_DUELIST, drawCount, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(HARPIES_FEATHER_REST);

  if (spellZone != NULL && spellZone->id == HARPIES_FEATHER_REST)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);

  /* ponytail: "cannot Special Summon except WIND for the rest of this turn"
   * needs a Special Summon lock hook outside this file (ArchlordKristya-style
   * attribute gate). Ceiling: no SS lock after resolve; upgrade: turn flag →
   * Duel_SpecialSummon* reject non-ATTRIBUTE_WIND until End Phase clear. */

  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectHARPIES_FEATHER_REST(void)
{
  if (!CanActivateHarpiesFeatherRest()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(HARPIES_FEATHER_REST, HARPIES_FEATHER_REST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HARPIES_FEATHER_REST_SelfCheck(void)
{
  if (!IsHarpieLadyOrSisters(HARPIE_LADY))
    while (1)
      ;
  if (!IsHarpieLadyOrSisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (IsHarpieLadyOrSisters(CYBER_SLASH_HARPIE_LADY))
    while (1)
      ;
  if (!IsHarpieMonster(HARPIE_LADY_SISTERS))
    while (1)
      ;
}
#endif
