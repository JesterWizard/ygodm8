#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "card_passives.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "card.h"
#include "elemental_hero_flash.h"
#include "familiar_knight.h"
#include "giant_rat.h"
#include "graveyard_effects.h"
#include "the_unhappy_maiden.h"
#include "spear_dragon.h"
#include "mad_sword_beast.h"
#include "dark_driceratops.h"
#include "robbin_goblin.h"
#include "robbin_zombie.h"
#include "yata_garasu.h"
#include "fenrir.h"
#include "kaiser_glider.h"
#include "piranha_army.h"
#include "vampire_baby.h"
#include "ghost_knight_of_jackal.h"
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "light_barrier.h"
#include "royal_knight.h"
#include "elemental_hero_steam_healer.h"
#include "elemental_hero_flame_wingman.h"
#include "lesser_fiend.h"
#include "dark_magician_of_chaos.h"
#include "airknight_parshath.h"
#include "needle_burrower.h"
#include "absorbing_kid_from_the_sky.h"
#include "reaper_on_the_nightmare.h"
#include "spirit_reaper.h"
#include "hyper_hammerhead.h"
#include "neo_spacian_grand_mole.h"
#include "lightning_warrior.h"
#include "neo_spacian_glow_moss.h"
#include "neo_spacian_twinkle_moss.h"
#include "reptilianne_gorgon.h"
#include "don_zaloog.h"
#include "red_dragon_archfiend.h"
#include "reptilianne_scylla.h"
#include "gyaku_gire_panda.h"
#include "sasuke_samurai_3.h"
#include "d_d_warrior.h"
#include "des_kangaroo.h"
#include "des_counterblow.h"
#include "continuous_destruction_punch.h"
#include "amazoness_heirloom.h"
#include "ancient_gear_fist.h"
#include "double_tool_c_and_d.h"
#include "dragon_s_rage.h"
#include "attack_pheromones.h"
#include "backup_squad.h"
#include "berserker_soul.h"
#include "bubble_blaster.h"
#include "chicken_game.h"
#include "clock_tower_prison.h"
#include "tornado_wall.h"
#include "big_bang_shot.h"
#include "h_heated_heart.h"
#include "cyber_end_dragon.h"
#include "elemental_hero_bladedge.h"
#include "elemental_hero_plasma_vice.h"
#include "elemental_hero_knospe.h"
#include "elemental_hero_poison_rose.h"
#include "elemental_hero_voltic.h"
#include "elemental_hero_core.h"
#include "the_supremacy_sun.h"
#include "elemental_hero_ice_edge.h"
#include "harpie_lady_2.h"
#include "harpie_lady_3.h"
#include "hamon_lord_of_striking_thunder.h"
#include "constants/card_ids.h"
#include "spell_effects.h"
#include "yubel.h"
#include "custom_field_spell.h"
#include "constants/custom_field_spells.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

void SetCardInfo(u16 id);

struct StoneUnk2023E80 {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct StoneUnk2023E80 sActionData;

void ApplyShinatoKingOfAHigherPlaneBattleEffect(void);
void ApplyObnoxiousCelticGuardianBattleProtection(void);
void ApplyKaiserGliderBattleProtection(void);

static void ApplySanctuaryInTheSkyBattleDamageProtection(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (gActiveCustomFieldSpellId != CUSTOM_FIELD_SPELL_SANCTUARY_IN_THE_SKY)
    return;
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (playerDamage > 0 && sActionData.playerCardId != CARD_NONE) {
    SetCardInfo(sActionData.playerCardId);
    if (gCardInfo.type == TYPE_FAIRY) {
      gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
      gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
      if (opponentDamage == 0 && playerDamage >= gDuelLifePoints[DUEL_OPPONENT])
        sActionData.flags &= ~FLAG_LOSER_PLAYER;
    }
  }

  if (opponentDamage > 0 && sActionData.opponentCardId != CARD_NONE) {
    SetCardInfo(sActionData.opponentCardId);
    if (gCardInfo.type == TYPE_FAIRY) {
      gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
      gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
      if (playerDamage == 0 && opponentDamage >= gDuelLifePoints[DUEL_PLAYER])
        sActionData.flags &= ~FLAG_LOSER_OPPONENT;
    }
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyAmazonessSwordsWomanBattleDamageRedirect(void) {
  u16 playerDamage;
  u16 opponentDamage;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (sActionData.playerCardId == AMAZON_SWORD_WOMAN && playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];

    if (gDuelLifePoints[DUEL_OPPONENT] <= playerDamage) {
      gDuelLifePoints[DUEL_OPPONENT] = 0;
      sActionData.flags |= FLAG_LOSER_OPPONENT;
    }
    else {
      gDuelLifePoints[DUEL_OPPONENT] -= playerDamage;
    }
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= ~FLAG_LOSER_PLAYER;
  }
  else if (sActionData.opponentCardId == AMAZON_SWORD_WOMAN && opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];

    if (gDuelLifePoints[DUEL_PLAYER] <= opponentDamage) {
      gDuelLifePoints[DUEL_PLAYER] = 0;
      sActionData.flags |= FLAG_LOSER_PLAYER;
    }
    else {
      gDuelLifePoints[DUEL_PLAYER] -= opponentDamage;
    }
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= ~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

LYN_REPLACE_CHECK(CheckGraveyardAndLoserFlags);
void CheckGraveyardAndLoserFlags__Replacement(void) {
  u16 damage;
  u8 playerGraveyardDestroy;
  u8 opponentGraveyardDestroy;

  ApplySanctuaryInTheSkyBattleDamageProtection();
  ApplyAmazonessSwordsWomanBattleDamageRedirect();
  ApplyYubelBattleEffects();

  if (sActionData.playerCardId == STONE_STATUE_OF_THE_AZTECS && sActionData.id == 5) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage > 0) {
      if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
        gDuelLifePoints[DUEL_OPPONENT] = 0;
        sActionData.flags |= 16;
      } else {
        gDuelLifePoints[DUEL_OPPONENT] -= damage;
      }
      gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    }
  }

  if (sActionData.opponentCardId == STONE_STATUE_OF_THE_AZTECS && sActionData.id == 2) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage > 0) {
      if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
        gDuelLifePoints[DUEL_PLAYER] = 0;
        sActionData.flags |= 4;
      } else {
        gDuelLifePoints[DUEL_PLAYER] -= damage;
      }
      gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    }
  }

  ApplyShinatoKingOfAHigherPlaneBattleEffect();
  ApplyObnoxiousCelticGuardianBattleProtection();
  ApplyKaiserGliderBattleProtection();
  ApplyAmazonessHeirloomBattleProtection();
  ApplyBubbleBlasterBattleProtection();
  Duel_ApplyBattleDestroyProtection();
  if (sActionData.flags & FLAG_GRAVEYARD_PLAYER) {
    struct DuelCard *zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];

    if (MoltingEscape_PreventsBattleDestruction(zone)) {
      MoltingEscape_ApplyBattleProtection(zone);
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_PLAYER;
    } else if (GladiatorBeastsBattleManica_PreventsBattleDestruction(zone)) {
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_PLAYER;
    }
  }
  if (sActionData.flags & FLAG_GRAVEYARD_OPPONENT) {
    struct DuelCard *zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

    if (MoltingEscape_PreventsBattleDestruction(zone)) {
      MoltingEscape_ApplyBattleProtection(zone);
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_OPPONENT;
    } else if (GladiatorBeastsBattleManica_PreventsBattleDestruction(zone)) {
      sActionData.flags &= (u8)~FLAG_GRAVEYARD_OPPONENT;
    }
  }
  playerGraveyardDestroy = (sActionData.flags & FLAG_GRAVEYARD_PLAYER) != 0;
  opponentGraveyardDestroy = (sActionData.flags & FLAG_GRAVEYARD_OPPONENT) != 0;
  ApplyPiranhaArmyDoubleDirectDamage();
  ApplyBlueEyesChaosMaxDragonDoublePiercingDamage();
  ApplySpearDragonBattleEffect();
  ApplyMadSwordBeastBattleEffect();
  ApplyDarkDriceratopsBattleEffect();
  ApplyMefistTheInfernalGeneralPiercingBattleEffect();
  ApplyAirknightParshathPiercingBattleEffect();
  ApplyCyberEndDragonPiercingBattleEffect();
  ApplyElementalHeroBladedgePiercingBattleEffect();
  ApplyElementalHeroPlasmaVicePiercingBattleEffect();
  ApplyBigBangShotPiercingBattleEffect();
  ApplyHHeatedHeartPiercingBattleEffect();
  ApplyDragonsRagePiercingBattleEffect();
  ApplyGyakuGirePandaBattleEffect();
  ApplyDDWarriorBattleEffect();
  ApplyLesserFiendBattleEffect();
  ApplyDarkMagicianOfChaosBattleEffect();
  ApplyDesKangarooBattleEffect();
  ApplyContinuousDestructionPunchBattleEffect();
  ApplyAmazonessHeirloomBattleEffect();
  ApplyAncientGearFistBattleEffect();
  ApplyDoubleToolCAndDBattleEffect();
  ApplyAttackPheromonesBattleEffect();

  {
    s32 playerDmg =
        (s32)gUnk2023EA0.unk0[0].initialLifePoints - (s32)gDuelLifePoints[DUEL_PLAYER];
    s32 opponentDmg =
        (s32)gUnk2023EA0.unk0[1].initialLifePoints - (s32)gDuelLifePoints[DUEL_OPPONENT];

    if (playerDmg > 0) {
      if (ChickenGame_ShouldBlockBattleDamage(DUEL_PLAYER)
          || ClockTowerPrison_ShouldBlockBattleDamage(DUEL_PLAYER)
          || TornadoWall_ShouldBlockBattleDamage(DUEL_PLAYER)) {
        gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
        gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
        sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
      } else {
        ApplyBackupSquadAfterDamage(playerDmg, DUEL_PLAYER);
        if (sActionData.playerCardId == CARD_NONE) {
          BerserkerSoul_OnDirectDamage(playerDmg);
          TryApplyDesCounterblowAfterDirectDamage(DUEL_PLAYER);
        }
      }
    }
    if (opponentDmg > 0) {
      if (ChickenGame_ShouldBlockBattleDamage(DUEL_OPPONENT)
          || ClockTowerPrison_ShouldBlockBattleDamage(DUEL_OPPONENT)
          || TornadoWall_ShouldBlockBattleDamage(DUEL_OPPONENT)) {
        gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
        gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
        sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
      } else {
        ApplyBackupSquadAfterDamage(opponentDmg, DUEL_OPPONENT);
        if (sActionData.opponentCardId == CARD_NONE) {
          BerserkerSoul_OnDirectDamage(opponentDmg);
          TryApplyDesCounterblowAfterDirectDamage(DUEL_OPPONENT);
        }
      }
    }
  }

  Duel_RemapMutualDestroyBattleAnim(playerGraveyardDestroy, opponentGraveyardDestroy);

  {
    u8 fieldChanged = FALSE;

  if (sActionData.flags & 1) {
    struct DuelCard *zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];

    /* ponytail: expanded graveyard keeps every push; skip if zone already cleared. */
    if (zone != NULL && zone->id != CARD_NONE
        && !DarkMagicianOfChaosBattleZoneIsPendingBanish(sActionData.playerMonsterRow,
                                                         sActionData.unkA)) {
      if (CardDefersGraveyardEffectUntilBattleFinish(zone->id))
        gDeferGraveyardDrawBattleResolve = TRUE;
      MarkFamiliarKnightBattleDestruction(zone->id);
      MarkElementalHeroFlashBattleDestruction(zone->id);
      MarkGiantRatBattleDestruction(DUEL_PLAYER, zone->id);
      MarkElementalHeroCoreDestroyedFromField(zone);
      MarkTheSupremacySunDestroyedFromField(zone);
      EffectEvent_EmitSimple(EFFECT_EVENT_ON_BATTLE_DESTROY, zone->id, zone);
      EffectEvent_EmitSimple(EFFECT_EVENT_ON_LEAVE_FIELD, zone->id, zone);
      ClearZoneAndSendMonToGraveyard2(zone, 0);
      fieldChanged = TRUE;
    }
  }
  if (sActionData.flags & 2) {
    struct DuelCard *zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

    if (zone != NULL && zone->id != CARD_NONE
        && !DarkMagicianOfChaosBattleZoneIsPendingBanish(sActionData.opponentMonsterRow,
                                                         sActionData.unk16)) {
      if (CardDefersGraveyardEffectUntilBattleFinish(zone->id))
        gDeferGraveyardDrawBattleResolve = TRUE;
      MarkFamiliarKnightBattleDestruction(zone->id);
      MarkElementalHeroFlashBattleDestruction(zone->id);
      MarkGiantRatBattleDestruction(DUEL_OPPONENT, zone->id);
      MarkElementalHeroCoreDestroyedFromField(zone);
      MarkTheSupremacySunDestroyedFromField(zone);
      EffectEvent_EmitSimple(EFFECT_EVENT_ON_BATTLE_DESTROY, zone->id, zone);
      EffectEvent_EmitSimple(EFFECT_EVENT_ON_LEAVE_FIELD, zone->id, zone);
      ClearZoneAndSendMonToGraveyard2(zone, 1);
      fieldChanged = TRUE;
    }
  }

  if (fieldChanged)
    EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);
  }

  MarkVampireBabyBattleDestruction(
      sActionData.playerCardId, sActionData.opponentCardId, sActionData.flags);
  if (sActionData.flags & 4)
    DeclareLoser(0);
  if (sActionData.flags & 16)
    DeclareLoser(1);

  ApplyTheUnhappyMaidenBattleEffect();
  ApplyRobbinGoblinBattleEffect();
  ApplyReaperOnTheNightmareDirectDamageEffect();
  ApplySpiritReaperDiscardBattleEffect();
  ApplyMefistTheInfernalGeneralDiscardBattleEffect();
  ApplyGuardianAngelJoanBattleEffect();
  ApplyLightBarrierBattleEffect();
  ApplyRoyalKnightBattleEffect();
  ApplyElementalHeroSteamHealerBattleEffect();
  ApplyElementalHeroFlameWingmanBattleEffect();
  ApplyElementalHeroKnospeBattleEffect();
  ApplyElementalHeroPoisonRoseBattleEffect();
  ApplyElementalHeroVolticBattleEffect();
  ApplyElementalHeroCoreBattleEffect();
  ApplyElementalHeroIceEdgeBattleEffect();
  ApplyGhostKnightOfJackalBattleEffect();
  ApplyAirknightParshathDrawBattleEffect();
  ApplyNeedleBurrowerBattleEffect();
  ApplyAbsorbingKidFromTheSkyBattleEffect();
  ApplyRobbinZombieBattleEffect();
  ApplyYataGarasuBattleEffect();
  ApplyFenrirBattleEffect();
  ApplyHyperHammerheadBattleEffect();
  ApplyNeoSpacianGrandMoleBattleEffect();
  ApplyLightningWarriorBattleEffect();
  ApplyNeoSpacianGlowMossBattleEffect();
  ApplyNeoSpacianTwinkleMossBattleEffect();
  ApplyReptilianneGorgonBattleEffect();
  ApplyDonZaloogBattleEffect();
  ApplyRedDragonArchfiendBattleEffect();
  ApplyReptilianneScyllaBattleEffect();
  ApplySasukeSamurai3BattleEffect();
  ApplyHarpieLady2FlipNegation();
  ApplyHarpieLady3AttackLock();
  ApplyHamonLordOfStrikingThunderBattleEffect();

  if ((sActionData.flags & (FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT)) != 0) {
    if (CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_PLAYER].graveyard)
        || CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_OPPONENT].graveyard))
      gDeferGraveyardDrawBattleResolve = TRUE;
  }
}
/* Light End Dragon converted to activated effect in activated_effects/light_end_dragon.c */