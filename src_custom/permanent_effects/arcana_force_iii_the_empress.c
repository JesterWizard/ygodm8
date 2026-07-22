#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "six_card_hand.h"

#define ARCANA_FORCE_III_THE_EMPRESS_COIN_HEADS 1
#define ARCANA_FORCE_III_THE_EMPRESS_COIN_TAILS 2

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
u8 GetDuelistForZone(struct DuelCard *zone);

static const char sArcanaForceName[] APPEND_RODATA = "Arcana Force";

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  return gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist]
             ? ACTIVE_DUELIST
             : INACTIVE_DUELIST;
}

static u8 IsNormalSummonMode(enum DuelSummonMode mode)
{
  return mode == DUEL_SUMMON_NORMAL_FACE_UP_ATK || mode == DUEL_SUMMON_NORMAL_SET;
}

static u8 IsArcanaForceMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sArcanaForceName);
}

static s8 FindArcanaForceHandZone(u8 turnDuelist)
{
  u8 i;
  u8 max = IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW;

  for (i = 0; i < max; i++) {
    u16 cardId = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], i)->id;

    if (IsArcanaForceMonster(cardId))
      return (s8)i;
  }

  return -1;
}

static struct DuelCard *FindOppEmpress(u8 summonerFixed)
{
  u8 monRow = summonerFixed == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[monRow][col];

    if (zone == NULL || zone->id != ARCANA_FORCE_III_THE_EMPRESS)
      continue;

    if (zone->unk4 == 0)
      continue;

    if (!IsCardFaceUp(zone) && zone->isDefending)
      continue;

    return zone;
  }

  return NULL;
}

unsigned char ShouldActivateARCANA_FORCE_III_THE_EMPRESS(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != ARCANA_FORCE_III_THE_EMPRESS)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  return TRUE;
}

void ActivateARCANA_FORCE_III_THE_EMPRESS(void)
{
  struct DuelCard *zone;
  u8 heads;

  Duel_ShowEffectTextTyped(ARCANA_FORCE_III_THE_EMPRESS, 8);
  if (IsDuelOver() == TRUE)
    return;

  zone = SelfZone();
  if (zone == NULL)
    return;

  heads = RandRangeU8(0, 1) == 1;
  zone->unk4 = heads ? ARCANA_FORCE_III_THE_EMPRESS_COIN_HEADS
                     : ARCANA_FORCE_III_THE_EMPRESS_COIN_TAILS;
}

/* Opp Normal Summon: Heads SS Arcana Force from hand; Tails opp discards 1. */
void TryArcanaForceIiiTheEmpressOnOppNormalSummon(struct DuelCard *zone,
                                                  enum DuelSummonMode mode)
{
  struct DuelCard *empress;
  u8 summonerFixed;
  u8 empressFixed;
  u8 empressTurn;
  u8 summonerTurn;
  s8 handZone;
  struct DuelSummonOpts opts;

  if (zone == NULL || zone->id == CARD_NONE || !IsNormalSummonMode(mode))
    return;

  if (gHideEffectText)
    return;

  summonerFixed = GetDuelistForZone(zone);
  if (summonerFixed > DUEL_OPPONENT)
    return;

  empress = FindOppEmpress(summonerFixed);
  if (empress == NULL)
    return;

  empressFixed = GetDuelistForZone(empress);
  if (empressFixed > DUEL_OPPONENT)
    return;

  empressTurn = TurnDuelistForFixed(empressFixed);
  summonerTurn = TurnDuelistForFixed(summonerFixed);

  Duel_ShowEffectTextTyped(ARCANA_FORCE_III_THE_EMPRESS, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (empress->unk4 == ARCANA_FORCE_III_THE_EMPRESS_COIN_HEADS) {
    if (ArchlordKristya_IsSpecialSummonLocked())
      return;

    handZone = FindArcanaForceHandZone(empressTurn);
    if (handZone < 0)
      return;

    if (FirstEmptyZoneInRow(gTurnZones[empressTurn == ACTIVE_DUELIST
                                          ? ACTIVE_DUELIST_MONSTER_ROW
                                          : INACTIVE_DUELIST_MONSTER_ROW])
        < 0)
      return;

    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    if (Duel_SpecialSummonFromHandZone(empressTurn, (u8)handZone, opts) != DUEL_ACTION_OK)
      return;
  } else if (empress->unk4 == ARCANA_FORCE_III_THE_EMPRESS_COIN_TAILS) {
    if (Duel_CountCardsInHand(gTurnHands[summonerTurn]) == 0)
      return;

    if (Duel_DiscardRandomFromHand(summonerTurn, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
      return;
  } else {
    return;
  }

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
