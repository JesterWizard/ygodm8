#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void RefreshFieldMonsterStatOverlays(void);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 OppHasDestroyableAtkLeSelf(u16 ceilingAtk)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (Duel_GetZoneFinalAtk(zone) <= ceilingAtk)
      return TRUE;
  }

  return FALSE;
}

static u8 DestroyOppAtkLeSelf(u16 ceilingAtk)
{
  u8 col;
  u8 destroyed = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
      continue;

    if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    if (Duel_GetZoneFinalAtk(zone) > ceilingAtk)
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return destroyed;

    destroyed++;
  }

  if (destroyed > 0)
    NotifyDynamicEquipFieldChanged();

  return destroyed;
}

unsigned char CanActivateEVIL_HERO_MALICIOUS_BANE(void)
{
  struct DuelCard *zone;
  u16 selfAtk;

  if (gMonEffect.id != EVIL_HERO_MALICIOUS_BANE)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != EVIL_HERO_MALICIOUS_BANE)
    return FALSE;

  /* ponytail: destruction immunity + HERO-only attack gate need destroy/attack hooks.
   * Ceiling: OPT destroy opp monsters with ATK≤self, +tempStage, mark unk4. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  selfAtk = Duel_GetZoneFinalAtk(zone);
  return OppHasDestroyableAtkLeSelf(selfAtk);
}

void ActivateEVIL_HERO_MALICIOUS_BANEEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u16 selfAtk;
  u8 destroyed;
  s8 stages;

  Duel_ShowEffectTextTyped(EVIL_HERO_MALICIOUS_BANE, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  selfAtk = Duel_GetZoneFinalAtk(self);
  destroyed = DestroyOppAtkLeSelf(selfAtk);

  if (IsDuelOver() == TRUE)
    return;

  if (destroyed == 0)
    return;

  /* ponytail: +200 ATK each via tempStage (~500/unit); attack lock only marks self unk4. */
  stages = (s8)((destroyed * 200 + 499) / 500);
  if (stages > 0) {
    if (self->tempStage > 127 - stages)
      self->tempStage = 127;
    else
      self->tempStage = (s8)(self->tempStage + stages);
    RefreshFieldMonsterStatOverlays();
  }

  self->unk4 |= 0x80;
  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
