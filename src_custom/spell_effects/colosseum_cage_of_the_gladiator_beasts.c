#include "global.h"
#include "common-chax.h"
#include "colosseum_cage_of_the_gladiator_beasts.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 sColosseumPendingDeckSummonController APPEND_DATA = {0xFF};

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS || cardId == MYSTIC_MINE
      || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE)
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

static struct DuelCard *FindFaceUpColosseumCage(u8 fixedDuelist)
{
  return Duel_FindBackrowCard(fixedDuelist, COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS, TRUE);
}

static u8 IsGladiatorBeastMonster(u16 cardId)
{
  if (cardId == CARD_NONE || !Duel_CardIsMonster(cardId))
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u8 FixedDuelistForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (zone == NULL || !Duel_FindFixedZone(zone, &fixedRow, &col))
    return 0xFF;

  if (fixedRow == PLAYER_BACKROW || fixedRow == PLAYER_MONSTER_ROW)
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

static u8 IsColosseumCageHandCard(u16 cardId)
{
  return cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS;
}

static u8 HandHasAnotherColosseumCage(u8 turnDuelist)
{
  return RowHasCardMatch(gTurnHands[turnDuelist], COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS);
}

void ApplyColosseumCageStatForZone(struct DuelCard *zone)
{
  struct DuelCard *colosseum;
  u8 fixedDuelist;
  u8 row;
  u8 col;
  u32 boosted;

  if (zone == NULL || zone->id == CARD_NONE || !ZoneShowsCombatStats(zone))
    return;

  if (!IsGladiatorBeastMonster(zone->id))
    return;

  if (!Duel_FindFixedZone(zone, &row, &col) || !Duel_IsFixedMonsterRow(row))
    return;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(row);
  colosseum = FindFaceUpColosseumCage(fixedDuelist);
  if (colosseum == NULL)
    return;

  if (colosseum->unk4 == 0)
    return;

  if (gCardInfo.atk != 0xFFFF) {
    boosted = (u32)gCardInfo.atk
              + (u32)colosseum->unk4 * COLOSSEUM_CAGE_ATK_DEF_PER_COUNTER;
    gCardInfo.atk = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }

  if (gCardInfo.def != 0xFFFF) {
    boosted = (u32)gCardInfo.def
              + (u32)colosseum->unk4 * COLOSSEUM_CAGE_ATK_DEF_PER_COUNTER;
    gCardInfo.def = boosted > 0xFFFE ? 0xFFFE : (u16)boosted;
  }
}

void ColosseumCage_MarkSpecialSummonFromDeck(u8 controllerFixedDuelist)
{
  if (controllerFixedDuelist == DUEL_PLAYER || controllerFixedDuelist == DUEL_OPPONENT)
    sColosseumPendingDeckSummonController = controllerFixedDuelist;
}

u8 Cond_ColosseumCageOnDeckSpecialSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != sColosseumPendingDeckSummonController)
    return FALSE;

  if (FindFaceUpColosseumCage(ev->controller) == NULL)
    return FALSE;

  return TRUE;
}

enum DuelActionResult Op_ColosseumCageOnDeckSpecialSummon(struct EffectCtx *ctx)
{
  struct DuelCard *colosseum;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  colosseum = FindFaceUpColosseumCage(ctx->event->controller);
  if (colosseum == NULL)
    return DUEL_ACTION_NO_TARGET;

  if (colosseum->unk4 < 255)
    colosseum->unk4++;

  sColosseumPendingDeckSummonController = 0xFF;
  RefreshFieldMonsterStatOverlays();
  return DUEL_ACTION_OK;
}

u8 ColosseumCage_TryPreventDestroyByCardEffect(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS)
    return FALSE;

  fixedDuelist = FixedDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  if (!HandHasAnotherColosseumCage(turnDuelist))
    return FALSE;

  Duel_ShowEffectText(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS);
  if (IsDuelOver() == TRUE)
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
  }

  if (Duel_DiscardFromHand(turnDuelist, 1, IsColosseumCageHandCard, TRUE) != DUEL_ACTION_OK)
    return FALSE;

  return TRUE;
}

static void COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  if (zone != NULL)
    zone->unk4 = 0;

  Duel_ShowEffectText(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS);
}

APPEND_TEXT void EffectCOLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS(void)
{
  if (Duel_TryResolveSpellThroughTraps(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS,
                                       COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS_SelfCheck(void)
{
  if (!Duel_CardNameContains(GLADIATOR_BEAST_ANDAL, sGladiatorBeastName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, sGladiatorBeastName))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS))
    while (1)
      ;
  if (COLOSSEUM_CAGE_ATK_DEF_PER_COUNTER != 100)
    while (1)
      ;
}
#endif
