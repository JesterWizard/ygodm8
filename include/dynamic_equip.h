#ifndef GUARD_DYNAMIC_EQUIP_H
#define GUARD_DYNAMIC_EQUIP_H

#define MAX_DYNAMIC_EQUIP_SLOTS 5
#define DYNAMIC_EQUIP_COORD_INVALID 0xFF

struct DynamicEquipLink
{
  u8 active;
  u8 spellFixedRow;
  u8 spellFixedCol;
  u8 targetFixedRow;
  u8 targetFixedCol;
  u16 spellId;
  u8 appliedStages;
};

extern struct DynamicEquipLink gDynamicEquipLinks[MAX_DYNAMIC_EQUIP_SLOTS];

void ResetDynamicEquips(void);
u8 CountDuelistSpellTrapBackrowCards(u8 duelist);
u8 CountDuelistMonsterRowCards(u8 duelist);
u8 GetDuelistForZone(const struct DuelCard *zone);
u8 RegisterDynamicEquip(struct DuelCard *spellZone, struct DuelCard *targetZone, u16 spellId, u8 stages);
void ApplyDynamicEquipStages(struct DuelCard *targetZone, u8 stages);
void RemoveDynamicEquipStages(struct DynamicEquipLink *link);
s8 GetDynamicEquipStageDelta(const struct DuelCard *zone);
u8 IsActiveDynamicEquipSpellZone(const struct DuelCard *zone);
void OnDynamicEquipZoneAboutToClear(struct DuelCard *zone);
u8 HasActiveDynamicEquips(void);
u8 FieldHasActiveDynamicEquipSpellOnBoard(void);
void RecalculateAllDynamicEquips(void);
void NotifyDynamicEquipFieldChanged(void);
void DynamicEquip_DiscardLinkForSpellZone(const struct DuelCard *zone);
void DynamicEquip_DiscardLinkForTargetZone(struct DuelCard *zone);
u8 DynamicEquipTargetsMonsterWithSpell(const struct DuelCard *target, u16 spellId);

#endif // GUARD_DYNAMIC_EQUIP_H
