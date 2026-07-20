#include "global.h"
#include "common-chax.h"
#include "configs/runtime.h"
#include "constants/card_ids.h"
#include "constants/music_ids.h"
#include "duel_helpers.h"
#include "effect_events.h"
#include "dynamic_equip.h"
#include "spell_effects.h"

void ClearZone(struct DuelCard *zone);
void ExtraDeck_AddCard(u16 cardId);
void UpdateDuelGfxExceptField(void);

extern const CardData gCardData_NEW[];

static u8 IsSynchroMonster(u16 cardId)
{
  if (cardId == CARD_NONE || GetTypeGroup(cardId) != TYPE_GROUP_MONSTER)
    return FALSE;

  return gCardData_NEW[cardId].color == COLOR_SYNCHRO;
}

static u8 IsValidDeSynchroTarget(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *zone;

  if (!Duel_IsFixedMonsterRow(fixedRow))
    return FALSE;

  zone = gFixedZones[fixedRow][fixedCol];
  if (!Duel_SpellMayTargetMonsterZone(zone))
    return FALSE;

  return IsSynchroMonster(zone->id);
}

static u8 HasDeSynchroTarget(void)
{
  u8 row;
  u8 col;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      if (IsValidDeSynchroTarget(row, col))
        return TRUE;
    }
  }

  return FALSE;
}

u8 CanActivateDE_SYNCHRO(void)
{
  return HasDeSynchroTarget();
}

static void DestroyDeSynchroSpellZone(void)
{
  struct DuelCard *spellZone = gTurnZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (spellZone != NULL && spellZone->id == DE_SYNCHRO)
    Duel_DestroyZone(spellZone, ACTIVE_DUELIST, TRUE);
  else
    UpdateDuelGfxExceptField();
}

static void ReturnSynchroToExtraDeck(struct DuelCard *zone)
{
  u16 cardId;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  cardId = zone->id;
  ClearZone(zone);
  NotifyDynamicEquipFieldChanged();
  EffectEvent_EmitSimple(EFFECT_EVENT_ON_FIELD_CHANGE, CARD_NONE, NULL);

  /* ponytail: duel Extra Deck return is imperfect — ExtraDeck_AddCard writes the
   * player's trunk Extra Deck only (deck-builder API). Ceiling: ClearZone off-field
   * + best-effort ExtraDeck_AddCard when enable_extra_deck; upgrade: per-duelist
   * mid-duel Extra Deck return for the Synchro's controller. */
  if (gRuntimeConfig.enable_extra_deck)
    ExtraDeck_AddCard(cardId);
}

static void FinishDeSynchro(u8 fixedRow, u8 fixedCol)
{
  struct DuelCard *target = gFixedZones[fixedRow][fixedCol];

  if (!IsValidDeSynchroTarget(fixedRow, fixedCol)) {
    DestroyDeSynchroSpellZone();
    return;
  }

  ReturnSynchroToExtraDeck(target);
  DestroyDeSynchroSpellZone();

  /* ponytail: Synchro Summon materials are not recorded at summon time, so
   * "if all materials are in your GY, SS all of them" cannot run.
   * Ceiling: return-to-Extra-Deck only; upgrade: store material cardIds on the
   * Synchro zone at SynchroDuel_Execute, then if each is in GY, SS from GY. */
}

static void ResolveDeSynchroTarget(u8 fixedRow, u8 fixedCol)
{
  if (!IsValidDeSynchroTarget(fixedRow, fixedCol))
    return;

  FinishDeSynchro(fixedRow, fixedCol);
}

static void CancelDeSynchroTargeting(void)
{
  PlayMusic(SFX_CANCEL);
  DestroyDeSynchroSpellZone();
}

static u8 AiPickDeSynchroTarget(u8 *outRow, u8 *outCol)
{
  u8 row;
  u8 col;
  u8 found = FALSE;
  u16 bestAtk = 0;

  for (row = OPPONENT_MONSTER_ROW; row <= PLAYER_MONSTER_ROW; row++) {
    for (col = 0; col < MAX_ZONES_IN_ROW; col++) {
      struct DuelCard *zone;
      u16 atk;

      if (!IsValidDeSynchroTarget(row, col))
        continue;

      zone = gFixedZones[row][col];
      atk = Duel_GetZoneFinalAtk(zone);
      if (!found || atk > bestAtk) {
        found = TRUE;
        bestAtk = atk;
        *outRow = row;
        *outCol = col;
      }
    }
  }

  return found;
}

static void DE_SYNCHRO_ResolveBody(void)
{
  Duel_ShowEffectText(DE_SYNCHRO);

  if (IsDuelOver() == TRUE || !CanActivateDE_SYNCHRO())
    return;

  gDuelCursor.destY = gSpellEffectData.row1;
  gDuelCursor.destX = gSpellEffectData.col1;

  Duel_SetupPickZone(IsValidDeSynchroTarget, ResolveDeSynchroTarget,
                     CancelDeSynchroTargeting, AiPickDeSynchroTarget);

  if (WhoseTurn() == DUEL_PLAYER)
    Duel_EnterPickZoneTargeting();
  else
    Duel_ResolvePickZoneForAi();
}

APPEND_TEXT void EffectDE_SYNCHRO(void)
{
  if (!CanActivateDE_SYNCHRO()) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(DE_SYNCHRO, DE_SYNCHRO_ResolveBody)
      == DUEL_ACTION_BLOCKED)
    return;
}

#if defined(DUEL_HELPERS_SELF_CHECK)
void DE_SYNCHRO_SelfCheck(void)
{
  if (!IsSynchroMonster(STARDUST_DRAGON))
    while (1)
      ;
  if (IsSynchroMonster(BLUE_EYES_WHITE_DRAGON))
    while (1)
      ;
}
#endif
