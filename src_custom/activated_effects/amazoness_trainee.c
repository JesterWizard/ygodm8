#include "global.h"
#include "common-chax.h"
#include "amazoness_trainee.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void ClearZone(struct DuelCard *zone);
u8 GetDuelistForZone(struct DuelCard *zone);
void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct AmazonessTraineeActionData {
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

extern struct AmazonessTraineeActionData sActionData;

void ClearAmazonessTraineePending(void)
{
  gAmazonessTraineePendingDefenderRow = AMAZONESS_TRAINEE_PENDING_NONE;
  gAmazonessTraineePendingDefenderCol = 0;
  gAmazonessTraineePendingAttackerRow = AMAZONESS_TRAINEE_PENDING_NONE;
  gAmazonessTraineePendingAttackerCol = 0;
}

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

static u8 TryMarkTraineeDestroy(void)
{
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 3
      && sActionData.id != 5)
    return FALSE;

  if (sActionData.playerCardId == AMAZONESS_TRAINEE
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      && !(sActionData.flags & FLAG_GRAVEYARD_PLAYER)) {
    gAmazonessTraineePendingDefenderRow = sActionData.opponentMonsterRow;
    gAmazonessTraineePendingDefenderCol = sActionData.unk16;
    gAmazonessTraineePendingAttackerRow = sActionData.playerMonsterRow;
    gAmazonessTraineePendingAttackerCol = sActionData.unkA;
    sActionData.flags &= (u8)~FLAG_GRAVEYARD_OPPONENT;
    return TRUE;
  }

  if (sActionData.opponentCardId == AMAZONESS_TRAINEE
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER)
      && !(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)) {
    gAmazonessTraineePendingDefenderRow = sActionData.playerMonsterRow;
    gAmazonessTraineePendingDefenderCol = sActionData.unkA;
    gAmazonessTraineePendingAttackerRow = sActionData.opponentMonsterRow;
    gAmazonessTraineePendingAttackerCol = sActionData.unk16;
    sActionData.flags &= (u8)~FLAG_GRAVEYARD_PLAYER;
    return TRUE;
  }

  return FALSE;
}

void ApplyAmazonessTraineeBattleEffect(void)
{
  if (gHideEffectText)
    return;

  if (!TryMarkTraineeDestroy()) {
    ClearAmazonessTraineePending();
    return;
  }

  if (gUnk2023EA0.unk18 == 0)
    ResolveAmazonessTraineeBattleEffect();
}

void ResolveAmazonessTraineeBattleEffect(void)
{
  u8 defRow;
  u8 defCol;
  u8 atkRow;
  u8 atkCol;
  struct DuelCard *defender;
  struct DuelCard *attacker;

  defRow = gAmazonessTraineePendingDefenderRow;
  if (defRow == AMAZONESS_TRAINEE_PENDING_NONE)
    return;

  defCol = gAmazonessTraineePendingDefenderCol;
  atkRow = gAmazonessTraineePendingAttackerRow;
  atkCol = gAmazonessTraineePendingAttackerCol;
  ClearAmazonessTraineePending();

  defender = gFixedZones[defRow][defCol];
  attacker = gFixedZones[atkRow][atkCol];

  if (defender == NULL || defender->id == CARD_NONE
      || GetTypeGroup(defender->id) != TYPE_GROUP_MONSTER)
    return;

  Duel_ShowEffectTextTyped(AMAZONESS_TRAINEE, 3);
  if (IsDuelOver() == TRUE)
    return;

  if (!AppendCardToOwnerDeckBottom(defender))
    return;

  /* +200 ATK ≈ +1 tempStage (~500) — stage granularity ceiling. */
  if (attacker != NULL && attacker->id == AMAZONESS_TRAINEE
      && attacker->tempStage < 126)
    attacker->tempStage = (s8)(attacker->tempStage + 1);

  RefreshFieldMonsterStatOverlays();
  UpdateDuelGfxExceptField();
}

unsigned char CanActivateAMAZONESS_TRAINEE(void)
{
  if (gMonEffect.id != AMAZONESS_TRAINEE)
    return FALSE;

  /* Battle deck-bottom + ATK live via ApplyAmazonessTraineeBattleEffect. */
  return FALSE;
}

void ActivateAMAZONESS_TRAINEEEffect(void)
{
  Duel_ShowEffectTextTyped(AMAZONESS_TRAINEE, 2);
}
