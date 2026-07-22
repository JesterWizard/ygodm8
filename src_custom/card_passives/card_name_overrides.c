#include "global.h"
#include "common-chax.h"
#include "card_name_overrides.h"
#include "constants/card_ids.h"

u8 AmazonessPrincess_TreatsNameAsQueen(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != AMAZONESS_PRINCESS)
    return FALSE;

  return TRUE;
}

u8 DarkMagicianTheMagicianOfBlackMagic_TreatsNameAsDarkMagician(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_MAGIC)
    return FALSE;

  return zone->isFaceUp;
}

u8 DarkMagicianTheMagicianOfBlackChaos_TreatsNameAsDarkMagician(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != DARK_MAGICIAN_THE_MAGICIAN_OF_BLACK_CHAOS)
    return FALSE;

  return zone->isFaceUp;
}

u8 DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id != DARK_MAGICIAN_THE_DRAGON_KNIGHT)
    return FALSE;

  return zone->isFaceUp;
}

u8 DarkMagicianGirlTheMagiciansApprentice_TreatsNameAsDarkMagicianGirl(const struct DuelCard *zone)
{
  if (zone == NULL)
    return FALSE;

  if (zone->id != DARK_MAGICIAN_GIRL_THE_MAGICIAN_S_APPRENTICE
      && zone->id != DARK_MAGICIAN_GIRL_THE_MAGICIANS_APPRENTICE)
    return FALSE;

  return zone->isFaceUp;
}

#if !defined(__GNUC__)
void CardNameOverrides_SelfCheck(void);
#endif

void CardNameOverrides_SelfCheck(void)
{
  struct DuelCard zone;

  zone.isFaceUp = TRUE;
  zone.id = AMAZONESS_PRINCESS;
  if (!AmazonessPrincess_TreatsNameAsQueen(&zone))
    return;

  zone.id = DARK_MAGICIAN_THE_DRAGON_KNIGHT;
  if (!DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician(&zone))
    return;

  zone.isFaceUp = FALSE;
  if (DarkMagicianTheDragonKnight_TreatsNameAsDarkMagician(&zone))
    return;
}
