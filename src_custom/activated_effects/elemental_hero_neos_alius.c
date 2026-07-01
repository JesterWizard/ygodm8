#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/monster_effects.h"
#include "duel.h"
#include "duel_helpers.h"
#include "elemental_hero_neos_alius.h"
#include "monster_effect_usage.h"

void SetCardInfo(unsigned short id);
void UpdateDuelGfxExceptField(void);

extern struct DuelCard *gSetFinalStatZone;
extern struct DuelCard *gFixedZones[5][MAX_ZONES_IN_ROW];

extern u8 gNeosAliusAwakenedBoard[NEOS_ALIUS_BOARD_CELL_COUNT];
extern u8 gApplyingNeosAliusCardInfo;

void BlockTurnSummoning(u8);
void LockMonsterCardsInRow(u8);

static u8 GetBoardPosition(struct DuelCard *zone, u8 *row, u8 *col)
{
  u8 r;
  u8 c;

  for (r = 0; r < 4; r++) {
    for (c = 0; c < MAX_ZONES_IN_ROW; c++) {
      if (&gDuel.board[r][c] == zone) {
        *row = r;
        *col = c;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static u8 *GetAwakenedEntry(u8 row, u8 col)
{
  return &gNeosAliusAwakenedBoard[row * MAX_ZONES_IN_ROW + col];
}

void ElementalHeroNeosAlius_Reset(void)
{
  u8 i;

  for (i = 0; i < NEOS_ALIUS_BOARD_CELL_COUNT; i++)
    gNeosAliusAwakenedBoard[i] = FALSE;
}

void ElementalHeroNeosAlius_ClearZone(struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (GetBoardPosition(zone, &row, &col) == FALSE)
    return;

  *GetAwakenedEntry(row, col) = FALSE;
}

u8 ElementalHeroNeosAlius_IsAwakened(struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (zone == NULL || zone->id != ELEMENTAL_HERO_NEOS_ALIUS)
    return FALSE;

  if (GetBoardPosition(zone, &row, &col) == FALSE)
    return FALSE;

  return *GetAwakenedEntry(row, col);
}

static u8 ZoneIsOnMonsterRow(struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (GetBoardPosition(zone, &row, &col) == FALSE)
    return FALSE;

  return row == OPPONENT_MONSTER_ROW || row == PLAYER_MONSTER_ROW;
}

u16 ElementalHeroNeosAlius_GetEffectiveCardId(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_NEOS_ALIUS)
    return zone != NULL ? zone->id : CARD_NONE;

  if (ZoneIsOnMonsterRow(zone))
    return ELEMENTAL_HERO_NEOS;

  return ELEMENTAL_HERO_NEOS_ALIUS;
}

static struct DuelCard *FindContextZoneForCardId(u16 cardId)
{
  struct DuelCard *zone;

  if (cardId != ELEMENTAL_HERO_NEOS_ALIUS)
    return NULL;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == cardId
      && ZoneIsOnMonsterRow(gSetFinalStatZone))
    return gSetFinalStatZone;

  if (gMonEffect.id == cardId) {
    zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
    if (zone != NULL && zone->id == cardId && ZoneIsOnMonsterRow(zone))
      return zone;
  }

  if (gDuelCursor.currentY == OPPONENT_MONSTER_ROW
      || gDuelCursor.currentY == PLAYER_MONSTER_ROW) {
    zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];
    if (zone != NULL && zone->id == cardId)
      return zone;
  }

  return NULL;
}

void ElementalHeroNeosAlius_ApplyCardInfoOverridesFromContext(u16 cardId)
{
  struct DuelCard *zone;

  if (gApplyingNeosAliusCardInfo)
    return;

  zone = FindContextZoneForCardId(cardId);
  if (zone != NULL)
    ElementalHeroNeosAlius_ApplyCardInfoOverrides(zone);
}

void ElementalHeroNeosAlius_ApplyCardInfoOverrides(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != ELEMENTAL_HERO_NEOS_ALIUS)
    return;

  if (!ZoneIsOnMonsterRow(zone))
    return;

  {
    const u8 *neosName;

    gApplyingNeosAliusCardInfo = TRUE;
    SetCardInfo(ELEMENTAL_HERO_NEOS);
    neosName = gCardInfo.name;
    SetCardInfo(ELEMENTAL_HERO_NEOS_ALIUS);
    gApplyingNeosAliusCardInfo = FALSE;
    gCardInfo.name = (u8 *)neosName;
    gCardInfo.nameUnused = (u8 *)neosName;
  }

  if (!ElementalHeroNeosAlius_IsAwakened(zone)) {
    gCardInfo.color = NORMAL_CARD;
    gCardInfo.monsterEffect = MONSTER_EFFECT_NONE;
  }
}

unsigned char CanActivateElementalHeroNeosAlius(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (gMonEffect.id != ELEMENTAL_HERO_NEOS_ALIUS)
    return FALSE;

  if (!zone->isFaceUp)
    return FALSE;

  if (ElementalHeroNeosAlius_IsAwakened(zone))
    return FALSE;

  if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    return FALSE;

  return TRUE;
}

void ActivateElementalHeroNeosAliusEffect(void)
{
  struct DuelCard *zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 row;
  u8 col;

  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_NEOS_ALIUS, 2);

  if (IsDuelOver())
    return;

  if (GetBoardPosition(zone, &row, &col) == FALSE)
    return;

  *GetAwakenedEntry(row, col) = TRUE;
  BlockTurnSummoning(ACTIVE_DUELIST);
  LockMonsterCardsInRow(4);
  UpdateDuelGfxExceptField();
}

#if !defined(__GNUC__)
#error Elemental HERO Neos Alius self-check requires GCC
#elif __GNUC__
void ElementalHeroNeosAlius_SelfCheck(void)
{
  struct DuelCard zone = {ELEMENTAL_HERO_NEOS_ALIUS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  ElementalHeroNeosAlius_Reset();
  zone.isFaceUp = TRUE;
  gDuel.board[PLAYER_MONSTER_ROW][0] = zone;

  if (ElementalHeroNeosAlius_IsAwakened(&gDuel.board[PLAYER_MONSTER_ROW][0]) != FALSE)
    while (1)
      ;
  if (ElementalHeroNeosAlius_GetEffectiveCardId(&gDuel.board[PLAYER_MONSTER_ROW][0]) != ELEMENTAL_HERO_NEOS)
    while (1)
      ;

  *GetAwakenedEntry(PLAYER_MONSTER_ROW, 0) = TRUE;
  if (ElementalHeroNeosAlius_IsAwakened(&gDuel.board[PLAYER_MONSTER_ROW][0]) == FALSE)
    while (1)
      ;
}
#endif
