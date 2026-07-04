#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "graveyard_effects.h"
#include "the_big_saturn.h"

void ClearTheBigSaturnPending(void)
{
  gTheBigSaturnGyDamagePending = 0;
  gTheBigSaturnGyDamageTurnRow = 0xFF;
  gTheBigSaturnGyDamageFromField = FALSE;
}

static u8 FixedDuelistForTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW || turnRow == ACTIVE_DUELIST_BACKROW
      || turnRow == ACTIVE_DUELIST_HAND)
    return WhoseTurn();

  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW || turnRow == INACTIVE_DUELIST_BACKROW)
    return WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return 0xFF;
}

static u8 FixedDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;

  if (fixedRow == PLAYER_BACKROW || fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_HAND)
    return DUEL_PLAYER;

  return 0xFF;
}

static u8 GraveyardScanRowForTurnDuelist(u8 turnDuelist)
{
  return (turnDuelist == ACTIVE_DUELIST) ? 6 : 7;
}

static u8 EffectOwnerFromCardOnField(u16 cardId)
{
  u8 row;
  u8 col;

  if (cardId == CARD_NONE)
    return 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[PLAYER_BACKROW][col]->id == cardId)
      return DUEL_PLAYER;
    if (gFixedZones[OPPONENT_BACKROW][col]->id == cardId)
      return DUEL_OPPONENT;
    if (gFixedZones[PLAYER_MONSTER_ROW][col]->id == cardId)
      return DUEL_PLAYER;
    if (gFixedZones[OPPONENT_MONSTER_ROW][col]->id == cardId)
      return DUEL_OPPONENT;
  }

  for (row = 0; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gTurnZones[row][col]->id != cardId)
        continue;

      return FixedDuelistForTurnRow(row);
    }
  }

  return 0xFF;
}

static u8 GetResolvingCardEffectOwnerFixed(void)
{
  u8 owner;
  u8 originRow;

  if (gTrapEffectData.trapCardId != CARD_NONE) {
    owner = EffectOwnerFromCardOnField(gTrapEffectData.trapCardId);
    if (owner != 0xFF)
      return owner;
  }

  owner = EffectOwnerFromCardOnField(gTrapEffectData.originCardId);
  if (owner != 0xFF)
    return owner;

  if (Duel_IsMonsterEffectResolving())
    return FixedDuelistForTurnRow(gMonEffect.row);

  if (Duel_IsSpellEffectResolving()) {
    /* ponytail: custom targeted spells store fixed-row origins in row2. */
    originRow = gSpellEffectData.row2;
    if (originRow <= PLAYER_HAND
        && gFixedZones[originRow][gSpellEffectData.col2]->id == gSpellEffectData.id)
      return FixedDuelistForFixedRow(originRow);

    owner = FixedDuelistForTurnRow(gSpellEffectData.row1);
    if (owner != 0xFF)
      return owner;

    return FixedDuelistForFixedRow(gSpellEffectData.row1);
  }

  return 0xFF;
}

static u8 DestroyedByOpponentCardEffect(struct DuelCard *zone)
{
  u8 saturnOwner;
  u8 effectOwner;

  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  saturnOwner = GetDuelistForZone(zone);
  if (saturnOwner == 0xFF)
    return FALSE;

  effectOwner = GetResolvingCardEffectOwnerFixed();
  if (effectOwner == 0xFF && gActiveEffect.cardId != CARD_NONE
      && gActiveEffect.cardId != THE_BIG_SATURN)
    effectOwner = FixedDuelistForTurnRow(gActiveEffect.turnRow);

  if (effectOwner == 0xFF || effectOwner == saturnOwner)
    return FALSE;

  return TRUE;
}

void NoteTheBigSaturnGraveyardSend(struct DuelCard *zone)
{
  u8 turnDuelist;

  if (zone == NULL || zone->id != THE_BIG_SATURN)
    return;

  if (!DestroyedByOpponentCardEffect(zone))
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(GetDuelistForZone(zone));
  gTheBigSaturnGyDamageTurnRow = GraveyardScanRowForTurnDuelist(turnDuelist);
  gTheBigSaturnGyDamagePending = Duel_GetZoneFinalAtk(zone);
  gTheBigSaturnGyDamageFromField = gGraveyardSendWasFromField;
}

u8 TheBigSaturn_PendingGraveyardTurnRow(void)
{
  if (gTheBigSaturnGyDamagePending == 0)
    return 0xFF;

  return gTheBigSaturnGyDamageTurnRow;
}

void TheBigSaturn_PrepareGraveyardScan(u8 turnRow, u16 *cardId)
{
  if (cardId == NULL || gTheBigSaturnGyDamagePending == 0)
    return;

  if (gTheBigSaturnGyDamageTurnRow != turnRow)
    return;

  *cardId = THE_BIG_SATURN;
}

unsigned char ShouldActivateTheBigSaturn(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return FALSE;

  if (!gTheBigSaturnGyDamageFromField)
    return FALSE;

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (gTheBigSaturnGyDamagePending == 0)
    return FALSE;

  return gActiveEffect.turnRow == gTheBigSaturnGyDamageTurnRow;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;
  return DUEL_OPPONENT;
}

static void RemoveTheBigSaturnFromGraveyard(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 count;
  s8 i;

  if (GraveyardExpand_IsEnabled()) {
    count = GraveyardExpand_GetCount(fixedDuelist);
    for (i = (s8)count - 1; i >= 0; i--) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, (u8)i) != THE_BIG_SATURN)
        continue;

      GraveyardExpand_RemoveAtTurn(turnDuelist, (u8)i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      return;
    }
  }

  if (gTurnDuelistBattleState[turnDuelist]->graveyard == THE_BIG_SATURN)
    GetGraveCardAndClearGrave(turnDuelist);
}

void ActivateTheBigSaturn(void)
{
  u8 turnDuelist = (gActiveEffect.turnRow == 6) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  u16 damage = gTheBigSaturnGyDamagePending;
  u8 hideEffectText;

  if (gTheBigSaturnGyDamagePending == 0)
    return;

  gTheBigSaturnGyDamagePending = 0;
  gTheBigSaturnGyDamageTurnRow = 0xFF;
  gTheBigSaturnGyDamageFromField = FALSE;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(THE_BIG_SATURN, CARD_EFFECT_TEXT_THE_BIG_SATURN_POPUP_2);
  gHideEffectText = hideEffectText;

  if (damage == 0 || IsDuelOver() == TRUE)
    return;

  if (Duel_ChangeLp(DUEL_PLAYER, -(s32)damage, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(DUEL_OPPONENT, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  RemoveTheBigSaturnFromGraveyard(turnDuelist);
}

void TheBigSaturn_TryResolveGyDamage(void)
{
  if (gDeferGraveyardDrawBattleResolve)
    return;

  if (gTheBigSaturnGyDamagePending == 0)
    return;

  if (!gTheBigSaturnGyDamageFromField)
    return;

  /* ponytail: GY permanent scan misses some opponent-turn effect destroys (Core pattern). */
  gActiveEffect.turnRow = gTheBigSaturnGyDamageTurnRow;
  gActiveEffect.col = 0;
  gActiveEffect.cardId = THE_BIG_SATURN;
  ActivateTheBigSaturn();
}

#ifdef THE_BIG_SATURN_SELF_CHECK
void TheBigSaturn_SelfCheck(void)
{
  if (Duel_StageModifiedStat(2800, THE_BIG_SATURN_ATK_BOOST_STAGES) != 3800)
    while (1)
      ;
}
#endif
