#include "global.h"
#include "common-chax.h"
#include "ai_actions.h"
#include "ai_decision.h"
#include "duel.h"

#include "../generated/ai_action_table_generated.inc"

u8 IsAiTributeSummonAction(u16 action) {
  switch (action) {
    case AI_ACTION_1_TRIBUTE_SUMMON:
    case AI_ACTION_2_TRIBUTE_SUMMON:
    case AI_ACTION_3_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiAttackAction(u16 action) {
  switch (action) {
    case AI_ACTION_DIRECT_ATTACK_NO_TRAP:
    case AI_ACTION_ATTACK_FACE_UP_NO_TRAP:
    case AI_ACTION_DIRECT_ATTACK_WITH_TRAP:
    case AI_ACTION_ATTACK_FACE_UP_WITH_TRAP:
    case AI_ACTION_ATTACK_FACE_DOWN_NO_TRAP:
    case AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP:
    case AI_ACTION_PERM_CARD_DIRECT_ATTACK_NO_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_UP_NO_TRAP:
    case AI_ACTION_PERM_CARD_DIRECT_ATTACK_WITH_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_UP_WITH_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_NO_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_WITH_TRAP:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiDirectAttackAction(u16 action) {
  return IsAiDirectAttackVoicingAction(action);
}

u8 IsAiSummonAction(u16 action) {
  switch (action) {
    case AI_ACTION_0_TRIBUTE_SUMMON:
    case AI_ACTION_1_TRIBUTE_SUMMON:
    case AI_ACTION_2_TRIBUTE_SUMMON:
    case AI_ACTION_3_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_0_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
    case AI_ACTION_ACTIVATE_RITUAL_SPELL:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiDefensePositionAction(u16 action) {
  switch (action) {
    case AI_ACTION_DEFENSE_POSITION:
    case AI_ACTION_PERM_CARD_DEFENSE_POSITION:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiSetSpellAction(u16 action) {
  switch (action) {
    case AI_ACTION_PLACE_EQUIP_SPELL:
    case AI_ACTION_PLACE_NORMAL_SPELL:
    case AI_ACTION_PLACE_RITUAL_SPELL:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiSetTrapAction(u16 action) {
  switch (action) {
    case AI_ACTION_PLACE_NON_DESTINY_BOARD_TRAP:
    case AI_ACTION_PLACE_DESTINY_BOARD_TRAP:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiActivateSpellAction(u16 action) {
  switch (action) {
    case AI_ACTION_ACTIVATE_EQUIP_SPELL_NO_TRAP:
    case AI_ACTION_ACTIVATE_EQUIP_SPELL_WITH_TRAP:
    case AI_ACTION_ACTIVATE_NORMAL_SPELL_NO_TRAP:
    case AI_ACTION_ACTIVATE_NORMAL_SPELL_WITH_TRAP:
    case AI_ACTION_ACTIVATE_RITUAL_SPELL:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiMonsterEffectAction(u16 action) {
  return action == AI_ACTION_MONSTER_EFFECT;
}

u8 IsAiHighImpactAction(u16 action) {
  switch (action) {
    case AI_ACTION_2_TRIBUTE_SUMMON:
    case AI_ACTION_3_TRIBUTE_SUMMON:
    case AI_ACTION_ACTIVATE_RITUAL_SPELL:
    case AI_ACTION_ACTIVATE_NORMAL_SPELL_NO_TRAP:
    case AI_ACTION_ACTIVATE_NORMAL_SPELL_WITH_TRAP:
    case AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON:
    case AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON:
      return TRUE;
    default:
      return IsAiTributeSummonAction(action);
  }
}

u8 IsAiFaceDownAttackAction(u16 action) {
  switch (action) {
    case AI_ACTION_ATTACK_FACE_DOWN_NO_TRAP:
    case AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_NO_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_WITH_TRAP:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 IsAiFaceUpAttackAction(u16 action) {
  switch (action) {
    case AI_ACTION_ATTACK_FACE_UP_NO_TRAP:
    case AI_ACTION_ATTACK_FACE_UP_WITH_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_UP_NO_TRAP:
    case AI_ACTION_PERM_CARD_ATTACK_FACE_UP_WITH_TRAP:
      return TRUE;
    default:
      return FALSE;
  }
}

u8 AiAction_GetCategory(u16 action) {
  if (IsAiDirectAttackVoicingAction(action))
    return AI_CATEGORY_DIRECT;
  if (IsAiAttackAction(action))
    return AI_CATEGORY_ATTACK;
  if (IsAiSummonAction(action))
    return AI_CATEGORY_SUMMON;
  if (IsAiDefensePositionAction(action))
    return AI_CATEGORY_DEFENSE;
  if (IsAiSetSpellAction(action))
    return AI_CATEGORY_SET_SPELL;
  if (IsAiSetTrapAction(action))
    return AI_CATEGORY_SET_TRAP;
  if (IsAiActivateSpellAction(action))
    return AI_CATEGORY_ACTIVATE_SPELL;
  if (IsAiMonsterEffectAction(action))
    return AI_CATEGORY_MONSTER_EFFECT;
  return AI_CATEGORY_OTHER;
}

u16 AiAction_GetCardAtZone(u8 zonePosition) {
  u8 row = zonePosition >> 4;
  u8 col = zonePosition & 0xF;

  if (row >= 5 || col >= MAX_ZONES_IN_ROW)
    return CARD_NONE;

  return gTurnZones[row][col]->id;
}

void AiDecodeActionIndex(u16 actionIndex, struct AiDecodedAction *out) {
  const struct AiActionTemplate *template;

  out->actionIndex = actionIndex;
  out->primaryCardId = CARD_NONE;
  out->secondaryCardId = CARD_NONE;
  out->handCol = 0xFF;
  out->zone0Row = 0xFF;
  out->zone0Col = 0xFF;
  out->zone1Row = 0xFF;
  out->zone1Col = 0xFF;

  if (actionIndex >= AI_ACTION_TABLE_COUNT) {
    out->action = AI_ACTION_NONE;
    out->category = AI_CATEGORY_NONE;
    return;
  }

  template = &sAiActionTable[actionIndex];
  out->action = template->action;
  out->category = AiAction_GetCategory(template->action);

  out->primaryCardId = AiAction_GetCardAtZone(template->zones[0]);
  out->secondaryCardId = AiAction_GetCardAtZone(template->zones[1]);

  if (template->zones[0] != 0) {
    out->zone0Row = template->zones[0] >> 4;
    out->zone0Col = template->zones[0] & 0xF;
    if (out->zone0Row == ACTIVE_DUELIST_HAND)
      out->handCol = out->zone0Col;
  }

  if (template->zones[1] != 0) {
    out->zone1Row = template->zones[1] >> 4;
    out->zone1Col = template->zones[1] & 0xF;
  }
}

u8 AiAction_IsHighImpact(u16 action) {
  return IsAiHighImpactAction(action);
}
