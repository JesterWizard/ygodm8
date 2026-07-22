#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "helios_trice_megistus.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

#define HELIOS_TRICE_STAT_PER_BANISHED 300

static u8 CountBanishedMonsters(void)
{
  u8 total = 0;
  u8 d;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return 0;

  for (d = 0; d < 2; d++) {
    for (i = 0; i < RemovedFromPlay_GetCount(d); i++) {
      if (GetTypeGroup(RemovedFromPlay_GetCardAt(d, i)) == TYPE_GROUP_MONSTER)
        total++;
    }
  }
  return total;
}

u8 HeliosTriceMegistus_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != HELIOS_TRICE_MEGISTUS)
    return FALSE;

  stat = Duel_StatFromCount(CountBanishedMonsters(), HELIOS_TRICE_STAT_PER_BANISHED, 0);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

static struct DuelCard *FindHeliosDuoMegistusYouControl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == HELIOS_DUO_MEGISTUS)
      return zone;
  }
  return NULL;
}

unsigned char CanActivateHELIOS_TRICE_MEGISTUS(void)
{
  if (gMonEffect.id != HELIOS_TRICE_MEGISTUS)
    return FALSE;

  /* Continuous ATK/DEF via HeliosTriceMegistus_ApplyDynamicZoneStats.
   * Battle-destroy EP SS via ApplyHeliosTriceMegistusBattleDestroyPending.
   * ponytail: extra attack if opp controls a monster needs multi-attack hook. */
  return FALSE;
}

void ActivateHELIOS_TRICE_MEGISTUSEffect(void)
{
  Duel_ShowEffectTextTyped(HELIOS_TRICE_MEGISTUS, 2);
}

u8 CanSpecialSummonHeliosTriceMegistusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;
  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HELIOS_TRICE_MEGISTUS)
    return FALSE;
  if (FindHeliosDuoMegistusYouControl() == NULL)
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;
  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHeliosTriceMegistusFromHand(u8 handZone)
{
  struct DuelCard *tribute = FindHeliosDuoMegistusYouControl();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHeliosTriceMegistusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HELIOS_TRICE_MEGISTUS, 2);
  if (IsDuelOver() == TRUE)
    return TRUE;
  if (tribute != NULL)
    ClearZone(tribute);
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return FALSE;

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
  return TRUE;
}

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define HELIOS_TRICE_EP_STAT_STAGES 1 /* ~500; printed +500 */

struct HeliosTriceBdActionData {
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

extern struct HeliosTriceBdActionData sActionData;
static u8 sHeliosTricePending APPEND_DATA = {0};

static u8 TurnDuelistForFixedTrice(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

void ApplyHeliosTriceMegistusBattleDestroyPending(void)
{
  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.playerCardId == HELIOS_TRICE_MEGISTUS)
    sHeliosTricePending |= 1;
  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == HELIOS_TRICE_MEGISTUS)
    sHeliosTricePending |= 2;
}

void TryApplyHeliosTriceMegistusEndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 bit = fixed == DUEL_PLAYER ? 1 : 2;
  u8 turnDuelist;
  u8 monsterRow;
  struct DuelSummonOpts opts;
  struct DuelCard *zone;
  u8 col;

  if ((sHeliosTricePending & bit) == 0)
    return;
  sHeliosTricePending &= (u8)~bit;

  turnDuelist = TurnDuelistForFixedTrice(fixed);
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  Duel_ShowEffectTextTyped(HELIOS_TRICE_MEGISTUS, 2);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, HELIOS_TRICE_MEGISTUS, opts) != DUEL_ACTION_OK)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[monsterRow][col];
    if (zone != NULL && zone->id == HELIOS_TRICE_MEGISTUS) {
      if (zone->tempStage < 126)
        zone->tempStage += HELIOS_TRICE_EP_STAT_STAGES;
      break;
    }
  }
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
