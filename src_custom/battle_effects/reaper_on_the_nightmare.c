#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "reaper_on_the_nightmare.h"

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ReaperOnTheNightmareActionData {
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

extern struct ReaperOnTheNightmareActionData sActionData;

void ClearReaperDiscardPending(void) {
  gPendingReaperDiscardDuelist = REAPER_DISCARD_PENDING_NONE;
}

static u8 CountCardsInDuelistHand(u8 duelist) {
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++)
    if (gDuel.hands[duelist][i].id != CARD_NONE)
      count++;

  return count;
}

static u8 PickRandomHandZone(u8 duelist) {
  u8 i;
  u8 occupied = CountCardsInDuelistHand(duelist);
  u8 chosen;
  u8 seen = 0;

  if (occupied == 0)
    return 0xFF;

  chosen = RandRangeU8(0, occupied - 1);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[duelist][i].id == CARD_NONE)
      continue;

    if (seen == chosen)
      return i;

    seen++;
  }

  return 0xFF;
}

static void DiscardRandomHandCard(u8 duelist) {
  u8 zone = PickRandomHandZone(duelist);

  if (zone == 0xFF)
    return;

  ClearZoneAndSendMonToGraveyard(&gDuel.hands[duelist][zone], duelist);
}

void ApplyReaperOnTheNightmareBattleProtection(void) {
  if (sActionData.playerCardId == REAPER_ON_THE_NIGHTMARE
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    sActionData.flags &= ~FLAG_GRAVEYARD_PLAYER;

  if (sActionData.opponentCardId == REAPER_ON_THE_NIGHTMARE
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
    sActionData.flags &= ~FLAG_GRAVEYARD_OPPONENT;

  if (sActionData.playerCardId == SPIRIT_REAPER
      && (sActionData.flags & FLAG_GRAVEYARD_PLAYER))
    sActionData.flags &= ~FLAG_GRAVEYARD_PLAYER;

  if (sActionData.opponentCardId == SPIRIT_REAPER
      && (sActionData.flags & FLAG_GRAVEYARD_OPPONENT))
    sActionData.flags &= ~FLAG_GRAVEYARD_OPPONENT;
}

void ApplyReaperOnTheNightmareDirectDamageEffect(void) {
  u8 damagedDuelist;
  u16 damage;

  if (gHideEffectText)
    return;

  if (sActionData.id == 4 && sActionData.playerCardId == REAPER_ON_THE_NIGHTMARE) {
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
    damagedDuelist = DUEL_OPPONENT;
  } else if (sActionData.id == 6 && sActionData.opponentCardId == REAPER_ON_THE_NIGHTMARE) {
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
    damagedDuelist = DUEL_PLAYER;
  } else {
    return;
  }

  if (damage == 0 || CountCardsInDuelistHand(damagedDuelist) == 0)
    return;

  gPendingReaperDiscardDuelist = damagedDuelist;

  /* Attacks without a battle animation resolve immediately (e.g. some AI paths). */
  if (gUnk2023EA0.unk18 == 0)
    ResolveReaperOnTheNightmareDirectDamageEffect();
}

void ResolveReaperOnTheNightmareDirectDamageEffect(void) {
  u8 damagedDuelist;

  damagedDuelist = gPendingReaperDiscardDuelist;
  if (damagedDuelist == REAPER_DISCARD_PENDING_NONE)
    return;

  gPendingReaperDiscardDuelist = REAPER_DISCARD_PENDING_NONE;

  if (CountCardsInDuelistHand(damagedDuelist) == 0)
    return;

  Duel_ShowEffectTextTyped(REAPER_ON_THE_NIGHTMARE, 3);
  DiscardRandomHandCard(damagedDuelist);
}
