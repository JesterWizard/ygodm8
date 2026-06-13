#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "player_decks.h"
#include "copycat.h"
#include "cost_down.h"
#include "constants/spell_effects.h"
#include "custom_field_spell.h"
#include "embodiment_of_apophis.h"
#include "ojama_trio.h"
#include "riryoku.h"

#include "generated/field_spell_stat_mods_generated.inc"

extern const u16 gCardAtks[];
extern const u16 gCardDefs[];
extern const u8 gCardAttributes[];
extern const u8 gCardLevels[];
extern const u8 gCardTypes[];
extern const u8 gCardColors[];
extern const u8 gCardMagicEffect[];
extern const u8 gCardMonsterEffects[];
extern const u8 gCardTrapEffect[];
extern u8 *gCardNames[];
extern unsigned char *gUnk8F985E0[];
extern u8 gUnk8094C37[];
extern u8 gUnk8094CC3[];
extern u8 gUnk8094FE4[NUM_FIELDS][NUM_CARD_TYPES];
extern u8 gDuelistLevelTooLowText[];
extern unsigned gDuelistLevel;
extern s8 gE0CFF4[];
u32 GetDuelistLevel(void);
extern u8 *g8E0CD10;
extern struct {
  u8 *unk0;
  u32 unk4;
} g80D2D00[];
extern u32 gLfsrState;
extern void (*g20245AC)(int, u8 *, int);
unsigned short GetNthCardOnScreen(u8);
void SyncAllCustomTrunkCardQtyMirrorsToVanilla(void);
int GetTrunkCardQty(unsigned short);
int sub_80588C4(u8 *, int, int);
void sub_800BD44(void);
void sub_800BDA0(void);
void ScalePriceToQty(void);
void sub_80327C8(void);
void sub_803519C(void);
void sub_8030C14(void);
void sub_8030CA8(void);
u8 LfsrNextBit(void);
u8 LfsrNextByte(void);

typedef struct {
  const u16 *cardIds;
  u8 cardCount;
  u8 unk1E;
} CardEffectDispatchOverride;

static const u16 sZeroUnk1ECardIds[] __attribute__((section(".text"))) = {
  SORCERER_OF_DARK_MAGIC,
  MONSTER_TAMER,
};

static const CardEffectDispatchOverride sCardEffectDispatchOverrides[] __attribute__((section(".text"))) = {
  {
    .cardIds = sZeroUnk1ECardIds,
    .cardCount = ARRAY_COUNT(sZeroUnk1ECardIds),
    .unk1E = 0,
  },
};

static u8 GetCardEffectDispatchOverride(u16 id) {
  u8 i;
  u8 j;

  if (id >= NUM_TOTAL_CARDS)
    return 0;

  for (i = 0; i < ARRAY_COUNT(sCardEffectDispatchOverrides); i++) {
    const CardEffectDispatchOverride *override = &sCardEffectDispatchOverrides[i];

    for (j = 0; j < override->cardCount; j++) {
      if (override->cardIds[j] == id)
        return override->unk1E;
    }
  }

  return gUnk8094CC3[id];
}

#define gShieldAndSwordActive (*(u8 *)0x02022EBC)
#define CARD_COST_TABLE_COUNT NUM_TOTAL_CARDS
#define COST_SEED_MAGIC_0 'C'
#define COST_SEED_MAGIC_1 'S'
#define COST_SEED_MAGIC_2 'T'
#define COST_SEED_MAGIC_3 '1'
#define COST_SEED_RECORD_SIZE 8
#define COST_SEED_FLASH_PRIMARY ((int)&gCostSeedFlashPrimary)
#define COST_SEED_FLASH_BACKUP ((int)&gCostSeedFlashBackup)

extern u32 gCostEntropyState;
static u32 *const sCostEntropyState = &gCostEntropyState;

static u32 XorShift32(u32 seed) {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  if (seed == 0)
    seed = 1;
  return seed;
}

static u32 ReadStoredCostSeed(void) {
  if (sStoredCostSeedRecord[0] != COST_SEED_MAGIC_0
      || sStoredCostSeedRecord[1] != COST_SEED_MAGIC_1
      || sStoredCostSeedRecord[2] != COST_SEED_MAGIC_2
      || sStoredCostSeedRecord[3] != COST_SEED_MAGIC_3)
    return 0;

  return (u32)sStoredCostSeedRecord[4]
      | ((u32)sStoredCostSeedRecord[5] << 8)
      | ((u32)sStoredCostSeedRecord[6] << 16)
      | ((u32)sStoredCostSeedRecord[7] << 24);
}

static void WriteStoredCostSeed(u32 seed) {
  sStoredCostSeedRecord[0] = COST_SEED_MAGIC_0;
  sStoredCostSeedRecord[1] = COST_SEED_MAGIC_1;
  sStoredCostSeedRecord[2] = COST_SEED_MAGIC_2;
  sStoredCostSeedRecord[3] = COST_SEED_MAGIC_3;
  sStoredCostSeedRecord[4] = (u8)seed;
  sStoredCostSeedRecord[5] = (u8)(seed >> 8);
  sStoredCostSeedRecord[6] = (u8)(seed >> 16);
  sStoredCostSeedRecord[7] = (u8)(seed >> 24);
}

static u32 ReadStoredCostSeedFromFlash(int address) {
  u8 record[COST_SEED_RECORD_SIZE];

  if (g20245AC == NULL)
    return 0;

  g20245AC(address, record, COST_SEED_RECORD_SIZE);
  if (record[0] != COST_SEED_MAGIC_0
      || record[1] != COST_SEED_MAGIC_1
      || record[2] != COST_SEED_MAGIC_2
      || record[3] != COST_SEED_MAGIC_3)
    return 0;

  return (u32)record[4]
      | ((u32)record[5] << 8)
      | ((u32)record[6] << 16)
      | ((u32)record[7] << 24);
}

static void WriteStoredCostSeedToFlash(int address, u32 seed) {
  u8 record[COST_SEED_RECORD_SIZE];

  record[0] = COST_SEED_MAGIC_0;
  record[1] = COST_SEED_MAGIC_1;
  record[2] = COST_SEED_MAGIC_2;
  record[3] = COST_SEED_MAGIC_3;
  record[4] = (u8)seed;
  record[5] = (u8)(seed >> 8);
  record[6] = (u8)(seed >> 16);
  record[7] = (u8)(seed >> 24);
  sub_80588C4(record, address, COST_SEED_RECORD_SIZE);
}

static u32 GetPersistentCostSeed(void) {
  u32 seed = ReadStoredCostSeed();

  if (seed != 0)
    return seed;

  seed = ReadStoredCostSeedFromFlash(COST_SEED_FLASH_PRIMARY);
  if (seed == 0)
    seed = ReadStoredCostSeedFromFlash(COST_SEED_FLASH_BACKUP);

  if (seed != 0) {
    WriteStoredCostSeed(seed);
    return seed;
  }

  seed = *sCostEntropyState;
  seed ^= gLfsrState;
  seed ^= ((u32)REG_VCOUNT << 16);
  seed ^= REG_KEYINPUT;
  seed ^= 0x6D2B79F5;
  seed = XorShift32(seed);
  WriteStoredCostSeed(seed);
  WriteStoredCostSeedToFlash(COST_SEED_FLASH_PRIMARY, seed);
  WriteStoredCostSeedToFlash(COST_SEED_FLASH_BACKUP, seed);
  return seed;
}

void InitializeRandomizedCardCosts(void) {
  u32 i;
  u32 seed;

  if (gRuntimeConfig.randomize_card_costs_at_start != TRUE) {
    for (i = 0; i < CARD_COST_TABLE_COUNT; i++)
      sRandomizedCardCosts[i] = 0;
    return;
  }

  sRandomizedCardCosts[CARD_NONE] = 0;
  seed = GetPersistentCostSeed();
  for (i = 1; i < CARD_COST_TABLE_COUNT; i++) {
    seed = XorShift32(seed);
    sRandomizedCardCosts[i] = seed % 501;
  }
}

static u32 GetConfiguredCardCost(u16 id) {
  if (id >= NUM_TOTAL_CARDS)
    return 0;

  if (gRuntimeConfig.randomize_card_costs_at_start == TRUE)
    return sRandomizedCardCosts[id];

  return gCardData_NEW[id].cost;
}

u32 GetCardCostForDuelistCheck(u16 cardId) {
  return GetConfiguredCardCost(cardId);
}

u8 CardExceedsCurrentDuelistLevel(u16 cardId) {
  return gDuelistLevel < GetConfiguredCardCost(cardId);
}

void ApplyDuelistLevelTooLowCardDescription(void) {
  if (gCardInfo.cost > gDuelistLevel)
    gCardInfo.description = gDuelistLevelTooLowText;
}

static u8 *GetCardDescription_Hook(const CardData *card, u16 cardId) {
  if (cardId >= NUM_TOTAL_CARDS)
    return gUnk8F985E0[CARD_NONE];
  if (card->description != NULL)
    return (u8 *)card->description;

  return gUnk8F985E0[cardId];
}

static unsigned short GetStageModifiedStat_Hook(unsigned short stat, s8 stage) {
  long finalStat;

  if (stat == 0xFFFF)
    return stat;

  finalStat = stage * 500 + stat;

  if (finalStat <= 0)
    stat = 0;
  else if (finalStat > 0xFFFE)
    stat = 0xFFFE;
  else
    stat = finalStat;

  return stat;
}

static unsigned short GetFieldModifiedStat_Hook(unsigned short stat, u8 fieldMod) {
  u32 scaled;
  u8 percent;

  if (stat == 0xFFFF)
    return stat;

  percent = gRuntimeConfig.field_stat_change_percent;

  switch (fieldMod) {
    case 0:
    case 2:
    case 4:
      break;
    case 1:
      scaled = (u32)stat * (100 - percent) / 100;
      stat = scaled > 0xFFFE ? 0xFFFE : (u16)scaled;
      break;
    case 3:
      scaled = (u32)stat * (100 + percent) / 100;
      stat = scaled > 0xFFFE ? 0xFFFE : (u16)scaled;
      break;
  }

  return stat;
}

static u8 GetFieldStatModifier(u8 field, u8 type) {
#if NUM_CUSTOM_FIELDS > 0
  if (IsCustomField(field))
    return gCustomFieldStatMods[field - FIRST_CUSTOM_FIELD][type];
#endif
  return gUnk8094FE4[field][type];
}

static u64 GetDynamicShopBasePrice(void) {
  u16 cardId = gShopSelectedCard.cardId;
  u64 basePrice = (u64)gCardData_NEW[cardId].cost * 40;

  if (basePrice == 0)
    basePrice = 1;

  return basePrice;
}

static void ScaleDynamicShopPriceToQty(void) {
  u64 basePrice = GetDynamicShopBasePrice();
  u8 val = gShopSelectedCard.shopQty - 1;

  if (val < 250)
    gShopSelectedCard.buyPrice = basePrice * (251 - gShopSelectedCard.shopQty) / 250;
  else
    gShopSelectedCard.buyPrice = 0;

  if (gShopSelectedCard.buyPrice == 0 && val < 250)
    gShopSelectedCard.buyPrice = 1;

  if (gShopSelectedCard.shopQty < 250)
    gShopSelectedCard.sellPrice = basePrice * (250 - gShopSelectedCard.shopQty) / 5000;
  else
    gShopSelectedCard.sellPrice = basePrice / 5000;

  if (gShopSelectedCard.sellPrice == 0)
    gShopSelectedCard.sellPrice = 1;
}

static void ApplyDuelistLevelShopDiscount(void) {
  u32 level;
  u32 discount;
  u64 discountedPrice;

  if (gRuntimeConfig.discount_shop_costs_by_duelist_level == FALSE || gShopSelectedCard.buyPrice == 0)
    return;

  level = GetDuelistLevel();
  if (gRuntimeConfig.max_duelist_level_at_start == TRUE && level < 999)
    level = 999;
  else if (level > 999)
    level = 999;

  discount = ((level + 99) / 100) * 5;
  if (discount > 50)
    discount = 50;

  discountedPrice = gShopSelectedCard.buyPrice * (100 - discount) / 100;
  if (discountedPrice == 0)
    discountedPrice = 1;

  gShopSelectedCard.buyPrice = discountedPrice;
}

#include "generated/card_name_generated.inc"
#include "embodiment_of_apophis.h"

extern s8 gE0CFDC[];

LYN_REPLACE_CHECK(SetCardInfo);
void SetCardInfo__Replacement(unsigned short id) {
  const CardData *card;
  u8 customCard = 0;

  if (id >= NUM_TOTAL_CARDS)
    id = CARD_NONE;
  else if (gRuntimeConfig.enable_custom_cards_past_800 == FALSE && id >= CUSTOM_CARD_START)
    id = CARD_NONE;
  else if (id >= CUSTOM_CARD_START)
    customCard = 1;

  card = &gCardData_NEW[id];

  gCardInfo.id = id;
  gCardInfo.atk = card->atk;
  gCardInfo.def = card->def;
  gCardInfo.cost = GetConfiguredCardCost(id);
  gCardInfo.attribute = gRuntimeConfig.disable_element_system == TRUE ? ATTRIBUTE_NONE : card->attribute;
  gCardInfo.level = card->level;
  gCardInfo.type = card->type;
  gCardInfo.color = card->color;
  gCardInfo.spellEffect = card->spellEffect;
  gCardInfo.monsterEffect = card->monsterEffect;
  gCardInfo.trapEffect = card->trapEffect;
  gCardInfo.ritualEffect = gUnk8094C37[gCardInfo.spellEffect];
  gCardInfo.unk1E = customCard ? 0 : GetCardEffectDispatchOverride(id);
  gCardInfo.name = GetCardName_Hook(id);
  gCardInfo.nameUnused = GetCardName_Hook(id);
  gCardInfo.description = GetCardDescription_Hook(card, id);
}

LYN_REPLACE_CHECK(GetSpellType);
int GetSpellType__Replacement(u16 cardId) {
  SetCardInfo(cardId);
  if (cardId == JAM_BREEDING_MACHINE || cardId == CHAIN_ENERGY || cardId == TOLL
      || cardId == THE_DARK_DOOR || cardId == DARK_ROOM_OF_NIGHTMARE
      || cardId == WAVE_MOTION_CANNON || cardId == PYRAMID_OF_LIGHT
      || cardId == SWORDS_OF_REVEALING_LIGHT || cardId == GUARDIAN_TREASURE)
    return SPELL_TYPE_NORMAL;

  if (cardId == MAGE_POWER || cardId == UNITED_WE_STAND)
    return SPELL_TYPE_EQUIP;

  if (gCardInfo.spellEffect >= SPELL_EFFECT_FOREST
      && gCardInfo.spellEffect <= SPELL_EFFECT_YAMI)
    return SPELL_TYPE_NORMAL;

  return gE0CFF4[gCardInfo.spellEffect];
}

LYN_REPLACE_CHECK(ScalePriceToQty);
void ScalePriceToQty__Replacement(void) {
  if (gRuntimeConfig.dynamic_card_shop_costs == TRUE)
    ScaleDynamicShopPriceToQty();
  else {
    sub_800BD44();
    sub_800BDA0();
  }

  ApplyDuelistLevelShopDiscount();
}

u8 ZoneShowsCombatStats(const struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return TRUE;

  if (EmbodimentOfApophisZoneIsMonsterForm(zone))
    return TRUE;

  if (OjamaTrioZoneIsMonsterForm(zone))
    return TRUE;

  return FALSE;
}

void ApplyFieldZoneStatsToCardInfo(struct DuelCard *zone)
{
  struct StatMod statMod;
  s8 stage;
  u8 fieldMod;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  statMod.card = zone->id;
  statMod.field = gDuel.field;
  statMod.stage = 0;

  SetCardInfo__Replacement(zone->id);
  ApplyEmbodimentOfApophisCardInfoOverridesForStatMod(&statMod);
  ApplyOjamaTrioCardInfoOverridesForStatMod(&statMod);

  if (zone->id == COPYCAT && gComputingCopycatStats == FALSE) {
    ApplyCopycatStatsToCardInfo(&statMod);
    return;
  }

  if (!ZoneShowsCombatStats(zone))
    return;

  stage = GetFinalStage(zone);
  fieldMod = GetFieldStatModifier(gDuel.field, gCardInfo.type);
  gCardInfo.atk = GetStageModifiedStat_Hook(
      GetFieldModifiedStat_Hook(gCardInfo.atk, fieldMod), stage);
  gCardInfo.def = GetStageModifiedStat_Hook(
      GetFieldModifiedStat_Hook(gCardInfo.def, fieldMod), stage);

  if (gShieldAndSwordActive == TRUE && GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER) {
    u16 atk = gCardInfo.atk;
    gCardInfo.atk = gCardInfo.def;
    gCardInfo.def = atk;
  }

  ApplyRiryokuAtkDeltaToCardInfo(zone);
}

LYN_REPLACE_CHECK(SetFinalStat);
void SetFinalStat__Replacement(struct StatMod *ptr) {
  SetCardInfo__Replacement(ptr->card);
  ApplyEmbodimentOfApophisCardInfoOverridesForStatMod(ptr);
  ApplyOjamaTrioCardInfoOverridesForStatMod(ptr);

  if (ptr->card == COPYCAT && gComputingCopycatStats == FALSE)
    ApplyCopycatStatsToCardInfo(ptr);
  else if (GetTypeGroup(ptr->card) == TYPE_GROUP_MONSTER
           || (gSetFinalStatZone != NULL
               && gSetFinalStatZone->id == ptr->card
               && (EmbodimentOfApophisZoneIsMonsterForm(gSetFinalStatZone)
                   || OjamaTrioZoneIsMonsterForm(gSetFinalStatZone)))) {
    s8 stage = ptr->stage;

    if (gSetFinalStatZone != NULL && gSetFinalStatZone->id == ptr->card)
      stage = (s8)GetFinalStage(gSetFinalStatZone);

    gCardInfo.atk = GetFieldModifiedStat_Hook(gCardInfo.atk, GetFieldStatModifier(ptr->field, gCardInfo.type));
    gCardInfo.def = GetFieldModifiedStat_Hook(gCardInfo.def, GetFieldStatModifier(ptr->field, gCardInfo.type));
    gCardInfo.atk = GetStageModifiedStat_Hook(gCardInfo.atk, stage);
    gCardInfo.def = GetStageModifiedStat_Hook(gCardInfo.def, stage);
  }

  if (gDuelCursor.currentY == PLAYER_HAND
      && ShouldApplyCostDownForHandSlot(gDuelCursor.currentX, gCardInfo.id))
    gCardInfo.level = GetCostDownAdjustedLevel(gCardInfo.id, gCardInfo.level);

  if (gShieldAndSwordActive == TRUE && GetTypeGroup(gCardInfo.id) == TYPE_GROUP_MONSTER) {
    u16 atk = gCardInfo.atk;
    gCardInfo.atk = gCardInfo.def;
    gCardInfo.def = atk;
  }

  if (gSetFinalStatZone != NULL
      && gSetFinalStatZone->id == ptr->card
      && GetTypeGroup(ptr->card) == TYPE_GROUP_MONSTER)
    ApplyRiryokuAtkDeltaToCardInfo(gSetFinalStatZone);

  gSetFinalStatZone = NULL;
}

LYN_REPLACE_CHECK(sub_80327C8);
void sub_80327C8__Replacement(void) {
  CpuSet(sub_8030C14, (void *)0x03001478, 0x04000040);
  CpuSet(sub_8030CA8, (void *)0x03001578, 0x04000040);
}

void sub_80351F8(void);

LYN_REPLACE_CHECK(sub_803519C);
void sub_803519C__Replacement(void) {
  unsigned r3 = 0, r5 = 0;
  u16 i;

  for (; g80D2D00[r3].unk0; r3++) {
    unsigned long r1;
    unsigned char *dest = g80D2D00[r3].unk0;
    for (r1 = g80D2D00[r3].unk4; r1; r5++, dest++, r1--)
      *dest = ((u8 *)g8E0CD10)[r5];
  }

  InitializeRandomizedCardCosts();
  g20245AC((int)gCustomTrunkCardQtyFlashPrimary, gCustomTrunkCardQty, NUM_CUSTOM_CARDS);
  g20245AC((int)gCustomShopCardQtyFlashPrimary, gCustomShopCardQty, NUM_CUSTOM_CARDS);
  g20245AC((int)gCustomPlayerTempCardQtyFlashPrimary, gCustomPlayerTempCardQty, NUM_CUSTOM_CARDS);

  SyncAllCustomTrunkCardQtyMirrorsToVanilla();
  for (i = 0; i < NUM_CUSTOM_CARDS; i++) {
    SetShopCardQty(CUSTOM_CARD_START + i, gCustomShopCardQty[i]);
    SetPlayerTempCardQty(CUSTOM_CARD_START + i, gCustomPlayerTempCardQty[i]);
  }

}

LYN_REPLACE_CHECK(sub_80351F8);
void sub_80351F8__Replacement(void) {
  unsigned r4 = 0, r6 = 0;

  PlayerDecks_PrepareVanillaSaveBuffer();

  for (; g80D2D00[r4].unk0; r4++) {
    unsigned long r1;
    unsigned char *src = g80D2D00[r4].unk0;
    for (r1 = g80D2D00[r4].unk4; r1; src++, r6++, r1--)
      g8E0CD10[r6] = *src;
  }

  PlayerDecks_RestoreAfterVanillaSaveBuffer();
}

LYN_REPLACE_CHECK(LfsrNextByte);
u8 LfsrNextByte__Replacement(void) {
  u8 value = 0;
  u8 i;

  for (i = 0; i < 8; i++) {
    value <<= 1;
    value |= LfsrNextBit();
  }

  if (gRuntimeConfig.randomize_card_costs_at_start == TRUE) {
    u32 seed = *sCostEntropyState;
    seed ^= gLfsrState;
    seed ^= ((u32)REG_VCOUNT << 16);
    seed ^= REG_KEYINPUT;
    seed ^= (u32)value << 24;
    seed = XorShift32(seed);
    if (seed == 0)
      seed = 1;
    *sCostEntropyState = seed;
  }

  return value;
}

LYN_REPLACE_CHECK(SetCardInfoWithWarning);
void SetCardInfoWithWarning__Replacement(unsigned short *id) {
  SetCardInfo__Replacement(*id);
  ApplyDuelistLevelTooLowCardDescription();
}

LYN_REPLACE_CHECK(TrySelectingAnte);
unsigned char TrySelectingAnte__Replacement(void)
{
  unsigned selectionFailed = 1;
  unsigned short cardId = GetNthCardOnScreen(2);
  unsigned char trunkQty = GetTrunkCardQty(cardId);

  if (!trunkQty)
      return selectionFailed;
  else if (trunkQty < 2
      && gRuntimeConfig.allow_ante_with_one_copy_of_card == FALSE)
        sub_800C32C(); // OneOfAKindAntePrompt();
  else if (IsGodCard(cardId) == 1)
        sub_800C378(); // GodCardAntePrompt();
  else if (!IsNormalAnte(cardId)) {
    if (!LowLevelAntePrompt()) {
      selectionFailed = 0;
      gAnte = cardId;
    }
  }
  else {
    selectionFailed = 0;
    gAnte = cardId;
    PlayMusic(SFX_TRANSITION_TRUNK_TO_DUEL);
  }

  WaitForVBlank();
  return selectionFailed;
}
