#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 FixedDuelistForTurn(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s8 FindDarkFusionGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == DARK_FUSION)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DARK_FUSION)
      return (s8)i;
  }

  return -1;
}

static u8 AddDarkFusionFromGyFor(u8 turnDuelist, s8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);
  s8 empty;
  u16 cardId;
  struct DuelCard *slot;

  empty = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (empty < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    if (cardId != DARK_FUSION)
      return FALSE;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    if (cardId != DARK_FUSION)
      return FALSE;
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    GraveyardExpand_RefreshDisplay();
  }

  slot = gTurnHands[turnDuelist][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

static u8 CanAddDarkFusionFor(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurn(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(turnDuelist, DARK_FUSION) >= 0)
    return TRUE;

  return FindDarkFusionGyIndex(fixedDuelist) >= 0;
}

static u8 CountOwnGyMonsters(u8 fixedDuelist)
{
  u8 i;
  u8 count = 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (GetTypeGroup(gDuel.duelistbattleState[fixedDuelist].graveyard) == TYPE_GROUP_MONSTER)
      return 1;
    return 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GetTypeGroup(GraveyardExpand_GetCardAt(fixedDuelist, i)) == TYPE_GROUP_MONSTER)
      count++;
  }

  return count;
}

static u8 CanSetSuperPolymerization(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();

  if (self == NULL)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(ACTIVE_DUELIST, SUPER_POLYMERIZATION) < 0)
    return FALSE;

  /* Need 4 other GY monsters (self banished from field as 5th). */
  return CountOwnGyMonsters(fixedDuelist) >= 4;
}

static u8 SetSpellFromDeck(u16 cardId)
{
  s8 empty;
  s16 deckIndex;
  struct DuelCard *slot;

  empty = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_BACKROW]);
  if (empty < 0)
    return FALSE;

  deckIndex = Duel_FindDeckCardIndex(ACTIVE_DUELIST, cardId);
  if (deckIndex < 0)
    return FALSE;

  if (Duel_RemoveDeckCardAt(ACTIVE_DUELIST, (u8)deckIndex, FALSE) != DUEL_ACTION_OK)
    return FALSE;

  Duel_ShuffleDeckFromDrawn(ACTIVE_DUELIST);

  slot = gTurnZones[ACTIVE_DUELIST_BACKROW][empty];
  slot->id = cardId;
  slot->isFaceUp = FALSE;
  slot->isLocked = FALSE;
  slot->isDefending = FALSE;
  slot->unkTwo = 0;
  slot->unkThree = 0;
  slot->unk4 = 0;
  slot->willChangeSides = FALSE;
  ResetPermStage(slot);
  ResetTempStage(slot);
  return TRUE;
}

static void BanishSelfAndFourGyMonsters(struct DuelCard *self)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 banished = 0;
  u8 i;

  if (Duel_BanishZone(self, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    /* Legacy: only top GY available — banish top repeatedly if monster. */
    while (banished < 4) {
      if (GetTypeGroup(gDuel.duelistbattleState[fixedDuelist].graveyard)
          != TYPE_GROUP_MONSTER)
        break;
      if (Duel_BanishGraveyardTopTurn(ACTIVE_DUELIST) == CARD_NONE)
        break;
      banished++;
    }
    return;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < 4; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
      continue;

    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1) == CARD_NONE)
      continue;

    banished++;
  }
}

static u8 DoAddDarkFusionFor(u8 turnDuelist)
{
  s8 gyIndex;

  if (Duel_FindDeckCardIndex(turnDuelist, DARK_FUSION) >= 0) {
    if (Duel_AddDeckCardToHand(turnDuelist, DARK_FUSION, TRUE) != DUEL_ACTION_OK)
      return FALSE;
    return TRUE;
  }

  gyIndex = FindDarkFusionGyIndex(FixedDuelistForTurn(turnDuelist));
  if (gyIndex < 0)
    return FALSE;

  return AddDarkFusionFromGyFor(turnDuelist, gyIndex);
}

static u8 DoSetSuperPolymerization(struct DuelCard *self)
{
  BanishSelfAndFourGyMonsters(self);
  if (IsDuelOver() == TRUE)
    return TRUE;

  return SetSpellFromDeck(SUPER_POLYMERIZATION);
}

void TryEvilHeroInfernalRiderOnMonsterPlacement(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 turnDuelist;

  if (zone == NULL || zone->id != EVIL_HERO_INFERNAL_RIDER)
    return;

  if (EffectOpt_IsUsed(EVIL_HERO_INFERNAL_RIDER))
    return;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist > DUEL_OPPONENT)
    return;

  turnDuelist = Duel_TurnDuelistForFixedDuelist(fixedDuelist);
  if (!CanAddDarkFusionFor(turnDuelist))
    return;

  Duel_ShowEffectTextTyped(EVIL_HERO_INFERNAL_RIDER, 8);

  if (!DoAddDarkFusionFor(turnDuelist))
    return;

  EffectOpt_MarkUsed(EVIL_HERO_INFERNAL_RIDER);
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateEVIL_HERO_INFERNAL_RIDER(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != EVIL_HERO_INFERNAL_RIDER)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_INFERNAL_RIDER)
    return FALSE;

  /* Add Dark Fusion via TryEvilHeroInfernalRiderOnMonsterPlacement (EffectOpt).
   * OPT banish self+4 GY → Set Super Poly.
   * HERO lock need SS gates. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  /* Dark Fusion add is on-summon; field OPT only for Super Poly path. */
  return CanSetSuperPolymerization(zone);
}

void ActivateEVIL_HERO_INFERNAL_RIDEREffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(EVIL_HERO_INFERNAL_RIDER, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!CanSetSuperPolymerization(self))
    return;

  if (!DoSetSuperPolymerization(self))
    return;

  if (self->id == EVIL_HERO_INFERNAL_RIDER)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
