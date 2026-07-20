#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsMachineMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_MACHINE);
}

static struct DuelCard *FindMachineInHand(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsMachineMonster(slot->id))
      return slot;
  }

  return NULL;
}

static u8 AddPolymerizationFromDeck(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) < 0)
    return FALSE;

  return Duel_AddDeckCardToHand(ACTIVE_DUELIST, POLYMERIZATION, TRUE) == DUEL_ACTION_OK;
}

unsigned char CanActivateANCIENT_GEAR_GOLEM_ULTIMATE_POUND(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_GOLEM_ULTIMATE_POUND)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_GOLEM_ULTIMATE_POUND)
    return FALSE;

  /* ponytail: piercing/multi-attack + destroy-trigger Poly FALSE.
   * Ceiling: OPT discard Machine → unk4 extra-attack, else OPT add Poly. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FindMachineInHand() != NULL)
    return TRUE;

  return FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) >= 0
      && Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) >= 0;
}

void ActivateANCIENT_GEAR_GOLEM_ULTIMATE_POUNDEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *machine;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_GOLEM_ULTIMATE_POUND, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  machine = FindMachineInHand();
  if (machine != NULL) {
    if (Duel_DestroyZone(machine, ACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;

    /* ponytail: real multi-attack needs battle hook; unk4=2 extra-attack stand-in. */
    self->unk4 = 2;
    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!AddPolymerizationFromDeck())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
