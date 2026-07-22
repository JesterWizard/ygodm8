#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "spell_gear.h"

#define SPELL_GEAR_SEND_COUNT 3

void UpdateDuelGfxExceptField(void);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";
static const char sAncientGearGolemName[] APPEND_RODATA = "Ancient Gear Golem";

static u8 sSpellGearPickCount APPEND_DATA = {0};
static u8 sSpellGearPickRows[SPELL_GEAR_SEND_COUNT] APPEND_DATA = {0};
static u8 sSpellGearPickCols[SPELL_GEAR_SEND_COUNT] APPEND_DATA = {0};
static u8 sSpellGearNsLockPlayer APPEND_DATA = {0};
static u8 sSpellGearNsLockOpponent APPEND_DATA = {0};

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 IsAncientGearCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 IsAncientGearGolemCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearGolemName);
}

static u8 AlreadyPicked(u8 fixedRow, u8 fixedCol)
{
  u8 i;

  for (i = 0; i < sSpellGearPickCount; i++) {
    if (sSpellGearPickRows[i] == fixedRow && sSpellGearPickCols[i] == fixedCol)
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidSpellGearSendTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow() && fixedRow != ActiveBackrowFixedRow())
    return FALSE;

  if (AlreadyPicked(fixedRow, fixedCol))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsAncientGearCard(zone->id);
}

static u8 CountAncientGearOnField(void)
{
  u8 count = 0;
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 backRow = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *monster = gFixedZones[monsterRow][col];
    struct DuelCard *back = gFixedZones[backRow][col];

    if (monster != NULL && IsAncientGearCard(monster->id) && !AlreadyPicked(monsterRow, col))
      count++;
    if (back != NULL && IsAncientGearCard(back->id) && !AlreadyPicked(backRow, col))
      count++;
  }

  return count;
}

static u8 HandHasAncientGearGolem(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnHands[ACTIVE_DUELIST][i]->id == ANCIENT_GEAR_GOLEM)
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasAncientGearGolem(void)
{
  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM) >= 0;
}

static u8 CanSpecialSummonGolem(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 CanActivateSPELL_GEAR(void)
{
  /* Temporarily clear pick state so count is accurate before activation. */
  sSpellGearPickCount = 0;
  return CountAncientGearOnField() >= SPELL_GEAR_SEND_COUNT;
}

static u8 IsNonGolemMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return !IsAncientGearGolemCard(zone->id);
}

static void DestroySpellGearSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == SPELL_GEAR)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void TryOptionalSummonGolems(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  /* "You can" — AI always summons when able; player path same (no skip UI).
   * Optional SS offered as auto-yes when legal; cannot skip a legal hand/Deck AGG SS
   * (skip UI unsupported). Upgrade: A/B confirm per location. */
  if (HandHasAncientGearGolem() && CanSpecialSummonGolem())
    Duel_SpecialSummonFromHand(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM, NULL, opts);

  if (IsDuelOver() == TRUE)
    return;

  if (DeckHasAncientGearGolem() && CanSpecialSummonGolem())
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, ANCIENT_GEAR_GOLEM, opts);
}

static void FinishSpellGear(void)
{
  u8 i;

  for (i = 0; i < sSpellGearPickCount; i++) {
    struct DuelCard *zone = gFixedZones[sSpellGearPickRows[i]][sSpellGearPickCols[i]];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
    if (IsDuelOver() == TRUE)
      return;
  }

  TryOptionalSummonGolems();
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyAllMonstersMatching(ACTIVE_DUELIST_MONSTER_ROW, IsNonGolemMonster, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  DestroySpellGearSpellZone();

  SpellGear_ArmNormalSummonLock(
      gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER]
          ? DUEL_PLAYER
          : DUEL_OPPONENT);
  gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked = 1;
}

void SpellGear_ArmNormalSummonLock(u8 fixedDuelist)
{
  /* 2 = rest of this turn + next turn (until end of your next turn). */
  if (fixedDuelist == DUEL_PLAYER)
    sSpellGearNsLockPlayer = 2;
  else if (fixedDuelist == DUEL_OPPONENT)
    sSpellGearNsLockOpponent = 2;
}

u8 SpellGear_BlocksNormalSummon(u8 turnDuelist)
{
  u8 fixed;

  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    fixed = DUEL_PLAYER;
  else
    fixed = DUEL_OPPONENT;

  if (fixed == DUEL_PLAYER)
    return sSpellGearNsLockPlayer > 0;
  return sSpellGearNsLockOpponent > 0;
}

void SpellGear_OnTurnBoundary(void)
{
  if (sSpellGearNsLockPlayer > 0)
    sSpellGearNsLockPlayer--;
  if (sSpellGearNsLockOpponent > 0)
    sSpellGearNsLockOpponent--;
}

static void CancelSpellGearTargeting(void)
{
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 backRow = ActiveBackrowFixedRow();
  u8 col;

  PlayMusic(SFX_CANCEL);

  while (sSpellGearPickCount < SPELL_GEAR_SEND_COUNT) {
    u8 found = FALSE;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidSpellGearSendTarget(monsterRow, col)) {
        sSpellGearPickRows[sSpellGearPickCount] = monsterRow;
        sSpellGearPickCols[sSpellGearPickCount] = col;
        sSpellGearPickCount++;
        found = TRUE;
        break;
      }
      if (IsValidSpellGearSendTarget(backRow, col)) {
        sSpellGearPickRows[sSpellGearPickCount] = backRow;
        sSpellGearPickCols[sSpellGearPickCount] = col;
        sSpellGearPickCount++;
        found = TRUE;
        break;
      }
    }

    if (!found)
      break;
  }

  if (sSpellGearPickCount >= SPELL_GEAR_SEND_COUNT)
    FinishSpellGear();
  else
    DestroySpellGearSpellZone();
}

static u8 AiPickSpellGearTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 backRow = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidSpellGearSendTarget(monsterRow, col)) {
      *outRow = monsterRow;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidSpellGearSendTarget(backRow, col)) {
      *outRow = backRow;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void BeginNextSpellGearPick(void);

static void ResolveSpellGearTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidSpellGearSendTarget(fixedRow, fixedCol))
    return;

  sSpellGearPickRows[sSpellGearPickCount] = fixedRow;
  sSpellGearPickCols[sSpellGearPickCount] = fixedCol;
  sSpellGearPickCount++;

  if (sSpellGearPickCount < SPELL_GEAR_SEND_COUNT) {
    BeginNextSpellGearPick();
    return;
  }

  FinishSpellGear();
}

static void BeginNextSpellGearPick(void)
{
  Duel_SetupPickZone(IsValidSpellGearSendTarget, ResolveSpellGearTarget,
                     CancelSpellGearTargeting, AiPickSpellGearTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void ResolveSpellGearForAi(void)
{
  while (sSpellGearPickCount < SPELL_GEAR_SEND_COUNT) {
    u8 row;
    u8 col;

    if (!AiPickSpellGearTarget(&row, &col))
      break;

    sSpellGearPickRows[sSpellGearPickCount] = row;
    sSpellGearPickCols[sSpellGearPickCount] = col;
    sSpellGearPickCount++;
  }

  if (sSpellGearPickCount >= SPELL_GEAR_SEND_COUNT)
    FinishSpellGear();
  else
    DestroySpellGearSpellZone();
}

static void SPELL_GEAR_ResolveBody(void)
{
  Duel_ShowEffectText(SPELL_GEAR);

  sSpellGearPickCount = 0;

  if (IsDuelOver() == TRUE || CountAncientGearOnField() < SPELL_GEAR_SEND_COUNT)
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolveSpellGearForAi();
    return;
  }

  BeginNextSpellGearPick();
}

APPEND_TEXT void EffectSPELL_GEAR(void)
{
  if (!CanActivateSPELL_GEAR()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(SPELL_GEAR, SPELL_GEAR_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SPELL_GEAR_SelfCheck(void)
{
  if (!IsAncientGearCard(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (!IsAncientGearGolemCard(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (!IsAncientGearGolemCard(ULTIMATE_ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
