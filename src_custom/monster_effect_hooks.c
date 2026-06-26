#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/monster_effects.h"
#include "cannon_soldier.h"
#include "monster_effect_usage.h"
#include "soul_exchange.h"
#include "tribute.h"
#include "great_maju_garzett.h"
#include "maju_garzett.h"
#include "weather_report.h"
#include "berserk_gorilla.h"
#include "level_limit_area_b.h"
#include "vengeful_bog_spirit.h"
#include "sasuke_samurai_2.h"
#include "man_thro_tro.h"
#include "breaker_the_magical_warrior.h"
#include "jowls_of_dark_demise.h"
#include "invader_of_the_throne.h"
#include "possessed_dark_soul.h"
#include "ryu_kishin_clown.h"
#include "nightmare_wheel.h"
#include "dark_dust_spirit.h"
#include "levia_dragon_daedalus.h"
#include "spirit_caller.h"
#include "amazoness_archer.h"
#include "elemental_hero_bubbleman.h"

extern void (*const gMonEffects[])(void);

void ActivateMonsterEffect(void);
void MonsterActionMenu(void);
unsigned char HandlePlayerMonsterAction(void);
void sub_8044570(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
unsigned char CanActivateAmazonessChainMaster(void);
void ActivateAmazonessChainMasterEffect(void);
void ActivateGoddessOfWhimEffect(void);
void ActivateMaskOfDarknessEffect(void);
void ActivatePrincessOfTsurugiEffect(void);
void ActivateFireReaperEffect(void);
unsigned char CanActivateNeedleBall(void);
void ActivateNeedleBallEffect(void);
void ActivateNeedleWormEffect(void);
unsigned char CanActivateKarateMan(void);
void ActivateKarateManEffect(void);
unsigned char CanActivateMonsterTamer(void);
void ActivateMonsterTamerEffect(void);
void ActivateHourglassOfLifeEffect(void);
unsigned char CanActivateDesKoala(void);
void ActivateDesKoalaEffect(void);
unsigned char CanActivateMonsterEffect(void) {
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  switch (gCardInfo.monsterEffect) {
    case MONSTER_EFFECT_INJECTION_FAIRY_LILY:
      return CanActivateInjectionFairyLily();
    case MONSTER_EFFECT_CYBER_STEIN:
      return CanActivateCyberStein();
    case MONSTER_EFFECT_NEEDLE_BALL:
      return CanActivateNeedleBall();
    case MONSTER_EFFECT_AMAZON_CHAIN_MASTER:
      return CanActivateAmazonessChainMaster();
    case MONSTER_EFFECT_PENGUIN_SOLDIER:
      return CanActivatePenguinSoldier();
    case MONSTER_EFFECT_KARATE_MAN:
      return CanActivateKarateMan();
    case MONSTER_EFFECT_KAIBAMAN:
      return CanActivateKaibaman();
    case MONSTER_EFFECT_MONSTER_TAMER:
      return CanActivateMonsterTamer();
    case MONSTER_EFFECT_CANNON_SOLDIER:
      return CanActivateCannonSoldier();
    case MONSTER_EFFECT_DES_KOALA:
      return CanActivateDesKoala();
    case MONSTER_EFFECT_WEATHER_REPORT:
      return CanActivateWeatherReport();
    case MONSTER_EFFECT_THE_AGENT_OF_CREATION_VENUS:
      return CanActivateTheAgentOfCreationVenus();
    case MONSTER_EFFECT_MAGICAL_MERCHANT:
      return CanActivateMagicalMerchant();
    case MONSTER_EFFECT_SASUKE_SAMURAI_2:
      return CanActivateSasukeSamurai2();
    case MONSTER_EFFECT_MAN_THRO_TRO:
      return CanActivateManThroTro();
    case MONSTER_EFFECT_BREAKER_THE_MAGICAL_WARRIOR:
      return CanActivateBreakerTheMagicalWarrior();
    case MONSTER_EFFECT_JOWLS_OF_DARK_DEMISE:
      return CanActivateJowlsOfDarkDemise();
    case MONSTER_EFFECT_POSSESSED_DARK_SOUL:
      return CanActivatePossessedDarkSoul();
    case MONSTER_EFFECT_INVADER_OF_THE_THRONE:
      return CanActivateInvaderOfTheThrone();
    case MONSTER_EFFECT_SPIRIT_CALLER:
      return CanActivateSpiritCaller();
    case MONSTER_EFFECT_RYU_KISHIN_CLOWN:
      return CanActivateRyuKishinClown();
    case MONSTER_EFFECT_DARK_DUST_SPIRIT:
      return CanActivateDarkDustSpirit();
    case MONSTER_EFFECT_LEVIA_DRAGON_DAEDALUS:
      return CanActivateLeviaDragonDaedalus();
    case MONSTER_EFFECT_BUBBLEMAN:
      return CanActivateElementalHeroBubbleman();
    default:
      return TRUE;
  }
}

unsigned char TryActivateSkillDrainAndNegate(void);

LYN_REPLACE_CHECK(ActivateMonsterEffect);
void ActivateMonsterEffect__Replacement(void) {
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (TryActivateSkillDrainAndNegate())
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(2);
  SetCardInfo(gMonEffect.id);
  MarkMonsterEffectUsed(zone);

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_INJECTION_FAIRY_LILY) {
    ActivateInjectionFairyLilyEffect();
    return;
  }

  if (gMonEffect.id == AMAZON_CHAIN_MASTER) {
    ActivateAmazonessChainMasterEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CYBER_JAR) {
    EffectCyberJar();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CYBER_STEIN) {
    EffectCyberStein();
    return;
  }

  if (gMonEffect.id == NEEDLE_BALL) {
    ActivateNeedleBallEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_NEEDLE_WORM) {
    ActivateNeedleWormEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_GODDESS_OF_WHIM) {
    ActivateGoddessOfWhimEffect();
    return;
  }

  if (gMonEffect.id == MASK_OF_DARKNESS) {
    ActivateMaskOfDarknessEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_PRINCESS_OF_TSURUGI) {
    ActivatePrincessOfTsurugiEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_PENGUIN_SOLDIER) {
    ActivatePenguinSoldierEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_KARATE_MAN) {
    ActivateKarateManEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_FIRE_REAPER) {
    ActivateFireReaperEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_COPYCAT) {
    ActivateCopycatEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_KAIBAMAN) {
    ActivateKaibamanEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MONSTER_TAMER) {
    ActivateMonsterTamerEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_CANNON_SOLDIER) {
    ActivateCannonSoldierEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DES_KOALA) {
    ActivateDesKoalaEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_WEATHER_REPORT) {
    ActivateWeatherReportEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_THE_AGENT_OF_CREATION_VENUS) {
    ActivateTheAgentOfCreationVenusEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_STEALTH_BIRD) {
    ActivateStealthBirdEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MAGICAL_MERCHANT) {
    ActivateMagicalMerchantEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_SASUKE_SAMURAI_2) {
    ActivateSasukeSamurai2Effect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MAN_THRO_TRO) {
    ActivateManThroTroEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BREAKER_THE_MAGICAL_WARRIOR) {
    ActivateBreakerTheMagicalWarriorEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DICE_JAR) {
    ActivateDiceJarEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_JOWLS_OF_DARK_DEMISE) {
    ActivateJowlsOfDarkDemiseEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_POSSESSED_DARK_SOUL) {
    ActivatePossessedDarkSoulEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_INVADER_OF_THE_THRONE) {
    ActivateInvaderOfTheThroneEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_SPIRIT_CALLER) {
    ActivateSpiritCallerEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_RYU_KISHIN_CLOWN) {
    ActivateRyuKishinClownEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_DUST_SPIRIT) {
    ActivateDarkDustSpiritEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_LEVIA_DRAGON_DAEDALUS) {
    ActivateLeviaDragonDaedalusEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_BUBBLEMAN) {
    ActivateElementalHeroBubblemanEffect();
    return;
  }

  if (gMonEffect.id == AMAZONESS_ARCHER) {
    ActivateAmazonessArcherEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_HOURGLASS_OF_LIFE) {
    ActivateHourglassOfLifeEffect();
    return;
  }

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_MONSTER_EYE) {
    u8 i;

    for (i = 0; i < MAX_ZONES_IN_ROW; i++)
      if (gTurnHands[INACTIVE_DUELIST][i]->id != CARD_NONE)
        gTurnHands[INACTIVE_DUELIST][i]->isFaceUp = TRUE;

    if (!gHideEffectText) {
      gCardEffectTextData.cardId = gMonEffect.id;
      ActivateCardEffectText();
    }
    return;
  }

  gMonEffects[gCardInfo.monsterEffect]();
}

LYN_REPLACE_CHECK(MonsterActionMenu);
void MonsterActionMenu__Replacement(void) {
  switch (HandlePlayerMonsterAction()) {
    case 1:
      sub_8044570();
      break;
    case 2:
      if (BerserkGorilla_CannotUseDefensePosition(
              gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
        PlayMusic(SFX_FORBIDDEN);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      } else if (NightmareWheel_CannotChangeBattlePosition(
                     gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
        PlayMusic(SFX_FORBIDDEN);
      } else if (!gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked) {
        PlayMusic(SFX_SELECT);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 1;
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
      }
      else {
        PlayMusic(SFX_FORBIDDEN);
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
    case 3:
      if (IsSoulExchangeActive() && gDuelCursor.currentY == PLAYER_MONSTER_ROW) {
        PlayMusic(SFX_FORBIDDEN);
        UpdateDuelGfxExceptField();
        break;
      }
      PlayMusic(SFX_TRIBUTE);
      if (IsSoulExchangeActive() && gDuelCursor.currentY == OPPONENT_MONSTER_ROW) {
        ApplyMonsterTributeFromFixedRow(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], OPPONENT_MONSTER_ROW);
      } else {
        TryCaptureGreatMajuGarzettTributeFromZone(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        TryCaptureMajuGarzettTributeFromZone(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
        AddTributeCredit(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
        ClearZoneAndSendMonToGraveyard2(
            gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], DUEL_PLAYER);
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
    case 4: {
      struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];
      u8 isFaceUp = zone->isFaceUp;

      if (!isFaceUp && NightmareWheel_CannotChangeBattlePosition(zone))
        goto FAILED;

      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked)
        zone->isDefending = 0;
      if (!isFaceUp || zone->id == CANNON_SOLDIER || zone->id == MAN_THRO_TRO
          || zone->id == POSSESSED_DARK_SOUL
          || zone->id == BREAKER_THE_MAGICAL_WARRIOR
          || zone->id == THE_AGENT_OF_CREATION_VENUS
          || zone->id == AMAZONESS_ARCHER
          || SasukeSamurai2_AllowsFaceUpEffectActivation(zone->id)) {
        gMonEffect.id = zone->id;
        SetCardInfo(gMonEffect.id);
        if (gMonEffect.id == NEEDLE_BALL) {
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
          break;
        }
        gMonEffect.row = gDuelCursor.currentY;
        gMonEffect.zone = gDuelCursor.currentX;
        if ((gCardInfo.monsterEffect == MONSTER_EFFECT_NONE && gMonEffect.id != MASK_OF_DARKNESS && gMonEffect.id != NEEDLE_BALL && gMonEffect.id != AMAZONESS_ARCHER) || !CanActivateMonsterEffect()) {
FAILED:
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
        }
        else {
          if (!isFaceUp) {
            zone->isDefending = 0;
            zone->isFaceUp = 1;
            TryVengefulBogSpiritOnFlipSummon(zone);
          }
          if (gCardInfo.monsterEffect != MONSTER_EFFECT_RYU_KISHIN_CLOWN
              && gCardInfo.monsterEffect != MONSTER_EFFECT_DARK_DUST_SPIRIT)
            ActivateMonsterEffect();
          if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
            LockMonsterCardsInRow(4);
          UpdateDuelGfxExceptField();
          if (gCardInfo.monsterEffect == MONSTER_EFFECT_RYU_KISHIN_CLOWN)
            TryActivateRyuKishinClownOnMonsterPlacement(zone);
          if (gCardInfo.monsterEffect == MONSTER_EFFECT_DARK_DUST_SPIRIT)
            TryActivateDarkDustSpiritOnMonsterPlacement(zone);
          if (gDuelCursor.state == DUEL_CURSOR_CANNON_SOLDIER_TARGET
              || gDuelCursor.state == DUEL_CURSOR_MAN_THRO_TRO_TARGET
              || gDuelCursor.state == DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET
              || gDuelCursor.state == DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET
              || gDuelCursor.state == DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET
              || gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE1
              || gDuelCursor.state == DUEL_CURSOR_AMAZONESS_ARCHER_TRIBUTE2)
            break;
          CheckWinConditionExodia();
          if (IsDuelOver() != 1)
            TryActivatingPermanentEffects();
        }
      }
      else
        goto FAILED;
      break;
    }
    case 5:
      if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending) {
        if (LevelLimitAreaB_CannotUseAttackPosition(
                gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id)) {
          PlayMusic(SFX_FORBIDDEN);
        } else if (NightmareWheel_CannotChangeBattlePosition(
                       gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX])) {
          PlayMusic(SFX_FORBIDDEN);
        } else if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked) {
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
        }
      }
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
  }
}
