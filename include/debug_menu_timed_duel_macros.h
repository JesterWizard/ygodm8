#ifndef GUARD_DEBUG_MENU_TIMED_DUEL_MACROS_H
#define GUARD_DEBUG_MENU_TIMED_DUEL_MACROS_H

/* Card slot helpers for debug_menu_timed_duel_layouts.c */
#define TD_EMPTY                  { CARD_NONE, FALSE, FALSE, 0 }
#define TD_ATK(card)              { (card), TRUE, FALSE, 0 }
#define TD_ATK_STAGE(card, stage) { (card), TRUE, FALSE, (stage) }
#define TD_DEF(card)              { (card), TRUE, TRUE, 0 }
#define TD_SET(card)              { (card), FALSE, FALSE, 0 }
#define TD_FACEUP(card)           { (card), TRUE, FALSE, 0 }

#endif // GUARD_DEBUG_MENU_TIMED_DUEL_MACROS_H
