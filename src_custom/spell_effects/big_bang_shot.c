#include "global.h"
#include "common-chax.h"
#include "big_bang_shot.h"
#include "constants/card_ids.h"
#include "dynamic_equip.h"
#include "duel_helpers.h"
#include "spell_effects.h"

static u8 BigBangShot_SlotBaseForDuelist(u8 duelist)
{
  return duelist == DUEL_PLAYER ? 0 : BIG_BANG_SHOT_SLOTS_PER_DUELIST;
}

static u8 BigBangShot_EncodeSlot(u8 spellCol, u8 targetCol)
{
  return (u8)(((spellCol + 1) << 4) | (targetCol + 1));
}

static u8 BigBangShot_SpellColFromSlot(u8 slot)
{
  return (slot >> 4) - 1;
}

static void BigBangShot_ClearEncodedSlot(u8 duelist, u8 encoded)
{
  u8 base;
  u8 i;

  if (encoded == 0)
    return;

  base = BigBangShot_SlotBaseForDuelist(duelist);
  for (i = 0; i < BIG_BANG_SHOT_SLOTS_PER_DUELIST; i++) {
    if (gBigBangShotTargetCol[base + i] == encoded)
      gBigBangShotTargetCol[base + i] = 0;
  }
}

void BigBangShot_ResetAllBoosts(void)
{
  u8 i;

  for (i = 0; i < BIG_BANG_SHOT_RAM_BYTES; i++)
    gBigBangShotTargetCol[i] = 0;
}

u8 BigBangShot_ClaimEquipSlot(struct DuelCard *targetZone, struct DuelCard *spellZone)
{
  u8 targetRow;
  u8 targetCol;
  u8 spellRow;
  u8 spellCol;
  u8 duelist;
  u8 base;
  u8 encoded;
  u8 i;

  if (!Duel_FindFixedMonsterZone(targetZone, &targetRow, &targetCol))
    return FALSE;
  if (!Duel_FindFixedZone(spellZone, &spellRow, &spellCol))
    return FALSE;

  duelist = GetDuelistForZone(spellZone);
  if (duelist == 0xFF)
    return FALSE;

  encoded = BigBangShot_EncodeSlot(spellCol, targetCol);
  base = BigBangShot_SlotBaseForDuelist(duelist);
  for (i = 0; i < BIG_BANG_SHOT_SLOTS_PER_DUELIST; i++) {
    if (gBigBangShotTargetCol[base + i] == 0) {
      gBigBangShotTargetCol[base + i] = encoded;
      return TRUE;
    }
  }

  /* ponytail: 3 copies max per side — reuse slot 0 if all busy */
  gBigBangShotTargetCol[base] = encoded;
  return TRUE;
}

void BigBangShot_ClearEquipBonus(const struct DynamicEquipLink *link)
{
  u8 duelist;
  u8 encoded;

  if (link == NULL || !link->active || link->spellId != BIG_BANG_SHOT)
    return;

  if (link->targetFixedRow == PLAYER_MONSTER_ROW)
    duelist = DUEL_PLAYER;
  else if (link->targetFixedRow == OPPONENT_MONSTER_ROW)
    duelist = DUEL_OPPONENT;
  else
    return;

  encoded = BigBangShot_EncodeSlot(link->spellFixedCol, link->targetFixedCol);
  BigBangShot_ClearEncodedSlot(duelist, encoded);
}

void BigBangShot_OnTargetZoneLeaving(struct DuelCard *zone)
{
  u8 targetRow;
  u8 targetCol;
  u8 duelist;
  u8 base;
  u8 backrowRow;
  u8 i;
  u8 encoded;
  u8 spellCol;
  struct DuelCard *spellZone;

  if (zone == NULL || GetTypeGroup(zone->id) != TYPE_GROUP_MONSTER)
    return;

  if (!Duel_FindFixedMonsterZone(zone, &targetRow, &targetCol))
    return;

  duelist = targetRow == PLAYER_MONSTER_ROW ? DUEL_PLAYER : DUEL_OPPONENT;
  base = BigBangShot_SlotBaseForDuelist(duelist);
  backrowRow = duelist == DUEL_PLAYER ? PLAYER_BACKROW : OPPONENT_BACKROW;

  for (i = 0; i < BIG_BANG_SHOT_SLOTS_PER_DUELIST; i++) {
    encoded = gBigBangShotTargetCol[base + i];
    if ((encoded & 0xF) != targetCol + 1)
      continue;

    spellCol = BigBangShot_SpellColFromSlot(encoded);
    gBigBangShotTargetCol[base + i] = 0;

    if (spellCol >= MAX_ZONES_IN_ROW)
      return;

    spellZone = gFixedZones[backrowRow][spellCol];
    if (spellZone != NULL && spellZone->id == BIG_BANG_SHOT)
      ClearZone(spellZone);
    return;
  }
}

void ApplyBigBangShotAtkBonusToCardInfo(const struct DuelCard *zone)
{
  u8 fixedRow;
  u8 col;
  u8 duelist;
  u8 base;
  u8 i;
  u32 atk;

  if (zone == NULL || zone->id == CARD_NONE)
    return;

  if (!Duel_FindFixedMonsterZone((struct DuelCard *)zone, &fixedRow, &col))
    return;

  duelist = GetDuelistForZone(zone);
  if (duelist == 0xFF)
    return;

  base = BigBangShot_SlotBaseForDuelist(duelist);
  for (i = 0; i < BIG_BANG_SHOT_SLOTS_PER_DUELIST; i++) {
    if ((gBigBangShotTargetCol[base + i] & 0xF) != col + 1)
      continue;

    atk = (u32)gCardInfo.atk + (u32)BIG_BANG_SHOT_ATK_BONUS;
    gCardInfo.atk = Duel_ClampStat(atk);
    return;
  }
}

static void BigBangShot_ResolveBody(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];
  struct DuelCard *spellZone = gFixedZones[gSpellEffectData.row2][gSpellEffectData.col2];

  if (!RegisterDynamicEquip(spellZone, target, BIG_BANG_SHOT, 0))
    return;

  if (!BigBangShot_ClaimEquipSlot(target, spellZone)) {
    DynamicEquip_DiscardLinkForSpellZone(spellZone);
    return;
  }

  Duel_ActivateContinuousZone(spellZone);
  NotifyDynamicEquipFieldChanged();
  Duel_ShowEffectText(BIG_BANG_SHOT);
}

APPEND_TEXT void EffectBigBangShot(void)
{
  struct DuelCard *target = gFixedZones[gSpellEffectData.row1][gSpellEffectData.col1];

  if (!Duel_IsMonsterZoneTarget(target->id)) {
    if (!gHideEffectText)
      PlayMusic(SFX_FORBIDDEN);
    return;
  }

  if (Duel_TryResolveSpellThroughTraps(BIG_BANG_SHOT, BigBangShot_ResolveBody) == DUEL_ACTION_BLOCKED)
    return;
}

#if !defined(__GNUC__)
#error Big Bang Shot self-check requires GCC
#elif __GNUC__
void BigBangShot_SelfCheck(void)
{
  if (BigBangShot_EncodeSlot(2, 3) != 0x34)
    return;
  if (BigBangShot_SpellColFromSlot(0x34) != 2)
    return;
  BigBangShot_ResetAllBoosts();
}
#endif
