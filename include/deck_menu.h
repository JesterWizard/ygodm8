#ifndef GUARD_DECK_MENU_H
#define GUARD_DECK_MENU_H

#include "gba/types.h"

void DeckMenuMain(void);
void DeckMenuMainReadOnly(void);
void DeckMenu_BeginDuelTrunkView(void);
void DeckMenu_EndDuelTrunkView(void);

enum {
  DECK_MENU_PICK_LABEL_DETAILS,
  DECK_MENU_PICK_LABEL_FUSION_SUMMON,
  DECK_MENU_PICK_LABEL_SELECT_CARD,
};

#define DECK_MENU_PICK_MAX_OPTIONS 3

/* ponytail: card-opened duel trunk views should bracket menu calls with
 * Begin/End so duel graphics are restored consistently on every exit path. */
bool8 DeckMenuMainPickConfirmWithLabels(const u8 *labels, u8 labelCount);
bool8 DeckMenuMainPickConfirm(void);

#endif // GUARD_DECK_MENU_H
