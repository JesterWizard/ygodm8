#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "card.h"
#include "duel.h"
#include "splendid_venus.h"

extern unsigned char IsSkillDrainActiveOnField(void);

static u8 ZoneHasFaceUpSplendidVenus(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == THE_SPLENDID_VENUS && zone->isFaceUp;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

u8 IsSplendidVenusActiveOnField(void)
{
  u8 col;

  if (IsSkillDrainActiveOnField())
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (ZoneHasFaceUpSplendidVenus(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col])
        || ZoneHasFaceUpSplendidVenus(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

u8 GetSplendidVenusControllerDuelist(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (ZoneHasFaceUpSplendidVenus(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      return FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (ZoneHasFaceUpSplendidVenus(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      return FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  }

  return 0xFF;
}

u8 TheSplendidVenus_DuelistHasNegationImmunity(u8 fixedDuelist)
{
  u8 controller;

  if (!IsSplendidVenusActiveOnField())
    return FALSE;

  controller = GetSplendidVenusControllerDuelist();
  return controller != 0xFF && controller == fixedDuelist;
}

s8 SplendidVenus_AdjustStage(s8 stage, u16 cardId)
{
  const CardData *card;

  if (!IsSplendidVenusActiveOnField() || cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return stage;

  card = &gCardData_NEW[cardId];
  if (card->type >= TYPE_SPELL || card->type == TYPE_FAIRY)
    return stage;

  return stage - 1;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void SplendidVenus_SelfCheck(void)
{
  if (SplendidVenus_AdjustStage(0, CARD_NONE) != 0)
    while (1)
      ;
  if (SplendidVenus_AdjustStage(2, CARD_NONE) != 2)
    while (1)
      ;
}
#endif
