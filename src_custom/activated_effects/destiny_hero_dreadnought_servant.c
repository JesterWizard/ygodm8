#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsLevel8DestinyHero(u16 cardId)
{
  if (!IsDestinyHeroMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level == 8;
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

static s8 FindServantInGy(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_DREADNOUGHT_SERVANT)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DREADNOUGHT_SERVANT)
      return (s8)i;
  }

  return -1;
}

static void ReturnCardToDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

/* ponytail: auto-pick first opp card; upgrade: PickZone targeting. */
static struct DuelCard *FindOppCardToPlaceOnDeck(u8 summonerTurn)
{
  u8 oppTurn = summonerTurn == ACTIVE_DUELIST ? INACTIVE_DUELIST : ACTIVE_DUELIST;
  u8 monRow = oppTurn == ACTIVE_DUELIST ? ACTIVE_DUELIST_MONSTER_ROW
                                        : INACTIVE_DUELIST_MONSTER_ROW;
  u8 backRow = oppTurn == ACTIVE_DUELIST ? ACTIVE_DUELIST_BACKROW : INACTIVE_DUELIST_BACKROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monRow][col];

    if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
      return zone;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[backRow][col];

    if (zone != NULL && zone->id != CARD_NONE && !IsGodCard(zone->id))
      return zone;
  }

  return NULL;
}

void TryDestinyHeroDreadnoughtServantOnMonsterPlacement(struct DuelCard *zone,
                                                        enum DuelSummonMode mode)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 gyIndex;
  struct DuelCard *target;
  u16 cardId;
  u8 oppFixed;

  if (zone == NULL || !IsLevel8DestinyHero(zone->id) || !SummonModeIsSpecial(mode))
    return;
  if (EffectOpt_IsUsed(DESTINY_HERO_DREADNOUGHT_SERVANT))
    return;
  if (gHideEffectText)
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  gyIndex = FindServantInGy(fixedDuelist);
  if (gyIndex < 0)
    return;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  target = FindOppCardToPlaceOnDeck(turnDuelist);
  if (target == NULL)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_SERVANT, 8);
  if (IsDuelOver() == TRUE)
    return;

  EffectOpt_MarkUsed(DESTINY_HERO_DREADNOUGHT_SERVANT);

  if (GraveyardExpand_IsEnabled())
    Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex);
  else
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;

  oppFixed = GetDuelistForZone(target);
  if (oppFixed > DUEL_OPPONENT)
    oppFixed = fixedDuelist == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  cardId = target->id;
  ClearZone(target);
  ReturnCardToDeckTop(oppFixed, cardId);
  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 IsFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  return GetSpellType(cardId) == SPELL_TYPE_INVALID;
}

static u8 ControlsDestinyHeroOrFieldSpell(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && IsDestinyHeroMonster(zone->id))
      return TRUE;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone != NULL && IsFieldSpell(zone->id) && IsCardFaceUp(zone))
      return TRUE;
  }

  return FALSE;
}

static struct DuelCard *FindOwnDestroyTarget(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone == NULL || zone == self || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      return zone;
    }
  }

  return NULL;
}

static u8 AddPolymerizationFromDeck(void)
{
  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, POLYMERIZATION) < 0)
    return FALSE;

  return Duel_AddDeckCardToHand(ACTIVE_DUELIST, POLYMERIZATION, TRUE) == DUEL_ACTION_OK;
}

unsigned char CanActivateDESTINY_HERO_DREADNOUGHT_SERVANT(void)
{
  if (gMonEffect.id != DESTINY_HERO_DREADNOUGHT_SERVANT)
    return FALSE;

  /* GY banish → opp Deck top on Lv8 D-HERO SS via
   * TryDestinyHeroDreadnoughtServantOnMonsterPlacement.
   * Ceiling: FromHand if control D-HERO or Field Spell → SS, destroy 1, add Poly. */
  return FALSE;
}

u8 CanSpecialSummonDestinyHeroDreadnoughtServantFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DESTINY_HERO_DREADNOUGHT_SERVANT)
    return FALSE;

  if (!ControlsDestinyHeroOrFieldSpell())
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDestinyHeroDreadnoughtServantFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  struct DuelCard *self;
  struct DuelCard *destroy;
  s8 empty;

  if (!CanSpecialSummonDestinyHeroDreadnoughtServantFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_SERVANT, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (empty < 0)
    return FALSE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  self = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][empty];
  destroy = FindOwnDestroyTarget(self);
  if (destroy != NULL) {
    if (Duel_DestroyZone(destroy, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return TRUE;

    NotifyDynamicEquipFieldChanged();
    AddPolymerizationFromDeck();
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  return TRUE;
}

void ActivateDESTINY_HERO_DREADNOUGHT_SERVANTEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADNOUGHT_SERVANT, 2);
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDestinyHeroDreadnoughtServantFromHand(u8 handZone);
u8 TrySpecialSummonDestinyHeroDreadnoughtServantFromHand(u8 handZone);
#endif
