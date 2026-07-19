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
  DECK_MENU_PICK_LABEL_RETURN_TO_TRUNK,
  DECK_MENU_PICK_LABEL_SYNCHRO_SUMMON,
  DECK_MENU_PICK_LABEL_XYZ_SUMMON,
};

#define DECK_MENU_PICK_MAX_OPTIONS 3
#define DECK_MENU_PICK_RESULT_CANCEL 0xFF

/* ponytail: card-opened duel trunk views should bracket menu calls with
 * Begin/End so duel graphics are restored consistently on every exit path. */
bool8 DeckMenuMainPickConfirmWithLabels(const u8 *labels, u8 labelCount);
/* Returns DECK_MENU_PICK_LABEL_* for the confirmed action, or
 * DECK_MENU_PICK_RESULT_CANCEL if the player backs out of the submenu. */
u8 DeckMenuMainPickChosenLabel(const u8 *labels, u8 labelCount);
bool8 DeckMenuMainPickConfirm(void);

/* Opens a read-only card list viewer.  gDeckMenu.cards[] must be
 * populated with card IDs before calling.  Handles save/restore of
 * gDeckMenu internally. */
void CardListViewerOpenLoaded(u8 cardCount);

#endif // GUARD_DECK_MENU_H
