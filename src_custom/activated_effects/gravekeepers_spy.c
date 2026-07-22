#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static const char sGravekeepersName[] APPEND_RODATA = "Gravekeeper";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsSpyTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sGravekeepersName))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.atk <= 1500;
}

static u16 FindDeckSpyTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (IsSpyTarget(gDuelDecks[fixedDuelist].cards[i])
        && !Duel_CardCannotBeSpecialSummoned(gDuelDecks[fixedDuelist].cards[i]))
      return gDuelDecks[fixedDuelist].cards[i];
  }

  return CARD_NONE;
}

unsigned char CanActivateGRAVEKEEPERS_SPY(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_SPY)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_SPY)
    return FALSE;

  /* FLIP trigger needs flip hook. */
  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FindDeckSpyTarget() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateGRAVEKEEPERS_SPYEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_SPY, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckSpyTarget();
  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
