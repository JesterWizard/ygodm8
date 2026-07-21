#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "pandemonium.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void SetDuelFieldGfx(u8 field);

static const char sArchfiendName[] APPEND_RODATA = "Archfiend";
static u16 sPandemoniumSearchMaxLevel APPEND_DATA = {0};

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFieldSpellCardOnField(u16 cardId)
{
  if (cardId == PANDEMONIUM || cardId == COLOSSEUM_CAGE_OF_THE_GLADIATOR_BEASTS
      || cardId == FLAVIAN_COLOSSEUM_OF_THE_GLADIATOR_BEASTS || cardId == MYSTIC_MINE
      || cardId == HARPIES_HUNTING_GROUND || cardId == PSEUDO_SPACE
      || cardId == SKYSCRAPER_2_HERO_CITY || cardId == SKYSCRAPER || cardId == WETLANDS
      || cardId == GEARTOWN || cardId == DRAGON_RAVINE || cardId == BURNING_LAND
      || cardId == SEAL_OF_ORICHALCOS || cardId == FUSION_GATE || cardId == AMAZONESS_VILLAGE
      || cardId == NECROVALLEY || cardId == CHICKEN_GAME)
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

static void PANDEMONIUM_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  DestroyOtherFieldSpellsOnBoard(zone);

  if (IsDuelOver() == TRUE)
    return;

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(PANDEMONIUM);
  /* Parent: Pandemonium_ShouldSkipArchfiendMaintenance; effect.c ON_DESTROY Cond/Op. */
}

u8 Pandemonium_IsFaceUpOnField(void)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, PANDEMONIUM, TRUE) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, PANDEMONIUM, TRUE) != NULL;
}

u8 Pandemonium_ShouldSkipArchfiendMaintenance(u16 cardId)
{
  if (!Pandemonium_IsFaceUpOnField())
    return FALSE;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArchfiendName);
}

u8 Cond_PandemoniumOnArchfiendDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL || !Pandemonium_IsFaceUpOnField())
    return FALSE;

  ev = ctx->event;
  if (!Duel_CardNameContains(ev->cardId, sArchfiendName))
    return FALSE;

  SetCardInfo(ev->cardId);
  sPandemoniumSearchMaxLevel = gCardInfo.level;
  return sPandemoniumSearchMaxLevel > 1;
}

enum DuelActionResult Op_PandemoniumOnArchfiendDestroy(struct EffectCtx *ctx)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  u8 deckSize;
  u8 top;
  u8 i;
  s8 emptyHand;

  if (!Cond_PandemoniumOnArchfiendDestroy(ctx))
    return DUEL_ACTION_NO_TARGET;

  fixedDuelist = ctx->event->controller;
  if (fixedDuelist > DUEL_OPPONENT)
    return DUEL_ACTION_INVALID;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  emptyHand = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (emptyHand < 0)
    return DUEL_ACTION_NO_ZONE;

  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;
  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!Duel_CardNameContains(cardId, sArchfiendName))
      continue;
    SetCardInfo(cardId);
    if (gCardInfo.level >= sPandemoniumSearchMaxLevel)
      continue;

    Duel_ShowEffectText(PANDEMONIUM);
    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;

    /* Move deck card to hand (no pred). */
    {
      struct DuelCard *handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)emptyHand);

      if (handSlot == NULL)
        return DUEL_ACTION_NO_ZONE;
      if (Duel_RemoveDeckCardAt(turnDuelist, i, FALSE) != DUEL_ACTION_OK)
        return DUEL_ACTION_NO_TARGET;

      handSlot->id = cardId;
      handSlot->isFaceUp = FALSE;
      handSlot->isLocked = FALSE;
      handSlot->isDefending = FALSE;
      handSlot->unkTwo = 0;
      handSlot->unkThree = 0;
      handSlot->unk4 = 0;
      handSlot->willChangeSides = FALSE;
      ResetPermStage(handSlot);
      ResetTempStage(handSlot);
      Duel_ShuffleDeckFromDrawn(turnDuelist);
      return DUEL_ACTION_OK;
    }
  }

  return DUEL_ACTION_NO_TARGET;
}

APPEND_TEXT void EffectPANDEMONIUM(void)
{
  if (Duel_TryResolveSpellThroughTraps(PANDEMONIUM, PANDEMONIUM_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void PANDEMONIUM_SelfCheck(void)
{
  if (!Duel_CardNameContains(RED_DRAGON_ARCHFIEND, sArchfiendName))
    while (1)
      ;
  if (Duel_CardNameContains(BLUE_EYES_WHITE_DRAGON, sArchfiendName))
    while (1)
      ;
  if (!IsFieldSpellCardOnField(PANDEMONIUM))
    while (1)
      ;
}
#endif
