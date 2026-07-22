#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static const u8 sDystopiaPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsValidGyTarget(u16 cardId)
{
  if (!IsDestinyHeroMonster(cardId))
    return FALSE;

  if (cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  return gCardData_NEW[cardId].level <= 4;
}

static u8 GyHasTarget(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsValidGyTarget(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsValidGyTarget(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsValidGyTarget(cardId))
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

static s8 FindBestGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsValidGyTarget(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestIndex = i;
      bestAtk = atk;
    }
  }

  return (s8)bestIndex;
}

static s8 PlayerPickGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sDystopiaPickLabels,
                                         ARRAY_COUNT(sDystopiaPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u16 GetPrintedAtk(u16 cardId)
{
  if (cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].atk;
}

static void BurnForGyIndexTo(u8 fixedDuelist, s8 gyIndex, u8 burnTargetTurn)
{
  u16 cardId;
  u16 burn;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsValidGyTarget(cardId))
      return;

    burn = GetPrintedAtk(cardId);
    if (burn == 0)
      return;

    Duel_ChangeLp(burnTargetTurn, -(s32)burn, TRUE);
    return;
  }

  if (gyIndex < 0)
    return;

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);
  if (!IsValidGyTarget(cardId))
    return;

  burn = GetPrintedAtk(cardId);
  if (burn == 0)
    return;

  Duel_ChangeLp(burnTargetTurn, -(s32)burn, TRUE);
}

static void BurnForGyIndex(u8 fixedDuelist, s8 gyIndex)
{
  BurnForGyIndexTo(fixedDuelist, gyIndex, INACTIVE_DUELIST);
}

static void BurnForGyIndexForOpp(u8 fixedDuelist, u8 controllerTurn, s8 gyIndex)
{
  u8 opp = controllerTurn == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  BurnForGyIndexTo(fixedDuelist, gyIndex, opp);
}

void TryDestinyHeroDystopiaOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 gyIndex;

  if (zone == NULL || zone->id != DESTINY_HERO_DYSTOPIA || gHideEffectText)
    return;

  if (EffectOpt_IsUsed(DESTINY_HERO_DYSTOPIA))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (!GyHasTarget(fixedDuelist))
    return;

  /* printed is on-SS; any placement stand-in. Player GY trunk pick when expanded. */
  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindBestGyIndex(fixedDuelist);

  if (gyIndex < 0 && !GraveyardExpand_IsEnabled())
    gyIndex = 0;
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DYSTOPIA, 8);
  BurnForGyIndexForOpp(fixedDuelist, turnDuelist, gyIndex);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DYSTOPIA);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateDESTINY_HERO_DYSTOPIA(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;

  if (gMonEffect.id != DESTINY_HERO_DYSTOPIA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DYSTOPIA)
    return FALSE;

  /* Printed remainder omitted by this ruleset. */
  if (EffectOpt_IsUsed(DESTINY_HERO_DYSTOPIA))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  fixedDuelist = FixedDuelistForActive();
  return GyHasTarget(fixedDuelist);
}

void ActivateDESTINY_HERO_DYSTOPIAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  s8 gyIndex;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DYSTOPIA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER && GraveyardExpand_IsEnabled())
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindBestGyIndex(fixedDuelist);

  if (gyIndex < 0 && !GraveyardExpand_IsEnabled()) {
    if (!GyHasTarget(fixedDuelist))
      return;
    gyIndex = 0;
  }

  if (gyIndex < 0)
    return;

  BurnForGyIndex(fixedDuelist, gyIndex);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DYSTOPIA);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
