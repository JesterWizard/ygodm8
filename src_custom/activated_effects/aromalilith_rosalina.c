#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "monster_effect_usage.h"
#include "six_card_hand.h"
#include "synchro_duel.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sAromaName[] APPEND_RODATA = "Aroma";

static u8 FixedDuelistForActive(void)
{
  if (gTurnDuelistBattleState[ACTIVE_DUELIST] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsAromaMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sAromaName);
}

static u8 IsFaceUpAromaOnField(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  if (fixedRow != ACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  if (zone == NULL || !IsAromaMonster(zone->id))
    return FALSE;

  return IsCardFaceUp(zone) || zone->isDefending == FALSE;
}

static u8 ControlsFaceUpAroma(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsFaceUpAromaOnField(ACTIVE_DUELIST_MONSTER_ROW, col))
      return TRUE;
  }

  return FALSE;
}

static u16 HighestControlledAromaAtk(void)
{
  u8 col;
  u16 best = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gFixedZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    u16 atk;

    if (!IsFaceUpAromaOnField(ACTIVE_DUELIST_MONSTER_ROW, col))
      continue;

    atk = Duel_GetZoneFinalAtk(zone);
    if (atk > best)
      best = atk;
  }

  return best;
}

static u16 FindNonTunerAromaInDeck(void)
{
  u8 fixedDuelist = FixedDuelistForActive();
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsAromaMonster(cardId) && !Card_IsTuner(cardId)
        && !Duel_CardCannotBeSpecialSummoned(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char CanActivateAROMALILITH_ROSALINA(void)
{
  struct DuelCard *zone;

  if (gMonEffect.id != AROMALILITH_ROSALINA)
    return FALSE;

  zone = gTurnZones[gMonEffect.row][gMonEffect.zone];
  if (zone == NULL || zone->id != AROMALILITH_ROSALINA)
    return FALSE;

  /* ponytail: discard quick LP + Plant-only SS lock need chain/SS hooks.
   * Ceiling: OPT SS 1 non-Tuner Aroma from Deck in DEF. */
  if (!CanUseMonsterEffect(zone))
    return FALSE;

  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return FindNonTunerAromaInDeck() != CARD_NONE;
}

void ActivateAROMALILITH_ROSALINAEffect(void)
{
  struct DuelCard *self = gTurnZones[gMonEffect.row][gMonEffect.zone];
  struct DuelSummonOpts opts;
  u16 cardId;

  Duel_ShowEffectTextTyped(AROMALILITH_ROSALINA, 2);

  if (self == NULL || IsDuelOver() == TRUE)
    return;

  cardId = FindNonTunerAromaInDeck();
  if (cardId == CARD_NONE)
    return;

  opts = Duel_DefaultSpecialSummonOpts(TRUE);
  opts.mode = DUEL_SUMMON_SPECIAL_FACE_UP_DEF;
  if (Duel_SpecialSummonFromDeck(ACTIVE_DUELIST, cardId, opts) != DUEL_ACTION_OK)
    return;

  MarkMonsterEffectUsed(self);
  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

u8 CanActivateAromalilithRosalinaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= (IsSixCardHandEnabled() ? MAX_HAND_ZONES_SIX : MAX_ZONES_IN_ROW))
    return FALSE;

  if (SixCardHand_ZoneAtHandRow(handRow, handZone)->id != AROMALILITH_ROSALINA)
    return FALSE;

  return ControlsFaceUpAroma();
}

u8 TryActivateAromalilithRosalinaFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  u16 aromaAtk;
  s32 gain;

  if (!CanActivateAromalilithRosalinaFromHand(handZone))
    return FALSE;

  Duel_ShowEffectTextTyped(AROMALILITH_ROSALINA, 2);

  if (IsDuelOver() == TRUE)
    return TRUE;

  aromaAtk = HighestControlledAromaAtk();
  if (aromaAtk == 0)
    return FALSE;

  if (Duel_DestroyZone(SixCardHand_ZoneAtHandRow(handRow, handZone), ACTIVE_DUELIST, FALSE)
      == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  if (IsDuelOver() == TRUE)
    return TRUE;

  gain = (s32)(aromaAtk / 2);
  if (gain > 0
      && Duel_ChangeLp(ACTIVE_DUELIST, gain, TRUE) == DUEL_ACTION_DUEL_OVER)
    return TRUE;

  UpdateDuelGfxExceptField();
  return TRUE;
}

#if !defined(__GNUC__)
u8 CanActivateAromalilithRosalinaFromHand(u8 handZone);
u8 TryActivateAromalilithRosalinaFromHand(u8 handZone);
#endif
