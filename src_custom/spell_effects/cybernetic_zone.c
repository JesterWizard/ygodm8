#include "global.h"
#include "common-chax.h"
#include "cybernetic_zone.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "removed_from_play.h"
#include "spell_effects.h"

void IncrementPermStage(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

#define CYBERNETIC_ZONE_PHASE_IDLE 0
#define CYBERNETIC_ZONE_PHASE_BANISHED 1
#define CYBERNETIC_ZONE_PHASE_AWAIT_DESTROY 2
#define CYBERNETIC_ZONE_BOARD_CELLS 20

/* Pending temporary-banish state (wire TryApply* from turn_effect_hooks). */
static u16 sCyberneticZoneCardId APPEND_DATA = {0};
static u8 sCyberneticZoneFixedDuelist APPEND_DATA = {0};
static u8 sCyberneticZonePhase APPEND_DATA = {0};
static u16 sCyberneticZoneBoardCell APPEND_DATA = {0};

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsMachineFusionMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.color != FUSION_CARD)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsValidCyberneticZoneTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  if (!IsMachineFusionMonster(zone->id))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasCyberneticZoneTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidCyberneticZoneTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateCYBERNETIC_ZONE(void)
{
  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  return HasCyberneticZoneTarget();
}

static void DestroyCyberneticZoneSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == CYBERNETIC_ZONE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u16 GetDuelBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone < base || zone >= base + CYBERNETIC_ZONE_BOARD_CELLS)
    return 0xFFFF;

  return (u16)(zone - base);
}

/* ponytail: no RemovedFromPlay_RemoveAt — shift RFP after return. */
static void RemoveBanishedMatching(u8 fixedDuelist, u16 cardId)
{
  u8 count;
  u8 i;
  u8 j;

  if (fixedDuelist > DUEL_OPPONENT || cardId == CARD_NONE)
    return;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    if (RemovedFromPlay_GetCardAt(fixedDuelist, i) != cardId)
      continue;

    for (j = i + 1; j < count; j++)
      gRemovedFromPlay[fixedDuelist][j - 1] = gRemovedFromPlay[fixedDuelist][j];

    gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
    return;
  }
}

static void DoubleReturnedAtk(struct DuelCard *zone)
{
  u16 originalAtk;
  u8 stages;
  u8 i;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  SetCardInfo(zone->id);
  originalAtk = gCardInfo.atk;
  /* ponytail: stage unit is 500 ATK — double via +original/500 stages.
   * Ceiling: non-multiples of 500 are floored; upgrade: exact ATK overlay. */
  stages = (u8)(originalAtk / 500);
  for (i = 0; i < stages; i++)
    IncrementPermStage(zone);
}

static void ClearCyberneticZoneState(void)
{
  sCyberneticZoneCardId = CARD_NONE;
  sCyberneticZoneFixedDuelist = 0;
  sCyberneticZonePhase = CYBERNETIC_ZONE_PHASE_IDLE;
  sCyberneticZoneBoardCell = 0xFFFF;
}

/* Wire from turn_effect_hooks near TryApplyPowerBondEndPhaseBurn.
 * Runs at start of next turn (engine "End Phase" timing). */
void TryApplyCyberneticZoneEndPhase(void)
{
  u16 cardId;
  u8 fixedDuelist;
  u8 turnDuelist;
  struct DuelSummonOpts opts;
  enum DuelActionResult result;
  u8 col;
  struct DuelCard *zone;

  if (sCyberneticZonePhase != CYBERNETIC_ZONE_PHASE_BANISHED)
    return;

  if (IsDuelOver() == TRUE) {
    ClearCyberneticZoneState();
    return;
  }

  /* Controller's turn just ended → INACTIVE is that duelist. */
  if (FixedDuelistForTurnDuelist(INACTIVE_DUELIST) != sCyberneticZoneFixedDuelist)
    return;

  cardId = sCyberneticZoneCardId;
  fixedDuelist = sCyberneticZoneFixedDuelist;
  turnDuelist = TurnDuelistForFixed(fixedDuelist);

  if (cardId == CARD_NONE || FirstEmptyZoneInRow(gTurnZones[Duel_TurnMonsterRowForDuelist(turnDuelist)]) < 0) {
    ClearCyberneticZoneState();
    return;
  }

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  result = Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts);
  if (result != DUEL_ACTION_OK && result != DUEL_ACTION_DUEL_OVER) {
    ClearCyberneticZoneState();
    return;
  }

  RemoveBanishedMatching(fixedDuelist, cardId);

  zone = NULL;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *candidate = gTurnZones[Duel_TurnMonsterRowForDuelist(turnDuelist)][col];

    if (candidate != NULL && candidate->id == cardId) {
      zone = candidate;
      break;
    }
  }

  if (zone != NULL) {
    DoubleReturnedAtk(zone);
    sCyberneticZoneBoardCell = GetDuelBoardCellIndex(zone);
  } else {
    sCyberneticZoneBoardCell = 0xFFFF;
  }

  sCyberneticZonePhase = CYBERNETIC_ZONE_PHASE_AWAIT_DESTROY;
  UpdateDuelGfxExceptField();
}

/* Wire from turn_effect_hooks Standby (with Future Fusion / Capsule). */
void TryApplyCyberneticZoneStandby(void)
{
  struct DuelCard *zone;

  if (sCyberneticZonePhase != CYBERNETIC_ZONE_PHASE_AWAIT_DESTROY)
    return;

  if (IsDuelOver() == TRUE) {
    ClearCyberneticZoneState();
    return;
  }

  /* Controller's Standby → ACTIVE is that duelist. */
  if (FixedDuelistForTurnDuelist(ACTIVE_DUELIST) != sCyberneticZoneFixedDuelist)
    return;

  if (sCyberneticZoneBoardCell < CYBERNETIC_ZONE_BOARD_CELLS) {
    struct DuelCard *base = &gDuel.board[0][0];

    zone = &base[sCyberneticZoneBoardCell];
    if (zone->id == sCyberneticZoneCardId)
      Duel_DestroyZone(zone, ACTIVE_DUELIST, TRUE);
  }

  ClearCyberneticZoneState();
}

static void ResolveCyberneticZoneTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u16 cardId;
  u8 fixedDuelist;

  if (!IsValidCyberneticZoneTarget(fixedRow, fixedCol)) {
    DestroyCyberneticZoneSpellZone();
    return;
  }

  cardId = zone->id;
  fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  {
    enum DuelActionResult banished = Duel_BanishZone(zone, TRUE);

    if (banished == DUEL_ACTION_DUEL_OVER) {
      DestroyCyberneticZoneSpellZone();
      return;
    }
    if (banished != DUEL_ACTION_OK) {
      DestroyCyberneticZoneSpellZone();
      return;
    }
  }

  sCyberneticZoneCardId = cardId;
  sCyberneticZoneFixedDuelist = fixedDuelist;
  sCyberneticZonePhase = CYBERNETIC_ZONE_PHASE_BANISHED;
  sCyberneticZoneBoardCell = 0xFFFF;

  DestroyCyberneticZoneSpellZone();

  /* Parent wires TryApplyCyberneticZoneEndPhase and
   * TryApplyCyberneticZoneStandby from cybernetic_zone.h into the matching
   * turn-effect boundaries. */
}

static void CancelCyberneticZoneTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyCyberneticZoneSpellZone();
}

static u8 AiPickCyberneticZoneTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidCyberneticZoneTarget(fixedRow, col))
      continue;

    zone = gFixedZones[fixedRow][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (!found || atk > bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = fixedRow;
      *outCol = col;
    }
  }

  return found;
}

static void CYBERNETIC_ZONE_ResolveBody(void)
{
  Duel_ShowEffectText(CYBERNETIC_ZONE);

  if (IsDuelOver() == TRUE || !CanActivateCYBERNETIC_ZONE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidCyberneticZoneTarget, ResolveCyberneticZoneTarget,
                     CancelCyberneticZoneTargeting, AiPickCyberneticZoneTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectCYBERNETIC_ZONE(void)
{
  if (!CanActivateCYBERNETIC_ZONE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(CYBERNETIC_ZONE, CYBERNETIC_ZONE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CYBERNETIC_ZONE_SelfCheck(void)
{
  if (!Duel_CardHasMonsterType(CYBER_END_DRAGON, TYPE_MACHINE))
    while (1)
      ;
  if (Duel_CardHasMonsterType(BLUE_EYES_WHITE_DRAGON, TYPE_MACHINE))
    while (1)
      ;
}
#endif
