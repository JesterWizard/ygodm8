#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "gladiator_beasts_valor.h"

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

static u8 ControlsGladiatorBeast(u8 fixedDuelist)
{
  u8 col;
  u8 row = Duel_FixedMonsterRowForDuelist(fixedDuelist);

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && Duel_CardNameContains(zone->id, sGladiatorBeastName))
      return TRUE;
  }
  return FALSE;
}

static void ActivateGLADIATOR_BEASTS_VALORZone(struct DuelCard *zone)
{
  u8 controller = GetDuelistForZone(zone);

  if (controller > DUEL_OPPONENT || !ControlsGladiatorBeast(controller))
    return;

  if (Duel_ActivateContinuousTrapPreamble(zone, GLADIATOR_BEASTS_VALOR)
      == DUEL_ACTION_DUEL_OVER)
    return;
}

void TryActivateGLADIATOR_BEASTS_VALOROnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(GLADIATOR_BEASTS_VALOR,
                                         ActivateGLADIATOR_BEASTS_VALORZone);
}

u8 GladiatorBeastsValor_CanAttackMonsterZone(struct DuelCard *zone)
{
  u8 defender;

  if (zone == NULL || zone->id == CARD_NONE)
    return TRUE;

  defender = GetDuelistForZone(zone);
  if (defender > DUEL_OPPONENT)
    return TRUE;
  if (Duel_FindBackrowCard(defender, GLADIATOR_BEASTS_VALOR, TRUE) == NULL)
    return TRUE;

  return Duel_CardNameContains(zone->id, sGladiatorBeastName);
}
