#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "skull_invitation.h"

#define SKULL_INVITATION_DAMAGE 300

extern u8 gSuppressSkullInvitationDamage;

static u8 ZoneIsHandSlot(const struct DuelCard *zone)
{
  u8 i;
  u8 j;

  if (zone == NULL)
    return FALSE;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[PLAYER_HAND][i] == zone)
      return TRUE;
  }

  for (i = 0; i < 2; i++) {
    for (j = 0; j < MAX_ZONES_IN_ROW; j++) {
      if (gTurnHands[i][j] == zone)
        return TRUE;
    }
  }

  return FALSE;
}

u8 IsActivatedSkullInvitationZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == SKULL_INVITATION && zone->isFaceUp == TRUE;
}

u8 IsSkullInvitationActiveOnField(void)
{
  u8 row;
  u8 i;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      if (IsActivatedSkullInvitationZone(gFixedZones[row][i]))
        return TRUE;
    }
  }

  return FALSE;
}

u8 ShouldSuppressSkullInvitationDamageOnCopy(const struct DuelCard *dst, const struct DuelCard *src)
{
  return GetDuelistForZone(src) != 0xFF && ZoneIsHandSlot(dst);
}

static void ApplySkullInvitationDamage(u8 fixedDuelist)
{
  u8 hideEffectText = gHideEffectText;

  if (fixedDuelist == DUEL_PLAYER)
    SetPlayerLifePointsToSubtract(SKULL_INVITATION_DAMAGE);
  else
    SetOpponentLifePointsToSubtract(SKULL_INVITATION_DAMAGE);

  if (!hideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SKULL_INVITATION;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }

  gHideEffectText = TRUE;
  HandleAtkAndLifePointsAction();
  gHideEffectText = hideEffectText;
  CheckLoserFlags();
}

void TryApplySkullInvitationOnFieldLeave(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 suppress = gSuppressSkullInvitationDamage;

  gSuppressSkullInvitationDamage = FALSE;

  if (suppress)
    return;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!IsSkullInvitationActiveOnField())
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return;

  ApplySkullInvitationDamage(fixedDuelist);
}

static void ActivateSkullInvitationZone(struct DuelCard *zone)
{
  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(3);
    gCardEffectTextData.cardId = SKULL_INVITATION;
    ActivateCardEffectText();
    ResetCardEffectTextData();
  }
}

void TryActivateSkullInvitationOnOpponentTurnStart(void)
{
  u8 i;
  struct DuelCard *zone;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    zone = gTurnZones[INACTIVE_DUELIST_BACKROW][i];
    if (zone->id != SKULL_INVITATION || zone->isFaceUp != FALSE)
      continue;

    ActivateSkullInvitationZone(zone);
    return;
  }
}

APPEND_TEXT void EffectSkullInvitation(void)
{
  ActivateSkullInvitationZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1]);
}
