#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "spell_effects.h"
#include "venom_swamp.h"

void UpdateDuelGfxExceptField(void);
void ApplyFieldZoneStatsToCardInfo(struct DuelCard *zone);

static const char sVenomName[] APPEND_RODATA = "Venom";

static u8 IsVenomMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sVenomName);
}

static u8 FieldHasFaceUpVenomSwamp(void)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, VENOM_SWAMP, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, VENOM_SWAMP, TRUE) != NULL;
}

static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

void TryApplyVenomSwampEndPhase(void)
{
  u8 row;
  u8 col;
  struct DuelCard *zone;

  if (!FieldHasFaceUpVenomSwamp())
    return;

  if (IsDuelOver() == TRUE)
    return;

  /* Place 1 Venom Counter stand-in (−1 stage ≈ −500 ATK) on each face-up non-Venom. */
  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      zone = gFixedZones[row][col];
      if (!MonsterIsFaceUp(zone) || IsVenomMonster(zone->id))
        continue;

      DecrementPermStage(zone);
    }
  }

  Duel_RefreshMonsterStatOverlays();

  /* Destroy monsters whose ATK hit 0 after the drain. */
  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      zone = gFixedZones[row][col];
      if (!MonsterIsFaceUp(zone) || IsVenomMonster(zone->id))
        continue;

      ApplyFieldZoneStatsToCardInfo(zone);
      if (gCardInfo.atk == 0) {
        u8 gy = row == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;

        Duel_DestroyZone(zone, gy, FALSE);
        if (IsDuelOver() == TRUE)
          return;
      }
    }
  }
}

static void VENOM_SWAMP_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(VENOM_SWAMP);
}

APPEND_TEXT void EffectVENOM_SWAMP(void)
{
  if (Duel_TryResolveSpellThroughTraps(VENOM_SWAMP, VENOM_SWAMP_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
