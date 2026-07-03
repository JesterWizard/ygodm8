#include "global.h"
#include "common-chax.h"
#include "chaos_emperor_dragon_envoy_of_the_end.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);
void UpdateDuelGfxExceptField(void);
void sub_8022080(void);

extern const u8 gActivationDescription_ChaosEmperorDragonEnvoyOfTheEnd_Popup1[];

#define CED_BANISH_INDEX_NONE 0xFF

static u8 FixedDuelistYouControl(void)
{
  return WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static u8 IsOnActiveDuelistMonsterRow(void)
{
  if (WhoseTurn() == DUEL_PLAYER)
    return gMonEffect.row == PLAYER_MONSTER_ROW;

  return gMonEffect.row == OPPONENT_MONSTER_ROW;
}

static u8 GraveyardMonsterHasAttribute(u16 cardId, u16 attribute)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == attribute;
}

static u8 FindGraveyardMonsterByAttribute(u8 fixedDuelist, u16 attribute, u8 skipIndex,
                                          u8 *outIndex)
{
  u8 i;
  u8 count;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!GraveyardMonsterHasAttribute(cardId, attribute))
      return FALSE;

    *outIndex = 0;
    return TRUE;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    u16 cardId;

    if (skipIndex != CED_BANISH_INDEX_NONE && i == skipIndex)
      continue;

    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!GraveyardMonsterHasAttribute(cardId, attribute))
      continue;

    *outIndex = i;
    return TRUE;
  }

  return FALSE;
}

static u8 GraveyardHasLightAndDarkMonsters(u8 fixedDuelist)
{
  u8 lightIndex;
  u8 darkIndex;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_LIGHT, CED_BANISH_INDEX_NONE,
                                      &lightIndex))
    return FALSE;

  return FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_SHADOW, lightIndex, &darkIndex);
}

static void BanishGraveyardCardAt(u8 fixedDuelist, u8 index)
{
  if (GraveyardExpand_IsEnabled()) {
    GraveyardExpand_RemoveAtFixed(fixedDuelist, index);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
    return;
  }

  gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
}

static u8 BanishLightAndDarkFromGraveyard(u8 fixedDuelist)
{
  u8 lightIndex;
  u8 darkIndex;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_LIGHT, CED_BANISH_INDEX_NONE,
                                      &lightIndex))
    return FALSE;

  if (!FindGraveyardMonsterByAttribute(fixedDuelist, ATTRIBUTE_SHADOW, lightIndex, &darkIndex))
    return FALSE;

  if (lightIndex > darkIndex) {
    BanishGraveyardCardAt(fixedDuelist, lightIndex);
    BanishGraveyardCardAt(fixedDuelist, darkIndex);
  } else {
    BanishGraveyardCardAt(fixedDuelist, darkIndex);
    BanishGraveyardCardAt(fixedDuelist, lightIndex);
  }

  return TRUE;
}

u8 CanSpecialSummonChaosEmperorDragonEnvoyOfTheEndFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistYouControl();

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return GraveyardHasLightAndDarkMonsters(fixedDuelist);
}

static void EnsureChaosEmperorDragonSummonedFaceUp(void)
{
  u8 col;
  struct DuelCard *zone;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id != CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END)
      continue;

    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    Duel_NotifyMonsterZoneChanged(zone);
    return;
  }
}

u8 TrySpecialSummonChaosEmperorDragonEnvoyOfTheEndFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistYouControl();

  if (!CanSpecialSummonChaosEmperorDragonEnvoyOfTheEndFromHand(handZone))
    return FALSE;

  if (!BanishLightAndDarkFromGraveyard(fixedDuelist))
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  EnsureChaosEmperorDragonSummonedFaceUp();
  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}

static u8 CanPayChaosEmperorDragonCost(void)
{
  u8 turn = WhoseTurn();

  return gDuelLifePoints[turn] >= 1000;
}

static void SendHandToGraveyardAndCount(u8 duelist, u16 *gyCount)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == CARD_NONE)
      continue;

    (*gyCount)++;

    if (Duel_DestroyZone(handRow[i], duelist, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

static u8 TurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void SendFieldToGraveyardAndCount(struct DuelCard *protectedZone, u16 *gyCount)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    u8 graveyardDuelist = TurnDuelistForFixedRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      (*gyCount)++;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }
}

static void ResolveChaosEmperorDragonBoardWipe(void)
{
  u16 gyCount = 0;
  u16 damage;
  struct DuelCard *cedZone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  SendHandToGraveyardAndCount(ACTIVE_DUELIST, &gyCount);
  if (IsDuelOver() == TRUE)
    return;

  SendHandToGraveyardAndCount(INACTIVE_DUELIST, &gyCount);
  if (IsDuelOver() == TRUE)
    return;

  SendFieldToGraveyardAndCount(cedZone, &gyCount);
  if (IsDuelOver() == TRUE)
    return;

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();

  damage = gyCount * 300;
  if (damage > 0) {
    if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)damage, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  CheckWinConditionExodia(WhoseTurn());
  TryActivatingPermanentEffects();
}

unsigned char CanActivateChaosEmperorDragonEnvoyOfTheEnd(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END)
    return FALSE;

  if (!IsOnActiveDuelistMonsterRow())
    return FALSE;

  if (!CanPayChaosEmperorDragonCost())
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  return CanUseMonsterEffect(zone);
}

static void ShowChaosEmperorDragonActivationText(void)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  gCardEffectTextData.cardId = CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((u8 *)gActivationDescription_ChaosEmperorDragonEnvoyOfTheEnd_Popup1,
              CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END, CARD_NONE, 0, 0);
  SetCardInfo(CHAOS_EMPEROR_DRAGON_ENVOY_OF_THE_END);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  sub_8022080();
}

void ActivateChaosEmperorDragonEnvoyOfTheEndEffect(void)
{
  ShowChaosEmperorDragonActivationText();

  if (IsDuelOver() == TRUE)
    return;

  if (!CanPayChaosEmperorDragonCost())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -1000, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  ResolveChaosEmperorDragonBoardWipe();
}
