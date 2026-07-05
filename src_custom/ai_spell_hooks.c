#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "card.h"
#include "constants/card_ids.h"
#include "constants/duel_fields.h"
#include "constants/spell_effects.h"
#include "duel.h"
#include "monster_reborn.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;
extern void (*g8DFF7F0[])(void);
extern void (*g8DFFA48[])(void);

struct AiDuelSimulationState {
  struct Duel duel;
};

#define AI_SIM_PRIORITY (*(u32 *)((u8 *)gUnk_8DFF6A4 + 0x2298))
#define AI_SIM_PRE_FIELD (((struct AiDuelSimulationState *)gUnk_8DFF6A4)->duel.field)

#define AI_PRIORITY_PLACE_NORMAL_SPELL 0x7FFFFFF7u
#define AI_PRIORITY_TERRAIN_FIELD_ACTIVATION 0x7FFFFFF8u

static u8 sAiScoringSpellEffect APPEND_DATA = 0;

static u8 FieldForTerrainSpellEffect(u8 spellEffect)
{
  if (spellEffect < SPELL_EFFECT_FOREST || spellEffect > SPELL_EFFECT_YAMI)
    return FIELD_ARENA;
  return spellEffect - SPELL_EFFECT_FOREST + FIELD_FOREST;
}

static u8 BackrowHasSetNormalSpell(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (zone->id == CARD_NONE)
      continue;
    if (GetTypeGroup(zone->id) == TYPE_GROUP_SPELL
        && GetSpellType(zone->id) == SPELL_TYPE_NORMAL)
      return TRUE;
  }

  return FALSE;
}

void ActivateSpellEffect(void);
void ClearZone(struct DuelCard *zone);
void LockMonsterCardsInRow(unsigned char turnRow);
void sub_800EC68(void);
void sub_800ECC0(void);
void sub_80116F0(void);
void sub_80124D8(void);
void sub_80124F8(void);
void sub_8013B98(void);

static u8 SpellShouldRemainOnFieldAfterActivation(u16 cardId)
{
  return cardId == SWORDS_OF_REVEALING_LIGHT;
}

static void AiActivateNormalSpellFromBackrow(u8 lockMonstersAfterActivation, u8 clearZoneAfterActivation)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u16 spellId = gTurnZones[row2][col2]->id;

  if (spellId == MONSTER_REBORN && !CanActivateMonsterReborn())
    return;

  gSpellEffectData.id = spellId;
  gSpellEffectData.row1 = row2;
  gSpellEffectData.col1 = col2;
  ActivateSpellEffect();

  if (lockMonstersAfterActivation && gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  if (clearZoneAfterActivation && !SpellShouldRemainOnFieldAfterActivation(spellId))
    ClearZone(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800EC68);
void sub_800EC68__Replacement(void)
{
  AiActivateNormalSpellFromBackrow(TRUE, TRUE);
}

LYN_REPLACE_CHECK(sub_800ECC0);
void sub_800ECC0__Replacement(void)
{
  AiActivateNormalSpellFromBackrow(FALSE, TRUE);
}

LYN_REPLACE_CHECK(sub_80116F0);
void sub_80116F0__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u8 row3 = sAI_Command.zone2Position >> 4;
  u8 col3 = sAI_Command.zone2Position & 0xF;

  SetCardInfo(gTurnZones[row2][col2]->id);

  if (!gCardInfo.unk1E && gTurnZones[row3][col3]->id == CARD_NONE) {
    /* ponytail: place priority (0x7FFFFFF7) outranks Raigeki/Heavy Storm activate (0x7FF…).
     * With duplicate copies in hand the AI kept setting and never flipped. Activate any
     * set normal spell before placing another (covers terrain waiting too). */
    if (BackrowHasSetNormalSpell())
      AI_SIM_PRIORITY = AI_PRIORITY_DISABLE;
    else
      AI_SIM_PRIORITY = AI_PRIORITY_PLACE_NORMAL_SPELL;
  } else {
    AI_SIM_PRIORITY = AI_PRIORITY_DISABLE;
  }
}

LYN_REPLACE_CHECK(sub_80124F8);
void sub_80124F8__Replacement(void)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;

  SetCardInfo(gTurnZones[row2][col2]->id);
  sAiScoringSpellEffect = gCardInfo.spellEffect;
  g8DFF7F0[gCardInfo.spellEffect]();
}

LYN_REPLACE_CHECK(sub_80124D8);
void sub_80124D8__Replacement(void)
{
  u8 preField;
  u8 targetField;

  preField = AI_SIM_PRE_FIELD;
  targetField = FieldForTerrainSpellEffect(sAiScoringSpellEffect);

  g8DFFA48[sAiScoringSpellEffect]();

  if (AI_SIM_PRIORITY != AI_PRIORITY_DISABLE)
    return;

  if (targetField == FIELD_ARENA)
    return;

  // ponytail: vanilla disables terrain spells when board ATK+DEF is unchanged; score the
  // first activation that changes gDuel.field above set-spell priority. Use spell effect
  // saved in sub_80124F8 — the backrow zone is empty by now (activation sim clears it).
  if (preField != targetField && gDuel.field == targetField)
    AI_SIM_PRIORITY = AI_PRIORITY_TERRAIN_FIELD_ACTIVATION;
}

LYN_REPLACE_CHECK(sub_8013B98);
void sub_8013B98__Replacement(void)
{
  if (!CanActivateMonsterReborn())
    AI_SIM_PRIORITY = AI_PRIORITY_DISABLE;
  else
    AI_SIM_PRIORITY = 0x7FB3183D;
}
