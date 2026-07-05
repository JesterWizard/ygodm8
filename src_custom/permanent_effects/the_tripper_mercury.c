#include "global.h"
#include "common-chax.h"
#include "constants/card_effect_texts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "summon_tribute.h"
#include "the_tripper_mercury.h"
#include "mini_card.h"

void UpdateDuelGfxExceptField(void);
void FlipCardFaceUp(struct DuelCard *zone);

extern u8 gHideEffectText;

#define TRIPPER_MERCURY_TRIBUTE_COUNT 3
#define TRIPPER_MERCURY_DRAIN_ACTIVE 1
#define TRIPPER_MERCURY_SUMMONED 2

static void SetMonsterFaceUpAttack(struct DuelCard *zone)
{
  zone->isDefending = FALSE;
  FlipCardFaceUp(zone);
}

static void SetAllMonstersFaceUpAttack(void)
{
  u8 row;
  u8 col;
  u8 changed = FALSE;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone = gTurnZones[row][col];

      if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
        continue;

      SetMonsterFaceUpAttack(zone);
      changed = TRUE;
    }
  }

  if (changed)
    NotifyDynamicEquipFieldChanged();
}

static void ShowTripperMercuryPopup(u16 effectTextId)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  Duel_ShowCardEffectText(THE_TRIPPER_MERCURY, effectTextId);
  gHideEffectText = hideEffectText;
}

static void ShowTheTripperMercuryActivationText(void)
{
  ShowTripperMercuryPopup(CARD_EFFECT_TEXT_THE_TRIPPER_MERCURY_POPUP_1);
}

static void ShowTheTripperMercuryDrainText(void)
{
  ShowTripperMercuryPopup(CARD_EFFECT_TEXT_THE_TRIPPER_MERCURY_POPUP_2);
}

static void ResolveTheTripperMercuryTributeSummon(struct DuelCard *zone)
{
  u8 paidTributes = GetPendingSummonTributeCount();

  ShowTheTripperMercuryActivationText();

  if (IsDuelOver() == TRUE)
    return;

  if (paidTributes == TRIPPER_MERCURY_TRIBUTE_COUNT) {
    ShowTheTripperMercuryDrainText();

    if (IsDuelOver() == TRUE)
      return;
  }

  SetAllMonstersFaceUpAttack();
  SetMonsterFaceUpAttack(zone);

  if (paidTributes == TRIPPER_MERCURY_TRIBUTE_COUNT)
    zone->unk4 = TRIPPER_MERCURY_DRAIN_ACTIVE;
  else
    zone->unk4 = TRIPPER_MERCURY_SUMMONED;

  ClearPendingSummonTributeCount();

  if (zone->unk4 == TRIPPER_MERCURY_DRAIN_ACTIVE)
    RefreshFieldMonsterStatOverlays();

  UpdateDuelGfxExceptField();
}

void FinishTheTripperMercuryTributeSummon(struct DuelCard *zone, u8 fixedRow, u8 fixedCol)
{
  (void)fixedRow;
  (void)fixedCol;

  if (zone == NULL || zone->id != THE_TRIPPER_MERCURY)
    return;

  if (GetPendingSummonTributeCount() == 0)
    return;

  if (zone->unk4 != 0)
    return;

  ResolveTheTripperMercuryTributeSummon(zone);
}

unsigned char ShouldActivateTheTripperMercury(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != THE_TRIPPER_MERCURY)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (GetPendingSummonTributeCount() == 0)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  return zone->unk4 == 0;
}

void ActivateTheTripperMercury(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  ResolveTheTripperMercuryTributeSummon(zone);
}

u8 TheTripperMercury_DrainActiveOnTurnRow(u8 turnRow)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[turnRow][col];

    if (zone->id != THE_TRIPPER_MERCURY || !zone->isFaceUp)
      continue;
    if (zone->unk4 == TRIPPER_MERCURY_DRAIN_ACTIVE)
      return TRUE;
  }

  return FALSE;
}

void ApplyTheTripperMercuryOpponentAtkDrain(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;
  u8 opponentRow;
  u16 computedAtk;
  u16 originalAtk;

  if (zone == NULL || zone->id == CARD_NONE || !ZoneShowsCombatStats(zone))
    return;

  if (!Duel_FindTurnMonsterZone(zone, &turnRow, &col))
    return;

  opponentRow = (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
      ? INACTIVE_DUELIST_MONSTER_ROW
      : ACTIVE_DUELIST_MONSTER_ROW;

  if (!TheTripperMercury_DrainActiveOnTurnRow(opponentRow))
    return;

  computedAtk = gCardInfo.atk;
  /* ponytail: SetCardInfo would reset gCardInfo.atk/def back to printed base. */
  if (zone->id < NUM_TOTAL_CARDS)
    originalAtk = gCardData_NEW[zone->id].atk;
  else
    originalAtk = 0;
  gCardInfo.atk = (computedAtk > originalAtk) ? computedAtk - originalAtk : 0;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void TheTripperMercury_SelfCheck(void)
{
  if (TRIPPER_MERCURY_DRAIN_ACTIVE == TRIPPER_MERCURY_SUMMONED)
    while (1)
      ;
}
#endif
