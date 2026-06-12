#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "cost_down.h"
#include "custom_field_spell.h"

extern void (*const gSpellEffects[])(void);
extern void EffectCardOfDemise(void);
extern void EffectCardOfSanctity(void);
extern void EffectJamBreedingMachine(void);
extern void EffectShieldAndSword(void);
extern void EffectSwordsOfRevealingLight(void);
extern void EffectChainEnergy(void);
extern void EffectExchange(void);
extern void EffectMagePower(void);
extern void EffectUnitedWeStand(void);
extern void EffectWaveMotionCannon(void);
extern void EffectPyramidOfLight(void);
extern void EffectSoulExchange(void);
extern void EffectMysticalSpaceTyphoon(void);
extern void EffectDoubleSummon(void);
extern void EffectCostDown(void);
extern void EffectAncientRules(void);
extern void EffectSagesStone(void);
extern void EffectDarkMagicCurtain(void);
extern void EffectRiryoku(void);
extern void EffectGuardianTreasure(void);
extern void EffectGoblinThief(void);
extern void EffectDelinquentDuo(void);
extern void EffectMeteorOfDestruction(void);
extern void EffectBlockAttack(void);
extern void EffectToll(void);
extern void EffectSkullInvitation(void);
extern void EffectRainOfMercy(void);
extern void EffectUpstartGoblin(void);
extern void EffectReload(void);
extern void EffectThousandEnergy(void);
extern void EffectTheDarkDoor(void);
void ApplyMahaVailoEquipBonus(struct DuelCard* zone);

void ActivateSpellEffect(void);
void ActivateTrapEffect(u16 lp);
unsigned IsTrapTriggered(void);
u8 TryPayChainEnergyCost(void);
unsigned char IsSpellCancellerSpellLockActive(void);

static u8 SpellHandlesOwnTrapResponse(u16 spellId, u8 spellEffect)
{
  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP)
    return TRUE;

  switch (spellId) {
    case MAGE_POWER:
    case UNITED_WE_STAND:
    case MYSTICAL_SPACE_TYPHOON:
    case RIRYOKU:
    case WAVE_MOTION_CANNON:
    case GOBLIN_THIEF:
    case DELINQUENT_DUO:
    case METEOR_OF_DESTRUCTION:
    case BLOCK_ATTACK:
    case RAIN_OF_MERCY:
    case UPSTART_GOBLIN:
      return TRUE;
    default:
      break;
  }

  switch (spellEffect) {
    case SPELL_EFFECT_MOOYAN_CURRY:
    case SPELL_EFFECT_RED_MEDICINE:
    case SPELL_EFFECT_GOBLINS_SECRET_REMEDY:
    case SPELL_EFFECT_SOUL_OF_THE_PURE:
    case SPELL_EFFECT_DIAN_KETO_THE_CURE_MASTER:
    case SPELL_EFFECT_SPARKS:
    case SPELL_EFFECT_HINOTAMA:
    case SPELL_EFFECT_FINAL_FLAME:
    case SPELL_EFFECT_OOKAZI:
    case SPELL_EFFECT_TREMENDOUS_FIRE:
    case SPELL_EFFECT_DARK_HOLE:
    case SPELL_EFFECT_RAIGEKI:
      return TRUE;
    default:
      return FALSE;
  }
}

static u8 TryResolveSpellActivationThroughTraps(u16 spellId)
{
  u8 spellRow;
  u8 spellCol;
  struct DuelCard *spellZone;

  if (GetTypeGroup(spellId) != TYPE_GROUP_SPELL)
    return TRUE;

  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP) {
    spellRow = gSpellEffectData.row2;
    spellCol = gSpellEffectData.col2;
  } else {
    spellRow = gSpellEffectData.row1;
    spellCol = gSpellEffectData.col1;
  }

  spellZone = NULL;
  if (spellRow <= PLAYER_HAND && spellCol < MAX_ZONES_IN_ROW)
    spellZone = gFixedZones[spellRow][spellCol];
  else if (spellRow < 5 && spellCol < MAX_ZONES_IN_ROW)
    spellZone = gTurnZones[spellRow][spellCol];

  gTrapEffectData.originRow = spellRow;
  gTrapEffectData.originCol = spellCol;
  gTrapEffectData.originCardId = spellZone != NULL ? spellZone->id : CARD_NONE;

  if (IsTrapTriggered() != TRUE || gHideEffectText)
    return TRUE;

  ActivateTrapEffect(0);
  return FALSE;
}

LYN_REPLACE_CHECK(ActivateSpellEffect);
void ActivateSpellEffect__Replacement(void)
{
  if (gSpellEffectData.row1 == ACTIVE_DUELIST_HAND) {
    if (!TryPayChainEnergyCost())
      return;
  }

  if (IsSpellCancellerSpellLockActive()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(1);
  SetCardInfo(gSpellEffectData.id);

  if (!SpellHandlesOwnTrapResponse(gSpellEffectData.id, gCardInfo.spellEffect)) {
    if (!TryResolveSpellActivationThroughTraps(gSpellEffectData.id))
      return;
  }

  if (TryActivateCustomFieldSpell(gSpellEffectData.id))
    return;

  if (TryActivateVanillaFieldSpell(gSpellEffectData.id, gCardInfo.spellEffect))
    return;

  if (gCardInfo.spellEffect >= SPELL_EFFECT_FOREST
      && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI) {
    gSpellEffects[gCardInfo.spellEffect]();
    return;
  }

  switch (gSpellEffectData.id) {
    case CARD_OF_DEMISE:
      EffectCardOfDemise();
      return;
    case CARD_OF_SANCTITY:
      EffectCardOfSanctity();
      return;
    case JAM_BREEDING_MACHINE:
      EffectJamBreedingMachine();
      return;
    case SHIELD_AND_SWORD:
      EffectShieldAndSword();
      return;
    case SWORDS_OF_REVEALING_LIGHT:
      EffectSwordsOfRevealingLight();
      return;
    case CHAIN_ENERGY:
      EffectChainEnergy();
      return;
    case TOLL:
      EffectToll();
      return;
    case SKULL_INVITATION:
      EffectSkullInvitation();
      return;
    case RAIN_OF_MERCY:
      EffectRainOfMercy();
      return;
    case UPSTART_GOBLIN:
      EffectUpstartGoblin();
      return;
    case RELOAD:
      EffectReload();
      return;
    case WAVE_MOTION_CANNON:
      EffectWaveMotionCannon();
      return;
    case PYRAMID_OF_LIGHT:
      EffectPyramidOfLight();
      return;
    case SOUL_EXCHANGE:
      EffectSoulExchange();
      return;
    case MYSTICAL_SPACE_TYPHOON:
      EffectMysticalSpaceTyphoon();
      return;
    case DOUBLE_SUMMON:
      EffectDoubleSummon();
      return;
    case COST_DOWN:
      EffectCostDown();
      return;
    case ANCIENT_RULES:
      EffectAncientRules();
      return;
    case SAGES_STONE:
      EffectSagesStone();
      return;
    case DARK_MAGIC_CURTAIN:
      EffectDarkMagicCurtain();
      return;
    case RIRYOKU:
      EffectRiryoku();
      return;
    case GUARDIAN_TREASURE:
      EffectGuardianTreasure();
      return;
    case GOBLIN_THIEF:
      EffectGoblinThief();
      return;
    case DELINQUENT_DUO:
      EffectDelinquentDuo();
      return;
    case METEOR_OF_DESTRUCTION:
      EffectMeteorOfDestruction();
      return;
    case BLOCK_ATTACK:
      EffectBlockAttack();
      return;
    case EXCHANGE:
      EffectExchange();
      return;
    case MAGE_POWER:
      EffectMagePower();
      return;
    case UNITED_WE_STAND:
      EffectUnitedWeStand();
      return;
    case THOUSAND_ENERGY:
      EffectThousandEnergy();
      return;
    case THE_DARK_DOOR:
      EffectTheDarkDoor();
      return;
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP
          && gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id == CARD_NONE)
        ApplyMahaVailoEquipBonus(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
      return;
  }
}
