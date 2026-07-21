#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

#define REPTILIANNE_SPAWN_TOKEN_COUNT 2

#define REPTILIANNE_SPAWN_TOKEN_ID MOON_TOKEN

static const char sReptilianneArchetypeName[] APPEND_RODATA = "Reptilianne";

static const u8 sReptilianneSpawnPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsReptilianneMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sReptilianneArchetypeName);
}

static s8 FindFirstReptilianneGyIndex(u8 fixedDuelist)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < gyCount; i++) {
    if (IsReptilianneMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 CanSpecialSummonTokens(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW])
      >= REPTILIANNE_SPAWN_TOKEN_COUNT;
}

u8 CanActivateREPTILIANNE_SPAWN(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!CanSpecialSummonTokens())
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return IsReptilianneMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard);

  return FindFirstReptilianneGyIndex(fixedDuelist) >= 0;
}

static u8 LoadReptilianneGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsReptilianneMonster(cardId))
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

  menuCount = LoadReptilianneGyMenu(fixedDuelist, gyIndexMap);
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
  if (!DeckMenuMainPickConfirmWithLabels(sReptilianneSpawnPickLabels,
                                         ARRAY_COUNT(sReptilianneSpawnPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static u8 BanishReptilianneFromGy(u8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsReptilianneMonster(gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsReptilianneMonster(cardId))
    return FALSE;

  Duel_BanishGraveyardAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_RefreshDisplay();
  return TRUE;
}

static void SpecialSummonReptilianneTokens(void)
{
  u8 i;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  opts.lockMonster = TRUE;
  opts.markSpecialSummon = FALSE;

  for (i = 0; i < REPTILIANNE_SPAWN_TOKEN_COUNT; i++) {
    if (i + 1 == REPTILIANNE_SPAWN_TOKEN_COUNT)
      opts.updateGfx = TRUE;

    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, REPTILIANNE_SPAWN_TOKEN_ID, opts)
        != DUEL_ACTION_OK)
      break;
  }
}

static void REPTILIANNE_SPAWN_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 gyIndex;

  Duel_ShowEffectText(REPTILIANNE_SPAWN);

  if (IsDuelOver() == TRUE || !CanActivateREPTILIANNE_SPAWN())
    return;

  if (!GraveyardExpand_IsEnabled()) {
    if (!BanishReptilianneFromGy(0))
      return;

    SpecialSummonReptilianneTokens();
    if (IsDuelOver() == TRUE)
      return;

    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    gyIndex = PlayerPickGyIndex(fixedDuelist);
  else
    gyIndex = FindFirstReptilianneGyIndex(fixedDuelist);

  if (gyIndex < 0)
    return;

  if (!BanishReptilianneFromGy((u8)gyIndex))
    return;

  if (!CanSpecialSummonTokens()) {
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
    return;
  }

  SpecialSummonReptilianneTokens();
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectREPTILIANNE_SPAWN(void)
{
  if (!CanActivateREPTILIANNE_SPAWN()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(REPTILIANNE_SPAWN, REPTILIANNE_SPAWN_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ReptilianneSpawn_SelfCheck(void)
{
  if (!IsReptilianneMonster(REPTILIANNE_VASKII))
    while (1)
      ;
  if (IsReptilianneMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
