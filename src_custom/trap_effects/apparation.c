#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"

void UpdateDuelGfxExceptField(void);

static const char sVisionHeroName[] APPEND_RODATA = "Vision HERO";
static const char sVisionHeroNameAlt[] APPEND_RODATA = "Vision Hero";
static const char sHeroName[] APPEND_RODATA = "HERO";
static const char sHeroNameAlt[] APPEND_RODATA = "Hero";

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsVisionHeroLv4OrLower(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;
  if (!Duel_CardNameContains(cardId, sVisionHeroName)
      && !Duel_CardNameContains(cardId, sVisionHeroNameAlt))
    return FALSE;

  SetCardInfo(cardId);
  return gCardInfo.level > 0 && gCardInfo.level <= 4;
}

static u8 HadHeroDestroyedContext(void)
{
  u8 row = WhoseTurn() == DUEL_PLAYER ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
  u8 col;

  if (Duel_CardNameContains(gTrapEffectData.originCardId, sHeroName)
      || Duel_CardNameContains(gTrapEffectData.originCardId, sHeroNameAlt))
    return TRUE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[row][col];

    if (zone != NULL
        && (Duel_CardNameContains(zone->id, sHeroName)
            || Duel_CardNameContains(zone->id, sHeroNameAlt)))
      return TRUE;
  }

  return FALSE;
}

APPEND_TEXT void EffectAPPARATION(void)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(INACTIVE_DUELIST);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;
  u16 cardId = CARD_NONE;
  struct DuelSummonOpts opts;
  u8 oppRow = WhoseTurn() == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;

  Duel_ShowTrapResponseText(APPARATION, gTrapEffectData.originCardId);

  if (!HadHeroDestroyedContext() || ArchlordKristya_IsSpecialSummonLocked()
      || FirstEmptyZoneInRow(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW]) < 0) {
    Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                     INACTIVE_DUELIST, FALSE);
    return;
  }

  for (i = top; i < deckSize; i++) {
    if (IsVisionHeroLv4OrLower(gDuelDecks[fixedDuelist].cards[i])) {
      cardId = gDuelDecks[fixedDuelist].cards[i];
      break;
    }
  }

  if (cardId != CARD_NONE) {
    opts = Duel_DefaultSpecialSummonOpts(TRUE);
    Duel_SpecialSummonFromDeck(INACTIVE_DUELIST, cardId, opts);

    /* Optional: halve opp monster ATK/DEF stand-in via -stages. */
    for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
      struct DuelCard *m = gFixedZones[oppRow][i];

      if (m != NULL && m->isFaceUp && m->id != CARD_NONE) {
        DecrementPermStage(m);
        DecrementPermStage(m);
        break;
      }
    }
  }

  Duel_DestroyZone(gTurnZones[INACTIVE_DUELIST_BACKROW][gTrapEffectData.trapZoneCol],
                   INACTIVE_DUELIST, FALSE);
  UpdateDuelGfxExceptField();
}
