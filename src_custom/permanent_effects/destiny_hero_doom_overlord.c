#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"

void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);

static const char sDestinyHeroName[] APPEND_RODATA = "Destiny HERO";

static struct DuelCard *SelfZone(void)
{
  return gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
}

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 RivalFixedMonsterRow(void)
{
  u8 fixedRow;
  u8 col;

  if (!Duel_FindFixedMonsterZone(SelfZone(), &fixedRow, &col))
    return OPPONENT_MONSTER_ROW;

  return fixedRow == PLAYER_MONSTER_ROW ? OPPONENT_MONSTER_ROW : PLAYER_MONSTER_ROW;
}

static u8 IsOppMonsterTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (fixedRow != RivalFixedMonsterRow())
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER;
}

static u8 FieldHasOppMonster(void)
{
  u8 col;
  u8 row = RivalFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppMonsterTarget(row, col))
      return TRUE;
  }

  return FALSE;
}

static u8 IsDestinyHeroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sDestinyHeroName);
}

static u8 IsSupportSpell(u16 cardId)
{
  return cardId == CLOCK_TOWER_PRISON || cardId == DARK_CITY_AT_MIDNIGHT;
}

static u16 FindDestinyHeroInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDestinyHeroMonster(cardId))
      return cardId;
  }

  return CARD_NONE;
}

static s16 FindSupportSpellGyIndex(u8 fixedDuelist)
{
  u8 i;

  if (!GraveyardExpand_IsEnabled()) {
    u16 top = gDuel.duelistbattleState[fixedDuelist].graveyard;

    if (IsSupportSpell(top))
      return 0;
    return -1;
  }

  for (i = 0; i < GraveyardExpand_GetCount(fixedDuelist); i++) {
    if (IsSupportSpell(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s16)i;
  }

  return -1;
}

static u16 FindSupportSpellInDeck(u8 turnDuelist)
{
  if (Duel_FindDeckCardIndex(turnDuelist, CLOCK_TOWER_PRISON) >= 0)
    return CLOCK_TOWER_PRISON;
  if (Duel_FindDeckCardIndex(turnDuelist, DARK_CITY_AT_MIDNIGHT) >= 0)
    return DARK_CITY_AT_MIDNIGHT;

  return CARD_NONE;
}

static u8 CanMillAndSearch(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);

  if (FirstEmptyZoneInRow(gTurnHands[turnDuelist]) < 0)
    return FALSE;

  if (FindDestinyHeroInDeck(turnDuelist) == CARD_NONE)
    return FALSE;

  if (FindSupportSpellInDeck(turnDuelist) != CARD_NONE)
    return TRUE;

  return FindSupportSpellGyIndex(fixedDuelist) >= 0;
}

static u8 MillOneDestinyHeroFromDeck(u8 turnDuelist)
{
  u16 cardId = FindDestinyHeroInDeck(turnDuelist);

  if (cardId == CARD_NONE)
    return FALSE;

  if (Duel_RemoveDeckCardAt(turnDuelist,
          (u8)Duel_FindDeckCardIndex(turnDuelist, cardId), FALSE)
      != DUEL_ACTION_OK)
    return FALSE;

  GraveyardExpand_PushTurn(turnDuelist, cardId);
  return TRUE;
}

static u8 AddSupportSpellToHand(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u16 deckId = FindSupportSpellInDeck(turnDuelist);
  s16 gyIndex;
  s8 handZone;
  u16 cardId;
  struct DuelCard *handSlot;

  handZone = FirstEmptyZoneInRow(gTurnHands[turnDuelist]);
  if (handZone < 0)
    return FALSE;

  if (deckId != CARD_NONE)
    return Duel_AddDeckCardToHand(turnDuelist, deckId, TRUE) == DUEL_ACTION_OK;

  gyIndex = FindSupportSpellGyIndex(fixedDuelist);
  if (gyIndex < 0)
    return FALSE;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gDuel.duelistbattleState[fixedDuelist].graveyard;
    gDuel.duelistbattleState[fixedDuelist].graveyard = CARD_NONE;
  } else {
    cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, (u8)gyIndex);
    GraveyardExpand_SyncLegacyTop(fixedDuelist);
  }

  if (!IsSupportSpell(cardId))
    return FALSE;

  handSlot = SixCardHand_ZoneAtHandRow(gTurnHands[turnDuelist], (u8)handZone);
  handSlot->id = cardId;
  handSlot->isFaceUp = FALSE;
  handSlot->isLocked = FALSE;
  handSlot->isDefending = FALSE;
  handSlot->unkTwo = 0;
  handSlot->unkThree = 0;
  handSlot->unk4 = 0;
  handSlot->willChangeSides = FALSE;
  ResetPermStage(handSlot);
  ResetTempStage(handSlot);
  return TRUE;
}

static void DoMillAndSearch(u8 turnDuelist)
{
  if (!CanMillAndSearch(turnDuelist))
    return;

  if (!MillOneDestinyHeroFromDeck(turnDuelist))
    return;

  AddSupportSpellToHand(turnDuelist);
}

static void ResolveBanishTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];
  struct DuelCard *self = SelfZone();
  u8 duelist;

  if (!IsOppMonsterTarget(fixedRow, fixedCol) || zone == NULL)
    return;

  if (Duel_BanishZone(zone, FALSE) == DUEL_ACTION_DUEL_OVER)
    return;

  NotifyDynamicEquipFieldChanged();
  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  DoMillAndSearch(duelist);

  if (self != NULL)
    self->unk4 = 1;

  UpdateDuelGfxExceptField();
  CheckWinConditionExodia(WhoseTurn());
  if (IsDuelOver() != TRUE)
    TryActivatingPermanentEffects();
}

static void CancelTargeting(void)
{
  struct DuelCard *self = SelfZone();
  u8 duelist;

  PlayMusic(SFX_CANCEL);
  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  DoMillAndSearch(duelist);

  if (self != NULL)
    self->unk4 = 1;

  UpdateDuelGfxExceptField();
}

static u8 AiPickBanishTarget(u8 *outRow, u8 *outCol)
{
  u8 col;
  u8 row = RivalFixedMonsterRow();

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOppMonsterTarget(row, col)) {
      *outRow = row;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

unsigned char ShouldActivateDESTINY_HERO_DOOM_OVERLORD(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != DESTINY_HERO_DOOM_OVERLORD)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = SelfZone();
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  return FieldHasOppMonster() || CanMillAndSearch(duelist);
}

void ActivateDESTINY_HERO_DOOM_OVERLORD(void)
{
  u8 duelist;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(DESTINY_HERO_DOOM_OVERLORD, 8);
  if (IsDuelOver() == TRUE)
    return;

  if (!FieldHasOppMonster()) {
    DoMillAndSearch(duelist);
    if (SelfZone() != NULL)
      SelfZone()->unk4 = 1;
    UpdateDuelGfxExceptField();
    return;
  }

  gDuelCursor.destY = gActiveEffect.turnRow;
  gDuelCursor.destX = gActiveEffect.col;

  Duel_SetupPickZone(IsOppMonsterTarget, ResolveBanishTarget, CancelTargeting,
                     AiPickBanishTarget);

  if (WhoseTurn() == DUEL_PLAYER && gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
  /* ponytail: banish-until-Standby = permanent banish; DARK HERO SS lock not wired. */
}
