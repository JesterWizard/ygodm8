#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "player_decks.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

extern u16 gNewButtons;
extern u16 gPressedButtons;

/* ponytail: OPT bit never cleared mid-duel without turn_effect reset hook.
 * Ceiling: blocks 2nd Fang only until soft-reset / new duel BSS;
 * upgrade: turn_effect Standby → sFangOfCritiasUsedThisTurn = 0. */
static u8 sFangOfCritiasUsedThisTurn APPEND_DATA = {0};

struct CritiasTrapFusion {
  u16 trapId;
  u16 fusionId;
};

static const struct CritiasTrapFusion sCritiasPairs[] APPEND_RODATA = {
  { CRUSH_CARD, DOOM_VIRUS_DRAGON },
  { MIRROR_FORCE, MIRROR_FORCE_DRAGON },
  { TYRANT_WING, TYRANT_BURST_DRAGON },
};

static u16 FusionForCritiasTrap(u16 trapId)
{
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sCritiasPairs); i++) {
    if (sCritiasPairs[i].trapId == trapId)
      return sCritiasPairs[i].fusionId;
  }

  return CARD_NONE;
}

static u8 IsCritiasMaterialTrap(u16 cardId)
{
  return FusionForCritiasTrap(cardId) != CARD_NONE;
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

static u8 ExtraDeckHasFusion(u16 fusionId)
{
  u16 *extra;
  u8 k;

  if (!gRuntimeConfig.enable_extra_deck)
    return TRUE;

  extra = ActiveExtraDeck();
  for (k = 0; k < EXTRA_DECK_SIZE; k++) {
    if (extra[k] == fusionId)
      return TRUE;
  }

  return FALSE;
}

static u8 ActiveBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
}

static u8 HandHasCritiasTrap(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (!IsCritiasMaterialTrap(cardId))
      continue;
    if (ExtraDeckHasFusion(FusionForCritiasTrap(cardId)))
      return TRUE;
  }

  return FALSE;
}

static u8 FieldHasCritiasTrap(void)
{
  u8 col;
  u8 fixedRow = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];
    u16 fusionId;

    if (zone == NULL || zone->id == CARD_NONE || !IsCritiasMaterialTrap(zone->id))
      continue;

    fusionId = FusionForCritiasTrap(zone->id);
    if (ExtraDeckHasFusion(fusionId))
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateFangOfCritias(void)
{
  if (sFangOfCritiasUsedThisTurn)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasCritiasTrap() || FieldHasCritiasTrap();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = hand, FALSE = field. */
static u8 PlayerChoosesHandTrap(void)
{
  /* ponytail: no dedicated hand/field choice UI — A = hand, B = field.
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

static s8 PickCritiasHandZone(void)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsCritiasMaterialTrap);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;

    if (IsCritiasMaterialTrap(cardId) && ExtraDeckHasFusion(FusionForCritiasTrap(cardId)))
      return (s8)i;
  }

  return -1;
}

static u8 IsValidCritiasFieldTrap(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u16 fusionId;

  if (fixedRow != ActiveBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !IsCritiasMaterialTrap(zone->id))
    return FALSE;

  fusionId = FusionForCritiasTrap(zone->id);
  return ExtraDeckHasFusion(fusionId);
}

static u8 AiPickCritiasFieldTrap(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 fixedRow = ActiveBackrowFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidCritiasFieldTrap(fixedRow, col))
      continue;

    *outRow = fixedRow;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveCritiasFieldTrap(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *trapZone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 trapId;
  u16 fusionId;
  struct DuelSummonOpts opts;

  if (!IsValidCritiasFieldTrap(fixedRow, fixedCol))
    return;

  trapId = trapZone->id;
  fusionId = FusionForCritiasTrap(trapId);
  if (fusionId == CARD_NONE)
    return;

  /* Set traps: reveal by flipping face-up briefly before send. */
  if (trapZone->isFaceUp == FALSE)
    trapZone->isFaceUp = TRUE;

  Duel_DestroyZone(trapZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  if (gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(fusionId))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, fusionId, opts) != DUEL_ACTION_OK)
    return;

  sFangOfCritiasUsedThisTurn = TRUE;
}

static void CancelCritiasFieldTargeting(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  PlayMusic(SFX_CANCEL);
  if (spellZone != NULL && spellZone->id == THE_FANG_OF_CRITIAS)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

static void ResolveFromHand(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  s8 handZone;
  u16 trapId;
  u16 fusionId;
  struct DuelSummonOpts opts;

  handZone = PickCritiasHandZone();
  if (handZone < 0)
    return;

  trapId = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone)->id;
  fusionId = FusionForCritiasTrap(trapId);
  if (fusionId == CARD_NONE || !ExtraDeckHasFusion(fusionId))
    return;

  ClearZoneAndSendMonToGraveyard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), ACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  if (gRuntimeConfig.enable_extra_deck && !ExtraDeck_TryRemoveCard(fusionId))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, fusionId, opts) != DUEL_ACTION_OK)
    return;

  sFangOfCritiasUsedThisTurn = TRUE;
}

static void BeginFieldTrapPick(void)
{
  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidCritiasFieldTrap, ResolveCritiasFieldTrap,
                     CancelCritiasFieldTargeting, AiPickCritiasFieldTrap);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void THE_FANG_OF_CRITIAS_ResolveBody(void)
{
  u8 hasHand;
  u8 hasField;
  u8 useHand;

  Duel_ShowEffectText(THE_FANG_OF_CRITIAS);

  if (IsDuelOver() == TRUE || !CanActivateFangOfCritias())
    return;

  hasHand = HandHasCritiasTrap();
  hasField = FieldHasCritiasTrap();

  if (!hasHand && !hasField)
    return;

  if (hasHand && hasField && WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    useHand = PlayerChoosesHandTrap();
  else if (hasHand)
    useHand = TRUE;
  else
    useHand = FALSE;

  if (useHand)
    ResolveFromHand();
  else
    BeginFieldTrapPick();

  /* ponytail: "always treated as Legendary Dragon Critias" name/tag needs a
   * treat-as outside this file. Ceiling: activation + trap-send + Extra Deck SS
   * only; upgrade: name-contains / archetype tag = Legendary Dragon Critias. */
}

APPEND_TEXT void EffectTHE_FANG_OF_CRITIAS(void)
{
  if (!CanActivateFangOfCritias()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(THE_FANG_OF_CRITIAS, THE_FANG_OF_CRITIAS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void THE_FANG_OF_CRITIAS_SelfCheck(void)
{
  if (FusionForCritiasTrap(CRUSH_CARD) != DOOM_VIRUS_DRAGON)
    while (1)
      ;
  if (FusionForCritiasTrap(MIRROR_FORCE) != MIRROR_FORCE_DRAGON)
    while (1)
      ;
  if (FusionForCritiasTrap(TYRANT_WING) != TYRANT_BURST_DRAGON)
    while (1)
      ;
  if (FusionForCritiasTrap(BLUE_EYES_WHITE_DRAGON) != CARD_NONE)
    while (1)
      ;
}
#endif
