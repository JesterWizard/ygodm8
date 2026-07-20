#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

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

unsigned char CanActivateTHESTALOS_THE_FIRESTORM_MONARCH(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != THESTALOS_THE_FIRESTORM_MONARCH)
    return FALSE;

  /* ponytail: Tribute Summon trigger needs summon hook. Ceiling: once via usage if opp hand. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) > 0;
}

void ActivateTHESTALOS_THE_FIRESTORM_MONARCHEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];

  Duel_ShowEffectTextTyped(THESTALOS_THE_FIRESTORM_MONARCH, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  if (Duel_CountCardsInHand(gTurnHands[INACTIVE_DUELIST]) == 0)
    return;

  if (Duel_DiscardRandomFromHand(INACTIVE_DUELIST, 1, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  if (IsDuelOver() == TRUE)
    return;

  TryBurnForDiscardedMonster();

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
