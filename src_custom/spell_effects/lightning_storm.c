#include "global.h"
#include "common-chax.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void InitButtonMaps(void);
void UpdateFilteredInput_WithRepeat(void);
void UpdateDuelGfxExceptField(void);
void WaitForVBlank(void);

extern u16 gNewButtons;
extern u16 gPressedButtons;

enum {
  LIGHTNING_STORM_MODE_MONSTERS = 0,
  LIGHTNING_STORM_MODE_SPELLS_TRAPS = 1,
};

static u8 IsSpellOrTrapCard(u16 cardId)
{
  u8 typeGroup;

  if (cardId == CARD_NONE)
    return FALSE;

  typeGroup = GetTypeGroup(cardId);
  return typeGroup == TYPE_GROUP_SPELL || typeGroup == TYPE_GROUP_TRAP;
}

/* Attack-position summons keep isFaceUp=0 until end-of-turn flip. */
static u8 MonsterIsFaceUp(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  if (IsCardFaceUp(zone))
    return TRUE;

  return zone->isDefending == FALSE;
}

static u8 ZoneIsFaceUpCard(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) == TYPE_GROUP_MONSTER)
    return MonsterIsFaceUp(zone);

  return zone->isFaceUp == TRUE;
}

static u8 ControlsNoFaceUpCardsExceptActivating(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *monster = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];
    struct DuelCard *backrow = gTurnZones[ACTIVE_DUELIST_BACKROW][col];

    if (MonsterIsFaceUp(monster))
      return FALSE;

    if (backrow == spellZone)
      continue;

    if (ZoneIsFaceUpCard(backrow))
      return FALSE;
  }

  return TRUE;
}

static u8 IsOpponentAttackPositionMonster(struct DuelCard *zone)
{
  if (zone == NULL || zone->id == CARD_NONE)
    return FALSE;

  if (GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return FALSE;

  return zone->isDefending == FALSE;
}

static u8 OpponentHasAttackPositionMonster(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsOpponentAttackPositionMonster(gTurnZones[INACTIVE_DUELIST_MONSTER_ROW][col]))
      return TRUE;
  }

  return FALSE;
}

static u8 OpponentHasSpellOrTrap(void)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    if (IsSpellOrTrapCard(gTurnZones[INACTIVE_DUELIST_BACKROW][col]->id))
      return TRUE;
  }

  return FALSE;
}

u8 CanActivateLIGHTNING_STORM(void)
{
  /* ponytail: once-per-turn not tracked after this normal spell leaves the field
   * (no shared turn-flag RAM editable from this file alone).
   * Ceiling: multiple Lightning Storm per turn; upgrade: duel-state OPT bit. */
  return ControlsNoFaceUpCardsExceptActivating();
}

static void WaitForNoButtonsHeld(void)
{
  while (gPressedButtons & ANY_BUTTON)
    WaitForVBlank();
}

/* TRUE = destroy Attack Position monsters; FALSE = destroy Spells/Traps. */
static u8 PlayerChoosesDestroyMonsters(void)
{
  /* ponytail: no dedicated choice UI — A = monsters, B = Spells/Traps.
   * Ceiling: unlabeled buttons; upgrade: effect-text choice menu. */
  InitButtonMaps();
  WaitForNoButtonsHeld();
  InitButtonMaps();

  for (;;) {
    UpdateFilteredInput_WithRepeat();

    if (gNewButtons & A_BUTTON) {
      PlayMusic(SFX_SELECT);
      return TRUE;
    }

    if (gNewButtons & B_BUTTON) {
      PlayMusic(SFX_SELECT);
      return FALSE;
    }

    WaitForVBlank();
  }
}

static u8 ChooseLightningStormMode(void)
{
  u8 hasMonsters = OpponentHasAttackPositionMonster();
  u8 hasSpells = OpponentHasSpellOrTrap();

  if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText && hasMonsters && hasSpells)
    return PlayerChoosesDestroyMonsters() ? LIGHTNING_STORM_MODE_MONSTERS
                                          : LIGHTNING_STORM_MODE_SPELLS_TRAPS;

  if (hasMonsters)
    return LIGHTNING_STORM_MODE_MONSTERS;

  if (hasSpells)
    return LIGHTNING_STORM_MODE_SPELLS_TRAPS;

  /* No targets either way — default to monster mode (empty destroy-all). */
  return LIGHTNING_STORM_MODE_MONSTERS;
}

static void DestroyOpponentAttackPositionMonsters(void)
{
  Duel_DestroyAllMonstersMatching(INACTIVE_DUELIST_MONSTER_ROW,
                                  IsOpponentAttackPositionMonster, FALSE);
}

static void DestroyOpponentSpellsAndTraps(void)
{
  u8 col;
  u8 destroyed = FALSE;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[INACTIVE_DUELIST_BACKROW][col];

    if (zone == NULL || zone->id == CARD_NONE || !IsSpellOrTrapCard(zone->id))
      continue;

    if (Duel_DestroyZone(zone, INACTIVE_DUELIST, FALSE) == DUEL_ACTION_DUEL_OVER)
      return;

    destroyed = TRUE;
  }

  if (destroyed)
    NotifyDynamicEquipFieldChanged();
}

static void LIGHTNING_STORM_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 mode;

  Duel_ShowEffectText(LIGHTNING_STORM);

  if (IsDuelOver() == TRUE || !CanActivateLIGHTNING_STORM())
    return;

  mode = ChooseLightningStormMode();

  if (mode == LIGHTNING_STORM_MODE_MONSTERS)
    DestroyOpponentAttackPositionMonsters();
  else
    DestroyOpponentSpellsAndTraps();

  if (IsDuelOver() == TRUE)
    return;

  if (spellZone != NULL && spellZone->id == LIGHTNING_STORM)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectLIGHTNING_STORM(void)
{
  if (!CanActivateLIGHTNING_STORM()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(LIGHTNING_STORM, LIGHTNING_STORM_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void LIGHTNING_STORM_SelfCheck(void)
{
  struct DuelCard atk;

  atk.id = BLUE_EYES_WHITE_DRAGON;
  atk.isDefending = FALSE;
  atk.isFaceUp = FALSE;
  if (!IsOpponentAttackPositionMonster(&atk))
    while (1)
      ;

  atk.isDefending = TRUE;
  if (IsOpponentAttackPositionMonster(&atk))
    while (1)
      ;
}
#endif
