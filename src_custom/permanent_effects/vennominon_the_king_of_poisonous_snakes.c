#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "vennominon_the_king_of_poisonous_snakes.h"

#define VENNOMINON_ATK_PER_REPTILE 500

static u8 CountReptileInGraveyard(u8 fixedDuelist)
{
  u8 count = 0;
  u8 i;
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);

  for (i = 0; i < gyCount; i++) {
    if (Duel_CardHasMonsterType(GraveyardExpand_GetCardAt(fixedDuelist, i), TYPE_REPTILE))
      count++;
  }

  return count;
}

static u16 VennominonCurrentAtk(struct DuelCard *zone)
{
  u8 fixedDuelist = GetDuelistForZone(zone);
  u32 baseAtk;

  if (fixedDuelist == 0xFF)
    return gCardData_NEW[zone->id].atk;

  baseAtk = gCardData_NEW[zone->id].atk;
  return Duel_StatFromCount(
      CountReptileInGraveyard(fixedDuelist),
      VENNOMINON_ATK_PER_REPTILE,
      baseAtk);
}

u8 VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id != VENNOMINON_THE_KING_OF_POISONOUS_SNAKES)
    return FALSE;

  atk = VennominonCurrentAtk(zone);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, gCardData_NEW[zone->id].def);
  return TRUE;
}

unsigned char ShouldActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void)
{
  /* ATK overlay live; battle-destroy SS via ApplyVennominonBattleDestroySs. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateVENNOMINON_THE_KING_OF_POISONOUS_SNAKES(void)
{
}

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct VennominonActionData {
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

extern struct VennominonActionData sActionData;

void UpdateDuelGfxExceptField(void);

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static s8 FindOtherReptileGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    /* Legacy top is Vennominon itself after BD — no other reptile. */
    return -1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0; i--) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i - 1);

    if (cardId == VENNOMINON_THE_KING_OF_POISONOUS_SNAKES)
      continue;
    if (Duel_CardHasMonsterType(cardId, TYPE_REPTILE))
      return (s8)(i - 1);
  }
  return -1;
}

static void TryVennominonSs(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts;
  s8 gyIndex;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;
  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return;

  gyIndex = FindOtherReptileGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(VENNOMINON_THE_KING_OF_POISONOUS_SNAKES, 2);
  if (Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex) == CARD_NONE)
    return;
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  Duel_SpecialSummonFromGrave(turnDuelist, VENNOMINON_THE_KING_OF_POISONOUS_SNAKES, opts);
  UpdateDuelGfxExceptField();
}

void ApplyVennominonBattleDestroySs(void)
{
  /* After ClearZone — Vennominon is in GY. */
  if ((sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && sActionData.playerCardId == VENNOMINON_THE_KING_OF_POISONOUS_SNAKES) {
    TryVennominonSs(DUEL_PLAYER);
    return;
  }
  if ((sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && sActionData.opponentCardId == VENNOMINON_THE_KING_OF_POISONOUS_SNAKES)
    TryVennominonSs(DUEL_OPPONENT);
}

#if !defined(__GNUC__)
#error Vennominon stat hook self-check requires GCC
#elif __GNUC__
void VennominonTheKingOfPoisonousSnakes_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = VENNOMINON_THE_KING_OF_POISONOUS_SNAKES;
  VennominonTheKingOfPoisonousSnakes_ApplyDynamicZoneStats(&zone);
}
#endif
