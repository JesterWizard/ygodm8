#ifndef GUARD_REPTILIANNE_SCYLLA_H
#define GUARD_REPTILIANNE_SCYLLA_H

#define REPTILIANNE_SCYLLA_PENDING_NONE 0xFF

extern u8 gPendingReptilianneScyllaController;
extern u8 gPendingReptilianneScyllaGraveyardDuelist;

void ApplyReptilianneScyllaBattleEffect(void);
void ResolveReptilianneScyllaBattleEffect(void);
void ClearReptilianneScyllaPending(void);

#endif
