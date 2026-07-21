#include "global.h"
#include "common-chax.h"
#include "amazoness_scouts.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

/* Bit0 = player Amazoness protected; bit1 = opponent. */
static u8 sScoutsProtect APPEND_DATA = {0};

void AmazonessScouts_ArmProtection(u8 controller)
{
  if (controller == DUEL_PLAYER)
    sScoutsProtect |= 1;
  else if (controller == DUEL_OPPONENT)
    sScoutsProtect |= 2;
}

void AmazonessScouts_ClearTurnState(void)
{
  sScoutsProtect = 0;
}

static u8 ControllerHasScoutsProtect(u8 controller)
{
  if (controller == DUEL_PLAYER)
    return (sScoutsProtect & 1) != 0;
  if (controller == DUEL_OPPONENT)
    return (sScoutsProtect & 2) != 0;
  return FALSE;
}

static u8 ZoneController(const struct DuelCard *zone)
{
  u8 row;
  u8 col;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &row, &col))
    return 0xFF;

  if (row == PLAYER_MONSTER_ROW)
    return DUEL_PLAYER;
  if (row == OPPONENT_MONSTER_ROW)
    return DUEL_OPPONENT;
  return 0xFF;
}

u8 AmazonessScouts_PreventsDestroy(const struct DuelCard *zone)
{
  u8 controller;

  if (zone == NULL || !zone->isFaceUp || !Duel_IsAmazonessCard(zone->id))
    return FALSE;

  controller = ZoneController(zone);
  return ControllerHasScoutsProtect(controller);
}

u8 AmazonessScouts_IsTargetImmune(const struct DuelCard *zone)
{
  return AmazonessScouts_PreventsDestroy(zone);
}

unsigned char CanActivateAMAZONESS_SCOUTS(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AMAZONESS_SCOUTS)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AMAZONESS_SCOUTS)
    return FALSE;

  /* Either-player quick timing not wired; once via usage on your turn only. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  return TRUE;
}

void ActivateAMAZONESS_SCOUTSEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  u8 controller;

  Duel_ShowEffectTextTyped(AMAZONESS_SCOUTS, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  MarkMonsterEffectUsed(self);
  PlayMusic(SFX_TRIBUTE);

  controller = WhoseTurn();
  if (Duel_DestroyZone(self, ACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  AmazonessScouts_ArmProtection(controller);

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
