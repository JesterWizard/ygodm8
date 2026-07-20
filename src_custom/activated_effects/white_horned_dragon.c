#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

#define WHITE_HORNED_MAX_BANISH 5

static u8 IsSpellCard(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_SPELL;
}

static u8 OppGySpellCount(void)
{
  u8 fixedDuelist = DUEL_OPPONENT;
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsSpellCard(cardId) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsSpellCard(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 BanishUpToFiveOppGySpells(void)
{
  u8 fixedDuelist = DUEL_OPPONENT;
  u8 banished = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsSpellCard(cardId))
      return 0;

    Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < WHITE_HORNED_MAX_BANISH;
       i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsSpellCard(cardId))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    banished++;
  }

  return banished;
}

unsigned char CanActivateWHITE_HORNED_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != WHITE_HORNED_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != WHITE_HORNED_DRAGON)
    return FALSE;

  /* ponytail: on-Normal/Special Summon trigger needs summon hook. Ceiling: OPT
   * banish up to 5 opp GY Spells + tempStage once via usage. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OppGySpellCount() > 0;
}

void ActivateWHITE_HORNED_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 banished;

  Duel_ShowEffectTextTyped(WHITE_HORNED_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  banished = BanishUpToFiveOppGySpells();
  if (banished == 0)
    return;

  /* ponytail: +1 tempStage per banished (~500 ATK each, not exact +300). */
  if (self->tempStage < 127 - (s8)banished)
    self->tempStage += (s8)banished;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
