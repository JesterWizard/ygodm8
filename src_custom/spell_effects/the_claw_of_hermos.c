#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "player_decks.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

u8 ExtraDeck_TryRemoveCard(u16 cardId);

struct HermosFusionEntry {
  u16 fusionId;
  u8 materialType;
};

static const struct HermosFusionEntry sHermosFusions[] APPEND_RODATA = {
  { GODDESS_BOW, TYPE_WARRIOR },
  { ROCKET_HERMOS_CANNON, TYPE_WARRIOR },
  { RED_EYES_BLACK_DRAGON_SWORD, TYPE_DRAGON },
  { TIME_MAGIC_HAMMER, TYPE_SPELLCASTER },
};

static const u8 sHermosPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* ponytail: OPT needs turn-scoped flag cleared outside this file.
 * Ceiling: multiple Claw per turn until soft-reset; upgrade: Standby clear. */
/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */
static u16 sHermosChosenFusion APPEND_DATA = {0};
static u8 sHermosRequiredType APPEND_DATA = {0};

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u16 *ActiveExtraDeck(void)
{
  u8 active = gActiveDeckIndex;

  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      return gPlayerDeck1ExtraDeck;
    case 2:
      return gPlayerDeck2ExtraDeck;
    case 3:
      return gPlayerDeck3ExtraDeck;
    default:
      return gPlayerDeck1ExtraDeck;
    }
  }

  return gPlayerDeck1ExtraDeck;
}

static u8 ExtraDeckHasCard(u16 cardId)
{
  u16 *extra;
  u8 i;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  extra = ActiveExtraDeck();
  for (i = 0; i < EXTRA_DECK_SIZE; i++) {
    if (extra[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

static u8 HermosRequiredType(u16 fusionId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sHermosFusions); i++) {
    if (sHermosFusions[i].fusionId == fusionId)
      return sHermosFusions[i].materialType;
  }

  return 0;
}

static u8 IsHermosMaterialMonster(u16 cardId, u8 monsterType)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, monsterType);
}

static u8 HandHasMaterialType(u8 monsterType)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHermosMaterialMonster(gTurnHands[ACTIVE_DUELIST][i]->id, monsterType))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasMaterialType(u8 monsterType)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsHermosMaterialMonster(zone->id, monsterType))
      return TRUE;
  }

  return FALSE;
}

static u8 HasMaterialForFusion(u16 fusionId)
{
  u8 monsterType = HermosRequiredType(fusionId);

  if (monsterType == 0)
    return FALSE;

  return HandHasMaterialType(monsterType) || FieldHasMaterialType(monsterType);
}

static u8 BuildHermosTargets(u16 *outIds, u8 maxOut)
{
  u8 count = 0;
  u8 i;

  if (outIds == NULL || maxOut == 0)
    return 0;

  for (i = 0; i < ARRAY_COUNT(sHermosFusions) && count < maxOut; i++) {
    u16 fusionId = sHermosFusions[i].fusionId;

    if (!ExtraDeckHasCard(fusionId))
      continue;

    if (!HasMaterialForFusion(fusionId))
      continue;

    outIds[count++] = fusionId;
  }

  return count;
}

static u8 CanActivateClawOfHermos(void)
{
  u16 targets[ARRAY_COUNT(sHermosFusions)];

  if (EffectOpt_IsUsed(THE_CLAW_OF_HERMOS))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return BuildHermosTargets(targets, ARRAY_COUNT(sHermosFusions)) > 0;
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = field, FALSE = hand. */
static u8 PlayerChoosesField(void)
{
  /* ponytail: no dedicated field/hand choice UI — A = field, B = hand.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u16 PlayerPickHermosFusion(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;

  if (count == 1)
    return targetIds[0];

  DECKMENU_SAVE();

  for (j = 0; j < EXTRA_DECK_SIZE; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sHermosPickLabels,
                                         ARRAY_COUNT(sHermosPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickHermosFusion(const u16 *targetIds, u8 count)
{
  u8 i;
  u16 bestId = CARD_NONE;
  u16 bestAtk = 0;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (bestId == CARD_NONE || gCardInfo.atk > bestAtk) {
      bestId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return bestId;
}

static void DestroyClawSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == THE_CLAW_OF_HERMOS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 HandMaterialPred(u16 cardId)
{
  return IsHermosMaterialMonster(cardId, sHermosRequiredType);
}

static void FinishHermosSummon(void)
{
  struct DuelSummonOpts opts;

  if (gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(sHermosChosenFusion)) {
    DestroyClawSpellZone();
    return;
  }

  DestroyClawSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, sHermosChosenFusion, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(THE_CLAW_OF_HERMOS);
}

static void CancelHermosTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyClawSpellZone();
}

static u8 IsValidHermosFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return IsHermosMaterialMonster(zone->id, sHermosRequiredType);
}

static u8 AiPickHermosFieldTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidHermosFieldTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveHermosFieldTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsValidHermosFieldTarget(fixedRow, fixedCol))
    return;

  zone = gFixedZones[fixedRow][fixedCol];
  /* ponytail: Set reveal has no dedicated flip UI — send face-down as-is.
   * Ceiling: no reveal animation; upgrade: brief face-up before GY send. */
  Duel_DestroyZone(zone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  FinishHermosSummon();
}

static void BeginHermosFieldPick(void)
{
  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidHermosFieldTarget, ResolveHermosFieldTarget,
                     CancelHermosTargeting, AiPickHermosFieldTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void SendHermosMaterialThenSummon(void)
{
  u8 hasField = FieldHasMaterialType(sHermosRequiredType);
  u8 hasHand = HandHasMaterialType(sHermosRequiredType);
  u8 useField;

  if (!hasField && !hasHand) {
    DestroyClawSpellZone();
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasField && hasHand)
    useField = PlayerChoosesField();
  else if (hasField)
    useField = TRUE;
  else
    useField = FALSE;

  if (useField) {
    BeginHermosFieldPick();
    return;
  }

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, HandMaterialPred, FALSE) != DUEL_ACTION_OK) {
    DestroyClawSpellZone();
    return;
  }

  if (IsDuelOver() == TRUE)
    return;

  FinishHermosSummon();
}

static void THE_CLAW_OF_HERMOS_ResolveBody(void)
{
  u16 targets[ARRAY_COUNT(sHermosFusions)];
  u8 targetCount;
  u16 chosenId;

  Duel_ShowEffectText(THE_CLAW_OF_HERMOS);

  if (IsDuelOver() == TRUE || !CanActivateClawOfHermos())
    return;

  targetCount = BuildHermosTargets(targets, ARRAY_COUNT(sHermosFusions));
  if (targetCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chosenId = PlayerPickHermosFusion(targets, targetCount);
  else
    chosenId = AiPickHermosFusion(targets, targetCount);

  if (chosenId == CARD_NONE || HermosRequiredType(chosenId) == 0)
    return;

  sHermosChosenFusion = chosenId;
  sHermosRequiredType = HermosRequiredType(chosenId);
  SendHermosMaterialThenSummon();
}

APPEND_TEXT void EffectTHE_CLAW_OF_HERMOS(void)
{
  if (!CanActivateClawOfHermos()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_CLAW_OF_HERMOS, THE_CLAW_OF_HERMOS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_CLAW_OF_HERMOS_SelfCheck(void)
{
  if (HermosRequiredType(GODDESS_BOW) != TYPE_WARRIOR)
    while (1)
      ;
  if (HermosRequiredType(RED_EYES_BLACK_DRAGON_SWORD) != TYPE_DRAGON)
    while (1)
      ;
  if (HermosRequiredType(TIME_MAGIC_HAMMER) != TYPE_SPELLCASTER)
    while (1)
      ;
  if (!IsHermosMaterialMonster(GAIA_THE_FIERCE_KNIGHT, TYPE_WARRIOR))
    while (1)
      ;
  if (IsHermosMaterialMonster(BLUE_EYES_WHITE_DRAGON, TYPE_WARRIOR))
    while (1)
      ;
}
#endif
