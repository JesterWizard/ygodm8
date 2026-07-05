#include "global.h"
#include "common-chax.h"
#include "constants/custom_field_spells.h"
#include "custom_field_spell.h"
#include "divine_sanctuary.h"
#include "card.h"
#include "duel_helpers.h"

#define DIVINE_SANCTUARY_ATK_PENALTY 500

u8 IsDivineSanctuaryActive(void)
{
  return gActiveCustomFieldSpellId == CUSTOM_FIELD_SPELL_DIVINE_SANCTUARY;
}

u8 IsActivatedDivineSanctuaryZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == DIVINE_SANCTUARY && zone->isFaceUp == TRUE;
}

static u8 IsFairyMonster(u16 cardId)
{
  const CardData *card;

  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  card = &gCardData_NEW[cardId];

  if (card->color != NORMAL_CARD && card->color != EFFECT_CARD
      && card->color != FUSION_CARD && card->color != RITUAL_CARD)
    return FALSE;

  return card->type == TYPE_FAIRY;
}

int ApplyDivineSanctuaryTributeOverride(u16 cardId, int requiredTributes)
{
  if (!IsDivineSanctuaryActive() || !IsFairyMonster(cardId))
    return requiredTributes;

  SetCardInfo(cardId);

  if (gCardInfo.level <= 6)
    return 0;

  if (gCardInfo.level >= 7)
    return 1;

  return requiredTributes;
}

void ApplyDivineSanctuaryFieldStatPenalty(u16 cardId, u16 *atk, u16 *def)
{
  (void)def;

  if (!IsDivineSanctuaryActive() || IsFairyMonster(cardId) || atk == NULL)
    return;

  if (*atk == 0xFFFF)
    return;

  if (*atk > DIVINE_SANCTUARY_ATK_PENALTY)
    *atk -= DIVINE_SANCTUARY_ATK_PENALTY;
  else
    *atk = 0;
}

void ApplyDivineSanctuaryFieldStatPenaltyForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return;

  ApplyDivineSanctuaryFieldStatPenalty(zone->id, &gCardInfo.atk, &gCardInfo.def);
}

#if defined(DIVINE_SANCTUARY_SELF_CHECK)
void DivineSanctuary_SelfCheck(void)
{
  if (ApplyDivineSanctuaryTributeOverride(TINY_ANGEL, 1) != 0)
    while (1)
      ;
  if (ApplyDivineSanctuaryTributeOverride(GUARDIAN_ANGEL_JOAN, 2) != 1)
    while (1)
      ;
}
#endif
