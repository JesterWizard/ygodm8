#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 PickAttributeFromFirstOppMonster(u8 *outAttr)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
      continue;

    if (!(IsCardFaceUp(zone) || zone->isDefending == FALSE))
      continue;

    SetCardInfo(zone->id);
    *outAttr = gCardInfo.attribute;
    return TRUE;
  }

  return FALSE;
}

static u8 FieldHasFaceUpAttr(u8 attr)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      if (!(IsCardFaceUp(zone) || zone->isDefending == FALSE))
        continue;

      SetCardInfo(zone->id);
      if (gCardInfo.attribute == attr)
        return TRUE;
    }
  }

  return FALSE;
}

static void DestroyAllFaceUpWithAttr(u8 attr)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];
      u8 gyDuelist;

      if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
        continue;

      if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      if (!(IsCardFaceUp(zone) || zone->isDefending == FALSE))
        continue;

      SetCardInfo(zone->id);
      if (gCardInfo.attribute != attr)
        continue;

      gyDuelist = (row <= OPPONENT_MONSTER_ROW)
          ? (WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST)
          : (WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST);

      if (Duel_DestroyZone(zone, gyDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;
    }
  }
}

unsigned char CanActivateTUALATIN(void)
{
  struct DuelCard *zone;
  u8 attr;

  if (gMonEffect.id != TUALATIN)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != TUALATIN)
    return FALSE;

  /* ponytail: FromHand battle-wipe SS + Summon Attribute lock FALSE.
   * Ceiling: OPT destroy all face-up monsters of first opp monster's Attribute. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (!PickAttributeFromFirstOppMonster(&attr))
    return FALSE;

  return FieldHasFaceUpAttr(attr);
}

void ActivateTUALATINEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 attr;

  Duel_ShowEffectTextTyped(TUALATIN, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!PickAttributeFromFirstOppMonster(&attr))
    return;

  DestroyAllFaceUpWithAttr(attr);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
