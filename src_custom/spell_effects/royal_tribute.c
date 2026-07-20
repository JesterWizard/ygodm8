#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ControlsNecrovalley(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  /* id gate; name-equivalent Field Spell is NECROVALLEY. */
  return Duel_FindBackrowCard(fixedDuelist, NECROVALLEY, FALSE) != NULL;
}

u8 CanActivateROYAL_TRIBUTE(void)
{
  return ControlsNecrovalley();
}

static void DiscardAllMonstersFromHand(u8 turnDuelist)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 maxSlots = ExpandedHand_MaxSlots();
  u8 i;

  for (i = 0; i < maxSlots; i++) {
    struct DuelCard *slot = ExpandedHand_ZoneAtHandRow(handRow, i);

    if (slot == NULL || slot->id == CARD_NONE)
      continue;

    if (!Duel_CardIsMonster(slot->id))
      continue;

    ClearZoneAndSendMonToGraveyard(slot, turnDuelist);

    if (IsDuelOver() == TRUE)
      return;
  }
}

static void ROYAL_TRIBUTE_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ShowEffectText(ROYAL_TRIBUTE);

  if (IsDuelOver() == TRUE || !CanActivateROYAL_TRIBUTE())
    return;

  DiscardAllMonstersFromHand(ACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  DiscardAllMonstersFromHand(INACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectROYAL_TRIBUTE(void)
{
  if (!CanActivateROYAL_TRIBUTE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ROYAL_TRIBUTE, ROYAL_TRIBUTE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}
