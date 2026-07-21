#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == MYSTIC_MINE || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS
      || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static u8 IsActivatedMysticMineZone(const struct DuelCard *zone)
{
  return zone != NULL && zone->id == MYSTIC_MINE && zone->isFaceUp == TRUE;
}

static u8 FindActiveMysticMine(struct DuelCard **outZone, u8 *outController)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (!IsActivatedMysticMineZone(zone))
        continue;

      *outZone = zone;
      *outController = (row == OPPONENT_BACKROW) ? DUEL_OPPONENT : DUEL_PLAYER;
      return TRUE;
    }
  }

  return FALSE;
}

u8 MysticMine_IsActiveOnField(void)
{
  struct DuelCard *zone;
  u8 controller;

  return FindActiveMysticMine(&zone, &controller);
}

/* Fixed duelist with fewer monsters is locked (cannot attack / activate monster effects).
 * Returns 0xFF if equal count or Mine inactive. */
u8 MysticMine_GetLockedFixedDuelist(void)
{
  struct DuelCard *zone;
  u8 controller;
  u8 playerCount;
  u8 oppCount;

  if (!FindActiveMysticMine(&zone, &controller))
    return 0xFF;

  (void)controller;

  playerCount = Duel_CountMonstersOnFixedRow(PLAYER_MONSTER_ROW);
  oppCount = Duel_CountMonstersOnFixedRow(OPPONENT_MONSTER_ROW);

  if (playerCount < oppCount)
    return DUEL_PLAYER;
  if (oppCount < playerCount)
    return DUEL_OPPONENT;

  return 0xFF;
}

u8 MysticMine_LocksFixedDuelist(u8 fixedDuelist)
{
  return fixedDuelist == DUEL_PLAYER || fixedDuelist == DUEL_OPPONENT
      ? MysticMine_GetLockedFixedDuelist() == fixedDuelist
      : FALSE;
}

void TryApplyMysticMineEndPhase(void)
{
  struct DuelCard *zone;
  u8 controller;
  u8 playerCount;
  u8 oppCount;

  if (IsDuelOver() == TRUE)
    return;

  if (!FindActiveMysticMine(&zone, &controller))
    return;

  playerCount = Duel_CountMonstersOnFixedRow(PLAYER_MONSTER_ROW);
  oppCount = Duel_CountMonstersOnFixedRow(OPPONENT_MONSTER_ROW);

  if (playerCount != oppCount)
    return;

  Duel_DestroyZone(zone, controller == WhoseTurn() ? ACTIVE_DUELIST : INACTIVE_DUELIST,
                   TRUE);
}

static void MYSTIC_MINE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(MYSTIC_MINE);

  /* Parent wires: reject monster effects and attacks for
   * MysticMine_LocksFixedDuelist(fixedDuelist), then call
   * TryApplyMysticMineEndPhase() from the End Phase sequence. */
}

APPEND_TEXT void EffectMYSTIC_MINE(void)
{
  if (Duel_TryResolveSpellThroughTraps(MYSTIC_MINE, MYSTIC_MINE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MYSTIC_MINE_SelfCheck(void)
{
  if (!IsFieldSpellCardOnField(MYSTIC_MINE))
    while (1)
      ;
  if (IsActivatedMysticMineZone(NULL))
    while (1)
      ;
}
#endif
