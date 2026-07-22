#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "evil_hero_wild_cyclone.h"

struct WildCycloneActionData {
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

extern struct WildCycloneActionData sActionData;

void UpdateDuelGfxExceptField(void);

static u8 TurnDuelistForFixed(u8 fixedDuelist)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[fixedDuelist])
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 DidWildCycloneDealBattleDamage(u8 attackerFixed)
{
  u16 damage;

  if (attackerFixed == DUEL_PLAYER) {
    if (sActionData.playerCardId != EVIL_HERO_WILD_CYCLONE)
      return FALSE;
    if (sActionData.id != 1 && sActionData.id != 2 && sActionData.id != 4)
      return FALSE;
    damage = gUnk2023EA0.unk0[1].initialLifePoints - gDuelLifePoints[DUEL_OPPONENT];
  } else {
    if (sActionData.opponentCardId != EVIL_HERO_WILD_CYCLONE)
      return FALSE;
    if (sActionData.id != 5 && sActionData.id != 6)
      return FALSE;
    damage = gUnk2023EA0.unk0[0].initialLifePoints - gDuelLifePoints[DUEL_PLAYER];
  }
  return damage > 0;
}

static void DestroyFaceDownBackrow(u8 oppFixed)
{
  u8 backrow = oppFixed == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;
  u8 turn = TurnDuelistForFixed(oppFixed);
  u8 col;
  u8 destroyed = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[backrow][col];

    if (zone == NULL || zone->id == CARD_NONE || zone->isFaceUp)
      continue;
    if (destroyed == 0)
      Duel_ShowEffectTextTyped(EVIL_HERO_WILD_CYCLONE, 2);
    Duel_DestroyZone(zone, turn, FALSE);
    destroyed = 1;
    if (IsDuelOver() == TRUE)
      return;
  }

  if (destroyed)
    UpdateDuelGfxExceptField();
}

void ApplyEvilHeroWildCycloneBattleEffect(void)
{
  if (DidWildCycloneDealBattleDamage(DUEL_PLAYER)) {
    DestroyFaceDownBackrow(DUEL_OPPONENT);
    return;
  }
  if (DidWildCycloneDealBattleDamage(DUEL_OPPONENT))
    DestroyFaceDownBackrow(DUEL_PLAYER);
}

unsigned char ShouldActivateEVIL_HERO_WILD_CYCLONE(void)
{
  /* Battle-damage Set S/T wipe via ApplyEvilHeroWildCycloneBattleEffect.
   * ponytail: attack S/T lock until end of Damage Step needs chain gate. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateEVIL_HERO_WILD_CYCLONE(void)
{
}
