#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

#define DESTINY_DRAW_DRAW_COUNT 2

static const char sDestinyHeroArchetypeName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroArchetypeName);
}

static u8 HandHasDestinyHero(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDestinyHeroCard(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateDESTINY_DRAW(void)
{
  return HandHasDestinyHero(gTurnHands[ACTIVE_DUELIST]);
}

static s8 PickDestinyHeroHandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsDestinyHeroCard);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsDestinyHeroCard(handRow[i]->id))
      return i;
  }

  return -1;
}

static void DESTINY_DRAW_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  if (!CanActivateDESTINY_DRAW())
    return;

  Duel_ShowEffectText(DESTINY_DRAW);

  if (IsDuelOver() == TRUE)
    return;

  handZone = PickDestinyHeroHandZone(handRow);
  if (handZone < 0)
    return;

  ClearZoneAndSendMonToGraveyard(handRow[handZone], ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, DESTINY_DRAW_DRAW_COUNT, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectDESTINY_DRAW(void)
{
  if (!CanActivateDESTINY_DRAW()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DESTINY_DRAW, DESTINY_DRAW_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
