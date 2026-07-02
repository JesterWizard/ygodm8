#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "blowback_dragon.h"
#include "black_luster_soldier_envoy_of_the_beginning.h"
#include "breaker_the_magical_warrior.h"
#include "caius_the_shadow_monarch.h"
#include "dark_magician_knight.h"
#include "harpies_pet_baby_dragon.h"
#include "invader_of_the_throne.h"
#include "jowls_of_dark_demise.h"
#include "kaiser_glider.h"
#include "mobius_the_frost_monarch.h"
#include "ryu_kishin_clown.h"
#include "zaborg_the_thunder_monarch.h"
#include "elemental_hero_terra_firma.h"

void ResetCursorDestToCurrentPos(void);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

u16 gChaosCommandMagicianBlockedOriginMonsterEffectId APPEND_DATA = CARD_NONE;

static u16 GetMonsterEffectTargetingOriginId(void)
{
  struct DuelCard *origin;

  if (gMonEffect.id != CARD_NONE && GetTypeGroup(gMonEffect.id) == TYPE_GROUP_MONSTER)
    return gMonEffect.id;

  if (gActiveEffect.cardId != CARD_NONE
      && GetTypeGroup(gActiveEffect.cardId) == TYPE_GROUP_MONSTER)
    return gActiveEffect.cardId;

  origin = gFixedZones[gDuelCursor.destY][gDuelCursor.destX];
  if (origin != NULL && origin->id != CARD_NONE
      && GetTypeGroup(origin->id) == TYPE_GROUP_MONSTER)
    return origin->id;

  return CARD_NONE;
}

static u8 IsMonsterEffectTargetingCursorState(u8 state)
{
  switch (state) {
    case DUEL_CURSOR_BREAKER_THE_MAGICAL_WARRIOR_TARGET:
    case DUEL_CURSOR_JOWLS_OF_DARK_DEMISE_TARGET:
    case DUEL_CURSOR_INVADER_OF_THE_THRONE_TARGET:
    case DUEL_CURSOR_DARK_MAGICIAN_KNIGHT_TARGET:
    case DUEL_CURSOR_ZABORG_THE_THUNDER_MONARCH_TARGET:
    case DUEL_CURSOR_CAIUS_THE_SHADOW_MONARCH_TARGET:
    case DUEL_CURSOR_MOBIUS_THE_FROST_MONARCH_TARGET:
    case DUEL_CURSOR_RYU_KISHIN_CLOWN_TARGET:
    case DUEL_CURSOR_KAISER_GLIDER_TARGET:
    case DUEL_CURSOR_HARPIES_PET_BABY_DRAGON_TARGET:
    case DUEL_CURSOR_BLOWBACK_DRAGON_TARGET:
    case DUEL_CURSOR_BLACK_LUSTER_SOLDIER_ENVOY_TARGET:
    case DUEL_CURSOR_TERRA_FIRMA_TARGET:
    case DUEL_CURSOR_PICK_ZONE:
      return TRUE;
    default:
      return FALSE;
  }
}

static void FinishNegatedMonsterEffectTarget(void)
{
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void FinishNegatedMonsterEffectTargetForAi(void)
{
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static u8 TryNegateChaosCommandMagicianFromZone(u16 originCardId, struct DuelCard *zone)
{
  if (originCardId == CHAOS_COMMAND_MAGICIAN)
    return FALSE;

  if (originCardId == CARD_NONE || originCardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (GetTypeGroup(originCardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (zone == NULL || zone->id != CHAOS_COMMAND_MAGICIAN || !zone->isFaceUp)
    return FALSE;

  if (!gHideEffectText) {
    ResetCardEffectTextData();
    SetCardEffectTextType(8);
    gCardEffectTextData.cardId = CHAOS_COMMAND_MAGICIAN;
    gCardEffectTextData.cardId2 = originCardId;
    ActivateCardEffectText();
  }

  return TRUE;
}

u8 TryNegateChaosCommandMagicianTargetedMonsterEffect(u16 originCardId, u8 targetFixedRow,
                                                      u8 targetFixedCol)
{
  struct DuelCard *target;

  if (targetFixedRow >= 4 || targetFixedCol >= MAX_ZONES_IN_ROW)
    return FALSE;

  target = gFixedZones[targetFixedRow][targetFixedCol];
  return TryNegateChaosCommandMagicianFromZone(originCardId, target);
}

u8 Duel_TryNegateMonsterEffectOnTarget(u16 originCardId, u8 targetFixedRow, u8 targetFixedCol)
{
  return TryNegateChaosCommandMagicianTargetedMonsterEffect(originCardId, targetFixedRow,
                                                            targetFixedCol);
}

u8 Duel_TryNegateMonsterEffectOnZone(u16 originCardId, struct DuelCard *zone)
{
  if (!TryNegateChaosCommandMagicianFromZone(originCardId, zone))
    return FALSE;

  gChaosCommandMagicianBlockedOriginMonsterEffectId = originCardId;
  return TRUE;
}

u8 Duel_ShouldSuppressChaosCommandMagicianBlockedMonsterEffectText(u16 cardId)
{
  if (gChaosCommandMagicianBlockedOriginMonsterEffectId == CARD_NONE)
    return FALSE;

  if (cardId != gChaosCommandMagicianBlockedOriginMonsterEffectId)
    return FALSE;

  gChaosCommandMagicianBlockedOriginMonsterEffectId = CARD_NONE;
  return TRUE;
}

u8 Duel_TryNegateMonsterEffectTargetSelection(void)
{
  u16 originId;
  u8 targetRow;
  u8 targetCol;

  if (!IsMonsterEffectTargetingCursorState(gDuelCursor.state))
    return FALSE;

  originId = GetMonsterEffectTargetingOriginId();
  targetRow = gDuelCursor.currentY;
  targetCol = gDuelCursor.currentX;

  if (!Duel_TryNegateMonsterEffectOnTarget(originId, targetRow, targetCol))
    return FALSE;

  FinishNegatedMonsterEffectTarget();
  return TRUE;
}

u8 Duel_MonsterEffectConfirmTargetForAi(u16 originCardId, u8 targetRow, u8 targetCol)
{
  if (!Duel_TryNegateMonsterEffectOnTarget(originCardId, targetRow, targetCol))
    return FALSE;

  FinishNegatedMonsterEffectTargetForAi();
  return TRUE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ChaosCommandMagician_SelfCheck(void)
{
  if (TryNegateChaosCommandMagicianTargetedMonsterEffect(BLOWBACK_DRAGON, PLAYER_MONSTER_ROW, 0)
      != FALSE)
    __builtin_trap();
  if (TryNegateChaosCommandMagicianTargetedMonsterEffect(BOOK_OF_MOON, PLAYER_MONSTER_ROW, 0)
      != FALSE)
    __builtin_trap();
  if (TryNegateChaosCommandMagicianTargetedMonsterEffect(CHAOS_COMMAND_MAGICIAN,
                                                         PLAYER_MONSTER_ROW, 0)
      != FALSE)
    __builtin_trap();
}
#endif
