#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "graveyard_effects.h"

extern unsigned char IsSkillDrainActiveOnField(void);
extern unsigned char TryActivateSkillDrainAndNegateCardId(u16 negatedCardId);

#define GRANADORA_SUMMON_HEAL 1000
#define GRANADORA_DESTRUCTION_DAMAGE 2000

static u8 DuelistForMonsterTurnRow(u8 turnRow)
{
  if (turnRow == ACTIVE_DUELIST_MONSTER_ROW)
    return ACTIVE_DUELIST;
  if (turnRow == INACTIVE_DUELIST_MONSTER_ROW)
    return INACTIVE_DUELIST;
  return ACTIVE_DUELIST;
}

static u8 GraveyardDuelistForTurnRow(u8 turnRow)
{
  if (turnRow == 6)
    return ACTIVE_DUELIST;
  return INACTIVE_DUELIST;
}

static u8 GraveyardMatchesGranadora(u8 turnRow)
{
  if (turnRow == 7)
    return gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard == GRANADORA;

  return gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard == GRANADORA;
}

static u8 FindMonsterTurnRowColForZone(struct DuelCard *zone, u8 *turnRow, u8 *col)
{
  u8 row;

  for (row = INACTIVE_DUELIST_MONSTER_ROW; row <= ACTIVE_DUELIST_MONSTER_ROW; row++) {
    for (*col = 0; *col < MAX_ZONES_IN_ROW; (*col)++) {
      if (gTurnZones[row][*col] == zone) {
        *turnRow = row;
        return TRUE;
      }
    }
  }

  return FALSE;
}

static void ShowGranadoraEffectText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  gCardEffectTextData.cardId = GRANADORA;
  ActivateCardEffectText();
  gHideEffectText = hideEffectText;
}

static void ActivateGranadoraSummon(void)
{
  u8 duelist;
  struct DuelCard *zone;

  duelist = DuelistForMonsterTurnRow(gActiveEffect.turnRow);
  zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

  ShowGranadoraEffectText();
  FlipCardFaceUp(zone);

  if (Duel_ChangeLp(duelist, GRANADORA_SUMMON_HEAL, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  zone->unk4 = 1;
}

static void ActivateGranadoraGraveyard(void)
{
  u8 duelist = GraveyardDuelistForTurnRow(gActiveEffect.turnRow);
  u8 turnDuelist = (gActiveEffect.turnRow == 6) ? ACTIVE_DUELIST : INACTIVE_DUELIST;

  ShowGranadoraEffectText();

  if (Duel_ChangeLp(duelist, -GRANADORA_DESTRUCTION_DAMAGE, TRUE) == DUEL_ACTION_DUEL_OVER)
    return;

  GetGraveCardAndClearGrave(turnDuelist);
}

unsigned char ShouldActivateGranadora(void)
{
  if (gActiveEffect.cardId != GRANADORA)
    return FALSE;

  if (gActiveEffect.turnRow == ACTIVE_DUELIST_MONSTER_ROW
      || gActiveEffect.turnRow == INACTIVE_DUELIST_MONSTER_ROW) {
    struct DuelCard *zone = gTurnZones[gActiveEffect.turnRow][gActiveEffect.col];

    // ponytail: unk4==1 means summon effect already fired; 0/2 are fresh normal/special summon
    return zone->unk4 != 1;
  }

  if (gActiveEffect.turnRow != 6 && gActiveEffect.turnRow != 7)
    return FALSE;

  if (!gGraveyardSendWasFromField)
    return FALSE;

  return GraveyardMatchesGranadora(gActiveEffect.turnRow);
}

void ActivateGranadora(void)
{
  if (gActiveEffect.turnRow == 6 || gActiveEffect.turnRow == 7) {
    ActivateGranadoraGraveyard();
    return;
  }

  ActivateGranadoraSummon();
}

void TryActivateGranadoraOnMonsterPlacement(struct DuelCard *zone)
{
  u8 turnRow;
  u8 col;

  if (zone == NULL || zone->id != GRANADORA || zone->unk4 == 1)
    return;

  if (!FindMonsterTurnRowColForZone(zone, &turnRow, &col))
    return;

  if (IsSkillDrainActiveOnField() && TryActivateSkillDrainAndNegateCardId(GRANADORA))
    return;

  gActiveEffect.turnRow = turnRow;
  gActiveEffect.col = col;
  gActiveEffect.cardId = GRANADORA;

  ResetCardEffectTextData();
  SetCardEffectTextType(8);
  ActivateGranadoraSummon();
}
