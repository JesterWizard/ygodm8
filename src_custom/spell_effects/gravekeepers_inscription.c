#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

/* 0 = none; 1 = no GY effects; 2 = no GY banish; 3 = no SS from GY. */
static u8 sInscriptionMode APPEND_DATA = {0};
/* Turns remaining after activation (activator turn + opponent turn ≈ 2). */
static u8 sInscriptionTurnsLeft APPEND_DATA = {0};

#define INSCRIPTION_MODE_NO_GY_EFFECTS 1
#define INSCRIPTION_MODE_NO_GY_BANISH 2
#define INSCRIPTION_MODE_NO_SS_FROM_GY 3
#define INSCRIPTION_DURATION_TURNS 2

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* Returns INSCRIPTION_MODE_*. */
static u8 PlayerChoosesInscriptionMode(void)
{
  /* ponytail: no dedicated 3-way choice UI — A / B / START.
   * Ceiling: unlabeled buttons; upgrade path: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return INSCRIPTION_MODE_NO_GY_EFFECTS;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return INSCRIPTION_MODE_NO_GY_BANISH;
    }

    if (gNewButtons & START_BUTTON) {
      PlayMusic(SFX_SELECT);
      return INSCRIPTION_MODE_NO_SS_FROM_GY;
    }

    WaitForVBlank();
  }
}

static u8 AiChoosesInscriptionMode(void)
{
  return INSCRIPTION_MODE_NO_SS_FROM_GY;
}

u8 GravekeepersInscription_GetActiveMode(void)
{
  if (sInscriptionTurnsLeft == 0)
    return 0;

  return sInscriptionMode;
}

u8 GravekeepersInscription_BlocksGraveyardEffects(void)
{
  return GravekeepersInscription_GetActiveMode() == INSCRIPTION_MODE_NO_GY_EFFECTS;
}

u8 GravekeepersInscription_BlocksGraveyardBanish(void)
{
  return GravekeepersInscription_GetActiveMode() == INSCRIPTION_MODE_NO_GY_BANISH;
}

u8 GravekeepersInscription_BlocksSpecialSummonFromGraveyard(void)
{
  return GravekeepersInscription_GetActiveMode() == INSCRIPTION_MODE_NO_SS_FROM_GY;
}

/* Wire from turn_effect_hooks End Phase (clear after opponent's turn). */
void TryClearGravekeepersInscriptionEndPhase(void)
{
  if (sInscriptionTurnsLeft == 0)
    return;

  if (sInscriptionTurnsLeft > 0)
    sInscriptionTurnsLeft--;

  if (sInscriptionTurnsLeft == 0)
    sInscriptionMode = 0;
}

static void GRAVEKEEPERS_INSCRIPTION_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 mode;

  Duel_ShowEffectText(GRAVEKEEPERS_INSCRIPTION);

  if (IsDuelOver() == TRUE)
    return;

  /* ponytail: "activate only at start of Main Phase 1" needs a phase/action
   * counter outside this file (no Main Phase 1-start gate API). Ceiling: activable
   * any time like a normal spell; upgrade: CanActivate → require MP1 + no prior
   * play/set/summon this turn. */

  if (WhoseTurn() == DUEL_PLAYER)
    mode = PlayerChoosesInscriptionMode();
  else
    mode = AiChoosesInscriptionMode();

  sInscriptionMode = mode;
  sInscriptionTurnsLeft = INSCRIPTION_DURATION_TURNS;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectGRAVEKEEPERS_INSCRIPTION(void)
{
  if (Duel_TryResolveSpellThroughTraps(GRAVEKEEPERS_INSCRIPTION,
                                       GRAVEKEEPERS_INSCRIPTION_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GRAVEKEEPERS_INSCRIPTION_SelfCheck(void)
{
  if (INSCRIPTION_MODE_NO_GY_EFFECTS != 1)
    while (1)
      ;
  if (INSCRIPTION_MODE_NO_GY_BANISH != 2)
    while (1)
      ;
  if (INSCRIPTION_MODE_NO_SS_FROM_GY != 3)
    while (1)
      ;
  if (INSCRIPTION_DURATION_TURNS != 2)
    while (1)
      ;
}
#endif
