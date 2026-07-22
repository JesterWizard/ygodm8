#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "reptilianne_naga.h"

void UpdateDuelGfxExceptField(void);

u8 ReptilianneNaga_PreventsBattleDestroy(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != REPTILIANNE_NAGA)
    return FALSE;

  return zone->isFaceUp;
}

void TryApplyReptilianneNagaEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || zone->id != REPTILIANNE_NAGA || !zone->isFaceUp)
      continue;

    if (!zone->isDefending)
      continue;

    Duel_ShowEffectTextTyped(REPTILIANNE_NAGA, 9);
    zone->isDefending = FALSE;
    zone->isLocked = TRUE;
    UpdateDuelGfxExceptField();
    return;
  }
}

unsigned char ShouldActivateREPTILIANNE_NAGA(void)
{
  /* Battle indestructible via ReptilianneNaga_PreventsBattleDestroy; EP DEF→ATK
   * via TryApplyReptilianneNagaEndPhase. ponytail: battle ATK-to-0 needs hook. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateREPTILIANNE_NAGA(void)
{
}
