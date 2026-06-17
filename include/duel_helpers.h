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

struct DuelSummonOpts Duel_DefaultSpecialSummonOpts(u8 updateGfx);
struct DuelSummonOpts Duel_DefaultNormalSummonOpts(u8 updateGfx);

u8 Duel_CountCardsInHand(struct DuelCard **handRow);
enum DuelActionResult Duel_DrawCards(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Duel_MillTopDeckCards(u8 duelist, u8 count, u8 updateGfx);

enum DuelActionResult Duel_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx);
enum DuelActionResult Duel_DestroyAllMonstersMatching(u8 turnRow, MonsterZonePredicate pred,
                                                       u8 updateGfx);

enum DuelActionResult Duel_DiscardFromHand(u8 duelist, u8 count, HandCardPredicate pred,
                                           u8 updateGfx);
enum DuelActionResult Duel_DiscardRandomFromHand(u8 duelist, u8 count, u8 updateGfx);
enum DuelActionResult Duel_DestroyAllHandCards(u8 duelist, u8 updateGfx);
enum DuelActionResult Duel_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx);

void Duel_IncrementPermStageOnDuelistMonsters(u8 turnDuelist);
void Duel_RefreshMonsterStatOverlays(void);

void Duel_ShowEffectText(u16 cardId);
void Duel_ShowEffectTextTyped(u16 cardId, u8 textType);

enum DuelActionResult Duel_TryResolveSpellThroughTraps(u16 spellId, void (*resolveBody)(void));
enum DuelActionResult Duel_TryResolveSpellThroughTrapsEx(u16 spellId, u16 trapLp,
                                                         void (*resolveBody)(void));

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

#endif // GUARD_DUEL_HELPERS_H
