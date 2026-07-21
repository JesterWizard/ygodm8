#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

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

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

/* Printed NEX pairs: Aqua Dolphin → Marine Dolphin, Glow Moss → Twinkle Moss. */
static u16 NexLv4FormFor(u16 neoSpacianId)
{
  switch (neoSpacianId) {
  case NEO_SPACIAN_AQUA_DOLPHIN:
    return NEO_SPACIAN_MARINE_DOLPHIN;
  case NEO_SPACIAN_GLOW_MOSS:
    return NEO_SPACIAN_TWINKLE_MOSS;
  default:
    return CARD_NONE;
  }
}

static u8 IsValidNexTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != ActiveMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || !MonsterIsFaceUp(zone) || !IsNeoSpacianMonster(zone->id))
    return FALSE;

  return NexLv4FormFor(zone->id) != CARD_NONE;
}

static u8 HasNexTarget(void)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidNexTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateNEX(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return HasNexTarget();
}

static void DestroyNexSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == NEX)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static u8 DeckHasCard(u8 turnDuelist, u16 cardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == cardId)
      return TRUE;
  }

  return FALSE;
}

static void FinishNex(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *targetZone = gFixedZones[fixedRow][fixedCol];
  u16 lv4Form;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!IsValidNexTarget(fixedRow, fixedCol)) {
    DestroyNexSpellZone();
    return;
  }

  lv4Form = NexLv4FormFor(targetZone->id);

  DestroyNexSpellZone();
  if (IsDuelOver() == TRUE)
    return;

  if (Duel_DestroyZone(targetZone, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  if (lv4Form == CARD_NONE || Duel_CardCannotBeSpecialSummoned(lv4Form))
    return;

  if (DeckHasCard(ACTIVE_DUELIST, lv4Form)) {
    Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, lv4Form, opts);
    return;
  }

  Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, lv4Form, opts);
}

static void CancelNexTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyNexSpellZone();
}

static u8 AiPickNexTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = ActiveMonsterFixedRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (!IsValidNexTarget(row, col))
      continue;

    *outRow = row;
    *outCol = col;
    return TRUE;
  }

  return FALSE;
}

static void ResolveNexTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidNexTarget(fixedRow, fixedCol))
    return;

  FinishNex(fixedRow, fixedCol);
}

static void NEX_ResolveBody(void)
{
  Duel_ShowEffectText(NEX);

  if (IsDuelOver() == TRUE || !CanActivateNEX())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidNexTarget, ResolveNexTarget, CancelNexTargeting, AiPickNexTarget);

  if (WhoseTurn() != DUEL_PLAYER)
    Duel_ResolvePickZoneForAi();
  else
    Duel_EnterPickZoneTargeting();
}

APPEND_TEXT void EffectNEX(void)
{
  if (!CanActivateNEX()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(NEX, NEX_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
