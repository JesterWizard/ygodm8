#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_doom_lord.h"
#include "duel_helpers.h"
#include "removed_from_play.h"

void UpdateDuelGfxExceptField(void);

#define DOOM_LORD_RETURN_STANDBYS 2

static u16 sDoomLordReturnCardId APPEND_DATA = {0};
static u8 sDoomLordReturnOppFixed APPEND_DATA = {0};
static u8 sDoomLordReturnOwnerFixed APPEND_DATA = {0xFF};
static u8 sDoomLordReturnStandbys APPEND_DATA = {0};

void DestinyHeroDoomLord_OnBanishOpponentMonster(u16 cardId, u8 oppFixedDuelist)
{
  u8 ownerFixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;

  sDoomLordReturnCardId = cardId;
  sDoomLordReturnOppFixed = oppFixedDuelist;
  sDoomLordReturnOwnerFixed = ownerFixed;
  sDoomLordReturnStandbys = DOOM_LORD_RETURN_STANDBYS;
}

void TryApplyDestinyHeroDoomLordStandbyReturn(void)
{
  u8 ownerFixed;
  u8 monsterRow;
  u8 col;
  struct DuelSummonOpts opts;

  if (sDoomLordReturnCardId == CARD_NONE || sDoomLordReturnStandbys == 0
      || sDoomLordReturnOwnerFixed > DUEL_OPPONENT)
    return;

  ownerFixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  if (ownerFixed != sDoomLordReturnOwnerFixed)
    return;

  monsterRow = ACTIVE_DUELIST_MONSTER_ROW;
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monsterRow][col];

    if (zone != NULL && zone->id == DESTINY_HERO_DOOM_LORD && !zone->isDefending
        && (IsCardFaceUp(zone) || zone->isFaceUp))
      break;
  }

  if (col >= MAX_ZONES_IN_ROW)
    return;

  sDoomLordReturnStandbys--;
  if (sDoomLordReturnStandbys != 0)
    return;

  if (!RemovedFromPlay_IsEnabled())
    return;

  if (!RemovedFromPlay_RemoveMatching(sDoomLordReturnOppFixed, sDoomLordReturnCardId))
    return;

  if (FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOOM_LORD, 9);

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonMonsterId(INACTIVE_DUELIST, sDoomLordReturnCardId, opts) != DUEL_ACTION_OK)
    return;

  sDoomLordReturnCardId = CARD_NONE;
  sDoomLordReturnOwnerFixed = 0xFF;
  UpdateDuelGfxExceptField();
}
