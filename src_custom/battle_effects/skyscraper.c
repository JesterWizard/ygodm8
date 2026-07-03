#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/custom_field_spells.h"
#include "custom_field_spell.h"
#include "duel.h"
#include "duel_helpers.h"
#include "skyscraper.h"

#define SKYSCRAPER_BATTLE_ATK_BOOST 1000

struct SkyscraperActionData {
  unsigned short playerCardId;
  unsigned short playerCardAtkOrLifePointsMod;
  unsigned short playerCardDefense;
  unsigned short playerLifePoints;
  unsigned char playerCardAttribute;
  unsigned char playerMonsterRow;
  unsigned char unkA;
  unsigned short opponentCardId;
  unsigned short opponentCardAtkOrLifePointsMod;
  unsigned short opponentCardDefense;
  unsigned short opponentLifePoints;
  unsigned char opponentCardAttribute;
  unsigned char opponentMonsterRow;
  unsigned char unk16;
  unsigned char filler17;
  unsigned char id;
  unsigned char flags;
  unsigned char unk1A;
  unsigned char unk1B;
};

extern struct SkyscraperActionData sActionData;

static u8 IsMonsterBattleAction(u8 id)
{
  return id == 1 || id == 2 || id == 4 || id == 5 || id == 6;
}

static u8 IsPlayerAttackAction(u8 id)
{
  return id == 1 || id == 2 || id == 4;
}

static u8 IsOpponentAttackAction(u8 id)
{
  return id == 5 || id == 6;
}

static u8 SkyscraperMayBoostAttacker(u8 attackerDuelist)
{
  if (gActiveFieldSpellController == FIELD_SPELL_CONTROLLER_NONE)
    return FALSE;
  if (gActiveFieldSpellController != attackerDuelist)
    return FALSE;
  if (WhoseTurn() != attackerDuelist)
    return FALSE;

  return TRUE;
}

void ApplySkyscraperBattleAtkBoost(void)
{
  u8 attackerDuelist;
  u16 attackerCardId;
  u16 *attackerAtk;
  u16 defenderCardId;
  u16 defenderAtk;
  u8 defenderRow;
  u8 defenderCol;
  struct DuelCard *defenderZone;

  if (!IsMonsterBattleAction(sActionData.id))
    return;
  if (gActiveCustomFieldSpellId != CUSTOM_FIELD_SPELL_SKYSCRAPER)
    return;

  if (IsPlayerAttackAction(sActionData.id)) {
    attackerDuelist = DUEL_PLAYER;
    attackerCardId = sActionData.playerCardId;
    attackerAtk = &sActionData.playerCardAtkOrLifePointsMod;
    defenderCardId = sActionData.opponentCardId;
    defenderAtk = sActionData.opponentCardAtkOrLifePointsMod;
    defenderRow = sActionData.opponentMonsterRow;
    defenderCol = sActionData.unk16;
  } else if (IsOpponentAttackAction(sActionData.id)) {
    attackerDuelist = DUEL_OPPONENT;
    attackerCardId = sActionData.opponentCardId;
    attackerAtk = &sActionData.opponentCardAtkOrLifePointsMod;
    defenderCardId = sActionData.playerCardId;
    defenderAtk = sActionData.playerCardAtkOrLifePointsMod;
    defenderRow = sActionData.playerMonsterRow;
    defenderCol = sActionData.unkA;
  } else {
    return;
  }

  if (!SkyscraperMayBoostAttacker(attackerDuelist))
    return;
  if (!Duel_IsElementalHeroCard(attackerCardId) || defenderCardId == CARD_NONE)
    return;

  defenderZone = gFixedZones[defenderRow][defenderCol];
  if (defenderZone == NULL || defenderZone->id != defenderCardId
      || defenderZone->isDefending || defenderAtk <= *attackerAtk)
    return;

  *attackerAtk = Duel_ClampStat((u32)(*attackerAtk) + SKYSCRAPER_BATTLE_ATK_BOOST);
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void Skyscraper_SelfCheck(void)
{
  struct SkyscraperActionData saved = sActionData;
  struct DuelCard savedDefenderZone = gFixedZones[1][2];
  u8 savedController = gActiveFieldSpellController;
  u8 savedTurn = gWhoseTurn;

  gActiveCustomFieldSpellId = CUSTOM_FIELD_SPELL_SKYSCRAPER;
  gActiveFieldSpellController = DUEL_PLAYER;
  gWhoseTurn = DUEL_PLAYER;
  sActionData.id = 1;
  sActionData.playerCardId = ELEMENTAL_HERO_SPARKMAN;
  sActionData.playerCardAtkOrLifePointsMod = 1800;
  sActionData.playerMonsterRow = 2;
  sActionData.unkA = 2;
  sActionData.opponentCardId = SUMMONED_SKULL;
  sActionData.opponentCardAtkOrLifePointsMod = 2500;
  sActionData.opponentMonsterRow = 1;
  sActionData.unk16 = 2;
  gFixedZones[1][2].id = SUMMONED_SKULL;
  gFixedZones[1][2].isDefending = FALSE;
  ApplySkyscraperBattleAtkBoost();
  if (sActionData.playerCardAtkOrLifePointsMod != 2800)
    while (1)
      ;

  gWhoseTurn = DUEL_OPPONENT;
  sActionData.playerCardAtkOrLifePointsMod = 1800;
  ApplySkyscraperBattleAtkBoost();
  if (sActionData.playerCardAtkOrLifePointsMod != 1800)
    while (1)
      ;

  gActiveFieldSpellController = DUEL_OPPONENT;
  gWhoseTurn = DUEL_OPPONENT;
  sActionData.id = 5;
  sActionData.opponentCardId = ELEMENTAL_HERO_SPARKMAN;
  sActionData.opponentCardAtkOrLifePointsMod = 1800;
  sActionData.opponentMonsterRow = 1;
  sActionData.unk16 = 2;
  sActionData.playerCardId = SUMMONED_SKULL;
  sActionData.playerCardAtkOrLifePointsMod = 2500;
  sActionData.playerMonsterRow = 2;
  sActionData.unkA = 2;
  ApplySkyscraperBattleAtkBoost();
  if (sActionData.opponentCardAtkOrLifePointsMod != 1800)
    while (1)
      ;

  sActionData = saved;
  gFixedZones[1][2] = savedDefenderZone;
  gActiveFieldSpellController = savedController;
  gWhoseTurn = savedTurn;
  gActiveCustomFieldSpellId = CUSTOM_FIELD_SPELL_NONE;
}
#endif
