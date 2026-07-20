#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

extern int NumCardsInDeck(unsigned char);

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 ActiveMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsTributeableMonster(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

/* Normal Summonable/Set: Normal/Effect monsters (not Fusion/Ritual/etc.). */
static u8 IsNormalSummonableMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color == COLOR_NORMAL || gCardInfo.color == COLOR_EFFECT;
}

static u8 IsValidTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL)
    return FALSE;

  return IsTributeableMonster(zone->id);
}

static u8 HasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidTributeTarget(ActiveMonsterFixedRow(), col))
      return TRUE;
  }

  return FALSE;
}

static u8 DeckHasRemainingCards(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  return gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist);
}

u8 CanActivateMONSTER_GATE(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (!HasTributeTarget())
    return FALSE;

  return DeckHasRemainingCards();
}

static void DestroyMonsterGateSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == MONSTER_GATE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

/* Excavate top until Normal Summonable; SS it; rest already pushed to GY. */
static enum DuelActionResult ExcavateAndSpecialSummon(void)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 foundId = CARD_NONE;

  while (gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist)) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];

    gDuelDecks[fixedDuelist].cardsDrawn++;

    if (IsNormalSummonableMonster(cardId)) {
      foundId = cardId;
      break;
    }

    /* Non-matches go to GY (PushTurn also covers legacy-only mode). */
    GraveyardExpand_PushTurn(ACTIVE_DUELIST, cardId);
  }

  if (foundId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, foundId, opts);
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *tributeZone = gFixedZones[fixedRow][fixedCol];

  if (!IsValidTributeTarget(fixedRow, fixedCol))
    return;

  if (ArchlordKristya_IsSpecialSummonLocked() || !DeckHasRemainingCards())
    return;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   FALSE);

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_TRIBUTE);

  if (Duel_DestroyZone(tributeZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  ExcavateAndSpecialSummon();
  UpdateDuelGfxExceptField();
}

static void CancelTributeTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyMonsterGateSpellZone();
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 monsterRow = ActiveMonsterFixedRow();
  u16 bestAtk = 0xFFFF;
  u8 found = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsValidTributeTarget(monsterRow, col))
      continue;

    zone = gFixedZones[monsterRow][col];
    SetCardInfo(zone->id);
    atk = gCardInfo.atk;
    if (!found || atk < bestAtk) {
      found = TRUE;
      bestAtk = atk;
      *outRow = monsterRow;
      *outCol = col;
    }
  }

  return found;
}

static void MONSTER_GATE_ResolveBody(void)
{
  Duel_ShowEffectText(MONSTER_GATE);

  if (IsDuelOver() == TRUE || !CanActivateMONSTER_GATE())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidTributeTarget, ResolveTributeTarget, CancelTributeTargeting,
                     AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectMONSTER_GATE(void)
{
  if (!CanActivateMONSTER_GATE()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MONSTER_GATE, MONSTER_GATE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MONSTER_GATE_SelfCheck(void)
{
  if (!IsNormalSummonableMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (IsNormalSummonableMonster(POLYMERIZATION))
    while (1)
      ;
}
#endif
