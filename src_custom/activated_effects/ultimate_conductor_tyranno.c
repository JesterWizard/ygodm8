#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void FlipCardFaceDown(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDinosaurMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR);
}

static u8 CountDinosaursInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsDinosaurMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsDinosaurMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 BanishDinosaursFromGy(u8 need)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (need > 1)
      return FALSE;

    if (!IsDinosaurMonster(gDuel.duelistbattleState[fixedDuelist].graveyard))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  while (banished < need) {
    u8 i;
    u8 found = FALSE;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (!IsDinosaurMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
        continue;

      {
        u16 cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);

        GraveyardExpand_SyncLegacyTop(fixedDuelist);
        RemovedFromPlay_PushFixed(fixedDuelist, cardId);
      }
      banished++;
      found = TRUE;
      break;
    }

    if (!found)
      break;
  }

  return banished >= need;
}

static u8 IsFaceUpOppMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone);
}

static u8 OppHasFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpOppMonster(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindOwnHandMonster(void)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);

    if (slot->id != CARD_NONE && GetTypeGroup(slot->id) == TYPE_GROUP_MONSTER)
      return slot;
  }

  return NULL;
}

static struct DuelCard *FindOwnFieldMonster(struct DuelCard *self)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone != self && zone->id != CARD_NONE
        && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
      return zone;
  }

  return self;
}

static u8 CanDestroyOwnMonster(void)
{
  return FindOwnHandMonster() != NULL || FindOwnFieldMonster(NULL) != NULL;
}

static u8 DestroyOwnMonsterForCost(struct DuelCard *self)
{
  struct DuelCard *handMon = FindOwnHandMonster();

  if (handMon != NULL)
    return Duel_DestroyZone(handMon, ACTIVE_DUELIST, FALSE) != DUEL_ACTION_DUEL_OVER;

  {
    struct DuelCard *fieldMon = FindOwnFieldMonster(self);

    if (fieldMon == NULL)
      return FALSE;

    return Duel_DestroyZone(fieldMon, ACTIVE_DUELIST, FALSE) != DUEL_ACTION_DUEL_OVER;
  }
}

static void FlipAllOppFaceUpMonstersFaceDownDef(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsFaceUpOppMonster(zone))
      continue;

    zone->isDefending = TRUE;
    FlipCardFaceDown(zone);
  }
}

unsigned char CanActivateULTIMATE_CONDUCTOR_TYRANNO(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ULTIMATE_CONDUCTOR_TYRANNO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ULTIMATE_CONDUCTOR_TYRANNO)
    return FALSE;

  /* multi-attack + DEF burn/send need battle hooks.
   * Ceiling: OPT destroy 1 of your monsters → flip all opp face-up monsters face-down DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CanDestroyOwnMonster() && OppHasFaceUpMonster();
}

void ActivateULTIMATE_CONDUCTOR_TYRANNOEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(ULTIMATE_CONDUCTOR_TYRANNO, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!CanDestroyOwnMonster() || !OppHasFaceUpMonster())
    return;

  if (!DestroyOwnMonsterForCost(self))
    return;

  if (IsDuelOver() == TRUE)
    return;

  FlipAllOppFaceUpMonstersFaceDownDef();
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonUltimateConductorTyrannoFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != ULTIMATE_CONDUCTOR_TYRANNO)
    return FALSE;

  if (CountDinosaursInGy() < 2)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonUltimateConductorTyrannoFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonUltimateConductorTyrannoFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(ULTIMATE_CONDUCTOR_TYRANNO, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!BanishDinosaursFromGy(2))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonUltimateConductorTyrannoFromHand(u8 handZone);
u8 TrySpecialSummonUltimateConductorTyrannoFromHand(u8 handZone);
#endif
