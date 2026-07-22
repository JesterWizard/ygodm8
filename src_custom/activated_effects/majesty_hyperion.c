#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "majesty_hyperion.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_LOSER_OPPONENT 16
#define FLAG_LOSER_PLAYER 4

struct MajestyHyperionActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct MajestyHyperionActionData sActionData;

static const char sTheAgentName[] APPEND_RODATA = "The Agent";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsTheAgentMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == MAJESTY_HYPERION)
    return FALSE;

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_FAIRY);
}

static struct DuelCard *FindFaceUpHyperion(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == MAJESTY_HYPERION)
      return zone;
  }

  return NULL;
}

static void MirrorDamageToOpponent(u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }

  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void MirrorDamageToPlayer(u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }

  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

void ApplyMajestyHyperionBattleDamageShare(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (playerDamage > 0 && FindFaceUpHyperion(DUEL_PLAYER) != NULL
      && IsFairyMonster(sActionData.playerCardId))
    MirrorDamageToOpponent(playerDamage);

  if (opponentDamage > 0 && FindFaceUpHyperion(DUEL_OPPONENT) != NULL
      && IsFairyMonster(sActionData.opponentCardId))
    MirrorDamageToPlayer(opponentDamage);
}

static u8 HasTheAgentAccessible(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsTheAgentMonster(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return TRUE;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && IsTheAgentMonster(zone->id))
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return IsTheAgentMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsTheAgentMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 BanishOneTheAgent(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (IsTheAgentMonster(slot->id)) {
      if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone != NULL && IsTheAgentMonster(zone->id)) {
      if (Duel_BanishZone(zone, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (IsTheAgentMonster(gDuel.duelistbattleState[fixedDuelist].graveyard)) {
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
      return TRUE;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsTheAgentMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);

      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      RemovedFromPlay_PushFixed(fixedDuelist, cardId);
      return TRUE;
    }
  }

  return FALSE;
}

static u8 HasFairyHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsFairyMonster(SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id))
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 BanishOneFairyHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (IsFairyMonster(slot->id)) {
      if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
        return FALSE;
      return TRUE;
    }
  }

  if (!GraveyardExpand_IsEnabled()) {
    if (IsFairyMonster(gDuel.duelistbattleState[fixedDuelist].graveyard)) {
      Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
      return TRUE;
    }
    return FALSE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsFairyMonster(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
      u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);

      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      RemovedFromPlay_PushFixed(fixedDuelist, cardId);
      return TRUE;
    }
  }

  return FALSE;
}

static u8 IsDestroyableFieldCard(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return !IsGodCard(zone->id);
}

static u8 FieldHasDestroyableCard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableFieldCard(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 GraveyardDuelistForZone(u8 fixedRow)
{
  if (fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW)
    return INACTIVE_DUELIST;

  return ACTIVE_DUELIST;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsDestroyableFieldCard(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (!BanishOneFairyHandOrGy())
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForZone(fixedRow), TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDestroyableFieldCard(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateMAJESTY_HYPERION(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MAJESTY_HYPERION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MAJESTY_HYPERION)
    return FALSE;

  /* Fairy damage sharing, the removal procedure, and the hand summon are active. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HasFairyHandOrGy() && FieldHasDestroyableCard();
}

void ActivateMAJESTY_HYPERIONEffect(void)
{
  Duel_ShowEffectTextTyped(MAJESTY_HYPERION, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsDestroyableFieldCard, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

u8 CanSpecialSummonMajestyHyperionFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != MAJESTY_HYPERION)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HasTheAgentAccessible();
}

u8 TrySpecialSummonMajestyHyperionFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonMajestyHyperionFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(MAJESTY_HYPERION, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishOneTheAgent())
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonMajestyHyperionFromHand(u8 handZone);
u8 TrySpecialSummonMajestyHyperionFromHand(u8 handZone);
#endif
