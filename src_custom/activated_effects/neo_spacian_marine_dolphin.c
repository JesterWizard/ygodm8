#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

#define MARINE_DOLPHIN_DAMAGE 500

static u8 IsHandMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 OppHandHasMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandMonster(gTurnHands[INACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u16 HighestOwnFieldAtk(void)
{
  u8 col;
  u16 best = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (atk > best)
      best = atk;
  }

  return best;
}

static s8 PickOppHandMonsterZone(void)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], IsHandMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandMonster(gTurnHands[INACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

unsigned char CanActivateNEO_SPACIAN_MARINE_DOLPHIN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != NEO_SPACIAN_MARINE_DOLPHIN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != NEO_SPACIAN_MARINE_DOLPHIN)
    return FALSE;

  /* ponytail: treated-as Aqua Dolphin name + NEX-only SS need continuous/summon hooks. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) == 0)
    return FALSE;

  return OppHandHasMonster();
}

void ActivateNEO_SPACIAN_MARINE_DOLPHINEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard **oppHand = gTurnHands[INACTIVE_DUELIST];
  s8 oppZone;
  u16 ownAtk;
  u16 chosenAtk;

  Duel_ShowEffectTextTyped(NEO_SPACIAN_MARINE_DOLPHIN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  ShowExchangeOpponentHandResult();

  oppZone = PickOppHandMonsterZone();
  if (oppZone < 0)
    return;

  ownAtk = HighestOwnFieldAtk();
  chosenAtk = gCardData_NEW[oppHand[oppZone]->id].atk;

  if (ownAtk >= chosenAtk) {
    if (Duel_DestroyZone(oppHand[oppZone], INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    if (IsDuelOver() == TRUE)
      goto finish;

    if (Duel_ChangeLp(INACTIVE_DUELIST, -(s32)MARINE_DOLPHIN_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)MARINE_DOLPHIN_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

finish:
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
