#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

struct AI_Command {
  u16 action;
  u8 zone1Position;
  u8 zone2Position;
  u8 zone3Position;
  u8 zone4Position;
  u8 zone5Position;
  u8 zone6Position;
};

extern struct AI_Command sAI_Command;

void ActivateSpellEffect(void);
void ClearZone(struct DuelCard *zone);
void LockMonsterCardsInRow(unsigned char turnRow);
void sub_800EC68(void);
void sub_800ECC0(void);

static u8 SpellShouldRemainOnFieldAfterActivation(u16 cardId)
{
  return cardId == SWORDS_OF_REVEALING_LIGHT;
}

static void AiActivateNormalSpellFromBackrow(u8 lockMonstersAfterActivation, u8 clearZoneAfterActivation)
{
  u8 row2 = sAI_Command.zone1Position >> 4;
  u8 col2 = sAI_Command.zone1Position & 0xF;
  u16 spellId = gTurnZones[row2][col2]->id;

  gSpellEffectData.id = spellId;
  gSpellEffectData.row1 = row2;
  gSpellEffectData.col1 = col2;
  ActivateSpellEffect();

  if (lockMonstersAfterActivation && gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
    LockMonsterCardsInRow(ACTIVE_DUELIST_HAND);

  if (clearZoneAfterActivation && !SpellShouldRemainOnFieldAfterActivation(spellId))
    ClearZone(gTurnZones[row2][col2]);
}

LYN_REPLACE_CHECK(sub_800EC68);
void sub_800EC68__Replacement(void)
{
  AiActivateNormalSpellFromBackrow(TRUE, TRUE);
}

LYN_REPLACE_CHECK(sub_800ECC0);
void sub_800ECC0__Replacement(void)
{
  AiActivateNormalSpellFromBackrow(FALSE, TRUE);
}
