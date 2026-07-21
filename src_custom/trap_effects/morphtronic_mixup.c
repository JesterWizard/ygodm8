#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static u8 IsMorphtronic(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 CountFaceUpMorphtronic(void)
{
  u8 col;
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && IsMorphtronic(zone->id))
      count++;
  }

  return count;
}

APPEND_TEXT void EffectMORPHTRONIC_MIXUP(void)
{
  u8 r;
  u8 c;
  struct DuelCard *picked[2];
  u8 pickCount = 0;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 oppBack = WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 destroyIdx;

  Duel_ShowTrapResponseText(MORPHTRONIC_MIXUP, gTrapEffectData.originCardId);

  if (CountFaceUpMorphtronic() < 2) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  /* Select up to 2 opp cards (auto first available). */
  for (r = 0; r < 4 && pickCount < 2; r++) {
    if (r != oppRow && r != oppBack)
      continue;
    for (c = 0; c < MAX_ZONES_IN_ROW && pickCount < 2; c++) {
      struct DuelCard *zone = gFixedZones[r][c];

      if (zone != NULL && zone->id != CARD_NONE)
        picked[pickCount++] = zone;
    }
  }

  if (pickCount > 0) {
    /* Opp chooses which of the 2 to destroy — AI/random. */
    destroyIdx = (pickCount == 1) ? 0 : RandRangeU8(0, pickCount - 1);
    Duel_DestroyZone(picked[destroyIdx], ACTIVE_DUELIST, FALSE);
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();

}
