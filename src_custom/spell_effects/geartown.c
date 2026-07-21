#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "geartown.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static const char sAncientGearName[] APPEND_RODATA = "Ancient Gear";

static u8 IsAncientGearMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAncientGearName);
}

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS)
    return TRUE;

  return IsVanillaTerrainFieldSpell(cardId);
}

static u8 GetTurnDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void ResetActiveFieldTerrain(void)
{
  RevertCustomFieldToArena();

  if (gDuel.field == FIELD_ARENA)
    return;

  gDuel.field = FIELD_ARENA;

  if (!gHideEffectText)
    SetDuelFieldGfx(gDuel.field);
}

static void DestroyOtherFieldSpellsOnBoard(struct DuelCard *activatingZone)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == activatingZone || zone->id == CARD_NONE)
        continue;

      if (!IsFieldSpellCardOnField(zone->id))
        continue;

      Duel_DestroyZone(zone, GetTurnDuelistForFixedRow(row), FALSE);

      if (IsDuelOver() == TRUE)
        return;
    }
  }

  ResetActiveFieldTerrain();
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

u8 Geartown_ReduceRequiredTributes(u16 cardId, int requiredTributes)
{
  if (requiredTributes <= 0 || !IsAncientGearMonster(cardId))
    return (u8)requiredTributes;

  if (Duel_FindBackrowCard(FixedDuelistForActive(), GEARTOWN, TRUE) == NULL)
    return (u8)requiredTributes;

  return (u8)(requiredTributes - 1);
}

static u16 FindAncientGearInHand(u8 turnDuelist)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 id = gTurnHands[turnDuelist][col]->id;

    if (IsAncientGearMonster(id) && !Duel_CardCannotBeSpecialSummoned(id))
      return id;
  }

  return CARD_NONE;
}

static u16 FindAncientGearInDeck(u8 fixedDuelist)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 id = gDuelDecks[fixedDuelist].cards[i];

    if (IsAncientGearMonster(id) && !Duel_CardCannotBeSpecialSummoned(id))
      return id;
  }

  return CARD_NONE;
}

static u16 FindAncientGearInGy(u8 fixedDuelist)
{
  u8 count = GraveyardExpand_GetCount(fixedDuelist);
  u8 i;

  for (i = 0; i < count; i++) {
    u16 id = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsAncientGearMonster(id) && !Duel_CardCannotBeSpecialSummoned(id))
      return id;
  }

  return CARD_NONE;
}

u8 Cond_GeartownOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != GEARTOWN)
    return FALSE;

  fixedDuelist = ev->controller;
  if (fixedDuelist != DUEL_PLAYER && fixedDuelist != DUEL_OPPONENT)
    return FALSE;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
                                         ? ACTIVE_DUELIST_MONSTER_ROW
                                         : INACTIVE_DUELIST_MONSTER_ROW])
      < 0)
    return FALSE;

  return FindAncientGearInHand(turnDuelist) != CARD_NONE
      || FindAncientGearInDeck(fixedDuelist) != CARD_NONE
      || FindAncientGearInGy(fixedDuelist) != CARD_NONE;
}

enum DuelActionResult Op_GeartownOnDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  fixedDuelist = ev->controller;
  turnDuelist = TurnDuelistForFixed(fixedDuelist);

  Duel_ShowEffectText(GEARTOWN);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;

  cardId = FindAncientGearInHand(turnDuelist);
  if (cardId != CARD_NONE)
    return Duel_SpecialSummonFromHand(turnDuelist, cardId, NULL, opts);

  cardId = FindAncientGearInDeck(fixedDuelist);
  if (cardId != CARD_NONE)
    return Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);

  cardId = FindAncientGearInGy(fixedDuelist);
  if (cardId != CARD_NONE)
    return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);

  return DUEL_ACTION_NO_TARGET;
}

static void GEARTOWN_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(GEARTOWN);
}

APPEND_TEXT void EffectGEARTOWN(void)
{
  if (Duel_TryResolveSpellThroughTraps(GEARTOWN, GEARTOWN_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GEARTOWN_SelfCheck(void)
{
  if (!IsAncientGearMonster(ANCIENT_GEAR_GOLEM))
    while (1)
      ;
  if (IsAncientGearMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
