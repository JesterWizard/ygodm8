#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sChrysalisName[] APPEND_RODATA = "Chrysalis";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsChrysalisMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sChrysalisName);
}

/* Printed Chrysalis → Neo-Spacian pairs from card text. */
static u16 NeoSpacianForChrysalis(u16 chrysalisId)
{
  switch (chrysalisId) {
  case CHRYSALIS_CHICKY:
    return NEO_SPACIAN_AIR_HUMMINGBIRD;
  case CHRYSALIS_DOLPHIN:
    return NEO_SPACIAN_AQUA_DOLPHIN;
  case CHRYSALIS_MOLE:
    return NEO_SPACIAN_GRAND_MOLE;
  case CHRYSALIS_PANTAIL:
    return NEO_SPACIAN_DARK_PANTHER;
  case CHRYSALIS_PINNY:
    return NEO_SPACIAN_GLOW_MOSS;
  default:
    /* ponytail: only the five Chrysalis in-trunk pairs are mapped. */
    return CARD_NONE;
  }
}

static u8 IsValidChrysalisTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !IsChrysalisMonster(zone->id) || !MonsterIsFaceUp(zone))
    return FALSE;

  return NeoSpacianForChrysalis(zone->id) != CARD_NONE;
}

static u8 HasChrysalisTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidChrysalisTarget(ActiveMonsterFixedRow(), col))
      return TRUE;
  }

  return FALSE;
}

static u8 FindNeoInFixedGy(u8 fixedDuelist, u16 neoId, u8 *outIndex)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != neoId)
      return FALSE;

    *outIndex = 0;
    return TRUE;
  }

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == neoId) {
      *outIndex = i;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 FindNeoInEitherGy(u16 neoId, u8 *outFixedDuelist, u8 *outIndex)
{
  u8 fd;

  fd = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  if (FindNeoInFixedGy(fd, neoId, outIndex)) {
    *outFixedDuelist = fd;
    return TRUE;
  }

  fd = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  if (FindNeoInFixedGy(fd, neoId, outIndex)) {
    *outFixedDuelist = fd;
    return TRUE;
  }

  return FALSE;
}

static u8 FieldHasMappedNeoInGy(void)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 fd;
  u8 idx;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 neoId;

    if (!IsValidChrysalisTarget(monsterRow, col))
      continue;

    zone = gFixedZones[monsterRow][col];
    neoId = NeoSpacianForChrysalis(zone->id);
    if (neoId != CARD_NONE && FindNeoInEitherGy(neoId, &fd, &idx))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateCOCOON_REBIRTH(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!HasChrysalisTarget())
    return FALSE;

  return FieldHasMappedNeoInGy();
}

static enum DuelActionResult SpecialSummonNeoFromGy(u8 fixedDuelist, u8 gyIndex, u16 neoId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 cardId;
  u8 turnDuelist;

  if (!GraveyardExpand_IsEnabled()) {
    turnDuelist = (gTurnDuelistBattleState[ACTIVE_DUELIST]
                   == &gDuel.duelistbattleState[fixedDuelist])
        ? ACTIVE_DUELIST
        : INACTIVE_DUELIST;
    cardId = GetGraveCardAndClearGrave(turnDuelist);
    if (cardId != neoId)
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  if (cardId != neoId)
    return DUEL_ACTION_NO_TARGET;

  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static void DestroyCocoonSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == COCOON_REBIRTH)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveChrysalisTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];
  u16 neoId;
  u8 gyFixed;
  u8 gyIndex;

  if (!IsValidChrysalisTarget(fixedRow, fixedCol))
    return;

  neoId = NeoSpacianForChrysalis(tributeZone->id);
  if (neoId == CARD_NONE || !FindNeoInEitherGy(neoId, &gyFixed, &gyIndex))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   FALSE);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Re-find after tribute — Chrysalis landing in GY can shift indices. */
  if (!FindNeoInEitherGy(neoId, &gyFixed, &gyIndex))
    return;

  SpecialSummonNeoFromGy(gyFixed, gyIndex, neoId);
  UpdateDuelGfxExceptField();
}

static void CancelChrysalisTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyCocoonSpellZone();
}

static u8 AiPickChrysalisTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();
  u8 fd;
  u8 idx;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 neoId;

    if (!IsValidChrysalisTarget(monsterRow, col))
      continue;

    zone = gFixedZones[monsterRow][col];
    neoId = NeoSpacianForChrysalis(zone->id);
    if (neoId == CARD_NONE || !FindNeoInEitherGy(neoId, &fd, &idx))
      continue;

    *outRow = monsterRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void COCOON_REBIRTH_ResolveBody(void)
{
  Duel_ShowEffectText(COCOON_REBIRTH);

  if (IsDuelOver() == TRUE || !CanActivateCOCOON_REBIRTH())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidChrysalisTarget, ResolveChrysalisTarget, CancelChrysalisTargeting,
                     AiPickChrysalisTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectCOCOON_REBIRTH(void)
{
  if (!CanActivateCOCOON_REBIRTH()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(COCOON_REBIRTH, COCOON_REBIRTH_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void COCOON_REBIRTH_SelfCheck(void)
{
  if (NeoSpacianForChrysalis(CHRYSALIS_CHICKY) != NEO_SPACIAN_AIR_HUMMINGBIRD)
    while (1)
      ;
  if (NeoSpacianForChrysalis(CHRYSALIS_PINNY) != NEO_SPACIAN_GLOW_MOSS)
    while (1)
      ;
}
#endif
