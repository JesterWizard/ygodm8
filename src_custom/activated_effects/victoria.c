#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static const u8 sVictoriaPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 OppFixedDuelist(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_OPPONENT;

  return DUEL_PLAYER;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u8 OppGyHasDragon(u8 oppFixed)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[oppFixed].graveyard;

    return IsDragonMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(oppFixed); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(oppFixed, i);

    if (IsDragonMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadOppDragonGyMenu(u8 oppFixed, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(oppFixed);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(oppFixed, i);

    if (!IsDragonMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
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

static s8 FindBestOppDragonGyIndexForAi(u8 oppFixed)
{
  u8 gyCount = GraveyardExpand_GetCount(oppFixed);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(oppFixed, i);

    if (!IsDragonMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    SetCardInfo(cardId);
    if (bestIndex == 0xFF || gCardInfo.atk > bestAtk) {
      bestAtk = gCardInfo.atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickOppDragonGyIndex(u8 oppFixed)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadOppDragonGyMenu(oppFixed, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sVictoriaPickLabels, ARRAY_COUNT(sVictoriaPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static enum DuelActionResult SpecialSummonDragonFromOppGy(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 oppFixed = OppFixedDuelist();
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[oppFixed].graveyard;
    if (!IsDragonMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    gDuel.duelistbattleState[oppFixed].graveyard = CARD_NONE;
    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(oppFixed, gyIndex);
  if (!IsDragonMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(oppFixed, gyIndex);
  GraveyardExpand_SyncLegacyTop(oppFixed);
  GraveyardExpand_RefreshDisplay();
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

unsigned char CanActivateVICTORIA(void)
{
  struct DuelCard *zone;
  u8 oppFixed;

  if (gMonEffect.id != VICTORIA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VICTORIA)
    return FALSE;

  /* ponytail: continuous attack redirect for other face-up Fairies needs
   * attack-target hook. Ceiling: OPT SS 1 Dragon from opponent's GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  oppFixed = OppFixedDuelist();
  return OppGyHasDragon(oppFixed);
}

void ActivateVICTORIAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 oppFixed = OppFixedDuelist();
  s8 gyIndex;

  Duel_ShowEffectTextTyped(VICTORIA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickOppDragonGyIndex(oppFixed);
  else if (GraveyardExpand_IsEnabled())
    gyIndex = FindBestOppDragonGyIndexForAi(oppFixed);
  else
    gyIndex = OppGyHasDragon(oppFixed) ? 0 : -1;

  if (gyIndex < 0)
    return;

  if (SpecialSummonDragonFromOppGy((u8)gyIndex) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
