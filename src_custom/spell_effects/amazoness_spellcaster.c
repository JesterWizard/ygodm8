#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "riryoku.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

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

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 InactiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u16 GetOriginalAtk(u16 cardId)
{
  SetCardInfo(cardId);
  return gCardInfo.atk;
}

static u8 IsValidAmazonessTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return Duel_IsAmazonessCard(zone->id);
}

static u8 IsValidOpponentFaceUpTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != InactiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasAmazonessTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidAmazonessTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 HasOpponentFaceUpTarget(void)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidOpponentFaceUpTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateAMAZONESS_SPELLCASTER(void)
{
  return HasAmazonessTarget() && HasOpponentFaceUpTarget();
}

static void DestroySpellcasterSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == AMAZONESS_SPELLCASTER)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishSpellcasterSwap(u8 oppRow, u8 oppCol)
{
  struct DuelCard *amazoness = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];
  struct DuelCard *opponent = gFixedZones[oppRow][oppCol];
  u16 amazonessOrig;
  u16 opponentOrig;
  s16 amazonessDelta;
  s16 opponentDelta;

  if (!IsValidAmazonessTarget(gSpellEffectData.row2, gSpellEffectData.col2)
      || !IsValidOpponentFaceUpTarget(oppRow, oppCol)) {
    DestroySpellcasterSpellZone();
    return;
  }

  amazonessOrig = GetOriginalAtk(amazoness->id);
  opponentOrig = GetOriginalAtk(opponent->id);

  /* Switch printed ATK via EOT-cleared Riryoku deltas (stages/field still apply). */
  amazonessDelta = (s16)((s32)opponentOrig - (s32)amazonessOrig);
  opponentDelta = (s16)((s32)amazonessOrig - (s32)opponentOrig);

  if (amazonessDelta != 0)
    AddRiryokuAtkDelta(amazoness, amazonessDelta);
  if (opponentDelta != 0)
    AddRiryokuAtkDelta(opponent, opponentDelta);

  RefreshFieldMonsterStatOverlays();
  DestroySpellcasterSpellZone();
}

static void CancelSpellcasterTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroySpellcasterSpellZone();
}

static u8 AiPickOpponentFaceUp(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = InactiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidOpponentFaceUpTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveOpponentFaceUpTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidOpponentFaceUpTarget(fixedRow, fixedCol))
    return;

  FinishSpellcasterSwap(fixedRow, fixedCol);
}

static void BeginOpponentFaceUpPick(void)
{
  Duel_SetupPickZone(IsValidOpponentFaceUpTarget, ResolveOpponentFaceUpTarget,
                     CancelSpellcasterTargeting, AiPickOpponentFaceUp);
  Duel_EnterPickZoneTargeting();
}

static u8 AiPickAmazoness(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidAmazonessTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveAmazonessTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidAmazonessTarget(fixedRow, fixedCol))
    return;

  gSpellEffectData.row2 = fixedRow;
  gSpellEffectData.col2 = fixedCol;

  if (!HasOpponentFaceUpTarget()) {
    DestroySpellcasterSpellZone();
    return;
  }

  BeginOpponentFaceUpPick();
}

static void ResolveSpellcasterForAi(void)
{
  u8 amazonRow;
  u8 amazonCol;
  u8 oppRow;
  u8 oppCol;

  if (!AiPickAmazoness(&amazonRow, &amazonCol) || !AiPickOpponentFaceUp(&oppRow, &oppCol)) {
    DestroySpellcasterSpellZone();
    return;
  }

  gSpellEffectData.row2 = amazonRow;
  gSpellEffectData.col2 = amazonCol;
  FinishSpellcasterSwap(oppRow, oppCol);
}

static void AMAZONESS_SPELLCASTER_ResolveBody(void)
{
  Duel_ShowEffectText(AMAZONESS_SPELLCASTER);

  if (IsDuelOver() == TRUE || !CanActivateAMAZONESS_SPELLCASTER())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  if (WhoseTurn() != DUEL_PLAYER) {
    ResolveSpellcasterForAi();
    return;
  }

  Duel_SetupPickZone(IsValidAmazonessTarget, ResolveAmazonessTarget, CancelSpellcasterTargeting,
                     AiPickAmazoness);
  Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectAMAZONESS_SPELLCASTER(void)
{
  if (!CanActivateAMAZONESS_SPELLCASTER()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_SPELLCASTER, AMAZONESS_SPELLCASTER_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_SPELLCASTER_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
