#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void UpdateDuelGfxExceptField(void);

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static u8 IsArcanaForce(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 BanishFirstArcanaFromGy(u8 fixedDuelist)
{
  u8 i;
  u8 count;
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (!IsArcanaForce(cardId))
      return CARD_NONE;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  count = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < count; i++) {
    cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    if (!IsArcanaForce(cardId))
      continue;
    return Duel_BanishGraveyardAtFixed(fixedDuelist, i);
  }

  return CARD_NONE;
}

APPEND_TEXT void EffectARCANA_CALL(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  struct DuelCard *fieldAf = NULL;
  u16 banishedId;
  u8 fixedPlayer = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 fixedOpp = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  Duel_ShowTrapResponseText(ARCANA_CALL, gTrapEffectData.originCardId);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && IsArcanaForce(zone->id)) {
      fieldAf = zone;
      break;
    }
  }

  banishedId = BanishFirstArcanaFromGy(fixedPlayer);
  if (banishedId == CARD_NONE)
    banishedId = BanishFirstArcanaFromGy(fixedOpp);

  if (fieldAf != NULL && banishedId != CARD_NONE) {
    /* Mark copied identity until EP. */
    fieldAf->unk4 = (u8)(banishedId & 0xFF);

    /* ponytail: until EP, selected AF uses banished AF's coin effect — needs
     * End Phase clear + Arcana effect dispatch override. Ceiling: marks field
     * monster; GY Arcana banished. */
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
