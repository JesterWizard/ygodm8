#include "global.h"
#include "common-chax.h"
#include "dynamic_equip.h"
#include "pyramid_of_light.h"
#include "soul_exchange.h"

u8 TryPayChainEnergyCost(void);
u8 IsActivatedChainEnergyZone(const struct DuelCard *zone);
u8 TryConsumeUltimateOfferingExtraSummonPayment(void);
void TryEnableUltimateOfferingExtraSummonAfterPlacement(void);
u8 IsActivatedUltimateOfferingZone(const struct DuelCard *zone);
void MarkUltimateOfferingJustSet(struct DuelCard *zone);
unsigned char IsSpellCancellerSpellLockActive(void);

extern struct DuelCard gSelectedCard;

void DisplayCardInfoBar(void);
void HandlePlayerBackrowAction(void);
void TrySelectSpellTarget(void);
void sub_8041E70(u8, u8);
void ActivateSpellEffect(void);
void LockMonsterCardsInRow(unsigned char);
void UpdateDuelGfxExceptField(void);
void CheckWinConditionExodia(unsigned char);
void TryActivatingPermanentEffects(void);
void SelectZone(struct DuelCard *zone);
void ResetCursorDestToCurrentPos(void);
unsigned char GetFirstNonEmptyMonZoneId(struct DuelCard *zone[]);
void ClearZone(struct DuelCard *zone);
void CopySelectedCardToZone(struct DuelCard *zone);
void sub_80449D8(void);
void sub_80441D0(void);
void MonsterActionMenu(void);
void HandlePlayerBackrowAction(void);
void DisplayNumRequiredTributesTextbox(unsigned char);
void sub_80442AC(void);

static void FinishEquipSpellTargeting(void)
{
  u8 cursorRow = gDuelCursor.currentY;

  if (cursorRow == PLAYER_MONSTER_ROW)
    sub_8041E70(PLAYER_MONSTER_ROW, PLAYER_BACKROW);

  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}

static void OpenPlayerMonsterActionMenu(void)
{
  if (gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->id != CARD_NONE
      && !gFixedZones[PLAYER_MONSTER_ROW][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_SELECT);
    MonsterActionMenu();
  } else {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  }
}


LYN_REPLACE_CHECK(sub_80441D0);
void sub_80441D0__Replacement(void)
{
  switch (gDuelCursor.currentY) {
    case PLAYER_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        OpenPlayerMonsterActionMenu();
      }
      break;
    case OPPONENT_MONSTER_ROW:
      if (IsSoulExchangeActive()) {
        PerformSoulExchangeOpponentTribute();
        break;
      } else {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      }
      break;
    case PLAYER_BACKROW:
      if (gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id == CARD_NONE) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetRitualNumRequiredTributes(
            gFixedZones[PLAYER_BACKROW][gDuelCursor.currentX]->id);
        if (!numTributes)
          HandlePlayerBackrowAction();
        else {
          PlayMusic(SFX_FORBIDDEN);
          DisplayNumRequiredTributesTextbox(numTributes);
        }
      }
      break;
    case PLAYER_HAND:
      if (gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->id == CARD_NONE
          || gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->isLocked) {
        PlayMusic(SFX_FORBIDDEN);
        WaitForVBlank();
      } else {
        unsigned char numTributes = GetMonsterNumRequiredTributes(
            gFixedZones[PLAYER_HAND][gDuelCursor.currentX]->id);
        if (numTributes) {
          PlayMusic(SFX_FORBIDDEN);
          DisplayNumRequiredTributesTextbox(numTributes);
        } else {
          PlayMusic(SFX_SELECT);
          sub_80442AC();
        }
      }
      break;
    default:
      PlayMusic(SFX_FORBIDDEN);
      WaitForVBlank();
  }
}

LYN_REPLACE_CHECK(HandlePlayerBackrowAction);
void HandlePlayerBackrowAction__Replacement(void) {
  u16 id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
  struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];

  if ((id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE)
      || IsActivatedChainEnergyZone(zone)
      || IsActivatedPyramidOfLightZone(zone)
      || IsActivatedUltimateOfferingZone(zone)
      || IsActiveDynamicEquipSpellZone(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  SelectZone(zone);
  ResetCursorDestToCurrentPos();

  if (IsSpellCancellerSpellLockActive()
      && GetTypeGroup(id) == TYPE_GROUP_SPELL) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

  switch (GetSpellType(id)) {
    case SPELL_TYPE_NORMAL:
      gDuelCursor.state = 0;
      gSpellEffectData.id = id;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
      if (gTurnDuelistBattleState[ACTIVE_DUELIST]->summoningBlocked)
        LockMonsterCardsInRow(4);
      UpdateDuelGfxExceptField();
      CheckWinConditionExodia(WhoseTurn());
      if (IsDuelOver() != TRUE)
        TryActivatingPermanentEffects();
      break;
    case SPELL_TYPE_EQUIP:
      PlayMusic(SFX_SELECT);
      gDuelCursor.state = 2;
      gDuelCursor.currentX = GetFirstNonEmptyMonZoneId(gFixedZones[2]);
      gDuelCursor.currentY = 2;
      break;
    case SPELL_TYPE_INVALID:
      PlayMusic(SFX_FORBIDDEN);
      gDuelCursor.state = 0;
      break;
  }

  DisplayCardInfoBar();
  sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
}

LYN_REPLACE_CHECK(TrySelectSpellTarget);
void TrySelectSpellTarget__Replacement(void) {
  if (gDuelCursor.currentY != 2) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id == CARD_NONE) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else if (gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->isLocked) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
  } else {
    SetCardInfo(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id);
    if (GetTypeGroup(gCardInfo.id) == TYPE_GROUP_MONSTER) {
      gSpellEffectData.id = gFixedZones[gDuelCursor.destY][gDuelCursor.destX]->id;
      gSpellEffectData.row2 = gDuelCursor.destY;
      gSpellEffectData.col2 = gDuelCursor.destX;
      gSpellEffectData.row1 = gDuelCursor.currentY;
      gSpellEffectData.col1 = gDuelCursor.currentX;
      ActivateSpellEffect();
    }
    gDuelCursor.state = 0;
    FinishEquipSpellTargeting();
    TryActivatingPermanentEffects();
  }
}

LYN_REPLACE_CHECK(sub_80449D8);
void sub_80449D8__Replacement(void)
{
  if (!TryPayChainEnergyCost()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (!TryConsumeUltimateOfferingExtraSummonPayment()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  if (ShouldBlockGodCardSummon(gSelectedCard.id)) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ClearZone(gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
  CopySelectedCardToZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
  MarkUltimateOfferingJustSet(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
  TryEnableUltimateOfferingExtraSummonAfterPlacement();
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}
