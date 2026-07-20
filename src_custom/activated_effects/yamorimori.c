#include "global.h"
#include "common-chax.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindYamorimoriInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == YAMORIMORI)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == YAMORIMORI)
      return (s16)i;
  }

  return -1;
}

static u8 IsReptileMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_REPTILE);
}

static u8 OwnFieldHasReptile(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->isFaceUp && IsReptileMonster(zone->id))
      return TRUE;
  }

  return FALSE;
}

static u8 IsOppFaceUpMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE || IsGodCard(zone->id))
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 OppHasFaceUpMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppFaceUpMonster(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 AiPickOppTarget(u8 *outCol)
{
  u8 col;
  u16 bestAtk = 0;
  u8 bestCol = 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col];

    if (!IsOppFaceUpMonster(zone))
      continue;

    SetCardInfo(zone->id);
    if (bestCol == 0xFF || gCardInfo.atk > bestAtk) {
      bestAtk = gCardInfo.atk;
      bestCol = col;
    }
  }

  if (bestCol == 0xFF)
    return FALSE;

  *outCol = bestCol;
  return TRUE;
}

unsigned char CanActivateYAMORIMORI(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != YAMORIMORI)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone != NULL && zone->id == YAMORIMORI)
    return FALSE;

  /* ponytail: GY ignition needs GY-menu wire. Ceiling: banish self from GY +
   * own Reptile + opp face-up present → destroy opp face-up monster. */
  if (FindYamorimoriInGy() < 0)
    return FALSE;

  return OwnFieldHasReptile() && OppHasFaceUpMonster();
}

void ActivateYAMORIMORIEffect(void)
{
  s16 gyIndex;
  u8 fixedDuelist = FixedDuelistForActive();
  u8 targetCol;
  struct DuelCard *target;

  Duel_ShowEffectTextTyped(YAMORIMORI, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindYamorimoriInGy();
  if (gyIndex < 0 || !OwnFieldHasReptile() || !OppHasFaceUpMonster())
    return;

  Duel_BanishGraveyardAtFixed(fixedDuelist, (u8)gyIndex);
  GraveyardExpand_RefreshDisplay();

  if (IsDuelOver() == TRUE)
    return;

  if (!AiPickOppTarget(&targetCol))
    return;

  target = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][targetCol];
  if (Duel_DestroyZone(target, INACTIVE_DUELIST, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
