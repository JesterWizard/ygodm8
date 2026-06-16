#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "card_passives.h"
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
#include "mefist_the_infernal_general.h"
#include "guardian_angel_joan.h"
#include "airknight_parshath.h"
#include "needle_burrower.h"
#include "absorbing_kid_from_the_sky.h"
#include "reaper_on_the_nightmare.h"
#include "spirit_reaper.h"
#include "hyper_hammerhead.h"
#include "gyaku_gire_panda.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

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
  ApplyReaperOnTheNightmareBattleProtection();
  ApplyPiranhaArmyDoubleDirectDamage();
  ApplyBlueEyesChaosMaxDragonDoublePiercingDamage();
  ApplySpearDragonBattleEffect();
  ApplyMadSwordBeastBattleEffect();
  ApplyDarkDriceratopsBattleEffect();
  ApplyMefistTheInfernalGeneralPiercingBattleEffect();
  ApplyAirknightParshathPiercingBattleEffect();
  ApplyGyakuGirePandaBattleEffect();

  if (sActionData.flags & 1) {
    MarkFamiliarKnightBattleDestruction(
        gFixedZones[sActionData.playerMonsterRow][sActionData.unkA]->id);
    MarkGiantRatBattleDestruction(
        DUEL_PLAYER, gFixedZones[sActionData.playerMonsterRow][sActionData.unkA]->id);
    ClearZoneAndSendMonToGraveyard2(gFixedZones[sActionData.playerMonsterRow][sActionData.unkA], 0);
  }
  if (sActionData.flags & 2) {
    MarkFamiliarKnightBattleDestruction(
        gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16]->id);
    MarkGiantRatBattleDestruction(
        DUEL_OPPONENT, gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16]->id);
    ClearZoneAndSendMonToGraveyard2(gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16], 1);
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
  ApplyAirknightParshathDrawBattleEffect();
  ApplyNeedleBurrowerBattleEffect();
  ApplyAbsorbingKidFromTheSkyBattleEffect();
  ApplyRobbinZombieBattleEffect();
  ApplyYataGarasuBattleEffect();
  ApplyFenrirBattleEffect();
  ApplyHyperHammerheadBattleEffect();

  if ((sActionData.flags & (FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT)) != 0) {
    if (CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_PLAYER].graveyard)
        || CardDefersGraveyardEffectUntilBattleFinish(gDuel.duelistbattleState[DUEL_OPPONENT].graveyard))
      gDeferGraveyardDrawBattleResolve = TRUE;
  }
}
