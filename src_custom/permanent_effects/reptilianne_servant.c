#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOtherFaceUpMonster(struct DuelCard *self, struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;
  if (zone == self)
    return FALSE;
  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone);
}

static u8 FieldHasOtherFaceUpMonster(struct DuelCard *self)
{
  u8 row;
  u8 col;

  for (row = ACTIVE_DUELIST_MONSTER_ROW; row <= INACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsOtherFaceUpMonster(self, gTurnZones[row][col]))
        return TRUE;
    }
  }

  return FALSE;
}

unsigned char ShouldActivateREPTILIANNE_SERVANT(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != REPTILIANNE_SERVANT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return FieldHasOtherFaceUpMonster(zone);
}

void ActivateREPTILIANNE_SERVANT(void)
{
  struct DuelCard *zone;

  Duel_ShowEffectTextTyped(REPTILIANNE_SERVANT, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || !FieldHasOtherFaceUpMonster(zone))
    return;

  zone->unk4 = 1;
  ClearZone(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
  /* ponytail: cannot-be-attacked + NS lock + spell-target destroy need battle/continuous hooks. */
}
