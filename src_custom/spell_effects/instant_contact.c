#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "configs/runtime.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "effect_events.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "fusion_duel.h"
#include "player_decks.h"
#include "spell_effects.h"

#define INSTANT_CONTACT_LP_COST 1000
#define INSTANT_CONTACT_MAX_LEVEL 7

void UpdateDuelGfxExceptField(void);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

static const char sNeoSpacianName[] APPEND_RODATA = "Neo-Spacian";

static const u8 sInstantContactPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

/* OPT via EffectOpt_* — cleared on turn boundary (EffectEvent_OnTurnBoundary). */

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u16 *ActiveExtraDeck(void)
{
  u8 active = gActiveDeckIndex;

  if (active >= PLAYER_DECK_INDEX_MIN && active <= PLAYER_DECK_INDEX_MAX) {
    switch (active) {
    case 1:
      return gPlayerDeck1ExtraDeck;
    case 2:
      return gPlayerDeck2ExtraDeck;
    case 3:
      return gPlayerDeck3ExtraDeck;
    default:
      return gPlayerDeck1ExtraDeck;
    }
  }

  return gPlayerDeck1ExtraDeck;
}

static u8 IsNeoSpacianMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sNeoSpacianName);
}

static u8 IsInstantContactTarget(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (!Duel_IsElementalHeroCard(cardId) && !IsNeoSpacianMonster(cardId))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= INSTANT_CONTACT_MAX_LEVEL;
}

static u8 BuildInstantContactTargets(u16 *outIds, u8 maxOut)
{
  u8 count = 0;
  u8 i;
  u8 j;

  if (outIds == NULL || maxOut == 0)
    return 0;

  if (gRuntimeConfig.enable_extra_deck) {
    u16 *extra = ActiveExtraDeck();

    for (i = 0; i < EXTRA_DECK_SIZE && count < maxOut; i++) {
      u16 cardId = extra[i];
      u8 dup = FALSE;

      if (!IsInstantContactTarget(cardId))
        continue;

      for (j = 0; j < count; j++) {
        if (outIds[j] == cardId) {
          dup = TRUE;
          break;
        }
      }
      if (dup)
        continue;

      outIds[count++] = cardId;
    }

    return count;
  }

  /* Extra Deck off: offer matching Fusion recipe results by id. */
  {
    u8 recipeCount = FusionRecipe_Count();

    for (i = 0; i < recipeCount && count < maxOut; i++) {
      u16 cardId = gFusionRecipes[i].result;
      u8 dup = FALSE;

      if (!IsInstantContactTarget(cardId))
        continue;

      for (j = 0; j < count; j++) {
        if (outIds[j] == cardId) {
          dup = TRUE;
          break;
        }
      }
      if (dup)
        continue;

      outIds[count++] = cardId;
    }
  }

  return count;
}

static u16 PlayerPickInstantContactTarget(const u16 *targetIds, u8 count)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 j;
  u16 chosenId;

  if (targetIds == NULL || count == 0)
    return CARD_NONE;

  if (count == 1)
    return targetIds[0];

  DECKMENU_SAVE();

  for (j = 0; j < EXTRA_DECK_SIZE; j++)
    gDeckMenu.cards[j] = CARD_NONE;
  for (j = 0; j < count; j++)
    gDeckMenu.cards[j] = targetIds[j];

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = count;

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sInstantContactPickLabels,
                                         ARRAY_COUNT(sInstantContactPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return CARD_NONE;
  }

  chosenId = gDeckMenu.cards[gDeckMenu.currentPos];
  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenId;
}

static u16 AiPickInstantContactTarget(const u16 *targetIds, u8 count)
{
  u8 i;
  u16 bestId = CARD_NONE;
  u16 bestAtk = 0;

  for (i = 0; i < count; i++) {
    SetCardInfo(targetIds[i]);
    if (bestId == CARD_NONE || gCardInfo.atk > bestAtk) {
      bestId = targetIds[i];
      bestAtk = gCardInfo.atk;
    }
  }

  return bestId;
}

static u8 ControlsOrGyHasElementalHeroNeos(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u8 i;
  u8 gyCount;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i]->id == ELEMENTAL_HERO_NEOS)
      return TRUE;
  }

  if (!GraveyardExpand_IsEnabled())
    return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == ELEMENTAL_HERO_NEOS;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == ELEMENTAL_HERO_NEOS)
      return TRUE;
  }

  return FALSE;
}

static u8 CanActivateInstantContact(void)
{
  u16 targets[EXTRA_DECK_SIZE];

  if (EffectOpt_IsUsed(INSTANT_CONTACT))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (WhoseTurn() == DUEL_PLAYER) {
    if (gDuelLifePoints[DUEL_PLAYER] < INSTANT_CONTACT_LP_COST)
      return FALSE;
  } else if (gDuelLifePoints[DUEL_OPPONENT] < INSTANT_CONTACT_LP_COST) {
    return FALSE;
  }

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return BuildInstantContactTargets(targets, EXTRA_DECK_SIZE) > 0;
}

static void INSTANT_CONTACT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u16 targets[EXTRA_DECK_SIZE];
  u8 targetCount;
  u16 chosenId;
  struct DuelSummonOpts opts;
  u8 neosPresent;

  Duel_ShowEffectText(INSTANT_CONTACT);

  if (IsDuelOver() == TRUE || !CanActivateInstantContact())
    return;

  if (Duel_ChangeLp(ACTIVE_DUELIST, -INSTANT_CONTACT_LP_COST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  targetCount = BuildInstantContactTargets(targets, EXTRA_DECK_SIZE);
  if (targetCount == 0)
    return;

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText)
    chosenId = PlayerPickInstantContactTarget(targets, targetCount);
  else
    chosenId = AiPickInstantContactTarget(targets, targetCount);

  if (chosenId == CARD_NONE || !IsInstantContactTarget(chosenId))
    return;

  if (gRuntimeConfig.enable_extra_deck
      && (Duel_BlocksExtraDeckSpecialSummon(chosenId) || !ExtraDeck_TryRemoveCard(chosenId)))
    return;

  Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);
  if (IsDuelOver() == TRUE)
    return;

  neosPresent = ControlsOrGyHasElementalHeroNeos();

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  /* Without Neos: cannot attack — isLocked honored by attack validators. */
  opts.lockMonster = !neosPresent;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, chosenId, opts) != DUEL_ACTION_OK)
    return;

  EffectOpt_MarkUsed(INSTANT_CONTACT);

  /* ponytail: without Neos, effects negated + End Phase return to Extra need
   * negate + turn_effect hooks outside this file. Ceiling: SS + attack-lock only
   * when Neos absent; upgrade: mark zone / turn_effect End Phase → ExtraDeck
   * return + effect-negate while marked. */
}

APPEND_TEXT void EffectINSTANT_CONTACT(void)
{
  if (!CanActivateInstantContact()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTrapsEx(INSTANT_CONTACT, INSTANT_CONTACT_LP_COST,
                                         INSTANT_CONTACT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void INSTANT_CONTACT_SelfCheck(void)
{
  if (!IsInstantContactTarget(ELEMENTAL_HERO_FLAME_WINGMAN))
    while (1)
      ;
  if (!IsNeoSpacianMonster(NEO_SPACIAN_AIR_HUMMINGBIRD))
    while (1)
      ;
  if (IsInstantContactTarget(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
