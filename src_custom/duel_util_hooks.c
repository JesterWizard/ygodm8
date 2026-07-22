#include "global.h"
#include "common-chax.h"
#include "ai_decision.h"
#include "card_passives.h"
#include "constants/card_ids.h"
#include "configs/runtime.h"
#include "custom_decks/custom_decks.h"
#include "dynamic_equip.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "solemn_wishes.h"
#include "appropriate.h"
#include "drop_off.h"
#include "destiny_hero_dasher.h"
#include "shard_of_greed.h"
#include "tethys_goddess_of_light.h"
#include "six_card_hand.h"
#include "generated/duelist_decks_generated.inc"

extern int NumCardsInDeck(unsigned char);
extern struct DuelDeck gDuelDecks[2];
extern void DeclareLoser(unsigned char);
void InitCardsForDuelDeck(unsigned char, unsigned short *);
void InitDuelDeck(unsigned char, unsigned char);
void ExtraDeck_AddCard(u16 cardId);
void ExtraDeck_FillWithCard(u16 cardId);
u8 ExtraDeck_GetCardQty(u16 cardId);

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
  u16 deckOverrideCardId = CARD_NONE;

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

  if (duelistId == 0 && gRuntimeConfig.player_deck_card_id != CARD_NONE)
    deckOverrideCardId = gRuntimeConfig.player_deck_card_id;
  else if (duelistId != 0 && gRuntimeConfig.opponent_deck_card_id != CARD_NONE)
    deckOverrideCardId = gRuntimeConfig.opponent_deck_card_id;

  if (deckOverrideCardId != CARD_NONE) {
    u16 overrideDeck[40];
    u8 i;

    for (i = 0; i < 40; i++)
      overrideDeck[i] = deckOverrideCardId;
    InitCardsForDuelDeck(duelist, overrideDeck);
  } else {
    InitCardsForDuelDeck(duelist, (unsigned short *)deck);
  }

  if (duelistId == 0 && gRuntimeConfig.enable_extra_deck
      && gRuntimeConfig.player_extra_deck_card_id != CARD_NONE)
    ExtraDeck_FillWithCard(gRuntimeConfig.player_extra_deck_card_id);
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

    /* Board-wipe AI (Raigeki/Dark Hole) treats destruction-immune monsters as empty.
     * Control-switch immunity alone must not count — Mataza still dies to Raigeki. */
    if (IsGodCard(currentCardId) == TRUE
        || IsImmuneToHarmfulTargetedEffectsOnField(currentCardId, ACTIVE_DUELIST_MONSTER_ROW))
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

      /* Plant copies for the opening hand. If the card was not already in the deck,
       * plant two: one is drawn, one stays for deck-search effects (Blazeman, etc.). */
      {
        u8 copiesInDeck = 0;
        u8 needCopies;

        for (i = 0; i < deckSize; i++) {
          if (gDuelDecks[turn_u8].cards[i] == cardId)
            copiesInDeck++;
        }

        needCopies = (copiesInDeck == 0) ? 2 : 1;
        while (copiesInDeck < needCopies && deckSize > 0) {
          u8 planted = FALSE;

          for (i = deckSize; i > 0; i--) {
            u8 idx = i - 1;

            if (idx < MAX_ZONES_IN_ROW && appliedSlots[idx])
              continue;
            if (gDuelDecks[turn_u8].cards[idx] == cardId)
              continue;

            gDuelDecks[turn_u8].cards[idx] = cardId;
            copiesInDeck++;
            planted = TRUE;
            break;
          }

          if (!planted)
            break;
        }
      }

      // Swap an unused copy to this hand slot so it is drawn in the opening hand
      for (i = 0; i < deckSize; i++) {
        if (i < MAX_ZONES_IN_ROW && appliedSlots[i])
          continue;
        if (gDuelDecks[turn_u8].cards[i] != cardId)
          continue;

        gDuelDecks[turn_u8].cards[i] = gDuelDecks[turn_u8].cards[slot];
        gDuelDecks[turn_u8].cards[slot] = cardId;
        appliedSlots[slot] = TRUE;
        break;
      }
    }

    /* Synchro playtest: Junk Synchron in opening hand → seed Stardust ED. */
    if (gRuntimeConfig.enable_extra_deck
        && (gRuntimeConfig.card_in_hand_1 == JUNK_SYNCHRON
            || gRuntimeConfig.card_in_hand_2 == JUNK_SYNCHRON
            || gRuntimeConfig.card_in_hand_3 == JUNK_SYNCHRON)
        && ExtraDeck_GetCardQty(STARDUST_DRAGON) == 0) {
      ExtraDeck_AddCard(STARDUST_DRAGON);
    }

    /* XYZ playtest: three Level 4s → seed Gagagigo the Risen ED. */
    if (gRuntimeConfig.enable_extra_deck
        && gRuntimeConfig.card_in_hand_1 == MYSTICAL_ELF
        && gRuntimeConfig.card_in_hand_2 == BATTLE_OX
        && gRuntimeConfig.card_in_hand_3 == CELTIC_GUARDIAN
        && ExtraDeck_GetCardQty(GAGAGIGO_THE_RISEN) == 0) {
      ExtraDeck_AddCard(GAGAGIGO_THE_RISEN);
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
      TryApplyTethysGoddessOfLightOnDraw(turn_u8, cardDrawn, i);
      TryApplyAppropriateOnDraw(turn_u8);
      if (gDrawPhaseNormalDrawActive) {
        TryApplyDropOffOnDrawPhaseDraw(turn_u8, i);
        TryApplyDestinyHeroDasherOnDraw(turn_u8, cardDrawn, i);
        ShardOfGreed_OnNormalDraw(turn_u8);
      }
    } else
      DeclareLoser(turn_u8); // deck out
    return;
  }

  if (IsExpandedCardHandEnabled()) {
    for (i = 0; i < MAX_HAND_EXTRA; i++) {
      if (gHandExtraSlots[turn_u8][i].id != CARD_NONE)
        continue;
      if ((unsigned char)NumCardsInDeck(turn_u8) < gDuelDecks[turn_u8].cardsDrawn)
        cardDrawn = CARD_NONE;
      else {
        cardDrawn = gDuelDecks[turn_u8].cards[gDuelDecks[turn_u8].cardsDrawn];
        gDuelDecks[turn_u8].cardsDrawn++;
      }
      if (cardDrawn != CARD_NONE) {
        u8 handSlot = HAND_SLOT_FIRST_EXTRA + i;

        gHandExtraSlots[turn_u8][i].id = cardDrawn;
        TryApplySolemnWishesOnDraw(turn_u8, cardDrawn, handSlot);
        TryApplyTethysGoddessOfLightOnDraw(turn_u8, cardDrawn, handSlot);
        TryApplyAppropriateOnDraw(turn_u8);
        if (gDrawPhaseNormalDrawActive) {
          TryApplyDropOffOnDrawPhaseDraw(turn_u8, handSlot);
          TryApplyDestinyHeroDasherOnDraw(turn_u8, cardDrawn, handSlot);
          ShardOfGreed_OnNormalDraw(turn_u8);
        }
      } else
        DeclareLoser(turn_u8);
      return;
    }
  }
}

LYN_REPLACE_CHECK(NumCardMatchesInRow);
int NumCardMatchesInRow__Replacement(struct DuelCard **zonePtr, unsigned short cardId)
{
  signed char count = 0;
  unsigned char i;
  u8 fixedDuelist;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if ((*zonePtr++)->id == cardId)
      count++;
  }

  if (!IsExpandedCardHandEnabled())
    return count;

  /* Rewind: zonePtr advanced past the row; recover via hand-row identity. */
  zonePtr -= MAX_ZONES_IN_ROW;
  fixedDuelist = ExpandedHand_FixedDuelistForHandRow(zonePtr);
  if (fixedDuelist != 0xFF) {
    for (i = 0; i < MAX_HAND_EXTRA; i++) {
      if (gHandExtraSlots[fixedDuelist][i].id == cardId)
        count++;
    }
  }

  return count;
}

LYN_REPLACE_CHECK(FirstEmptyZoneInRow);
signed char FirstEmptyZoneInRow__Replacement(struct DuelCard **zonePtr)
{
  unsigned char i;
  u8 fixedDuelist;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (zonePtr[i]->id == CARD_NONE)
      return (signed char)i;
  }

  if (!IsExpandedCardHandEnabled())
    return 0;

  fixedDuelist = ExpandedHand_FixedDuelistForHandRow(zonePtr);
  if (fixedDuelist != 0xFF) {
    for (i = 0; i < MAX_HAND_EXTRA; i++) {
      if (gHandExtraSlots[fixedDuelist][i].id == CARD_NONE)
        return (signed char)(HAND_SLOT_FIRST_EXTRA + i);
    }
  }

  return 0;
}
