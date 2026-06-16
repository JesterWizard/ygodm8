#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "duel_status.h"
#include "god_card.h"
#include "mask_of_restrict.h"
#include "summon_tribute.h"
#include "tribute.h"

extern void UpdateDuelGfxExceptField(void);
extern void ActivateTrapEffect(u16 lp);
extern void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);

struct DuelSummonOpts Duel_DefaultSpecialSummonOpts(u8 updateGfx)
{
  struct DuelSummonOpts opts;

  opts.updateGfx = updateGfx;
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  opts.markSpecialSummon = TRUE;
  opts.lockMonster = FALSE;
  return opts;
}

struct DuelSummonOpts Duel_DefaultNormalSummonOpts(u8 updateGfx)
{
  struct DuelSummonOpts opts;

  opts.updateGfx = updateGfx;
  opts.mode = DUEL_SUMMON_NORMAL_FACE_UP_ATK;
  opts.markSpecialSummon = FALSE;
  opts.lockMonster = FALSE;
  return opts;
}

static void MaybeUpdateGfx(u8 updateGfx)
{
  /* ponytail: AI_Main simulates actions with gHideEffectText set; duel state is
   * restored after each probe but field VRAM is not. */
  if (updateGfx && !gHideEffectText)
    UpdateDuelGfxExceptField();
}

static u8 TurnDuelistToFixed(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistToTurnDuelist(u8 fixedDuelist)
{
  u8 turnDuelist;

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[fixedDuelist])
      return turnDuelist;
  }

  return ACTIVE_DUELIST;
}

static u8 MonsterRowForDuelist(u8 turnDuelist)
{
  if (turnDuelist == ACTIVE_DUELIST)
    return ACTIVE_DUELIST_MONSTER_ROW;

  return INACTIVE_DUELIST_MONSTER_ROW;
}

static u8 HandMatchesCardOrPredicate(u16 handCardId, u16 cardId, HandCardPredicate pred)
{
  if (handCardId == CARD_NONE)
    return FALSE;

  if (cardId != CARD_NONE && handCardId != cardId)
    return FALSE;

  if (pred != NULL && pred(handCardId) != TRUE)
    return FALSE;

  return TRUE;
}

static u16 sSelectHandCardId APPEND_DATA = CARD_NONE;
static HandCardPredicate sSelectHandPred APPEND_DATA = NULL;

static u8 AnyHandCardForSelect(u16 handCardId)
{
  return handCardId != CARD_NONE;
}

static u8 SelectHandWrapper(u16 handCardId)
{
  return HandMatchesCardOrPredicate(handCardId, sSelectHandCardId, sSelectHandPred);
}

static s8 FindHandZoneMatching(u8 turnDuelist, u16 cardId, HandCardPredicate pred)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (HandMatchesCardOrPredicate(handRow[i]->id, cardId, pred))
      return i;
  }

  return -1;
}

static s8 SelectHandZone(u8 turnDuelist, u16 cardId, HandCardPredicate pred)
{
  struct DuelCard **handRow = gTurnHands[turnDuelist];

  if (FindHandZoneMatching(turnDuelist, cardId, pred) < 0)
    return -1;

  if (WhoseTurn() == DUEL_PLAYER) {
    sSelectHandCardId = cardId;
    sSelectHandPred = pred;
    return SelectHandCardMatchingPredicate(handRow, SelectHandWrapper);
  }

  return FindHandZoneMatching(turnDuelist, cardId, pred);
}

static void InitMonsterZone(struct DuelCard *zone, struct DuelSummonOpts opts)
{
  enum DuelSummonMode mode = opts.mode;
  u8 markSpecialSummon = opts.markSpecialSummon;

  ResetPermStage(zone);
  ResetTempStage(zone);
  zone->unkTwo = 0;
  zone->unkThree = 0;
  zone->willChangeSides = 0;
  zone->effectExhausted = 0;
  zone->effectUsedThisTurn = 0;

  // ponytail: Berserk Gorilla cannot be placed in Defense Position
  if (zone->id == BERSERK_GORILLA
      && mode != DUEL_SUMMON_NORMAL_FACE_UP_ATK
      && mode != DUEL_SUMMON_SPECIAL_FACE_UP_ATK)
    mode = DUEL_SUMMON_NORMAL_FACE_UP_ATK;

  switch (mode) {
  case DUEL_SUMMON_SPECIAL_FACE_UP_DEF:
    zone->isFaceUp = TRUE;
    zone->isDefending = TRUE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    break;
  case DUEL_SUMMON_NORMAL_SET:
    zone->isFaceUp = FALSE;
    zone->isDefending = TRUE;
    zone->isLocked = FALSE;
    FlipCardFaceDown(zone);
    break;
  case DUEL_SUMMON_NORMAL_FACE_UP_ATK:
  case DUEL_SUMMON_SPECIAL_FACE_UP_ATK:
  default:
    zone->isFaceUp = TRUE;
    zone->isDefending = FALSE;
    zone->isLocked = FALSE;
    UnlockCard(zone);
    break;
  }

  if (opts.lockMonster)
    zone->isLocked = TRUE;

  if (markSpecialSummon
      && (mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF))
    zone->unk4 = 2;
  else
    zone->unk4 = 0;
}

static enum DuelActionResult PlaceMonsterFromId(u8 turnDuelist, u16 monsterId, struct DuelSummonOpts opts)
{
  u8 monsterRow = MonsterRowForDuelist(turnDuelist);
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (monsterId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0)
    return DUEL_ACTION_NO_ZONE;

  summonZone = gTurnZones[monsterRow][monsterZone];
  summonZone->id = monsterId;
  InitMonsterZone(summonZone, opts);
  MaybeUpdateGfx(opts.updateGfx);
  return DUEL_ACTION_OK;
}

static u8 SpellTrapOriginUsesRow2(u16 spellId)
{
  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP)
    return TRUE;

  switch (spellId) {
  case MYSTICAL_SPACE_TYPHOON:
  case RIRYOKU:
  case BLOCK_ATTACK:
  case BOOK_OF_MOON:
  case SOUL_TAKER:
    return TRUE;
  default:
    return FALSE;
  }
}

static void SetupSpellTrapOrigin(void)
{
  u8 spellRow;
  u8 spellCol;

  if (SpellTrapOriginUsesRow2(gSpellEffectData.id)) {
    spellRow = gSpellEffectData.row2;
    spellCol = gSpellEffectData.col2;
  } else {
    spellRow = gSpellEffectData.row1;
    spellCol = gSpellEffectData.col1;
  }

  gTrapEffectData.originRow = spellRow;
  gTrapEffectData.originCol = spellCol;
  gTrapEffectData.originCardId = gSpellEffectData.id;
}

static void ApplyLpDelta(u8 turnDuelist, s32 delta)
{
  u8 affectsPlayerSide = ((turnDuelist == ACTIVE_DUELIST) == (WhoseTurn() == DUEL_PLAYER));

  if (delta >= 0) {
    if (affectsPlayerSide)
      SetPlayerLifePointsToAdd((u32)delta);
    else
      SetOpponentLifePointsToAdd((u32)delta);
  } else {
    if (affectsPlayerSide)
      SetPlayerLifePointsToSubtract((u32)(-delta));
    else
      SetOpponentLifePointsToSubtract((u32)(-delta));
  }
}

static u8 CountTributeMonstersOnRow(u8 turnDuelist, u16 avoidCardId)
{
  u8 row = MonsterRowForDuelist(turnDuelist);
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone->id == CARD_NONE || zone->id == avoidCardId)
      continue;

    count++;
  }

  return count;
}

static enum DuelActionResult PayTributesFromMonsterRow(u8 turnDuelist, u8 count, u16 avoidCardId)
{
  u8 row = MonsterRowForDuelist(turnDuelist);
  u8 fixedDuelist = TurnDuelistToFixed(turnDuelist);
  u8 paid = 0;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW && paid < count; col++) {
    struct DuelCard *zone = gTurnZones[row][col];

    if (zone->id == CARD_NONE || zone->id == avoidCardId)
      continue;

    ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
    paid++;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  if (paid < count)
    return DUEL_ACTION_NO_TARGET;

  return DUEL_ACTION_OK;
}

u8 Duel_CountCardsInHand(struct DuelCard **handRow)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id != CARD_NONE)
      count++;
  }

  return count;
}

enum DuelActionResult Duel_DrawCards(u8 duelist, u8 count, u8 updateGfx)
{
  u8 i;
  u8 fixedDuelist = TurnDuelistToFixed(duelist);

  for (i = 0; i < count; i++) {
    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist)) {
      DeclareLoser(fixedDuelist);
      return DUEL_ACTION_DUEL_OVER;
    }

    TryDrawingCard(duelist);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_MillTopDeckCards(u8 duelist, u8 count, u8 updateGfx)
{
  u8 i;
  u8 fixedDuelist = TurnDuelistToFixed(duelist);

  for (i = 0; i < count; i++) {
    if (gDuelDecks[fixedDuelist].cardsDrawn >= NumCardsInDeck(fixedDuelist)) {
      DeclareLoser(fixedDuelist);
      return DUEL_ACTION_DUEL_OVER;
    }

    gDuelDecks[fixedDuelist].cardsDrawn++;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DestroyZone(struct DuelCard *zone, u8 graveyardDuelist, u8 updateGfx)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
  MaybeUpdateGfx(updateGfx);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DestroyAllMonstersMatching(u8 turnRow, MonsterZonePredicate pred,
                                                      u8 updateGfx)
{
  u8 col;
  u8 graveyardDuelist;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  if (turnRow != INACTIVE_DUELIST_MONSTER_ROW && turnRow != ACTIVE_DUELIST_MONSTER_ROW)
    return DUEL_ACTION_INVALID;

  graveyardDuelist = (turnRow == ACTIVE_DUELIST_MONSTER_ROW) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id == CARD_NONE)
      continue;

    if (IsGodCard(zone->id))
      continue;

    if (pred != NULL && pred(zone) != TRUE)
      continue;

    ClearZoneAndSendMonToGraveyard(zone, graveyardDuelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

static s8 PickRandomHandZone(struct DuelCard **handRow)
{
  u8 i;
  u8 occupied = Duel_CountCardsInHand(handRow);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return -1;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return -1;
}

static u8 HandCardMatchesDiscardPred(u16 cardId, HandCardPredicate pred)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (pred == NULL)
    return TRUE;

  return pred(cardId);
}

enum DuelActionResult Duel_DiscardFromHand(u8 duelist, u8 count, HandCardPredicate pred, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;

  for (i = 0; i < count; i++) {
    s8 zone;

    if (Duel_CountCardsInHand(handRow) == 0)
      return DUEL_ACTION_NO_TARGET;

    if (WhoseTurn() == DUEL_PLAYER) {
      if (pred != NULL)
        zone = SelectHandCardMatchingPredicate(handRow, pred);
      else
        zone = SelectHandCardMatchingPredicate(handRow, AnyHandCardForSelect);
    } else {
      zone = PickRandomHandZone(handRow);
      if (zone >= 0 && !HandCardMatchesDiscardPred(handRow[zone]->id, pred))
        return DUEL_ACTION_NO_TARGET;
    }

    if (zone < 0)
      return DUEL_ACTION_NO_TARGET;

    ClearZoneAndSendMonToGraveyard(handRow[zone], duelist);

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DestroyAllHandCards(u8 duelist, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;
  enum DuelActionResult result = DUEL_ACTION_NO_TARGET;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (handRow[i]->id == CARD_NONE)
      continue;

    ClearZoneAndSendMonToGraveyard(handRow[i], duelist);
    result = DUEL_ACTION_OK;

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return result;
}

enum DuelActionResult Duel_ChangeLp(u8 targetDuelist, s32 delta, u8 updateGfx)
{
  if (delta == 0)
    return DUEL_ACTION_OK;

  ApplyLpDelta(targetDuelist, delta);
  HandleAtkAndLifePointsAction();
  CheckLoserFlags();
  MaybeUpdateGfx(updateGfx);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

void Duel_ShowEffectText(u16 cardId)
{
  if (gHideEffectText)
    return;

  gCardEffectTextData.cardId = cardId;
  ActivateCardEffectText();
}

void Duel_ShowEffectTextTyped(u16 cardId, u8 textType)
{
  if (gHideEffectText)
    return;

  ResetCardEffectTextData();
  SetCardEffectTextType(textType);
  gCardEffectTextData.cardId = cardId;
  ActivateCardEffectText();
}

enum DuelActionResult Duel_TryResolveSpellThroughTrapsEx(u16 spellId, u16 trapLp,
                                                         void (*resolveBody)(void))
{
  if (GetTypeGroup(spellId) != TYPE_GROUP_SPELL) {
    if (resolveBody != NULL)
      resolveBody();
    return DUEL_ACTION_OK;
  }

  SetupSpellTrapOrigin();

  if (IsTrapTriggered() != TRUE || gHideEffectText) {
    if (resolveBody != NULL)
      resolveBody();
    return DUEL_ACTION_OK;
  }

  ActivateTrapEffect(trapLp);
  return DUEL_ACTION_BLOCKED;
}

enum DuelActionResult Duel_TryResolveSpellThroughTraps(u16 spellId, void (*resolveBody)(void))
{
  return Duel_TryResolveSpellThroughTrapsEx(spellId, 0, resolveBody);
}

s16 Duel_FindDeckCardIndex(u8 duelist, u16 cardId)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 i;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;

  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == cardId)
      return (s16)i;
  }

  return -1;
}

enum DuelActionResult Duel_RemoveDeckCardAt(u8 duelist, u8 index, u8 updateGfx)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 deckSize = NumCardsInDeck(fixedDuelist);

  if (index < top || index >= deckSize)
    return DUEL_ACTION_INVALID;

  gDuelDecks[fixedDuelist].cards[index] = gDuelDecks[fixedDuelist].cards[top];
  gDuelDecks[fixedDuelist].cardsDrawn++;
  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

void Duel_ShuffleDeckFromDrawn(u8 duelist)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u8 start = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 end = NumCardsInDeck(fixedDuelist);
  u8 size;
  int i;

  if (end <= start)
    return;

  size = end - start;
  if (size <= 1)
    return;

  for (i = 0; i < 200; i++) {
    u8 indexA = RandRangeU8(0, size - 1);
    u8 indexB = RandRangeU8(0, size - 1);
    u16 temp = gDuelDecks[fixedDuelist].cards[start + indexA];

    gDuelDecks[fixedDuelist].cards[start + indexA] =
        gDuelDecks[fixedDuelist].cards[start + indexB];
    gDuelDecks[fixedDuelist].cards[start + indexB] = temp;
  }
}

enum DuelActionResult Duel_SpecialSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                 struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  s8 handZone;
  u16 monsterId;
  enum DuelActionResult result;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  handZone = SelectHandZone(duelist, cardId, pred);
  if (handZone < 0)
    return DUEL_ACTION_NO_TARGET;

  monsterId = handRow[handZone]->id;
  ClearZone(handRow[handZone]);
  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonFromHandZone(u8 duelist, s8 handZone,
                                                     struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u16 monsterId;
  enum DuelActionResult result;

  if (handZone < 0 || handZone >= MAX_ZONES_IN_ROW)
    return DUEL_ACTION_INVALID;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (handRow[handZone]->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  monsterId = handRow[handZone]->id;
  ClearZone(handRow[handZone]);
  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonFromGrave(u8 duelist, u16 cardId, struct DuelSummonOpts opts)
{
  u8 fixedDuelist = TurnDuelistToFixed(duelist);
  u16 revivedId;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  if (cardId != CARD_NONE && gTurnDuelistBattleState[duelist]->graveyard != cardId)
    return DUEL_ACTION_NO_TARGET;

  revivedId = GetGraveCardAndClearGrave(fixedDuelist);
  if (revivedId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  if (cardId != CARD_NONE && revivedId != cardId)
    return DUEL_ACTION_NO_TARGET;

  return PlaceMonsterFromId(duelist, revivedId, opts);
}

enum DuelActionResult Duel_SpecialSummonFromDeck(u8 duelist, u16 cardId, struct DuelSummonOpts opts)
{
  s16 deckIndex;
  u16 monsterId;
  enum DuelActionResult result;

  if (cardId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterRowForDuelist(duelist)]) < 0)
    return DUEL_ACTION_NO_ZONE;

  deckIndex = Duel_FindDeckCardIndex(duelist, cardId);
  if (deckIndex < 0)
    return DUEL_ACTION_NO_TARGET;

  monsterId = cardId;
  result = Duel_RemoveDeckCardAt(duelist, (u8)deckIndex, FALSE);
  if (result != DUEL_ACTION_OK)
    return result;

  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_SpecialSummonMonsterId(u8 duelist, u16 monsterId,
                                                    struct DuelSummonOpts opts)
{
  enum DuelActionResult result;

  result = PlaceMonsterFromId(duelist, monsterId, opts);

  if (result == DUEL_ACTION_OK && IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return result;
}

enum DuelActionResult Duel_NormalSummonFromHand(u8 duelist, u16 cardId, HandCardPredicate pred,
                                                struct DuelSummonOpts opts)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  s8 handZone;
  u16 monsterId;
  int requiredTributes;
  enum DuelActionResult tributeResult;
  u8 monsterRow = MonsterRowForDuelist(duelist);

  if (gTurnDuelistBattleState[duelist]->summoningBlocked)
    return DUEL_ACTION_BLOCKED;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return DUEL_ACTION_NO_ZONE;

  handZone = SelectHandZone(duelist, cardId, pred);
  if (handZone < 0)
    return DUEL_ACTION_NO_TARGET;

  monsterId = handRow[handZone]->id;
  if (monsterId == RARE_METAL_DRAGON)
    return DUEL_ACTION_INVALID;

  if (GetTypeGroup(monsterId) != TYPE_GROUP_MONSTER)
    return DUEL_ACTION_INVALID;

  requiredTributes = GetMonsterNumRequiredTributesForHandSlot((u8)handZone, monsterId);
  if (requiredTributes == MASK_OF_RESTRICT_TRIBUTE_BLOCK)
    return DUEL_ACTION_BLOCKED;

  if (requiredTributes > 0) {
    if (CountTributeMonstersOnRow(duelist, CARD_NONE) < (u8)requiredTributes)
      return DUEL_ACTION_NO_TARGET;

    SetPendingTributeSummonCardId(monsterId);
    tributeResult = PayTributesFromMonsterRow(duelist, (u8)requiredTributes, CARD_NONE);
    if (tributeResult != DUEL_ACTION_OK)
      return tributeResult;

    SetPendingSummonTributeCount((u8)requiredTributes);
    TryApplyPreciousCardsFromBeyondOnTributeSummon(monsterId, duelist);
  }

  ClearZone(handRow[handZone]);
  tributeResult = PlaceMonsterFromId(duelist, monsterId, opts);
  if (tributeResult != DUEL_ACTION_OK)
    return tributeResult;

  BlockTurnSummoning(duelist);
  ClearPendingTributeSummonCardId();
  ClearPendingSummonTributeCount();

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_ReturnMonsterZoneToOwnerHand(struct DuelCard *zone, u8 updateGfx)
{
  u8 fixedDuelist;
  u8 turnDuelist;
  s8 handZone;

  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return DUEL_ACTION_INVALID;

  turnDuelist = FixedDuelistToTurnDuelist(fixedDuelist);
  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return DUEL_ACTION_NO_ZONE;

  CopyCard(gTurnHands[turnDuelist][handZone], zone);
  gTurnHands[turnDuelist][handZone]->isFaceUp = FALSE;
  gTurnHands[turnDuelist][handZone]->isLocked = FALSE;
  gTurnHands[turnDuelist][handZone]->isDefending = FALSE;
  gTurnHands[turnDuelist][handZone]->unkTwo = 0;
  gTurnHands[turnDuelist][handZone]->unkThree = 0;
  gTurnHands[turnDuelist][handZone]->unk4 = 0;
  gTurnHands[turnDuelist][handZone]->willChangeSides = FALSE;
  ResetPermStage(gTurnHands[turnDuelist][handZone]);
  ResetTempStage(gTurnHands[turnDuelist][handZone]);
  ClearZone(zone);
  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DuelHelpers_SelfCheck(void)
{
  struct DuelCard hand[5];
  struct DuelCard *handRow[5];
  struct DuelCard zone;
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    hand[i].id = (i < 3) ? (u16)(100 + i) : CARD_NONE;
    handRow[i] = &hand[i];
  }

  if (Duel_CountCardsInHand(handRow) != 3)
    while (1)
      ;

  zone.id = 1;
  InitMonsterZone(&zone, Duel_DefaultSpecialSummonOpts(FALSE));
  if (zone.unk4 != 2 || zone.isFaceUp != TRUE || zone.isDefending != FALSE)
    while (1)
      ;

  InitMonsterZone(&zone, Duel_DefaultNormalSummonOpts(FALSE));
  if (zone.unk4 != 0)
    while (1)
      ;

  {
    struct DuelSummonOpts locked = Duel_DefaultSpecialSummonOpts(FALSE);

    locked.lockMonster = TRUE;
    InitMonsterZone(&zone, locked);
    if (zone.isLocked != TRUE)
      while (1)
        ;
  }
}
#endif
