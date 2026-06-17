#include "global.h"
#include "common-chax.h"
#include "call_of_the_haunted.h"
#include "graveyard_effects.h"
#include "constants/card_ids.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "duel.h"

extern struct ApophisLink gApophisLinks[MAX_APOPHIS_LINKS];
extern u8 gApophisClearingPartner;

static u8 TryGetBoardCoords(const struct DuelCard *zone, u8 *boardRow, u8 *boardCol)
{
  u8 row;
  u8 col;

  if (zone == NULL)
    return FALSE;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (&gDuel.board[row][col] == zone) {
        *boardRow = row;
        *boardCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static struct DuelCard *ZoneFromBoardCoords(u8 boardRow, u8 boardCol)
{
  if (boardRow >= 4 || boardCol >= MAX_ZONES_IN_ROW)
    return NULL;

  return &gDuel.board[boardRow][boardCol];
}

static u8 BoardRowIsBackrow(u8 boardRow)
{
  return boardRow == 0 || boardRow == 3;
}

static u8 BoardRowIsMonsterRow(u8 boardRow)
{
  return boardRow == 1 || boardRow == 2;
}

static u8 MonsterBoardRowForTrapBoardRow(u8 trapBoardRow)
{
  if (trapBoardRow == 3)
    return 2;

  if (trapBoardRow == 0)
    return 1;

  return APOPHIS_BOARD_COORD_INVALID;
}

static s8 FirstEmptyColInBoardRow(u8 boardRow)
{
  u8 col;

  if (boardRow >= 4)
    return -1;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gDuel.board[boardRow][col].id == CARD_NONE)
      return (s8)col;
  }

  return -1;
}

struct DuelCard *EmbodimentOfApophisMonsterZoneForTrap(struct DuelCard *trapZone)
{
  u8 trapBoardRow;
  u8 trapBoardCol;
  u8 monsterBoardRow;
  s8 monsterCol;

  if (!TryGetBoardCoords(trapZone, &trapBoardRow, &trapBoardCol))
    return NULL;

  monsterBoardRow = MonsterBoardRowForTrapBoardRow(trapBoardRow);
  if (monsterBoardRow == APOPHIS_BOARD_COORD_INVALID)
    return NULL;

  monsterCol = FirstEmptyColInBoardRow(monsterBoardRow);
  if (monsterCol < 0)
    return NULL;

  return ZoneFromBoardCoords(monsterBoardRow, (u8)monsterCol);
}

u8 EmbodimentOfApophisHasEmptyMonsterZoneForTrap(struct DuelCard *trapZone)
{
  return EmbodimentOfApophisMonsterZoneForTrap(trapZone) != NULL;
}

void TryActivateEmbodimentOfApophisOnAttack(void)
{
  u8 i;
  struct DuelCard *trapZone;

  if (GetTypeGroup(gTrapEffectData.originCardId) != TYPE_GROUP_MONSTER)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (trapZone->id != EMBODIMENT_OF_APOPHIS)
      continue;
    if (!EmbodimentOfApophisHasEmptyMonsterZoneForTrap(trapZone))
      continue;
    if (EmbodimentOfApophisTrapZoneIsAwakened(trapZone))
      continue;

    gTrapEffectData.trapZoneCol = i;
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectEmbodimentOfApophis();
    return;
  }
}

static u8 InactiveDuelistFieldIsOnlyEmbodimentOfApophis(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;
  u8 sawApophis = FALSE;

  for (row = INACTIVE_DUELIST_BACKROW; row <= INACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      zone = gTurnZones[row][col];
      if (zone->id == CARD_NONE)
        continue;
      if (zone->id != EMBODIMENT_OF_APOPHIS)
        return FALSE;
      sawApophis = TRUE;
    }
  }

  return sawApophis;
}

u8 EmbodimentOfApophisRedirectsDirectAttack(u8 *defenderFixedCol)
{
  u8 col;
  u8 monsterCount = 0;
  u8 apophisMonsterCol = 0xFF;
  struct DuelCard *zone;

  if (defenderFixedCol == NULL)
    return FALSE;

  if (!InactiveDuelistFieldIsOnlyEmbodimentOfApophis())
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    if (zone->id == CARD_NONE)
      continue;
    if (!EmbodimentOfApophisZoneIsMonsterForm(zone))
      return FALSE;
    monsterCount++;
    apophisMonsterCol = col;
  }

  if (monsterCount != 1)
    return FALSE;

  *defenderFixedCol = apophisMonsterCol;
  return TRUE;
}

void PerformDirectAttackOrRedirectToEmbodimentOfApophis(u8 attackerFixedCol)
{
  u8 defenderFixedCol;

  if (CallOfTheHauntedRedirectsDirectAttack(&defenderFixedCol)) {
    gFixedZones[PLAYER_MONSTER_ROW][defenderFixedCol]->isFaceUp = TRUE;

    if (WhoseTurn() == DUEL_PLAYER)
      SetAttackAction(attackerFixedCol, defenderFixedCol);
    else
      SetAttackAction(defenderFixedCol, attackerFixedCol);
  } else if (EmbodimentOfApophisRedirectsDirectAttack(&defenderFixedCol)) {
    if (WhoseTurn() == DUEL_PLAYER)
      gFixedZones[OPPONENT_MONSTER_ROW][defenderFixedCol]->isFaceUp = TRUE;
    else
      gFixedZones[PLAYER_MONSTER_ROW][defenderFixedCol]->isFaceUp = TRUE;

    if (WhoseTurn() == DUEL_PLAYER)
      SetAttackAction(attackerFixedCol, defenderFixedCol);
    else
      SetAttackAction(defenderFixedCol, attackerFixedCol);
  } else {
    SetAttackActionDirectAttack(attackerFixedCol);
  }
}

static void ClearApophisLink(struct ApophisLink *link)
{
  link->active = FALSE;
  link->trapBoardRow = APOPHIS_BOARD_COORD_INVALID;
  link->trapBoardCol = APOPHIS_BOARD_COORD_INVALID;
  link->monBoardRow = APOPHIS_BOARD_COORD_INVALID;
  link->monBoardCol = APOPHIS_BOARD_COORD_INVALID;
}

void ResetApophisLinks(void)
{
  u8 i;

  gApophisClearingPartner = FALSE;
  for (i = 0; i < MAX_APOPHIS_LINKS; i++)
    ClearApophisLink(&gApophisLinks[i]);
}

static struct ApophisLink *FindInactiveApophisLink(void)
{
  u8 i;

  for (i = 0; i < MAX_APOPHIS_LINKS; i++) {
    if (!gApophisLinks[i].active)
      return &gApophisLinks[i];
  }

  return NULL;
}

static u8 ApophisLinkZonesStillPaired(const struct ApophisLink *link)
{
  struct DuelCard *trapZone;
  struct DuelCard *monsterZone;

  if (link == NULL || !link->active)
    return FALSE;

  trapZone = ZoneFromBoardCoords(link->trapBoardRow, link->trapBoardCol);
  monsterZone = ZoneFromBoardCoords(link->monBoardRow, link->monBoardCol);

  if (trapZone == NULL || monsterZone == NULL)
    return FALSE;

  return trapZone->id == EMBODIMENT_OF_APOPHIS && monsterZone->id == EMBODIMENT_OF_APOPHIS;
}

static struct ApophisLink *FindApophisLinkContainingZone(const struct DuelCard *zone)
{
  u8 i;
  u8 boardRow;
  u8 boardCol;
  struct ApophisLink *link;

  if (zone == NULL || !TryGetBoardCoords(zone, &boardRow, &boardCol))
    return NULL;

  for (i = 0; i < MAX_APOPHIS_LINKS; i++) {
    if (!gApophisLinks[i].active)
      continue;

    if (gApophisLinks[i].trapBoardRow != boardRow && gApophisLinks[i].monBoardRow != boardRow)
      continue;

    if (gApophisLinks[i].trapBoardRow == boardRow && gApophisLinks[i].trapBoardCol == boardCol)
      link = &gApophisLinks[i];
    else if (gApophisLinks[i].monBoardRow == boardRow && gApophisLinks[i].monBoardCol == boardCol)
      link = &gApophisLinks[i];
    else
      continue;

    if (!ApophisLinkZonesStillPaired(link)) {
      ClearApophisLink(link);
      continue;
    }

    return link;
  }

  return NULL;
}

static struct ApophisLink *FindApophisLinkForZone(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != EMBODIMENT_OF_APOPHIS)
    return NULL;

  return FindApophisLinkContainingZone(zone);
}

static struct DuelCard *GetApophisPartnerZone(struct ApophisLink *link, const struct DuelCard *zone)
{
  struct DuelCard *trapZone;
  struct DuelCard *monsterZone;
  u8 boardRow;
  u8 boardCol;

  if (link == NULL || !link->active || zone == NULL)
    return NULL;

  trapZone = ZoneFromBoardCoords(link->trapBoardRow, link->trapBoardCol);
  monsterZone = ZoneFromBoardCoords(link->monBoardRow, link->monBoardCol);

  if (zone == trapZone)
    return monsterZone;

  if (zone == monsterZone)
    return trapZone;

  if (!TryGetBoardCoords(zone, &boardRow, &boardCol))
    return NULL;

  if (link->trapBoardRow == boardRow && link->trapBoardCol == boardCol)
    return monsterZone;

  if (link->monBoardRow == boardRow && link->monBoardCol == boardCol)
    return trapZone;

  return NULL;
}

u8 RegisterEmbodimentOfApophisLinkFromZones(struct DuelCard *trapZone, struct DuelCard *monsterZone)
{
  struct ApophisLink *link;
  struct ApophisLink *existing;
  u8 trapBoardRow;
  u8 trapBoardCol;
  u8 monBoardRow;
  u8 monBoardCol;
  u8 i;

  if (!TryGetBoardCoords(trapZone, &trapBoardRow, &trapBoardCol))
    return FALSE;

  if (!TryGetBoardCoords(monsterZone, &monBoardRow, &monBoardCol))
    return FALSE;

  for (i = 0; i < MAX_APOPHIS_LINKS; i++) {
    if (!gApophisLinks[i].active)
      continue;

    if (gApophisLinks[i].trapBoardRow == trapBoardRow && gApophisLinks[i].trapBoardCol == trapBoardCol)
      ClearApophisLink(&gApophisLinks[i]);
  }

  link = FindInactiveApophisLink();
  if (link == NULL)
    return FALSE;

  link->active = TRUE;
  link->trapBoardRow = trapBoardRow;
  link->trapBoardCol = trapBoardCol;
  link->monBoardRow = monBoardRow;
  link->monBoardCol = monBoardCol;
  return TRUE;
}

u8 EmbodimentOfApophisTrapZoneIsAwakened(const struct DuelCard *zone)
{
  return FindApophisLinkForZone(zone) != NULL;
}

u8 EmbodimentOfApophisZoneIsTrapForm(const struct DuelCard *zone)
{
  u8 boardRow;
  u8 boardCol;

  if (zone == NULL || zone->id != EMBODIMENT_OF_APOPHIS)
    return FALSE;

  if (!TryGetBoardCoords(zone, &boardRow, &boardCol))
    return FALSE;

  return BoardRowIsBackrow(boardRow);
}

u8 EmbodimentOfApophisZoneOnMonsterRow(const struct DuelCard *zone)
{
  u8 boardRow;
  u8 boardCol;

  if (zone == NULL || zone->id != EMBODIMENT_OF_APOPHIS)
    return FALSE;

  if (!TryGetBoardCoords(zone, &boardRow, &boardCol))
    return FALSE;

  return BoardRowIsMonsterRow(boardRow);
}

u8 EmbodimentOfApophisZoneIsMonsterForm(const struct DuelCard *zone)
{
  if (!EmbodimentOfApophisZoneOnMonsterRow(zone))
    return FALSE;

  return FindApophisLinkContainingZone(zone) != NULL;
}

void ApplyEmbodimentOfApophisCardInfoOverridesForStatMod(struct StatMod *ptr)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  if (ptr == NULL || ptr->card != EMBODIMENT_OF_APOPHIS)
    return;

  for (row = 0; row < 4; row++) {
    if (!BoardRowIsMonsterRow(row))
      continue;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      zone = ZoneFromBoardCoords(row, col);
      if (!EmbodimentOfApophisZoneIsMonsterForm(zone))
        continue;
      if (ComputeFinalStage(zone) != ptr->stage)
        continue;

      gCardInfo.type = TYPE_SEA_SERPENT;
      gCardInfo.color = COLOR_NORMAL;
      return;
    }
  }
}

static void SendApophisZoneToGraveyardIfNeeded(struct DuelCard *zone, u8 turn)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER || EmbodimentOfApophisZoneOnMonsterRow(zone)) {
    MarkGraveyardSendFromField();
    gDuel.duelistbattleState[turn].graveyard = zone->id;
  }
}

void OnEmbodimentOfApophisZoneAboutToClear(struct DuelCard *zone)
{
  struct ApophisLink *link;
  struct DuelCard *partner;
  u8 partnerToGrave;

  if (gApophisClearingPartner || zone == NULL)
    return;

  link = FindApophisLinkContainingZone(zone);
  if (link == NULL || zone->id != EMBODIMENT_OF_APOPHIS)
    return;

  partner = GetApophisPartnerZone(link, zone);
  partnerToGrave = EmbodimentOfApophisZoneOnMonsterRow(partner);
  ClearApophisLink(link);

  if (partner == NULL || partner->id != EMBODIMENT_OF_APOPHIS)
    return;

  gApophisClearingPartner = TRUE;
  if (partnerToGrave)
    MarkGraveyardSendFromField();
  if (partnerToGrave)
    gDuel.duelistbattleState[DUEL_PLAYER].graveyard = partner->id;
  ClearZone(partner);
  gApophisClearingPartner = FALSE;
}

void InitEmbodimentOfApophisMonsterZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = FALSE;
}

LYN_REPLACE_CHECK(ClearZoneAndSendMonToGraveyard2);
void ClearZoneAndSendMonToGraveyard2__Replacement(struct DuelCard *zone, u8 turn)
{
  ApplyOjamaTrioDestructionDamage(zone);
  SendOjamaTrioZoneToGraveyardIfNeeded(zone, turn);
  SendApophisZoneToGraveyardIfNeeded(zone, turn);
  ClearZone(zone);
}
