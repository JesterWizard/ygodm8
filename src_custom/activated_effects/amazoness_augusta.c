#include "global.h"
#include "common-chax.h"
#include "amazoness_augusta.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAmazonessName[] APPEND_RODATA = "Amazoness";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ControllerHasFaceUpAugusta(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AMAZONESS_AUGUSTA)
      return TRUE;
  }

  return FALSE;
}

static u8 ZoneController(const struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &row, &col))
    return 0xFF;

  if (row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  if (row == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;
  return 0xFF;
}

static u8 IsOtherAmazonessMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == AMAZONESS_AUGUSTA)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAmazonessName)
      || Duel_IsAmazonessCard(cardId);
}

static u16 FindAmazonessInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsOtherAmazonessMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 MaterialsIncludeQueenOrEmpress(const u16 *materialIds, u8 materialCount)
{
  u8 i;

  if (materialIds == NULL)
    return FALSE;

  for (i = 0; i < materialCount; i++) {
    if (materialIds[i] == AMAZONESS_QUEEN || materialIds[i] == AMAZONESS_EMPRESS)
      return TRUE;
  }

  return FALSE;
}

u8 AmazonessAugusta_PreventsDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;
  if (zone->id == AMAZONESS_AUGUSTA || !Duel_IsAmazonessCard(zone->id))
    return FALSE;

  controller = ZoneController(zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  return ControllerHasFaceUpAugusta(controller);
}

u8 AmazonessAugusta_IsTargetImmune(const struct DuelCard *zone)
{
  return AmazonessAugusta_PreventsDestroy(zone);
}

void AmazonessAugusta_OnFusionSummoned(struct DuelCard *zone, const u16 *materialIds,
                                      u8 materialCount)
{
  u16 cardId;
  struct DuelSummonOpts opts;

  if (zone == NULL || zone->id != AMAZONESS_AUGUSTA)
    return;

  if (MaterialsIncludeQueenOrEmpress(materialIds, materialCount) && zone->unk4 < 2)
    zone->unk4 = 2;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  cardId = FindAmazonessInDeck();
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_AUGUSTA, 2);

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateAMAZONESS_AUGUSTA(void)
{
  /* Continuous protect + Fusion Summon trigger (no field OPT). */
  return FALSE;
}

void ActivateAMAZONESS_AUGUSTAEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_AUGUSTA, 2);
}
