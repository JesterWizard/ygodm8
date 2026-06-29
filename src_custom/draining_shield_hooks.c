#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "debug_ruleset.h"
#include "draining_shield.h"
#include "embodiment_of_apophis.h"
#include "fairy_box.h"
#include "mirror_wall.h"
#include "cats_ear_tribe.h"
#include "spirit_ryu.h"
#include "graveyard_effects.h"
#include "hayabusa_knight.h"
#include "mermaid_knight.h"
#include "twin_swords_of_flashing_light_tryce.h"
#include "tyrant_dragon.h"
#include "cyber_twin_dragon.h"
#include "the_unhappy_maiden.h"
#include "vampire_baby.h"
#include "ghost_knight_of_jackal.h"
#include "toll.h"
#include "the_dark_door.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;

void sub_801BC00(void);
void sub_8022080(void);
void CheckGraveyardAndLoserFlags(void);
void HandleAtkAndLifePointsAction(void);
void SetAttackAction(s32, s32);
void UpdateAllDuelGfx(void);
void ResolveTheUnhappyMaidenBattleEffect(void);
void ResolveVampireBabyBattleEffect(void);
void ResolveGhostKnightOfJackalBattleEffect(void);
void ResolveMefistTheInfernalGeneralDiscardBattleEffect(void);
void ResolveReaperOnTheNightmareDirectDamageEffect(void);
void ResolveSpiritReaperDiscardBattleEffect(void);
void ResolveGuardianAngelJoanBattleEffect(void);
void ResolveRoyalKnightBattleEffect(void);
void ResolveElementalHeroSteamHealerBattleEffect(void);
void ResolveLesserFiendBattleEffect(void);
void ResolveDarkMagicianOfChaosBattleEffect(void);
void ResolveAirknightParshathDrawBattleEffect(void);
void ResolveSasukeSamurai3BattleEffect(void);
void ResolveNeedleBurrowerBattleEffect(void);
void ResolveHyperHammerheadBattleEffect(void);
void ResolveDDWarriorBattleEffect(void);
void ResolveDesKangarooBattleEffect(void);
void ResolveAbsorbingKidFromTheSkyBattleEffect(void);
void ResolveCoffinSellerBattleEffect(void);
void FinishGraveyardDrawBattleResolve(void);

static struct {
  u8 valid;
  u8 isDirect;
  u8 attackerRow;
  u8 attackerCol;
  u8 defenderRow;
  u8 defenderCol;
} sAttackResume APPEND_DATA = {0};

void SaveDrainingShieldAttackResume(void)
{
  u8 row2;
  u8 col2;
  u8 row3;
  u8 col3;

  sAttackResume.valid = TRUE;
  sAttackResume.attackerRow = gTrapEffectData.originRow;
  sAttackResume.attackerCol = gTrapEffectData.originCol;

  if (gTrapEffectData.originRow == gDuelCursor.destY
      && gTrapEffectData.originCol == gDuelCursor.destX
      && gDuelCursor.currentY <= 3) {
    sAttackResume.isDirect = FALSE;
    sAttackResume.defenderRow = gDuelCursor.currentY;
    sAttackResume.defenderCol = gDuelCursor.currentX;
    return;
  }

  row2 = sAI_Command.zone1Position >> 4;
  col2 = sAI_Command.zone1Position & 0xF;
  row3 = sAI_Command.zone2Position >> 4;
  col3 = sAI_Command.zone2Position & 0xF;

  if (row2 == gTrapEffectData.originRow && col2 == gTrapEffectData.originCol
      && row3 <= 3 && col3 < MAX_ZONES_IN_ROW
      && gTurnZones[row3][col3]->id != CARD_NONE) {
    sAttackResume.isDirect = FALSE;
    sAttackResume.defenderRow = row3;
    sAttackResume.defenderCol = col3;
    return;
  }

  sAttackResume.isDirect = TRUE;
}

static u8 FixedColForTurnZone(u8 row, u8 col)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[row][i] == gTurnZones[row][col])
      return i;
  }

  return col;
}

void TryResumeInterruptedAttackAfterDrainingShield(void)
{
  u8 attackerFixedRow;
  u8 attackerFixedCol;
  u8 defenderFixedCol;
  struct DuelCard *attacker;

  if (!sAttackResume.valid)
    return;

  sAttackResume.valid = FALSE;

  if (IsDuelOver() == TRUE)
    return;

  attacker = gTurnZones[sAttackResume.attackerRow][sAttackResume.attackerCol];
  if (attacker->id == CARD_NONE)
    return;

  attackerFixedRow = (WhoseTurn() == DUEL_PLAYER) ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  attackerFixedCol = FixedColForTurnZone(sAttackResume.attackerRow, sAttackResume.attackerCol);

  attacker->isDefending = FALSE;
  attacker->isFaceUp = TRUE;
  attacker->isLocked = TRUE;

  if (!TryPayAttackFieldCosts())
    return;

  if (sAttackResume.isDirect) {
    PerformDirectAttackOrRedirectToEmbodimentOfApophis(attackerFixedCol);
  } else {
    struct DuelCard *defender;

    defender = gTurnZones[sAttackResume.defenderRow][sAttackResume.defenderCol];
    if (defender->id == CARD_NONE)
      return;

    defender->isFaceUp = TRUE;
    defenderFixedCol = FixedColForTurnZone(sAttackResume.defenderRow, sAttackResume.defenderCol);

    if (WhoseTurn() == DUEL_PLAYER)
      SetAttackAction(defenderFixedCol, attackerFixedCol);
    else
      SetAttackAction(attackerFixedCol, defenderFixedCol);
  }

  TryApplyFairyBoxToPendingAction();
  TryApplyMirrorWallToPendingAction();
  TryApplyCatsEarTribeToPendingAction();
  TryApplySpiritRyuToPendingAction();
  HandleAtkAndLifePointsAction();
  DebugRuleset_MarkAttackUsed();
  TheDarkDoor_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
  TryUnlockHayabusaKnightForSecondAttack(attacker);
  TryUnlockMermaidKnightForSecondAttack(attacker);
  TryUnlockTryceEquipForSecondAttack(attacker);
  TryUnlockTyrantDragonForSecondAttack(attacker);
  TryUnlockCyberTwinDragonForSecondAttack(attacker);
  sub_801BC00();
  UpdateAllDuelGfx();
  ResolveTheUnhappyMaidenBattleEffect();
  ResolveVampireBabyBattleEffect();
  ResolveGhostKnightOfJackalBattleEffect();
  ResolveMefistTheInfernalGeneralDiscardBattleEffect();
  ResolveReaperOnTheNightmareDirectDamageEffect();
  ResolveSpiritReaperDiscardBattleEffect();
  ResolveGuardianAngelJoanBattleEffect();
  ResolveRoyalKnightBattleEffect();
  ResolveElementalHeroSteamHealerBattleEffect();
  ResolveLesserFiendBattleEffect();
  ResolveDarkMagicianOfChaosBattleEffect();
  ResolveAirknightParshathDrawBattleEffect();
  ResolveSasukeSamurai3BattleEffect();
  ResolveNeedleBurrowerBattleEffect();
  ResolveHyperHammerheadBattleEffect();
  ResolveDDWarriorBattleEffect();
  ResolveDesKangarooBattleEffect();
  ResolveAbsorbingKidFromTheSkyBattleEffect();
  ResolveCoffinSellerBattleEffect();
  sub_8022080();
  FinishGraveyardDrawBattleResolve();
}
