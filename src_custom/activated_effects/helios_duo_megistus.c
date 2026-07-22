#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"
#include "helios_duo_megistus.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void RefreshFieldMonsterStatOverlays(void);

#define HELIOS_DUO_STAT_PER_BANISHED 200

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

u8 HeliosDuoMegistus_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 stat;

  if (zone == NULL || zone->id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  stat = Duel_StatFromCount(CountBanishedMonsters(), HELIOS_DUO_STAT_PER_BANISHED, 0);
  Duel_WriteCardInfoStats(zone->id, stat, stat);
  return TRUE;
}

static struct DuelCard *FindHeliosThePrimordialSunYouControl(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == HELIOS_THE_PRIMORDIAL_SUN)
      return zone;
  }

  return NULL;
}

unsigned char CanActivateHELIOS_DUO_MEGISTUS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  /* Continuous ATK/DEF via HeliosDuoMegistus_ApplyDynamicZoneStats.
   * Battle-destroy EP SS via ApplyHeliosDuoMegistusBattleDestroyPending. */
  return FALSE;
}

void ActivateHELIOS_DUO_MEGISTUSEffect(void)
{
  Duel_ShowEffectTextTyped(HELIOS_DUO_MEGISTUS, 2);
}

u8 CanSpecialSummonHeliosDuoMegistusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != HELIOS_DUO_MEGISTUS)
    return FALSE;

  if (FindHeliosThePrimordialSunYouControl() == NULL)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

u8 TrySpecialSummonHeliosDuoMegistusFromHand(u8 handZone)
{
  struct DuelCard *tribute = FindHeliosThePrimordialSunYouControl();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (!CanSpecialSummonHeliosDuoMegistusFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(HELIOS_DUO_MEGISTUS, 2);

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

#if !defined(__GNUC__)
u8 CanSpecialSummonHeliosDuoMegistusFromHand(u8 handZone);
u8 TrySpecialSummonHeliosDuoMegistusFromHand(u8 handZone);
#endif

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define HELIOS_DUO_EP_STAT_STAGES 1 /* ~500; printed +300 */

struct HeliosDuoBdActionData {
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

extern struct HeliosDuoBdActionData sActionData;
static u8 sHeliosDuoPending APPEND_DATA = {0};

static u8 TurnDuelistForFixedDuo(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

void ApplyHeliosDuoMegistusBattleDestroyPending(void)
{
  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.playerCardId == HELIOS_DUO_MEGISTUS)
    sHeliosDuoPending |= 1;
  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == HELIOS_DUO_MEGISTUS)
    sHeliosDuoPending |= 2;
}

void TryApplyHeliosDuoMegistusEndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 bit = fixed == DUEL_PLAYER ? 1 : 2;
  u8 turnDuelist;
  u8 monsterRow;
  struct DuelSummonOpts opts;
  struct DuelCard *zone;
  u8 col;

  if ((sHeliosDuoPending & bit) == 0)
    return;
  sHeliosDuoPending &= (u8)~bit;

  turnDuelist = TurnDuelistForFixedDuo(fixed);
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  Duel_ShowEffectTextTyped(HELIOS_DUO_MEGISTUS, 2);
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromGrave(turnDuelist, HELIOS_DUO_MEGISTUS, opts) != DUEL_ACTION_OK)
    return;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    zone = gTurnZones[monsterRow][col];
    if (zone != NULL && zone->id == HELIOS_DUO_MEGISTUS) {
      if (zone->tempStage < 126)
        zone->tempStage += HELIOS_DUO_EP_STAT_STAGES;
      break;
    }
  }
  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}
