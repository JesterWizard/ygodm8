#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "r_righteous_justice.h"
#include "spell_effects.h"

void DisplayCardInfoBar(void);
void sub_8041E70(u8, u8);
void MoveCursorLeft(void);
void MoveCursorRight(void);
void MoveCursorUp(void);
void MoveCursorDown(void);
void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void WaitForVBlank(void);
void UpdateDuelGfxExceptField(void);

extern u16 gNewButtons;
extern u16 gRepeatedOrNewButtons;
extern u16 gPressedButtons;

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup = GetTypeGroup(cardId);

  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 CountFaceUpElementalHeroes(void)
{
  u8 i;
  u8 count = 0;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][i];

    if (zone == NULL || zone->id == CARD_NONE || !MonsterIsFaceUp(zone))
      continue;
    if (Duel_IsElementalHeroCard(zone->id))
      count++;
  }

  return count;
}

static struct DuelCard *SpellZoneAt(u8 row, u8 col)
{
  struct DuelCard *zone;

  if (col >= MAX_ZONES_IN_ROW)
    return NULL;

  if (row <= ACTIVE_DUELIST_HAND) {
    zone = gTurnZones[row][col];
    if (zone != NULL && zone->id == R_RIGHTEOUS_JUSTICE)
      return zone;
  }

  if (row <= PLAYER_HAND) {
    zone = gFixedZones[row][col];
    if (zone != NULL && zone->id == R_RIGHTEOUS_JUSTICE)
      return zone;
  }

  return NULL;
}

static u8 IsValidDestroyTarget(u8 fixedRow, u8 fixedCol, struct DuelCard *spellZone)
{
  struct DuelCard *zone;

  if (fixedRow != OPPONENT_BACKROW && fixedRow != PLAYER_BACKROW)
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (zone == NULL || zone == spellZone || zone->id == CARD_NONE)
    return FALSE;

  return IsSpellOrTrapCard(zone->id);
}

static u8 FindFirstDestroyTarget(struct DuelCard *spellZone, u8 *outRow, u8 *outCol)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(OPPONENT_BACKROW, col, spellZone)) {
      *outRow = OPPONENT_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(PLAYER_BACKROW, col, spellZone)) {
      *outRow = PLAYER_BACKROW;
      *outCol = col;
      return TRUE;
    }
  }

  return FALSE;
}

static u8 CountDestroyTargets(struct DuelCard *spellZone)
{
  u8 col;
  u8 count = 0;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsValidDestroyTarget(OPPONENT_BACKROW, col, spellZone))
      count++;
    if (IsValidDestroyTarget(PLAYER_BACKROW, col, spellZone))
      count++;
  }

  return count;
}

static u8 GetGraveyardDuelistForFixedRow(u8 fixedRow)
{
  if (fixedRow <= OPPONENT_MONSTER_ROW)
    return WhoseTurn() == DUEL_PLAYER ? INACTIVE_DUELIST : ACTIVE_DUELIST;

  return WhoseTurn() == DUEL_PLAYER ? ACTIVE_DUELIST : INACTIVE_DUELIST;
}

static void DestroyTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone = gFixedZones[fixedRow][fixedCol];

  Duel_DestroyZone(zone, GetGraveyardDuelistForFixedRow(fixedRow), TRUE);
  NotifyDynamicEquipFieldChanged();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

static u8 PickDestroyTarget(struct DuelCard *spellZone, u8 *outRow, u8 *outCol)
{
  struct DuelCursor savedCursor = gDuelCursor;
  u8 scrollY;
  u8 targetRow;
  u8 targetCol;

  if (!FindFirstDestroyTarget(spellZone, &targetRow, &targetCol))
    return FALSE;

  InitButtonMaps();
  gDuelCursor.currentY = targetRow;
  gDuelCursor.destY = targetRow;
  gDuelCursor.currentX = targetCol;
  gDuelCursor.destX = targetCol;
  DisplayCardInfoBar();
  sub_8041E70(savedCursor.currentY, targetRow);

  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    scrollY = gDuelCursor.currentY;
    UpdateFilteredInput_WithRepeat();

    if (gRepeatedOrNewButtons & DPAD_LEFT) {
      MoveCursorLeft();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_RIGHT) {
      MoveCursorRight();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_UP) {
      MoveCursorUp();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gRepeatedOrNewButtons & DPAD_DOWN) {
      MoveCursorDown();
      DisplayCardInfoBar();
      sub_8041E70(scrollY, gDuelCursor.currentY);
    } else if (gNewButtons & A_BUTTON) {
      if (IsValidDestroyTarget(gDuelCursor.currentY, gDuelCursor.currentX, spellZone)) {
        PlayMusic(SFX_SELECT);
        *outRow = gDuelCursor.currentY;
        *outCol = gDuelCursor.currentX;
        gDuelCursor = savedCursor;
        return TRUE;
      }
      PlayMusic(SFX_FORBIDDEN);
    }

    WaitForVBlank();
  }
}

static void DestroySpellTraps(u8 count, struct DuelCard *spellZone)
{
  u8 i;

  for (i = 0; i < count; i++) {
    u8 targetRow;
    u8 targetCol;

    if (!FindFirstDestroyTarget(spellZone, &targetRow, &targetCol))
      break;

    if (WhoseTurn() == DUEL_PLAYER) {
      if (!PickDestroyTarget(spellZone, &targetRow, &targetCol))
        break;
    }

    DestroyTarget(targetRow, targetCol);
  }
}

u8 CanActivateRRighteousJustice(u8 originRow, u8 originCol)
{
  struct DuelCard *spellZone = SpellZoneAt(originRow, originCol);
  u8 heroCount = CountFaceUpElementalHeroes();

  return heroCount > 0 && CountDestroyTargets(spellZone) >= heroCount;
}

static void RRighteousJustice_ResolveBody(void)
{
  struct DuelCard *spellZone = SpellZoneAt(gSpellEffectData.row1, gSpellEffectData.col1);
  u8 heroCount = CountFaceUpElementalHeroes();

  Duel_ShowEffectText(R_RIGHTEOUS_JUSTICE);
  if (IsDuelOver() == TRUE)
    return;

  if (heroCount > 0)
    DestroySpellTraps(heroCount, spellZone);

  if (spellZone != NULL && spellZone->id == R_RIGHTEOUS_JUSTICE)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
}

APPEND_TEXT void EffectRRighteousJustice(void)
{
  if (!CanActivateRRighteousJustice(gSpellEffectData.row1, gSpellEffectData.col1)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(R_RIGHTEOUS_JUSTICE, RRighteousJustice_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void RRighteousJustice_SelfCheck(void)
{
  if (IsSpellOrTrapCard(POLYMERIZATION) == FALSE)
    while (1)
      ;
  if (IsSpellOrTrapCard(MIRROR_FORCE) == FALSE)
    while (1)
      ;
  if (Duel_IsElementalHeroCard(ELEMENTAL_HERO_SPARKMAN) == FALSE)
    while (1)
      ;
}
#endif
