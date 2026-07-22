#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "deep_sea_diva.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static u8 IsDivaDeckTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardHasMonsterType(cardId, TYPE_SEA_SERPENT))
    return FALSE;
  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 1 && gCardInfo.level <= 3;
}

static u16 FindDeckDivaTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsDivaDeckTarget(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

static u8 TrySpecialSummonDivaTargetFromDeck(struct DuelCard *self)
{
  struct DuelSummonOpts opts;
  u16 cardId;

  if (self == NULL || IsDuelOver() == TRUE)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  cardId = FindDeckDivaTarget();
  if (cardId == CARD_NONE
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  Duel_ShowEffectTextTyped(DEEP_SEA_DIVA, 2);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return FALSE;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  return TRUE;
}

void TryDeepSeaDivaOnNormalSummon(struct DuelCard *zone, enum DuelSummonMode mode)
{
  if (zone == NULL || zone->id != DEEP_SEA_DIVA || SummonModeIsSpecial(mode))
    return;

  if (zone->effectUsedThisTurn)
    return;

  (void)TrySpecialSummonDivaTargetFromDeck(zone);
}

unsigned char CanActivateDEEP_SEA_DIVA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DEEP_SEA_DIVA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DEEP_SEA_DIVA)
    return FALSE;

  /* NS SS via TryDeepSeaDivaOnNormalSummon. Ceiling: OPT duplicate if NS already
   * consumed effectUsedThisTurn. */
  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FindDeckDivaTarget() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateDEEP_SEA_DIVAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  (void)TrySpecialSummonDivaTargetFromDeck(self);
}
