#include "global.h"
#include "common-chax.h"
#include "berserker_soul.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

#define BERSERKER_SOUL_DAMAGE 500
#define BERSERKER_SOUL_MAX_REPEATS 8

static u8 sBerserkerSoulDirectDamageFlag APPEND_DATA = {0};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 HandHasAnyCard(void)
{
  return Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) > 0;
}

static void DiscardEntireHand(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    ClearZoneAndSendMonToGraveyard(zone, ACTIVE_DUELIST);
  }
}

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

void BerserkerSoul_OnDirectDamage(s32 dmg)
{
  if (dmg > 0 && dmg <= BERSERKER_SOUL_DIRECT_DAMAGE_MAX)
    sBerserkerSoulDirectDamageFlag = TRUE;
}

u8 BerserkerSoul_CanActivateFromBattleFlag(void)
{
  return sBerserkerSoulDirectDamageFlag;
}

void BerserkerSoul_OnTurnBoundary(void)
{
  sBerserkerSoulDirectDamageFlag = FALSE;
}

u8 CanActivateBERSERKER_SOUL(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (!BerserkerSoul_CanActivateFromBattleFlag())
    return FALSE;
  if (EffectOpt_IsUsed(BERSERKER_SOUL))
    return FALSE;
  if (!HandHasAnyCard())
    return FALSE;
  if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
    return FALSE;

  return TRUE;
}

static void BERSERKER_SOUL_ResolveBody(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 repeats;
  u16 cardId;

  if (!CanActivateBERSERKER_SOUL()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  Duel_ShowEffectText(BERSERKER_SOUL);
  if (IsDuelOver() == TRUE)
    return;

  DiscardEntireHand();

  for (repeats = 0; repeats < BERSERKER_SOUL_MAX_REPEATS; repeats++) {
    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist))
      break;

    cardId = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];
    gDuelDecks[fixedDuelist].cardsDrawn++;

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER) {
      PlaceCardOnDeckTop(fixedDuelist, cardId);
      break;
    }

    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
    if (Duel_ChangeLp(INACTIVE_DUELIST, -BERSERKER_SOUL_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  EffectOpt_MarkUsed(BERSERKER_SOUL);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectBERSERKER_SOUL(void)
{
  if (Duel_TryResolveSpellThroughTraps(BERSERKER_SOUL, BERSERKER_SOUL_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void BERSERKER_SOUL_SelfCheck(void)
{
  if (BERSERKER_SOUL_DIRECT_DAMAGE_MAX != 1500)
    while (1)
      ;
}
#endif
