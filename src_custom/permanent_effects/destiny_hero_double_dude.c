#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "destiny_hero_double_dude.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "the_dark_door.h"

extern u8 gDoubleDudeBattleDestroyedPending;

void TryUnlockDestinyHeroDoubleDudeForSecondAttack(struct DuelCard *attacker)
{
  if (attacker == NULL || attacker->id != DESTINY_HERO_DOUBLE_DUDE)
    return;
  if (IsTheDarkDoorActiveOnField())
    return;

  if (attacker->effectUsedThisTurn == FALSE) {
    attacker->effectUsedThisTurn = TRUE;
    attacker->isLocked = FALSE;
  }
}

static void OnDoubleDudeBattleDestroyed(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != DESTINY_HERO_DOUBLE_DUDE)
    return;

  if (ev->controller == DUEL_PLAYER)
    gDoubleDudeBattleDestroyedPending |= 1;
  else if (ev->controller == DUEL_OPPONENT)
    gDoubleDudeBattleDestroyedPending |= 2;
}

void DestinyHeroDoubleDude_EnsureInit(void)
{
  static u8 sInit APPEND_DATA = {0};

  if (sInit)
    return;
  sInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_BATTLE_DESTROY, OnDoubleDudeBattleDestroyed);
}

static u8 FixedDuelistForActiveTurn(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;
  return DUEL_OPPONENT;
}

u8 ShouldActivateDestinyHeroDoubleDudeTurnEffect(void)
{
  u8 fixed;
  u8 bit;

  DestinyHeroDoubleDude_EnsureInit();

  if (gActiveEffect.cardId != DESTINY_HERO_DOUBLE_DUDE)
    return FALSE;
  if (gActiveEffect.turnRow != 6)
    return FALSE;

  fixed = FixedDuelistForActiveTurn();
  bit = (fixed == DUEL_PLAYER) ? 1 : 2;
  if ((gDoubleDudeBattleDestroyedPending & bit) == 0)
    return FALSE;

  return NumEmptyZonesInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 2;
}

void ActivateDestinyHeroDoubleDudeTurnEffect(void)
{
  u8 fixed = FixedDuelistForActiveTurn();
  u8 bit = (fixed == DUEL_PLAYER) ? 1 : 2;
  u8 i;
  struct DuelSummonOpts opts;

  if (!ShouldActivateDestinyHeroDoubleDudeTurnEffect())
    return;

  gDoubleDudeBattleDestroyedPending &= (u8)~bit;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOUBLE_DUDE, 9);
  if (IsDuelOver() == TRUE)
    return;

  /* Token stand-in: Moon Token (no dedicated Double Dude Token id). */
  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_ATK;
  opts.markSpecialSummon = FALSE;
  for (i = 0; i < 2; i++) {
    if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, MOON_TOKEN, opts) != DUEL_ACTION_OK)
      break;
  }
}

unsigned char ShouldActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
  /* Double attack + Standby tokens live via unlock + turn effect. */
  (void)gActiveEffect;
  return FALSE;
}

void ActivateDESTINY_HERO_DOUBLE_DUDE(void)
{
}
