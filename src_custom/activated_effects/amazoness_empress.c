#include "global.h"
#include "common-chax.h"
#include "amazoness_empress.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define FLAG_LOSER_PLAYER 4
#define FLAG_LOSER_OPPONENT 16

struct AmazonessEmpressActionData {
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

extern struct AmazonessEmpressActionData sActionData;

static u8 sEmpressInit APPEND_DATA = {0};

static u8 ControllerHasFaceUpEmpress(u8 controller)
{
  u8 row = Duel_FixedMonsterRowForDuelist(controller);
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AMAZONESS_EMPRESS)
      return TRUE;
  }

  return FALSE;
}

static void ApplyPiercingDamageToOpponent(u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_OPPONENT] <= damage) {
    gDuelLifePoints[DUEL_OPPONENT] = 0;
    sActionData.flags |= FLAG_LOSER_OPPONENT;
  } else {
    gDuelLifePoints[DUEL_OPPONENT] -= damage;
  }

  gUnk2023EA0.unk0[1].lifePointsAfterDamage = gDuelLifePoints[DUEL_OPPONENT];
  sActionData.opponentLifePoints = gDuelLifePoints[DUEL_OPPONENT];
}

static void ApplyPiercingDamageToPlayer(u16 damage)
{
  if (damage == 0)
    return;

  if (gDuelLifePoints[DUEL_PLAYER] <= damage) {
    gDuelLifePoints[DUEL_PLAYER] = 0;
    sActionData.flags |= FLAG_LOSER_PLAYER;
  } else {
    gDuelLifePoints[DUEL_PLAYER] -= damage;
  }

  gUnk2023EA0.unk0[0].lifePointsAfterDamage = gDuelLifePoints[DUEL_PLAYER];
  sActionData.playerLifePoints = gDuelLifePoints[DUEL_PLAYER];
}

void ApplyAmazonessEmpressPiercingBattleEffect(void)
{
  u16 attackerAtk;
  u16 defenderDef;
  u16 damage;

  /* Player Amazoness attacks DEF (id 2). */
  if (sActionData.id == 2 && Duel_IsAmazonessCard(sActionData.playerCardId)
      && ControllerHasFaceUpEmpress(DUEL_PLAYER)
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    attackerAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderDef = sActionData.opponentCardDefense;
    if (attackerAtk > defenderDef) {
      damage = attackerAtk - defenderDef;
      ApplyPiercingDamageToOpponent(damage);
    }
    return;
  }

  /* Opponent Amazoness attacks DEF (id 5). */
  if (sActionData.id == 5 && Duel_IsAmazonessCard(sActionData.opponentCardId)
      && ControllerHasFaceUpEmpress(DUEL_OPPONENT)
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    attackerAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderDef = sActionData.playerCardDefense;
    if (attackerAtk > defenderDef) {
      damage = attackerAtk - defenderDef;
      ApplyPiercingDamageToPlayer(damage);
    }
  }
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST]
      == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;

  return INACTIVE_DUELIST;
}

static u8 CanSpecialSummonQueen(u8 turnDuelist)
{
  u8 monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[monsterRow]) >= 0;
}

static u8 TrySsQueenFromHand(u8 turnDuelist)
{
  u8 col;
  struct DuelSummonOpts opts;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *slot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], col);

    if (slot == NULL || slot->id != AMAZONESS_QUEEN)
      continue;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    return Duel_SpecialSummonFromHandZone(turnDuelist, col, opts) == DUEL_ACTION_OK;
  }

  return FALSE;
}

static u8 TrySsQueenFromDeck(u8 turnDuelist)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (Duel_FindDeckCardIndex(turnDuelist, AMAZONESS_QUEEN) < 0)
    return FALSE;

  return Duel_SpecialSummonFromDeck(turnDuelist, AMAZONESS_QUEEN, opts) == DUEL_ACTION_OK;
}

static u8 TrySsQueenFromGy(u8 fixedDuelist, u8 turnDuelist)
{
  s16 gyIndex = -1;
  u16 cardId;
  struct DuelSummonOpts opts;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard != AMAZONESS_QUEEN)
      return FALSE;
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    u8 i;

    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (GraveyardExpand_GetCardAt(fixedDuelist, i) == AMAZONESS_QUEEN) {
        gyIndex = (s16)i;
        break;
      }
    }
    if (gyIndex < 0)
      return FALSE;
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  if (cardId != AMAZONESS_QUEEN)
    return FALSE;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  return Duel_SpecialSummonMonsterId(turnDuelist, cardId, opts) == DUEL_ACTION_OK;
}

static void TrySpecialSummonAmazonessQueen(u8 fixedDuelist)
{
  u8 turnDuelist = TurnDuelistForFixed(fixedDuelist);

  if (!CanSpecialSummonQueen(turnDuelist))
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_EMPRESS, 2);
  if (IsDuelOver() == TRUE)
    return;

  if (TrySsQueenFromHand(turnDuelist)
      || TrySsQueenFromDeck(turnDuelist)
      || TrySsQueenFromGy(fixedDuelist, turnDuelist)) {
    UpdateDuelGfxExceptField();
    CheckWinConditionExodia(WhoseTurn());
    if (IsDuelOver() != TRUE)
      TryActivatingPermanentEffects();
  }
}

static void OnEmpressLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != AMAZONESS_EMPRESS)
    return;

  if (ev->controller != DUEL_PLAYER && ev->controller != DUEL_OPPONENT)
    return;

  TrySpecialSummonAmazonessQueen(ev->controller);
}

void AmazonessEmpress_EnsureInit(void)
{
  if (sEmpressInit)
    return;

  sEmpressInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnEmpressLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnEmpressLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_DESTROY, OnEmpressLeaveField);
}

unsigned char CanActivateAMAZONESS_EMPRESS(void)
{
  if (gMonEffect.id != AMAZONESS_EMPRESS)
    return FALSE;

  /* Battle protect via AmazonessQueen_PreventsBattleDestroy.
   * Leave-field SS Queen via AmazonessEmpress_EnsureInit.
   * Pierce via ApplyAmazonessEmpressPiercingBattleEffect. */
  return FALSE;
}

void ActivateAMAZONESS_EMPRESSEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_EMPRESS, 2);
}
