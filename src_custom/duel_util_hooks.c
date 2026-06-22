#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "card_passives.h"
#include "custom_decks/custom_decks.h"
#include "dynamic_equip.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "solemn_wishes.h"
#include "drop_off.h"
#include "generated/duelist_decks_generated.inc"

extern int NumCardsInDeck(unsigned char);
extern struct DuelDeck gDuelDecks[2];
extern void DeclareLoser(unsigned char);
void InitCardsForDuelDeck(unsigned char, unsigned short *);
void InitDuelDeck(unsigned char, unsigned char);

static void CopyDuelDeckCards(unsigned char duelist, const unsigned short *deck) {
  unsigned i;

  for (i = 0; i < 40; i++)
    gDuelDecks[duelist].cards[i] = deck[i];
}


static inline u8 sub_8052268_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 0)
    if (y >= -8)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_8052298_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 8)
    if (x >= 0)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522C0_inline(int y, int x) {
  u8 temp = 0;
  if (y <= 8)
    if (y >= 0)
      temp = 1;
  if (x <= 4)
    if (x >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

static inline u8 sub_80522E8_inline(int y, int x) {
  u8 temp = 0;
  if (x <= 0)
    if (x >= -8)
      temp = 1;
  if (y <= 4)
    if (y >= -4)
      temp |= 2;
  if (temp == 3)
    return 1;
  return 0;
}

s8 GetObjectIdInFrontOfPlayer(u8 x, u8 y, u8 playerDirection) {
  u8 i, objExists;

  for (i = 1; i < 15; i++) {
    switch (playerDirection) {
      case 0:
        objExists = sub_8052268_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 1:
        objExists = sub_8052298_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      case 2:
        objExists = sub_80522C0_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
      default:
        objExists = sub_80522E8_inline(y - gOverworld.objects[i].y, x - gOverworld.objects[i].x);
        break;
    }
    if (objExists)
      return i;
  }
  return -1;
}

LYN_REPLACE_CHECK(InitDuelDeck);
void InitDuelDeck__Replacement(unsigned char duelist, u16 duelistId) {
  const u16 *deck;

  if (duelist == DUEL_PLAYER)
    AiMemory_Reset();

  if (!duelistId)
    deck = gDeckMenu.cards; // player deck
  else {
    switch (GetTalkingUnitSprite()) {
      case SPRITE_TEA:
        deck = TeaCustomDeck_GetDuelDeck();
        break;
      default: {
        const u16 *manifestDeck = GetManifestDuelDeck(gDuelData.opponent);

        deck = manifestDeck != NULL ? manifestDeck : gDuelData.duelist.deck;
        break;
      }
    }
  }

  if (duelistId != 0 && gRuntimeConfig.opponent_deck_card_id != CARD_NONE) {
    u16 opponentOverrideDeck[40];
    u8 i;

    for (i = 0; i < 40; i++)
      opponentOverrideDeck[i] = gRuntimeConfig.opponent_deck_card_id;
    InitCardsForDuelDeck(duelist, opponentOverrideDeck);
    return;
  }

  InitCardsForDuelDeck(duelist, (unsigned short *)deck);
}

LYN_REPLACE_CHECK(NumFaceUpMatchingAttributeInRow);
unsigned NumFaceUpMatchingAttributeInRow__Replacement(unsigned char turnRow, unsigned char attribute) {
  u8 i, count = 0;

  if (gRuntimeConfig.disable_element_system == TRUE)
    return 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gTurnZones[turnRow][i]->id == CARD_NONE || !gTurnZones[turnRow][i]->isFaceUp)
      continue;
    SetCardInfo(gTurnZones[turnRow][i]->id);
    if (gCardInfo.attribute == attribute)
      count++;
  }

  return count;
}

LYN_REPLACE_CHECK(HighestAtkMonInRowExceptGodCards);
int HighestAtkMonInRowExceptGodCards__Replacement(struct DuelCard **zonePtr) {
  unsigned char zoneIndex = 0;
  signed char i;
  int highestAtk = -1;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if ((*zonePtr)->id == CARD_NONE) {
      zonePtr++;
      continue;
    }
    if (IsGodCard((*zonePtr)->id) == 1 || IsImmuneToControlSwitch((*zonePtr)->id)) {
      zonePtr++;
      continue;
    }
    gStatMod.card = (*zonePtr)->id;
    gStatMod.field = gDuel.field;
    gStatMod.stage = GetFinalStage(*zonePtr);
    SetFinalStat(&gStatMod);
    if (gCardInfo.atk > highestAtk) {
      highestAtk = gCardInfo.atk;
      zoneIndex = i;
    }
    zonePtr++;
  }
  return (signed char)zoneIndex;
}

LYN_REPLACE_CHECK(NumEmptyZonesAndGodCardsInRow);
int NumEmptyZonesAndGodCardsInRow__Replacement(struct DuelCard **zonePtr) {
  signed char count = 0;
  unsigned char i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    unsigned short currentCardId = (*zonePtr++)->id;

    if (IsGodCard(currentCardId) == TRUE || IsImmuneToControlSwitch(currentCardId))
      currentCardId = CARD_NONE;
    if (currentCardId == CARD_NONE)
      count++;
  }
  return count;
}

LYN_REPLACE_CHECK(ZoneHasEquipSpell);
unsigned ZoneHasEquipSpell__Replacement(struct DuelCard *zone)
{
  if (IsActiveDynamicEquipSpellZone(zone))
    return FALSE;

  return GetTypeGroup(zone->id) == TYPE_GROUP_SPELL && GetSpellType(zone->id) == SPELL_TYPE_EQUIP;
}

LYN_REPLACE_CHECK(ZoneHasTrapCard);
unsigned ZoneHasTrapCard__Replacement(struct DuelCard *zone)
{
  if (EmbodimentOfApophisZoneIsTrapForm(zone))
    return TRUE;

  return zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_TRAP;
}

LYN_REPLACE_CHECK(ZoneHasUnlockedMonsterCard);
unsigned ZoneHasUnlockedMonsterCard__Replacement(struct DuelCard *zone)
{
  if (EmbodimentOfApophisZoneIsMonsterForm(zone))
    return !zone->isLocked;

  if (OjamaTrioZoneIsMonsterForm(zone))
    return !zone->isLocked;

  return zone->id != CARD_NONE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER && !zone->isLocked;
}

LYN_REPLACE_CHECK(TryDrawingCard);
void TryDrawingCard__Replacement(unsigned turn) {
  unsigned char i;
  unsigned short cardDrawn;
  unsigned char turn_u8 = turn;

  if (turn_u8 == DUEL_PLAYER && gDuelDecks[turn_u8].cardsDrawn == 0) {
    u8 slot;
    u16 cardId;
    u8 appliedSlots[MAX_ZONES_IN_ROW];
    u16 configuredCards[MAX_ZONES_IN_ROW] = {
      gRuntimeConfig.card_in_hand_1,
      gRuntimeConfig.card_in_hand_2,
      gRuntimeConfig.card_in_hand_3,
      gRuntimeConfig.card_in_hand_4,
      gRuntimeConfig.card_in_hand_5
    };
    u16 deckSize = NumCardsInDeck(turn_u8);

    for (slot = 0; slot < MAX_ZONES_IN_ROW; slot++)
      appliedSlots[slot] = FALSE;

    for (slot = 0; slot < MAX_ZONES_IN_ROW; slot++) {
      cardId = configuredCards[slot];
      if (cardId == CARD_NONE)
        continue;

      // If card isn't in the deck at all, add it — first empty slot, or displace the last card
      for (i = 0; i < deckSize; i++) {
        if (gDuelDecks[turn_u8].cards[i] == cardId)
          break;
      }
      if (i >= deckSize) {
        for (i = 0; i < deckSize; i++) {
          if (gDuelDecks[turn_u8].cards[i] == CARD_NONE) {
            gDuelDecks[turn_u8].cards[i] = cardId;
            break;
          }
        }
        if (i >= deckSize && deckSize > 0)
          gDuelDecks[turn_u8].cards[deckSize - 1] = cardId; // full deck — overwrite last slot
      }

      // Now swap it to the top slot so it gets drawn in the opening hand
      for (i = 0; i < deckSize; i++) {
        if (i < slot && appliedSlots[i])
          continue;
        if (gDuelDecks[turn_u8].cards[i] != cardId)
          continue;

        gDuelDecks[turn_u8].cards[i] = gDuelDecks[turn_u8].cards[slot];
        gDuelDecks[turn_u8].cards[slot] = cardId;
        appliedSlots[slot] = TRUE;
        break;
      }
    }
  }

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (gDuel.hands[turn_u8][i].id != CARD_NONE)
      continue;
    if ((unsigned char)NumCardsInDeck(turn_u8) < gDuelDecks[turn_u8].cardsDrawn)
      cardDrawn = CARD_NONE;
    else {
      cardDrawn = gDuelDecks[turn_u8].cards[gDuelDecks[turn_u8].cardsDrawn];
      gDuelDecks[turn_u8].cardsDrawn++;
    }
    if (cardDrawn != CARD_NONE) {
      gDuel.hands[turn_u8][i].id = cardDrawn;
      TryApplySolemnWishesOnDraw(turn_u8, cardDrawn, i);
      if (gDrawPhaseNormalDrawActive)
        TryApplyDropOffOnDrawPhaseDraw(turn_u8, i);
    } else
      DeclareLoser(turn_u8); // deck out
    break;
  }
}
