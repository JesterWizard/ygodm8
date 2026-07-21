#include "global.h"
#include "common-chax.h"
#include "aroma_jar.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);

u8 AromaJar_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == AROMA_JAR && zone->isFaceUp
      && zone->unk4 == AROMA_JAR_FLIPPED;
}

void TryAromaJarOnFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != AROMA_JAR || !zone->isFaceUp)
    return;

  zone->unk4 = AROMA_JAR_FLIPPED;
}

void TryApplyAromaJarEndPhase(void)
{
  u8 fixed;
  u8 col;
  u8 gained = FALSE;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);
    u8 turnDuelist;

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id != AROMA_JAR || !zone->isFaceUp
          || zone->unk4 != AROMA_JAR_FLIPPED)
        continue;

      turnDuelist =
          (gTurnDuelistBattleState[ACTIVE_DUELIST]
           == &gDuel.duelistbattleState[fixed])
              ? ACTIVE_DUELIST
              : INACTIVE_DUELIST;

      if (Duel_ChangeLp(turnDuelist, 500, TRUE) == DUEL_ACTION_DUEL_OVER)
        return;

      gained = TRUE;
    }
  }

  if (gained)
    UpdateDuelGfxExceptField();
}

unsigned char CanActivateAROMA_JAR(void)
{
  if (gMonEffect.id != AROMA_JAR)
    return FALSE;

  /* Flip battle protect + EP LP are live via AromaJar_* hooks. */
  return FALSE;
}

void ActivateAROMA_JAREffect(void)
{
  Duel_ShowEffectTextTyped(AROMA_JAR, 2);
}
