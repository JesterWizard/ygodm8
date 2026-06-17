#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "skull_invitation.h"

#define SKULL_INVITATION_DAMAGE 300

extern u8 gSuppressSkullInvitationDamage;

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
  return GetDuelistForZone(src) != 0xFF && Duel_ZoneIsHandSlot(dst);
}

static void ApplySkullInvitationDamage(u8 fixedDuelist)
{
  Duel_ChangeLpWithPrefaceText(Duel_TurnDuelistMatchingWhoseTurn(fixedDuelist),
                               -SKULL_INVITATION_DAMAGE, SKULL_INVITATION, 3, FALSE);
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
  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectTextTyped(SKULL_INVITATION, 3);
  ResetCardEffectTextData();
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
