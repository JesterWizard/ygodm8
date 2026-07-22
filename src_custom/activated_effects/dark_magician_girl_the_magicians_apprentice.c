#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 HandHasOtherCard(u8 selfHandZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (i == selfHandZone)
      continue;

    if (SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i)->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 DiscardOtherCardExceptZone(u8 exceptZone)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    struct DuelCard *slot;

    if (i == exceptZone)
      continue;

    slot = SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], i);
    if (slot->id == CARD_NONE)
      continue;

    return Duel_DestroyZone(slot, ACTIVE_DUELIST, TRUE) != DUEL_ACTION_DUEL_OVER;
  }

  return FALSE;
}

void TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE)
    return;

  if (EffectOpt_IsUsed(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  if (Duel_FindDeckCardIndex(turnDuelist, SHINING_SARCOPHAGUS) < 0)
    return;

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE, 8);

  if (Duel_AddDeckCardToHand(turnDuelist, SHINING_SARCOPHAGUS, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateDARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE)
    return FALSE;

  /* On-NS/SS search via TryDarkMagicianGirlTheMagiciansApprenticeOnMonsterPlacement.
   * OPT add Shining Sarcophagus (shares EffectOpt).
   * Name=DMG GY +300 mention FALSE. */
  if (EffectOpt_IsUsed(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return Duel_FindDeckCardIndex(ACTIVE_DUELIST, SHINING_SARCOPHAGUS) >= 0;
}

void ActivateDARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE))
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, SHINING_SARCOPHAGUS, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id
      != DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE)
    return FALSE;

  if (!HandHasOtherCard(handZone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (!DiscardOtherCardExceptZone(handZone))
    return FALSE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  /* Name=Dark Magician Girl via DarkMagicianGirlTheMagiciansApprentice_TreatsNameAsDarkMagicianGirl
   * + Duel_ZoneEffectCardId. */
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(u8 handZone);
u8 TrySpecialSummonDarkMagicianGirlTheMagiciansApprenticeAltFromHand(u8 handZone);
#endif
