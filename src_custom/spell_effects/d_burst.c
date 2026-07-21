#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "d_burst.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_conditions.h"
#include "effect_events.h"
#include "effect_ops.h"
#include "effect_selectors.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

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

  Op_DestroyZone(zone, WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  if (Op_Draw(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (ControlsDestinyHero())
    TrySsDestinyHero();

  EffectOpt_MarkUsed(D_BURST);
  UpdateDuelGfxExceptField();
}

static void DBurstCancel(void)
{
  Duel_ClearPickZone();
}

u8 CanActivateD_BURST(void)
{
  if (EffectOpt_IsUsed(D_BURST))
    return FALSE;

  return EffectSel_ExistsByCond(EFFECT_COND_ACTIVE_FACE_UP_SPELL);
}

static s8 FindDBurstGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return -1;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == D_BURST)
      return (s8)i;
  }

  return -1;
}

static u8 AttackerBelongsToFixedDuelist(struct DuelCard *attacker, u8 fixedDuelist)
{
  u8 turnRow;
  u8 turnCol;
  u8 turnDuelist;

  if (attacker == NULL || !Duel_FindTurnMonsterZone(attacker, &turnRow, &turnCol))
    return FALSE;

  turnDuelist = turnRow == ACTIVE_DUELIST_MONSTER_ROW ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  return FixedDuelistForTurnDuelist(turnDuelist) == fixedDuelist;
}

/* Parent wires these d_burst.h helpers at the end of a Destiny HERO battle. */
u8 D_Burst_CanActivateGyBattle(struct DuelCard *attacker, u8 fixedDuelist)
{
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  if (EffectOpt_IsUsed(D_BURST))
    return FALSE;

  if (!AttackerBelongsToFixedDuelist(attacker, fixedDuelist))
    return FALSE;

  if (!IsDestinyHeroMonster(attacker->id))
    return FALSE;

  return FindDBurstGyIndex(fixedDuelist) >= 0;
}

void D_Burst_ActivateGyBattle(struct DuelCard *attacker, u8 fixedDuelist)
{
  s8 gyIndex;

  if (!D_Burst_CanActivateGyBattle(attacker, fixedDuelist))
    return;

  gyIndex = FindDBurstGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectText(D_BURST);
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex) == CARD_NONE)
    return;

  EffectOpt_MarkUsed(D_BURST);
  attacker->isLocked = FALSE;
  UpdateDuelGfxExceptField();
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
  Duel_SetupPickZone(EffectCond_ActiveFaceUpSpell, DBurstOnTarget, DBurstCancel,
                     EffectSel_AiPickFirst);
  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectD_BURST(void)
{
  if (Duel_TryResolveSpellThroughTraps(D_BURST, D_BURST_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
