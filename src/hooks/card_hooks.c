#include "global.h"
#include "configs/runtime.h"

extern const u16 gCardAtks[];
extern const u16 gCardDefs[];
extern const u32 gCardCosts[];
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

static unsigned short GetStageModifiedStat_Hook(unsigned short stat, s8 stage) {
  long finalStat = stage * 500 + stat;

  if (finalStat <= 0)
    stat = 0;
  else if (finalStat > 0xFFFE)
    stat = 0xFFFE;
  else
    stat = finalStat;

  return stat;
}

static unsigned short GetFieldModifiedStat_Hook(unsigned short stat, u8 fieldMod) {
  switch (fieldMod) {
    case 0:
    case 2:
    case 4:
      break;
    case 1:
      stat *= 0.7;
      break;
    case 3:
      stat *= 1.3;
      if (stat >= 0xFFFE)
        stat = 0xFFFE;
      break;
  }

  return stat;
}

static u8 *GetCardName_Hook(unsigned short cardId) {
  return gCardNames[cardId];
}

LYN_REPLACE_CHECK(SetCardInfo);
void SetCardInfo__Replacement(unsigned short id) {
  gCardInfo.id = id;
  gCardInfo.atk = gCardAtks_NEW.cards[id];
  gCardInfo.def = gCardDefs_NEW.cards[id];
  gCardInfo.cost = gCardCosts_NEW.cards[id];
  gCardInfo.attribute = gCardAttributes_NEW.cards[id];
  gCardInfo.level = gCardLevels_NEW.cards[id];
  gCardInfo.type = gCardTypes_NEW.cards[id];
  gCardInfo.color = gCardColors_NEW.cards[id];
  gCardInfo.spellEffect = gCardMagicEffect_NEW.cards[id];
  gCardInfo.monsterEffect = gCardMonsterEffects_NEW.cards[id];
  gCardInfo.trapEffect = gCardTrapEffect_NEW.cards[id];
  gCardInfo.ritualEffect = gUnk8094C37[gCardInfo.spellEffect];
  gCardInfo.unk1E = gUnk8094CC3[id];
  gCardInfo.name = GetCardName_Hook(id);
  gCardInfo.nameUnused = GetCardName_Hook(id);
  gCardInfo.description = gUnk8F985E0[id];
}

LYN_REPLACE_CHECK(SetFinalStat);
void SetFinalStat__Replacement(struct StatMod *ptr) {
  SetCardInfo(ptr->card);

  if (gCardInfo.spellEffect == 2) {
    gCardInfo.atk = GetFieldModifiedStat_Hook(gCardInfo.atk, gUnk8094FE4[ptr->field][gCardInfo.type]);
    gCardInfo.def = GetFieldModifiedStat_Hook(gCardInfo.def, gUnk8094FE4[ptr->field][gCardInfo.type]);
    gCardInfo.atk = GetStageModifiedStat_Hook(gCardInfo.atk, ptr->stage);
    gCardInfo.def = GetStageModifiedStat_Hook(gCardInfo.def, ptr->stage);
  }
}

LYN_REPLACE_CHECK(SetCardInfoWithWarning);
void SetCardInfoWithWarning__Replacement(unsigned short *id) {
  SetCardInfo(*id);

  if (gCardInfo.cost > GetDuelistLevel())
    gCardInfo.description = gDuelistLevelTooLowText;
}
