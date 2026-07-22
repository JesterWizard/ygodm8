#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "armed_neos.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void SetCardInfo(unsigned short id);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

u8 ExtraDeck_GetCardQty(u16 cardId);
u8 ExtraDeck_TryRemoveCard(u16 cardId);

#define FLAG_GRAVEYARD_PLAYER 1
#define FLAG_GRAVEYARD_OPPONENT 2
#define ARMED_NEOS_QUICK_EFFECT 2

struct ArmedNeosActionData {
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

extern struct ArmedNeosActionData sActionData;

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsDragonMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_DRAGON);
}

static u8 HighestDragonLevelInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 bestLevel = 0;
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (!IsDragonMonster(cardId))
      return 0;

    SetCardInfo(cardId);
    return gCardInfo.level;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsDragonMonster(cardId))
      continue;

    SetCardInfo(cardId);
    if (gCardInfo.level > bestLevel)
      bestLevel = gCardInfo.level;
  }

  return bestLevel;
}

static u8 OppHasMonsterLevelAtMost(u8 maxLevel)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level <= maxLevel)
      return TRUE;
  }

  return FALSE;
}

static u16 FindNeosExtraDeckCard(void)
{
  static const u16 sNeosCandidates[] APPEND_RODATA = {
    ELEMENTAL_HERO_NEOS,
    ELEMENTAL_HERO_BRAVE_NEOS,
    ARMED_NEOS,
    ELEMENTAL_HERO_GRAND_NEOS,
    ELEMENTAL_HERO_FLARE_NEOS,
    ELEMENTAL_HERO_AIR_NEOS,
    ELEMENTAL_HERO_AQUA_NEOS,
    ELEMENTAL_HERO_DARK_NEOS,
    ELEMENTAL_HERO_GLOW_NEOS,
    ELEMENTAL_HERO_MAGMA_NEOS,
    ELEMENTAL_HERO_MARINE_NEOS,
    ELEMENTAL_HERO_STORM_NEOS,
    ELEMENTAL_HERO_CHAOS_NEOS,
    ELEMENTAL_HERO_COSMO_NEOS,
    ELEMENTAL_HERO_NEBULA_NEOS,
  };
  u8 i;

  for (i = 0; i < ARRAY_COUNT(sNeosCandidates); i++) {
    if (ExtraDeck_GetCardQty(sNeosCandidates[i]) > 0)
      return sNeosCandidates[i];
  }

  return CARD_NONE;
}

static u8 CanResolveArmedNeosQuickEffect(struct DuelCard *zone)
{
  u16 extraId;

  if (zone == NULL || zone->id != ARMED_NEOS || zone->unk4 != ARMED_NEOS_QUICK_EFFECT)
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  extraId = FindNeosExtraDeckCard();
  if (extraId == CARD_NONE)
    return FALSE;

  return !Duel_BlocksExtraDeckSpecialSummon(extraId);
}

static void ResolveArmedNeosQuickEffect(struct DuelCard *self)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 extraId = FindNeosExtraDeckCard();

  if (self == NULL || extraId == CARD_NONE)
    return;

  if (!ExtraDeck_TryRemoveCard(extraId))
    return;

  Duel_ShowEffectTextTyped(ARMED_NEOS, 3);

  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  self->unk4 = 0;

  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, extraId, opts) == DUEL_ACTION_DUEL_OVER)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

void ApplyArmedNeosBattleDestroyGrant(void)
{
  struct DuelCard *zone;

  if (gHideEffectText)
    return;

  if (!(sActionData.flags & FLAG_GRAVEYARD_OPPONENT)
      || sActionData.opponentCardId == CARD_NONE
      || GetTypeGroup(sActionData.opponentCardId) != TYPE_GROUP_MONSTER)
    return;

  if (sActionData.playerCardId == ARMED_NEOS) {
    zone = gFixedZones[sActionData.playerMonsterRow][sActionData.unkA];
  } else if (sActionData.opponentCardId == ARMED_NEOS) {
    zone = gFixedZones[sActionData.opponentMonsterRow][sActionData.unk16];
  } else {
    return;
  }

  if (zone == NULL || zone->id != ARMED_NEOS)
    return;

  zone->unk4 = ARMED_NEOS_QUICK_EFFECT;
}

static void DestroyOppMonstersLevelAtMost(u8 maxLevel)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    SetCardInfo(zone->id);
    if (gCardInfo.level > maxLevel)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;
  }
}

unsigned char CanActivateARMED_NEOS(void)
{
  struct DuelCard *zone;
  u8 maxLevel;

  if (gMonEffect.id != ARMED_NEOS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != ARMED_NEOS)
    return FALSE;

  if (zone->unk4 == ARMED_NEOS_QUICK_EFFECT)
    return CanResolveArmedNeosQuickEffect(zone);

  /* Battle-destroy quick tribute SS via ApplyArmedNeosBattleDestroyGrant.
   * OPT destroy opp monsters with Level ≤ highest Dragon Level in GY. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  maxLevel = HighestDragonLevelInGy();
  if (maxLevel == 0)
    return FALSE;

  return OppHasMonsterLevelAtMost(maxLevel);
}

void ActivateARMED_NEOSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 maxLevel;

  Duel_ShowEffectTextTyped(ARMED_NEOS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (self->unk4 == ARMED_NEOS_QUICK_EFFECT) {
    ResolveArmedNeosQuickEffect(self);
    return;
  }

  maxLevel = HighestDragonLevelInGy();
  if (maxLevel == 0)
    return;

  DestroyOppMonstersLevelAtMost(maxLevel);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
