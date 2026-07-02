#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "card_passives.h"
#include "duel_helpers.h"
#include "card.h"
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
#include "gyaku_gire_panda.h"
#include "sasuke_samurai_3.h"
#include "d_d_warrior.h"
#include "des_kangaroo.h"
#include "big_bang_shot.h"
#include "cyber_end_dragon.h"
#include "elemental_hero_bladedge.h"
#include "elemental_hero_knospe.h"
#include "harpie_lady_2.h"
#include "harpie_lady_3.h"
#include "constants/card_ids.h"
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
  Duel_ApplyBattleDestroyProtection();
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
  ApplyBigBangShotPiercingBattleEffect();
  ApplyGyakuGirePandaBattleEffect();
  ApplyDDWarriorBattleEffect();
  ApplyLesserFiendBattleEffect();
  ApplyDarkMagicianOfChaosBattleEffect();
  ApplyDesKangarooBattleEffect();

  Duel_RemapMutualDestroyBattleAnim(playerGraveyardDestroy, opponentGraveyardDestroy);

  if (sActionData.flags & 1) {
    struct DuelCard *zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];

    /* ponytail: expanded graveyard keeps every push; skip if zone already cleared. */
    if (zone != NULL && zone->id != CARD_NONE
        && !DarkMagicianOfChaosBattleZoneIsPendingBanish(sActionData.playerMonsterRow,
                                                         sActionData.unkA)) {
      MarkFamiliarKnightBattleDestruction(zone->id);
      MarkGiantRatBattleDestruction(DUEL_PLAYER, zone->id);
      ClearZoneAndSendMonToGraveyard2(zone, 0);
    }
  }
  if (sActionData.flags & 2) {
    struct DuelCard *zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];

    if (zone != NULL && zone->id != CARD_NONE
        && !DarkMagicianOfChaosBattleZoneIsPendingBanish(sActionData.opponentMonsterRow,
                                                         sActionData.unk16)) {
      MarkFamiliarKnightBattleDestruction(zone->id);
      MarkGiantRatBattleDestruction(DUEL_OPPONENT, zone->id);
      ClearZoneAndSendMonToGraveyard2(zone, 1);
    }
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
  ApplyRoyalKnightBattleEffect();
  ApplyElementalHeroSteamHealerBattleEffect();
  ApplyElementalHeroFlameWingmanBattleEffect();
  ApplyElementalHeroKnospeBattleEffect();
  ApplyGhostKnightOfJackalBattleEffect();
  ApplyAirknightParshathDrawBattleEffect();
  ApplyNeedleBurrowerBattleEffect();
  ApplyAbsorbingKidFromTheSkyBattleEffect();
  ApplyRobbinZombieBattleEffect();
  ApplyYataGarasuBattleEffect();
  ApplyFenrirBattleEffect();
  ApplyHyperHammerheadBattleEffect();
  ApplySasukeSamurai3BattleEffect();
  ApplyHarpieLady2FlipNegation();
  ApplyHarpieLady3AttackLock();

  if ((sActionData.flags & (FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT)) != 0) {
    if (CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_PLAYER].graveyard)
        || CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_OPPONENT].graveyard))
      gDeferGraveyardDrawBattleResolve = TRUE;
  }
}