#include "global.h"
#include "common-chax.h"
#include "duel_helpers.h"

extern const u8 gActivationDescription_BlueEyesShiningDragon_Popup1[];

static u8 CardIsDragon(u16 cardId) {
  if (cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_DRAGON;
}

static u8 DuelistForMonsterTurnRow(u8 turnRow) {
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 CountDragonsForDuelist(u8 duelist) {
  u8 i;
  u8 count = 0;
  u8 monsterRow = duelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (CardIsDragon(gTurnZones[monsterRow][i]->id))
      count++;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (CardIsDragon(gTurnHands[duelist][i]->id))
      count++;
  }

  return count;
}

static void ApplyDragonStageBoost(struct DuelCard *zone, u8 duelist) {
  u8 stages = CountDragonsForDuelist(duelist);

  while (stages--)
    IncrementTempStage(zone);
}

static void ShowBlueEyesShiningDragonActivationText(void) {
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = BLUE_EYES_SHINING_DRAGON;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94((u8 *)gActivationDescription_BlueEyesShiningDragon_Popup1, BLUE_EYES_SHINING_DRAGON, 0, 0, 0);
  SetCardInfo(BLUE_EYES_SHINING_DRAGON);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  gHideEffectText = hideEffectText;
}

static u8 BlueEyesShiningDragonOnField(void) {
  return RowHasCardMatch(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW], BLUE_EYES_SHINING_DRAGON)
      || RowHasCardMatch(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW], BLUE_EYES_SHINING_DRAGON);
}

// in-place BEUD zone replacement; Duel_SpecialSummon* only fills empty zones
static void InitLockedSpecialSummonZone(struct DuelCard *zone, struct DuelSummonOpts opts) {
  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->willChangeSides = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;
  zone->isFaceUp = TRUE;
  zone->isDefending = FALSE;
  zone->isLocked = opts.lockMonster;
  zone->unk4 = opts.markSpecialSummon ? 2 : 0;
}

unsigned char ShouldActivateBlueEyesShiningDragon(void) {
  if (gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  return gActiveEffect.cardId == BLUE_EYES_SHINING_DRAGON;
}

void ActivateBlueEyesShiningDragon(void) {
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  u8 duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  FlipCardFaceUp(zone);
  ApplyDragonStageBoost(zone, duelist);
}

static u8 TryAutoSummonBlueEyesShiningDragonForDuelist(u8 duelist) {
  u8 monsterRow = duelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  s8 beudCol;
  s8 shiningHandCol;
  struct DuelCard *summonZone;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);

  if (!RowHasCardMatch(gTurnZones[monsterRow], BLUE_EYES_ULTIMATE_DRAGON))
    return FALSE;

  if (!RowHasCardMatch(gTurnHands[duelist], BLUE_EYES_SHINING_DRAGON))
    return FALSE;

  beudCol = GetFirstCardMatchZoneId(gTurnZones[monsterRow], BLUE_EYES_ULTIMATE_DRAGON);
  shiningHandCol = GetFirstCardMatchZoneId(gTurnHands[duelist], BLUE_EYES_SHINING_DRAGON);

  if (beudCol < 0 || shiningHandCol < 0)
    return FALSE;

  opts.lockMonster = TRUE;
  ShowBlueEyesShiningDragonActivationText();

  summonZone = gTurnZones[monsterRow][beudCol];
  ClearZoneAndSendMonToGraveyard2(summonZone, duelist);
  summonZone->id = BLUE_EYES_SHINING_DRAGON;
  InitLockedSpecialSummonZone(summonZone, opts);
  ClearZone(gTurnHands[duelist][shiningHandCol]);

  return TRUE;
}

u8 TryAutoSummonBlueEyesShiningDragon(void) {
  if (IsDuelOver() == TRUE)
    return FALSE;

  if (BlueEyesShiningDragonOnField())
    return FALSE;

  if (TryAutoSummonBlueEyesShiningDragonForDuelist(ACTIVE_DUELIST))
    return TRUE;

  if (TryAutoSummonBlueEyesShiningDragonForDuelist(INACTIVE_DUELIST))
    return TRUE;

  return FALSE;
}
