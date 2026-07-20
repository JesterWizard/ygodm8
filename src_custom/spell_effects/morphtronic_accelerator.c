#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicArchetypeName[] APPEND_RODATA = "Morphtronic";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicArchetypeName);
}

static u8 HandHasMorphtronic(struct DuelCard **handRow)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMorphtronicMonster(handRow[i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow > PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return Duel_SpellMayTargetMonsterZone(zone);

  return TRUE;
}

static u8 HasDestroyTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDestroyTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateMORPHTRONIC_ACCELERATOR(void)
{
  /* Spell itself is a valid destroy target once activated on empty boards. */
  return HandHasMorphtronic(gTurnHands[ACTIVE_DUELIST]);
}

static s8 PickMorphtronicHandZone(struct DuelCard **handRow)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(handRow, IsMorphtronicMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMorphtronicMonster(handRow[i]->id))
      return (s8)i;
  }

  return -1;
}

static void ReturnHandCardToDeck(u8 turnDuelist, u8 handZone)
{
  struct DuelCard *handCard = gTurnHands[turnDuelist][handZone];
  u16 cardId = handCard->id;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (cardId == CARD_NONE)
    return;

  ClearZone(handCard);

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

static void DestroyAcceleratorSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MORPHTRONIC_ACCELERATOR)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void FinishAccelerator(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidDestroyTarget(fixedRow, fixedCol))
    return;

  if (Duel_DestroyZone(zone, GraveyardDuelistForFixedRow(fixedRow), FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DrawCards(ACTIVE_DUELIST, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  DestroyAcceleratorSpellZone();
}

static void CancelAcceleratorTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyAcceleratorSpellZone();
}

static u8 AiPickDestroyTarget(u8 *outRow, u8 *outCol)
{
  u8 pass;
  u8 row;
  u8 col;
  u8 inactiveMonster = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW
                                                  : PLAYER_MONSTER_ROW;
  u8 inactiveBackrow = WhoseTurn() == DUEL_PLAYER ? OPPONENT_BACKROW
                                                  : PLAYER_BACKROW;
  u8 activeMonster = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW
                                                : OPPONENT_MONSTER_ROW;
  u8 activeBackrow = WhoseTurn() == DUEL_PLAYER ? PLAYER_BACKROW
                                                : OPPONENT_BACKROW;
  u8 preferRows[4];

  preferRows[0] = inactiveMonster;
  preferRows[1] = inactiveBackrow;
  preferRows[2] = activeMonster;
  preferRows[3] = activeBackrow;

  for (pass = 0; pass < 4; pass++) {
    row = preferRows[pass];
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (!IsValidDestroyTarget(row, col))
        continue;

      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDestroyTarget(u8 fixedRow, u8 fixedCol)
{
  FinishAccelerator(fixedRow, fixedCol);
}

static void BeginDestroyPick(void)
{
  Duel_SetupPickZone(IsValidDestroyTarget, ResolveDestroyTarget, CancelAcceleratorTargeting,
                     AiPickDestroyTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

static void MORPHTRONIC_ACCELERATOR_ResolveBody(void)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 handZone;

  Duel_ShowEffectText(MORPHTRONIC_ACCELERATOR);

  if (IsDuelOver() == TRUE || !CanActivateMORPHTRONIC_ACCELERATOR())
    return;

  handZone = PickMorphtronicHandZone(handRow);
  if (handZone < 0)
    return;

  ReturnHandCardToDeck(ACTIVE_DUELIST, (u8)handZone);
  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  if (!HasDestroyTarget()) {
    DestroyAcceleratorSpellZone();
    return;
  }

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;
  BeginDestroyPick();
}

APPEND_TEXT void EffectMORPHTRONIC_ACCELERATOR(void)
{
  if (!CanActivateMORPHTRONIC_ACCELERATOR()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_ACCELERATOR,
                                       MORPHTRONIC_ACCELERATOR_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MorphtronicAccelerator_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_CELFON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
