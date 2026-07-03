#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

extern const u8 gActivationDescription_Gilasaurus_Popup1[];

static void ShowGilasaurusActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = GILASAURUS;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(
      (u8 *)gActivationDescription_Gilasaurus_Popup1,
      GILASAURUS,
      CARD_NONE,
      0,
      0);
  SetCardInfo(GILASAURUS);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  gHideEffectText = hideEffectText;
}

static void TrySummonOpponentGraveyardMonster(void)
{
  u16 cardId = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return;

  if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, CARD_NONE, opts);
}

u8 CanSpecialSummonGilasaurusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != GILASAURUS)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonGilasaurusFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!CanSpecialSummonGilasaurusFromHand(handZone))
    return FALSE;

  ShowGilasaurusActivationText();

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  TrySummonOpponentGraveyardMonster();
  return TRUE;
}
