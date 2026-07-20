#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define DUNKER_DAMAGE 500

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroCard(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 HandHasDestinyHero(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsDestinyHeroCard(SixCardHand_ZoneAtHandRow(handRow, i)->id))
      return TRUE;
  }

  return FALSE;
}

static s8 PickDestinyHeroHandZoneForAi(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (IsDestinyHeroCard(SixCardHand_ZoneAtHandRow(handRow, i)->id))
      return (s8)i;
  }

  return -1;
}

unsigned char CanActivateDESTINY_HERO_DUNKER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DESTINY_HERO_DUNKER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DUNKER)
    return FALSE;

  return CanUseMonsterEffect(zone) && HandHasDestinyHero();
}

void ActivateDESTINY_HERO_DUNKEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DUNKER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(handRow, IsDestinyHeroCard);
  else
    handZone = PickDestinyHeroHandZoneForAi();

  if (handZone < 0)
    return;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  if (Duel_ChangeLp(INACTIVE_DUELIST, -DUNKER_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
