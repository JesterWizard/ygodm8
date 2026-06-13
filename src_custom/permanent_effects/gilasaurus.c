#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"

extern const u8 gActivationDescription_Gilasaurus[];

void UpdateDuelGfxExceptField(void);

static void InitSummonedMonsterZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = FALSE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void InitOpponentGraveyardReviveZone(struct DuelCard *zone)
{
  zone->isFaceUp = TRUE;
  zone->isLocked = FALSE;
  zone->isDefending = TRUE;
  zone->permStage = 0;
  zone->tempStage = 0;
  zone->unk4 = 0;
  zone->unkTwo = 0;
  zone->willChangeSides = 0;
}

static void ShowGilasaurusActivationText(void)
{
  u8 hideEffectText = gHideEffectText;

  gHideEffectText = FALSE;
  ResetCardEffectTextData();
  gCardEffectTextData.cardId = GILASAURUS;
  PlayMusic(SFX_SPELL_ACTIVATION_START);
  sub_8041C94(
      (u8 *)gActivationDescription_Gilasaurus,
      GILASAURUS,
      CARD_NONE,
      0,
      0);
  SetCardInfo(GILASAURUS);
  PlayMusic(SFX_SPELL_ACTIVATION_END);
  gHideEffectText = hideEffectText;
}

static void TrySummonOpponentGraveyardMonster(void)
{
  u16 cardId;
  s8 monsterZone;
  struct DuelCard *summonZone;
  struct DuelCard **monsterRow;

  cardId = gTurnDuelistBattleState[INACTIVE_DUELIST]->graveyard;
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return;

  monsterRow = gTurnZones[INACTIVE_DUELIST_MONSTER_ROW];
  monsterZone = FirstEmptyZoneInRow(monsterRow);
  if (monsterZone < 0)
    return;

  cardId = GetGraveCardAndClearGrave(INACTIVE_DUELIST);
  summonZone = monsterRow[monsterZone];
  summonZone->id = cardId;
  InitOpponentGraveyardReviveZone(summonZone);
}

u8 CanSpecialSummonGilasaurusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];

  if (handZone >= MAX_ZONES_IN_ROW)
    return FALSE;

  if (handRow[handZone]->id != GILASAURUS)
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  return TRUE;
}

u8 TrySpecialSummonGilasaurusFromHand(u8 handZone)
{
  struct DuelCard **handRow = gTurnHands[ACTIVE_DUELIST];
  s8 monsterZone;
  struct DuelCard *summonZone;

  if (!CanSpecialSummonGilasaurusFromHand(handZone))
    return FALSE;

  monsterZone = FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]);
  if (monsterZone < 0)
    return FALSE;

  ShowGilasaurusActivationText();

  summonZone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][monsterZone];
  summonZone->id = GILASAURUS;
  InitSummonedMonsterZone(summonZone);
  ClearZone(handRow[handZone]);
  TrySummonOpponentGraveyardMonster();

  return TRUE;
}
