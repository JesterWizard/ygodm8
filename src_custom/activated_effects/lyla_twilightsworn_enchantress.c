#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static const char sLightswornName[] APPEND_RODATA = "Lightsworn";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsLightswornMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sLightswornName);
}

static u8 HandHasLightsworn(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsLightswornMonster(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GyHasLightsworn(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsLightswornMonster(cardId);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsLightswornMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 HasLightswornInHandOrGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();

  return HandHasLightsworn() || GyHasLightsworn(fixedDuelist);
}

static u8 BanishOneLightswornFromHandOrGy(void)
{
  u8 col;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = gTurnHands[ACTIVE_DUELIST][col];

    if (!IsLightswornMonster(slot->id))
      continue;

    if (Duel_BanishZone(slot, TRUE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    return TRUE;
  }

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;

    if (!IsLightswornMonster(cardId))
      return FALSE;

    Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST);
    return TRUE;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (!IsLightswornMonster(cardId))
      continue;

    Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
    return TRUE;
  }

  return FALSE;
}

static u8 IsFaceUpSpellTrapZone(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  u8 typeGroup;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return FALSE;

  typeGroup = GetTypeGroup(zone->id);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 FieldHasFaceUpSpellTrap(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpSpellTrapZone(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW)
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void ResolveTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!IsFaceUpSpellTrapZone(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();

  EffectOpt_MarkUsed(LYLA_TWILIGHTSWORN_ENCHANTRESS);
  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsFaceUpSpellTrapZone(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

unsigned char CanActivateLYLA_TWILIGHTSWORN_ENCHANTRESS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != LYLA_TWILIGHTSWORN_ENCHANTRESS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != LYLA_TWILIGHTSWORN_ENCHANTRESS)
    return FALSE;

  /* OPT banish LS from hand/GY then destroy 1 face-up Spell/Trap (EffectOpt).
   * EP mill 3 via TryApplyTwilightswornEndPhase. Ceiling: quick effect on
   * Spell/Trap activation + mill 3 when other LS activates need chain hooks. */
  if (EffectOpt_IsUsed(LYLA_TWILIGHTSWORN_ENCHANTRESS))
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HasLightswornInHandOrGy() && FieldHasFaceUpSpellTrap();
}

void ActivateLYLA_TWILIGHTSWORN_ENCHANTRESSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(LYLA_TWILIGHTSWORN_ENCHANTRESS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (EffectOpt_IsUsed(LYLA_TWILIGHTSWORN_ENCHANTRESS))
    return;

  if (!BanishOneLightswornFromHandOrGy())
    return;

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsFaceUpSpellTrapZone, ResolveTarget, CancelTargeting, AiPickTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
