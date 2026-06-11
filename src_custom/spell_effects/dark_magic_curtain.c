#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "spell_effects.h"

static u8 CanSpecialSummonWithDarkMagicCurtain(void)
{
  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

static void InitSummonedMonsterZone(struct DuelCard *zone)
{
  zone->id = DARK_MAGICIAN;
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void PayHalfLifePoints(void)
{
  u16 halfLp;

  if (WhoseTurn() == DUEL_PLAYER)
  {
    halfLp = gDuelLifePoints[DUEL_PLAYER] / 2;
    SetPlayerLifePointsToSubtract(halfLp);
  }
  else
  {
    halfLp = gDuelLifePoints[DUEL_OPPONENT] / 2;
    SetOpponentLifePointsToSubtract(halfLp);
  }
}

static void SpecialSummonDarkMagician(void)
{
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonWithDarkMagicCurtain())
    return;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return;

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  InitSummonedMonsterZone(summonZone);
}

APPEND_TEXT void EffectDarkMagicCurtain(void)
{
  ClearZoneAndSendMonToGraveyard(
      gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST);

  PayHalfLifePoints();
  HandleAtkAndLifePointsAction();

  if (IsDuelOver() == TRUE)
    return;

  if (!gHideEffectText) {
    gCardEffectTextData.cardId = DARK_MAGIC_CURTAIN;
    ActivateCardEffectText();
  }

  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonDarkMagician();
}
