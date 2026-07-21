#include "global.h"
#include "common-chax.h"
#include "chrysalis_neo_spacian.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sChrysalisName[] APPEND_RODATA = "Chrysalis";

u8 ChrysalisNeoSpacian_IsChrysalisMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sChrysalisName);
}

u16 ChrysalisNeoSpacian_ForId(u16 chrysalisId)
{
  switch (chrysalisId) {
  case CHRYSALIS_CHICKY:
    return NEO_SPACIAN_AIR_HUMMINGBIRD;
  case CHRYSALIS_DOLPHIN:
    return NEO_SPACIAN_AQUA_DOLPHIN;
  case CHRYSALIS_MOLE:
    return NEO_SPACIAN_GRAND_MOLE;
  case CHRYSALIS_PANTAIL:
    return NEO_SPACIAN_DARK_PANTHER;
  case CHRYSALIS_PINNY:
    return NEO_SPACIAN_GLOW_MOSS;
  default:
    /* ponytail: only the five Chrysalis in-trunk pairs are mapped. */
    return CARD_NONE;
  }
}

u8 ChrysalisNeoSpacian_IsMappedPair(u16 chrysalisId)
{
  return ChrysalisNeoSpacian_ForId(chrysalisId) != CARD_NONE;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void CHRYSALIS_NEO_SPACIAN_SelfCheck(void)
{
  if (ChrysalisNeoSpacian_ForId(CHRYSALIS_CHICKY) != NEO_SPACIAN_AIR_HUMMINGBIRD)
    while (1)
      ;
  if (ChrysalisNeoSpacian_ForId(CHRYSALIS_PINNY) != NEO_SPACIAN_GLOW_MOSS)
    while (1)
      ;
  if (ChrysalisNeoSpacian_IsMappedPair(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
