#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "aromaseraphy_jasmine.h"
#include "constants/card_enums.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "god_card.h"
#include "monster_effect_usage.h"

void ClearZoneAndSendMonToGraveyard2(struct DuelCard *zone, u8 player);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 ControllerHasFaceUpSeraphyJasmineWithLpAdvantage(u8 controller)
{
  u8 opp = controller == DUEL_PLAYER ? DUEL_OPPONENT : DUEL_PLAYER;
  u8 row;
  u8 col;

  if (gDuelLifePoints[controller] <= gDuelLifePoints[opp])
    return FALSE;

  row = Duel_FixedMonsterRowForDuelist(controller);
  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL && zone->isFaceUp && zone->id == AROMASERAPHY_JASMINE)
      return TRUE;
  }

  return FALSE;
}

u8 AromaseraphyJasmine_PreventsBattleDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || !zone->isFaceUp || !Duel_CardHasMonsterType(zone->id, TYPE_PLANT))
    return FALSE;

  controller = GetDuelistForZone((struct DuelCard *)zone);
  if (controller > DUEL_OPPONENT)
    return FALSE;

  /* All your Plants while Jasmine face-up and LP higher (no Link points). */
  return ControllerHasFaceUpSeraphyJasmineWithLpAdvantage(controller);
}

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 OwnMonsterFixedRow(void)
{
  return WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u8 IsPlantMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardHasMonsterType(cardId, TYPE_PLANT);
}

static u16 FindDeckPlant(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsPlantMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gMonEffect.row][gMonEffect.zone];
}

static u8 IsOwnTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;
  struct DuelCard *self = SelfZone();

  if (fixedRow != OwnMonsterFixedRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE || zone == self)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER || IsGodCard(zone->id))
    return FALSE;

  return TRUE;
}

static u8 FieldHasTributeTarget(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOwnTributeTarget(OwnMonsterFixedRow(), col))
      return TRUE;
  }

  return FALSE;
}

static void SpecialSummonPlantFromDeck(void)
{
  u16 plantId = FindDeckPlant();
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);

  if (plantId == CARD_NONE)
    return;

  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, plantId, opts);
}

static void ResolveTributeTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = SelfZone();
  u8 fixedDuelist = FixedDuelistForActive();

  if (!IsOwnTributeTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  ClearZoneAndSendMonToGraveyard2(zone, fixedDuelist);
  NotifyDynamicEquipFieldChanged();

  if (IsDuelOver() == TRUE)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  SpecialSummonPlantFromDeck();

  if (self != NULL)
    MarkMonsterEffectUsed(self);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  PlayMusic(SFX_CANCEL);
}

static u8 AiPickTributeTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = OwnMonsterFixedRow();
  u16 lowestAtk = 0xFFFF;
  u8 pickCol = 0xFF;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone;
    u16 atk;

    if (!IsOwnTributeTarget(row, col))
      continue;

    zone = gFixedZones[row][col];
    atk = Duel_GetZoneFinalAtk(zone);
    if (pickCol == 0xFF || atk < lowestAtk) {
      pickCol = col;
      lowestAtk = atk;
    }
  }

  if (pickCol == 0xFF)
    return FALSE;

  *outRow = row;
  *outCol = pickCol;
  return TRUE;
}

unsigned char CanActivateAROMASERAPHY_JASMINE(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMASERAPHY_JASMINE)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->id != AROMASERAPHY_JASMINE)
    return FALSE;

  /* LP-higher Plant battle protect via AromaseraphyJasmine_PreventsBattleDestroy.
   * Tribute 1 you control → SS Plant from Deck. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (FindDeckPlant() == CARD_NONE)
    return FALSE;

  return FieldHasTributeTarget();
}

void ActivateAROMASERAPHY_JASMINEEffect(void)
{
  Duel_ShowEffectTextTyped(AROMASERAPHY_JASMINE, 2);

  if (IsDuelOver() == TRUE)
    return;

  gDuelCursor.destY = gMonEffect.row;
  gDuelCursor.destX = gMonEffect.zone;

  Duel_SetupPickZone(IsOwnTributeTarget, ResolveTributeTarget, CancelTargeting,
                     AiPickTributeTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}
