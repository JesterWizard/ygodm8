#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "ehren_lightsworn_monk.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

#define EHREN_END_PHASE_MILL 3

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct EhrenActionData {
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

extern struct EhrenActionData sActionData;

static u8 AppendCardToOwnerDeckBottom(struct DuelCard *zone)
{
  u8 fixedDuelist;
  u8 deckSize;
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  fixedDuelist = GetDuelistForZone(zone);
  if (fixedDuelist == 0xFF)
    return FALSE;

  cardId = zone->id;
  deckSize = NumCardsInDeck(fixedDuelist);
  if (deckSize >= 60)
    return FALSE;

  gDuelDecks[fixedDuelist].cards[deckSize] = cardId;
  ClearZone(zone);
  return TRUE;
}

void ApplyEhrenLightswornMonkBeforeDamageCalc(void)
{
  struct DuelCard *attacker;
  struct DuelCard *defender;
  u8 atkRow;
  u8 atkCol;
  u8 defRow;
  u8 defCol;

  if (sActionData.id != 2 && sActionData.id != 5)
    return;

  if (sActionData.id == 2) {
    if (sActionData.playerCardId != EHREN_LIGHTSWORN_MONK)
      return;
    atkRow = sActionData.playerMonsterRow;
    atkCol = sActionData.unkA;
    defRow = sActionData.opponentMonsterRow;
    defCol = sActionData.unk16;
  } else {
    if (sActionData.opponentCardId != EHREN_LIGHTSWORN_MONK)
      return;
    atkRow = sActionData.opponentMonsterRow;
    atkCol = sActionData.unk16;
    defRow = sActionData.playerMonsterRow;
    defCol = sActionData.unkA;
  }

  defender = gFixedZones[defRow][defCol];
  if (defender == NULL || defender->id == CARD_NONE || !defender->isDefending)
    return;

  attacker = gFixedZones[atkRow][atkCol];
  if (attacker == NULL || attacker->id != EHREN_LIGHTSWORN_MONK)
    return;

  if (!AppendCardToOwnerDeckBottom(defender))
    return;

  Duel_ShowEffectTextTyped(EHREN_LIGHTSWORN_MONK, 2);
  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();

  if (sActionData.id == 2) {
    sActionData.opponentCardId = CARD_NONE;
    sActionData.opponentCardAtkOrLifePointsMod = 0;
    sActionData.opponentCardDefense = 0;
  } else {
    sActionData.playerCardId = CARD_NONE;
    sActionData.playerCardAtkOrLifePointsMod = 0;
    sActionData.playerCardDefense = 0;
  }

  sActionData.flags &= (u8)~(FLAG_GRAVEYARD_PLAYER | FLAG_GRAVEYARD_OPPONENT);
}

void TryApplyEhrenEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != EHREN_LIGHTSWORN_MONK)
      continue;
    Duel_ShowEffectTextTyped(EHREN_LIGHTSWORN_MONK, 2);
    Duel_MillTopDeckCards(turn, EHREN_END_PHASE_MILL, TRUE);
    return;
  }
}

unsigned char CanActivateEHREN_LIGHTSWORN_MONK(void)
{
  if (gMonEffect.id != EHREN_LIGHTSWORN_MONK)
    return FALSE;

  /* DEF shuffle via ApplyEhrenLightswornMonkBeforeDamageCalc; EP mill via TryApplyEhrenEndPhase. */
  return FALSE;
}

void ActivateEHREN_LIGHTSWORN_MONKEffect(void)
{
  Duel_ShowEffectTextTyped(EHREN_LIGHTSWORN_MONK, 2);
}
