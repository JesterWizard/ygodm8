#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static const u8 sMezukiPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsZombieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_ZOMBIE);
}

static s16 FindMezukiInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == MEZUKI)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == MEZUKI)
      return (s16)i;
  }

  return -1;
}

static u8 GyHasOtherZombie(u8 mezukiIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    /* After banishing Mezuki top, another Zombie must already be below — not
     * visible in single-slot GY. Require expand for full effect. */
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (i == mezukiIndex)
      continue;
    if (IsZombieMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))
        && !Duel_CardCannotBeSpecialSummoned(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 LoadZombieGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsZombieMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
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

static s8 PlayerPickZombieGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadZombieGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sMezukiPickLabels,
                                         ARRAY_COUNT(sMezukiPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static s8 FindBestZombieGyIndexForAi(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 bestIndex = 0xFF;
  u16 bestAtk = 0;
  u8 i;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u16 atk;

    if (!IsZombieMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestIndex == 0xFF || atk > bestAtk) {
      bestAtk = atk;
      bestIndex = i;
    }
  }

  return (s8)bestIndex;
}

unsigned char CanActivateMEZUKI(void)
{
  s16 mezukiIndex;

  if (gMonEffect.id != MEZUKI)
    return FALSE;

  /* GY ignition needs GY-menu wire. Ceiling: allow when Mezuki +
   * another Zombie in expanded GY (callable if gMonEffect set to Mezuki). */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  mezukiIndex = FindMezukiInGy();
  if (mezukiIndex < 0)
    return FALSE;

  return GyHasOtherZombie((u8)mezukiIndex);
}

void ActivateMEZUKIEffect(void)
{
  s16 mezukiIndex;
  s8 zombieIndex;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 zombieId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(MEZUKI, 2);

  if (IsDuelOver() == TRUE)
    return;

  mezukiIndex = FindMezukiInGy();
  if (mezukiIndex < 0)
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)mezukiIndex);

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    zombieIndex = PlayerPickZombieGyIndex(fixedDuelist);
  else
    zombieIndex = FindBestZombieGyIndexForAi(fixedDuelist);

  if (zombieIndex < 0)
    return;

  zombieId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)zombieIndex);
  if (!IsZombieMonster(zombieId))
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, zombieId, opts);
  UpdateDuelGfxExceptField();
}
