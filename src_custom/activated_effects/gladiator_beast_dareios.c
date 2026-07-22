#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 IsLv4OrLowerGladiatorBeast(u16 cardId)
{
  if (!IsGladiatorBeastMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= 4;
}

static u8 OppHasMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      return TRUE;
  }

  return FALSE;
}

static u16 FindGladiatorBeastInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static s8 FindLv4OrLowerGbHandZone(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *zone = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (zone != NULL && IsLv4OrLowerGladiatorBeast(zone->id))
      return (s8)i;
  }

  return -1;
}

static u16 FindLv4OrLowerGbInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLv4OrLowerGladiatorBeast(cardId) ? cardId : CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsLv4OrLowerGladiatorBeast(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 CanSpecialSummonPath(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (OppHasMonster() && FindGladiatorBeastInDeck() != CARD_NONE)
    return TRUE;

  if (FindLv4OrLowerGbHandZone() >= 0)
    return TRUE;

  return FindLv4OrLowerGbInGy() != CARD_NONE;
}

static u8 SpecialSummonPath(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (OppHasMonster()) {
    u16 deckId = FindGladiatorBeastInDeck();

    if (deckId != CARD_NONE)
      return Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, deckId, opts) == DUEL_ACTION_OK;
  }

  {
    s8 handZone = FindLv4OrLowerGbHandZone();

    if (handZone >= 0)
      return Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) == DUEL_ACTION_OK;
  }

  {
    u16 gyId = FindLv4OrLowerGbInGy();
    u8 i;

    if (gyId == CARD_NONE)
      return FALSE;

    if (!GraveyardExpand_IsEnabled())
      return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, CARD_NONE, opts) == DUEL_ACTION_OK;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) != gyId)
        continue;

      gyId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
      GraveyardExpand_SyncLegacyTop(fixedDuelist);
      return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, gyId, opts) == DUEL_ACTION_OK;
    }
  }

  return FALSE;
}

unsigned char CanActivateGLADIATOR_BEAST_DAREIOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GLADIATOR_BEAST_DAREIOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GLADIATOR_BEAST_DAREIOS)
    return FALSE;

  /* OPT SS Lv≤4 GB from hand/GY, or any GB from Deck if opp has monster. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanSpecialSummonPath();
}

void ActivateGLADIATOR_BEAST_DAREIOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_DAREIOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!SpecialSummonPath())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
