#include "global.h"
#include "soul_exchange.h"
#include "tribute.h"

unsigned char GetKaiserSeaHorseTributeCount(u16 cardId);
void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);

u8 IsSoulExchangeActive(void)
{
  return gSoulExchangeActive != 0;
}

void ActivateSoulExchangeForTurn(void)
{
  gSoulExchangeActive = 1;
}

void ClearSoulExchange(void)
{
  gSoulExchangeActive = 0;
}

void ClearSoulExchangeTributeCredit(void)
{
  gSoulExchangeTributeCredit = 0;
}

void GrantSoulExchangeTributeCredit(void)
{
  gSoulExchangeTributeCredit = 1;
}

u8 CanActivateSoulExchange(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gFixedZones[OPPONENT_MONSTER_ROW][i]->id != CARD_NONE
        && !gFixedZones[OPPONENT_MONSTER_ROW][i]->isLocked)
      return TRUE;
  }

  return FALSE;
}

void ApplyMonsterTributeFromFixedRow(struct DuelCard *zone, u8 fixedMonsterRow)
{
  u8 wasSoulExchangeOpponent =
      IsSoulExchangeActive() && fixedMonsterRow == OPPONENT_MONSTER_ROW;
  u8 graveyardDuelist = DUEL_PLAYER;

  if (wasSoulExchangeOpponent)
    graveyardDuelist = DUEL_OPPONENT;

  if (wasSoulExchangeOpponent) {
    GrantSoulExchangeTributeCredit();
  } else {
    IncrementNumTributes();
    if (GetKaiserSeaHorseTributeCount(zone->id) == 2)
      IncrementNumTributes();
  }

  ClearZoneAndSendMonToGraveyard2(zone, graveyardDuelist);

  if (wasSoulExchangeOpponent)
    ClearSoulExchange();
}

void PerformSoulExchangeOpponentTribute(void)
{
  struct DuelCard *zone = gFixedZones[OPPONENT_MONSTER_ROW][gDuelCursor.currentX];

  if (!IsSoulExchangeActive() || zone->id == CARD_NONE || zone->isLocked) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  PlayMusic(SFX_TRIBUTE);
  ApplyMonsterTributeFromFixedRow(zone, OPPONENT_MONSTER_ROW);
  UpdateDuelGfxExceptField();
  TryActivatingPermanentEffects();
}
