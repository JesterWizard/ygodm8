#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "effect_scripts.h"
#include "effect_system.h"
#include "gadget_box.h"
#include "spell_effects.h"

/* ponytail: no dedicated Gadget Box Token card id — reuse MOON_TOKEN like other
 * token spells. Ceiling: wrong printed name/stats; upgrade: real token card. */
#define GADGET_BOX_TOKEN_ID MOON_TOKEN

#define GADGET_BOX_BOARD_CELLS 20

/* 0 means unmarked; fixed duelist + 1 identifies the Token's summoner. */
static u8 sGadgetBoxTokenControllers[GADGET_BOX_BOARD_CELLS] APPEND_DATA = {0};

static s8 GadgetBoxBoardCellIndex(const struct DuelCard *zone)
{
  const struct DuelCard *base = &gDuel.board[0][0];

  if (zone == NULL || zone < base || zone >= base + GADGET_BOX_BOARD_CELLS)
    return -1;

  return (s8)(zone - base);
}

static void GadgetBox_MarkToken(struct DuelCard *zone, u8 fixedDuelist)
{
  s8 cell = GadgetBoxBoardCellIndex(zone);

  if (cell < 0 || fixedDuelist > DUEL_OPPONENT || zone->id != GADGET_BOX_TOKEN_ID)
    return;

  sGadgetBoxTokenControllers[cell] = fixedDuelist + 1;
}

void GadgetBox_ClearTokenState(void)
{
  u8 i;

  for (i = 0; i < GADGET_BOX_BOARD_CELLS; i++)
    sGadgetBoxTokenControllers[i] = 0;
}

u8 GadgetBox_HasTokenForFixedDuelist(u8 fixedDuelist)
{
  u8 i;

  if (fixedDuelist > DUEL_OPPONENT)
    return FALSE;

  for (i = 0; i < GADGET_BOX_BOARD_CELLS; i++) {
    struct DuelCard *zone = &gDuel.board[0][0] + i;

    if (sGadgetBoxTokenControllers[i] == 0)
      continue;
    if (zone->id != GADGET_BOX_TOKEN_ID) {
      sGadgetBoxTokenControllers[i] = 0;
      continue;
    }
    if (sGadgetBoxTokenControllers[i] == fixedDuelist + 1)
      return TRUE;
  }

  return FALSE;
}

u8 GadgetBox_BlocksExtraDeckSpecialSummon(u8 fixedDuelist, u16 cardId)
{
  if (!GadgetBox_HasTokenForFixedDuelist(fixedDuelist) || cardId == CARD_NONE)
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.color != SYNCHRO_CARD;
}

u8 GadgetBox_CanActivateIgnition(struct DuelCard *zone)
{
  if (zone == NULL || zone->id != GADGET_BOX || zone->isFaceUp == FALSE || !zone->isLocked)
    return FALSE;
  if (zone->unk4 == 0 || EffectOpt_IsUsed(GADGET_BOX))
    return FALSE;
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

enum DuelActionResult GadgetBox_ResolveIgnition(struct DuelCard *zone)
{
  s8 emptyZone;
  struct DuelCard *tokenZone;
  u8 fixedRow;
  u8 fixedCol;
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  enum DuelActionResult result;

  if (!GadgetBox_CanActivateIgnition(zone))
    return DUEL_ACTION_BLOCKED;

  emptyZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  result = Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, GADGET_BOX_TOKEN_ID, opts);
  if (result != DUEL_ACTION_OK)
    return result;

  zone->unk4--;
  EffectOpt_MarkUsed(GADGET_BOX);
  tokenZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][emptyZone];
  if (Duel_FindFixedMonsterZone(tokenZone, &fixedRow, &fixedCol))
    GadgetBox_MarkToken(tokenZone, Duel_FixedDuelistForMonsterRow(fixedRow));

  return DUEL_ACTION_OK;
}

APPEND_TEXT void EffectGADGET_BOX(void)
{
  const struct EffectScript *script = EffectScript_Find(GADGET_BOX, EFFECT_KIND_SPELL);

  if (script != NULL)
    EffectScript_Run(script);

  (void)GADGET_BOX_TOKEN_ID;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void GADGET_BOX_SelfCheck(void)
{
  if (GadgetBox_CanActivateIgnition(NULL))
    __builtin_trap();
  if (GADGET_BOX_TOKEN_ID != MOON_TOKEN)
    __builtin_trap();
}
#endif
