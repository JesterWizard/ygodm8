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

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
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

  /* ponytail: GY banish destroy on Lv8 D-HERO SS FALSE.
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
