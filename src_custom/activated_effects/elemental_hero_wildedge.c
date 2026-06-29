#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "elemental_hero_wildedge.h"
#include "monster_effect_usage.h"
#include "the_dark_door.h"

extern u8 gElementalHeroWildedgeAttackedMask;
extern u8 gElementalHeroWildedgeEffectActive;
extern u8 gElementalHeroWildedgeAnchorRow;
extern u8 gElementalHeroWildedgeAnchorCol;

#define WILDEDGE_ZONE_NONE 0xFF

void ClearElementalHeroWildedgeState(void)
{
  gElementalHeroWildedgeAttackedMask = 0;
  gElementalHeroWildedgeEffectActive = FALSE;
  gElementalHeroWildedgeAnchorRow = WILDEDGE_ZONE_NONE;
  gElementalHeroWildedgeAnchorCol = WILDEDGE_ZONE_NONE;
}

static u8 OpponentMonsterTurnRow(void)
{
  return WhoseTurn() == DUEL_PLAYER
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;
}

static u8 OpponentHasMonsterOnField(void)
{
  u8 row = OpponentMonsterTurnRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[row][col]->id != CARD_NONE)
      return TRUE;
  }

  return FALSE;
}

static u8 HasUnattackedOpponentMonster(void)
{
  u8 row = OpponentMonsterTurnRow();
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[row][col]->id == CARD_NONE)
      continue;

    if ((gElementalHeroWildedgeAttackedMask & (1u << col)) == 0)
      return TRUE;
  }

  return FALSE;
}

static u8 AttackerIsActiveWildedge(struct DuelCard *attacker)
{
  u8 turnRow;
  u8 col;

  if (!gElementalHeroWildedgeEffectActive)
    return FALSE;

  if (attacker == NULL || attacker->id != ELEMENTAL_HERO_WILDEDGE)
    return FALSE;

  if (gElementalHeroWildedgeAnchorRow == WILDEDGE_ZONE_NONE)
    return FALSE;

  if (!Duel_FindTurnMonsterZone(attacker, &turnRow, &col))
    return FALSE;

  return turnRow == gElementalHeroWildedgeAnchorRow
      && col == gElementalHeroWildedgeAnchorCol;
}

static void MarkDefenderAttacked(struct DuelCard *defender)
{
  u8 turnRow;
  u8 col;

  if (defender == NULL || defender->id == CARD_NONE)
    return;

  if (!Duel_FindTurnMonsterZone(defender, &turnRow, &col))
    return;

  if (turnRow != OpponentMonsterTurnRow())
    return;

  gElementalHeroWildedgeAttackedMask |= (1u << col);
}

unsigned char CanActivateElementalHeroWildedge(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ELEMENTAL_HERO_WILDEDGE)
    return FALSE;

  if (gMonEffect.row != PLAYER_MONSTER_ROW && gMonEffect.row != OPPONENT_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return OpponentHasMonsterOnField();
}

void ActivateElementalHeroWildedgeEffect(void)
{
  Duel_ShowEffectTextTyped(ELEMENTAL_HERO_WILDEDGE, 2);

  if (IsDuelOver() == TRUE)
    return;

  gElementalHeroWildedgeAttackedMask = 0;
  gElementalHeroWildedgeEffectActive = TRUE;
  gElementalHeroWildedgeAnchorRow = gMonEffect.row;
  gElementalHeroWildedgeAnchorCol = gMonEffect.zone;
}

void TryUnlockElementalHeroWildedgeForNextAttack(struct DuelCard *attacker,
                                                 struct DuelCard *defender)
{
  if (!AttackerIsActiveWildedge(attacker))
    return;

  if (IsTheDarkDoorActiveOnField())
    return;

  MarkDefenderAttacked(defender);

  if (HasUnattackedOpponentMonster())
    attacker->isLocked = FALSE;
}
