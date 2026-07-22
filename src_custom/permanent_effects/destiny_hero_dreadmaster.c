#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_dreadmaster.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct DestinyHeroDreadmasterActionData {
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

extern struct DestinyHeroDreadmasterActionData sActionData;

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

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

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 FixedDuelistHasFaceUpDreadmaster(u8 fixedDuelist)
{
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_DREADMASTER)
      return TRUE;
  }

  return FALSE;
}

static u8 IsControllerDestinyHeroInBattle(u8 fixedDuelist)
{
  if (fixedDuelist == DUEL_PLAYER)
    return IsDestinyHeroMonster(sActionData.playerCardId);

  return IsDestinyHeroMonster(sActionData.opponentCardId);
}

u8 DestinyHeroDreadmaster_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 fixedCol;
  u8 fixedDuelist;

  if (zone == NULL || !IsDestinyHeroMonster(zone->id))
    return FALSE;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &fixedCol))
    return FALSE;

  fixedDuelist = Duel_FixedDuelistForMonsterRow(fixedRow);
  return FixedDuelistHasFaceUpDreadmaster(fixedDuelist);
}

void ApplyDestinyHeroDreadmasterNoBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (FixedDuelistHasFaceUpDreadmaster(DUEL_PLAYER)
      && IsControllerDestinyHeroInBattle(DUEL_PLAYER)
      && playerDamage > 0) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
  }

  if (FixedDuelistHasFaceUpDreadmaster(DUEL_OPPONENT)
      && IsControllerDestinyHeroInBattle(DUEL_OPPONENT)
      && opponentDamage > 0) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static u8 OwnMonsterRowHasNonDestinyHero(struct DuelCard *self, u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone == self || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (!IsDestinyHeroMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 GraveyardHasDestinyHero(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    return IsDestinyHeroMonster(top);
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsDestinyHeroMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonDestinyHeroesFromGrave(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return GraveyardHasDestinyHero(turnDuelist);
}

static void DestroyOwnNonDestinyHeroMonsters(struct DuelCard *self, u8 turnDuelist)
{
  u8 col;
  u8 destroyed = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][col];

    if (zone == self || zone->id == CARD_NONE)
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (IsDestinyHeroMonster(zone->id))
      continue;

    if (Duel_DestroyZone(zone, turnDuelist, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;

    destroyed = TRUE;
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

static u16 FindDestinyHeroInGraveyard(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsDestinyHeroMonster(top))
      return top;
    return CARD_NONE;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (IsDestinyHeroMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static u8 SpecialSummonUpToTwoDestinyHeroesFromGrave(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 summoned = 0;
  u16 cardId;

  while (summoned < 2 && FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0) {
    cardId = FindDestinyHeroInGraveyard(fixedDuelist);
    if (cardId == CARD_NONE)
      break;

    if (Duel_SpecialSummonFromGrave(turnDuelist, cardId, opts) != DUEL_ACTION_OK)
      break;

    summoned++;
  }

  return summoned > 0;
}

unsigned char ShouldActivateDESTINY_HERO_DREADMASTER(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != DESTINY_HERO_DREADMASTER)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  /* Ceiling: Clock Tower Prison gate skipped; on-summon destroy/SS stand-in.
   * D-HERO battle protect + no BD via DestinyHeroDreadmaster_* while face-up. */
  return OwnMonsterRowHasNonDestinyHero(zone, gActiveEffect.turnRow)
      || CanSpecialSummonDestinyHeroesFromGrave(duelist);
}

void ActivateDESTINY_HERO_DREADMASTER(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  zone = SelfZone();

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREADMASTER, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (zone != NULL)
    DestroyOwnNonDestinyHeroMonsters(zone, duelist);
  if (IsDuelOver() == TRUE)
    return;

  SpecialSummonUpToTwoDestinyHeroesFromGrave(duelist);

  if (zone != NULL)
    zone->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
