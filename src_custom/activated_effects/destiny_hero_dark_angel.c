#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 CountDestinyHeroInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 count = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsDestinyHeroMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 1 : 0;

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsDestinyHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      count++;
  }

  return count;
}

static u16 TakeDestinyHeroFromGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      return CARD_NONE;

    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
    return cardId;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDestinyHeroMonster(cardId) || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
    return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateDESTINY_HERO_DARK_ANGEL(void)
{
  if (gMonEffect.id != DESTINY_HERO_DARK_ANGEL)
    return FALSE;

  /* Ceiling: field spell-negate FALSE.
   * Ceiling: FromHand discard → SS D-HERO to opp DEF. */
  return FALSE;
}

void ActivateDESTINY_HERO_DARK_ANGELEffect(void)
{
  Duel_ShowEffectTextTyped(DESTINY_HERO_DARK_ANGEL, 2);
}

u8 CanSpecialSummonDestinyHeroDarkAngelFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != DESTINY_HERO_DARK_ANGEL)
    return FALSE;

  if (CountDestinyHeroInGy() < 3)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonDestinyHeroDarkAngelFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 reviveId;

  if (!CanSpecialSummonDestinyHeroDarkAngelFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DARK_ANGEL, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  reviveId = TakeDestinyHeroFromGy();
  if (reviveId == CARD_NONE)
    return FALSE;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonMonsterId(INACTIVE_DUELIST, reviveId, opts) != DUEL_ACTION_OK)
    return FALSE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanSpecialSummonDestinyHeroDarkAngelFromHand(u8 handZone);
u8 TrySpecialSummonDestinyHeroDarkAngelFromHand(u8 handZone);
#endif
