#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "neutron_blast.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 sNeutronBlastAttacksUsed APPEND_DATA = {0};
static u8 sNeutronBlastBlockOppEffects APPEND_DATA = {FALSE};

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

static u8 IsFusionSummonedBeud(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != BLUE_EYES_ULTIMATE_DRAGON)
    return FALSE;

  /* unk4 == 2 marks Special Summon (Fusion SS via Duel_SpecialSummonMonsterId). */
  if (zone->unk4 != 2)
    return FALSE;

  return MonsterIsFaceUp(zone);
}

static u8 IsValidNeutronBlastTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsFusionSummonedBeud(zone);
}

static u8 HasNeutronBlastTarget(void)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidNeutronBlastTarget(fixedRow, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateNEUTRON_BLAST(void)
{
  return HasNeutronBlastTarget();
}

static void DestroyNeutronBlastSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == NEUTRON_BLAST)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ApplyNeutronBlast(struct DuelCard *zone)
{
  /* Flag BEUD for Neutron Blast this turn (unkThree is a 1-bit field). */
  zone->unkThree = 1;
  zone->effectUsedThisTurn = FALSE;
  sNeutronBlastAttacksUsed = 0;
  sNeutronBlastBlockOppEffects = FALSE;
}

void TryUnlockNeutronBlastForExtraAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->id != BLUE_EYES_ULTIMATE_DRAGON)
    return;
  if (attacker->unkThree == 0)
    return;
  if (sNeutronBlastAttacksUsed >= 2)
    return;

  sNeutronBlastAttacksUsed++;
  attacker->isLocked = FALSE;
  sNeutronBlastBlockOppEffects = TRUE;
}

u8 NeutronBlast_ShouldBlockOpponentEffects(const struct DuelCard *attacker)
{
  (void)attacker;
  return sNeutronBlastBlockOppEffects;
}

void NeutronBlast_ClearDamageStepBlock(void)
{
  sNeutronBlastBlockOppEffects = FALSE;
}

static void ResolveNeutronBlastTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidNeutronBlastTarget(fixedRow, fixedCol))
    return;

  ApplyNeutronBlast(zone);
  DestroyNeutronBlastSpellZone();
}

static void CancelNeutronBlastTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyNeutronBlastSpellZone();
}

static u8 AiPickNeutronBlastTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidNeutronBlastTarget(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void NEUTRON_BLAST_ResolveBody(void)
{
  Duel_ShowEffectText(NEUTRON_BLAST);

  if (IsDuelOver() == TRUE || !HasNeutronBlastTarget())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidNeutronBlastTarget, ResolveNeutronBlastTarget,
                     CancelNeutronBlastTargeting, AiPickNeutronBlastTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectNEUTRON_BLAST(void)
{
  if (!CanActivateNEUTRON_BLAST()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(NEUTRON_BLAST, NEUTRON_BLAST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void NEUTRON_BLAST_SelfCheck(void)
{
  if (BLUE_EYES_ULTIMATE_DRAGON == CARD_NONE)
    while (1)
      ;
}
#endif
