#ifndef GUARD_DUEL_HELPERS_H
#define GUARD_DUEL_HELPERS_H

#include "global.h"
#include "duel.h"
#include "exchange_hand_selection.h"

enum DuelActionResult {
  DUEL_ACTION_OK,
  DUEL_ACTION_DUEL_OVER,
  DUEL_ACTION_NO_TARGET,
  DUEL_ACTION_NO_ZONE,
  DUEL_ACTION_BLOCKED,
  DUEL_ACTION_INVALID,
};

enum DuelSummonMode {
  DUEL_SUMMON_SPECIAL_FACE_UP_ATK,
  DUEL_SUMMON_SPECIAL_FACE_UP_DEF,
  DUEL_SUMMON_NORMAL_FACE_UP_ATK,
  DUEL_SUMMON_NORMAL_SET,
};

struct DuelSummonOpts {
  u8 updateGfx;
  enum DuelSummonMode mode;
  u8 markSpecialSummon;
  u8 lockMonster;
};

typedef u8 (*MonsterZonePredicate)(struct DuelCard *zone);
typedef u8 (*DuelZoneStatApplier)(struct DuelCard *zone);

struct DuelSummonOpts Duel_DefaultSpecialSummonOpts(u8 updateGfx);
struct DuelSummonOpts Duel_DefaultNormalSummonOpts(u8 updateGfx);
u8 Duel_CardCannotBeSpecialSummoned(u16 cardId);

u8 Duel_CountCardsInHand(struct DuelCard **handRow);
enum DuelActionResult Duel_DrawCards(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Duel_DrawCardsUntilHandSize(u8 turnDuelist, u8 targetHandSize, u8 updateGfx);
enum DuelActionResult Duel_MillTopDeckCards(u8 duelist, u8 count, u8 updateGfx);

enum DuelActionResult Duel_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx);
void Duel_DestroyMaskedMonstersInFixedRow(u8 fixedRow, u8 colMask, u8 graveyardDuelist, u8 updateGfx);
enum DuelActionResult Duel_DestroyAllMonstersMatching(u8 turnRow, MonsterZonePredicate pred,
                                                       u8 updateGfx);

enum DuelActionResult Duel_DiscardFromHand(u8 duelist, u8 count, HandCardPredicate pred,
                                           u8 updateGfx);
enum DuelActionResult Duel_DiscardRandomFromHand(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Duel_DestroyAllHandCards(u8 duelist, u8 updateGfx);
enum DuelActionResult Duel_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx);

void Duel_IncrementPermStageOnDuelistMonsters(u8 turnDuelist);
void Duel_RefreshMonsterStatOverlays(void);

u16 Duel_ClampStat(u32 stat);
u16 Duel_StatFromCount(u32 count, u16 perUnit, u32 base);
u8 Duel_CardHasMonsterType(u16 cardId, u8 monsterType);
u8 Duel_CardNameContains(u16 cardId, const char *needle);
u8 Duel_IsAmazonessCard(u16 cardId);
u8 Duel_IsFiendZone(struct DuelCard *zone);
u8 Duel_FindFixedMonsterZone(struct DuelCard *zone, u8 *fixedRow, u8 *col);
u8 Duel_FindFixedZone(struct DuelCard *zone, u8 *fixedRow, u8 *col);
u8 Duel_FindTurnMonsterZone(struct DuelCard *zone, u8 *turnRow, u8 *col);
u8 Duel_CountMonstersOnFixedRow(u8 fixedRow);
u8 Duel_OpponentMonsterRowForZone(struct DuelCard *zone);
u8 Duel_CountFixedMonstersMatching(MonsterZonePredicate pred);
u8 Duel_TurnRowHasOtherMonsterMatching(u8 turnRow, u8 exceptCol, MonsterZonePredicate pred);
void Duel_WriteCardInfoStats(u16 cardId, u16 atk, u16 def);
u8 Duel_ApplyStatModViaZoneApplier(struct StatMod *ptr, u16 cardId,
                                   DuelZoneStatApplier applyZone);
u8 Duel_TryApplyDynamicZoneStats(struct DuelCard *zone);
u8 Duel_TryApplyDynamicStatMod(struct StatMod *ptr);
u8 Duel_CanBeAttackedUnlessControllerHasOther(struct DuelCard *zone, u16 cardId,
                                              MonsterZonePredicate otherPred);
u8 Duel_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *Duel_GetForcedAttackTarget(u8 defenderDuelist);
u8 Duel_MonsterMayBeAttacked(struct DuelCard *zone);
u8 Duel_ForcedAttackBlocksDirect(u8 defenderDuelist);

u8 CanMonsterBeDestroyedByBattle(u16 cardId, u8 duelist, u16 battleAtk, u16 opponentBattleAtk);
void Duel_ApplyBattleDestroyProtection(void);
void Duel_RemapMutualDestroyBattleAnim(u8 playerDestroy, u8 opponentDestroy);

void Duel_ActivateContinuousZone(struct DuelCard *zone);
u16 Duel_GetZoneFinalAtk(struct DuelCard *zone);
u8 Duel_FixedMonsterRowForDuelist(u8 fixedDuelist);
u8 Duel_FixedDuelistForMonsterRow(u8 fixedRow);
u8 Duel_TurnMonsterRowForDuelist(u8 turnDuelist);
u8 Duel_TurnDuelistForFixedDuelist(u8 fixedDuelist);
u8 Duel_TurnDuelistMatchingWhoseTurn(u8 fixedDuelist);
u8 Duel_CountMonstersOnTurnRow(u8 turnRow);
u8 Duel_IsFixedMonsterRow(u8 fixedRow);
u8 Duel_IsTurnMonsterRow(u8 turnRow);
u8 Duel_FixedMonsterRowToTurnMonsterRow(u8 fixedRow);
u8 Duel_FixedMonsterRowHasMultipleMonsterTypes(u8 fixedRow);
u8 Duel_GetLeftmostMonsterTypeOnFixedRow(u8 fixedRow);
enum DuelActionResult Duel_EnforceSingleMonsterTypeOnFixedRow(u8 fixedRow, u8 updateGfx);
void Duel_EnforceSingleMonsterTypeOnBothMonsterRows(u8 updateGfx);
void Duel_NotifyFixedMonsterRowChanged(u8 fixedRow);
void Duel_NotifyMonsterZoneChanged(struct DuelCard *zone);
void Duel_CheckRivalryOfWarlordsAfterFieldChange(void);
void Duel_CheckLevelLimitAreaBAfterFieldChange(void);
void Duel_CheckLevelLimitAreaAAfterFieldChange(void);
void Duel_CheckAmazonessTigerAfterFieldChange(void);
void Duel_CheckRingOfDestructionAfterFieldChange(void);
u8 Duel_IsMonsterZoneTarget(u16 cardId);
u8 Duel_CardIsMonster(u16 cardId);
struct DuelCard *Duel_FindFixedZoneById(u8 fixedRow, u16 cardId, u8 requireFaceUp);
struct DuelCard *Duel_FindBackrowCard(u8 fixedDuelist, u16 cardId, u8 requireFaceUp);
struct DuelCard *Duel_FindBackrowCardOnField(u16 cardId, u8 requireFaceUp);
u8 Duel_IsBackrowCardOnField(u16 cardId, u8 requireFaceUp);
u8 Duel_FixedMonsterSlotBit(const struct DuelCard *zone);
u8 Duel_ZoneIsHandSlot(const struct DuelCard *zone);
enum DuelActionResult Duel_ChangeLpSuppressingEffectText(u8 turnDuelist, s32 delta, u8 updateGfx);
enum DuelActionResult Duel_ChangeLpWithPrefaceText(u8 turnDuelist, s32 delta, u16 cardId,
                                                   u8 textType, u8 updateGfx);
enum DuelActionResult Duel_ResolveBurnSpell(u16 spellId, s32 damage, u8 destroySpellGfx);
void Duel_ShowTrapResponseText(u16 trapId, u16 originCardId);

void Duel_ShowEffectText(u16 cardId);
void Duel_ShowEffectTextTyped(u16 cardId, u8 textType);

enum DuelActionResult Duel_TryResolveSpellThroughTraps(u16 spellId, void (*resolveBody)(void));
enum DuelActionResult Duel_TryResolveSpellThroughTrapsEx(u16 spellId, u16 trapLp,
                                                         void (*resolveBody)(void));
enum DuelActionResult Duel_TryResolveTrapThroughTraps(u16 trapId);

s16 Duel_FindDeckCardIndex(u8 duelist, u16 cardId);
enum DuelActionResult Duel_RemoveDeckCardAt(u8 duelist, u8 index, u8 updateGfx);
void Duel_ShuffleDeckFromDrawn(u8 duelist);

enum DuelActionResult Duel_SpecialSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                 struct DuelSummonOpts opts);
enum DuelActionResult Duel_SpecialSummonFromHandZone(u8 duelist, s8 handZone,
                                                     struct DuelSummonOpts opts);
enum DuelActionResult Duel_SpecialSummonFromGrave(u8 duelist, u16 cardId, struct DuelSummonOpts opts);
enum DuelActionResult Duel_SpecialSummonFromDeck(u8 duelist, u16 cardId, struct DuelSummonOpts opts);
enum DuelActionResult Duel_SpecialSummonMonsterId(u8 duelist, u16 monsterId,
                                                  struct DuelSummonOpts opts);

enum DuelActionResult Duel_NormalSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                struct DuelSummonOpts opts);

enum DuelActionResult Duel_ReturnMonsterZoneToOwnerHand(struct DuelCard *zone, u8 updateGfx);
enum DuelActionResult Duel_BanishZone(struct DuelCard *zone, u8 updateGfx);

void Duel_BeginSpellEffectResolve(void);
void Duel_EndSpellEffectResolve(void);
u8 Duel_IsSpellEffectResolving(void);
u8 Duel_ZoneIsImmuneToSpellEffects(struct DuelCard *zone);
u8 Duel_SpellMayTargetMonsterZone(struct DuelCard *zone);
u8 Duel_IsAnyTrapActivationBlocked(void);
u8 Duel_IsCardActivationBlocked(u16 cardId);

// --- PickZone targeting helper ---
// Eliminates per-card headers, cursor constants, and code_8043EF4_hooks.c edits.
// Effects call Duel_SetupPickZone + Duel_EnterPickZoneTargeting instead of
// defining a DUEL_CURSOR constant and wiring A/B button dispatch.

#define DUEL_CURSOR_PICK_ZONE 200

typedef u8 (*PickZoneValidator)(u8 fixedRow, u8 fixedCol);
typedef void (*PickZoneResolver)(u8 fixedRow, u8 fixedCol);
typedef void (*PickZoneCanceller)(void);
typedef u8 (*PickZoneAiPicker)(u8 *outRow, u8 *outCol);

struct PickZoneState {
  PickZoneValidator validator;
  PickZoneResolver resolver;
  PickZoneCanceller canceller;
  PickZoneAiPicker aiPicker;
};

extern struct PickZoneState gPickZoneState;

// Register targeting callbacks.
void Duel_SetupPickZone(PickZoneValidator validator,
                        PickZoneResolver resolver,
                        PickZoneCanceller canceller,
                        PickZoneAiPicker aiPicker);

// Enter targeting mode (finds first valid target, sets cursor).
// Requires gDuelCursor.destY/destX set to origin zone.
// Call AFTER Duel_SetupPickZone.
void Duel_EnterPickZoneTargeting(void);

// Handle A-button press during DUEL_CURSOR_PICK_ZONE.
void Duel_HandlePickZoneA(void);

// Handle B-button press during DUEL_CURSOR_PICK_ZONE.
void Duel_HandlePickZoneB(void);

// Resolve effect for AI (uses registered callbacks).
void Duel_ResolvePickZoneForAi(void);

#endif // GUARD_DUEL_HELPERS_H
