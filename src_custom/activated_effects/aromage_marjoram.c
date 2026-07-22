#include "global.h"
#include "common-chax.h"
#include "aromage_marjoram.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct AromageMarjoramActionData {
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

extern struct AromageMarjoramActionData sActionData;

static const char sAromaName[] APPEND_RODATA = "Aroma";

static struct DuelCard *FindFaceUpMarjoram(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMAGE_MARJORAM)
      return zone;
  }

  return NULL;
}

static u8 ControllerLpHigher(u8 controller)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  return gDuelLifePoints[controller] > gDuelLifePoints[opp];
}

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

void ApplyAromageMarjoramNoPlantBattleDamage(void)
{
  u16 playerDamage;
  u16 opponentDamage;

  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4
      && sActionData.id != 5 && sActionData.id != 6)
    return;

  playerDamage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  opponentDamage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];

  if (playerDamage > 0 && FindFaceUpMarjoram(DUEL_PLAYER) != NULL
      && ControllerLpHigher(DUEL_PLAYER)
      && Duel_CardHasMonsterType(sActionData.playerCardId, TYPE_PLANT)) {
    gDuelLifePoints[DUEL_PLAYER] = gUnk2023EA0.unk0[0].initialLifePoints;
    gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
    sActionData.flags &= (u8)~FLAG_LOSER_PLAYER;
  }

  if (opponentDamage > 0 && FindFaceUpMarjoram(DUEL_OPPONENT) != NULL
      && ControllerLpHigher(DUEL_OPPONENT)
      && Duel_CardHasMonsterType(sActionData.opponentCardId, TYPE_PLANT)) {
    gDuelLifePoints[DUEL_OPPONENT] = gUnk2023EA0.unk0[1].initialLifePoints;
    gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
    sActionData.flags &= (u8)~FLAG_LOSER_OPPONENT;
  }

  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 CountAromaOnField(void)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && IsAromaMonster(zone->id))
      count++;
  }

  return count;
}

static u8 OppGyCardCount(void)
{
  u8 fixedDuelist = FixedDuelistForActive() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;

  if (!GraveyardExpand_IsEnabled()) {
    return gDuel.duelistbattleState[fixedDuelist].graveyard != CARD_NONE ? 1 : 0;
  }

  return GraveyardExpand_GetCount(fixedDuelist);
}

static u8 BanishUpToNFromOppGy(u8 max)
{
  u8 fixedDuelist = FixedDuelistForActive() == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 banished = 0;
  u8 i;

  if (max == 0)
    return 0;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == CARD_NONE)
      return 0;

    Duel_BanishGraveyardTopTurn(INACTIVE_DUELIST);
    return 1;
  }

  for (i = GraveyardExpand_GetCount(fixedDuelist); i > 0 && banished < max; i--) {
    if (Duel_BanishGraveyardAtFixed(fixedDuelist, i - 1) == CARD_NONE)
      break;

    banished++;
  }

  if (banished > 0)
    GraveyardExpand_RefreshDisplay();

  return banished;
}

unsigned char CanActivateAROMAGE_MARJORAM(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMAGE_MARJORAM)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMAGE_MARJORAM)
    return FALSE;

  /* LP-higher Plant no battle damage via ApplyAromageMarjoramNoPlantBattleDamage.
   * Ceiling: destroy-SS + LP-gain trigger need destroy/LP hooks. Ceiling: OPT banish opp GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return CountAromaOnField() > 0 && OppGyCardCount() > 0;
}

void ActivateAROMAGE_MARJORAMEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 max;

  Duel_ShowEffectTextTyped(AROMAGE_MARJORAM, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  max = CountAromaOnField();
  if (max == 0)
    return;

  if (BanishUpToNFromOppGy(max) == 0)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
