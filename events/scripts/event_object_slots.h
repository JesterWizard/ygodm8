#ifndef EVENT_OBJECT_SLOTS_H
#define EVENT_OBJECT_SLOTS_H

/* Object slot aliases for event scripts.
 *
 * The player always occupies slot 0. Other characters use different slots
 * in each scene — define SLOT_<character> at the top of the map script
 * right after the includes, then use those names in object commands:
 *
 *   #define SLOT_YUGI 13
 *   #define SLOT_JOEY 14
 *
 *   LOAD_SPRITE(14, SPRITE_JOEY)
 *   MOVE_OBJECT(SPRITE_JOEY, DIRECTION_LEFT, 32, 0)
 *   SHOW_OBJECT(SPRITE_YUGI, 50, 74, 0, 0, 0)
 *
 * Object commands accept SPRITE_* names when that sprite is bound to exactly
 * one slot by a prior LOAD_SPRITE in the same script. Use explicit slot ids
 * when the same sprite appears on multiple slots.
 *
 * REACTION and OBJECT_EFFECT accept SPRITE_* names (resolved to slot
 * bitmasks), OBJECT_N constants, or combinations with |.
 */

#define SLOT_PLAYER 0

#endif
