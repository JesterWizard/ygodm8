#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_room_of_nightmare.h"
#include "duel_helpers.h"
#include "imperial_order.h"
#include "spell_effects.h"

#define DARK_ROOM_DAMAGE 300

struct DarkRoomActionData {
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

extern struct DarkRoomActionData sActionData;

u8 IsActivatedDarkRoomZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == DARK_ROOM_OF_NIGHTMARE && zone->isFaceUp == TRUE;
}

static struct DuelCard *FindDarkRoomZone(u8 controller)
{
  u8 backrow = controller == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[backrow][i]->id == DARK_ROOM_OF_NIGHTMARE
        && !IsImperialOrderNegatingSpell(DARK_ROOM_OF_NIGHTMARE))
      return gFixedZones[backrow][i];
  }

  return NULL;
}

static void FlipDarkRoomFaceUpIfNeeded(struct DuelCard *zone)
{
  if (zone->isFaceUp == FALSE) {
    FlipCardFaceUp(zone);
    zone->isLocked = TRUE;
  }
}

void ClearDarkRoomPending(void)
{
  gPendingDarkRoomTarget = DARK_ROOM_PENDING_NONE;
  gSuppressDarkRoomDamage = FALSE;
}

static void DeclareLoserFlagsFromAction(void)
{
  if (sActionData.flags & 4)
    DeclareLoser(DUEL_PLAYER);
  if (sActionData.flags & 16)
    DeclareLoser(DUEL_OPPONENT);
}

static u8 ShouldDeferDarkRoomResolve(void)
{
  if (gHideEffectText)
    return FALSE;

  return gCardEffectTextData.cardId == CARD_NONE;
}

static void ApplyDarkRoomDamage(u8 targetDuelist)
{
  u8 hideEffectText = gHideEffectText;

  gSuppressDarkRoomDamage = TRUE;

  if (targetDuelist == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(DARK_ROOM_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(DARK_ROOM_DAMAGE);

  if (!hideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = DARK_ROOM_OF_NIGHTMARE;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }

  gHideEffectText = TRUE;
  HandleAtkAndLifePointsAction();
  gHideEffectText = hideEffectText;
  DeclareLoserFlagsFromAction();

  gSuppressDarkRoomDamage = FALSE;
}

static void ApplyDarkRoomForTarget(u8 targetDuelist)
{
  u8 controller = targetDuelist == DUEL_OPPONENT ? DUEL_PLAYER : DUEL_OPPONENT;
  struct DuelCard *zone = FindDarkRoomZone(controller);

  if (zone == NULL)
    return;

  FlipDarkRoomFaceUpIfNeeded(zone);
  ApplyDarkRoomDamage(targetDuelist);
}

void ResolveDarkRoomEffect(void)
{
  u8 target;

  if (gSuppressDarkRoomDamage || IsDuelOver() == TRUE)
    return;

  target = gPendingDarkRoomTarget;
  if (target == DARK_ROOM_PENDING_NONE)
    return;

  gPendingDarkRoomTarget = DARK_ROOM_PENDING_NONE;
  ApplyDarkRoomForTarget(target);
}

void TryApplyDarkRoomAfterEffectDamage(u8 targetDuelist)
{
  u8 controller;

  if (gSuppressDarkRoomDamage || IsDuelOver() == TRUE)
    return;

  controller = targetDuelist == DUEL_OPPONENT ? DUEL_PLAYER : DUEL_OPPONENT;
  if (FindDarkRoomZone(controller) == NULL)
    return;

  if (ShouldDeferDarkRoomResolve()) {
    gPendingDarkRoomTarget = targetDuelist;
    return;
  }

  ApplyDarkRoomForTarget(targetDuelist);
}

APPEND_TEXT void EffectDarkRoomOfNightmare(void)
{
  struct DuelCard *zone;

  if (gSpellEffectData.row1 == PLAYER_BACKROW || gSpellEffectData.row1 == OPPONENT_BACKROW)
    zone = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  else
    zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = DARK_ROOM_OF_NIGHTMARE;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }
}
