#include "global.h"
#include "common-chax.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "duel_status.h"
#include "god_card.h"
#include "mask_of_restrict.h"
#include "mini_card.h"
#include "summon_tribute.h"
#include "raregold_armor.h"
#include "rivalry_of_warlords.h"
#include "level_limit_area_b.h"
#include "level_limit_area_a.h"
#include "ring_of_destruction.h"
#include "amazoness_tiger.h"
#include "blast_held_by_a_tribute.h"
#include "vengeful_bog_spirit.h"
#include "tribute.h"
#include "imperial_order.h"
#include "royal_decree.h"
#include "kishido_spirit.h"
#include "ryu_kishin_clown.h"
#include "dark_dust_spirit.h"
#include "kaiser_colosseum.h"
#include "elemental_hero_tempest.h"
#include "elemental_hero_neos_alius.h"
#include "elemental_hero_great_tornado.h"

extern unsigned char IsSpellCancellerSpellLockActive(void);
extern unsigned char IsSorcererOfDarkMagicTrapLockActive(void);

extern void UpdateDuelGfxExceptField(void);
extern void ActivateTrapEffect(u16 lp);
extern void TryApplyPreciousCardsFromBeyondOnTributeSummon(u16 summonCardId, u8 duelist);
extern struct DuelCard *gSetFinalStatZone;

/* Forward declarations used by PickZone targeting helpers */
extern void DisplayCardInfoBar(void);
extern void sub_8041E70(u8, u8);
extern void SetCursorToCardDest(void);
extern void ResetCursorDestToCurrentPos(void);
extern void CheckWinConditionExodia(unsigned char);
extern void TryActivatingPermanentEffects(void);

u8 ElementalHeroShiningPhoenixEnforcer_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroElectrum_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroHeat_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GoblinKing_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GyakuGirePanda_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 GreatMajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 MajuGarzett_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 AmazonessTiger_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ThebanNightmare_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 TheAgentOfForceMars_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 UnstoppableExodiaIncarnate_ApplyStat(struct DuelCard *zone);
u8 HarpiesPetBabyDragon_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 HarpiesPetBabyDragon_CanAttackMonsterZone(struct DuelCard *zone);
u8 ElementalHeroKnospe_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroKnospe_CanAttackMonsterZone(struct DuelCard *zone);
u8 ElementalHeroPoisonRose_ApplyDynamicZoneStats(struct DuelCard *zone);
u8 ElementalHeroPoisonRose_CanAttackMonsterZone(struct DuelCard *zone);
struct DuelCard *ElementalHeroPoisonRose_GetForcedAttackTarget(u8 defenderDuelist);
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
static const char sAmazonessArchetypeName[] APPEND_RODATA = "Amazoness";
static const char sElementalHeroArchetypeName[] APPEND_RODATA = "Elemental HERO";

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

  LevelLimitAreaB_EnforceOnSummon(zone);
}

static u8 SummonModeIsSpecial(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_SPECIAL_FACE_UP_ATK || mode == DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
}

u8 Duel_CardCannotBeSpecialSummoned(u16 cardId)
{
  return cardId == DARK_DUST_SPIRIT;
}

static enum DuelActionResult PlaceMonsterFromId(u8 turnDuelist, u16 monsterId, struct DuelSummonOpts opts)
{
  u8 monsterRow = MonsterRowForDuelist(turnDuelist);
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (monsterId == CARD_NONE)
    return DUEL_ACTION_INVALID;

  if (SummonModeIsSpecial(opts.mode) && Duel_CardCannotBeSpecialSummoned(monsterId))
    return DUEL_ACTION_BLOCKED;

  if (!KaiserColosseum_AllowsMonsterPlacement(Duel_FixedMonsterRowForDuelist(TurnDuelistToFixed(turnDuelist))))
    return DUEL_ACTION_BLOCKED;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[monsterRow]);
  if (monsterZone < 0)
    return DUEL_ACTION_NO_ZONE;

  summonZone = gTurnZones[monsterRow][monsterZone];
  summonZone->id = monsterId;
  InitMonsterZone(summonZone, opts);
  TryBlastHeldByATributeOnMonsterPlacement(summonZone);
  TryVengefulBogSpiritOnMonsterPlacement(summonZone);
  MaybeUpdateGfx(opts.updateGfx);
  TryActivateRyuKishinClownOnMonsterPlacement(summonZone);
  TryActivateDarkDustSpiritOnMonsterPlacement(summonZone);
  TryElementalHeroGreatTornadoOnMonsterPlacement(summonZone);
  Duel_NotifyFixedMonsterRowChanged(Duel_FixedMonsterRowForDuelist(TurnDuelistToFixed(turnDuelist)));
  return DUEL_ACTION_OK;
}

static u8 SpellTrapOriginUsesRow2(u16 spellId)
{
  if (GetSpellType(spellId) == SPELL_TYPE_EQUIP)
    return TRUE;

  switch (spellId) {
  case MYSTICAL_SPACE_TYPHOON:
  case DUST_TORNADO:
  case RIRYOKU:
  case BLOCK_ATTACK:
  case BOOK_OF_MOON:
  case BOOK_OF_TAIYOU:
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

    TryDrawingCard(TurnDuelistToFixed(duelist));

    if (IsDuelOver() == TRUE)
      return DUEL_ACTION_DUEL_OVER;
  }

  MaybeUpdateGfx(updateGfx);
  return DUEL_ACTION_OK;
}

enum DuelActionResult Duel_DrawCardsUntilHandSize(u8 turnDuelist, u8 targetHandSize, u8 updateGfx)
{
  while (Duel_CountCardsInHand(gTurnHands[turnDuelist]) < targetHandSize) {
    if (Duel_CountCardsInHand(gTurnHands[turnDuelist]) >= MAX_ZONES_IN_ROW)
      break;
    if (Duel_DrawCards(turnDuelist, 1, FALSE) == DUEL_ACTION_DUEL_OVER)
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

void Duel_DestroyMaskedMonstersInFixedRow(u8 fixedRow, u8 colMask, u8 graveyardDuelist, u8 updateGfx)
{
  u8 col;

  if (colMask == 0)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;

    if (!(colMask & (1 << col)))
      continue;

    zone = gFixedZones[fixedRow][col];
    if (zone->id != CARD_NONE)
      Duel_DestroyZone(zone, graveyardDuelist, updateGfx);
  }
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

enum DuelActionResult Duel_DiscardRandomFromHand(u8 duelist, u8 count, u8 updateGfx)
{
  struct DuelCard **handRow = gTurnHands[duelist];
  u8 i;

  for (i = 0; i < count; i++) {
    s8 zone;

    if (Duel_CountCardsInHand(handRow) == 0)
      return DUEL_ACTION_NO_TARGET;

    zone = PickRandomHandZone(handRow);
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

void Duel_IncrementPermStageOnDuelistMonsters(u8 turnDuelist)
{
  u8 i;
  u8 row = MonsterRowForDuelist(turnDuelist);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[row][i];

    if (zone->id != CARD_NONE)
      IncrementPermStage(zone);
  }
}

void Duel_RefreshMonsterStatOverlays(void)
{
  RefreshFieldMonsterStatOverlays();
}

u16 Duel_ClampStat(u32 stat)
{
  if (stat > 0xFFFE)
    return 0xFFFE;
  return (u16)stat;
}

u16 Duel_StatFromCount(u32 count, u16 perUnit, u32 base)
{
  return Duel_ClampStat(base + count * perUnit);
}

u8 Duel_CardIsMonster(u16 cardId)
{
  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE && cardId >= CUSTOM_CARD_START)
    return FALSE;

  return gCardData_NEW[cardId].type < TYPE_SPELL;
}

u8 Duel_CardHasMonsterType(u16 cardId, u8 monsterType)
{
  if (cardId == CARD_NONE)
    return FALSE;

  if (!Duel_CardIsMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.type == monsterType;
}

u8 Duel_CardNameContains(u16 cardId, const char *needle)
{
  const u8 *name;
  u8 needleLen = 0;
  u8 i;

  if (cardId == CARD_NONE || needle == NULL)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == cardId)
    cardId = ElementalHeroNeosAlius_GetEffectiveCardId(gSetFinalStatZone);

  while (needle[needleLen] != 0)
    needleLen++;

  if (needleLen == 0)
    return FALSE;

  SetCardInfo(cardId);
  name = gCardInfo.name;
  if (name == NULL)
    return FALSE;

  for (i = 0; name[i] != 0; i++) {
    u8 j = 0;

    while (j < needleLen && name[i + j] == (u8)needle[j])
      j++;

    if (j == needleLen)
      return TRUE;
  }

  return FALSE;
}

u8 Duel_IsAmazonessCard(u16 cardId)
{
  return Duel_CardNameContains(cardId, sAmazonessArchetypeName);
}

u8 Duel_IsElementalHeroCard(u16 cardId)
{
  return Duel_CardNameContains(cardId, sElementalHeroArchetypeName);
}

u16 Duel_GetEffectiveCardId(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return CARD_NONE;

  return ElementalHeroNeosAlius_GetEffectiveCardId(zone);
}

u8 Duel_IsFiendZone(struct DuelCard *zone)
{
  return zone != NULL && zone->id != CARD_NONE
      && Duel_CardHasMonsterType(zone->id, TYPE_FIEND);
}

u8 Duel_FindFixedMonsterZone(struct DuelCard *zone, u8 *fixedRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gFixedZones[row][*col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Duel_FindTurnMonsterZone(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Duel_FindFixedZone(struct DuelCard *zone, u8 *fixedRow, u8 *col)
{
  u8 row;

  if (zone == NULL)
    return FALSE;

  for (row = OPPONENT_BACKROW; row <= PLAYER_HAND; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gFixedZones[row][*col] == zone) {
        *fixedRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

u8 Duel_CountMonstersOnFixedRow(u8 fixedRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[fixedRow][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

u8 Duel_OpponentMonsterRowForZone(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return OPPONENT_MONSTER_ROW;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

u8 Duel_CountFixedMonstersMatching(MonsterZonePredicate pred)
{
  u8 row;
  u8 col;
  u8 count = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id == CARD_NONE)
        continue;
      if (pred != NULL && pred(zone) != TRUE)
        continue;
      count++;
    }
  }

  return count;
}

u8 Duel_TurnRowHasOtherMonsterMatching(u8 turnRow, u8 exceptCol, MonsterZonePredicate pred)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (col == exceptCol)
      continue;
    if (gTurnZones[turnRow][col]->id == CARD_NONE)
      continue;
    if (pred != NULL && pred(gTurnZones[turnRow][col]) != TRUE)
      continue;
    return TRUE;
  }

  return FALSE;
}

void Duel_WriteCardInfoStats(u16 cardId, u16 atk, u16 def)
{
  SetCardInfo(cardId);
  gCardInfo.atk = atk;
  gCardInfo.def = def;
}

u8 Duel_ApplyStatModViaZoneApplier(struct StatMod *ptr, u16 cardId,
                                  DuelZoneStatApplier applyZone)
{
  u8 row;
  u8 col;

  if (ptr == NULL || ptr->card != cardId || applyZone == NULL)
    return FALSE;

  if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == cardId)
    return applyZone(gSetFinalStatZone);

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone->id != cardId)
        continue;
      if (ComputeFinalStage(zone) != ptr->stage)
        continue;
      if (applyZone(zone))
        return TRUE;
    }
  }

  return FALSE;
}

struct DuelDynamicZoneStat {
  u16 cardId;
  DuelZoneStatApplier applyZone;
};

struct DuelAttackGate {
  u16 cardId;
  MonsterZonePredicate blockWhenControllerHasOther;
};

static const struct DuelDynamicZoneStat sDynamicZoneStats[] __attribute__((section(".text"))) = {
  { ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER, ElementalHeroShiningPhoenixEnforcer_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_ELECTRUM, ElementalHeroElectrum_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_SHINING_FLARE_WINGMAN, ElementalHeroShiningFlareWingman_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_HEAT, ElementalHeroHeat_ApplyDynamicZoneStats },
  { GREAT_MAJU_GARZETT, GreatMajuGarzett_ApplyDynamicZoneStats },
  { MAJU_GARZETT, MajuGarzett_ApplyDynamicZoneStats },
  { GOBLIN_KING, GoblinKing_ApplyDynamicZoneStats },
  { GYAKU_GIRE_PANDA, GyakuGirePanda_ApplyDynamicZoneStats },
  { AMAZONESS_TIGER, AmazonessTiger_ApplyDynamicZoneStats },
  { THEBAN_NIGHTMARE, ThebanNightmare_ApplyDynamicZoneStats },
  { THE_AGENT_OF_FORCE_MARS, TheAgentOfForceMars_ApplyDynamicZoneStats },
  { THE_UNSTOPPABLE_EXODIA_INCARNATE, UnstoppableExodiaIncarnate_ApplyStat },
  { HARPIES_PET_BABY_DRAGON, HarpiesPetBabyDragon_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_KNOSPE, ElementalHeroKnospe_ApplyDynamicZoneStats },
  { ELEMENTAL_HERO_POISON_ROSE, ElementalHeroPoisonRose_ApplyDynamicZoneStats },
};

static const struct DuelAttackGate sAttackGates[] __attribute__((section(".text"))) = {
  { GOBLIN_KING, Duel_IsFiendZone },
};

typedef struct DuelCard *(*DuelForcedAttackTargetFn)(u8 defenderDuelist);

struct DuelForcedAttackRedirect {
  DuelForcedAttackTargetFn getForcedTarget;
};

static const struct DuelForcedAttackRedirect sForcedAttackRedirects[] __attribute__((section(".text"))) = {
  { RaregoldArmor_GetForcedAttackTarget },
  { ElementalHeroPoisonRose_GetForcedAttackTarget },
};

typedef u8 (*DuelAttackZoneCheckFn)(struct DuelCard *zone);

static const DuelAttackZoneCheckFn sAttackZoneChecks[] __attribute__((section(".text"))) = {
  AmazonessTiger_CanAttackMonsterZone,
  HarpiesPetBabyDragon_CanAttackMonsterZone,
  ElementalHeroKnospe_CanAttackMonsterZone,
  ElementalHeroPoisonRose_CanAttackMonsterZone,
};

u8 Duel_TryApplyDynamicZoneStats(struct DuelCard *zone)
{
  u8 i;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sDynamicZoneStats); i++) {
    if (sDynamicZoneStats[i].cardId != zone->id)
      continue;
    return sDynamicZoneStats[i].applyZone(zone);
  }

  return FALSE;
}

u8 Duel_TryApplyDynamicStatMod(struct StatMod *ptr)
{
  u8 i;

  if (ptr == NULL || ptr->card == CARD_NONE)
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sDynamicZoneStats); i++) {
    if (sDynamicZoneStats[i].cardId != ptr->card)
      continue;
    return Duel_ApplyStatModViaZoneApplier(ptr, ptr->card,
                                           sDynamicZoneStats[i].applyZone);
  }

  return FALSE;
}

u8 Duel_CanBeAttackedUnlessControllerHasOther(struct DuelCard *zone, u16 cardId,
                                              MonsterZonePredicate otherPred)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id != cardId)
    return TRUE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return TRUE;

  return !Duel_TurnRowHasOtherMonsterMatching(turnRow, col, otherPred);
}

u8 Duel_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 i;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  for (i = 0; i < ARRAY_COUNT(sAttackGates); i++) {
    if (sAttackGates[i].cardId != zone->id)
      continue;
    return Duel_CanBeAttackedUnlessControllerHasOther(
        zone, sAttackGates[i].cardId, sAttackGates[i].blockWhenControllerHasOther);
  }

  for (i = 0; i < ARRAY_COUNT(sAttackZoneChecks); i++) {
    if (!sAttackZoneChecks[i](zone))
      return FALSE;
  }

  return TRUE;
}

struct DuelCard *Duel_GetForcedAttackTarget(u8 defenderDuelist)
{
  u8 i;
  struct DuelCard *target;

  for (i = 0; i < ARRAY_COUNT(sForcedAttackRedirects); i++) {
    target = sForcedAttackRedirects[i].getForcedTarget(defenderDuelist);
    if (target != NULL)
      return target;
  }

  return NULL;
}

u8 Duel_MonsterMayBeAttacked(struct DuelCard *zone)
{
  struct DuelCard *forcedTarget;
  u8 defenderDuelist;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  defenderDuelist = GetDuelistForZone(zone);
  if (defenderDuelist == 0xFF)
    return TRUE;

  forcedTarget = Duel_GetForcedAttackTarget(defenderDuelist);
  if (forcedTarget == NULL)
    return TRUE;

  return zone == forcedTarget;
}

u8 Duel_ForcedAttackBlocksDirect(u8 defenderDuelist)
{
  return Duel_GetForcedAttackTarget(defenderDuelist) != NULL;
}

u8 CanMonsterBeDestroyedByBattle(u16 cardId, u8 duelist, u16 battleAtk, u16 opponentBattleAtk)
{
  (void)duelist;
  (void)battleAtk;
  (void)opponentBattleAtk;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == REAPER_ON_THE_NIGHTMARE || cardId == SPIRIT_REAPER
      || cardId == ELEMENTAL_HERO_PHOENIX_ENFORCER
      || cardId == ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER)
    return FALSE;

  return TRUE;
}

struct DuelBattleActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct DuelBattleActionData sActionData;

static u8 IsMonsterVersusMonsterBattleAction(u8 actionId)
{
  return actionId == 1 || actionId == 2 || actionId == 3 || actionId == 5;
}

static u8 BattleAtksEqualForKishido(u16 playerAtk, u16 opponentAtk)
{
  return playerAtk == opponentAtk && (playerAtk | opponentAtk);
}

static void ApplyKishidoSpiritEqualAtkProtection(void)
{
  // GBA text: your-side monsters only — not TCG "neither destroyed".
  if (!BattleAtksEqualForKishido(
          sActionData.playerCardAtkOrLifePointsMod,
          sActionData.opponentCardAtkOrLifePointsMod))
    return;

  if (IsKishidoSpiritActiveForDuelist(DUEL_PLAYER))
    sActionData.flags &= ~1u;

  if (IsKishidoSpiritActiveForDuelist(DUEL_OPPONENT))
    sActionData.flags &= ~2u;
}

void Duel_ApplyBattleDestroyProtection(void)
{
  if (!IsMonsterVersusMonsterBattleAction(sActionData.id))
    return;

  ApplyKishidoSpiritEqualAtkProtection();

  if ((sActionData.flags & 1)
      && !ElementalHeroTempestProtectsBattleZone(sActionData.playerMonsterRow, sActionData.unkA)
      && !CanMonsterBeDestroyedByBattle(
          sActionData.playerCardId, DUEL_PLAYER,
          sActionData.playerCardAtkOrLifePointsMod,
          sActionData.opponentCardAtkOrLifePointsMod)) {
    sActionData.flags &= ~1;
  }

  if ((sActionData.flags & 2)
      && !ElementalHeroTempestProtectsBattleZone(sActionData.opponentMonsterRow, sActionData.unk16)
      && !CanMonsterBeDestroyedByBattle(
          sActionData.opponentCardId, DUEL_OPPONENT,
          sActionData.opponentCardAtkOrLifePointsMod,
          sActionData.playerCardAtkOrLifePointsMod)) {
    sActionData.flags &= ~2;
  }
}

void Duel_RemapMutualDestroyBattleAnim(u8 playerDestroy, u8 opponentDestroy)
{
  if (!IsMonsterVersusMonsterBattleAction(sActionData.id))
    return;

  if (playerDestroy && opponentDestroy) {
    gUnk2023EA0.unk18 = 2;
    return;
  }

  if (!playerDestroy && !opponentDestroy) {
    gUnk2023EA0.unk18 = 8;
    return;
  }

  if (gUnk2023EA0.unk18 != 2 && gUnk2023EA0.unk18 != 16 && gUnk2023EA0.unk18 != 17)
    return;

  if (!playerDestroy && opponentDestroy)
    gUnk2023EA0.unk18 = 1;
  else if (playerDestroy && !opponentDestroy)
    gUnk2023EA0.unk18 = 3;
}

void Duel_ActivateContinuousZone(struct DuelCard *zone)
{
  if (zone == NULL)
    return;

  FlipCardFaceUp(zone);
  zone->isLocked = TRUE;
}

u16 Duel_GetZoneFinalAtk(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return 0;

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;
  gSetFinalStatZone = NULL;
  return atk;
}

u8 Duel_FixedMonsterRowForDuelist(u8 fixedDuelist)
{
  return fixedDuelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

u8 Duel_FixedDuelistForMonsterRow(u8 fixedRow)
{
  return fixedRow == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;
}

u8 Duel_TurnMonsterRowForDuelist(u8 turnDuelist)
{
  return MonsterRowForDuelist(turnDuelist);
}

u8 Duel_TurnDuelistForFixedDuelist(u8 fixedDuelist)
{
  return FixedDuelistToTurnDuelist(fixedDuelist);
}

u8 Duel_TurnDuelistMatchingWhoseTurn(u8 fixedDuelist)
{
  return (fixedDuelist == DUEL_PLAYER) == (WhoseTurn() == DUEL_PLAYER) ? ACTIVE_DUELIST
                                                                         : INACTIVE_DUELIST;
}

u8 Duel_CountMonstersOnTurnRow(u8 turnRow)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnZones[turnRow][col]->id != CARD_NONE)
      count++;
  }

  return count;
}

u8 Duel_IsFixedMonsterRow(u8 fixedRow)
{
  return fixedRow == OPPONENT_MONSTER_ROW || fixedRow == PLAYER_MONSTER_ROW;
}

u8 Duel_IsTurnMonsterRow(u8 turnRow)
{
  return turnRow == INACTIVE_DUELIST_MONSTER_ROW || turnRow == ACTIVE_DUELIST_MONSTER_ROW;
}

u8 Duel_FixedMonsterRowToTurnMonsterRow(u8 fixedRow)
{
  u8 fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  u8 turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);

  return Duel_TurnMonsterRowForDuelist(turnDuelist);
}

u8 Duel_FixedMonsterRowHasMultipleMonsterTypes(u8 fixedRow)
{
  u8 col;
  u8 otherCol;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];
    u8 typeA;

    if (zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    typeA = gCardInfo.type;

    for (otherCol = col + 1; otherCol < MAX_ZONES_IN_ROW; otherCol++) {
      struct DuelCard *other = gFixedZones[fixedRow][otherCol];

      if (other->id == CARD_NONE)
        continue;

      if (GetTypeGroup(other->id) != TYPE_GROUP_MONSTER)
        continue;

      SetCardInfo(other->id);
      if (gCardInfo.type != typeA)
        return TRUE;
    }
  }

  return FALSE;
}

u8 Duel_GetLeftmostMonsterTypeOnFixedRow(u8 fixedRow)
{
  u8 col;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    return gCardInfo.type;
  }

  return 0xFF;
}

static u8 MonsterZoneHasWrongTypeForSingleTypeLock(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 keptType;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_FindFixedMonsterZone(zone, &fixedRow, &col))
    return FALSE;

  keptType = Duel_GetLeftmostMonsterTypeOnFixedRow(fixedRow);
  if (keptType == 0xFF)
    return FALSE;

  SetCardInfo(zone->id);
  return gCardInfo.type != keptType;
}

enum DuelActionResult Duel_EnforceSingleMonsterTypeOnFixedRow(u8 fixedRow, u8 updateGfx)
{
  u8 turnRow;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return DUEL_ACTION_INVALID;

  if (Duel_GetLeftmostMonsterTypeOnFixedRow(fixedRow) == 0xFF)
    return DUEL_ACTION_OK;

  turnRow = Duel_FixedMonsterRowToTurnMonsterRow(fixedRow);
  return Duel_DestroyAllMonstersMatching(turnRow, MonsterZoneHasWrongTypeForSingleTypeLock,
                                         updateGfx);
}

void Duel_EnforceSingleMonsterTypeOnBothMonsterRows(u8 updateGfx)
{
  if (Duel_EnforceSingleMonsterTypeOnFixedRow(OPPONENT_MONSTER_ROW, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  Duel_EnforceSingleMonsterTypeOnFixedRow(PLAYER_MONSTER_ROW, updateGfx);
}

void Duel_NotifyFixedMonsterRowChanged(u8 fixedRow)
{
  if (!Duel_IsFixedMonsterRow(fixedRow))
    return;

  /* ponytail: opponent AI may call sub_8040EF0 after CopyCard and wipe text shown
   * mid-action; player-turn notifies can flip immediately. */
  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    RivalryOfWarlords_CheckAfterFieldChange();
}

void Duel_NotifyMonsterZoneChanged(struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 turnRow;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (Duel_FindFixedMonsterZone(zone, &fixedRow, &col)) {
    Duel_NotifyFixedMonsterRowChanged(fixedRow);
    return;
  }

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  fixedRow = Duel_FixedMonsterRowForDuelist(
      TurnDuelistToFixed(turnRow == ACTIVE_DUELIST_MONSTER_ROW ? ACTIVE_DUELIST
                                                               : INACTIVE_DUELIST));
  Duel_NotifyFixedMonsterRowChanged(fixedRow);
}

void Duel_CheckRivalryOfWarlordsAfterFieldChange(void)
{
  RivalryOfWarlords_CheckAfterFieldChange();
}

void Duel_CheckLevelLimitAreaBAfterFieldChange(void)
{
  LevelLimitAreaB_CheckAfterFieldChange();
}

void Duel_CheckLevelLimitAreaAAfterFieldChange(void)
{
  LevelLimitAreaA_CheckAfterFieldChange();
}

void Duel_CheckAmazonessTigerAfterFieldChange(void)
{
  AmazonessTiger_EnforceUniquenessOnField();
}

void Duel_CheckRingOfDestructionAfterFieldChange(void)
{
  RingOfDestruction_CheckAfterFieldChange();
}

u8 Duel_IsMonsterZoneTarget(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

struct DuelCard *Duel_FindFixedZoneById(u8 fixedRow, u16 cardId, u8 requireFaceUp)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[fixedRow][col];

    if (zone->id != cardId)
      continue;
    if (requireFaceUp && zone->isFaceUp != TRUE)
      continue;
    return zone;
  }

  return NULL;
}

struct DuelCard *Duel_FindBackrowCard(u8 fixedDuelist, u16 cardId, u8 requireFaceUp)
{
  u8 backrow = fixedDuelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  return Duel_FindFixedZoneById(backrow, cardId, requireFaceUp);
}

struct DuelCard *Duel_FindBackrowCardOnField(u16 cardId, u8 requireFaceUp)
{
  struct DuelCard *zone = Duel_FindBackrowCard(DUEL_OPPONENT, cardId, requireFaceUp);

  if (zone != NULL)
    return zone;

  return Duel_FindBackrowCard(DUEL_PLAYER, cardId, requireFaceUp);
}

u8 Duel_IsBackrowCardOnField(u16 cardId, u8 requireFaceUp)
{
  return Duel_FindBackrowCard(DUEL_PLAYER, cardId, requireFaceUp) != NULL
      || Duel_FindBackrowCard(DUEL_OPPONENT, cardId, requireFaceUp) != NULL;
}

u8 Duel_FixedMonsterSlotBit(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return 0xFF;

  return (fixedRow - OPPONENT_MONSTER_ROW) * MAX_ZONES_IN_ROW + col;
}

u8 Duel_ZoneIsHandSlot(const struct DuelCard *zone)
{
  u8 turnDuelist;
  u8 col;

  if (zone == NULL)
    return FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gFixedZones[PLAYER_HAND][col] == zone)
      return TRUE;
  }

  for (turnDuelist = 0; turnDuelist < 2; turnDuelist++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gTurnHands[turnDuelist][col] == zone)
        return TRUE;
    }
  }

  return FALSE;
}

enum DuelActionResult Duel_ChangeLpSuppressingEffectText(u8 turnDuelist, s32 delta, u8 updateGfx)
{
  u8 hideEffectText = gHideEffectText;
  enum DuelActionResult result;

  gHideEffectText = TRUE;
  result = Duel_ChangeLp(turnDuelist, delta, updateGfx);
  gHideEffectText = hideEffectText;
  return result;
}

enum DuelActionResult Duel_ChangeLpWithPrefaceText(u8 turnDuelist, s32 delta, u16 cardId,
                                                   u8 textType, u8 updateGfx)
{
  u8 hideEffectText = gHideEffectText;
  enum DuelActionResult result;

  if (!hideEffectText) {
    Duel_ShowEffectTextTyped(cardId, textType);
    ResetCardEffectTextData();
  }

  gHideEffectText = TRUE;
  result = Duel_ChangeLp(turnDuelist, delta, updateGfx);
  gHideEffectText = hideEffectText;
  return result;
}

enum DuelActionResult Duel_ResolveBurnSpell(u16 spellId, s32 damage, u8 destroySpellGfx)
{
  enum DuelActionResult result;

  result = Duel_ChangeLp(INACTIVE_DUELIST, -damage, FALSE);
  if (result == DUEL_ACTION_DUEL_OVER)
    return result;

  Duel_DestroyZone(gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1], ACTIVE_DUELIST,
                   destroySpellGfx);
  Duel_ShowEffectText(spellId);
  return DUEL_ACTION_OK;
}

void Duel_ShowTrapResponseText(u16 trapId, u16 originCardId)
{
  if (gHideEffectText)
    return;

  gCardEffectTextData.cardId2 = originCardId;
  Duel_ShowEffectText(trapId);
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

enum DuelActionResult Duel_TryResolveTrapThroughTraps(u16 trapId)
{
  if (GetTypeGroup(trapId) != TYPE_GROUP_TRAP)
    return DUEL_ACTION_OK;

  if (IsTrapTriggered() != TRUE || gHideEffectText)
    return DUEL_ACTION_OK;

  ActivateTrapEffect(0);
  return DUEL_ACTION_BLOCKED;
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

enum DuelActionResult Duel_BanishZone(struct DuelCard *zone, u8 updateGfx)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  ClearZone(zone);
  MaybeUpdateGfx(updateGfx);

  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  return DUEL_ACTION_OK;
}

static u8 sSpellEffectResolveDepth APPEND_DATA = 0;
static u8 sMonsterEffectResolveDepth APPEND_DATA = 0;

void Duel_BeginSpellEffectResolve(void)
{
  sSpellEffectResolveDepth++;
}

void Duel_EndSpellEffectResolve(void)
{
  if (sSpellEffectResolveDepth > 0)
    sSpellEffectResolveDepth--;
}

u8 Duel_IsSpellEffectResolving(void)
{
  return sSpellEffectResolveDepth > 0 && gTrapEffectData.trapCardId == 0;
}

void Duel_BeginMonsterEffectResolve(void)
{
  sMonsterEffectResolveDepth++;
}

void Duel_EndMonsterEffectResolve(void)
{
  if (sMonsterEffectResolveDepth > 0)
    sMonsterEffectResolveDepth--;
}

u8 Duel_IsMonsterEffectResolving(void)
{
  return sMonsterEffectResolveDepth > 0;
}

u8 Duel_ZoneIsImmuneToSpellEffects(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return FALSE;

  return IsImmuneToSpellEffectsOnField(zone->id, turnRow);
}

u8 Duel_SpellMayTargetMonsterZone(struct DuelCard *zone)
{
  return !Duel_ZoneIsImmuneToSpellEffects(zone);
}

u8 Duel_IsAnyTrapActivationBlocked(void)
{
  if (IsRoyalDecreeActiveOnField())
    return TRUE;
  if (IsSorcererOfDarkMagicTrapLockActive())
    return TRUE;
  return FALSE;
}

u8 Duel_IsCardActivationBlocked(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE || cardId >= NUM_TOTAL_CARDS)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  if (typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_RITUAL) {
    if (IsSpellCancellerSpellLockActive())
      return TRUE;
    if (IsImperialOrderNegatingSpell(cardId))
      return TRUE;
    return FALSE;
  }

  if (typeGroup == TYPE_GROUP_TRAP) {
    if (IsRoyalDecreeNegatingTrap(cardId))
      return TRUE;
    if (IsSorcererOfDarkMagicTrapLockActive())
      return TRUE;
    return FALSE;
  }

  return FALSE;
}

// --- PickZone targeting ----------------------------------------------------

static u8 FindFirstValidTarget(u8 *outRow, u8 *outCol)
{
  u8 row, col;

  if (gPickZoneState.validator == NULL)
    return FALSE;

  for (row = 0; row < 4; row++) {
    for (col = 0; col < 5; col++) {
      if (gPickZoneState.validator(row, col)) {
        *outRow = row;
        *outCol = col;
        return TRUE;
      }
    }
  }
  return FALSE;
}

void Duel_SetupPickZone(PickZoneValidator validator, PickZoneResolver resolver,
                         PickZoneCanceller canceller, PickZoneAiPicker aiPicker)
{
  gPickZoneState.validator = validator;
  gPickZoneState.resolver = resolver;
  gPickZoneState.canceller = canceller;
  gPickZoneState.aiPicker = aiPicker;
}

void Duel_EnterPickZoneTargeting(void)
{
  u8 targetRow, targetCol;

  if (!FindFirstValidTarget(&targetRow, &targetCol))
    return;

  if (IsDuelOver() == TRUE)
    return;

  PlayMusic(SFX_SELECT);
  gDuelCursor.state = DUEL_CURSOR_PICK_ZONE;
  gDuelCursor.currentY = targetRow;
  gDuelCursor.currentX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

void Duel_HandlePickZoneA(void)
{
  u8 targetRow = gDuelCursor.currentY;
  u8 targetCol = gDuelCursor.currentX;
  u8 originRow = gDuelCursor.destY;
  u8 originCol = gDuelCursor.destX;

  if (!gPickZoneState.validator(targetRow, targetCol)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  gPickZoneState.resolver(targetRow, targetCol);

  /* If resolver re-entered targeting (multi-pick like Mobius), skip cleanup */
  if (gDuelCursor.state == DUEL_CURSOR_PICK_ZONE)
    return;

  gDuelCursor.state = 0;
  gDuelCursor.currentY = originRow;
  gDuelCursor.currentX = originCol;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void Duel_HandlePickZoneB(void)
{
  u8 currY = gDuelCursor.currentY;

  gPickZoneState.canceller();

  gDuelCursor.state = 0;
  SetCursorToCardDest();
  DisplayCardInfoBar();
  sub_8041E70(currY, gDuelCursor.currentY);
}

void Duel_ResolvePickZoneForAi(void)
{
  u8 targetRow, targetCol;
  u16 originId;

  if (gPickZoneState.aiPicker == NULL || !gPickZoneState.aiPicker(&targetRow, &targetCol))
    return;

  if (gMonEffect.id != CARD_NONE && GetTypeGroup(gMonEffect.id) == TYPE_GROUP_MONSTER)
    originId = gMonEffect.id;
  else if (gActiveEffect.cardId != CARD_NONE
           && GetTypeGroup(gActiveEffect.cardId) == TYPE_GROUP_MONSTER)
    originId = gActiveEffect.cardId;
  else
    originId = CARD_NONE;

  if (Duel_TryNegateMonsterEffectOnTarget(originId, targetRow, targetCol))
    return;

  gPickZoneState.resolver(targetRow, targetCol);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DuelHelpers_SelfCheck(void)
{
  struct DuelCard hand[5];
  struct DuelCard *handRow[5];
  struct DuelCard zone;
  u8 i;

  if (Duel_ClampStat(0xFFFF) != 0xFFFE || Duel_ClampStat(100) != 100)
    while (1)
      ;

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

  if (Duel_CardIsMonster(THE_THING_IN_THE_CRATER) != TRUE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(THE_THING_IN_THE_CRATER, TYPE_PYRO) != TRUE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(METEOR_B_DRAGON, TYPE_PYRO) != FALSE)
    while (1)
      ;

  if (Duel_CardHasMonsterType(FLAME_MANIPULATOR, TYPE_PYRO) != TRUE)
    while (1)
      ;

  if (CanMonsterBeDestroyedByBattle(SPIRIT_REAPER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(SPIRIT_REAPER, DUEL_PLAYER, 2000, 1999) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(ELEMENTAL_HERO_PHOENIX_ENFORCER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(ELEMENTAL_HERO_SHINING_PHOENIX_ENFORCER, DUEL_PLAYER, 2000, 2000) != FALSE)
    __builtin_trap();
  if (CanMonsterBeDestroyedByBattle(KAISER_GLIDER, DUEL_PLAYER, 1500, 1500) != TRUE)
    __builtin_trap();
}
#endif
