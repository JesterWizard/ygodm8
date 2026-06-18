#include "global.h"
#include "common-chax.h"
#include "draining_shield.h"
#include "call_of_the_haunted.h"
#include "negate_attack.h"
#include "gravity_bind.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "duel_helpers.h"
#include "sasuke_samurai_2.h"
#include "seven_tools_of_the_bandit.h"
#include "blast_held_by_a_tribute.h"

#define TRAP_NONE 0
#define TRAP_WIDESPREAD_RUIN 1
#define TRAP_HOUSE_OF_ADHESIVE_TAPE 2
#define TRAP_EATGABOON 3
#define TRAP_BEAR_TRAP 4
#define TRAP_INVISIBLE_WIRE 5
#define TRAP_ACID_TRAP_HOLE 6
#define TRAP_GOBLIN_FAN 7
#define TRAP_BAD_REACTION_TO_SIMOCHI 8
#define TRAP_REVERSE_TRAP 9
#define TRAP_FAKE_TRAP 10
#define TRAP_ANTI_RAIGEKI 11
#define TRAP_INFINITE_DISMISSAL 12
#define TRAP_TORRENTIAL_TRIBUTE 13
#define TRAP_AMAZON_ARCHERS 14
#define TRAP_DESTINY_BOARD 15
#define TRAP_SPIRIT_MESSAGE_I 16
#define TRAP_SPIRIT_MESSAGE_N 17
#define TRAP_SPIRIT_MESSAGE_A 18
#define TRAP_SPIRIT_MESSAGE_L 19
#define TRAP_MAGIC_JAMMER 21
#define TRAP_EMBODIMENT_OF_APOPHIS 22
#define TRAP_MAGIC_CYLINDER 23
#define TRAP_DRAINING_SHIELD 24

extern void EffectMagicJammer(void);
extern void EffectSevenToolsOfTheBandit(void);
extern void EffectEmbodimentOfApophis(void);
extern void EffectMagicCylinder(void);

extern void EffectTrapNone(void);
extern void EffectWideSpreadRuin(void);
extern void EffectHouseOfAdhesiveTape(void);
extern void EffectEatgaboon(void);
extern void EffectBearTrap(void);
extern void EffectInvisibleWire(void);
extern void EffectAcidTrapHole(void);
extern void EffectGoblinFan(u16 lp);
extern void EffectBadReactionToSimochi(u16 lp);
extern void EffectReverseTrap(void);
extern void EffectFakeTrap(void);
extern void EffectAntiRaigeki(void);
extern void EffectInfiniteDismissal(void);
extern void EffectTorrentialTribute(void);
extern void EffectAmazonArchers(void);
extern void EffectDestinyBoard(void);
extern void EffectSpiritMessageI(void);
extern void EffectSpiritMessageN(void);
extern void EffectSpiritMessageA(void);
extern void EffectSpiritMessageL(void);

void ActivateTrapEffect(u16 lp);

static void ActivateTrapEffectVanillaBody(u16 lp)
{
  ResetCardEffectTextData();
  SetCardEffectTextType(3);

  switch (gTrapEffectData.trapCardId) {
    case TRAP_NONE:
      EffectTrapNone();
      break;
    case TRAP_WIDESPREAD_RUIN:
      EffectWideSpreadRuin();
      break;
    case TRAP_HOUSE_OF_ADHESIVE_TAPE:
      EffectHouseOfAdhesiveTape();
      break;
    case TRAP_EATGABOON:
      EffectEatgaboon();
      break;
    case TRAP_BEAR_TRAP:
      EffectBearTrap();
      break;
    case TRAP_INVISIBLE_WIRE:
      EffectInvisibleWire();
      break;
    case TRAP_ACID_TRAP_HOLE:
      EffectAcidTrapHole();
      break;
    case TRAP_GOBLIN_FAN:
      EffectGoblinFan(lp);
      break;
    case TRAP_BAD_REACTION_TO_SIMOCHI:
      EffectBadReactionToSimochi(lp);
      break;
    case TRAP_REVERSE_TRAP:
      EffectReverseTrap();
      break;
    case TRAP_FAKE_TRAP:
      EffectFakeTrap();
      break;
    case TRAP_ANTI_RAIGEKI:
      EffectAntiRaigeki();
      break;
    case TRAP_INFINITE_DISMISSAL:
      EffectInfiniteDismissal();
      break;
    case TRAP_TORRENTIAL_TRIBUTE:
      EffectTorrentialTribute();
      break;
    case TRAP_AMAZON_ARCHERS:
      EffectAmazonArchers();
      break;
    case TRAP_DESTINY_BOARD:
      EffectDestinyBoard();
      break;
    case TRAP_SPIRIT_MESSAGE_I:
      EffectSpiritMessageI();
      break;
    case TRAP_SPIRIT_MESSAGE_N:
      EffectSpiritMessageN();
      break;
    case TRAP_SPIRIT_MESSAGE_A:
      EffectSpiritMessageA();
      break;
    case TRAP_SPIRIT_MESSAGE_L:
      EffectSpiritMessageL();
      break;
  }
}

LYN_REPLACE_CHECK(ActivateTrapEffect);
void ActivateTrapEffect__Replacement(u16 lp)
{
  struct DuelCard *respondingZone;

  if (SasukeSamurai2_AreInactiveBackrowTrapsBlocked()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
      SaveDrainingShieldAttackResume();
      TryResumeInterruptedAttackAfterDrainingShield();
    }
    return;
  }

  respondingZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (respondingZone != NULL && Duel_IsCardActivationBlocked(respondingZone->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
      SaveDrainingShieldAttackResume();
      TryResumeInterruptedAttackAfterDrainingShield();
    }
    return;
  }

  if (gTrapEffectData.trapCardId != TRAP_ROYAL_DECREE
      && gTrapEffectData.trapCardId != TRAP_NONE) {
    TryActivateRoyalDecreeOnRespondingTrap();
    respondingZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
    if (respondingZone != NULL
        && Duel_IsCardActivationBlocked(respondingZone->id)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      if (GetTypeGroup(gTrapEffectData.originCardId) == TYPE_GROUP_MONSTER) {
        SaveDrainingShieldAttackResume();
        TryResumeInterruptedAttackAfterDrainingShield();
      }
      return;
    }
  }

  if (gTrapEffectData.trapCardId == TRAP_MAGIC_JAMMER) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectMagicJammer();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_SEVEN_TOOLS_OF_THE_BANDIT) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectSevenToolsOfTheBandit();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_EMBODIMENT_OF_APOPHIS) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectEmbodimentOfApophis();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_MAGIC_CYLINDER) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectMagicCylinder();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_DRAINING_SHIELD) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectDrainingShield();
    TryResumeInterruptedAttackAfterDrainingShield();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_NEGATE_ATTACK) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectNegateAttack();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_CALL_OF_THE_HAUNTED) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectCallOfTheHaunted();
    if (!gHideEffectText) {
      CallOfTheHauntedRequestAiResimulate();
      CallOfTheHauntedUnlockAiAttackerAfterTrap();
    }
    if (!gAiResimulateAfterCallOfTheHaunted)
      TryResumeInterruptedAttackAfterCallOfTheHaunted();
    CallOfTheHauntedShowActivationText();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_GRAVITY_BIND) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectGravityBind();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_IMPERIAL_ORDER) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectImperialOrder();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_ROYAL_DECREE) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectRoyalDecree();
    return;
  }

  if (gTrapEffectData.trapCardId == TRAP_BLAST_HELD_BY_A_TRIBUTE) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    EffectBlastHeldByATribute();
    return;
  }

  ActivateTrapEffectVanillaBody(lp);
}
