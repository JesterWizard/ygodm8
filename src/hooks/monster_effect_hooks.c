#include "global.h"
#include "configs/runtime.h"
#include "constants/monster_effects.h"

#define MONSTER_EFFECT_INJECTION_FAIRY_LILY 102

extern void (*const gMonEffects[])(void);

void ActivateMonsterEffect(void);
void MonsterActionMenu(void);
unsigned char HandlePlayerMonsterAction(void);
void sub_8044570(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(void);

static unsigned char CanActivateInjectionFairyLily(void) {
  if (gMonEffect.id != INJECTION_FAIRY_LILY)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER)
    return gDuelLifePoints[DUEL_PLAYER] >= 3000;

  return gDuelLifePoints[DUEL_OPPONENT] >= 3000;
}

static void ActivateInjectionFairyLilyEffect(void) {
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(3000);
  else
    SetOpponentLifePointsToSubtract(3000);

  HandleAtkAndLifePointsAction();
  CheckLoserFlags();

  // Increment by 4 stages, so 2000 ATK/DEF
  for (i = 0; i < 4; i++)
    IncrementPermStage(gTurnZones[gMonEffect.row][gMonEffect.zone]);

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = INJECTION_FAIRY_LILY;
    ActivateCardEffectText();
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
        if (gCardInfo.monsterEffect == MONSTER_EFFECT_NONE
         || (gCardInfo.monsterEffect == MONSTER_EFFECT_INJECTION_FAIRY_LILY && !CanActivateInjectionFairyLily())) {
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
