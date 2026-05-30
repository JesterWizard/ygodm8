#include "global.h"
#include "configs/runtime.h"
#include "delayed_effects.h"
#include "copycat.h"

u8 TryPayChainEnergyCost(void);
u8 ShouldPayChainEnergyForHandToFieldCopy(const struct DuelCard *dst, const struct DuelCard *src);
void CopyCard(struct DuelCard *dst, struct DuelCard *src);
void ResetUltimateOfferingTurnState(void);
void TryUnlockHandForUltimateOfferingExtraSummon(void);

void InitBoard(void);
void PlayerTurnMain(void);
void UpdateDuelGfxExceptField(void);
void InitButtonMaps(void);
void DisplayCardInfoBar(void);
void sub_8041E70(unsigned char, unsigned char);
void MoveCursorUp(void);
void MoveCursorDown(void);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void HandleAButtonAction(void);
void sub_8042F04(void);
void sub_8041014(void);
void sub_8044B2C(void);
void UpdateAllDuelGfx(void);
void HandleBButtonAction(void);
void TryActivatingTurnEffects(void);
void TryActivatingPermanentEffects(void);
void UpdateFilteredInput_WithRepeat(void);
void DeclareLoser(unsigned char);
void DestroyKarateManAtEndOfTurn(void);
void DecrementSorlTurns(unsigned char);

static struct DuelCard *GetSorlZoneForBlockedDuelist(u8 blockedDuelist)
{
  u8 row;
  u8 i;

  row = (blockedDuelist == DUEL_PLAYER) ? OPPONENT_BACKROW : PLAYER_BACKROW;
  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[row][i]->id == SWORDS_OF_REVEALING_LIGHT)
      return gFixedZones[row][i];
  }

  return NULL;
}

static u8 GetSorlBlockedDuelistByZone(struct DuelCard *zone)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[PLAYER_BACKROW][i] == zone)
      return DUEL_OPPONENT;
    if (gFixedZones[OPPONENT_BACKROW][i] == zone)
      return DUEL_PLAYER;
  }

  return 2;
}

static u8 GetBlockedDuelistForSorlCounter(void)
{
  return (WhoseTurn() == DUEL_PLAYER) ? DUEL_OPPONENT : DUEL_PLAYER;
}

extern unsigned char gIsPlayerTurnOver;
extern u16 gRepeatedOrNewButtons;
extern u16 gNewButtons;

static unsigned char ProcessInput__Replacement(void) {
  UpdateFilteredInput_WithRepeat();
  if (gRepeatedOrNewButtons & DPAD_UP)
    return 1;
  if (gRepeatedOrNewButtons & DPAD_DOWN)
    return 2;
  if (gRepeatedOrNewButtons & DPAD_LEFT)
    return 3;
  if (gRepeatedOrNewButtons & DPAD_RIGHT)
    return 4;
  if (gNewButtons & A_BUTTON)
    return 5;
  if (gNewButtons & L_BUTTON)
    return 6;
  if (gNewButtons & R_BUTTON)
    return 7;
  if (gNewButtons & B_BUTTON)
    return 8;
  if (gRepeatedOrNewButtons & START_BUTTON)
    return 0;
  if (gRepeatedOrNewButtons & SELECT_BUTTON)
    return 0;
  return 0;
}

LYN_REPLACE_CHECK(sub_803FBCC);
unsigned char sub_803FBCC__Replacement(unsigned char a, unsigned char b) {
  if (gRuntimeConfig.disable_element_system == TRUE)
    return 1;
  if (a == ATTRIBUTE_DIVINE)
    return 1;
  if (b == ATTRIBUTE_DIVINE)
    return 1;
  if (a == ATTRIBUTE_SHADOW && b == ATTRIBUTE_LIGHT)
    return 0;
  if (a == ATTRIBUTE_LIGHT && b == ATTRIBUTE_SHADOW)
    return 2;
  return 1;
}

LYN_REPLACE_CHECK(InitBoard);
void InitBoard__Replacement(void) {
  unsigned char i, j;

  ResetDelayedDuelEffects();
  ResetUltimateOfferingTurnState();
  InitDuelZonePtrs(2);
  for (i = 0; i < 4; i++)
    for (j = 0; j < 5; j++)
      ClearZone(&gDuel.board[i][j]);
  for (i = 0; i < 2; i++)
    for (j = 0; j < 5; j++) {
      ClearZone(&gDuel.hands[i][j]);
      TryDrawingCard(i);
    }
  gDuel.field = gRuntimeConfig.duel_fields_start_on_arena == TRUE
      ? FIELD_ARENA
      : gDuelData.duelist.field;
  for (i = 0; i < 2; i++) {
    gDuel.duelistbattleState[i].sorlTurns = 0;
    gDuel.duelistbattleState[i].defenseBlocked = 0;
    gDuel.duelistbattleState[i].graveyard = CARD_NONE;
    UnblockSummoning(i);
  }
}

LYN_REPLACE_CHECK(PlayerTurnMain);
void PlayerTurnMain__Replacement(void) {
  gIsPlayerTurnOver = 0;
  UpdateDuelGfxExceptField();
  TryActivatingTurnEffects();
  if (IsDuelOver() == TRUE)
    return;
  TryActivatingPermanentEffects();
  if (IsDuelOver() == TRUE)
    return;
  InitButtonMaps();
  while (IsDuelOver() != TRUE && gIsPlayerTurnOver != TRUE) {
    unsigned char y = gDuelCursor.currentY;
    switch (ProcessInput__Replacement()) {
      case 1:
        MoveCursorUp();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 2:
        MoveCursorDown();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 3:
        MoveCursorLeft();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 4:
        MoveCursorRight();
        DisplayCardInfoBar();
        sub_8041E70(y, gDuelCursor.currentY);
        break;
      case 5:
        HandleAButtonAction();
        break;
      case 6:
        if (gRuntimeConfig.instant_win_with_l_button == TRUE)
          DeclareLoser(1);
        else {
          sub_8042F04();
          WaitForVBlank();
          sub_8041014();
        }
        break;
      case 7:
        sub_8044B2C();
        UpdateAllDuelGfx();
        break;
      case 8:
        HandleBButtonAction();
        WaitForVBlank();
        break;
      case 9:
        DeclareLoser(0);
        break;
      case 10:
        DeclareLoser(1);
        break;
      default:
        WaitForVBlank();
        break;
    }
  }

  DestroyKarateManAtEndOfTurn();
  ResolveDelayedDuelEffectsAtTurnEnd(DUEL_PLAYER);
  UpdateDuelGfxExceptField();
}

LYN_REPLACE_CHECK(LockMonsterCardsInRow);
void LockMonsterCardsInRow__Replacement(unsigned char turnRow) {
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[turnRow][i]->id != CARD_NONE
        && GetTypeGroup(gTurnZones[turnRow][i]->id) == TYPE_GROUP_MONSTER)
      gTurnZones[turnRow][i]->isLocked = TRUE;
  }

  if (turnRow == ACTIVE_DUELIST_HAND)
    TryUnlockHandForUltimateOfferingExtraSummon();
}

LYN_REPLACE_CHECK(DecrementSorlTurns);
void DecrementSorlTurns__Replacement(unsigned char currPlayer) {
  struct DuelCard *sorlZone;
  u8 blockedDuelist;

  blockedDuelist = GetBlockedDuelistForSorlCounter();
  sorlZone = GetSorlZoneForBlockedDuelist(blockedDuelist);

  if (sorlZone == NULL) {
    gTurnDuelistBattleState[currPlayer]->sorlTurns = 0;
    return;
  }

  if (gTurnDuelistBattleState[currPlayer]->sorlTurns)
    gTurnDuelistBattleState[currPlayer]->sorlTurns--;

  if (gTurnDuelistBattleState[currPlayer]->sorlTurns == 0)
    ClearZoneAndSendMonToGraveyard(sorlZone, blockedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER);
}

LYN_REPLACE_CHECK(ClearZone);
void ClearZone__Replacement(struct DuelCard *zone) {
  if (zone->id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE) {
    u8 blockedDuelist = GetSorlBlockedDuelistByZone(zone);

    if (blockedDuelist < 2)
      gDuel.duelistbattleState[blockedDuelist].sorlTurns = 0;
  }

  zone->id = CARD_NONE;
  zone->isFaceUp = 0;
  zone->isLocked = 0;
  zone->isDefending = 0;
  zone->unkTwo = 0;
  zone->unkThree = 0;
  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unk4 = 0;
  zone->willChangeSides = 0;
  ClearCopycatBoardStatsForZone(zone);
}

LYN_REPLACE_CHECK(CopyCard);
void CopyCard__Replacement(struct DuelCard *dst, struct DuelCard *src)
{
  if (ShouldPayChainEnergyForHandToFieldCopy(dst, src)) {
    if (!TryPayChainEnergyCost())
      return;
  }

  dst->id = src->id;
  SetPermStage(dst, PermStage(src));
  ResetTempStage(dst);
  dst->unk4 = src->unk4;
  dst->isFaceUp = src->isFaceUp;
  dst->isLocked = src->isLocked;
  dst->isDefending = src->isDefending;
  dst->unkTwo = src->unkTwo;
  dst->unkThree = src->unkThree;
  dst->willChangeSides = src->willChangeSides;
}
