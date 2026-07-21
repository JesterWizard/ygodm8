#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "effect.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

/* Approximate "mentions Dark Magician" via name or known support IDs. */
static const u16 sDmMentionSupport[] APPEND_RODATA = {
  DARK_MAGICIAN,
  DARK_MAGICIAN_GIRL,
  DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT,
  THE_DARK_MAGICIANS,
  MAGICIANS_ROD,
  DARK_MAGIC_CURTAIN,
  THOUSAND_KNIVES,
  SAGES_STONE,
  DEDICATION_THROUGH_LIGHT_AND_DARKNESS,
  DARK_MAGIC_ATTACK,
  DARK_MAGIC_VEIL,
  DARK_MAGICAL_CIRCLE,
  BOND_BETWEEN_TEACHER_AND_STUDENT,
  DARK_BURNING_ATTACK,
  DARK_BURNING_MAGIC,
  ILLUSION_MAGIC,
  MAGICIAN_NAVIGATION,
  SECRETS_OF_DARK_MAGIC,
  ETERNAL_SOUL,
  DARK_MAGIC_RITUAL,
  DARK_MAGIC_INHERITANCE,
};

static const u8 sDmcPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 sDarkMagicianCircleTriggerOwner APPEND_DATA = {0xFF};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
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
}

static u8 MentionsDarkMagician(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == DARK_MAGICIAN)
    return TRUE;

  for (i = 0; i < ARRAY_COUNT(sDmMentionSupport); i++) {
    if (cardId == sDmMentionSupport[i])
      return TRUE;
  }

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u8 IsDmcLookTarget(u16 cardId)
{
  if (cardId == DARK_MAGICIAN)
    return TRUE;

  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return MentionsDarkMagician(cardId);
}

static u8 IsDarkMagicianCircleOpponentRow(u8 fixedRow)
{
  if (sDarkMagicianCircleTriggerOwner == DUEL_PLAYER)
    return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == OPPONENT_BACKROW;

  if (sDarkMagicianCircleTriggerOwner == DUEL_OPPONENT)
    return fixedRow == PLAYER_MONSTER_ROW || fixedRow == PLAYER_BACKROW;

  return FALSE;
}

static u8 IsDarkMagicianCircleBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!IsDarkMagicianCircleOpponentRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || Duel_ZoneIsImmuneToSpellEffects(zone))
    return FALSE;

  return !Duel_IsFixedMonsterRow(fixedRow) || Duel_SpellMayTargetMonsterZone(zone);
}

static u8 HasDarkMagicianCircleBanishTarget(u8 fixedDuelist)
{
  u8 rows[2];
  u8 rowIndex;
  u8 col;

  if (fixedDuelist == DUEL_PLAYER) {
    rows[0] = OPPONENT_MONSTER_ROW;
    rows[1] = OPPONENT_BACKROW;
  } else if (fixedDuelist == DUEL_OPPONENT) {
    rows[0] = PLAYER_MONSTER_ROW;
    rows[1] = PLAYER_BACKROW;
  } else {
    return FALSE;
  }

  sDarkMagicianCircleTriggerOwner = fixedDuelist;
  for (rowIndex = 0; rowIndex < ARRAY_COUNT(rows); rowIndex++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDarkMagicianCircleBanishTarget(rows[rowIndex], col))
        return TRUE;
    }
  }

  return FALSE;
}

static void ResolveDarkMagicianCircleBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_ClearPickZone();
  if (!IsDarkMagicianCircleBanishTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  Duel_BanishZone(zone, TRUE);
  UpdateDuelGfxExceptField();
}

static u8 AiPickDarkMagicianCircleBanishTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsDarkMagicianCircleBanishTarget(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Cond_DarkMagicianCircleOnDarkMagicianSummon(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != DARK_MAGICIAN || ev->controller > DUEL_OPPONENT)
    return FALSE;
  if (EffectOpt_IsUsed(DARK_MAGICIAN_CIRCLE))
    return FALSE;

  if (Duel_FindBackrowCard(ev->controller, DARK_MAGICIAN_CIRCLE, TRUE) == NULL)
    return FALSE;

  return HasDarkMagicianCircleBanishTarget(ev->controller);
}

enum DuelActionResult Op_DarkMagicianCircleOnDarkMagicianSummon(struct EffectCtx *ctx)
{
  struct DuelCard *circle;
  u8 row;
  u8 col;

  if (!Cond_DarkMagicianCircleOnDarkMagicianSummon(ctx))
    return DUEL_ACTION_NO_TARGET;

  circle = Duel_FindBackrowCard(ctx->event->controller, DARK_MAGICIAN_CIRCLE, TRUE);
  if (circle == NULL || !Duel_FindFixedZone(circle, &row, &col))
    return DUEL_ACTION_NO_TARGET;

  /* EffectOpt is cleared by EffectEvent_OnTurnBoundary. */
  EffectOpt_MarkUsed(DARK_MAGICIAN_CIRCLE);
  sDarkMagicianCircleTriggerOwner = ctx->event->controller;
  gDuelCursor.destY = row;
  gDuelCursor.destX = col;
  Duel_SetupPickZone(IsDarkMagicianCircleBanishTarget, ResolveDarkMagicianCircleBanishTarget,
                     Duel_ClearPickZone, AiPickDarkMagicianCircleBanishTarget);
  if (ctx->event->controller == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();

  return DUEL_ACTION_OK;
}

static void PlaceCardOnDeckTop(u8 fixedDuelist, u16 cardId)
{
  if (cardId == CARD_NONE)
    return;

  if (gDuelDecks[fixedDuelist].cardsDrawn > 0)
    gDuelDecks[fixedDuelist].cardsDrawn--;

  gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn] = cardId;
}

/* Look at top 3; optionally add 1 DM / DM-mention ST; rest on top (order preserved). */
static void ResolveDarkMagicalCircleLook(u16 effectCardId)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 peeked[3];
  u8 peekCount = 0;
  u8 i;
  s8 empty;
  s8 addIdx = -1;
  u8 menuCount = 0;
  u8 menuMap[3];
  u8 savedDeckMenu[sizeof(gDeckMenu)];

  while (peekCount < 3 && gDuelDecks[fixedDuelist].cardsDrawn < NumCardsInDeck(fixedDuelist)) {
    peeked[peekCount] = gDuelDecks[fixedDuelist].cards[gDuelDecks[fixedDuelist].cardsDrawn];
    gDuelDecks[fixedDuelist].cardsDrawn++;
    peekCount++;
  }

  if (peekCount == 0)
    return;

  empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  for (i = 0; i < peekCount; i++) {
    if (empty < 0)
      break;
    if (!IsDmcLookTarget(peeked[i]))
      continue;
    menuMap[menuCount] = i;
    menuCount++;
  }

  if (menuCount > 0 && empty >= 0) {
    if (menuCount == 1 || WhoseTurn() != DUEL_PLAYER) {
      addIdx = (s8)menuMap[0];
    } else {
      DECKMENU_SAVE();
      for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
        gDeckMenu.cards[i] = CARD_NONE;
      for (i = 0; i < menuCount; i++)
        gDeckMenu.cards[i] = peeked[menuMap[i]];
      gDeckMenu.cost = 0;
      gDeckMenu.currentPos = 0;
      gDeckMenu.sortMode = 0;
      gDeckMenu.displayMode = 1;
      gDeckMenu.cardCount = menuCount;
      DeckMenu_BeginDuelTrunkView();
      if (DeckMenuMainPickConfirmWithLabels(sDmcPickLabels, ARRAY_COUNT(sDmcPickLabels)))
        addIdx = (s8)menuMap[gDeckMenu.currentPos];
      DeckMenu_EndDuelTrunkView();
      DECKMENU_RESTORE();
    }
  }

  if (addIdx >= 0) {
    empty = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
    if (empty >= 0) {
      InitHandSlotFromCard(gTurnHands[ACTIVE_DUELIST][empty], peeked[addIdx]);
      peeked[addIdx] = CARD_NONE;
    }
  }

  /* Place remaining on top in original relative order (last peeked ends deepest). */
  for (i = peekCount; i > 0; i--) {
    if (peeked[i - 1] == CARD_NONE)
      continue;
    PlaceCardOnDeckTop(fixedDuelist, peeked[i - 1]);
  }

  (void)effectCardId;
  UpdateDuelGfxExceptField();
}

static void DARK_MAGICIAN_CIRCLE_ResolveBody(void)
{
  struct DuelCard *zone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  Duel_ActivateContinuousZone(zone);
  Duel_ShowEffectText(DARK_MAGICIAN_CIRCLE);
  ResolveDarkMagicalCircleLook(DARK_MAGICIAN_CIRCLE);
}

APPEND_TEXT void EffectDARK_MAGICIAN_CIRCLE(void)
{
  if (Duel_TryResolveSpellThroughTraps(DARK_MAGICIAN_CIRCLE, DARK_MAGICIAN_CIRCLE_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}
