#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "monster_effect_usage.h"
#include "summon_tribute.h"
#include "dark_dust_spirit.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);

void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);
void UpdateDuelGfxExceptField(void);
void FlipCardFaceUp(struct DuelCard *zone);

#define DARK_DUST_SPIRIT_END_PHASE_MARK 1

static u8 IsDarkDustSpiritSummonPlacement(const struct DuelCard *zone)
{
  /* Attack-position summons stay isFaceUp=0 until end-of-turn flip. */
  return zone->isFaceUp || !zone->isDefending;
}

static u8 FindMonsterTurnRowColForZone(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 GraveyardDuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 IsDestroyTargetFaceUpMonster(struct DuelCard *zone,
                                       const struct DuelCard *sourceZone)
{
  if (zone == NULL || zone == sourceZone)
    return FALSE;

  if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsGodCard(zone->id))
    return FALSE;

  /* GBA face-up = isFaceUp bit; attack-position keeps isFaceUp=0 until flip. */
  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static void DestroyOtherFaceUpMonsters(struct DuelCard *sourceZone)
{
  u8 row;
  u8 col;
  u8 destroyed = FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    u8 graveyardDuelist = GraveyardDuelistForMonsterTurnRow(row);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (!IsDestroyTargetFaceUpMonster(zone, sourceZone))
        continue;

      if (Duel_DestroyZone(zone, graveyardDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
        return;

      destroyed = TRUE;
    }
  }

  if (destroyed) {
    NotifyDynamicEquipFieldChanged();
    UpdateDuelGfxExceptField();
  }
}

static void MarkDarkDustSpiritForEndPhaseReturn(struct DuelCard *zone)
{
  zone->unk4 = DARK_DUST_SPIRIT_END_PHASE_MARK;
}

static void ResolveDarkDustSpiritEffect(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != DARK_DUST_SPIRIT || !IsDarkDustSpiritSummonPlacement(zone))
    return;

  if (!zone->isFaceUp)
    FlipCardFaceUp(zone);

  DestroyOtherFaceUpMonsters(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ShowEffectTextTyped(DARK_DUST_SPIRIT, 2);

  if (IsDuelOver() == TRUE)
    return;

  MarkDarkDustSpiritForEndPhaseReturn(zone);
  MarkMonsterEffectUsed(zone);
  CheckWinConditionExodia(WhoseTurn());

  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void TryActivateDarkDustSpiritOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id != DARK_DUST_SPIRIT)
    return;

  if (zone->unk4 == DARK_DUST_SPIRIT_END_PHASE_MARK)
    return;

  if (!IsDarkDustSpiritSummonPlacement(zone))
    return;

  if (!FindMonsterTurnRowColForZone(zone, &turnRow, &col))
    return;

  if (IsSkillDrainActiveOnField()
      && TryActivateSkillDrainAndNegateCardId(DARK_DUST_SPIRIT))
    return;

  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = col;
  gActiveEffect.cardId = DARK_DUST_SPIRIT;
  ResolveDarkDustSpiritEffect(zone);
}

unsigned char ShouldActivateDarkDustSpiritSummon(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != DARK_DUST_SPIRIT)
    return FALSE;

  if (GetPendingTributeSummonCardId() != DARK_DUST_SPIRIT)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone->unk4 == DARK_DUST_SPIRIT_END_PHASE_MARK)
    return FALSE;

  return IsDarkDustSpiritSummonPlacement(zone);
}

void ActivateDarkDustSpiritSummon(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  ResolveDarkDustSpiritEffect(zone);
}

unsigned char CanActivateDarkDustSpirit(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != DARK_DUST_SPIRIT)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gFixedZones[gMonEffect.row][gMonEffect.zone];
  return zone->id == DARK_DUST_SPIRIT && zone->isFaceUp == FALSE;
}

void ActivateDarkDustSpiritEffect(void)
{
  struct DuelCard *zone = gFixedZones[gMonEffect.row][gMonEffect.zone];

  ResolveDarkDustSpiritEffect(zone);
}

unsigned char ShouldActivateDarkDustSpiritTurnEffect(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  return zone->id == DARK_DUST_SPIRIT
      && zone->unk4 == DARK_DUST_SPIRIT_END_PHASE_MARK
      && NumEmptyZonesInRow(gTurnHands[ACTIVE_DUELIST]) > 0;
}

void ActivateDarkDustSpiritTurnEffect(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  Duel_ShowEffectTextTyped(DARK_DUST_SPIRIT, 9);

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_ReturnMonsterZoneToOwnerHand(zone, TRUE) == DUEL_ACTION_OK)
    zone->unk4 = 0;
}
