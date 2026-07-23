#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "harpie_perfumer.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyard);
void UpdateDuelGfxExceptField(void);

static const u16 sHystericPartyNameAsHlIds[] APPEND_RODATA = {
  HARPIE_LADY_1, HARPIE_LADY_2, HARPIE_LADY_3, CYBER_HARPIE,
  HARPIE_PERFUMER, HARPIE_CHANNELER, HARPIE_DANCER, HARPIE_ORACLE,
  HARPIE_QUEEN, HARPIE_HARPIST, HARPIE_CONDUCTOR,
};

static u8 sHystericPartyInit APPEND_DATA = {0};

static u8 AnyCard(u16 cardId)
{
  return cardId != CARD_NONE;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHarpieLadyNameId(u16 cardId)
{
  struct DuelCard probe;

  if (cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == CYBER_HARPIE)
    return TRUE;

  probe.id = cardId;
  probe.isFaceUp = TRUE;
  probe.isDefending = FALSE;
  probe.isLocked = FALSE;
  probe.unkTwo = 0;
  probe.unkThree = 0;
  probe.unk4 = 0;
  probe.willChangeSides = FALSE;
  return HarpiePerfumer_TreatsNameAsHarpieLady(&probe);
}

/* When Party leaves, destroy monsters it summoned (tracked by unk4 count). */
static void OnHystericPartyLeave(const struct EffectEvent *ev)
{
  u8 row;
  u8 col;
  u8 remaining;
  struct DuelCard *partyZone;

  if (ev == NULL || ev->cardId != HYSTERIC_PARTY || ev->controller > DUEL_OPPONENT)
    return;

  partyZone = ev->zone;
  remaining = (partyZone != NULL) ? partyZone->unk4 : 5;
  if (remaining == 0)
    return;

  row = Duel_FixedMonsterRowForDuelist(ev->controller);
  for (col = 0; col < MAX_ZONES_IN_ROW && remaining > 0; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    if (!IsHarpieLadyNameId(zone->id))
      continue;

    Duel_DestroyZone(zone, Duel_TurnDuelistForFixedDuelist(ev->controller), FALSE);
    remaining--;
    if (IsDuelOver() == TRUE)
      return;
  }

  UpdateDuelGfxExceptField();
}

static void HystericParty_EnsureInit(void)
{
  if (sHystericPartyInit)
    return;

  sHystericPartyInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnHystericPartyLeave);
}

APPEND_TEXT void EffectHYSTERIC_PARTY(void)
{
  s8 handZone;
  struct DuelCard *trapZone;
  struct DuelSummonOpts opts;
  u8 summoned = 0;
  u8 i;

  HystericParty_EnsureInit();
  Duel_ShowTrapResponseText(HYSTERIC_PARTY, gTrapEffectData.originCardId);

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  if (WhoseTurn() == DUEL_PLAYER)
    handZone = SelectHandCardMatchingPredicate(gTurnHands[INACTIVE_DUELIST], AnyCard);
  else
    handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);

  if (handZone >= 0)
    ClearZoneAndSendMonToGraveyard(gTurnHands[INACTIVE_DUELIST][handZone], INACTIVE_DUELIST);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];
  if (trapZone != NULL)
    Duel_ActivateContinuousZone(trapZone);

  if (!ArchlordKristya_IsSpecialSummonLocked()) {
    opts = Duel_DefaultSpecialSummonOpts(FALSE);
    /* Prefer literal Harpie Lady, then other name=HL forms in GY. */
    while (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
      if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, HARPIE_LADY, opts)
          == DUEL_ACTION_OK) {
        summoned++;
      } else {
        u8 found = FALSE;

        for (i = 0; i < ARRAY_COUNT(sHystericPartyNameAsHlIds); i++) {
          if (Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, sHystericPartyNameAsHlIds[i], opts)
              == DUEL_ACTION_OK) {
            summoned++;
            found = TRUE;
            break;
          }
        }
        if (!found)
          break;
      }
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  if (trapZone != NULL)
    trapZone->unk4 = summoned;

  UpdateDuelGfxExceptField();
}
