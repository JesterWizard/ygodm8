#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "removed_from_play.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

extern u16 gRemovedFromPlay[2][REMOVED_FROM_PLAY_CAPACITY];

static const char sHeroName[] APPEND_RODATA = "HERO";

static void InitHandSlotFromCard(struct DuelCard *handSlot, u16 cardId)
{
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName);
}

static u8 FindBanishedHero(u8 *outFixedDuelist, u8 *outIndex)
{
  u8 fixedDuelist;
  u8 i;

  if (!RemovedFromPlay_IsEnabled())
    return FALSE;

  for (fixedDuelist = DUEL_PLAYER; fixedDuelist <= DUEL_OPPONENT; fixedDuelist++) {
    u8 count = RemovedFromPlay_GetCount(fixedDuelist);

    for (i = 0; i < count; i++) {
      u16 cardId = RemovedFromPlay_GetCardAt(fixedDuelist, i);

      if (IsHeroMonster(cardId)) {
        *outFixedDuelist = fixedDuelist;
        *outIndex = i;
        return TRUE;
      }
    }
  }

  return FALSE;
}

/* ponytail: no RemovedFromPlay_RemoveAt — shift RFP array in place after add.
 * Ceiling: local mutate of gRemovedFromPlay; upgrade: RemovedFromPlay_RemoveAt. */
static void RemoveBanishedAt(u8 fixedDuelist, u8 index)
{
  u8 count;
  u8 i;

  count = RemovedFromPlay_GetCount(fixedDuelist);
  if (index >= count)
    return;

  for (i = index + 1; i < count; i++)
    gRemovedFromPlay[fixedDuelist][i - 1] = gRemovedFromPlay[fixedDuelist][i];

  gRemovedFromPlay[fixedDuelist][count - 1] = CARD_NONE;
}

static u8 AddBanishedHeroToHand(u8 fixedDuelist, u8 index)
{
  s8 handZone;
  u16 cardId;

  handZone = FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]);
  if (handZone < 0)
    return FALSE;

  cardId = RemovedFromPlay_GetCardAt(fixedDuelist, index);
  if (!IsHeroMonster(cardId))
    return FALSE;

  RemoveBanishedAt(fixedDuelist, index);
  InitHandSlotFromCard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), cardId);
  return TRUE;
}

unsigned char CanActivateVISION_HERO_GRAVITO(void)
{
  struct DuelCard *zone;
  u8 fixedDuelist;
  u8 index;

  if (gMonEffect.id != VISION_HERO_GRAVITO)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != VISION_HERO_GRAVITO)
    return FALSE;

  /* ponytail: tribute self → SS 2 Vision HERO from Spell & Trap Zone needs equip
   * zone API. Ceiling: OPT add 1 banished HERO monster to hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnHands[ACTIVE_DUELIST]) < 0)
    return FALSE;

  return FindBanishedHero(&fixedDuelist, &index);
}

void ActivateVISION_HERO_GRAVITOEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 fixedDuelist;
  u8 index;

  Duel_ShowEffectTextTyped(VISION_HERO_GRAVITO, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (!FindBanishedHero(&fixedDuelist, &index))
    return;

  if (!AddBanishedHeroToHand(fixedDuelist, index))
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
