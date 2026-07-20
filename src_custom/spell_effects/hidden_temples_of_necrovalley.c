#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static const char sGravekeeperArchetypeName[] APPEND_RODATA = "Gravekeeper";

static u8 IsGravekeeperMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sGravekeeperArchetypeName);
}

static u8 FieldHasGravekeeperMonster(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsGravekeeperMonster(gFixedZones[row][col]->id))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 NecrovalleyOnField(void)
{
  return Duel_IsBackrowCardOnField(NECROVALLEY, TRUE);
}

static u8 CanActivateHiddenTemples(void)
{
  return FieldHasGravekeeperMonster() && NecrovalleyOnField();
}

static void HIDDEN_TEMPLES_OF_NECROVALLEY_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!CanActivateHiddenTemples())
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(HIDDEN_TEMPLES_OF_NECROVALLEY);

  /* ponytail: SS lock "except Gravekeeper's" needs a CanSpecialSummon /
   * Duel_CardCannotBeSpecialSummoned gate outside this file.
   * Ceiling: continuous face-up only; upgrade: LynJump PlaceMonster /
   * Duel_CardCannotBeSpecialSummoned → if face-up HIDDEN_TEMPLES_OF_NECROVALLEY
   * on field and card is not Gravekeeper (Duel_CardNameContains "Gravekeeper"),
   * block SS for both players. */

  /* ponytail: self-destroy when no Gravekeeper or no Necrovalley needs a field-
   * change / permanent hook outside this file.
   * Ceiling: activation condition only; upgrade: after monster/backrow change,
   * if face-up HIDDEN_TEMPLES and (!FieldHasGravekeeper || !NecrovalleyOnField),
   * Duel_DestroyZone(this). */
}

APPEND_TEXT void EffectHIDDEN_TEMPLES_OF_NECROVALLEY(void)
{
  if (!CanActivateHiddenTemples()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(HIDDEN_TEMPLES_OF_NECROVALLEY,
                                       HIDDEN_TEMPLES_OF_NECROVALLEY_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void HIDDEN_TEMPLES_OF_NECROVALLEY_SelfCheck(void)
{
  if (!IsGravekeeperMonster(GRAVEKEEPERS_SPY))
    while (1)
      ;
  if (IsGravekeeperMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
