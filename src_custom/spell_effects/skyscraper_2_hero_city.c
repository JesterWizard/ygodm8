#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);

static const u8 sSkyscraper2PickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static u8 IsElementalHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_IsElementalHeroCard(cardId);
}

static s8 FindFirstEligibleGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsElementalHeroMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsElementalHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadEligibleGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsElementalHeroMonster(cardId))
      continue;

    gyIndexMap[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 PlayerPickGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadEligibleGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sSkyscraper2PickLabels, ARRAY_COUNT(sSkyscraper2PickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonEligibleFromGrave(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsElementalHeroMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsElementalHeroMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static u8 CanActivateSkyscraper2Ignition(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (zone == NULL || zone->id != SKYSCRAPER_2_HERO_CITY || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return IsElementalHeroMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

  return FindFirstEligibleGyIndex(fixedDuelist) >= 0;
}

static void ResolveSkyscraper2Ignition(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  if (!CanActivateSkyscraper2Ignition(zone))
    return;

  Duel_ShowEffectText(SKYSCRAPER_2_HERO_CITY);

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: no "destroyed by battle" GY filter — no destroy-reason memory on
   * expanded GY cards. Ceiling: any Elemental HERO in GY is legal; upgrade:
   * stamp battle-destroy on GY push / zone→GY, then filter IsElementalHeroMonster
   * && wasDestroyedByBattle. */

  if (!GraveyardExpand_IsEnabled()) {
    if (SpecialSummonEligibleFromGrave(0) == DUEL_ACTION_DUEL_OVER)
      return;
    zone->effectUsedThisTurn = TRUE;
    UpdateDuelGfxExceptField();
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindFirstEligibleGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  if (SpecialSummonEligibleFromGrave((u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void SKYSCRAPER_2_HERO_CITY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up field (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivateSkyscraper2Ignition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveSkyscraper2Ignition(zone);
    return;
  }

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);

  if (CanActivateSkyscraper2Ignition(zone))
    ResolveSkyscraper2Ignition(zone);
  else
    Duel_ShowEffectText(SKYSCRAPER_2_HERO_CITY);
}

APPEND_TEXT void EffectSKYSCRAPER_2_HERO_CITY(void)
{
  /* ponytail: not in GetSpellType NORMAL override (unlike VALHALLA) — face-up
   * OPT re-activation may need card_hooks GetSpellType + SKYSCRAPER_2_HERO_CITY
   * listed. Ceiling: first-activation OPT works; upgrade: add to NORMAL list. */
  if (Duel_TryResolveSpellThroughTraps(SKYSCRAPER_2_HERO_CITY,
                                       SKYSCRAPER_2_HERO_CITY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SKYSCRAPER_2_HERO_CITY_SelfCheck(void)
{
  if (!IsElementalHeroMonster(ELEMENTAL_HERO_SPARKMAN))
    while (1)
      ;
  if (IsElementalHeroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
