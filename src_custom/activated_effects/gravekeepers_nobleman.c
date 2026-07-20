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

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeepersName);
}

static u16 FindOtherGravekeeperInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGravekeeperMonster(cardId) && cardId != GRAVEKEEPERS_NOBLEMAN
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateGRAVEKEEPERS_NOBLEMAN(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != GRAVEKEEPERS_NOBLEMAN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GRAVEKEEPERS_NOBLEMAN)
    return FALSE;

  /* ponytail: destroyed-by-battle trigger needs battle/destroy hook.
   * Ceiling: OPT SS 1 GK from Deck face-down DEF except Nobleman. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindOtherGravekeeperInDeck() != CARD_NONE;
}

void ActivateGRAVEKEEPERS_NOBLEMANEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(GRAVEKEEPERS_NOBLEMAN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindOtherGravekeeperInDeck();
  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  /* ponytail: no DUEL_SUMMON_SPECIAL_FACE_DOWN_DEF — NORMAL_SET stand-in. */
  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_NORMAL_SET;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
