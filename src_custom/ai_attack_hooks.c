#include "global.h"
#include "common-chax.h"
#include "call_of_the_haunted.h"
#include "constants/card_ids.h"
#include "debug_ruleset.h"
#include "duel.h"
#include "fairy_box.h"
#include "mirror_wall.h"
#include "cyber_barrier_dragon.h"
#include "elemental_hero_core.h"
#include "elemental_hero_sunrise.h"
#include "cats_ear_tribe.h"
#include "spirit_ryu.h"
#include "embodiment_of_apophis.h"
#include "hayabusa_knight.h"
#include "mermaid_knight.h"
#include "twin_swords_of_flashing_light_tryce.h"
#include "tyrant_dragon.h"
#include "cyber_twin_dragon.h"
#include "the_tripper_mercury.h"
#include "chimeratech_overdragon.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "elemental_hero_wildedge.h"
#include "sasuke_samurai.h"
#include "toll.h"
#include "the_dark_door.h"
#include "duel_attack_restrictions.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "black_tyranno.h"
#include "drillago.h"
#include "thunder_nyan_nyan.h"
#include "elemental_hero_mariner.h"
#include "elemental_hero_knospe.h"
#include "elemental_hero_ice_edge.h"
#include "jowls_of_dark_demise.h"
#include "neo_spacian_glow_moss.h"
#include "red_dragon_archfiend.h"
#include "duel_helpers.h"
#include "d_d_warrior.h"
#include "lesser_fiend.h"
#include "dark_magician_of_chaos.h"
#include "sasuke_samurai_2.h"

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

void sub_800E50C(void);
void sub_800E54C(void);
void sub_800E58C(void);
void sub_800E5E4(void);
void sub_800E63C(void);
void sub_800E6B8(void);
void sub_800E734(void);
void sub_800E794(void);
void sub_800E7F4(void);
void sub_800E854(void);
void SetAttackAction(s32, s32);
void SetAttackActionDirectAttack(int);
void HandleAtkAndLifePointsAction(void);
void CheckGraveyardAndLoserFlags(void);
unsigned IsTrapTriggered(void);
void ActivateTrapEffect(u16 lp);

static u8 AiFixedColForZone(struct DuelCard *zone, u8 fixedRow) {
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[fixedRow][i] == zone)
      return i;
  }

  return 0;
}

static void AiPrepareAttacker(struct DuelCard *zone) {
  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  zone->isLocked = TRUE;
}

static void AiSetAttackOriginFromZone(struct DuelCard *attacker) {
  u8 i;
  u8 j;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gTurnZones[i][j] == attacker) {
        gTrapEffectData.originRow = i;
        gTrapEffectData.originCol = j;
        gTrapEffectData.originCardId = attacker->id;
        return;
      }
    }
  }
}

static u8 AiPayAttackTollIfNeeded(void)
{
  if (!TryPayAttackFieldCosts())
    return FALSE;

  if (AttackFieldCostsRequireCoTHResumeSkip())
    MarkCallOfTheHauntedAttackTollPaid();

  return TRUE;
}

static u8 AiTryActivateTrapOnAttack(struct DuelCard *attacker, struct DuelCard *defender)
{
  if (attacker->id == CARD_NONE)
    return FALSE;

  AiSetAttackOriginFromZone(attacker);
  TryActivateEmbodimentOfApophisOnAttack();
  if (TryNegateDeclaredAttackWithCyberBarrierDragon()) {
    PlayMusic(SFX_ATTACK_REBUFFED);
    return TRUE;
  }

  if (SasukeSamurai2_AreInactiveBackrowTrapsBlocked())
    return FALSE;

  if (IsTrapTriggered() != TRUE)
    return FALSE;

  /* ponytail: trap stops the attack; locking here leaves the monster stuck after CoTH */
  attacker->isDefending = FALSE;
  attacker->isFaceUp = TRUE;
  if (defender != NULL)
    defender->isFaceUp = TRUE;

  if (gTrapEffectData.trapCardId == TRAP_CALL_OF_THE_HAUNTED)
    CallOfTheHauntedRequestAiResimulate();

  ActivateTrapEffect(0);
  /* ponytail: non-CoTH traps (Magic Cylinder, Negate Attack) must keep the lock */
  if (gTrapEffectData.trapCardId == TRAP_CALL_OF_THE_HAUNTED)
    CallOfTheHauntedUnlockAiAttackerAfterTrap();
  return TRUE;
}

static void AiTrySetAttackPosition(struct DuelCard *zone)
{
  if (LevelLimitAreaB_CannotUseAttackPosition(zone->id)) {
    LevelLimitAreaB_EnforceOnZone(zone);
    return;
  }

  zone->isDefending = FALSE;
  zone->isFaceUp = TRUE;
  zone->isLocked = TRUE;
}

static void AiAttackDirect(struct DuelCard *attacker) {
  u8 fixedRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  if (!DebugRuleset_AllowDirectAttacks())
    return;

  if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()
      || !Duel_CanMonsterDeclareAttack(attacker)
      || Duel_ForcedAttackBlocksDirect(
          WhoseTurn() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER))
    return;

  if (attacker->id == CARD_NONE)
    return;

  if (ChimeratechOverdragon_BlocksDirectAttack(attacker))
    return;

  if (NumEmptyZonesInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) != MAX_ZONES_IN_ROW
      && !CanJowlsControlledMonsterAttackDirectly(attacker)
      && !CanElementalHeroMarinerAttackDirectly(attacker->id)
      && !CanElementalHeroKnospeAttackDirectly(attacker->id)
      && !CanElementalHeroIceEdgeAttackDirectly(attacker)
      && !CanNeoSpacianGlowMossAttackDirectly(attacker)
      && !CanThunderNyanNyanAttackDirectly(attacker->id))
    return;

  if (!AiPayAttackTollIfNeeded())
    return;

  if (AiTryActivateTrapOnAttack(attacker, NULL))
    return;

  AiPrepareAttacker(attacker);
  AiSetAttackOriginFromZone(attacker);
  TryActivateEmbodimentOfApophisOnAttack();
  MarkMonsterDeclaredAttackThisTurn(attacker);
  TryArmElementalHeroSunriseOnAttackDeclared(attacker, NULL);
  TryShowBlackTyrannoDirectAttackText(attacker->id);
  TryShowDrillagoDirectAttackText(attacker->id);
  TryShowThunderNyanNyanDirectAttackText(attacker->id);
  TryShowElementalHeroMarinerDirectAttackText(attacker->id);
  TryShowElementalHeroKnospeDirectAttackText(attacker->id);
  PerformDirectAttackOrRedirectToEmbodimentOfApophis(AiFixedColForZone(attacker, fixedRow));
  TryApplyFairyBoxToPendingAction();
  TryApplyMirrorWallToPendingAction();
  TryApplyElementalHeroCoreAtkDouble();
  TryApplyCatsEarTribeToPendingAction();
  TryApplySpiritRyuToPendingAction();
  HandleAtkAndLifePointsAction();
  DebugRuleset_MarkAttackUsed();
  TheDarkDoor_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
  ResolveDDWarriorBattleEffect();
  ResolveLesserFiendBattleEffect();
  TryUnlockHayabusaKnightForSecondAttack(attacker);
  TryUnlockMermaidKnightForSecondAttack(attacker);
  TryUnlockTryceEquipForSecondAttack(attacker);
  TryUnlockTyrantDragonForSecondAttack(attacker);
  TryUnlockCyberTwinDragonForSecondAttack(attacker);
  TryUnlockTheTripperMercuryForSecondAttack(attacker);
  TryUnlockChimeratechOverdragonForNextAttack(attacker);
  TryUnlockBlackLusterSoldierEnvoyForSecondAttack(attacker);
  TryUnlockElementalHeroWildedgeForNextAttack(attacker, NULL);
}

static void AiAttackMonster(struct DuelCard *attacker, struct DuelCard *defender) {
  u8 playerCol;
  u8 opponentCol;

  if (!DebugRuleset_CanAttackThisTurn() || !TheDarkDoor_CanAttackThisTurn()
      || !Duel_CanMonsterDeclareAttack(attacker)
      || !Duel_CanAttackMonsterZone(defender)
      || !Duel_MonsterMayBeAttacked(defender))
    return;

  if (attacker->id == CARD_NONE)
    return;

  if (!AiPayAttackTollIfNeeded())
    return;

  if (AiTryActivateTrapOnAttack(attacker, defender))
    return;

  AiPrepareAttacker(attacker);
  RefreshPendingSasukeBattleTarget();
  AiSetAttackOriginFromZone(attacker);
  TryActivateEmbodimentOfApophisOnAttack();
  MarkMonsterDeclaredAttackThisTurn(attacker);
  TryArmElementalHeroSunriseOnAttackDeclared(attacker, defender);

  if (WhoseTurn() == DUEL_PLAYER) {
    playerCol = AiFixedColForZone(attacker, PLAYER_MONSTER_ROW);
    opponentCol = AiFixedColForZone(defender, OPPONENT_MONSTER_ROW);
  } else {
    playerCol = AiFixedColForZone(defender, PLAYER_MONSTER_ROW);
    opponentCol = AiFixedColForZone(attacker, OPPONENT_MONSTER_ROW);
  }

  SetAttackAction(playerCol, opponentCol);
  TryApplyFairyBoxToPendingAction();
  TryApplyMirrorWallToPendingAction();
  TryApplyElementalHeroCoreAtkDouble();
  TryApplyCatsEarTribeToPendingAction();
  TryApplySpiritRyuToPendingAction();
  RunMonsterBattleAction();
  if (defender->id != CARD_NONE)
    defender->isFaceUp = TRUE;
  DebugRuleset_MarkAttackUsed();
  TheDarkDoor_MarkAttackUsed();
  CheckGraveyardAndLoserFlags();
  ResolveDDWarriorBattleEffect();
  ResolveLesserFiendBattleEffect();
  TryUnlockHayabusaKnightForSecondAttack(attacker);
  TryUnlockMermaidKnightForSecondAttack(attacker);
  TryUnlockTryceEquipForSecondAttack(attacker);
  TryUnlockTyrantDragonForSecondAttack(attacker);
  TryUnlockCyberTwinDragonForSecondAttack(attacker);
  TryUnlockTheTripperMercuryForSecondAttack(attacker);
  TryUnlockChimeratechOverdragonForNextAttack(attacker);
  TryUnlockBlackLusterSoldierEnvoyForSecondAttack(attacker);
  TryUnlockElementalHeroWildedgeForNextAttack(attacker, defender);
}

LYN_REPLACE_CHECK(sub_800E50C);
void sub_800E50C__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiTrySetAttackPosition(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E54C);
void sub_800E54C__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiTrySetAttackPosition(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E58C);
void sub_800E58C__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiAttackDirect(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E5E4);
void sub_800E5E4__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  AiAttackDirect(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800E63C);
void sub_800E63C__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  AiAttackMonster(gTurnZones[row2][col2], gTurnZones[row3][col3]);
}

LYN_REPLACE_CHECK(sub_800E6B8);
void sub_800E6B8__Replacement(void) {
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  AiAttackMonster(gTurnZones[row2][col2], gTurnZones[row3][col3]);
}

LYN_REPLACE_CHECK(sub_800E734);
void sub_800E734__Replacement(void) {
  sub_800E58C__Replacement();
}

LYN_REPLACE_CHECK(sub_800E794);
void sub_800E794__Replacement(void) {
  sub_800E5E4__Replacement();
}

LYN_REPLACE_CHECK(sub_800E7F4);
void sub_800E7F4__Replacement(void) {
  sub_800E63C__Replacement();
}

LYN_REPLACE_CHECK(sub_800E854);
void sub_800E854__Replacement(void) {
  sub_800E6B8__Replacement();
}
