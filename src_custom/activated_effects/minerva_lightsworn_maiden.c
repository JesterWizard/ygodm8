#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

#define MINERVA_DISTINCT_CAP 16

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 CountDistinctLightswornNamesInGy(u8 fixedDuelist)
{
  u16 seen[MINERVA_DISTINCT_CAP];
  u8 distinct = 0;
  u8 i;
  u8 j;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornMonster(cardId) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u8 already = FALSE;

    if (!IsLightswornMonster(cardId))
      continue;

    for (j = 0; j < distinct; j++) {
      if (seen[j] == cardId) {
        already = TRUE;
        break;
      }
    }

    if (already)
      continue;

    if (distinct >= MINERVA_DISTINCT_CAP)
      break;

    seen[distinct++] = cardId;
  }

  return distinct;
}

static u8 IsLightDragonSearchTarget(u16 cardId, u8 maxLevel)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  if (gCardInfo.attribute != ATTRIBUTE_LIGHT)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_DRAGON))
    return FALSE;

  if (gCardData_NEW[cardId].level == 0 || gCardData_NEW[cardId].level > maxLevel)
    return FALSE;

  return TRUE;
}

static u16 FindLightDragonInDeck(u8 maxLevel)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  if (maxLevel == 0)
    return CARD_NONE;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsLightDragonSearchTarget(cardId, maxLevel))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateMINERVA_LIGHTSWORN_MAIDEN(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 maxLevel;

  if (gMonEffect.id != MINERVA_LIGHTSWORN_MAIDEN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != MINERVA_LIGHTSWORN_MAIDEN)
    return FALSE;

  /* Normal Summon mill 4 via TryMinervaLightswornMaidenOnNormalSummon.
   * Field OPT search LIGHT Dragon Lv≤ distinct LS names in GY (EffectOpt). */
  if (EffectOpt_IsUsed(MINERVA_LIGHTSWORN_MAIDEN))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  maxLevel = CountDistinctLightswornNamesInGy(fixedDuelist);
  return FindLightDragonInDeck(maxLevel) != CARD_NONE;
}

void ActivateMINERVA_LIGHTSWORN_MAIDENEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 maxLevel;
  u16 searchId;

  Duel_ShowEffectTextTyped(MINERVA_LIGHTSWORN_MAIDEN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(MINERVA_LIGHTSWORN_MAIDEN))
    return;

  maxLevel = CountDistinctLightswornNamesInGy(fixedDuelist);
  searchId = FindLightDragonInDeck(maxLevel);
  if (searchId == CARD_NONE)
    return;

  if (Duel_AddDeckCardToHand(ACTIVE_DUELIST, searchId, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(MINERVA_LIGHTSWORN_MAIDEN);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
