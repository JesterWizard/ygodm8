#include "global.h"
#include "common-chax.h"
#include "constants/monster_effects.h"

extern void (*const gMonEffects[])(void);

void ActivateMonsterEffect(void);
void MonsterActionMenu(void);
unsigned char HandlePlayerMonsterAction(void);
void sub_8044570(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);
void ActivateGoddessOfWhimEffect(void);
void ActivateMaskOfDarknessEffect(void);
void ActivatePrincessOfTsurugiEffect(void);
unsigned char CanActivateNeedleBall(void);
void ActivateNeedleBallEffect(void);
void ActivateNeedleWormEffect(void);

unsigned char CanActivateMonsterEffect(void) {
  switch (gCardInfo.monsterEffect) {
    case MONSTER_EFFECT_INJECTION_FAIRY_LILY:
      return CanActivateInjectionFairyLily();
    case MONSTER_EFFECT_CYBER_STEIN:
      return CanActivateCyberStein();
    default:
      if (gMonEffect.id == NEEDLE_BALL)
        return CanActivateNeedleBall();
      return TRUE;
  }
}

LYN_REPLACE_CHECK(ActivateMonsterEffect);
void ActivateMonsterEffect__Replacement(void) {
  ResetCardEffectTextData();
  SetCardEffectTextType(2);
  SetCardInfo(gMonEffect.id);

  if (gCardInfo.monsterEffect == MONSTER_EFFECT_INJECTION_FAIRY_LILY) {
    ActivateInjectionFairyLilyEffect();
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

  if (gMonEffect.id == NEEDLE_WORM) {
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

  if (gCardInfo.monsterEffect = MONSTER_EFFECT_PRINCESS_OF_TSURUGI) {
    ActivatePrincessOfTsurugiEffect();
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
      if (!gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked) {
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
      PlayMusic(SFX_TRIBUTE);
      IncrementNumTributes();
      ClearZoneAndSendMonToGraveyard2(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX], 0);
      UpdateDuelGfxExceptField();
      TryActivatingPermanentEffects();
      break;
    case 4:
      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked)
        gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      if (!gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp) {
        SetCardInfo(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
        gMonEffect.id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
        gMonEffect.row = gDuelCursor.currentY;
        gMonEffect.zone = gDuelCursor.currentX;
        if ((gCardInfo.monsterEffect == MONSTER_EFFECT_NONE && gMonEffect.id != MASK_OF_DARKNESS && gMonEffect.id != NEEDLE_BALL && gMonEffect.id != NEEDLE_WORM) || !CanActivateMonsterEffect()) {
FAILED:
          PlayMusic(SFX_FORBIDDEN);
          UpdateDuelGfxExceptField();
        }
        else {
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isFaceUp = 1;
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked = 1;
          ActivateMonsterEffect();
          if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
            LockMonsterCardsInRow(4);
          UpdateDuelGfxExceptField();
          CheckWinConditionExodia();
          if (IsDuelOver() != 1)
            TryActivatingPermanentEffects();
        }
      }
      else
        goto FAILED;
      break;
    case 5:
      if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending)
        if (gTurnDuelistBattleState[ACTIVE_DUELIST]->defenseBlocked)
          gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isDefending = 0;
      UpdateDuelGfxExceptField();
      break;
  }
}
