#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"
#include "world_suppression.h"

void SetDuelFieldGfx(u8 field);
void UpdateDuelGfxExceptField(void);

static const u8 sPseudoSpacePickLabels[] APPEND_RODATA = {
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

static u8 IsFieldSpellCard(u16 cardId)
{
  if (cardId == PSEUDO_SPACE || cardId == HARPIES_HUNTING_GROUND
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == NEO_SPACE)
    return TRUE;

  if (WorldSuppression_IsFieldSpellCard(cardId))
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  return IsFieldSpellCard(cardId);
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

static s8 FindFirstFieldSpellGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (IsFieldSpellCard(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return 0;
    return -1;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsFieldSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadFieldSpellGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsFieldSpellCard(cardId))
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

static s8 PlayerPickFieldSpellGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadFieldSpellGyMenu(fixedDuelist, gyIndexMap);
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
          sPseudoSpacePickLabels, ARRAY_COUNT(sPseudoSpacePickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 BanishFieldSpellFromGy(u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsFieldSpellCard(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsFieldSpellCard(cardId))
    return FALSE;

  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

static u8 CanActivatePseudoSpaceIgnition(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (zone == NULL || zone->id != PSEUDO_SPACE || zone->isFaceUp == FALSE)
    return FALSE;

  if (zone->effectUsedThisTurn)
    return FALSE;

  return FindFirstFieldSpellGyIndex(fixedDuelist) >= 0;
}

static void ResolvePseudoSpaceIgnition(struct DuelCard *zone)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  if (!CanActivatePseudoSpaceIgnition(zone))
    return;

  Duel_ShowEffectText(PSEUDO_SPACE);

  if (IsDuelOver() == TRUE)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    if (!BanishFieldSpellFromGy(0))
      return;
    zone->effectUsedThisTurn = TRUE;
    UpdateDuelGfxExceptField();

    /* ponytail: name-become + replace effects until End Phase need copy-host /
     * turn_effect hooks outside this file (no per-zone name/effect RAM here).
     * Ceiling: OPT banish Field Spell from GY only; upgrade: store banished id
     * → treat zone as that Field Spell until End Phase clear. */
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    gyIndex = PlayerPickFieldSpellGyIndex(fixedDuelist);
  else
    gyIndex = FindFirstFieldSpellGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  if (!BanishFieldSpellFromGy((u8)gyIndex))
    return;

  zone->effectUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();

  /* ponytail: name-become + replace effects until End Phase — same ceiling as
   * legacy-GY path above. */
}

static void PSEUDO_SPACE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  /* Re-activation of face-up field (OPT ignition). */
  if (zone != NULL && zone->isLocked) {
    if (!CanActivatePseudoSpaceIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolvePseudoSpaceIgnition(zone);
    return;
  }

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);

  if (CanActivatePseudoSpaceIgnition(zone))
    ResolvePseudoSpaceIgnition(zone);
  else
    Duel_ShowEffectText(PSEUDO_SPACE);
}

APPEND_TEXT void EffectPSEUDO_SPACE(void)
{
if (Duel_TryResolveSpellThroughTraps(PSEUDO_SPACE, PSEUDO_SPACE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void PSEUDO_SPACE_SelfCheck(void)
{
  if (!IsFieldSpellCard(PSEUDO_SPACE))
    while (1)
      ;
  if (!IsFieldSpellCard(BURNING_LAND))
    while (1)
      ;
  if (IsFieldSpellCard(POT_OF_GREED))
    while (1)
      ;
}
#endif
