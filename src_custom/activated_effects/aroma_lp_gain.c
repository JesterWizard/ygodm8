#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "aroma_lp_gain.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"
#include "synchro_duel.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

static const char sAromaName[] APPEND_RODATA = "Aroma";
static const char sHarpieName[] APPEND_RODATA = "Harpie";
static u8 sAromaLpInit APPEND_DATA = {0};

static u8 FixedRowForController(u8 controller)
{
  return Duel_FixedMonsterRowForDuelist(controller);
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static struct DuelCard *FindFaceUpById(u8 controller, u16 cardId)
{
  u8 row = FixedRowForController(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == cardId)
      return zone;
  }
  return NULL;
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

static u8 BounceFirstOppSpellTrapToHand(u8 gainingController)
{
  u8 opp = gainingController == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 oppTurn = TurnDuelistForFixed(opp);
  u8 backRow = opp == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  s8 empty;
  u8 col;

  empty = FirstEmptyZoneInRow(gTurnHands[oppTurn]);
  if (empty < 0)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backRow][col];
    u8 typeGroup;
    u16 cardId;

    if (zone == NULL || zone->id == CARD_NONE)
      continue;
    typeGroup = GetTypeGroup(zone->id);
    if (typeGroup != TYPE_GROUP_SPELL && typeGroup != TYPE_GROUP_TRAP)
      continue;

    cardId = zone->id;
    ClearZone(zone);
    InitHandSlotFromCard(gTurnHands[oppTurn][empty], cardId);
    return TRUE;
  }
  return FALSE;
}

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sAromaName);
}

static u8 CountAromaOnFieldFor(u8 controller)
{
  u8 row = FixedRowForController(controller);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && IsAromaMonster(zone->id))
      count++;
  }
  return count;
}

static u8 BanishUpToNFromOppGyFor(u8 controller, u8 max)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 banished = 0;
  u8 i;

  if (max == 0)
    return 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[opp].graveyard == CARD_NONE)
      return 0;
    Duel_BanishGraveyardTopTurn(TurnDuelistForFixed(opp));
    return 1;
  }

  for (i = GraveyardExpand_GetCount(opp); i > 0 && banished < max; i--) {
    if (Duel_BanishGraveyardAtFixed(opp, i - 1) == CARD_NONE)
      break;
    banished++;
  }
  if (banished > 0)
    GraveyardExpand_RefreshDisplay();
  return banished;
}

static void TryBergamotOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_BERGAMOT);

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_BERGAMOT))
    return;
  if (zone->tempStage > 124)
    return;

  zone->tempStage += 2;
  EffectOpt_MarkUsed(AROMAGE_BERGAMOT);
  MarkMonsterEffectUsed(zone);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

static void TryCanangaOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_CANANGA);

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_CANANGA))
    return;
  if (!BounceFirstOppSpellTrapToHand(controller))
    return;

  EffectOpt_MarkUsed(AROMAGE_CANANGA);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void TryJasmineOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_JASMINE);
  u8 turnDuelist;

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_JASMINE))
    return;

  turnDuelist = TurnDuelistForFixed(controller);
  if (Duel_DrawCards(turnDuelist, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(AROMAGE_JASMINE);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}

static void TryMarjoramOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_MARJORAM);
  u8 max;

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_MARJORAM))
    return;

  max = CountAromaOnFieldFor(controller);
  if (max == 0 || BanishUpToNFromOppGyFor(controller, max) == 0)
    return;

  EffectOpt_MarkUsed(AROMAGE_MARJORAM);
  MarkMonsterEffectUsed(zone);
  UpdateDuelGfxExceptField();
}

static void TryLaurelTunerOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_LAUREL);
  u8 row;
  u8 col;

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_LAUREL))
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *plant = gFixedZones[row][col];

      if (plant == NULL || plant->id == CARD_NONE || !plant->isFaceUp)
        continue;
      if (!Duel_CardHasMonsterType(plant->id, TYPE_PLANT))
        continue;
      if (Card_IsTuner(plant->id))
        continue;

      /* Tuner-this-turn stand-in (same bit as Morphtronic Earfon). */
      plant->unk4 |= 0x40;
      EffectOpt_MarkUsed(AROMAGE_LAUREL);
      MarkMonsterEffectUsed(zone);
      UpdateDuelGfxExceptField();
      return;
    }
  }
}

static void TryAromageRosemaryOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMAGE_ROSEMARY);
  u8 row;
  u8 col;

  if (zone == NULL || EffectOpt_IsUsed(AROMAGE_ROSEMARY))
    return;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *mon = gFixedZones[row][col];

      if (mon == NULL || mon->id == CARD_NONE || !mon->isFaceUp)
        continue;
      if (GetTypeGroup(mon->id) != TYPE_GROUP_MONSTER)
        continue;

      mon->isDefending = !mon->isDefending;
      EffectOpt_MarkUsed(AROMAGE_ROSEMARY);
      MarkMonsterEffectUsed(zone);
      UpdateDuelGfxExceptField();
      return;
    }
  }
}

static void TryAromaseraphyRosemaryOnLpGain(u8 controller)
{
  struct DuelCard *zone = FindFaceUpById(controller, AROMASERAPHY_ROSEMARY);
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 monRow = Duel_FixedMonsterRowForDuelist(opp);
  u8 backRow = opp == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 col;

  if (zone == NULL || EffectOpt_IsUsed(AROMASERAPHY_ROSEMARY))
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gFixedZones[monRow][col];

    if (card == NULL || card->id == CARD_NONE || !card->isFaceUp)
      continue;
    card->unk4 |= 0x80; /* effects negated until EP stand-in */
    EffectOpt_MarkUsed(AROMASERAPHY_ROSEMARY);
    MarkMonsterEffectUsed(zone);
    UpdateDuelGfxExceptField();
    return;
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *card = gFixedZones[backRow][col];

    if (card == NULL || card->id == CARD_NONE || !card->isFaceUp)
      continue;
    card->unk4 |= 0x80;
    EffectOpt_MarkUsed(AROMASERAPHY_ROSEMARY);
    MarkMonsterEffectUsed(zone);
    UpdateDuelGfxExceptField();
    return;
  }
}

static void OnLpGain(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->controller > DUEL_OPPONENT)
    return;
  if (gHideEffectText)
    return;

  TryBergamotOnLpGain(ev->controller);
  TryCanangaOnLpGain(ev->controller);
  TryJasmineOnLpGain(ev->controller);
  TryMarjoramOnLpGain(ev->controller);
  TryLaurelTunerOnLpGain(ev->controller);
  TryAromageRosemaryOnLpGain(ev->controller);
  TryAromaseraphyRosemaryOnLpGain(ev->controller);
}

static void OnLaurelSentToGy(const struct EffectEvent *ev)
{
  u8 turnDuelist;

  if (ev == NULL || ev->cardId != AROMAGE_LAUREL)
    return;
  if (ev->controller > DUEL_OPPONENT || gHideEffectText)
    return;
  if (EffectOpt_IsUsed(AROMAGE_LAUREL))
    return;

  turnDuelist = TurnDuelistForFixed(ev->controller);
  Duel_ShowEffectTextTyped(AROMAGE_LAUREL, 8);
  if (Duel_ChangeLp(turnDuelist, 500, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  EffectOpt_MarkUsed(AROMAGE_LAUREL);
}

static s8 FindMarjoramHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    if (SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i)->id == AROMAGE_MARJORAM)
      return (s8)i;
  }
  return -1;
}

static void OnPlantBattleDestroyed(const struct EffectEvent *ev)
{
  u8 controller;
  u8 turnDuelist;
  s8 handZone;
  struct DuelSummonOpts opts;

  if (ev == NULL || ev->cardId == CARD_NONE || gHideEffectText)
    return;
  if (!Duel_CardHasMonsterType(ev->cardId, TYPE_PLANT))
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;

  controller = ev->controller;
  turnDuelist = TurnDuelistForFixed(controller);
  handZone = FindMarjoramHandZone(turnDuelist);
  if (handZone < 0)
    return;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[turnDuelist == ACTIVE_DUELIST
                                         ? ACTIVE_DUELIST_MONSTER_ROW
                                         : INACTIVE_DUELIST_MONSTER_ROW])
      < 0)
    return;
  if (EffectOpt_IsUsed(AROMAGE_MARJORAM))
    return;

  Duel_ShowEffectTextTyped(AROMAGE_MARJORAM, 8);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHandZone(turnDuelist, (u8)handZone, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(AROMAGE_MARJORAM);
  Duel_ChangeLp(turnDuelist, 500, TRUE);
  UpdateDuelGfxExceptField();
}

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  return Duel_CardNameContains(cardId, sHarpieName);
}

static void OnHarpieEleganceDestroyed(const struct EffectEvent *ev)
{
  u8 turnDuelist;
  u8 fixedDuelist;
  u8 deckSize;
  u8 top;
  u8 i;
  u16 cardId = CARD_NONE;

  if (ev == NULL || ev->cardId != HARPIE_LADY_ELEGANCE || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (EffectOpt_IsUsed(HARPIE_LADY_ELEGANCE))
    return;

  fixedDuelist = ev->controller;
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return;

  deckSize = NumCardsInDeck(fixedDuelist);
  top = gDuelDecks[fixedDuelist].cardsDrawn;
  for (i = top; i < deckSize; i++) {
    if (IsHarpieMonster(gDuelDecks[fixedDuelist].cards[i])) {
      cardId = gDuelDecks[fixedDuelist].cards[i];
      break;
    }
  }
  if (cardId == CARD_NONE)
    return;

  Duel_ShowEffectTextTyped(HARPIE_LADY_ELEGANCE, 8);
  if (Duel_AddDeckCardToHand(turnDuelist, cardId, TRUE) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(HARPIE_LADY_ELEGANCE);
  UpdateDuelGfxExceptField();
}

void AromaLpGain_EnsureInit(void)
{
  if (sAromaLpInit)
    return;

  sAromaLpInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LP_GAIN, OnLpGain);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnLaurelSentToGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnLaurelSentToGy);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnPlantBattleDestroyed);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnHarpieEleganceDestroyed);
}
