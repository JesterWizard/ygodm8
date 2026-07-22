#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "destiny_hero_dreamer.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "expanded_graveyard.h"
#include "monster_effect_usage.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static u8 sDreamerInit APPEND_DATA = {0};
static u8 sPendingDreamerBanish APPEND_DATA = {0xFF};

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static s16 FindDreamerInGy(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == DESTINY_HERO_DREAMER)
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DREAMER)
      return (s16)i;
  }

  return -1;
}

static s8 FindDreamerGyIndexFixed(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    if (gDuel.duelistbattleState[fixedDuelist].graveyard == DESTINY_HERO_DREAMER)
      return 0;
    return -1;
  }
  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (GraveyardExpand_GetCardAt(fixedDuelist, i) == DESTINY_HERO_DREAMER)
      return (s8)i;
  }
  return -1;
}

static void MarkDreamerLeaveBanish(u16 cardId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone != NULL && zone->id == cardId) {
      zone->unk4 |= 0x40; /* leave-banish mark (distinct from negate 0x80) */
      return;
    }
  }
}

u8 DestinyHeroDreamer_PreventsBattleDestroy(const struct DuelCard *zone)
{
  return zone != NULL && zone->isFaceUp && zone->id == DESTINY_HERO_DREAMER;
}

static void OnDreamerLeaveField(const struct EffectEvent *ev)
{
  if (ev == NULL || ev->cardId != DESTINY_HERO_DREAMER || gHideEffectText)
    return;
  if (ev->controller > DUEL_OPPONENT)
    return;
  if (ev->zone == NULL || (ev->zone->unk4 & 0x40) == 0)
    return;

  /* Resolve after ClearZone sends to GY — banish from GY. */
  sPendingDreamerBanish = ev->controller;
}

static void OnDreamerFieldChange(const struct EffectEvent *ev)
{
  u8 controller;
  s8 gyIndex;

  (void)ev;
  if (sPendingDreamerBanish > DUEL_OPPONENT)
    return;

  controller = sPendingDreamerBanish;
  sPendingDreamerBanish = 0xFF;
  gyIndex = FindDreamerGyIndexFixed(controller);
  if (gyIndex < 0)
    return;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREAMER, 8);
  Duel_BanishGraveyardAtFixed(controller, (u8)gyIndex);
  UpdateDuelGfxExceptField();
}

void DestinyHeroDreamer_EnsureInit(void)
{
  if (sDreamerInit)
    return;

  sDreamerInit = TRUE;
  EffectEvent_Subscribe(EFFECT_EVENT_ON_LEAVE_FIELD, OnDreamerLeaveField);
  EffectEvent_Subscribe(EFFECT_EVENT_ON_FIELD_CHANGE, OnDreamerFieldChange);
}

unsigned char CanActivateDESTINY_HERO_DREAMER(void)
{
  if (gMonEffect.id != DESTINY_HERO_DREAMER)
    return FALSE;

  /* Battle protect via DestinyHeroDreamer_PreventsBattleDestroy.
   * Leave-banish via DestinyHeroDreamer_EnsureInit (unk4 mark on GY SS).
   * Ceiling: true damage-calc GY SS timing needs battle hook. */
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FindDreamerInGy() < 0)
    return FALSE;

  return FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) >= 0;
}

void ActivateDESTINY_HERO_DREAMEREffect(void)
{
  s16 gyIndex;
  struct DuelSummonOpts opts;
  u8 fixedDuelist = FixedDuelistForActive();
  u16 cardId;

  Duel_ShowEffectTextTyped(DESTINY_HERO_DREAMER, 2);

  if (IsDuelOver() == TRUE)
    return;

  gyIndex = FindDreamerInGy();
  if (gyIndex < 0)
    return;

  if (ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  if (Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkDreamerLeaveBanish(cardId);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}
