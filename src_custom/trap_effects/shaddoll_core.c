#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sShaddollName[] APPEND_RODATA = "Shaddoll";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsShaddollSpellTrapExceptCore(u16 cardId)
{
  if (cardId == CARD_NONE || cardId == SHADDOLL_CORE)
    return FALSE;
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return Duel_CardNameContains(cardId, sShaddollName);
}

APPEND_TEXT void EffectSHADDOLL_CORE(void)
{
  struct DuelCard *trapZone;
  s8 empty;
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 i;
  u16 addId = CARD_NONE;
  s8 handEmpty;

  Duel_ShowTrapResponseText(SHADDOLL_CORE, gTrapEffectData.originCardId);

  trapZone = gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol];

  /* ponytail: true trap-monster (still a Trap) + Attribute fusion substitute
   * need Embodiment-style link. Ceiling: place SHADDOLL_CORE on monster row
   * and keep trap face-up continuous; GY add Shaddoll S/T stand-in on activate. */

  empty = FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]);
  if (trapZone != NULL && empty >= 0 && !ArchlordKristya_IsSpecialSummonLocked()) {
    struct DuelCard *m = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][empty];

    Duel_ActivateContinuousZone(trapZone);
    m->id = SHADDOLL_CORE;
    m->isFaceUp = TRUE;
    m->isLocked = FALSE;
    m->isDefending = FALSE;
    m->unk4 = 1;
    ResetPermStage(m);
    ResetTempStage(m);
    trapZone->unk4 = 1; /* linked monster form */
  } else if (trapZone != NULL) {
    Duel_DestroyZone(trapZone, INACTIVE_DUELIST, FALSE);
  }

  handEmpty = FirstEmptyZoneInRow(gTurnHands[INACTIVE_DUELIST]);
  if (handEmpty >= 0 && GraveyardExpand_IsEnabled()) {
    for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
      if (IsShaddollSpellTrapExceptCore(GraveyardExpand_GetCardAt(fixedDuelist, i))) {
        addId = GraveyardExpand_GetCardAt(fixedDuelist, i);
        GraveyardExpand_RemoveAtFixed(fixedDuelist, i);
        break;
      }
    }
    if (addId != CARD_NONE) {
      gTurnHands[INACTIVE_DUELIST][handEmpty]->id = addId;
      gTurnHands[INACTIVE_DUELIST][handEmpty]->isFaceUp = FALSE;
      gTurnHands[INACTIVE_DUELIST][handEmpty]->isLocked = FALSE;
      ResetPermStage(gTurnHands[INACTIVE_DUELIST][handEmpty]);
      ResetTempStage(gTurnHands[INACTIVE_DUELIST][handEmpty]);
    }
  }

  UpdateDuelGfxExceptField();
  (void)ClearZone;
}
