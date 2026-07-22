#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/spell_effects.h"
#include "duel_helpers.h"
#include "gravekeepers_priestess.h"
#include "spell_effects.h"

#define PRIESTESS_GK_STAT_BONUS 200

static u8 IsVanillaTerrainFieldSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.spellEffect >= SPELL_EFFECT_FOREST && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI;
}

static u8 IsFaceUpFieldSpellOnBoard(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_BACKROW; row <= PLAYER_BACKROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
        continue;
      if (GetTypeGroup(zone->id) != TYPE_GROUP_SPELL)
        continue;
      if (IsVanillaTerrainFieldSpell(zone->id))
        return TRUE;
      /* Named custom fields */
      if (zone->id == NECROVALLEY || zone->id == WETLANDS || zone->id == GEARTOWN
          || zone->id == DRAGON_RAVINE || zone->id == BURNING_LAND
          || zone->id == SEAL_OF_ORICHALCOS || zone->id == NEO_SPACE
          || zone->id == SKYSCRAPER || zone->id == SKYSCRAPER_2_HERO_CITY
          || zone->id == HARPIES_HUNTING_GROUND || zone->id == FUSION_GATE
          || zone->id == PSEUDO_SPACE)
        return TRUE;
    }
  }
  return FALSE;
}

static u8 AnyFaceUpPriestess(void)
{
  u8 fixed;
  u8 col;

  for (fixed = DUEL_PLAYER; fixed <= DUEL_OPPONENT; fixed++) {
    u8 row = Duel_FixedMonsterRowForDuelist(fixed);

    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gFixedZones[row][col];

      if (zone != NULL && zone->isFaceUp && zone->id == GRAVEKEEPERS_PRIESTESS)
        return TRUE;
    }
  }
  return FALSE;
}

u8 GravekeepersPriestess_TreatsFieldAsNecrovalley(void)
{
  return !IsFaceUpFieldSpellOnBoard() && AnyFaceUpPriestess();
}

void ApplyGravekeepersPriestessStatBoostToCardInfo(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || !zone->isFaceUp)
    return;
  if (!Necrovalley_IsGravekeeperMonster(zone->id))
    return;
  if (!AnyFaceUpPriestess())
    return;

  gCardInfo.atk = Duel_ClampStat((u32)gCardInfo.atk + PRIESTESS_GK_STAT_BONUS);
  gCardInfo.def = Duel_ClampStat((u32)gCardInfo.def + PRIESTESS_GK_STAT_BONUS);
}

unsigned char CanActivateGRAVEKEEPERS_PRIESTESS(void)
{
  if (gMonEffect.id != GRAVEKEEPERS_PRIESTESS)
    return FALSE;

  /* Continuous GK boost + Necrovalley treatment via Priestess helpers. */
  return FALSE;
}

void ActivateGRAVEKEEPERS_PRIESTESSEffect(void)
{
  Duel_ShowEffectTextTyped(GRAVEKEEPERS_PRIESTESS, 2);
}
