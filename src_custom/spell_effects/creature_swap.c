#include "global.h"
#include "common-chax.h"
#include "ameba.h"
#include "constants/card_ids.h"
#include "creature_swap.h"
#include "duel_helpers.h"
#include "card_passives.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void SetCursorToCardDest(void);
void ActivateSpellEffect(void);
void CopyCard(struct DuelCard *dst, struct DuelCard *src);
void CheckWinConditionExodia(void);

static u8 IsSwappableMonsterAt(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id) || IsImmuneToControlSwitch(zone->id))
    return FALSE;

  return TRUE;
}

static u8 IsSwappableMonsterZone(u8 fixedRow, u8 fixedCol, u8 requiredRow)
{
  if (fixedRow != requiredRow)
    return FALSE;

  return IsSwappableMonsterAt(fixedRow, fixedCol);
}

static u8 FindFirstSwappableMonster(u8 fixedRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsSwappableMonsterZone(fixedRow, col, fixedRow))
      continue;

    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static int LowestAtkMonInRowExceptGodCards(struct DuelCard **zonePtr)
{
  u8 zoneIndex = 0;
  u8 found = FALSE;
  u8 i;
  int lowestAtk = 0x7FFFFFFF;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if ((*zonePtr)->id == CARD_NONE) {
      zonePtr++;
      continue;
    }
    if (IsGodCard((*zonePtr)->id) || IsImmuneToControlSwitch((*zonePtr)->id)) {
      zonePtr++;
      continue;
    }
    gStatMod.card = (*zonePtr)->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(*zonePtr);
    SetFinalStat(&gStatMod);
    if (!found || (int)gCardInfo.atk < lowestAtk) {
      lowestAtk = gCardInfo.atk;
      zoneIndex = i;
      found = TRUE;
    }
    zonePtr++;
  }

  return found ? (signed char)zoneIndex : -1;
}

static void SwapMonsterZones(struct DuelCard *zoneA, struct DuelCard *zoneB)
{
  struct DuelCard temp;

  CopyCard(&temp, zoneA);
  CopyCard(zoneA, zoneB);
  CopyCard(zoneB, &temp);
  zoneA->willChangeSides = FALSE;
  zoneB->willChangeSides = FALSE;
}

static u8 TargetsAreReady(void)
{
  return IsSwappableMonsterAt(gCreatureSwapPlayerRow, gCreatureSwapPlayerCol)
      && IsSwappableMonsterAt(gCreatureSwapOppRow, gCreatureSwapOppCol)
      && (gCreatureSwapPlayerRow != gCreatureSwapOppRow
          || gCreatureSwapPlayerCol != gCreatureSwapOppCol);
}

static u8 PickOpponentWeakestMonster(void)
{
  s8 col = LowestAtkMonInRowExceptGodCards(gFixedZones[OPPONENT_MONSTER_ROW]);

  if (col < 0)
    return FALSE;

  gCreatureSwapOppRow = OPPONENT_MONSTER_ROW;
  gCreatureSwapOppCol = (u8)col;
  return TRUE;
}

static void CreatureSwap_ResolveBody(void)
{
  struct DuelCard *playerZone;
  struct DuelCard *oppZone;
  struct DuelCard *spellZone;

  if (!TargetsAreReady())
    return;

  if (IsDuelOver() == TRUE)
    return;

  playerZone = gFixedZones[gCreatureSwapPlayerRow][gCreatureSwapPlayerCol];
  oppZone = gFixedZones[gCreatureSwapOppRow][gCreatureSwapOppCol];
  spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  {
    u16 playerCardId = playerZone->id;
    u16 oppCardId = oppZone->id;
    u8 playerRow = gCreatureSwapPlayerRow;
    u8 oppRow = gCreatureSwapOppRow;

    SwapMonsterZones(playerZone, oppZone);
    Duel_NotifyMonsterControlSwitched(playerCardId, oppRow);
    if (IsDuelOver() != TRUE)
      Duel_NotifyMonsterControlSwitched(oppCardId, playerRow);
  }
  Duel_NotifyFixedMonsterRowChanged(PLAYER_MONSTER_ROW);
  Duel_NotifyFixedMonsterRowChanged(OPPONENT_MONSTER_ROW);
  Duel_RefreshMonsterStatOverlays();
  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static void CreatureSwap_BeginPlayerPickAfterOpponentChoice(void)
{
  if (!PickOpponentWeakestMonster())
    return;

  BeginCreatureSwapTargeting(gSpellEffectData.row2, gSpellEffectData.col2);
}

static void FinishCreatureSwapActivation(void)
{
  gSpellEffectData.id = CREATURE_SWAP;
  ActivateSpellEffect();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia();
  if (IsDuelOver() != 1)
    TryActivatingPermanentEffects();
}

u8 IsCreatureSwapCard(u16 cardId)
{
  return cardId == CREATURE_SWAP;
}

u8 FieldHasCreatureSwapTarget(u8 originFixedRow, u8 originFixedCol)
{
  u8 playerCol;
  u8 oppCol;

  (void)originFixedRow;
  (void)originFixedCol;

  return FindFirstSwappableMonster(PLAYER_MONSTER_ROW, &playerCol)
      && FindFirstSwappableMonster(OPPONENT_MONSTER_ROW, &oppCol);
}

void BeginCreatureSwapTargeting(u8 originFixedRow, u8 originFixedCol)
{
  u8 playerCol;

  if (!FindFirstSwappableMonster(PLAYER_MONSTER_ROW, &playerCol))
    return;

  Duel_ShowEffectText(CREATURE_SWAP);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.destY = originFixedRow;
  gDuelCursor.destX = originFixedCol;
  gDuelCursor.state = DUEL_CURSOR_CREATURE_SWAP_OWN;
  gDuelCursor.currentY = PLAYER_MONSTER_ROW;
  gDuelCursor.currentX = playerCol;
}

void TrySelectCreatureSwapOwnTarget(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;

  if (!IsSwappableMonsterZone(targetRow, targetCol, PLAYER_MONSTER_ROW)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gCreatureSwapPlayerRow = targetRow;
  gCreatureSwapPlayerCol = targetCol;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (!PickOpponentWeakestMonster()) {
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
      return;
    }
  } else if (!IsSwappableMonsterAt(gCreatureSwapOppRow, gCreatureSwapOppCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gSpellEffectData.row2 = gDuelCursor.destY;
  gSpellEffectData.col2 = gDuelCursor.destX;
  FinishCreatureSwapActivation();
}

void CancelCreatureSwapTargeting(void)
{
  u8 currY = gDuelCursor.currentY;

  PlayMusic(SFX_CANCEL);
  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

APPEND_TEXT void EffectCreatureSwap(void)
{
  if (WhoseTurn() != DUEL_PLAYER && !TargetsAreReady()) {
    gSpellEffectData.row2 = gSpellEffectData.row1;
    gSpellEffectData.col2 = gSpellEffectData.col1;

    if (Duel_TryResolveSpellThroughTraps(CREATURE_SWAP, CreatureSwap_BeginPlayerPickAfterOpponentChoice)
        == DUEL_ACTION_BLOCKED)
      return;
    return;
  }

  if (!TargetsAreReady()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER) {
    if (Duel_TryResolveSpellThroughTraps(CREATURE_SWAP, CreatureSwap_ResolveBody) == DUEL_ACTION_BLOCKED)
      return;
  } else {
    CreatureSwap_ResolveBody();
  }
}
