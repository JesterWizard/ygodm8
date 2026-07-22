#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

extern const u8 gActivationDescription_BlueEyesAlternativeWhiteDragon_Popup1[];

static void ShowBlueEyesAlternativeWhiteDragonActivationText(void) {
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = BLUE_EYES_ALTERNATIVE_WHITE_DRAGON;
  gCardEffectTextData.cardId2 = BLUE_EYES_WHITE_DRAGON;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(
      (u8 *)gActivationDescription_BlueEyesAlternativeWhiteDragon_Popup1,
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

// BEWD stays in hand as a visible cost; only the alt card is cleared
u8 TrySpecialSummonBlueEyesAlternativeWhiteDragonFromHand(u8 altHandZone) {
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 bewdZone;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonBlueEyesAlternativeWhiteDragonFromHand(altHandZone))
    return FALSE;

  bewdZone = GetFirstCardMatchZoneId(handRow, BLUE_EYES_WHITE_DRAGON);

  if (bewdZone < 0)
    return FALSE;

  ShowBlueEyesAlternativeWhiteDragonActivationText();

  handRow[bewdZone]->isFaceUp = TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, altHandZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  return TRUE;
}
