#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
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

static u8 AddDarkFusionFromGy(u8 turnDuelist, s8 gyIndex)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 handZone;
  u16 cardId;
  struct DuelCard *slot;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
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

  slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
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

static u8 CanAddDarkFusion(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (Duel_FindDeckCardIndex(turnDuelist, DARK_FUSION) >= 0)
    return TRUE;

  return FindDarkFusionGyIndex(fixedDuelist) >= 0;
}

static u8 DoAddDarkFusion(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  s8 gyIndex;

  if (Duel_FindDeckCardIndex(turnDuelist, DARK_FUSION) >= 0)
    return Duel_AddDeckCardToHand(turnDuelist, DARK_FUSION, TRUE) == DUEL_ACTION_OK;

  gyIndex = FindDarkFusionGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  return AddDarkFusionFromGy(turnDuelist, gyIndex);
}

unsigned char ShouldActivateEVIL_HERO_INFERNO_WING_BACKFIRE(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != EVIL_HERO_INFERNO_WING_BACKFIRE)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* ponytail: true trigger is Special Summon; on-summon stand-in covers SS path. */
  return CanAddDarkFusion(duelist);
}

void ActivateEVIL_HERO_INFERNO_WING_BACKFIRE(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(EVIL_HERO_INFERNO_WING_BACKFIRE, 8);
  if (IsDuelOver() == TRUE)
    return;

  DoAddDarkFusion(duelist);
  UpdateDuelGfxExceptField();

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: HERO battle-destroy 2100 burn needs battle-end hook. */
}
