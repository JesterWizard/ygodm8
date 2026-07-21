#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "ancient_gear_frame.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAncientGearGolemName[] APPEND_RODATA = "Ancient Gear Golem";
static u8 sFrameInit APPEND_DATA = {0};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGolemOrSpellTrapMentioningGolem(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId == ANCIENT_GEAR_FRAME)
    return FALSE;

  if (cardId == ANCIENT_GEAR_GOLEM || cardId == ANCIENT_GEAR_GOLEM_ULTIMATE_POUND
      || cardId == ULTIMATE_ANCIENT_GEAR_GOLEM)
    return TRUE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearGolemName);
}

static u16 FindSearchTargetInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGolemOrSpellTrapMentioningGolem(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 TrySpecialSummonGolemFromHand(u8 controller)
{
  u8 turnDuelist;
  struct DuelCard **hand;
  u8 col;
  struct DuelSummonOpts opts;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  turnDuelist = (controller == WhoseTurn()) ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  hand = gTurnHands[turnDuelist];
  opts = Duel_DefaultSpecialSummonOpts(TRUE);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(hand, col);

    if (slot == NULL || slot->id != ANCIENT_GEAR_GOLEM)
      continue;

    if (Duel_SpecialSummonFromHandZone(turnDuelist, (s8)col, opts) == DUEL_ACTION_OK)
      return TRUE;
  }

  return FALSE;
}

static void OnFrameLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != ANCIENT_GEAR_FRAME)
    return;

  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TrySpecialSummonGolemFromHand(ev->controller);
}

void AncientGearFrame_EnsureInit(void)
{
  if (sFrameInit)
    return;

  sFrameInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnFrameLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnFrameLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnFrameLeaveField);
}

unsigned char CanActivateANCIENT_GEAR_FRAME(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ANCIENT_GEAR_FRAME)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ANCIENT_GEAR_FRAME)
    return FALSE;

  /* Attack S/T lock live via AncientGear_AttackerBlocksOppSpellTrap.
   * Leave-field SS via AncientGearFrame_EnsureInit.
   * Ceiling: OPT discard 1 → add AG Golem or S/T mentioning Golem from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (Duel_CountCardsInHand(gTurnHands[ACTIVE_DUELIST]) < 1)
    return FALSE;

  return FindSearchTargetInDeck() != CARD_NONE;
}

void ActivateANCIENT_GEAR_FRAMEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 searchId;

  Duel_ShowEffectTextTyped(ANCIENT_GEAR_FRAME, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_DiscardFromHand(ACTIVE_DUELIST, 1, NULL, TRUE) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  searchId = FindSearchTargetInDeck();
  if (searchId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
