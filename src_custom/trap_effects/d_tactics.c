#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "expanded_graveyard.h"

void ClearZone(struct DuelCard *zone);
void UpdateDuelGfxExceptField(void);

static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sHeroNameAlt[] APPEND_RODATA = "Hero";
static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";
static const char sDestinyHeroNameAlt[] APPEND_RODATA = "Destiny Hero";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sHeroName)
      || Duel_CardNameContains(cardId, sHeroNameAlt);
}

static u8 IsHighDestinyHero(u16 cardId)
{
  if (cardId == DESTINY_END_DRAGOON)
    return TRUE;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sDestinyHeroName)
      && !Duel_CardNameContains(cardId, sDestinyHeroNameAlt))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level >= 8;
}

static void ActivateD_TACTICSZone(struct DuelCard *zone)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
  u8 col;
  u8 hasHighDh = FALSE;
  u8 fixedOpp = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);

  if (Duel_ActivateContinuousTrapPreamble(zone, D_TACTICS) == DUEL_ACTION_DUEL_OVER)
    return;

  /* ponytail: Standby HERO +400 + destroy-Set D-HERO Spell need turn/destroy
   * hooks. Ceiling: +1 stage on HERO monsters; if Lv8+ D-HERO present, banish
   * 1 opp card (field then GY then hand). */

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *m = gFixedZones[row][col];

    if (m != NULL && IsHeroMonster(m->id))
      IncrementPermStage(m);
    if (m != NULL && IsHighDestinyHero(m->id))
      hasHighDh = TRUE;
  }

  if (hasHighDh) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *m = gFixedZones[oppRow][col];

      if (m != NULL && m->id != CARD_NONE) {
        Duel_BanishZone(m, FALSE);
        UpdateDuelGfxExceptField();
        return;
      }
    }
    if (GraveyardExpand_IsEnabled() && GraveyardExpand_GetCount(fixedOpp) > 0) {
      Duel_BanishGraveyardAtFixed(fixedOpp, GraveyardExpand_GetCount(fixedOpp) - 1);
      UpdateDuelGfxExceptField();
      return;
    }
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (gTurnHands[ACTIVE_DUELIST][col] != NULL
          && gTurnHands[ACTIVE_DUELIST][col]->id != CARD_NONE) {
        ClearZone(gTurnHands[ACTIVE_DUELIST][col]);
        break;
      }
    }
  }

  UpdateDuelGfxExceptField();
}

void TryActivateD_TACTICSOnOpponentTurnStart(void)
{
  Duel_TryActivateBackrowTrapOnTurnStart(D_TACTICS, ActivateD_TACTICSZone);
}

