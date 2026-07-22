#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "gladiator_beast_battled.h"
#include "monster_effect_usage.h"
#include "extra_attack_unk4.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define GLADIATOR_BEAST_HOPLOMUS_TAG_DEF 2400
#define GLADIATOR_BEAST_LAQUARI_TAG_ATK 2100

static u8 sGladiatorBeastBattlePhaseActive APPEND_DATA = {FALSE};

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

struct GladiatorBeastBattledActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct GladiatorBeastBattledActionData sActionData;

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static void MarkBattledZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (zone != NULL && zone->id != CARD_NONE)
    zone->unk4 |= GLADIATOR_BEAST_BATTLED_MARK;
}

static void MarkGladiatorFromBattle(u16 cardId, u8 fixedRow, u8 fixedCol)
{
  if (!IsGladiatorBeastMonster(cardId))
    return;

  MarkBattledZone(fixedRow, fixedCol);
}

u8 GladiatorBeast_InBattlePhase(void)
{
  return sGladiatorBeastBattlePhaseActive;
}

void GladiatorBeast_MarkBattlePhaseActive(void)
{
  sGladiatorBeastBattlePhaseActive = TRUE;
}

void GladiatorBeast_ClearBattlePhaseActive(void)
{
  sGladiatorBeastBattlePhaseActive = FALSE;
}

u8 GladiatorBeast_CanActivateTagOutEffect(const struct DuelCard *zone)
{
  if (!GladiatorBeast_InBattlePhase())
    return FALSE;

  return GladiatorBeast_ZoneBattledThisBattlePhase(zone);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 FindOtherGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void ShuffleSelfToDeck(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId = self->id;

  ClearZone(self);
  ReturnCardToDeckTop(fixedDuelist, cardId);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);
  NotifyDynamicEquipFieldChanged();
}

u8 GladiatorBeast_HasOtherMonsterInDeck(u16 excludeId)
{
  return FindOtherGladiatorBeastInDeck(excludeId) != CARD_NONE;
}

u8 GladiatorBeast_CanActivateDeckTagOut(u16 cardId, struct DuelCard *zone)
{
  if (zone == NULL || zone->id != cardId)
    return FALSE;

  if (!GladiatorBeast_CanActivateTagOutEffect(zone))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return GladiatorBeast_HasOtherMonsterInDeck(cardId);
}

void GladiatorBeast_ActivateDeckTagOut(struct DuelCard *self, u16 selfCardId)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 tagId;

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfToDeck(self);

  if (IsDuelOver() == TRUE)
    return;

  tagId = FindOtherGladiatorBeastInDeck(selfCardId);
  if (tagId == CARD_NONE)
    return;

  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, tagId, opts);
  GladiatorBeast_MarkTagSummonedZone(tagId);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void GladiatorBeast_ActivateDeckTagOutDraw(struct DuelCard *self, u16 selfCardId)
{
  (void)selfCardId;

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfToDeck(self);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 GladiatorBeast_CanActivateTagOutDraw(u16 cardId, struct DuelCard *zone)
{
  if (zone == NULL || zone->id != cardId)
    return FALSE;

  if (!GladiatorBeast_CanActivateTagOutEffect(zone))
    return FALSE;

  return CanUseMonsterEffect(zone);
}

void GladiatorBeast_MarkTagSummonedZone(u16 cardId)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= GLADIATOR_BEAST_TAG_SS_MARK;
      TryMarkBuiltInExtraAttackOnPlacement(zone);
      return;
    }
  }
}

void ApplyGladiatorBeastTagOutStatBoostToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if ((zone->unk4 & GLADIATOR_BEAST_TAG_SS_MARK) == 0)
    return;

  if (zone->id == GLADIATOR_BEAST_HOPLOMUS) {
    if (gCardInfo.def < GLADIATOR_BEAST_HOPLOMUS_TAG_DEF)
      gCardInfo.def = GLADIATOR_BEAST_HOPLOMUS_TAG_DEF;
    return;
  }

  if (zone->id == GLADIATOR_BEAST_LAQUARI
      && gCardInfo.atk < GLADIATOR_BEAST_LAQUARI_TAG_ATK) {
    gCardInfo.atk = GLADIATOR_BEAST_LAQUARI_TAG_ATK;
  }
}

u8 GladiatorBeast_ZoneBattledThisBattlePhase(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return (zone->unk4 & GLADIATOR_BEAST_BATTLED_MARK) != 0;
}

void ApplyGladiatorBeastBattledMarks(void)
{
  if (sActionData.id == 0)
    return;

  MarkGladiatorFromBattle(sActionData.playerCardId, sActionData.playerMonsterRow,
                          sActionData.unkA);
  MarkGladiatorFromBattle(sActionData.opponentCardId, sActionData.opponentMonsterRow,
                          sActionData.unk16);
}

void ClearGladiatorBeastBattledMarks(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL)
        zone->unk4 &= (u8)~GLADIATOR_BEAST_BATTLED_MARK;
    }
  }
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u16 FindGladiatorBeastInDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastMonster(cardId) && cardId != excludeId)
      return cardId;
  }

  return CARD_NONE;
}

u8 GladiatorBeast_DeckHasTwoDifferentGladiatorBeasts(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u16 first = CARD_NONE;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsGladiatorBeastMonster(cardId) || cardId == excludeId)
      continue;

    if (first == CARD_NONE) {
      first = cardId;
      continue;
    }

    if (cardId != first)
      return TRUE;
  }

  return FALSE;
}

void GladiatorBeast_SpecialSummonTwoFromDeck(u16 excludeId)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 first = CARD_NONE;
  u16 second = CARD_NONE;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsGladiatorBeastMonster(cardId) || cardId == excludeId)
      continue;

    if (first == CARD_NONE) {
      first = cardId;
      continue;
    }

    if (cardId != first) {
      second = cardId;
      break;
    }
  }

  if (first != CARD_NONE)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, first, opts);

  if (IsDuelOver() == TRUE)
    return;

  if (second != CARD_NONE)
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, second, opts);
}

void GladiatorBeast_ActivateDeckTagOutTwo(struct DuelCard *self, u16 selfCardId)
{
  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  ShuffleSelfToDeck(self);

  if (IsDuelOver() == TRUE)
    return;

  GladiatorBeast_SpecialSummonTwoFromDeck(selfCardId);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 AttackerDestroyedDefenderByBattle(u16 attackerId, u8 attackerFixed,
                                            u16 *outDef)
{
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return FALSE;

  if (attackerFixed == DUEL_PLAYER && sActionData.playerCardId == attackerId
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    *outDef = sActionData.opponentCardDefense;
    return TRUE;
  }

  if (attackerFixed == DUEL_OPPONENT && sActionData.opponentCardId == attackerId
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    *outDef = sActionData.playerCardDefense;
    return TRUE;
  }

  return FALSE;
}

void ApplyGladiatorBeastPermanentBattleEffects(void)
{
  u16 def;
  u8 turnDuelist;
  u16 deckCard;

  if (gHideEffectText)
    return;

  if (AttackerDestroyedDefenderByBattle(GLADIATOR_BEAST_SAMNITE, DUEL_PLAYER, &def)) {
    turnDuelist = TurnDuelistForFixed(DUEL_PLAYER);
    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      return;

    deckCard = FindGladiatorBeastInDeck(GLADIATOR_BEAST_SAMNITE);
    if (deckCard == CARD_NONE)
      return;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_SAMNITE, 2);
    Duel_AddDeckCardToHand(turnDuelist, deckCard, TRUE);
    return;
  }

  if (AttackerDestroyedDefenderByBattle(GLADIATOR_BEAST_SAMNITE, DUEL_OPPONENT, &def)) {
    turnDuelist = TurnDuelistForFixed(DUEL_OPPONENT);
    if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
      return;

    deckCard = FindGladiatorBeastInDeck(GLADIATOR_BEAST_SAMNITE);
    if (deckCard == CARD_NONE)
      return;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_SAMNITE, 2);
    Duel_AddDeckCardToHand(turnDuelist, deckCard, TRUE);
    return;
  }

  if (AttackerDestroyedDefenderByBattle(GLADIATOR_BEAST_GAIODIAZ, DUEL_PLAYER, &def)) {
    if (def == 0)
      return;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_GAIODIAZ, 2);
    Duel_ChangeLp(INACTIVE_DUELIST, -(s32)def, TRUE);
    return;
  }

  if (AttackerDestroyedDefenderByBattle(GLADIATOR_BEAST_GAIODIAZ, DUEL_OPPONENT, &def)) {
    if (def == 0)
      return;

    Duel_ShowEffectTextTyped(GLADIATOR_BEAST_GAIODIAZ, 2);
    Duel_ChangeLp(ACTIVE_DUELIST, -(s32)def, TRUE);
  }
}

#if !defined(__GNUC__)
void GladiatorBeastBattled_SelfCheck(void);
#endif

void GladiatorBeastBattled_SelfCheck(void)
{
  struct DuelCard fake;

  fake.id = GLADIATOR_BEAST_HOPLOMUS;
  fake.unk4 = GLADIATOR_BEAST_TAG_SS_MARK;
  SetCardInfo(fake.id);
  ApplyGladiatorBeastTagOutStatBoostToCardInfo(&fake);
  if (gCardInfo.def != GLADIATOR_BEAST_HOPLOMUS_TAG_DEF)
    return;
}
