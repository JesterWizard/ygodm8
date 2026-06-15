#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "mini_card.h"
#include "riryoku.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

#define GRACEFUL_DICE_MAX_ATK 500

static u8 MonsterRowForDuelist(u8 duelist)
{
  return duelist == DUEL_PLAYER ? PLAYER_MONSTER_ROW : OPPONENT_MONSTER_ROW;
}

static u16 GetMonsterCurrentAtk(struct DuelCard *zone)
{
  u16 atk;

  gStatMod.card = zone->id;
  gStatMod.field = gDuel.field;
  gStatMod.stage = GetFinalStage(zone);
  gSetFinalStatZone = zone;
  SetFinalStat(&gStatMod);
  atk = gCardInfo.atk;
  gSetFinalStatZone = NULL;
  return atk;
}

static void MultiplyLowAtkMonstersByRoll(u8 duelist, u8 diceRoll)
{
  u8 i;
  u8 monsterRow = MonsterRowForDuelist(duelist);

  if (diceRoll <= 1)
    return;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gFixedZones[monsterRow][i];
    u16 atk;
    s16 delta;

    if (zone->id == CARD_NONE || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
      continue;

    atk = GetMonsterCurrentAtk(zone);
    if (atk == 0 || atk > GRACEFUL_DICE_MAX_ATK)
      continue;

    delta = (s16)((u32)atk * (u32)(diceRoll - 1));
    if (delta > 0)
      AddRiryokuAtkDelta(zone, delta);
  }
}

APPEND_TEXT void EffectGracefulDice(void)
{
  u8 diceRoll;
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  diceRoll = RandRangeU8(1, 6);
  MultiplyLowAtkMonstersByRoll(WhoseTurn(), diceRoll);
  RefreshFieldMonsterStatOverlays();

  ClearZoneAndSendMonToGraveyard(spellZone, ACTIVE_DUELIST);
  UpdateDuelGfxExceptField();

  Duel_ShowEffectText(GRACEFUL_DICE);
}
