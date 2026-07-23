#include "global.h"
#include "common-chax.h"
#include "alluring_mirror_split.h"
#include "constants/card_ids.h"
#include "duel.h"
#include "duel_helpers.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "expanded_graveyard.h"
#include "spell_effects.h"

static const char sHarpieName[] APPEND_RODATA = "Harpie";
static const char sHarpieLadySistersName[] APPEND_RODATA = "Harpie Lady Sisters";

static u8 IsHarpieMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsHarpieCard(u16 cardId)
{
  if (cardId == CARD_NONE)
    return FALSE;

  return Duel_CardNameContains(cardId, sHarpieName);
}

static u8 IsHarpieLadyOrSisters(u16 cardId)
{
  if (cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == HARPIE_LADY_SISTERS
      || cardId == CYBER_SLASH_HARPIE_LADY || cardId == CYBER_SLASH_HARPY_LADY
      || cardId == HARPIE_PERFUMER || cardId == HARPIE_QUEEN || cardId == HARPIE_DANCER
      || cardId == HARPIE_ORACLE || cardId == HARPIE_CONDUCTOR || cardId == HARPIE_CHANNELER
      || cardId == HARPIE_HARPIST)
    return TRUE;

  return Duel_CardNameContains(cardId, sHarpieLadySistersName);
}

static u8 FixedDuelistForController(u8 controller)
{
  return controller == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
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

static u16 FindDifferentNameHarpieInDeck(u8 fixedDuelist, u16 destroyedId)
{
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (!IsHarpieMonster(cardId))
      continue;
    if (cardId == destroyedId)
      continue;
    if (Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    return cardId;
  }

  return CARD_NONE;
}

static u8 CurrentEffectIsHarpieCard(void)
{
  if (IsHarpieCard(gSpellEffectData.id))
    return TRUE;
  if (IsHarpieCard(gMonEffect.id))
    return TRUE;
  if (IsHarpieCard(gActiveEffect.cardId))
    return TRUE;
  if (IsHarpieCard(gTrapEffectData.originCardId))
    return TRUE;

  return FALSE;
}

static u8 DestroyedByOpponentOrHarpieEffect(u8 mirrorController)
{
  /* Activator is ACTIVE; Mirror owner inactive ⇒ opponent's effect. */
  if (TurnDuelistForFixed(mirrorController) == INACTIVE_DUELIST)
    return TRUE;

  return CurrentEffectIsHarpieCard();
}

static u16 FindHarpieInGraveyard(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsHarpieMonster(top) && !Duel_CardCannotBeSpecialSummoned(top))
      return top;
    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsHarpieMonster(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

u8 Cond_AlluringMirrorSplitBattleDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!IsHarpieLadyOrSisters(ev->cardId))
    return FALSE;

  fixedDuelist = FixedDuelistForController(ev->controller);
  if (Duel_FindBackrowCard(fixedDuelist, ALLURING_MIRROR_SPLIT, TRUE) == NULL)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[MonsterTurnRowForFixed(fixedDuelist)]) < 0) {
    if (ev->fixedRow != PLAYER_MONSTER_ROW && ev->fixedRow != OPPONENT_MONSTER_ROW)
      return FALSE;
    if (Duel_FixedDuelistForMonsterRow(ev->fixedRow) != fixedDuelist)
      return FALSE;
  }

  return FindDifferentNameHarpieInDeck(fixedDuelist, ev->cardId) != CARD_NONE;
}

enum DuelActionResult Op_AlluringMirrorSplitBattleDestroy(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  fixedDuelist = FixedDuelistForController(ev->controller);
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  cardId = FindDifferentNameHarpieInDeck(fixedDuelist, ev->cardId);
  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShowEffectText(ALLURING_MIRROR_SPLIT);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  return Duel_SpecialSummonFromDeck(turnDuelist, cardId, opts);
}

u8 Cond_AlluringMirrorSplitFloat(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;

  if (ctx == NULL || ctx->event == NULL)
    return FALSE;

  ev = ctx->event;
  if (ev->cardId != ALLURING_MIRROR_SPLIT)
    return FALSE;

  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return FALSE;

  if (!DestroyedByOpponentOrHarpieEffect(ev->controller))
    return FALSE;

  fixedDuelist = FixedDuelistForController(ev->controller);
  if (FirstEmptyZoneInRow(gTurnZones[MonsterTurnRowForFixed(fixedDuelist)]) < 0)
    return FALSE;

  return FindHarpieInGraveyard(fixedDuelist) != CARD_NONE;
}

enum DuelActionResult Op_AlluringMirrorSplitFloat(struct EffectCtx *ctx)
{
  const struct EffectEvent *ev;
  u8 fixedDuelist;
  u8 turnDuelist;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (ctx == NULL || ctx->event == NULL)
    return DUEL_ACTION_INVALID;

  ev = ctx->event;
  fixedDuelist = FixedDuelistForController(ev->controller);
  turnDuelist = TurnDuelistForFixed(fixedDuelist);
  cardId = FindHarpieInGraveyard(fixedDuelist);
  if (cardId == CARD_NONE)
    return DUEL_ACTION_NO_TARGET;

  Duel_ShowEffectText(ALLURING_MIRROR_SPLIT);
  if (IsDuelOver() == TRUE)
    return DUEL_ACTION_DUEL_OVER;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  return Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts);
}

APPEND_TEXT void EffectALLURING_MIRROR_SPLIT(void)
{
  const struct EffectScript *script =
      EffectScript_Find(ALLURING_MIRROR_SPLIT, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ALLURING_MIRROR_SPLIT_SelfCheck(void)
{
  if (!IsHarpieMonster(HARPIE_LADY))
    while (1)
      ;
  if (!IsHarpieLadyOrSisters(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (IsHarpieMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
