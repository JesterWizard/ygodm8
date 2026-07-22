#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"
#include "summon_tribute.h"

extern const CardData gCardData_NEW[];

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u16 ReadOpponentGraveyardTop(void)
{
  u8 fixedDuelist = DUEL_OPPONENT;

  if (!GraveyardExpand_IsEnabled())
    return gDuel.duelistbattleState[fixedDuelist].graveyard;

  if (GraveyardExpand_GetCount(fixedDuelist) == 0)
    return CARD_NONE;

  return GraveyardExpand_GetCardAt(fixedDuelist, GraveyardExpand_GetCount(fixedDuelist) - 1);
}

static void TryBurnForDiscardedMonster(void)
{
  u16 cardId = ReadOpponentGraveyardTop();
  u16 level;
  s32 damage;

  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return;

  level = gCardData_NEW[cardId].level;
  if (level == 0)
    return;

  damage = (s32)level * 100;
  Duel_ChangeLpWithPrefaceText(INACTIVE_DUELIST, -damage, THESTALOS_THE_FIRESTORM_MONARCH, 2, TRUE);
}

static void RunThestalosDiscardAndBurn(struct DuelCard *self)
{
  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return;

  if (Duel_DiscardRandomFromHand(INACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  TryBurnForDiscardedMonster();
}

unsigned char ShouldActivateThestalosTheFirestormMonarchTribute(void)
{
  struct DuelCard *zone;

  if (gActiveEffect.cardId != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  if (GetPendingTributeSummonCardId() != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->id != THESTALOS_THE_FIRESTORM_MONARCH || zone->unk4 != 0)
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateThestalosTheFirestormMonarchTribute(void)
{
  struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  Duel_ShowEffectTextTyped(THESTALOS_THE_FIRESTORM_MONARCH, 8);
  RunThestalosDiscardAndBurn(zone);

  if (zone != NULL && IsDuelOver() != TRUE)
    zone->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

unsigned char CanActivateTHESTALOS_THE_FIRESTORM_MONARCH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  /* Tribute Summon discard/burn via ActivateThestalosTheFirestormMonarchTribute.
   * Field OPT below is a thin stand-in (not printed). */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateTHESTALOS_THE_FIRESTORM_MONARCHEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(THESTALOS_THE_FIRESTORM_MONARCH, 2);

  RunThestalosDiscardAndBurn(self);
  if (IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
