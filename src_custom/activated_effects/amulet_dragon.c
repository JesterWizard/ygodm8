#include "global.h"
#include "common-chax.h"
#include "amulet_dragon.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const u8 sAmuletDragonPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 IsSpellcasterMonster(u16 cardId)
{
  return Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 AnyGraveyardHasSpell(void)
{
  u8 fixedDuelist;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = GraveyardExpand_GetCount(fixedDuelist);
    u8 i;

    for (i = 0; i < count; i++) {
      if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
        return TRUE;
    }
  }

  return FALSE;
}

/* Ceiling: no multi-select GY UI — banish every Spell in both GYs (min.1 gate above). */
static u8 BanishAllSpellsFromGraveyards(void)
{
  u8 banished = 0;
  u8 fixedDuelist;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    s8 i;

    for (i = (s8)GraveyardExpand_GetCount(fixedDuelist) - 1; i >= 0; i--) {
      if (!IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, (u8)i)))
        continue;

      Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)i);
      banished++;
    }
  }

  if (banished > 0)
    GraveyardExpand_RefreshDisplay();

  return banished;
}

static u8 GraveyardHasSpellcaster(u8 fixedDuelist)
{
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    if (IsSpellcasterMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadSpellcasterGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsSpellcasterMonster(cardId))
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

static s8 FindBestSpellcasterGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsSpellcasterMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickSpellcasterGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadSpellcasterGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(
          sAmuletDragonPickLabels, ARRAY_COUNT(sAmuletDragonPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonSpellcasterFromGrave(u8 turnDuelist, u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[turnDuelist]->graveyard;
    if (!IsSpellcasterMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsSpellcasterMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtTurn(turnDuelist, gyIndex);
  if (!IsSpellcasterMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
}

static void ResolveSpellcasterSpecialSummon(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 gyIndex;

  if (!GraveyardHasSpellcaster(fixedDuelist))
    return;

  /* Popup already shown by ActivateAmuletDragonDestroy — then GY menu, then SS. */
  if (WhoseTurn() == DUEL_PLAYER && turnDuelist == ACTIVE_DUELIST
      && GraveyardExpand_IsEnabled() && !gHideEffectText)
    gyIndex = PlayerPickSpellcasterGyIndex(fixedDuelist);
  else if (GraveyardExpand_IsEnabled())
    gyIndex = FindBestSpellcasterGyIndexForAi(fixedDuelist);
  else
    gyIndex = 0;

  if (gyIndex < 0)
    return;

  if (SpecialSummonSpellcasterFromGrave(turnDuelist, (u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void ResolveAmuletDragonOnSpecialSummon(struct DuelCard *zone)
{
  u8 banished;

  if (zone == NULL || zone->id != AMULET_DRAGON)
    return;

  /* Special Summon marks unk4=2; skip Normal Summon / already-resolved. */
  if (zone->unk4 != 2)
    return;

  if (!AnyGraveyardHasSpell()) {
    zone->unk4 = 1;
    return;
  }

  if (IsSkillDrainActiveOnField()
      && TryActivateSkillDrainAndNegateCardId(AMULET_DRAGON)) {
    zone->unk4 = 1;
    return;
  }

  /* On-summon text after field draw so Amulet Dragon is visible (fusion uses
   * updateGfx=FALSE). */
  UpdateDuelGfxExceptField();

  Duel_ShowCardEffectText(AMULET_DRAGON, CARD_EFFECT_TEXT_AMULET_DRAGON_POPUP_1);
  if (IsDuelOver() == TRUE)
    return;

  banished = BanishAllSpellsFromGraveyards();
  if (banished > 0) {
    if (banished > 127)
      banished = 127;
    zone->permStage = (s8)banished;
    Duel_RefreshMonsterStatOverlays();
  }

  zone->unk4 = 1;
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 AmuletDragon_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 baseAtk;
  u16 baseDef;
  u8 count;

  if (zone == NULL || zone->id != AMULET_DRAGON)
    return FALSE;

  SetCardInfo(zone->id);
  baseAtk = gCardInfo.atk;
  baseDef = gCardInfo.def;
  count = (u8)zone->permStage;
  Duel_WriteCardInfoStats(zone->id,
                          Duel_StatFromCount(count, AMULET_DRAGON_ATK_PER_BANISH, baseAtk),
                          baseDef);
  return TRUE;
}

void TryAmuletDragonOnMonsterPlacement(struct DuelCard *zone)
{
  ResolveAmuletDragonOnSpecialSummon(zone);
}

unsigned char ShouldActivateAmuletDragonDestroy(void)
{
  u8 turnDuelist;
  u8 fixedDuelist;
  u8 monsterRow;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != AMULET_DRAGON)
    return FALSE;

  if (gActiveEffect.turnRow == 7) {
    if (gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard != AMULET_DRAGON)
      return FALSE;
    turnDuelist = INACTIVE_DUELIST;
  } else {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != AMULET_DRAGON)
      return FALSE;
    turnDuelist = ACTIVE_DUELIST;
  }

  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  return GraveyardHasSpellcaster(fixedDuelist);
}

void ActivateAmuletDragonDestroy(void)
{
  u8 turnDuelist;

  if (gActiveEffect.turnRow == 7)
    turnDuelist = INACTIVE_DUELIST;
  else
    turnDuelist = ACTIVE_DUELIST;

  Duel_ShowCardEffectText(AMULET_DRAGON, CARD_EFFECT_TEXT_AMULET_DRAGON_POPUP_2);
  if (IsDuelOver() == TRUE)
    return;

  GetGraveCardAndClearGrave(turnDuelist);
  UpdateDuelGfxExceptField();
  ResolveSpellcasterSpecialSummon(turnDuelist);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AmuletDragon_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = AMULET_DRAGON;
  zone.permStage = 3;
  AmuletDragon_ApplyDynamicZoneStats(&zone);
  if (gCardInfo.atk != 2900 + 3 * AMULET_DRAGON_ATK_PER_BANISH)
    while (1)
      ;
}
#endif
