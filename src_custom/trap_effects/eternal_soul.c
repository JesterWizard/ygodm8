#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static void TryAddDarkMagicSpell(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  s8 empty;
  u16 want = CARD_NONE;
  u8 idx = 0;

  empty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (empty < 0)
    return;

  for (i = top; i < deckSize; i++) {
    u16 id = gDuelDecks[fixedDuelist].cards[i];

    if (id == DARK_MAGIC_ATTACK || id == THOUSAND_KNIVES) {
      want = id;
      idx = i;
      break;
    }
  }

  if (want == CARD_NONE)
    return;
  if (Duel_RemoveDeckCardAt(INACTIVE_DUELIST, idx, FALSE) != DUEL_ACTION_OK)
    return;

  InitHandSlotFromCard(gTurnHands[INACTIVE_DUELIST][empty], want);
}

static void ActivateETERNAL_SOULZone(struct DuelCard *zone)
{
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  u16 gyDm = CARD_NONE;

  if (Duel_ActivateContinuousTrapPreamble(zone, ETERNAL_SOUL) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: DM unaffected by opp + destroy all on leave need protection /
   * leave hooks. Ceiling: OPT stand-in — SS Dark Magician from hand/GY, else
   * search Dark Magic Attack / Thousand Knives. */

  zone->unk4 = 1; /* protection mark for DMs */

  if (!ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromHand(INACTIVE_DUELIST, DARK_MAGICIAN, NULL, opts)
        == DUEL_ACTION_OK)
      return;

    if (GraveyardExpand_IsEnabled()) {
      for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
        if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_MAGICIAN) {
          gyDm = DARK_MAGICIAN;
          break;
        }
      }
    }
    if (gyDm != CARD_NONE) {
      Duel_SpecialSummonFromGrave(INACTIVE_DUELIST, gyDm, opts);
      return;
    }
  }

  TryAddDarkMagicSpell();
  UpdateDuelGfxExceptField();
}

void TryActivateETERNAL_SOULOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(ETERNAL_SOUL, ActivateETERNAL_SOULZone);
}

/* ponytail: TryActivateETERNAL_SOULOnOpponentTurnStart must be called from
 * turn_effect_hooks. Ceiling: body ready, not wired. */
