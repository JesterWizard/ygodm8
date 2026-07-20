#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

static u8 CountAromaOnField(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && IsAromaMonster(zone->id))
      count++;
  }

  return count;
}

static u8 OppGyCardCount(void)
{
  u8 fixedDuelist = FixedDuelistForActive() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (!GraveyardExpand_IsEnabled()) {
    return gDuel.duelistbattleState[fixedDuelist].graveyard != CARD_NONE ? 1 : 0;
  }

  return GraveyardExpand_GetCount(fixedDuelist);
}

static u8 BanishUpToNFromOppGy(u8 max)
{
  u8 fixedDuelist = FixedDuelistForActive() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 banished = 0;
  u8 i;

  if (max == 0)
    return 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == CARD_NONE)
      return 0;

    Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < max; i--) {
    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1) == CARD_NONE)
      break;

    banished++;
  }

  if (banished > 0)
    GraveyardExpand_RefreshDisplay();

  return banished;
}

unsigned char CanActivateAROMAGE_MARJORAM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_MARJORAM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_MARJORAM)
    return FALSE;

  /* ponytail: FromHand SS on Plant destroy + LP-gain trigger need destroy/LP hooks.
   * Ceiling: OPT banish up to Aroma-count cards from opp GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountAromaOnField() > 0 && OppGyCardCount() > 0;
}

void ActivateAROMAGE_MARJORAMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 max;

  Duel_ShowEffectTextTyped(AROMAGE_MARJORAM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  max = CountAromaOnField();
  if (max == 0)
    return;

  if (BanishUpToNFromOppGy(max) == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
