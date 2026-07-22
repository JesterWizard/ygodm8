#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "jain_lightsworn_paladin.h"

#define JAIN_DAMAGE_STEP_ATK 300
#define JAIN_END_PHASE_MILL 2

struct JainActionData {
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

extern struct JainActionData sActionData;

static u8 IsJainAttackingMonster(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != JAIN_LIGHTSWORN_PALADIN)
    return FALSE;
  if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 5)
    return FALSE;
  if (sActionData.playerCardId == JAIN_LIGHTSWORN_PALADIN
      && gFixedZones[sActionData.playerMonsterRow][sActionData.unkA] == zone)
    return sActionData.opponentCardId != CARD_NONE;
  if (sActionData.opponentCardId == JAIN_LIGHTSWORN_PALADIN
      && gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16] == zone)
    return sActionData.playerCardId != CARD_NONE;
  return FALSE;
}

void ApplyJainLightswornPaladinDamageStepAtk(const struct DuelCard *zone)
{
  if (!IsJainAttackingMonster(zone))
    return;
  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + JAIN_DAMAGE_STEP_ATK);
}

void TryApplyJainEndPhase(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 turn = ACTIVE_DUELIST;
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone == NULL || !zone->isFaceUp || zone->id != JAIN_LIGHTSWORN_PALADIN)
      continue;
    Duel_ShowEffectTextTyped(JAIN_LIGHTSWORN_PALADIN, 2);
    Duel_MillTopDeckCards(turn, JAIN_END_PHASE_MILL, TRUE);
    return;
  }
}

unsigned char CanActivateJAIN_LIGHTSWORN_PALADIN(void)
{
  if (gMonEffect.id != JAIN_LIGHTSWORN_PALADIN)
    return FALSE;

  /* Damage Step +300 via ApplyJainLightswornPaladinDamageStepAtk;
   * EP mill via TryApplyJainEndPhase. */
  return FALSE;
}

void ActivateJAIN_LIGHTSWORN_PALADINEffect(void)
{
  Duel_ShowEffectTextTyped(JAIN_LIGHTSWORN_PALADIN, 2);
}
