#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static u8 IsPlantMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_PLANT);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindDeckPlant(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsPlantMonster(gDuelDecks[fixedDuelist].cards[i])
        && !Duel_CardCannotBeSpecialSummoned(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

static u8 HasFaceUpPlantTribute(void)
{
  u8 col;
  u8 row = gMonEffect.row;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && zone->isFaceUp && IsPlantMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

unsigned char CanActivateLONEFIRE_BLOSSOM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LONEFIRE_BLOSSOM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LONEFIRE_BLOSSOM)
    return FALSE;

  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasFaceUpPlantTribute() && FindDeckPlant() != CARD_NONE
      && (NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) + 1 > 0);
}

void ActivateLONEFIRE_BLOSSOMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelCard *tribute = NULL;
  struct DuelSummonOpts opts;
  u16 plantId;
  u8 col;
  u8 row = gMonEffect.row;

  Duel_ShowEffectTextTyped(LONEFIRE_BLOSSOM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  /* Prefer tributing another Plant; else tribute self. */
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone != NULL && zone != self && zone->isFaceUp && IsPlantMonster(zone->id)) {
      tribute = zone;
      break;
    }
  }

  if (tribute == NULL && self->isFaceUp && IsPlantMonster(self->id))
    tribute = self;

  if (tribute == NULL)
    return;

  ClearZone(tribute);

  plantId = FindDeckPlant();
  if (plantId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, plantId, opts);

  /* If Lonefire itself remains, mark OPT used. */
  if (self != tribute && self->id == LONEFIRE_BLOSSOM)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
}
