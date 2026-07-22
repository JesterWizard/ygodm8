#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const u16 sShiningSarcophagusMentions[] APPEND_RODATA = {
  DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE,
  DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC,
  GANDORA_G_THE_DRAGON_OF_DESTRUCTION,
  DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE,
  DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS,
  SILENT_SWORDSMAN_ZERO,
};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FieldHasShiningSarcophagus(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->id == SHINING_SARCOPHAGUS)
        return TRUE;
    }
  }

  return FALSE;
}

static u8 IsShiningSarcophagusMentionLvLe7(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE || cardId == SHINING_SARCOPHAGUS
      || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (gCardData_NEW[cardId].level == 0 || gCardData_NEW[cardId].level > 7)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sShiningSarcophagusMentions); i++) {
    if (cardId == sShiningSarcophagusMentions[i])
      return TRUE;
  }

  return FALSE;
}

static u16 FindMentionLvLe7InDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsShiningSarcophagusMentionLvLe7(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u16 HalfLpCost(void)
{
  return gDuelLifePoints[FixedDuelistForActive()] / 2;
}

static u8 FieldHasOtherCard(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      return TRUE;
    }
  }

  return FALSE;
}

static void BanishAllOtherFieldCards(struct DuelCard *protectedZone)
{
  u8 row;
  u8 col;
  u8 banished = FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = &gDuel.board[row][col];

      if (zone == protectedZone || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      /* destroy+banish → Duel_BanishZone (no GY). */
      if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      banished = TRUE;
    }
  }

  if (banished) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

unsigned char CanActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTION(void)
{
  struct DuelCard *zone;
  u16 cost;

  if (gMonEffect.id != GANDORA_G_THE_DRAGON_OF_DESTRUCTION)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != GANDORA_G_THE_DRAGON_OF_DESTRUCTION)
    return FALSE;

  /* +300 ATK/banished needs permanent/banish count hook.
   * OPT pay half LP → banish all other field → SS Lv≤7 Sarc mention. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  cost = HalfLpCost();
  if (cost == 0)
    return FALSE;

  if (!FieldHasOtherCard(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FindMentionLvLe7InDeck() != CARD_NONE;
}

void ActivateGANDORA_G_THE_DRAGON_OF_DESTRUCTIONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 cost;
  u16 ssId;
  struct DuelSummonOpts opts;

  Duel_ShowEffectTextTyped(GANDORA_G_THE_DRAGON_OF_DESTRUCTION, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cost = HalfLpCost();
  if (cost == 0)
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -(s32)cost, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  BanishAllOtherFieldCards(self);

  if (IsDuelOver() == TRUE)
    return;

  ssId = FindMentionLvLe7InDeck();
  if (ssId != CARD_NONE && !ArchlordKristya_IsSpecialSummonLocked()
      && FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, ssId, opts);
  }

  MarkMonsterEffectUsed(self);
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanSpecialSummonGandoraGTheDragonOfDestructionFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id
      != GANDORA_G_THE_DRAGON_OF_DESTRUCTION)
    return FALSE;

  if (!FieldHasShiningSarcophagus())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonGandoraGTheDragonOfDestructionFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonGandoraGTheDragonOfDestructionFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(GANDORA_G_THE_DRAGON_OF_DESTRUCTION, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonGandoraGTheDragonOfDestructionFromHand(u8 handZone);
u8 TrySpecialSummonGandoraGTheDragonOfDestructionFromHand(u8 handZone);
#endif
