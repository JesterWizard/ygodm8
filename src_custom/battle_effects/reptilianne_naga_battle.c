#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "reptilianne_naga.h"

extern const CardData gCardData_NEW[];

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2

struct ReptilianneNagaActionData {
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

extern struct ReptilianneNagaActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static void ZeroZoneAtk(struct DuelCard *zone)
{
  u16 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  atk = gCardData_NEW[zone->id].atk;
  zone->tempStage = (s8)(-((s32)atk + 499) / 500);
}

static void TryZeroDefender(void)
{
  struct DuelCard *target;

  if (sActionData.id == 2 && sActionData.playerCardId == REPTILIANNE_NAGA) {
    target = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    ZeroZoneAtk(target);
  } else if (sActionData.id == 5 && sActionData.opponentCardId == REPTILIANNE_NAGA) {
    target = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    ZeroZoneAtk(target);
  }
}

void ApplyReptilianneNagaBattleZeroAtk(void)
{
  if (gHideEffectText)
    return;

  if (!IsMonsterBattleAction(sActionData.id))
    return;

  if (sActionData.id == 2 && sActionData.playerCardId == REPTILIANNE_NAGA) {
    if (sActionData.opponentCardId == CARD_NONE)
      return;
  } else if (sActionData.id == 5 && sActionData.opponentCardId == REPTILIANNE_NAGA) {
    if (sActionData.playerCardId == CARD_NONE)
      return;
  } else {
    return;
  }

  Duel_ShowEffectTextTyped(REPTILIANNE_NAGA, 2);
  TryZeroDefender();
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ReptilianneNagaBattle_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = BLUE_EYES_WHITE_DRAGON;
  zone.tempStage = 0;
  zone.tempStage = (s8)(-((s32)gCardData_NEW[zone.id].atk + 499) / 500);
  if (zone.tempStage >= 0)
    __builtin_trap();
}
#endif
