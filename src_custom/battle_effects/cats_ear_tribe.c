#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/duel_fields.h"
#include "custom_field_spell.h"

extern u8 gUnk8094FE4[NUM_FIELDS][NUM_CARD_TYPES];

struct CatsEarTribeActionData {
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

extern struct CatsEarTribeActionData sActionData;

static u8 IsMonsterAttackAction(void)
{
  return sActionData.id == 1 || sActionData.id == 2 || sActionData.id == 4
      || sActionData.id == 5 || sActionData.id == 6;
}

static u16 ComputeAtkWith200Base(struct DuelCard *zone, u16 cardId)
{
  u8 fieldMod;
  s8 stage;
  u32 finalAtk;
  u8 percent;

  stage = GetFinalStage(zone);
  SetCardInfo(cardId);
#if NUM_CUSTOM_FIELDS > 0
  if (IsCustomField(gDuel.field))
    fieldMod = gCustomFieldStatMods[gDuel.field - FIRST_CUSTOM_FIELD][gCardInfo.type];
  else
#endif
    fieldMod = gUnk8094FE4[gDuel.field][gCardInfo.type];
  percent = gRuntimeConfig.field_stat_change_percent;

  /* Apply field modifier on base 200 */
  finalAtk = 200;
  switch (fieldMod) {
    case 0:
    case 2:
    case 4:
      break;
    case 1:
      finalAtk = 200 * (100 - percent) / 100;
      break;
    case 3:
      finalAtk = 200 * (100 + percent) / 100;
      break;
  }

  /* Apply stage modifier (stage * 500) */
  finalAtk = (u32)(stage * 500) + finalAtk;

  if (finalAtk <= 0)
    return 0;
  if (finalAtk > 0xFFFE)
    return 0xFFFE;

  return (u16)finalAtk;
}

void TryApplyCatsEarTribeToPendingAction(void)
{
  if (!IsMonsterAttackAction())
    return;

  if (sActionData.playerCardId == CATS_EAR_TRIBE) {
    struct DuelCard *zone;

    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
    if (zone->id != CARD_NONE)
      sActionData.opponentCardAtkOrLifePointsMod =
          ComputeAtkWith200Base(zone, sActionData.opponentCardId);
  }

  if (sActionData.opponentCardId == CATS_EAR_TRIBE) {
    struct DuelCard *zone;

    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
    if (zone->id != CARD_NONE)
      sActionData.playerCardAtkOrLifePointsMod =
          ComputeAtkWith200Base(zone, sActionData.playerCardId);
  }
}
