#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "yubel.h"

static u8 HandHasCard(struct DuelCard **handRow, u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == cardId)
      return TRUE;
  }

  return FALSE;
}

static s8 PickHandZone(struct DuelCard **handRow, u16 cardId)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == cardId)
      return i;
  }

  return -1;
}

static u8 GraveyardHasCard(u8 fixedDuelist, u16 cardId)
{
  u8 count;
  u8 i;

  if (GraveyardExpand_IsEnabled()) {
    count = GraveyardExpand_GetCount(fixedDuelist);
    for (i = 0; i < count; i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == cardId)
        return TRUE;
    }
    return FALSE;
  }

  return gDuel.duelistbattleState[fixedDuelist].graveyard == cardId;
}

static void RemoveCardFromGraveyard(u8 turnDuelist, u8 fixedDuelist, u16 cardId)
{
  u8 count;
  s8 i;

  if (GraveyardExpand_IsEnabled()) {
    count = GraveyardExpand_GetCount(fixedDuelist);
    for (i = (s8)count - 1; i >= 0; i--) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)i) != cardId)
        continue;

      GraveyardExpand_RemoveAtTurn(turnDuelist, (u8)i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      return;
    }
  }

  if (gTurnDuelistBattleState[turnDuelist]->graveyard == cardId)
    GetGraveCardAndClearGrave(turnDuelist);
}

static u8 CanSpecialSummonEvolution(u8 turnDuelist, u16 cardId)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  u8 fixedDuelist = turnDuelist == ACTIVE_DUELIST ? DUEL_PLAYER : DUEL_OPPONENT;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  if (HandHasCard(gTurnHands[turnDuelist], cardId))
    return TRUE;

  if (Duel_FindDeckCardIndex(turnDuelist, cardId) >= 0)
    return TRUE;

  return GraveyardHasCard(fixedDuelist, cardId);
}

static void TrySpecialSummonEvolution(u8 turnDuelist, u16 cardId)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = turnDuelist == ACTIVE_DUELIST ? DUEL_PLAYER : DUEL_OPPONENT;
  s8 handZone;

  if (!CanSpecialSummonEvolution(turnDuelist, cardId))
    return;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (HandHasCard(handRow, cardId)) {
    handZone = PickHandZone(handRow, cardId);

    if (handZone >= 0) {
      gYubelOwnEffectSummon = TRUE;
      Duel_SpecialSummonFromHandZone(turnDuelist, handZone, opts);
      gYubelOwnEffectSummon = FALSE;
      return;
    }
  }

  if (Duel_FindDeckCardIndex(turnDuelist, cardId) >= 0) {
    gYubelOwnEffectSummon = TRUE;
    Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
    gYubelOwnEffectSummon = FALSE;
    return;
  }

  RemoveCardFromGraveyard(turnDuelist, fixedDuelist, cardId);
  gYubelOwnEffectSummon = TRUE;
  Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  gYubelOwnEffectSummon = FALSE;
}

void Yubel_NoteGraveyardMonsterSend(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != YUBEL)
    return;

  if (gYubelSelfDestructActive)
    gYubelSuppressGyEvolution = TRUE;
}

void Yubel_NoteMonsterLeftField(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id != YUBEL_TERROR_INCARNATE)
    return;

  if (Duel_ZoneIsHandSlot(zone))
    return;

  if (!zone->isFaceUp)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  gYubelTerrorLeftFieldPending = TRUE;
}

static u8 GraveyardTopMatches(u8 turnDuelist, u16 cardId)
{
  if (gActiveEffect.turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == cardId;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == cardId;
}

unsigned char ShouldActivateYubelEvolution(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != YUBEL)
    return FALSE;

  if (!GraveyardTopMatches(
          gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST, YUBEL))
    return FALSE;

  if (gYubelSelfDestructActive || gYubelSuppressGyEvolution) {
    gYubelSelfDestructActive = FALSE;
    gYubelSuppressGyEvolution = FALSE;
    gGraveyardSendWasFromField = FALSE;
    return FALSE;
  }

  if (!gGraveyardSendWasFromField)
    return FALSE;

  turnDuelist = gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  return CanSpecialSummonEvolution(turnDuelist, YUBEL_TERROR_INCARNATE);
}

void ActivateYubelEvolution(void)
{
  u8 turnDuelist = gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  u8 hideEffectText;

  if (gYubelSelfDestructActive || gYubelSuppressGyEvolution) {
    gYubelSelfDestructActive = FALSE;
    gYubelSuppressGyEvolution = FALSE;
    gGraveyardSendWasFromField = FALSE;
    return;
  }

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(YUBEL, CARD_EFFECT_TEXT_YUBEL_POPUP_2);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  GetGraveCardAndClearGrave(turnDuelist);
  TrySpecialSummonEvolution(turnDuelist, YUBEL_TERROR_INCARNATE);
}

unsigned char ShouldActivateYubelTerrorEvolution(void)
{
  u8 turnDuelist;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gYubelTerrorLeftFieldPending)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gActiveEffect.cardId != YUBEL_TERROR_INCARNATE)
    return FALSE;

  if (!GraveyardTopMatches(
          gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST,
          YUBEL_TERROR_INCARNATE))
    return FALSE;

  turnDuelist = gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  return CanSpecialSummonEvolution(turnDuelist, YUBEL_THE_ULTIMATE_NIGHTMARE);
}

void ActivateYubelTerrorEvolution(void)
{
  u8 turnDuelist = gActiveEffect.turnRow == 7 ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  gYubelTerrorLeftFieldPending = FALSE;
  Duel_ShowEffectText(YUBEL_TERROR_INCARNATE);
  GetGraveCardAndClearGrave(turnDuelist);
  TrySpecialSummonEvolution(turnDuelist, YUBEL_THE_ULTIMATE_NIGHTMARE);
}
