#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "dark_snake_syndrome.h"
#include "gravekeepers_servant.h"
#include "kishido_spirit.h"
#include "duel_activated_backrow.h"
#include "toll.h"
#include "the_dark_door.h"
#include "dark_room_of_nightmare.h"
#include "pyramid_of_light.h"
#include "mask_of_restrict.h"
#include "rivalry_of_warlords.h"
#include "gravity_bind.h"
#include "fairy_box.h"
#include "skull_invitation.h"
#include "self_destruct_button.h"
#include "curse_of_darkness.h"
#include "coffin_seller.h"
#include "final_countdown.h"
#include "precious_cards_from_beyond.h"
#include "dynamic_equip.h"
#include "level_limit_area_b.h"
#include "vengeful_bog_spirit.h"
#include "kaiser_colosseum.h"
#include "wall_of_revealing_light.h"
#include "nightmare_wheel.h"

u8 IsActivatedChainEnergyZone(const struct DuelCard *zone);
u8 IsActivatedUltimateOfferingZone(const struct DuelCard *zone);

u8 Duel_ZoneIsNonSelectableActivatedBackrow(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (zone->id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE)
    return TRUE;

  if (IsActivatedChainEnergyZone(zone))
    return TRUE;
  if (IsActivatedTollZone(zone))
    return TRUE;
  if (IsActivatedTheDarkDoorZone(zone))
    return TRUE;
  if (IsActivatedDarkRoomZone(zone))
    return TRUE;
  if (IsActivatedPyramidOfLightZone(zone))
    return TRUE;
  if (IsActivatedUltimateOfferingZone(zone))
    return TRUE;
  if (IsActivatedMaskOfRestrictZone(zone))
    return TRUE;
  if (IsActivatedRivalryOfWarlordsZone(zone))
    return TRUE;
  if (IsActivatedGravityBindZone(zone))
    return TRUE;
  if (IsActivatedFairyBoxZone(zone))
    return TRUE;
  if (IsActivatedSkullInvitationZone(zone))
    return TRUE;
  if (IsActivatedSelfDestructButtonZone(zone))
    return TRUE;
  if (IsActivatedCurseOfDarknessZone(zone))
    return TRUE;
  if (IsNonSelectableCoffinSellerZone(zone))
    return TRUE;
  if (IsActivatedFinalCountdownZone(zone))
    return TRUE;
  if (IsActivatedPreciousCardsFromBeyondZone(zone))
    return TRUE;
  if (IsActivatedLevelLimitAreaBZone(zone))
    return TRUE;
  if (IsActivatedDarkSnakeSyndromeZone(zone))
    return TRUE;
  if (IsActivatedGravekeepersServantZone(zone))
    return TRUE;
  if (IsActivatedVengefulBogSpiritZone(zone))
    return TRUE;
  if (IsActivatedKaiserColosseumZone(zone))
    return TRUE;
  if (IsActivatedWallOfRevealingLightZone(zone))
    return TRUE;
  if (IsActivatedNightmareWheelZone(zone))
    return TRUE;
  if (IsActivatedKishidoSpiritZone(zone))
    return TRUE;
  if (IsActiveDynamicEquipSpellZone(zone))
    return TRUE;

  return FALSE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DuelActivatedBackrow_SelfCheck(void)
{
  struct DuelCard zone;

  zone.id = LEVEL_LIMIT_AREA_B;
  zone.isFaceUp = TRUE;
  if (!Duel_ZoneIsNonSelectableActivatedBackrow(&zone))
    __builtin_trap();

  zone.id = DARK_SNAKE_SYNDROME;
  if (!Duel_ZoneIsNonSelectableActivatedBackrow(&zone))
    __builtin_trap();

  zone.id = GRAVEKEEPERS_SERVANT;
  if (!Duel_ZoneIsNonSelectableActivatedBackrow(&zone))
    __builtin_trap();

  zone.id = KISHIDO_SPIRIT;
  if (!Duel_ZoneIsNonSelectableActivatedBackrow(&zone))
    __builtin_trap();

  zone.id = CARD_NONE;
  if (Duel_ZoneIsNonSelectableActivatedBackrow(&zone))
    __builtin_trap();
}
#endif
