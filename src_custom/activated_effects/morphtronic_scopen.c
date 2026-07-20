#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 IsLevel4MorphtronicInHand(u16 cardId)
{
  if (!IsMorphtronicMonster(cardId))
    return FALSE;

  return gCardData_NEW[cardId].level == 4;
}

static u8 HandHasLevel4Morphtronic(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsLevel4MorphtronicInHand(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsHandLevel4Morphtronic(u16 cardId)
{
  return IsLevel4MorphtronicInHand(cardId);
}

unsigned char CanActivateMORPHTRONIC_SCOPEN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != MORPHTRONIC_SCOPEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MORPHTRONIC_SCOPEN)
    return FALSE;

  /* ponytail: DEF Position → treat as Level 4 + EP destroy on ATK-mode SS need
   * position/EP hooks. Ceiling: ATK Position OPT SS 1 Lv4 Morphtronic from hand. */
  if (zone->isDefending)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return HandHasLevel4Morphtronic();
}

void ActivateMORPHTRONIC_SCOPENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  Duel_ShowEffectTextTyped(MORPHTRONIC_SCOPEN, 2);

  if (self == NULL || IsDuelOver() == TRUE || self->isDefending)
    return;

  if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsHandLevel4Morphtronic, opts)
      != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
