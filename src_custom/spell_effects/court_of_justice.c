#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "court_of_justice.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "spell_effects.h"

extern struct DuelCard gSelectedCard;

void LockMonsterCardsInRow(unsigned char turnRow);
void UpdateDuelGfxExceptField(void);

extern u8 gCourtOfJusticeIgnitionPending;
extern u8 gCourtOfJusticeHandPlacementActive;

static u8 IsFairyMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].type == TYPE_FAIRY;
}

static u8 IsFaceUpMonsterZone(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  /* Attack-position monsters keep isFaceUp=0 until EOT FlipAtkPosCardsFaceUp. */
  return zone->isFaceUp || !zone->isDefending;
}

static u8 IsFaceUpLevel1FairyZone(const struct DuelCard *zone)
{
  if (!IsFaceUpMonsterZone(zone))
    return FALSE;

  if (gCardData_NEW[zone->id].type != TYPE_FAIRY)
    return FALSE;

  return gCardData_NEW[zone->id].level == 1;
}

static u8 ControlsFaceUpLevel1Fairy(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpLevel1FairyZone(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 HandHasFairyMonster(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsFairyMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindActiveCourtOfJusticeZone(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone->id == COURT_OF_JUSTICE && zone->isFaceUp == TRUE)
      return zone;
  }

  return NULL;
}

static u8 BackrowHasUsableCourtOfJustice(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][i];

    if (zone->id == COURT_OF_JUSTICE && zone->isFaceUp == TRUE && CanUseMonsterEffect(zone))
      return TRUE;
  }

  return FALSE;
}

static u8 CanCourtOfJusticeUnlockFairyHandCards(void)
{
  if (!BackrowHasUsableCourtOfJustice())
    return FALSE;

  if (!ControlsFaceUpLevel1Fairy())
    return FALSE;

  if (!HandHasFairyMonster(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void UnlockFairyMonstersInHand(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnHands[ACTIVE_DUELIST][i];

    if (IsFairyMonster(zone->id))
      zone->isLocked = FALSE;
  }
}

static u8 IsCourtOfJusticeHandToFieldPlacement(void)
{
  return gDuelCursor.currentY == ACTIVE_DUELIST_MONSTER_ROW
      && gDuelCursor.destY == ACTIVE_DUELIST_HAND
      && GetTypeGroup(gSelectedCard.id) == TYPE_GROUP_MONSTER
      && IsFairyMonster(gSelectedCard.id)
      && gCourtOfJusticeIgnitionPending;
}

void CourtOfJustice_ResetTurnState(void)
{
  gCourtOfJusticeIgnitionPending = FALSE;
  gCourtOfJusticeHandPlacementActive = FALSE;
}

void CourtOfJustice_RefreshHandUnlocks(void)
{
  if (!CanCourtOfJusticeUnlockFairyHandCards()) {
    gCourtOfJusticeIgnitionPending = FALSE;
    return;
  }

  gCourtOfJusticeIgnitionPending = TRUE;
  UnlockFairyMonstersInHand();
  UpdateDuelGfxExceptField();
}

u8 CanUseCourtOfJusticeHandIgnition(void)
{
  if (!gCourtOfJusticeIgnitionPending)
    return FALSE;

  return CanCourtOfJusticeUnlockFairyHandCards();
}

u8 CourtOfJustice_HandSlotMayIgnition(u8 handSlot)
{
  if (!CanUseCourtOfJusticeHandIgnition())
    return FALSE;

  if (handSlot >= MAX_ZONES_IN_ROW)
    return FALSE;

  return IsFairyMonster(gTurnHands[ACTIVE_DUELIST][handSlot]->id);
}

u8 TryConsumeCourtOfJusticeIgnitionPlacement(void)
{
  struct DuelCard *courtZone;

  if (!IsCourtOfJusticeHandToFieldPlacement())
    return TRUE;

  if (!CanUseCourtOfJusticeHandIgnition())
    return FALSE;

  courtZone = FindActiveCourtOfJusticeZone();
  if (courtZone == NULL || !CanActivateCourtOfJusticeIgnition(courtZone))
    return FALSE;

  Duel_ShowEffectText(COURT_OF_JUSTICE);
  if (IsDuelOver() == TRUE)
    return FALSE;

  gCourtOfJusticeIgnitionPending = FALSE;
  gCourtOfJusticeHandPlacementActive = TRUE;
  MarkMonsterEffectUsed(courtZone);
  LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  return TRUE;
}

void CourtOfJustice_FinishHandPlacement(struct DuelCard *zone)
{
  if (!gCourtOfJusticeHandPlacementActive)
    return;

  gCourtOfJusticeHandPlacementActive = FALSE;
  zone->unk4 = 2;
}

u8 CanActivateCourtOfJusticeIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != COURT_OF_JUSTICE || zone->isFaceUp == FALSE)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!ControlsFaceUpLevel1Fairy())
    return FALSE;

  if (!HandHasFairyMonster(gTurnHands[ACTIVE_DUELIST]))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void ResolveCourtOfJusticeIgnition(struct DuelCard *zone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanActivateCourtOfJusticeIgnition(zone))
    return;

  Duel_ShowEffectText(COURT_OF_JUSTICE);

  if (IsDuelOver() == TRUE || !ControlsFaceUpLevel1Fairy())
    return;

  gCourtOfJusticeIgnitionPending = FALSE;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsFairyMonster, opts)
      == DUEL_ACTION_DUEL_OVER)
    return;

  MarkMonsterEffectUsed(zone);
  CourtOfJustice_RefreshHandUnlocks();
}

void TryUnlockHandForCourtOfJusticeIgnition(void)
{
  CourtOfJustice_RefreshHandUnlocks();
}

void TryEnableCourtOfJusticeIgnitionAfterPlacement(void)
{
  CourtOfJustice_RefreshHandUnlocks();
}

APPEND_TEXT void EffectCourtOfJustice(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (zone != NULL && zone->isLocked) {
    if (!CanActivateCourtOfJusticeIgnition(zone)) {
      if (!gHideEffectText)
        PlayMusic(SFX_FORBIDDEN);
      return;
    }

    ResolveCourtOfJusticeIgnition(zone);
    return;
  }

  Duel_ActivateContinuousZone(zone);
  CourtOfJustice_RefreshHandUnlocks();

  if (CanActivateCourtOfJusticeIgnition(zone)) {
    ResolveCourtOfJusticeIgnition(zone);
    return;
  }

  Duel_ShowEffectText(COURT_OF_JUSTICE);
}
