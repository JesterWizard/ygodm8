#include "global.h"
#include "common-chax.h"
#include "amazoness_empress.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sEmpressInit APPEND_DATA = {0};

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 CanSpecialSummonQueen(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static u8 TrySsQueenFromHand(u8 turnDuelist)
{
  u8 col;
  struct DuelSummonOpts opts;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], col);

    if (slot == NULL || slot->id != AMAZONESS_QUEEN)
      continue;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    return Duel_SpecialSummonFromHandZone(turnDuelist, col, opts) == DUEL_ACTION_OK;
  }

  return FALSE;
}

static u8 TrySsQueenFromDeck(u8 turnDuelist)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (Duel_FindDeckCardIndex(turnDuelist, AMAZONESS_QUEEN) < 0)
    return FALSE;

  return Duel_SpecialSummonFromDeck(turnDuelist, AMAZONESS_QUEEN, opts) == DUEL_ACTION_OK;
}

static u8 TrySsQueenFromGy(u8 fixedDuelist, u8 turnDuelist)
{
  s16 gyIndex = -1;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != AMAZONESS_QUEEN)
      return FALSE;
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    u8 i;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == AMAZONESS_QUEEN) {
        gyIndex = (s16)i;
        break;
      }
    }
    if (gyIndex < 0)
      return FALSE;
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  if (cardId != AMAZONESS_QUEEN)
    return FALSE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts) == DUEL_ACTION_OK;
}

static void TrySpecialSummonAmazonessQueen(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);

  if (!CanSpecialSummonQueen(turnDuelist))
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_EMPRESS, 2);
  if (IsDuelOver() == TRUE)
    return;

  if (TrySsQueenFromHand(turnDuelist)
      || TrySsQueenFromDeck(turnDuelist)
      || TrySsQueenFromGy(fixedDuelist, turnDuelist)) {
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
  }
}

static void OnEmpressLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != AMAZONESS_EMPRESS)
    return;

  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TrySpecialSummonAmazonessQueen(ev->controller);
}

void AmazonessEmpress_EnsureInit(void)
{
  if (sEmpressInit)
    return;

  sEmpressInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnEmpressLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnEmpressLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnEmpressLeaveField);
}

unsigned char CanActivateAMAZONESS_EMPRESS(void)
{
  if (gMonEffect.id != AMAZONESS_EMPRESS)
    return FALSE;

  /* Battle protect via AmazonessQueen_PreventsBattleDestroy.
   * Leave-field SS Queen via AmazonessEmpress_EnsureInit.
   * ponytail: Amazoness pierce while Empress face-up not wired. */
  return FALSE;
}

void ActivateAMAZONESS_EMPRESSEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_EMPRESS, 2);
}
