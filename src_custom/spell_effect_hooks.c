#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "cost_down.h"
#include "curse_of_darkness.h"
#include "custom_field_spell.h"
#include "soul_taker.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "jar_robber.h"
#include "spirit_of_the_pot_of_greed.h"
#include "duel_helpers.h"
#include "effect_system.h"
#include "world_suppression.h"
#include "kishido_spirit.h"
#include "ring_of_destruction.h"
#include "dust_tornado.h"
#include "spell_economics.h"
#include "monster_reborn.h"
#include "generated/spell_effect_dispatch_decls.inc"
void ApplyMahaVailoEquipBonus(struct DuelCard* zone);
extern const u8 gCardSelectableOnce_Hook[];

void ActivateSpellEffect(void);
void ActivateTrapEffect(u16 lp);
unsigned IsTrapTriggered(void);
u8 TryPayChainEnergyCost(void);
u8 TryMaryokutaiSpellCounter(void);

static void SetupSpellTrapOrigin(void)
{
  u8 spellRow;
  u8 spellCol;

  if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP) {
    spellRow = gSpellEffectData.row2;
    spellCol = gSpellEffectData.col2;
  } else {
    spellRow = gSpellEffectData.row1;
    spellCol = gSpellEffectData.col1;
  }

  gTrapEffectData.originRow = spellRow;
  gTrapEffectData.originCol = spellCol;
  gTrapEffectData.originCardId = gSpellEffectData.id;
}

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
    case CONFISCATION:
    case METEOR_OF_DESTRUCTION:
    case BLOCK_ATTACK:
    case BOOK_OF_MOON:
    case H_HEATED_HEART:
    case E_EMERGENCY_CALL:
    case BOOK_OF_TAIYOU:
    case DE_FUSION:
    case DIFFUSION_WAVE_MOTION:
    case AUTONOMOUS_ACTION_UNIT:
    case PREMATURE_BURIAL:
    case SOUL_TAKER:
    case CREATURE_SWAP:
    case THUNDER_CRASH:
    case RAIN_OF_MERCY:
    case UPSTART_GOBLIN:
    case R_RIGHTEOUS_JUSTICE:
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
  return Duel_TryResolveSpellThroughTraps(spellId, NULL) != DUEL_ACTION_BLOCKED;
}

LYN_REPLACE_CHECK(ActivateSpellEffect);
static void ActivateSpellEffect__Body(void)
{
  if (gSpellEffectData.row1 == ACTIVE_DUELIST_HAND) {
    if (!TryPayChainEnergyCost())
      return;
  }

  ResetCardEffectTextData();
  SetCardEffectTextType(1);
  SetCardInfo(gSpellEffectData.id);
  SetupSpellTrapOrigin();

  if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (gSpellEffectData.id == MONSTER_REBORN && !CanActivateMonsterReborn()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  TryActivateImperialOrderOnSpellChain();

  if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (GetTypeGroup(gSpellEffectData.id) == TYPE_GROUP_TRAP) {
    TryActivateRoyalDecreeOnTrapChain();
    if (Duel_IsCardActivationBlocked(gSpellEffectData.id)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }
    if (Duel_TryResolveTrapThroughTraps(gSpellEffectData.id) == DUEL_ACTION_BLOCKED)
      return;
  }

  if (TryJarRobberPotOfGreedCounter())
    return;

  if (TryMaryokutaiSpellCounter())
    return;

  if (!SpellHandlesOwnTrapResponse(gSpellEffectData.id, gCardInfo.spellEffect)) {
    if (!TryResolveSpellActivationThroughTraps(gSpellEffectData.id))
      return;
  }

  TryApplyCurseOfDarknessSpellDamage();
  if (IsDuelOver() == TRUE)
    return;

  if (IsWorldSuppressionNegatingFieldSpell(gSpellEffectData.id)) {
    struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

    Duel_ShowEffectText(gSpellEffectData.id);
    if (zone != NULL)
      Duel_DestroyZone(zone, ACTIVE_DUELIST, TRUE);
    return;
  }

  if (gCardSelectableOnce_Hook[gSpellEffectData.id] && gSpellEffectData.row1 == ACTIVE_DUELIST_HAND) {
    u8 controllerBackrow = (WhoseTurn() == DUEL_PLAYER) ? PLAYER_BACKROW : OPPONENT_BACKROW;
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      struct DuelCard *zone = gFixedZones[controllerBackrow][i];
      if (zone != NULL && zone->id == gSpellEffectData.id && zone->isFaceUp == TRUE) {
        if (!gHideEffectText)
          PlayMusic(SFX_FORBIDDEN);
        return;
      }
    }
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

  if (EffectDispatch_TryActivate(gSpellEffectData.id, EFFECT_KIND_SPELL) == EFFECT_DISPATCH_HANDLED)
    return;

  switch (gSpellEffectData.id) {
#include "generated/spell_effect_dispatch_cases.inc"
    default:
      gSpellEffects[gCardInfo.spellEffect]();
      if (GetSpellType(gSpellEffectData.id) == SPELL_TYPE_EQUIP
          && gTurnZones[gSpellEffectData.row2][gSpellEffectData.col2]->id == CARD_NONE)
        ApplyMahaVailoEquipBonus(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
      return;
  }
}

void ActivateSpellEffect__Replacement(void)
{
  Duel_BeginSpellEffectResolve();
  ActivateSpellEffect__Body();
  Duel_EndSpellEffectResolve();
  Duel_RefreshMonsterStatOverlays();
}
