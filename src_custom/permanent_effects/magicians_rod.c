#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "summon_tribute.h"

static const char sDarkMagicianName[] APPEND_RODATA = "Dark Magician";

static const u16 sDmMentionSupport[] APPEND_RODATA = {
  DARK_MAGICIAN,
  DARK_MAGICIAN_GIRL,
  DARK_MAGICIAN_GIRL_THE_DRAGON_KNIGHT,
  THE_DARK_MAGICIANS,
  MAGICIANS_ROD,
  DARK_MAGIC_CURTAIN,
  THOUSAND_KNIVES,
  SAGES_STONE,
  DEDICATION_THROUGH_LIGHT_AND_DARKNESS,
  DARK_MAGIC_ATTACK,
  DARK_MAGIC_VEIL,
  DARK_MAGICAL_CIRCLE,
  BOND_BETWEEN_TEACHER_AND_STUDENT,
  DARK_BURNING_ATTACK,
  DARK_BURNING_MAGIC,
  ILLUSION_MAGIC,
  MAGICIAN_NAVIGATION,
  SECRETS_OF_DARK_MAGIC,
  ETERNAL_SOUL,
  DARK_MAGIC_RITUAL,
  DARK_MAGIC_INHERITANCE,
};

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

static u8 MentionsDarkMagician(u16 cardId)
{
  u8 i;

  if (cardId == CARD_NONE)
    return FALSE;

  if (cardId == DARK_MAGICIAN)
    return TRUE;

  for (i = 0; i < ARRAY_COUNT(sDmMentionSupport); i++) {
    if (cardId == sDmMentionSupport[i])
      return TRUE;
  }

  return Duel_CardNameContains(cardId, sDarkMagicianName);
}

static u8 IsDmMentionSpellTrap(u16 cardId)
{
  if (GetTypeGroup(cardId) != TYPE_GROUP_SPELL && GetTypeGroup(cardId) != TYPE_GROUP_TRAP)
    return FALSE;

  return MentionsDarkMagician(cardId);
}

static u16 FindDmMentionSpellTrapInDeck(u8 turnDuelist)
{
  u8 fixedDuelist = FixedDuelistForTurnDuelist(turnDuelist);
  u8 deckSize = NumCardsInDeck(fixedDuelist);
  u8 top = gDuelDecks[fixedDuelist].cardsDrawn;
  u8 i;

  for (i = top; i < deckSize; i++) {
    u16 cardId = gDuelDecks[fixedDuelist].cards[i];

    if (IsDmMentionSpellTrap(cardId))
      return cardId;
  }

  return CARD_NONE;
}

unsigned char ShouldActivateMAGICIANS_ROD(void)
{
  struct DuelCard *zone;
  u8 duelist;

  if (gActiveEffect.cardId != MAGICIANS_ROD)
    return FALSE;

  if (GetPendingTributeSummonCardId() != MAGICIANS_ROD)
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

  return FindDmMentionSpellTrapInDeck(duelist) != CARD_NONE;
}

void ActivateMAGICIANS_ROD(void)
{
  u8 duelist;
  struct DuelCard *zone;
  u16 cardId;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);

  Duel_ShowEffectTextTyped(MAGICIANS_ROD, 8);
  if (IsDuelOver() == TRUE)
    return;

  cardId = FindDmMentionSpellTrapInDeck(duelist);
  if (cardId != CARD_NONE)
    Duel_AddDeckCardToHand(duelist, cardId, TRUE);

  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];
  if (zone != NULL)
    zone->unk4 = 1;
  /* ponytail: GY tribute Spellcaster → add this needs opp-turn quick hook. */
}
