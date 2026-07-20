#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDinoLevel4OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(cardId, TYPE_DINOSAUR))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level <= 4;
}

static u16 FindDeckDinoTarget(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDinoLevel4OrLower(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateBABYCERASAURUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != BABYCERASAURUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != BABYCERASAURUS)
    return FALSE;

  /* ponytail: destroyed-by-effect→GY trigger needs destroy hook.
   * Ceiling: once via usage if Lv≤4 Dino in Deck and open MMZ. */
  if (!CanUseMonsterEffect(zone) || ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FindDeckDinoTarget() != CARD_NONE
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateBABYCERASAURUSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(BABYCERASAURUS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindDeckDinoTarget();
  if (cardId == CARD_NONE || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(FALSE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts);
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
}
