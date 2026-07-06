#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "limiter_removal.h"
#include "mini_card.h"
#include "riryoku.h"
#include "spell_effects.h"

u8 gLimiterRemovalDestroyMask;
u8 gLimiterRemovalFixedMonsterRow;

static u8 MonsterQualifiesForLimiterRemoval(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == TYPE_MACHINE;
}

void ResetLimiterRemovalState(void)
{
  Duel_ResetDestroyMaskState(&gLimiterRemovalDestroyMask, &gLimiterRemovalFixedMonsterRow);
}

void DestroyLimiterRemovalMonstersAtEndOfTurn(void)
{
  Duel_DestroyMaskedMonstersFromState(&gLimiterRemovalDestroyMask, &gLimiterRemovalFixedMonsterRow);
}

APPEND_TEXT void EffectLimiterRemoval(void)
{
  u8 i;
  u8 monsterRow;
  u8 duelist = WhoseTurn();

  Duel_ResetDestroyMaskState(&gLimiterRemovalDestroyMask, &gLimiterRemovalFixedMonsterRow);
  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST, FALSE);

  monsterRow = Duel_FixedMonsterRowForDuelist(duelist);
  gLimiterRemovalFixedMonsterRow = monsterRow;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];

    if (!MonsterQualifiesForLimiterRemoval(zone->id))
      continue;

    {
      u16 atk = Duel_GetZoneFinalAtk(zone);
      if (atk > 0)
        AddRiryokuAtkDelta(zone, (s16)atk);
    }

    gLimiterRemovalDestroyMask |= (1 << i);
  }

  Duel_ShowEffectText(LIMITER_REMOVAL);
  RefreshFieldMonsterStatOverlays();
}
