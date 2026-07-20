#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 sDBurstUsedThisTurn APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 IsFaceUpSpellTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL;
}

static u8 HasFaceUpSpell(void)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpSpellTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 ControlsDestinyHero(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsDestinyHeroMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static enum DuelActionResult TrySsDestinyHero(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 i;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (ArchlordKristya_IsSpecialSummonLocked())
    return DUEL_ACTION_OK;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return DUEL_ACTION_OK;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDestinyHeroMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, i, opts);
  }

  if (GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

      if (IsDestinyHeroMonster(cardId))
        return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
    }
  }

  /* Banished not scanned — ponytail. */
  return DUEL_ACTION_OK;
}

static void DBurstOnTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_ClearPickZone();
  if (zone == NULL)
    return;

  Duel_DestroyZone(zone, WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (ControlsDestinyHero())
    TrySsDestinyHero();

  sDBurstUsedThisTurn = TRUE;
  UpdateDuelGfxExceptField();
}

static void DBurstCancel(void)
{
  Duel_ClearPickZone();
}

static u8 DBurstValidate(u8 fixedRow, u8 fixedCol)
{
  return IsFaceUpSpellTarget(fixedRow, fixedCol);
}

static u8 DBurstAiPick(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsFaceUpSpellTarget(row, col))
      continue;
    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

u8 CanActivateD_BURST(void)
{
  if (sDBurstUsedThisTurn)
    return FALSE;

  return HasFaceUpSpell();
}

static void D_BURST_ResolveBody(void)
{
  if (!CanActivateD_BURST()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(D_BURST);
  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  Duel_SetupPickZone(DBurstValidate, DBurstOnTarget, DBurstCancel, DBurstAiPick);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  /* ponytail: GY ignition second attack needs battle End Damage Step hook. */
}

APPEND_TEXT void EffectD_BURST(void)
{
  if (Duel_TryResolveSpellThroughTraps(D_BURST, D_BURST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
