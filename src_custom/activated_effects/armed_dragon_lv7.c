#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "armed_dragon_lv7.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "exchange_hand_selection.h"
#include "god_card.h"
#include "monster_effect_usage.h"

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

static u8 OppHasMonsterAtOrBelowAtk(u16 atkLimit)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    if (gCardData_NEW[zone->id].atk <= atkLimit)
      return TRUE;
  }

  return FALSE;
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

static void DestroyOpponentMonstersAtOrBelowAtk(u16 atkLimit)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (!IsFaceUpMonsterZone(zone))
      continue;

    if (gCardData_NEW[zone->id].atk > atkLimit)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }

  NotifyDynamicEquipFieldChanged();
}

unsigned char CanActivateARMED_DRAGON_LV7(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != ARMED_DRAGON_LV7)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_DRAGON_LV7)
    return FALSE;

  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return HandHasMonster();
}

void ActivateARMED_DRAGON_LV7Effect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  s8 handZone;
  u16 discardedAtk;
  struct DuelCard *slot;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV7, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  handZone = PickHandMonsterZone(&discardedAtk);
  if (handZone < 0)
    return;

  slot = gTurnHands[ACTIVE_DUELIST][handZone];
  ClearZoneAndSendMonToGraveyard(slot, ACTIVE_DUELIST);

  if (IsDuelOver() == TRUE)
    return;

  if (OppHasMonsterAtOrBelowAtk(discardedAtk))
    DestroyOpponentMonstersAtOrBelowAtk(discardedAtk);

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ArmedDragonLv7ActionData {
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

extern struct ArmedDragonLv7ActionData sActionData;
static u8 sArmedDragonLv7Pending APPEND_DATA = {0};

static u8 HandHasArmedDragonLv10(u8 turnDuelist)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (gTurnHands[turnDuelist][col]->id == ARMED_DRAGON_LV10)
      return TRUE;
  }

  return FALSE;
}

static u8 CanSpecialSummonLv10(u8 turnDuelist, u8 monsterRow)
{
  u8 fixedDuelist;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[monsterRow]) < 0)
    return FALSE;

  fixedDuelist = gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER]
      ? DUEL_PLAYER
      : DUEL_OPPONENT;

  return HandHasArmedDragonLv10(turnDuelist)
      || Duel_FindDeckCardIndex(fixedDuelist, ARMED_DRAGON_LV10) >= 0;
}

void ApplyArmedDragonLv7BattleDestroyPending(void)
{
  if (sActionData.playerCardId == ARMED_DRAGON_LV7
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
    sArmedDragonLv7Pending |= 1;

  if (sActionData.opponentCardId == ARMED_DRAGON_LV7
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    sArmedDragonLv7Pending |= 2;
}

void TryApplyArmedDragonLv7EndPhase(void)
{
  u8 fixed = WhoseTurn() == DUEL_PLAYER ? DUEL_PLAYER : DUEL_OPPONENT;
  u8 bit = fixed == DUEL_PLAYER ? 1 : 2;
  u8 turnDuelist;
  u8 monsterRow;
  u8 col;
  struct DuelCard *self = NULL;
  struct DuelSummonOpts opts;

  if ((sArmedDragonLv7Pending & bit) == 0)
    return;
  sArmedDragonLv7Pending &= (u8)~bit;

  turnDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixed]
      ? ACTIVE_DUELIST
      : INACTIVE_DUELIST;
  monsterRow = turnDuelist == ACTIVE_DUELIST
      ? ACTIVE_DUELIST_MONSTER_ROW
      : INACTIVE_DUELIST_MONSTER_ROW;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[monsterRow][col];

    if (zone != NULL && zone->id == ARMED_DRAGON_LV7 && zone->isFaceUp) {
      self = zone;
      break;
    }
  }

  if (self == NULL || !CanSpecialSummonLv10(turnDuelist, monsterRow))
    return;

  Duel_ShowEffectTextTyped(ARMED_DRAGON_LV7, 9);
  ClearZone(self);
  if (IsDuelOver() == TRUE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (HandHasArmedDragonLv10(turnDuelist))
    Duel_SpecialSummonFromHand(turnDuelist, ARMED_DRAGON_LV10, NULL, opts);
  else
    Duel_SpecialSummonFromDeck(turnDuelist, ARMED_DRAGON_LV10, opts);

  UpdateDuelGfxExceptField();
}
