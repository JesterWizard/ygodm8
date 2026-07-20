#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

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

  return Duel_CardNameContains(cardId, sTheAgentName);
}

static u8 IsLightFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_LIGHT && gCardInfo.type == TYPE_FAIRY;
}

static u8 IsFaceUpLightFairyZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!IsLightFairyMonster(zone->id))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 OwnGyHasTheAgent(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsTheAgentMonster(gDuel.duelistbattleState[fixedDuelist].graveyard);

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsTheAgentMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasFaceUpLightFairy(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpLightFairyZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 BanishFirstAgentFromGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (!IsTheAgentMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsTheAgentMonster(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    RemovedFromPlay_PushFixed(fixedDuelist, cardId);
    return TRUE;
  }

  return FALSE;
}

static u8 OwnMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidLightFairyTarget(u8 fixedRow, u8 fixedCol)
{
  if (fixedRow != OwnMonsterFixedRow())
    return FALSE;

  return IsFaceUpLightFairyZone(gFixedZones[fixedRow][fixedCol]);
}

static void ResolveBuffTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();

  if (!IsValidLightFairyTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (!BanishFirstAgentFromGy(fixedDuelist))
    return;

  /* ponytail: +800 ATK until EP needs exact stage/EP clear; Sanctuary RFG revive
   * FALSE. Ceiling: banish Agent from GY → +2 tempStage on LIGHT Fairy. */
  if (zone->tempStage < 126)
    zone->tempStage += 2;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = OwnMonsterFixedRow();

  *outRow = row;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidLightFairyTarget(row, col)) {
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char CanActivateTHE_AGENT_OF_MIRACLES_JUPITER(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != THE_AGENT_OF_MIRACLES_JUPITER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_AGENT_OF_MIRACLES_JUPITER)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OwnGyHasTheAgent(fixedDuelist) && FieldHasFaceUpLightFairy();
}

void ActivateTHE_AGENT_OF_MIRACLES_JUPITEREffect(void)
{
  Duel_ShowEffectTextTyped(THE_AGENT_OF_MIRACLES_JUPITER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsValidLightFairyTarget, ResolveBuffTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
