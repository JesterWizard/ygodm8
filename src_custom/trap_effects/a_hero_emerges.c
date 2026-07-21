#include "global.h"
#include "common-chax.h"
#include "a_hero_emerges.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "draining_shield.h"
#include "duel_helpers.h"
#include "expanded_card_hand.h"

static u8 HandCardCanBeSpecialSummoned(u16 cardId, u8 duelist)
{
  u8 color;

  if (!Duel_CardIsMonster(cardId))
    return FALSE;
  if (Duel_CardCannotBeSpecialSummoned(cardId))
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  if (FirstEmptyZoneInRow(gTurnZones[Duel_TurnMonsterRowForDuelist(duelist)]) < 0)
    return FALSE;

  SetCardInfo(cardId);
  color = gCardInfo.color;
  /* ponytail: Extra Deck / Ritual need proper summon; treat as unsummonable from hand */
  if (color == FUSION_CARD || color == RITUAL_CARD || color == SYNCHRO_CARD
      || color == XYZ_CARD || color == LINK_CARD)
    return FALSE;

  return TRUE;
}

APPEND_TEXT void EffectAHeroEmerges(void)
{
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;
  struct DuelSummonOpts opts;

  SaveDrainingShieldAttackResume();

  Duel_ShowTrapResponseText(A_HERO_EMERGES, gTrapEffectData.originCardId);

  handZone = Duel_PickRandomHandZone(INACTIVE_DUELIST);
  if (handZone >= 0) {
    handSlot = ExpandedHand_ZoneAtHandRow(gTurnHands[INACTIVE_DUELIST], (u8)handZone);
    cardId = handSlot->id;

    if (HandCardCanBeSpecialSummoned(cardId, INACTIVE_DUELIST)) {
      opts = Duel_DefaultSpecialSummonOpts(FALSE);
      if (Duel_SpecialSummonFromHandZone(INACTIVE_DUELIST, handZone, opts)
          == DUEL_ACTION_DUEL_OVER)
        return;
    } else {
      Duel_DestroyZone(handSlot, INACTIVE_DUELIST, FALSE);
      if (IsDuelOver() == TRUE)
        return;
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
}
