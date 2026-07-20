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
  if (cardId == SUPREME_KINGS_CASTLE || cardId == PSEUDO_SPACE || cardId == HARPIES_HUNTING_GROUND
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == NEO_SPACE)
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

static void SUPREME_KINGS_CASTLE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(SUPREME_KINGS_CASTLE);

  /* ponytail: "Fusion Summon monsters that must be Special Summoned with Dark
   * Fusion, with effects other than Dark Fusion" needs a global Dark-Fusion-
   * substitute flag checked by Evil HERO summon gates outside this file.
   * Ceiling: face-up field only; upgrade: summon validators → if face-up
   * SUPREME_KINGS_CASTLE then treat non-Dark-Fusion FS as Dark Fusion. */

  /* ponytail: once-per-turn damage-calc send 1 Evil HERO from Deck/Extra → GY
   * and battling Fiend gains Level×200 ATK needs a battle_effects damage-calc
   * hook outside this file (like skyscraper.c).
   * Ceiling: face-up field only; upgrade: ApplySupremeKingsCastleBattleAtkBoost
   * → if face-up SUPREME_KINGS_CASTLE, !effectUsedThisTurn, attacker is Fiend
   * battling opp monster, then DeckMenu pick Evil HERO (name contains
   * "Evil HERO") from Deck/Extra, send to GY, attacker ATK += level*200 until
   * turn end, mark OPT. */
}

APPEND_TEXT void EffectSUPREME_KINGS_CASTLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(SUPREME_KINGS_CASTLE, SUPREME_KINGS_CASTLE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
static const char sEvilHeroArchetypeName[] APPEND_RODATA = "Evil HERO";

static u8 IsEvilHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sEvilHeroArchetypeName);
}

void SUPREME_KINGS_CASTLE_SelfCheck(void)
{
  if (!IsEvilHeroMonster(EVIL_HERO_MALICIOUS_EDGE))
    while (1)
      ;
  if (IsEvilHeroMonster(ELEMENTAL_HERO_AVIAN))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(SUPREME_KINGS_CASTLE))
    while (1)
      ;
}
#endif
