#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "elemental_hero_ice_edge.h"

void UpdateDuelGfxExceptField(void);

struct ElementalHeroIceEdgeActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct ElementalHeroIceEdgeActionData sActionData;

void ClearElementalHeroIceEdgeBattledPending(void)
{
  gElementalHeroIceEdgeBattledRow = ELEMENTAL_HERO_ICE_EDGE_BATTLED_NONE;
  gElementalHeroIceEdgeBattledCol = ELEMENTAL_HERO_ICE_EDGE_BATTLED_NONE;
}

static u8 OpponentBackrowFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? OPPONENT_BACKROW : PLAYER_BACKROW;
}

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

static u8 ZoneIsValidSetBackrowTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != OpponentBackrowFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (zone->isFaceUp)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstSetBackrowTarget(u8 *outRow, u8 *outCol)
{
  u8 row = OpponentBackrowFixedRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!ZoneIsValidSetBackrowTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static u8 PickAiSetBackrowTarget(u8 *outRow, u8 *outCol)
{
  return FindFirstSetBackrowTarget(outRow, outCol);
}

static u8 GraveyardDuelistForBackrowFixedRow(u8 fixedRow)
{
  u8 turn = WhoseTurn();

  if (fixedRow == OPPONENT_BACKROW || fixedRow == OPPONENT_MONSTER_ROW)
    return turn == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return turn == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
}

static void ResolveDestroyTarget(u8 targetRow, u8 targetCol)
{
  struct DuelCard *zone = gFixedZones[targetRow][targetCol];

  if (!ZoneIsValidSetBackrowTarget(targetRow, targetCol))
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForBackrowFixedRow(targetRow), TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
}

static void CancelDestroyTargeting(void)
{
}

static void DestroyFirstAutoTarget(void)
{
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstSetBackrowTarget(&targetRow, &targetCol))
    return;

  ResolveDestroyTarget(targetRow, targetCol);
  UpdateDuelGfxExceptField();
}

static void BeginDestroyTargeting(u8 originRow, u8 originCol)
{
  u8 targetRow;
  u8 targetCol;

  gDuelCursor.destY = originRow;
  gDuelCursor.destX = originCol;

  if (!FindFirstSetBackrowTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  Duel_SetupPickZone(ZoneIsValidSetBackrowTarget, ResolveDestroyTarget, CancelDestroyTargeting,
                     PickAiSetBackrowTarget);
  Duel_EnterPickZoneTargeting();
}

static u8 DidIceEdgeDealDirectBattleDamage(u8 *outRow, u8 *outCol)
{
  u16 damage;
  struct DuelCard *zone;

  if (sActionData.id == 4 && sActionData.playerCardId == ELEMENTAL_HERO_ICE_EDGE) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    if (damage == 0)
      return FALSE;
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (zone == NULL || zone->id != ELEMENTAL_HERO_ICE_EDGE)
      return FALSE;
    *outRow = sActionData.playerMonsterRow;
    *outCol = sActionData.unkA;
    return TRUE;
  }

  if (sActionData.id == 6 && sActionData.opponentCardId == ELEMENTAL_HERO_ICE_EDGE) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    if (damage == 0)
      return FALSE;
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (zone == NULL || zone->id != ELEMENTAL_HERO_ICE_EDGE)
      return FALSE;
    *outRow = sActionData.opponentMonsterRow;
    *outCol = sActionData.unk16;
    return TRUE;
  }

  return FALSE;
}

void ApplyElementalHeroIceEdgeBattleEffect(void)
{
  u8 row;
  u8 col;
  u8 targetRow;
  u8 targetCol;

  if (gHideEffectText)
    return;

  if (!DidIceEdgeDealDirectBattleDamage(&row, &col))
    return;

  if (!FindFirstSetBackrowTarget(&targetRow, &targetCol))
    return;

  gElementalHeroIceEdgeBattledRow = row;
  gElementalHeroIceEdgeBattledCol = col;

  /* Resolve only from post-battle sites (code_8043EF4 / AI_Main / etc.).
   * Inline PickZone here is wiped by attack cleanup (gDuelCursor.state = 0). */
}

void ResolveElementalHeroIceEdgeBattleEffect(void)
{
  u8 originRow = gElementalHeroIceEdgeBattledRow;
  u8 originCol = gElementalHeroIceEdgeBattledCol;
  struct DuelCard *zone;
  u8 targetRow;
  u8 targetCol;
  u8 hideEffectText;

  if (originRow == ELEMENTAL_HERO_ICE_EDGE_BATTLED_NONE
      || originCol == ELEMENTAL_HERO_ICE_EDGE_BATTLED_NONE)
    return;

  ClearElementalHeroIceEdgeBattledPending();

  zone = gFixedZones[originRow][originCol];
  if (zone == NULL || zone->id != ELEMENTAL_HERO_ICE_EDGE)
    return;

  if (!FindFirstSetBackrowTarget(&targetRow, &targetCol))
    return;

  hideEffectText = gHideEffectText;
  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(ELEMENTAL_HERO_ICE_EDGE,
                          CARD_EFFECT_TEXT_ELEMENTAL_HERO_ICE_EDGE_POPUP_2);
  gHideEffectText = hideEffectText;

  if (IsDuelOver() == TRUE)
    return;

  /* Printed remainder omitted by this ruleset. */
  if (WhoseTurn() != DUEL_PLAYER) {
    DestroyFirstAutoTarget();
    return;
  }

  BeginDestroyTargeting(originRow, originCol);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ElementalHeroIceEdge_BattleSelfCheck(void)
{
  if (IsSpellOrTrapCard(POLYMERIZATION) == FALSE)
    while (1)
      ;
  if (IsSpellOrTrapCard(MIRROR_FORCE) == FALSE)
    while (1)
      ;
}
#endif
