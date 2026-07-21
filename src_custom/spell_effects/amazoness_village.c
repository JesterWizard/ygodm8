#include "global.h"
#include "common-chax.h"
#include "amazoness_village.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

#define AMAZONESS_VILLAGE_ATK_BOOST 200

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == AMAZONESS_VILLAGE || cardId == HARPIES_HUNTING_GROUND
      || cardId == PSEUDO_SPACE || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER
      || cardId == WETLANDS || cardId == GEARTOWN || cardId == DRAGON_RAVINE
      || cardId == BURNING_LAND || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
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

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 MonsterTurnRowForFixed(u8 fixedDuelist)
{
  return TurnDuelistForFixed(fixedDuelist) == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 MonsterLevel(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return 0;

  return gCardData_NEW[cardId].level;
}

static u16 FindAmazonessInDeckLevelAtMost(u8 fixedDuelist, u8 maxLevel)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_IsAmazonessCard(cardId))
      continue;
    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;
    if (MonsterLevel(cardId) > maxLevel)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    return cardId;
  }

  return CARD_NONE;
}

void ApplyAmazonessVillageFieldStatBoostForZone(struct DuelCard *zone)
{
  u32 boosted;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  /* Field presence first — avoids SetCardInfo name scan when Village is off. */
  if (Duel_FindBackrowCardOnField(AMAZONESS_VILLAGE, TRUE) == NULL)
    return;

  if (!Duel_IsAmazonessCard(zone->id))
    return;

  if (gCardInfo.atk != 0xFFFF) {
    boosted = (u32)gCardInfo.atk + AMAZONESS_VILLAGE_ATK_BOOST;
    gCardInfo.atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
}

u8 Cond_AmazonessVillageDestroySs(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 maxLevel;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!Duel_IsAmazonessCard(ev->cardId))
    return FALSE;

  fixedDuelist = ev->controller;
  if (Duel_FindBackrowCard(fixedDuelist, AMAZONESS_VILLAGE, TRUE) == NULL)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterTurnRowForFixed(fixedDuelist)]) < 0) {
    if (ev->fixedRow != PLAYER_MONSTER_ROW && ev->fixedRow != OPPONENT_MONSTER_ROW)
      return FALSE;
    if (Duel_FixedDuelistForMonsterRow(ev->fixedRow) != fixedDuelist)
      return FALSE;
  }

  maxLevel = MonsterLevel(ev->cardId);
  return FindAmazonessInDeckLevelAtMost(fixedDuelist, maxLevel) != CARD_NONE;
}

enum DuelActionResult Op_AmazonessVillageDestroySs(struct EffectCtx *ctx)
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
  cardId = FindAmazonessInDeckLevelAtMost(fixedDuelist, MonsterLevel(ev->cardId));
  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShowEffectText(AMAZONESS_VILLAGE);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  return Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
}

static void AMAZONESS_VILLAGE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(AMAZONESS_VILLAGE);
}

APPEND_TEXT void EffectAMAZONESS_VILLAGE(void)
{
  if (Duel_TryResolveSpellThroughTraps(AMAZONESS_VILLAGE, AMAZONESS_VILLAGE_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void AMAZONESS_VILLAGE_SelfCheck(void)
{
  if (!Duel_IsAmazonessCard(AMAZONESS_QUEEN))
    while (1)
      ;
  if (Duel_IsAmazonessCard(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(AMAZONESS_VILLAGE))
    while (1)
      ;
}
#endif
