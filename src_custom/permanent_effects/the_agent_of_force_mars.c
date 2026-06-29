#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/custom_field_spells.h"
#include "custom_field_spell.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"

#define THE_AGENT_OF_FORCE_MARS_BASE_ATK 0
#define THE_AGENT_OF_FORCE_MARS_BASE_DEF 0

static u8 ControllerControlsSanctuary(struct DuelCard *zone)
{
  if (gActiveCustomFieldSpellId != CUSTOM_FIELD_SPELL_SANCTUARY_IN_THE_SKY)
    return FALSE;
  if (gActiveFieldSpellController == FIELD_SPELL_CONTROLLER_NONE)
    return FALSE;

  return GetDuelistForZone(zone) == gActiveFieldSpellController;
}

static u16 LpDifferenceBonus(u8 controller)
{
  u8 opponent = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u16 ownerLp = gDuelLifePoints[controller];
  u16 oppLp = gDuelLifePoints[opponent];

  if (ownerLp <= oppLp)
    return 0;

  return ownerLp - oppLp;
}

static void TheAgentOfForceMarsCurrentStats(struct DuelCard *zone, u16 *atk, u16 *def)
{
  u8 controller;
  u16 bonus;

  *atk = THE_AGENT_OF_FORCE_MARS_BASE_ATK;
  *def = THE_AGENT_OF_FORCE_MARS_BASE_DEF;

  if (!ControllerControlsSanctuary(zone))
    return;

  controller = GetDuelistForZone(zone);
  bonus = LpDifferenceBonus(controller);
  *atk = Duel_ClampStat((u32)*atk + bonus);
  *def = Duel_ClampStat((u32)*def + bonus);
}

u8 TheAgentOfForceMars_ApplyDynamicZoneStats(struct DuelCard *zone)
{
  u16 atk;
  u16 def;

  if (zone == NULL || zone->id != THE_AGENT_OF_FORCE_MARS)
    return FALSE;

  TheAgentOfForceMarsCurrentStats(zone, &atk, &def);
  SetCardInfo(zone->id);
  Duel_WriteCardInfoStats(zone->id, atk, def);
  return TRUE;
}

#if !defined(__GNUC__)
#error The Agent of Force - Mars stat hook self-check requires GCC
#elif __GNUC__
void TheAgentOfForceMars_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = THE_AGENT_OF_FORCE_MARS;
  TheAgentOfForceMars_ApplyDynamicZoneStats(&zone);
}
#endif
