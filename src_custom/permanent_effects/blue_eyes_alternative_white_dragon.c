#include "global.h"
#include "common-chax.h"

extern const u8 gActivationDescription_BlueEyesAlternativeWhiteDragon[];

void UpdateDuelGfxExceptField(void);

static void InitSummonedMonsterZone(struct DuelCard *zone) {
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void ShowBlueEyesAlternativeWhiteDragonActivationText(void) {
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = BLUE_EYES_ALTERNATIVE_WHITE_DRAGON;
  gCardEffectTextData.cardId2 = BLUE_EYES_WHITE_DRAGON;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(
      (u8 *)gActivationDescription_BlueEyesAlternativeWhiteDragon,
      BLUE_EYES_ALTERNATIVE_WHITE_DRAGON,
      BLUE_EYES_WHITE_DRAGON,
      0,
      0);
  SetCardInfo(BLUE_EYES_ALTERNATIVE_WHITE_DRAGON);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  gHideEffectText = hideEffectText;
}

static u8 HandHasBlueEyesWhiteDragon(struct DuelCard **handRow) {
  return RowHasCardMatch(handRow, BLUE_EYES_WHITE_DRAGON);
}

u8 CanSpecialSummonBlueEyesAlternativeWhiteDragonFromHand(u8 altHandZone) {
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 monsterZone;

  if (altHandZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[altHandZone]->id != BLUE_EYES_ALTERNATIVE_WHITE_DRAGON)
    return FALSE;

  if (!HandHasBlueEyesWhiteDragon(handRow))
    return FALSE;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(u8 altHandZone) {
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 bewdZone;
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonBlueEyesAlternativeWhiteDragonFromHand(altHandZone))
    return FALSE;

  bewdZone = GetFirstCardMatchZoneId(handRow, BLUE_EYES_WHITE_DRAGON);
  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);

  if (bewdZone < 0 || monsterZone < 0)
    return FALSE;

  ShowBlueEyesAlternativeWhiteDragonActivationText();

  handRow[bewdZone]->isFaceUp = TRUE;

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  summonZone->id = BLUE_EYES_ALTERNATIVE_WHITE_DRAGON;
  InitSummonedMonsterZone(summonZone);
  ClearZone(handRow[altHandZone]);

  return TRUE;
}
