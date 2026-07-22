#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern const CardData gCardData_NEW[];

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static s8 FindDestinyHeroHandZoneAtOrBelowAtk(u16 atkLimit, u16 excludeId)
{
  u8 col;
  s8 bestZone = -1;
  u16 bestAtk = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    u16 cardId = gTurnHands[ACTIVE_DUELIST][col]->id;
    u16 atk;

    if (!IsDestinyHeroMonster(cardId) || cardId == excludeId
        || Duel_CardCannotBeSpecialSummoned(cardId))
      continue;

    atk = gCardData_NEW[cardId].atk;
    if (atk > atkLimit)
      continue;

    if (bestZone < 0 || atk > bestAtk) {
      bestAtk = atk;
      bestZone = (s8)col;
    }
  }

  return bestZone;
}

unsigned char CanActivateDESTINY_HERO_DRILLDARK(void)
{
  struct DuelCard *zone;
  u16 selfAtk;
  s8 handZone;

  if (gMonEffect.id != DESTINY_HERO_DRILLDARK)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != DESTINY_HERO_DRILLDARK)
    return FALSE;

  /* Pierce via ApplySimplePiercersBattleEffect.
   * ponytail: on-Summon trigger need summon hook.
   * Ceiling: OPT SS 1 D-HERO from hand with ATK≤ this card's ATK. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  selfAtk = Duel_GetZoneFinalAtk(zone);
  handZone = FindDestinyHeroHandZoneAtOrBelowAtk(selfAtk, DESTINY_HERO_DRILLDARK);
  return handZone >= 0;
}

void ActivateDESTINY_HERO_DRILLDARKEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 selfAtk;
  s8 handZone;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DRILLDARK, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  selfAtk = Duel_GetZoneFinalAtk(self);
  handZone = FindDestinyHeroHandZoneAtOrBelowAtk(selfAtk, DESTINY_HERO_DRILLDARK);
  if (handZone < 0)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonFromHandZone(ACTIVE_DUELIST, handZone, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
