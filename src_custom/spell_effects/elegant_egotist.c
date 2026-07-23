#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "harpie_perfumer.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);
void TryActivatingPermanentEffects(void);
void CheckWinConditionExodia(unsigned char);

/* Attack-position summons often keep isFaceUp=0 until EOT flip. */
static u8 MonsterCountsAsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 IsPrintedHarpieLadyId(u16 cardId)
{
  return cardId == HARPIE_LADY || cardId == HARPIE_LADY_1 || cardId == HARPIE_LADY_2
      || cardId == HARPIE_LADY_3 || cardId == CYBER_HARPIE;
}

static u8 ZoneIsHarpieLadyName(struct DuelCard *zone)
{
  if (!MonsterCountsAsFaceUp(zone))
    return FALSE;

  if (IsPrintedHarpieLadyId(zone->id))
    return TRUE;

  return HarpiePerfumer_TreatsNameAsHarpieLady(zone);
}

static u8 FieldHasHarpieLady(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (ZoneIsHarpieLadyName(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 IsElegantEgotistSummon(u16 cardId)
{
  if (cardId == HARPIE_LADY_SISTERS)
    return TRUE;

  return IsPrintedHarpieLadyId(cardId);
}

static u8 HandHasElegantSummon(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsElegantEgotistSummon(gTurnHands[ACTIVE_DUELIST][col]->id)
        && !Duel_CardCannotBeSpecialSummoned(gTurnHands[ACTIVE_DUELIST][col]->id))
      return TRUE;
  }

  return FALSE;
}

static u16 FindElegantSummonInDeck(void)
{
  u8 fixedDuelist = gTurnDuelistBattleState[ACTIVE_DUELIST]
                        == &gDuel.duelistbattleState[DUEL_PLAYER]
                    ? DUEL_PLAYER
                    : DUEL_OPPONENT;
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  /* Prefer Sisters when both exist (common Harpie line). */
  for (i = top; i < deckSize; i++) {
    if (gDuelDecks[fixedDuelist].cards[i] == HARPIE_LADY_SISTERS
        && !Duel_CardCannotBeSpecialSummoned(HARPIE_LADY_SISTERS))
      return HARPIE_LADY_SISTERS;
  }

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsElegantEgotistSummon(cardId) && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

u8 CanActivateELEGANT_EGOTIST(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  if (!FieldHasHarpieLady())
    return FALSE;

  if (HandHasElegantSummon())
    return TRUE;

  return FindElegantSummonInDeck() != CARD_NONE;
}

static void ELEGANT_EGOTIST_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(TRUE);
  u16 deckId;

  Duel_ShowEffectText(ELEGANT_EGOTIST);

  if (IsDuelOver() == TRUE)
    return;

  if (spellZone != NULL)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, FALSE);

  if (IsDuelOver() == TRUE)
    return;

  if (HandHasElegantSummon()) {
    if (Duel_SpecialSummonFromHand(ACTIVE_DUELIST, CARD_NONE, IsElegantEgotistSummon, opts)
        == DUEL_ACTION_OK) {
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
      return;
    }
  }

  deckId = FindElegantSummonInDeck();
  if (deckId == CARD_NONE)
    return;

  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, deckId, opts) != DUEL_ACTION_OK)
    return;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

APPEND_TEXT void EffectELEGANT_EGOTIST(void)
{
  if (!CanActivateELEGANT_EGOTIST()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(ELEGANT_EGOTIST, ELEGANT_EGOTIST_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void ELEGANT_EGOTIST_SelfCheck(void)
{
  if (!IsElegantEgotistSummon(HARPIE_LADY_SISTERS))
    while (1)
      ;
  if (!IsElegantEgotistSummon(HARPIE_LADY))
    while (1)
      ;
  if (IsElegantEgotistSummon(HARPIE_PERFUMER))
    while (1)
      ;
}
#endif
