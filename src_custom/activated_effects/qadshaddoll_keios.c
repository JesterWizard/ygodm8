#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 IsShaddollMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

static u8 IsHandShaddollMonster(u16 cardId)
{
  return IsShaddollMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId);
}

static u8 HandHasShaddollMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsHandShaddollMonster(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateQADSHADDOLL_KEIOS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != QADSHADDOLL_KEIOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != QADSHADDOLL_KEIOS)
    return FALSE;

  /* FLIP vs sent-by-effect exclusivity + mill ATK gain need flip/send
   * hooks. OPT SS 1 Shaddoll from hand face-up DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasShaddollMonster();
}

void ActivateQADSHADDOLL_KEIOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(QADSHADDOLL_KEIOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!HandHasShaddollMonster() || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsHandShaddollMonster, opts)
      != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
