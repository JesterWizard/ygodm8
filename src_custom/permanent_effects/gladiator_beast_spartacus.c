#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"

static const char sGladiatorBeastName[] APPEND_RODATA = "Gladiator Beast";

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

static u8 IsGladiatorBeastEquipSpell(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_SPELL)
    return FALSE;

  if (GetSpellType(cardId) != SPELL_TYPE_EQUIP)
    return FALSE;

  return Duel_CardNameContains(cardId, sGladiatorBeastName);
}

static u16 FindGladiatorBeastEquipInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsGladiatorBeastEquipSpell(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char ShouldActivateGLADIATOR_BEAST_SPARTACUS(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != GLADIATOR_BEAST_SPARTACUS)
    return FALSE;

  if (gActiveEffect.turnRow != ACTIVE_DUELIST_MONSTER_ROW
      && gActiveEffect.turnRow != INACTIVE_DUELIST_MONSTER_ROW)
    return FALSE;

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone == NULL || zone->unk4 != 0)
    return FALSE;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  if (FirstEmptyZoneInRow(gTurnHands[duelist]) < 0)
    return FALSE;

  return FindGladiatorBeastEquipInDeck(duelist) != CARD_NONE;
}

void ActivateGLADIATOR_BEAST_SPARTACUS(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 equipId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(GLADIATOR_BEAST_SPARTACUS, 8);
  if (IsDuelOver() == TRUE)
    return;

  equipId = FindGladiatorBeastEquipInDeck(duelist);
  if (equipId != CARD_NONE)
    Duel_AddDeckCardToHand(duelist, equipId, TRUE);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: Hoplomus-only SS + GB tag-out need summon/battle-end hooks. */
}
