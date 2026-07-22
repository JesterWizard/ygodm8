#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/card_effect_texts.h"
#include "duel_helpers.h"
#include "raviel_lord_of_phantasms.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void BlockTurnSummoning(u8);

static u8 CountFiendMonstersOnField(u8 fixedDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == CARD_NONE)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.type == TYPE_FIEND)
      count++;
  }
  return count;
}

static void TributeFiendMonstersForSummon(u8 fixedDuelist)
{
  u8 fixedRow = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;
  u8 tributed = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW && tributed < RAVIEL_TRIBUTE_COST; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == CARD_NONE)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.type != TYPE_FIEND)
      continue;

    Duel_DestroyZone(zone, fixedDuelist, FALSE);
    tributed++;
  }
}

u8 CanSpecialSummonRavielLordOfPhantasmsFromHand(u8 handZone)
{
  u8 fixedDuelist;
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != RAVIEL_LORD_OF_PHANTASMS)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  return CountFiendMonstersOnField(fixedDuelist) >= RAVIEL_TRIBUTE_COST;
}

u8 TrySpecialSummonRavielLordOfPhantasmsFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  if (!CanSpecialSummonRavielLordOfPhantasmsFromHand(handZone))
    return FALSE;

  fixedDuelist = (WhoseTurn() == DUEL_PLAYER) ? DUEL_PLAYER : DUEL_OPPONENT;
  TributeFiendMonstersForSummon(fixedDuelist);

  Duel_ShowCardEffectText(RAVIEL_LORD_OF_PHANTASMS,
                          CARD_EFFECT_TEXT_RAVIEL_LORD_OF_PHANTASMS_POPUP_1);

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  BlockTurnSummoning(ACTIVE_DUELIST);
  return TRUE;
}

void TryRavielOnOpponentMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;
  u8 ravielTurnRow;
  u8 i;
  u8 hasRaviel = FALSE;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  /* Determine if this placement is on the "opponent" of Raviel's controller.
     Raviel controller could be active or inactive duelist. */
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
  {
    /* Placement on inactive row → check if active duelist has Raviel */
    ravielTurnRow = ACTIVE_DUELIST_MONSTER_ROW;
  }
  else if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
  {
    /* Placement on active row → check if inactive duelist has Raviel */
    ravielTurnRow = INACTIVE_DUELIST_MONSTER_ROW;
  }
  else
  {
    return;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
  {
    struct DuelCard *rz = gTurnZones[ravielTurnRow][i];
    if (rz->id == RAVIEL_LORD_OF_PHANTASMS && rz->isFaceUp)
    {
      hasRaviel = TRUE;
      break;
    }
  }

  if (!hasRaviel)
    return;

  /* triggers on any monster placement (Normal + Special).
     Card text says "Normal Summons" only — needs opts.markSpecialSummon check. */
  gRavielTokenSummonDuelist = (ravielTurnRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? ACTIVE_DUELIST : INACTIVE_DUELIST;
  gRavielPendingTokenCount = 1;
}
