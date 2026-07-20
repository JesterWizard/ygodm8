#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 IsHandMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 HandHasMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
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

static u8 OppHasMonsterAtOrBelowAtk(u16 atkLimit)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    if (gCardData_NEW[zone->id].atk <= atkLimit)
      return TRUE;
  }

  return FALSE;
}

static s8 PickHandMonsterZone(u16 *outAtk)
{
  u8 i;
  s8 bestZone = -1;
  u16 bestAtk = 0;

  if (WhoseTurn() == DUEL_PLAYER) {
    s8 zone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsHandMonster);

    if (zone < 0)
      return -1;

    *outAtk = gCardData_NEW[gTurnHands[ACTIVE_DUELIST][zone]->id].atk;
    return zone;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;
    u16 atk;

    if (!IsHandMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestZone < 0 || atk > bestAtk) {
      bestAtk = atk;
      bestZone = (s8)i;
    }
  }

  if (bestZone < 0)
    return -1;

  *outAtk = bestAtk;
  return bestZone;
}

static void DestroyOpponentMonstersAtOrBelowAtk(u16 atkLimit)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    if (gCardData_NEW[zone->id].atk > atkLimit)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateARMED_DRAGON_LV7(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARMED_DRAGON_LV7)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_DRAGON_LV7)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasMonster();
}

void ActivateARMED_DRAGON_LV7Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 handZone;
  u16 discardedAtk;
  struct DuelCard *slot;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV7, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  handZone = PickHandMonsterZone(&discardedAtk);
  if (handZone < 0)
    return;

  slot = gTurnHands[ACTIVE_DUELIST][handZone];
  ClearZoneAndSendMonToGraveyard(slot, ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  if (OppHasMonsterAtOrBelowAtk(discardedAtk))
    DestroyOpponentMonstersAtOrBelowAtk(discardedAtk);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
