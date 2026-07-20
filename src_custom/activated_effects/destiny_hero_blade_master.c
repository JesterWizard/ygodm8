#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 FieldHasFaceUpDestinyHero(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (IsDestinyHeroMonster(zone->id) && IsFaceUpMonsterZone(zone))
      return TRUE;
  }

  return FALSE;
}

static void BuffFaceUpDestinyHeroes(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsDestinyHeroMonster(zone->id) || !IsFaceUpMonsterZone(zone))
      continue;

    /* ponytail: +2 tempStage (~1000 ATK, not exact +800); until EP clear needs
     * EP tempStage reset hook. */
    if (zone->tempStage < 126)
      zone->tempStage += 2;
  }
}

unsigned char CanActivateDESTINY_HERO_BLADE_MASTER(void)
{
  if (gMonEffect.id != DESTINY_HERO_BLADE_MASTER)
    return FALSE;

  /* Printed effect is hand discard during opp Battle Phase — use FromHand path. */
  return FALSE;
}

void ActivateDESTINY_HERO_BLADE_MASTEREffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_BLADE_MASTER, 2);
}

u8 CanActivateDESTINY_HERO_BLADE_MASTERFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DESTINY_HERO_BLADE_MASTER)
    return FALSE;

  /* ponytail: opponent Battle Phase gate not wired; allow when face-up D-HERO
   * on field. Ceiling: discard anytime from hand; upgrade: opp BP phase hook. */
  return FieldHasFaceUpDestinyHero();
}

u8 TryActivateDESTINY_HERO_BLADE_MASTERFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (!CanActivateDESTINY_HERO_BLADE_MASTERFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_BLADE_MASTER, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  BuffFaceUpDestinyHeroes();
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  return TRUE;
}
