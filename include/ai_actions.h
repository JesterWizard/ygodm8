#ifndef GUARD_AI_ACTIONS_H
#define GUARD_AI_ACTIONS_H

#define AI_ACTION_NONE                           0
#define AI_ACTION_DISCARD                        1
#define AI_ACTION_0_TRIBUTE_SUMMON               2
#define AI_ACTION_1_TRIBUTE_SUMMON               3
#define AI_ACTION_2_TRIBUTE_SUMMON               4
#define AI_ACTION_DEFENSE_POSITION               5
#define AI_ACTION_ATTACK_POSITION                6
#define AI_ACTION_DIRECT_ATTACK_NO_TRAP          7
#define AI_ACTION_ATTACK_FACE_UP_NO_TRAP         8
#define AI_ACTION_DIRECT_ATTACK_WITH_TRAP        9
#define AI_ACTION_ATTACK_FACE_UP_WITH_TRAP       10
#define AI_ACTION_3_TRIBUTE_SUMMON               11
#define AI_ACTION_ATTACK_FACE_DOWN_NO_TRAP       12
#define AI_ACTION_ATTACK_FACE_DOWN_WITH_TRAP     13
#define AI_ACTION_PLACE_NON_DESTINY_BOARD_TRAP   14
#define AI_ACTION_PLACE_EQUIP_SPELL              15
#define AI_ACTION_ACTIVATE_EQUIP_SPELL_NO_TRAP   16
#define AI_ACTION_ACTIVATE_EQUIP_SPELL_WITH_TRAP 17
#define AI_ACTION_PLACE_NORMAL_SPELL             18
#define AI_ACTION_ACTIVATE_NORMAL_SPELL_NO_TRAP  19
#define AI_ACTION_ACTIVATE_NORMAL_SPELL_WITH_TRAP 20
#define AI_ACTION_PLACE_RITUAL_SPELL             21
#define AI_ACTION_ACTIVATE_RITUAL_SPELL          22
#define AI_ACTION_MONSTER_EFFECT                 23
#define AI_ACTION_PLACE_DESTINY_BOARD_TRAP       24
#define AI_ACTION_PERM_CARD_DISCARD              25
#define AI_ACTION_PERM_CARD_0_TRIBUTE_SUMMON     26
#define AI_ACTION_PERM_CARD_1_TRIBUTE_SUMMON     27
#define AI_ACTION_PERM_CARD_2_TRIBUTE_SUMMON     28
#define AI_ACTION_PERM_CARD_3_TRIBUTE_SUMMON     29
#define AI_ACTION_PERM_CARD_DEFENSE_POSITION     30
#define AI_ACTION_PERM_CARD_ATTACK_POSITION      31
#define AI_ACTION_PERM_CARD_DIRECT_ATTACK_NO_TRAP 41
#define AI_ACTION_PERM_CARD_ATTACK_FACE_UP_NO_TRAP 42
#define AI_ACTION_PERM_CARD_DIRECT_ATTACK_WITH_TRAP 43
#define AI_ACTION_PERM_CARD_ATTACK_FACE_UP_WITH_TRAP 44
#define AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_NO_TRAP 45
#define AI_ACTION_PERM_CARD_ATTACK_FACE_DOWN_WITH_TRAP 46

u8 IsAiTributeSummonAction(u16 action);
u8 IsAiDirectAttackVoicingAction(u16 action);
u8 IsAiDirectAttackAction(u16 action);
u8 IsAiAttackAction(u16 action);
u8 IsAiSummonAction(u16 action);
u8 IsAiDefensePositionAction(u16 action);
u8 IsAiSetSpellAction(u16 action);
u8 IsAiSetTrapAction(u16 action);
u8 IsAiActivateSpellAction(u16 action);
u8 IsAiMonsterEffectAction(u16 action);
u8 IsAiHighImpactAction(u16 action);
u8 IsAiFaceDownAttackAction(u16 action);
u8 IsAiFaceUpAttackAction(u16 action);

void TryPlayCustomOpponentAttackVoice(void);

#endif
