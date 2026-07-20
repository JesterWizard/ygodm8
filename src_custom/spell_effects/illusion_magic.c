#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

#define ILLUSION_MAGIC_ADD_COUNT 2

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsSpellcasterMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_SPELLCASTER);
}

static u8 IsValidSpellcasterTribute(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellcasterMonster(zone->id);
}

static u8 HasSpellcasterTribute(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidSpellcasterTribute(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasDarkMagician(void)
{
  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, DARK_MAGICIAN) >= 0;
}

static u8 GraveHasDarkMagician(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 count;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DARK_MAGICIAN;

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_MAGICIAN)
      return TRUE;
  }

  return FALSE;
}

static u8 HandHasEmptySlot(void)
{
  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0;
}

u8 CanActivateILLUSION_MAGIC(void)
{
  return HasSpellcasterTribute();
}

static void DestroyIllusionMagicSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == ILLUSION_MAGIC)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = Deck, FALSE = GY. */
static u8 PlayerChoosesDeck(void)
{
  /* ponytail: no dedicated Deck/GY choice UI — A = Deck, B = GY.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u8 AddDarkMagicianFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 handZone;
  u16 cardId;
  u8 i;
  u8 count;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard != DARK_MAGICIAN)
      return FALSE;

    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
    InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
                         cardId);
    return TRUE;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != DARK_MAGICIAN)
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    if (cardId != DARK_MAGICIAN)
      return FALSE;

    InitHandSlotFromCard(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone),
                         cardId);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    return TRUE;
  }

  return FALSE;
}

static u8 TryAddOneDarkMagician(void)
{
  u8 hasDeck = DeckHasDarkMagician();
  u8 hasGy = GraveHasDarkMagician();
  u8 chooseDeck;

  if (!HandHasEmptySlot())
    return FALSE;

  if (!hasDeck && !hasGy)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasDeck && hasGy)
    chooseDeck = PlayerChoosesDeck();
  else if (hasDeck)
    chooseDeck = TRUE;
  else
    chooseDeck = FALSE;

  if (chooseDeck)
    return Duel_AddDeckCardToHand(ACTIVE_DUELIST, DARK_MAGICIAN, FALSE) == DUEL_ACTION_OK;

  return AddDarkMagicianFromGy();
}

static void AddUpToTwoDarkMagicians(void)
{
  u8 i;

  for (i = 0; i < ILLUSION_MAGIC_ADD_COUNT; i++) {
    if (!TryAddOneDarkMagician())
      break;
  }
}

static void FinishIllusionMagic(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidSpellcasterTribute(fixedRow, fixedCol)) {
    DestroyIllusionMagicSpellZone();
    return;
  }

  PlayMusic(SFX_TRIBUTE);
  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (IsDuelOver() == TRUE)
    return;

  AddUpToTwoDarkMagicians();
  DestroyIllusionMagicSpellZone();
}

static void CancelIllusionMagicTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyIllusionMagicSpellZone();
}

static u8 AiPickSpellcasterTribute(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0xFFFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidSpellcasterTribute(row, col))
      continue;

    zone = gFixedZones[row][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = row;
      *outCol = col;
    }
  }

  return found;
}

static void ResolveSpellcasterTribute(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidSpellcasterTribute(fixedRow, fixedCol))
    return;

  FinishIllusionMagic(fixedRow, fixedCol);
}

static void ILLUSION_MAGIC_ResolveBody(void)
{
  Duel_ShowEffectText(ILLUSION_MAGIC);

  if (IsDuelOver() == TRUE || !CanActivateILLUSION_MAGIC())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidSpellcasterTribute, ResolveSpellcasterTribute,
                     CancelIllusionMagicTargeting, AiPickSpellcasterTribute);

  if (WhoseTurn() != DUEL_PLAYER)
    Duel_ResolvePickZoneForAi();
  else
    Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectILLUSION_MAGIC(void)
{
  /* ponytail: once-per-turn activation not tracked (no BSS turn flag editable
   * from this file alone). Ceiling: multiple Illusion Magic per turn possible;
   * upgrade: shared OPT RAM bit / effect_usage once_per_turn. */
  if (!CanActivateILLUSION_MAGIC()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ILLUSION_MAGIC, ILLUSION_MAGIC_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
