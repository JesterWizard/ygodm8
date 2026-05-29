#include "global.h"
#include "common-chax.h"

u8 TryPayChainEnergyCost(void);
u8 IsActivatedChainEnergyZone(const struct DuelCard *zone);
unsigned char IsSpellCancellerSpellLockActive(void);

void DisplayCardInfoBar(void);
void HandlePlayerBackrowAction(void);
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

LYN_REPLACE_CHECK(HandlePlayerBackrowAction);
void HandlePlayerBackrowAction__Replacement(void) {
  u16 id = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]->id;
  struct DuelCard *zone = gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX];

  SelectZone(zone);
  ResetCursorDestToCurrentPos();

  if ((id == SWORDS_OF_REVEALING_LIGHT && zone->isFaceUp == TRUE)
      || IsActivatedChainEnergyZone(zone)) {
    PlayMusic(SFX_FORBIDDEN);
    gDuelCursor.state = 0;
    DisplayCardInfoBar();
    sub_8041E70(gDuelCursor.destY, gDuelCursor.currentY);
    return;
  }

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

LYN_REPLACE_CHECK(sub_80449D8);
void sub_80449D8__Replacement(void)
{
  if (!TryPayChainEnergyCost()) {
    PlayMusic(SFX_FORBIDDEN);
    WaitForVBlank();
    return;
  }

  ClearZone(gFixedZones[gDuelCursor.destY][gDuelCursor.destX]);
  CopySelectedCardToZone(gFixedZones[gDuelCursor.currentY][gDuelCursor.currentX]);
  gDuelCursor.state = 0;
  ResetCursorDestToCurrentPos();
  UpdateDuelGfxExceptField();
}
