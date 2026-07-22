#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sFrogArchetypeName[] APPEND_RODATA = "Frog";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsFrogDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (cardId == FROG_THE_JAM)
    return FALSE;

  if (!Duel_CardNameContains(cardId, sFrogArchetypeName))
    return FALSE;

  return !Duel_CardCannotBeSpecialSummoned(cardId);
}

static u16 FindDeckFrogTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsFrogDeckTarget(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSsFrog(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindDeckFrogTarget() != CARD_NONE;
}

static u8 IsAquaMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER
      && Duel_CardHasMonsterType(cardId, TYPE_AQUA);
}

static struct DuelCard *FindAquaCost(struct DuelCard *self)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 col;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot != NULL && IsAquaMonster(slot->id))
      return slot;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone == self || zone->id == CARD_NONE)
      continue;

    if (zone->isFaceUp && IsAquaMonster(zone->id))
      return zone;
  }

  return NULL;
}

static u8 IsOppDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != INACTIVE_DUELIST_MONSTER_ROW && fixedRow != INACTIVE_DUELIST_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 OppHasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppDestroyTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 CanSendAquaDestroy(struct DuelCard *self)
{
  return FindAquaCost(self) != NULL && OppHasDestroyTarget();
}

static u8 SendAquaCost(struct DuelCard *self)
{
  struct DuelCard *aqua = FindAquaCost(self);
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;
  u8 fixedDuelist = FixedDuelistForActive();

  if (aqua == NULL)
    return FALSE;

  for (i = 0; i < max; i++) {
    if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i) != aqua)
      continue;

    return Duel_DestroyZone(aqua, ACTIVE_DUELIST, FALSE) != DUEL_ACTION_DUEL_OVER;
  }

  ClearZoneAndSendMonToGraveyard2(aqua, fixedDuelist);
  return TRUE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsOppDestroyTarget(fixedRow, fixedCol) || zone == NULL || self == NULL)
    return;

  if (!SendAquaCost(self) || IsDuelOver() == TRUE)
    return;

  if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOppDestroyTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateTOADALLY_AWESOME(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != TOADALLY_AWESOME)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TOADALLY_AWESOME)
    return FALSE;

  /* Printed remainder omitted by this ruleset.
   * OPT SS Frog from Deck, else OPT send Aqua → destroy 1 opp. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (CanSsFrog())
    return TRUE;

  return CanSendAquaDestroy(zone);
}

void ActivateTOADALLY_AWESOMEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 frogId;

  Duel_ShowEffectTextTyped(TOADALLY_AWESOME, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (CanSsFrog()) {
    frogId = FindDeckFrogTarget();
    if (frogId == CARD_NONE)
      return;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, frogId, opts) != DUEL_ACTION_OK)
      return;

    MarkMonsterEffectUsed(self);
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
    return;
  }

  if (!CanSendAquaDestroy(self))
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;
  Duel_SetupPickZone(IsOppDestroyTarget, ResolveDestroyTarget, CancelTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
