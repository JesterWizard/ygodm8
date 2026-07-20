#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
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

static u8 IsValidAceOfSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != PLAYER_MONSTER_ROW && fixedRow != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 HasAceOfSwordTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidAceOfSwordTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CoinIsHeads(void)
{
  return RandRangeU8(0, 1) == 1;
}

static void DestroyAceOfSwordSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == ACE_OF_SWORD)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ResolveAceOfSwordTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  u16 atk;
  u8 burnDuelist;

  if (!IsValidAceOfSwordTarget(fixedRow, fixedCol))
    return;

  atk = Duel_GetZoneFinalAtk(zone);
  burnDuelist = CoinIsHeads() ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  if (atk > 0 && Duel_ChangeLp(burnDuelist, -(s32)atk, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  DestroyAceOfSwordSpellZone();
}

static void CancelAceOfSwordTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  /* Activation already committed past traps — send the spell to GY. */
  DestroyAceOfSwordSpellZone();
}

static u8 AiPickAceOfSwordTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidAceOfSwordTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateACE_OF_SWORD(void)
{
  return HasAceOfSwordTarget();
}

static void ACE_OF_SWORD_ResolveBody(void)
{
  Duel_ShowEffectText(ACE_OF_SWORD);

  if (IsDuelOver() == TRUE || !CanActivateACE_OF_SWORD())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidAceOfSwordTarget, ResolveAceOfSwordTarget, CancelAceOfSwordTargeting,
                     AiPickAceOfSwordTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectACE_OF_SWORD(void)
{
  if (!CanActivateACE_OF_SWORD()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ACE_OF_SWORD, ACE_OF_SWORD_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ACE_OF_SWORD_SelfCheck(void)
{
  struct DuelCard stub;

  stub.id = BLUE_EYES_WHITE_DRAGON;
  stub.isFaceUp = TRUE;
  stub.isDefending = FALSE;
  if (!MonsterIsFaceUp(&stub))
    while (1)
      ;

  stub.id = MYSTICAL_SPACE_TYPHOON;
  if (MonsterIsFaceUp(&stub))
    while (1)
      ;
}
#endif
