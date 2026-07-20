#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 IsOwnFaceUpDragon(u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[ACTIVE_DUELIST_MONSTER_ROW][fixedCol];

  if (zone == NULL || zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_CardHasMonsterType(zone->id, TYPE_DRAGON))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 FieldHasOwnDragon(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnFaceUpDragon(col))
      return TRUE;
  }

  return FALSE;
}

static u8 MarkOwnDragonsProtected(void)
{
  u8 col;
  u8 marked = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOwnFaceUpDragon(col) || zone == NULL)
      continue;

    /* ponytail: until end of next turn clear needs EOT hook. */
    zone->unk4 |= 0x80;
    marked = TRUE;
  }

  return marked;
}

unsigned char CanActivateAZURE_EYES_SILVER_DRAGON(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AZURE_EYES_SILVER_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AZURE_EYES_SILVER_DRAGON)
    return FALSE;

  /* ponytail: Special Summon protection + Standby SS Normal need summon/phase
   * hooks. Ceiling: OPT mark your Dragons protected (unk4). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return FieldHasOwnDragon();
}

void ActivateAZURE_EYES_SILVER_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(AZURE_EYES_SILVER_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!MarkOwnDragonsProtected())
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
