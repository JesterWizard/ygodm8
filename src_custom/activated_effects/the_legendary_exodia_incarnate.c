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

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsForbiddenOneMonster(u16 cardId)
{
  return cardId == RIGHT_LEG_OF_THE_FORBIDDEN_ONE
      || cardId == LEFT_LEG_OF_THE_FORBIDDEN_ONE
      || cardId == RIGHT_ARM_OF_THE_FORBIDDEN_ONE
      || cardId == LEFT_ARM_OF_THE_FORBIDDEN_ONE
      || cardId == EXODIA_THE_FORBIDDEN_ONE;
}

static struct DuelCard *FindForbiddenOneTribute(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsForbiddenOneMonster(zone->id))
      return zone;
  }

  return NULL;
}

static u16 FindForbiddenOneInGy(u8 *outIndex)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsForbiddenOneMonster(cardId)) {
      *outIndex = 0;
      return cardId;
    }
    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsForbiddenOneMonster(cardId)) {
      *outIndex = i;
      return cardId;
    }
  }

  return CARD_NONE;
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

static u8 AddForbiddenOneFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 gyIndex;
  u16 cardId;
  s8 handZone;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  cardId = FindForbiddenOneInGy(&gyIndex);
  if (cardId == CARD_NONE)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

unsigned char CanActivateTHE_LEGENDARY_EXODIA_INCARNATE(void)
{
  struct DuelCard *zone;
  u8 gyIndex;

  if (gMonEffect.id != THE_LEGENDARY_EXODIA_INCARNATE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THE_LEGENDARY_EXODIA_INCARNATE)
    return FALSE;

  /* ponytail: ATK gain / unaffected FALSE.
   * Ceiling: OPT add Forbidden One from GY. FromHand tribute Forbidden One → SS. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindForbiddenOneInGy(&gyIndex) != CARD_NONE;
}

void ActivateTHE_LEGENDARY_EXODIA_INCARNATEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(THE_LEGENDARY_EXODIA_INCARNATE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!AddForbiddenOneFromGy())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonTheLegendaryExodiaIncarnateFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != THE_LEGENDARY_EXODIA_INCARNATE)
    return FALSE;

  if (FindForbiddenOneTribute() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  /* Tribute frees its zone for the SS. */
  return TRUE;
}

u8 TrySpecialSummonTheLegendaryExodiaIncarnateFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *tribute;

  if (!CanSpecialSummonTheLegendaryExodiaIncarnateFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(THE_LEGENDARY_EXODIA_INCARNATE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  tribute = FindForbiddenOneTribute();
  if (tribute == NULL)
    return FALSE;

  if (Duel_DestroyZone(tribute, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonTheLegendaryExodiaIncarnateFromHand(u8 handZone);
u8 TrySpecialSummonTheLegendaryExodiaIncarnateFromHand(u8 handZone);
#endif
