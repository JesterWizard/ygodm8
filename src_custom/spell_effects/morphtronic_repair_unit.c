#include "global.h"
#include "common-chax.h"
#include "archlord_kristya.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "deck_menu.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "exchange_hand_selection.h"
#include "expanded_graveyard.h"
#include "six_card_hand.h"
#include "spell_effects.h"

void UpdateDuelGfxExceptField(void);

static const char sMorphtronicName[] APPEND_RODATA = "Morphtronic";

static const u8 sRepairUnitPickLabels[] APPEND_RODATA = {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

static u8 FixedDuelistForTurnDuelist(u8 turnDuelist)
{
  if (gTurnDuelistBattleState[turnDuelist] == &gDuel.duelistbattleState[DUEL_PLAYER])
    return DUEL_PLAYER;

  return DUEL_OPPONENT;
}

static u8 IsMorphtronicMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return Duel_CardNameContains(cardId, sMorphtronicName);
}

static u8 HandHasMorphtronic(void)
{
  u8 i;

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMorphtronicMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return TRUE;
  }

  return FALSE;
}

static s8 PickMorphtronicHandZone(void)
{
  u8 i;

  if (WhoseTurn() == DUEL_PLAYER)
    return SelectHandCardMatchingPredicate(gTurnHands[ACTIVE_DUELIST], IsMorphtronicMonster);

  for (i = 0; i < MAX_ZONES_IN_ROW; i++) {
    if (IsMorphtronicMonster(gTurnHands[ACTIVE_DUELIST][i]->id))
      return (s8)i;
  }

  return -1;
}

static s8 FindFirstMorphtronicGyIndex(u8 fixedDuelist)
{
  u8 gyCount;
  u8 i;

  if (!GraveyardExpand_IsEnabled())
    return IsMorphtronicMonster(gDuel.duelistbattleState[fixedDuelist].graveyard) ? 0 : -1;

  gyCount = GraveyardExpand_GetCount(fixedDuelist);
  for (i = 0; i < gyCount; i++) {
    if (IsMorphtronicMonster(GraveyardExpand_GetCardAt(fixedDuelist, i)))
      return (s8)i;
  }

  return -1;
}

static u8 LoadMorphtronicGyMenu(u8 fixedDuelist, u8 *gyIndexMap)
{
  u8 gyCount = GraveyardExpand_GetCount(fixedDuelist);
  u8 menuCount = 0;
  u8 i;

  for (i = 0; i < EXPANDED_GRAVEYARD_CAPACITY; i++)
    gDeckMenu.cards[i] = CARD_NONE;

  for (i = 0; i < gyCount; i++) {
    u16 cardId = GraveyardExpand_GetCardAt(fixedDuelist, i);

    if (!IsMorphtronicMonster(cardId))
      continue;

    gyIndexMap[menuCount] = i;
    gDeckMenu.cards[menuCount] = cardId;
    menuCount++;
  }

  gDeckMenu.cost = 0;
  gDeckMenu.currentPos = 0;
  gDeckMenu.sortMode = 0;
  gDeckMenu.displayMode = 1;
  gDeckMenu.cardCount = menuCount;
  return menuCount;
}

static s8 PlayerPickMorphtronicGyIndex(u8 fixedDuelist)
{
  u8 savedDeckMenu[sizeof(gDeckMenu)];
  u8 gyIndexMap[EXPANDED_GRAVEYARD_CAPACITY];
  u8 menuCount;
  s8 chosenGyIndex;

  DECKMENU_SAVE();

  menuCount = LoadMorphtronicGyMenu(fixedDuelist, gyIndexMap);
  if (menuCount == 0) {
    DECKMENU_RESTORE();
    return -1;
  }

  if (menuCount == 1) {
    chosenGyIndex = (s8)gyIndexMap[0];
    DECKMENU_RESTORE();
    return chosenGyIndex;
  }

  DeckMenu_BeginDuelTrunkView();
  if (!DeckMenuMainPickConfirmWithLabels(sRepairUnitPickLabels,
                                         ARRAY_COUNT(sRepairUnitPickLabels))) {
    DECKMENU_RESTORE();
    DeckMenu_EndDuelTrunkView();
    return -1;
  }

  chosenGyIndex = (s8)gyIndexMap[gDeckMenu.currentPos];

  DECKMENU_RESTORE();
  DeckMenu_EndDuelTrunkView();
  return chosenGyIndex;
}

static struct DuelCard *FindSummonedMonsterZone(u16 monsterId)
{
  u8 col;

  for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
    struct DuelCard *zone = gTurnZones[ACTIVE_DUELIST_MONSTER_ROW][col];

    if (zone->id == monsterId)
      return zone;
  }

  return NULL;
}

static enum DuelActionResult SpecialSummonMorphtronicFromGyIndex(u8 gyIndex)
{
  struct DuelSummonOpts opts = Duel_DefaultSpecialSummonOpts(FALSE);
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  u16 cardId;

  if (!GraveyardExpand_IsEnabled()) {
    cardId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
    if (!IsMorphtronicMonster(cardId))
      return DUEL_ACTION_NO_TARGET;

    return Duel_SpecialSummonFromGrave(ACTIVE_DUELIST, cardId, opts);
  }

  cardId = GraveyardExpand_GetCardAt(fixedDuelist, gyIndex);
  if (!IsMorphtronicMonster(cardId))
    return DUEL_ACTION_NO_TARGET;

  cardId = GraveyardExpand_RemoveAtFixed(fixedDuelist, gyIndex);
  GraveyardExpand_SyncLegacyTop(fixedDuelist);
  return Duel_SpecialSummonMonsterId(ACTIVE_DUELIST, cardId, opts);
}

static u8 CanActivateMorphtronicRepairUnit(void)
{
  if (ArchlordKristya_IsSpecialSummonLocked())
    return FALSE;

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return FALSE;

  /* Sent Morphtronic becomes a legal GY target even if GY was empty. */
  return HandHasMorphtronic();
}

static void EquipRepairUnit(struct DuelCard *spellZone, struct DuelCard *target)
{
  if (!RegisterDynamicEquip(spellZone, target, MORPHTRONIC_REPAIR_UNIT, 0))
    return;

  Duel_ActivateContinuousZone(spellZone);

  /* ponytail: cannot change Battle Position — lockMonster / isLocked is the
   * nearest in-file flag (also blocks attack in some validators). Ceiling:
   * battle-position change may still be allowed; upgrade: position-change gate
   * → if DynamicEquipTargetsMonsterWithSpell(zone, MORPHTRONIC_REPAIR_UNIT)
   * then forbid manual position change. */
  target->isLocked = TRUE;

  NotifyDynamicEquipFieldChanged();
  Duel_NotifyMonsterZoneChanged(target);

  /* ponytail: not in GetSpellType EQUIP / IsActiveDynamicEquipSpellZone /
   * OnDynamicEquipZoneAboutToClear destroy-equipped list. Ceiling: link may
   * not clean up / destroy equipped on leave; upgrade: add
   * MORPHTRONIC_REPAIR_UNIT beside PREMATURE_BURIAL in dynamic_equip.c. */
}

static void MORPHTRONIC_REPAIR_UNIT_ResolveBody(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];
  u8 fixedDuelist = FixedDuelistForTurnDuelist(ACTIVE_DUELIST);
  s8 handZone;
  s8 gyIndex;
  u16 monsterId;
  struct DuelCard *summonedZone;

  Duel_ShowEffectText(MORPHTRONIC_REPAIR_UNIT);

  if (IsDuelOver() == TRUE || !CanActivateMorphtronicRepairUnit())
    return;

  handZone = PickMorphtronicHandZone();
  if (handZone < 0)
    return;

  ClearZoneAndSendMonToGraveyard(
      SixCardHand_ZoneAtHandRow(gTurnHands[ACTIVE_DUELIST], (u8)handZone), ACTIVE_DUELIST);
  if (IsDuelOver() == TRUE)
    return;

  GraveyardExpand_RefreshDisplay();

  if (FirstEmptyZoneInRow(gTurnZones[ACTIVE_DUELIST_MONSTER_ROW]) < 0)
    return;

  if (!GraveyardExpand_IsEnabled()) {
    gyIndex = 0;
  } else if (WhoseTurn() == DUEL_PLAYER && !gHideEffectText) {
    gyIndex = PlayerPickMorphtronicGyIndex(fixedDuelist);
  } else {
    gyIndex = FindFirstMorphtronicGyIndex(fixedDuelist);
  }

  if (gyIndex < 0)
    return;

  if (!GraveyardExpand_IsEnabled())
    monsterId = gTurnDuelistBattleState[ACTIVE_DUELIST]->graveyard;
  else
    monsterId = GraveyardExpand_GetCardAt(fixedDuelist, (u8)gyIndex);

  if (!IsMorphtronicMonster(monsterId))
    return;

  if (SpecialSummonMorphtronicFromGyIndex((u8)gyIndex) != DUEL_ACTION_OK)
    return;

  if (IsDuelOver() == TRUE)
    return;

  summonedZone = FindSummonedMonsterZone(monsterId);
  if (summonedZone == NULL)
    return;

  EquipRepairUnit(spellZone, summonedZone);
  UpdateDuelGfxExceptField();
}

APPEND_TEXT void EffectMORPHTRONIC_REPAIR_UNIT(void)
{
  if (!CanActivateMorphtronicRepairUnit()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(MORPHTRONIC_REPAIR_UNIT, MORPHTRONIC_REPAIR_UNIT_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void MORPHTRONIC_REPAIR_UNIT_SelfCheck(void)
{
  if (!IsMorphtronicMonster(MORPHTRONIC_DATATRON))
    while (1)
      ;
  if (IsMorphtronicMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
