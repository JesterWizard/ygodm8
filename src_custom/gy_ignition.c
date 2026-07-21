#include "global.h"
#include "common-chax.h"
#include "amazoness_call.h"
#include "amazoness_secret_arts.h"
#include "constants/card_ids.h"
#include "expanded_graveyard.h"
#include "gy_ignition.h"

u8 CanActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex);
void ActivateTheWhiteStoneOfAncientsGy(u8 fixedDuelist, u8 gyIndex);

struct GyIgnitionEntry {
  u16 cardId;
  u8 (*can)(u8 fixedDuelist, u8 gyIndex);
  void (*activate)(u8 fixedDuelist, u8 gyIndex);
};

static const struct GyIgnitionEntry sGyIgnitionTable[] APPEND_RODATA = {
  { THE_WHITE_STONE_OF_ANCIENTS,
    CanActivateTheWhiteStoneOfAncientsGy,
    ActivateTheWhiteStoneOfAncientsGy },
  { AMAZONESS_CALL,
    CanActivateAmazonessCallGy,
    ActivateAmazonessCallGy },
  { AMAZONESS_SECRET_ARTS,
    CanActivateAmazonessSecretArtsGy,
    ActivateAmazonessSecretArtsGy },
};

u8 GyIgnition_TryAt(u8 fixedDuelist, u16 cardId)
{
  const struct GyIgnitionEntry *entry = NULL;
  u8 i;
  u8 gyCount;

  if (cardId == CARD_NONE || !GraveyardExpand_IsEnabled())
    return FALSE;

  for (i = 0; i < ARRAY_COUNT(sGyIgnitionTable); i++) {
    if (sGyIgnitionTable[i].cardId == cardId) {
      entry = &sGyIgnitionTable[i];
      break;
    }
  }

  if (entry == NULL)
    return FALSE;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) != cardId)
      continue;

    if (!entry->can(fixedDuelist, i))
      continue;

    entry->activate(fixedDuelist, i);
    return TRUE;
  }

  return FALSE;
}
