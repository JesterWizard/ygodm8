#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "hyper_hammerhead.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct HyperHammerheadActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct HyperHammerheadActionData sActionData;

void ClearHyperHammerheadPending(void) {
  gPendingHyperHammerheadRow = HYPER_HAMMERHEAD_PENDING_NONE;
  gPendingHyperHammerheadCol = 0;
}

static u8 CanReturnZoneMonsterToOwnerHand(struct DuelCard *zone) {
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return FALSE;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return NumEmptyZonesInRow(gTurnHands[turnDuelist]) > 0;
  }

  return FALSE;
}

static u8 MarkPendingReturn(u8 targetRow, u8 targetCol) {
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (!CanReturnZoneMonsterToOwnerHand(zone))
    return FALSE;

  gPendingHyperHammerheadRow = targetRow;
  gPendingHyperHammerheadCol = targetCol;
  return TRUE;
}

void ResolveHyperHammerheadBattleEffect(void) {
  u8 targetRow;
  u8 targetCol;
  struct DuelCard *zone;

  targetRow = gPendingHyperHammerheadRow;
  if (targetRow == HYPER_HAMMERHEAD_PENDING_NONE)
    return;

  targetCol = gPendingHyperHammerheadCol;
  ClearHyperHammerheadPending();

  zone = gFixedZones[targetRow][targetCol];
  if (zone->id == CARD_NONE)
    return;

  Duel_ShowEffectText(HYPER_HAMMERHEAD);

  if (zone->id == CARD_NONE)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, TRUE) != DUEL_ACTION_OK)
    return;
}

void ApplyHyperHammerheadBattleEffect(void) {
  if (gHideEffectText)
    return;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.playerCardId == HYPER_HAMMERHEAD) {
    if (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      return;

    if (!MarkPendingReturn(sActionData.opponentMonsterRow, sActionData.unk16))
      return;
  } else if (sActionData.opponentCardId == HYPER_HAMMERHEAD) {
    if (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      return;

    if (!MarkPendingReturn(sActionData.playerMonsterRow, sActionData.unkA))
      return;
  } else {
    return;
  }

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveHyperHammerheadBattleEffect();
}
