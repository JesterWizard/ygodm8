#ifndef THE_WICKED_ERASER_H
#define THE_WICKED_ERASER_H

#include "card.h"

extern u8 gTheWickedEraserFieldWipePending;
extern u8 gTheWickedEraserFieldWipeTurnRow;
extern u8 gTheWickedEraserFieldWipeFromField;

void ClearTheWickedEraserPending(void);
void NoteTheWickedEraserGraveyardSend(struct DuelCard *zone);
unsigned char ShouldActivateTheWickedEraser(void);
void ActivateTheWickedEraser(void);
void TheWickedEraser_TryResolveFieldWipe(void);
u8 TheWickedEraser_ApplyDynamicZoneStats(struct DuelCard *zone);
void TryTheWickedEraserOnMonsterPlacement(struct DuelCard *zone);
void TheWickedEraser_OnZoneCleared(const struct DuelCard *zone);

unsigned char CanActivateTheWickedEraser(void);
void ActivateTheWickedEraserEffect(void);

#endif // THE_WICKED_ERASER_H
