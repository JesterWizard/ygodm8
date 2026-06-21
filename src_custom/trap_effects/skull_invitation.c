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
  if (GetDuelistForZone(src) == 0xFF)
    return FALSE;
  /* Suppress when copying TO a hand slot (draw / return-to-hand): ClearZone
     on the source zone is a copy-to-field-zone, not a GY send. */
  if (Duel_ZoneIsHandSlot(dst))
    return TRUE;
  /* Suppress when copying FROM a hand slot (play card from hand to field):
     ClearZone on the source hand slot is the placement cleanup, not a GY send. */
  if (Duel_ZoneIsHandSlot(src))
    return TRUE;
  return FALSE;
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

  if (gHideEffectText)
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
