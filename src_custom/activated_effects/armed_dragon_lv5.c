#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "god_card.h"
#include "monster_effect_usage.h"

#include "armed_dragon_lv5.h"

void ClearZoneAndSendMonToGraveyard(struct DuelCard *zone, u8 graveyardDuelist);
void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static u8 IsHandMonster(u16 cardId)
{
  return cardId != CARD_NONE && GetTypeGroup(cardId) == TYPE_GROUP_MONSTER;
}

static u8 HandHasMonster(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsHandMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsFaceUpMonsterZone(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static s8 PickHandMonsterZone(u16 *outAtk)
{
  u8 i;
  s8 bestZone = -1;
  u16 bestAtk = 0;

  if (WhoseTurn() == DUEL_PLAYER) {
    s8 zone = SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsHandMonster);

    if (zone < 0)
      return -1;

    *outAtk = gCardData_NEW[gTurnHands[ACTIVE_DUELIST][zone]->id].atk;
    return zone;
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][i]->id;
    u16 atk;

    if (!IsHandMonster(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (bestZone < 0 || atk > bestAtk) {
      bestAtk = atk;
      bestZone = (s8)i;
    }
  }

  if (bestZone < 0)
    return -1;

  *outAtk = bestAtk;
  return bestZone;
}

static u8 DestroyLowestOppMonsterAtOrBelowAtk(u16 atkLimit)
{
  u8 col;
  u8 bestCol = 0;
  u8 found = FALSE;
  u16 lowestAtk = 0xFFFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    atk = gCardData_NEW[zone->id].atk;
    if (atk > atkLimit)
      continue;

    if (!found || atk < lowestAtk) {
      found = TRUE;
      lowestAtk = atk;
      bestCol = col;
    }
  }

  if (!found)
    return FALSE;

  if (Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][bestCol], INACTIVE_DUELIST, TRUE)
      == DUEL_ACTION_DUEL_OVER)
    return FALSE;

  NotifyDynamicEquipFieldChanged();
  return TRUE;
}

unsigned char CanActivateARMED_DRAGON_LV5(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARMED_DRAGON_LV5)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_DRAGON_LV5)
    return FALSE;

  /* EP send self → SS LV7 via TryApplyArmedDragonLv5EndPhase when this card
   * destroyed a monster by battle. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasMonster();
}

void ActivateARMED_DRAGON_LV5Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 handZone;
  u16 discardedAtk;
  struct DuelCard *slot;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV5, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  handZone = PickHandMonsterZone(&discardedAtk);
  if (handZone < 0)
    return;

  slot = gTurnHands[ACTIVE_DUELIST][handZone];
  ClearZoneAndSendMonToGraveyard(slot, ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  DestroyLowestOppMonsterAtOrBelowAtk(discardedAtk);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ArmedDragonLv5ActionData {
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

extern struct ArmedDragonLv5ActionData sActionData;
static u8 sArmedDragonLv5Pending APPEND_DATA = {0};

static u8 HandHasArmedDragonLv7(u8 turnDuelist)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnHands[turnDuelist][col]->id == ARMED_DRAGON_LV7)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonLv7(u8 turnDuelist, u8 monsterRow)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  return HandHasArmedDragonLv7(turnDuelist)
      || Duel_FindDeckCardIndex(
             gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
                 ? DUEL_PLAYER
                 : DUEL_OPPONENT,
             ARMED_DRAGON_LV7) >= 0;
}

void ApplyArmedDragonLv5BattleDestroyPending(void)
{
  if (sActionData.playerCardId == ARMED_DRAGON_LV5
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
    sArmedDragonLv5Pending |= 1;

  if (sActionData.opponentCardId == ARMED_DRAGON_LV5
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    sArmedDragonLv5Pending |= 2;
}

void TryApplyArmedDragonLv5EndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 bit = fixed == DUEL_PLAYER ? 1 : 2;
  u8 turnDuelist;
  u8 monsterRow;
  u8 col;
  struct DuelCard *self = NULL;
  struct DuelSummonOpts opts;

  if ((sArmedDragonLv5Pending & bit) == 0)
    return;
  sArmedDragonLv5Pending &= (u8)~bit;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixed]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monsterRow][col];

    if (zone != NULL && zone->id == ARMED_DRAGON_LV5 && zone->isFaceUp) {
      self = zone;
      break;
    }
  }

  if (self == NULL || !CanSpecialSummonLv7(turnDuelist, monsterRow))
    return;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV5, 9);
  ClearZone(self);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (HandHasArmedDragonLv7(turnDuelist))
    Duel_SpecialSummonFromHand(turnDuelist, ARMED_DRAGON_LV7, NULL, opts);
  else
    Duel_SpecialSummonFromDeck(turnDuelist, ARMED_DRAGON_LV7, opts);

  UpdateDuelGfxExceptField();
}
