#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define RAINBOW_DARK_HAND_COST 7

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 GraveyardCardIsDarkMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.attribute == ATTRIBUTE_SHADOW;
}

static u8 CountDistinctDarkNamesInGraveyard(u8 fixedDuelist)
{
  u16 seen[RAINBOW_DARK_HAND_COST];
  u8 distinct = 0;
  u8 i;
  u8 j;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return GraveyardCardIsDarkMonster(cardId) ? 1 : 0;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);
    u8 already = FALSE;

    if (!GraveyardCardIsDarkMonster(cardId))
      continue;

    for (j = 0; j < distinct; j++) {
      if (seen[j] == cardId) {
        already = TRUE;
        break;
      }
    }

    if (already)
      continue;

    seen[distinct++] = cardId;
    if (distinct >= RAINBOW_DARK_HAND_COST)
      break;
  }

  return distinct;
}

static u8 BanishDistinctDarkFromGraveyard(u8 fixedDuelist, u8 count)
{
  u16 seen[RAINBOW_DARK_HAND_COST];
  u8 banished = 0;
  u8 i;
  u8 j;

  while (banished < count) {
    u8 found = FALSE;

    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
      u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);
      u8 already = FALSE;

      if (!GraveyardCardIsDarkMonster(cardId))
        continue;

      for (j = 0; j < banished; j++) {
        if (seen[j] == cardId) {
          already = TRUE;
          break;
        }
      }

      if (already)
        continue;

      seen[banished] = cardId;
      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
      found = TRUE;
      break;
    }

    if (!found)
      return banished;
  }

  return banished;
}

static u8 IsOtherDarkMonsterOnField(struct DuelCard *zone, struct DuelCard *self)
{
  if (zone == NULL || zone == self || zone->id == CARD_NONE)
    return FALSE;

  return GraveyardCardIsDarkMonster(zone->id);
}

static u8 CountOtherDarkOnField(struct DuelCard *self)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (IsOtherDarkMonsterOnField(zone, self))
      count++;
  }

  return count;
}

static u8 CountOtherDarkInGraveyard(u8 fixedDuelist)
{
  u8 i;
  u8 count = 0;

  if (!GraveyardExpand_IsEnabled())
    return 0;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardCardIsDarkMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u8 BanishOtherDarkFromField(struct DuelCard *self, u8 *outBanished)
{
  u8 col;
  u8 banished = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOtherDarkMonsterOnField(zone, self))
      continue;

    if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
      return FALSE;

    banished++;
  }

  *outBanished = banished;
  return TRUE;
}

static u8 BanishAllDarkFromGraveyard(u8 fixedDuelist, u8 *outBanished)
{
  u8 banished = 0;
  u8 i;

  for (;;) {
    u8 found = FALSE;

    for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
      if (!GraveyardCardIsDarkMonster(GraveyardExpand_GetCardAt(fixedDuelist, i - 1)))
        continue;

      Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1);
      banished++;
      found = TRUE;
      break;
    }

    if (!found)
      break;
  }

  *outBanished = banished;
  return TRUE;
}

u8 CanSpecialSummonRainbowDarkDragonFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u8 fixedDuelist = FixedDuelistForActive();

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != RAINBOW_DARK_DRAGON)
    return FALSE;

  if (!GraveyardExpand_IsEnabled())
    return FALSE;

  if (CountDistinctDarkNamesInGraveyard(fixedDuelist) < RAINBOW_DARK_HAND_COST)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonRainbowDarkDragonFromHand(u8 handZone)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u8 fixedDuelist = FixedDuelistForActive();

  if (!CanSpecialSummonRainbowDarkDragonFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(RAINBOW_DARK_DRAGON, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (BanishDistinctDarkFromGraveyard(fixedDuelist, RAINBOW_DARK_HAND_COST)
      < RAINBOW_DARK_HAND_COST)
    return FALSE;

  GraveyardExpand_RefreshDisplay();
  UpdateDuelGfxExceptField();

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

unsigned char CanActivateRAINBOW_DARK_DRAGON(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist = FixedDuelistForActive();

  if (gMonEffect.id != RAINBOW_DARK_DRAGON)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != RAINBOW_DARK_DRAGON)
    return FALSE;

  /* hand SS by banishing 7 different DARK uses FromHand path. Ceiling:
   * OPT banish other DARK you control/from GY → +500 ATK each (tempStage). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountOtherDarkOnField(zone) > 0 || CountOtherDarkInGraveyard(fixedDuelist) > 0;
}

void ActivateRAINBOW_DARK_DRAGONEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist = FixedDuelistForActive();
  u8 fieldBanished = 0;
  u8 gyBanished = 0;
  u8 totalBanished;

  Duel_ShowEffectTextTyped(RAINBOW_DARK_DRAGON, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!BanishOtherDarkFromField(self, &fieldBanished))
    return;

  BanishAllDarkFromGraveyard(fixedDuelist, &gyBanished);
  GraveyardExpand_RefreshDisplay();

  totalBanished = fieldBanished + gyBanished;
  if (totalBanished > 0 && self->tempStage < 127 - (s8)totalBanished)
    self->tempStage += (s8)totalBanished;

  MarkMonsterEffectUsed(self);
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#if !defined(__GNUC__)
u8 CanSpecialSummonRainbowDarkDragonFromHand(u8 handZone);
u8 TrySpecialSummonRainbowDarkDragonFromHand(u8 handZone);
#endif
