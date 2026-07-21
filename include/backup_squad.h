#ifndef GUARD_BACKUP_SQUAD_H
#define GUARD_BACKUP_SQUAD_H

#include "gba/types.h"

#define BACKUP_SQUAD_DAMAGE_THRESHOLD 1000

/* Wire from battle_damage_hooks after LP battle damage is applied. */
void ApplyBackupSquadAfterDamage(s32 damage, u8 damagedFixedDuelist);

#endif /* GUARD_BACKUP_SQUAD_H */
